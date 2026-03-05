#include "textsavevisitor.h"

#include "commands/keyboardkeypresscommand.h"
#include "commands/mouseclickcommand.h"
#include "commands/mousemovecommand.h"

TextSaveVisitor::TextSaveVisitor(QTextStream& stream)
    : ICommandVisitor{},
      m_out(stream)
{
}

void TextSaveVisitor::visit(const MouseClickCommand& command)
{
    m_out << QStringLiteral("CLICK %1 %2 %3 %4")
                 .arg(command.timestamp())
                 .arg(command.pos().x())
                 .arg(command.pos().y())
                 .arg(command.button())
          << Qt::endl;
}

void TextSaveVisitor::visit(const MouseMoveCommand& command)
{
    m_out << QStringLiteral("MOVE %1 %2 %3").arg(command.timestamp()).arg(command.pos().x()).arg(command.pos().y()) << Qt::endl;
}

void TextSaveVisitor::visit(const KeyboardKeyPressCommand& command)
{
    m_out << QStringLiteral("KEY %1 %2 %3").arg(command.timestamp()).arg(command.button()).arg(command.text()) << Qt::endl;
}