#include "mousemovecommand.h"

#include "serialization/visitors/icommandvisitor.h"

#include <QCoreApplication>
#include <QMouseEvent>
#include <QPoint>

MouseMoveCommand::MouseMoveCommand(const QPoint& pos, const quint64 timestamp)
    : IMacroCommand{timestamp},
      m_pos(pos)
{
}

void MouseMoveCommand::execute(QWidget* target)
{
    QPoint globalScreenPos = target->mapToGlobal(m_pos);
    QCursor::setPos(globalScreenPos);
}

void MouseMoveCommand::accept(ICommandVisitor& visitor) const
{
    visitor.visit(*this);
}