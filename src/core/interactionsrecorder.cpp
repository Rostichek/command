#include "interactionsrecorder.h"

#include "core/serialization/iscriptserializer.h"
#include "eventfilter.h"

#include <QMetaObject>
#include <QTimer>

InteractionsRecrorder::InteractionsRecrorder(QWidget* targetWidget, std::shared_ptr<IScriptSerializer> serializer, EventFilter* filter,
                                             QObject* parent)
    : QObject{parent},
      m_targetWidget(targetWidget),
      m_isRecording(false),
      m_isReplaying(false),
      m_replayIndex(0),
      m_serializer(serializer),
      m_eventFilter(filter)
{
    if (m_eventFilter) {
        connect(m_eventFilter, &EventFilter::commandCaptured, this, &InteractionsRecrorder::onCommandCaptured);
        connect(m_eventFilter, &EventFilter::abortSequence, this, [this] { m_isReplaying = false; });
    }
}

void InteractionsRecrorder::toggleRecording()
{
    if (m_isReplaying) return;

    if (!m_isRecording) {
        m_commands.clear();
        m_isRecording = true;
    } else {
        m_isRecording = false;
        m_commandsCached = false;
        saveScript();
    }
}

void InteractionsRecrorder::startReplay()
{
    if (m_isRecording || m_isReplaying) {
        return;
    }

    loadScript();

    m_isReplaying = true;
    m_replayIndex = 0;

    playNextCommand();
}

void InteractionsRecrorder::playNextCommand()
{
    if (!m_isReplaying) return;

    if (m_replayIndex >= m_commands.size()) {
        if (m_isLooping) {
            m_replayIndex = 0;
        } else {
            m_isReplaying = false;
            return;
        }
    }
    const auto previousCommand = m_commands.at(m_replayIndex > 0 ? m_replayIndex - 1 : 0);
    const auto command = m_commands.at(m_replayIndex++);

    const quint64 delay
        = (command->timestamp() > previousCommand->timestamp()) ? (command->timestamp() - previousCommand->timestamp()) : 0;

    QTimer::singleShot(delay, this, [this, command]() {
        if (!m_isReplaying) return;

        command->execute(m_targetWidget);
        QMetaObject::invokeMethod(this, "playNextCommand", Qt::QueuedConnection);
    });
}

bool InteractionsRecrorder::saveScript()
{
    if (!m_serializer || m_commands.isEmpty()) return false;
    return m_serializer->save(m_commands);
}

bool InteractionsRecrorder::loadScript()
{
    if (!m_serializer) return false;

    const auto loadedCommands = m_serializer->load();
    m_commandsCached = true;

    if (loadedCommands.isEmpty()) return false;

    m_commands = loadedCommands;
    return true;
}

void InteractionsRecrorder::onCommandCaptured(std::shared_ptr<IMacroCommand> command)
{
    if (!m_isRecording.value()) {
        return;
    }

    m_commands.append(command);
}
