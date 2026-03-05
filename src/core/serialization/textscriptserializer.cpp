#include "textscriptserializer.h"

#include "core/commands/keyboardkeypresscommand.h"
#include "core/commands/mouseclickcommand.h"
#include "core/commands/mousemovecommand.h"
#include "serialization/visitors/textsavevisitor.h"

#include <QFile>
#include <QStringList>
#include <QTextStream>

TextScriptSerializer::TextScriptSerializer(const QString& filePath)
    : IScriptSerializer{},
      m_filePath(filePath)
{
}

bool TextScriptSerializer::save(const QList<std::shared_ptr<IMacroCommand>>& commands)
{
    QFile file(m_filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream out(&file);
    TextSaveVisitor visitor(out);

    for (const auto& cmd : commands) {
        if (!cmd) continue;
        cmd->accept(visitor);
    }

    file.close();
    return true;
}

QList<std::shared_ptr<IMacroCommand>> TextScriptSerializer::load()
{
    QList<std::shared_ptr<IMacroCommand>> commands;
    QFile file(m_filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return commands;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) {
            continue;
        }

        QStringList parts = line.split(" ", Qt::SkipEmptyParts);
        QString type = parts[0];

        const auto timestamp = parts[1].toULongLong();

        if (type == QStringLiteral("CLICK") && parts.size() >= 5) {
            QPoint pos(parts[2].toInt(), parts[3].toInt());
            auto button = static_cast<Qt::MouseButton>(parts[4].toInt());
            commands.append(std::make_shared<MouseClickCommand>(pos, button, timestamp));
        } else if (type == QStringLiteral("MOVE") && parts.size() >= 4) {
            QPoint pos(parts[2].toInt(), parts[3].toInt());
            commands.append(std::make_shared<MouseMoveCommand>(pos, timestamp));
        } else if (type == QStringLiteral("KEY") && parts.size() >= 4) {
            int key = parts[2].toInt();
            QString text = parts.mid(3).join(" ");
            commands.append(std::make_shared<KeyboardKeyPressCommand>(key, text, timestamp));
        }
    }
    return commands;
}