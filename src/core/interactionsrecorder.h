#ifndef INTERACTIONSRECORDER_H
#define INTERACTIONSRECORDER_H

#include "core/commands/imacrocommand.h"

#include <QElapsedTimer>
#include <QList>
#include <QObject>
#include <QPoint>
#include <QProperty>

class IScriptSerializer;
class EventFilter;

/**
 * @class   InteractionsRecrorder
 * @brief   A controller orchestrating the recording, playback, and serialization of commands
 *
 * Acts as the mediator between the EventFilter (which captures raw input),
 * the IScriptSerializer (which handles I/O), and the Target Widget (where commands are executed).
 *
 * Usage Example:
 * @code
 * ...
 * m_recorder = new InteractionsRecrorder(ui->canvasWidget, serializer, filter, this);
 *
 * m_replayingChangeNotifier = m_recorder->bindableIsReplaying().addNotifier([this]() { ... }));
 * m_recordingChangeNotifier = m_recorder->bindableIsRecording().addNotifier([this]() { ... }));
 *
 * connect(ui->btnRecord, &QPushButton::clicked, m_recorder, &InteractionsRecrorder::toggleRecording);
 * connect(ui->btnReplay, &QPushButton::clicked, m_recorder, &InteractionsRecrorder::startReplay);
 * ...
 * @endcode
 */
class InteractionsRecrorder : public QObject
{
    Q_OBJECT

public:
    explicit InteractionsRecrorder(QWidget* targetWidget, std::shared_ptr<IScriptSerializer> serializer, EventFilter* filter,
                                   QObject* parent = nullptr);

    /**
     * @brief Returns a bindable property for the recording state
     * @return A QBindable<bool> that UI elements can bind to for automatic updates
     */
    QBindable<bool> bindableIsRecording() { return &m_isRecording; }
    /**
     * @brief Returns a bindable property for the replaying state
     * @return A QBindable<bool> that UI elements can bind to for automatic updates
     */
    QBindable<bool> bindableIsReplaying() { return &m_isReplaying; }
    /**
     * @brief Returns a bindable property for the looping state
     * @return A QBindable<bool> that UI elements can bind to for automatic updates
     */
    QBindable<bool> bindableIsLooping() { return &m_isLooping; }
    /**
     * @brief Checks if the controller is currently recording user inputs
     * @return true if actively recording, false otherwise
     */
    bool isRecording() const { return m_isRecording.value(); }
    /**
     * @brief Checks if the controller is currently playing back a macro
     * @return true if actively replaying, false otherwise
     */
    bool isReplaying() const { return m_isReplaying.value(); }
    /**
     * @brief Checks if the controller is currently set to looping mode
     * @return true if looping set, false otherwise
     */
    bool isLooping() const { return m_isLooping.value(); }
    /**
     * @brief Toggles the recording state on or off
     */
    void toggleRecording();
    /**
     * @brief Initiates the playback sequence of the stored commands
     */
    void startReplay();
    /**
     * @brief Sets loopling playback mode
     */
    void setLooping(bool loop) { m_isLooping = loop; };

private slots:
    void playNextCommand();
    void onCommandCaptured(std::shared_ptr<IMacroCommand> command);

private:
    QWidget* m_targetWidget;
    QList<std::shared_ptr<IMacroCommand>> m_commands;
    uint m_replayIndex{0};

    QProperty<bool> m_isRecording{false};
    QProperty<bool> m_isReplaying{false};
    QProperty<bool> m_isLooping{false};

    bool m_commandsCached{false};

    std::shared_ptr<IScriptSerializer> m_serializer{nullptr};
    EventFilter* m_eventFilter{nullptr};

private:
    bool saveScript();
    bool loadScript();
};

#endif // INTERACTIONSRECORDER_H
