#include "keyboardkeypresscommand.h"

#include "serialization/visitors/icommandvisitor.h"

#include <QCoreApplication>
#include <QMouseEvent>
#include <QPoint>

KeyboardKeyPressCommand::KeyboardKeyPressCommand(int key, const QString& text, const quint64 timestamp)
    : IMacroCommand{timestamp},
      m_key(key),
      m_text(text)
{
}

void KeyboardKeyPressCommand::execute(QWidget* target)
{
    auto* pressEvent = new QKeyEvent{QEvent::KeyPress, m_key, Qt::NoModifier, m_text};
    auto* releaseEvent = new QKeyEvent{QEvent::KeyRelease, m_key, Qt::NoModifier, m_text};

    QCoreApplication::postEvent(target, pressEvent);
    QCoreApplication::postEvent(target, releaseEvent);
}

void KeyboardKeyPressCommand::accept(ICommandVisitor& visitor) const
{
    visitor.visit(*this);
}
