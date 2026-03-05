#include "mouseclickcommand.h"

#include "serialization/visitors/icommandvisitor.h"

#include <QCoreApplication>
#include <QMouseEvent>
#include <QPoint>

MouseClickCommand::MouseClickCommand(const QPoint& pos, Qt::MouseButton button, const quint64 timestamp)
    : IMacroCommand{timestamp},
      m_pos(pos),
      m_button(button)
{
}

void MouseClickCommand::execute(QWidget* target)
{
    auto* pressEvent = new QMouseEvent{QEvent::MouseButtonPress, m_pos, m_pos, m_button, m_button, Qt::NoModifier};
    auto* releaseEvent = new QMouseEvent{QEvent::MouseButtonRelease, m_pos, m_pos, m_button, m_button, Qt::NoModifier};

    QCoreApplication::postEvent(target, pressEvent);
    QCoreApplication::postEvent(target, releaseEvent);
}

void MouseClickCommand::accept(ICommandVisitor& visitor) const
{
    visitor.visit(*this);
}