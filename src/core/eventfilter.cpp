#include "eventfilter.h"

#include "core/commands/keyboardkeypresscommand.h"
#include "core/commands/mouseclickcommand.h"
#include "core/commands/mousemovecommand.h"

#include <QEvent>
#include <QKeyEvent>
#include <QMouseEvent>

EventFilter::EventFilter(QObject* parent)
    : QObject(parent)
{
}

bool EventFilter::eventFilter(QObject* watched, QEvent* event)
{
    const auto* mouseEvent = static_cast<QMouseEvent*>(event);
    const auto* keyEvent = static_cast<QKeyEvent*>(event);

    switch (event->type()) {
    case QEvent::MouseMove:
        emit commandCaptured(std::make_shared<MouseMoveCommand>(mouseEvent->pos(), mouseEvent->timestamp()));
        break;
    case QEvent::MouseButtonPress:
        emit commandCaptured(
            std::make_shared<MouseClickCommand>(mouseEvent->pos(), mouseEvent->button(), mouseEvent->timestamp()));
        break;
    case QEvent::KeyPress:
        if (keyEvent->key() == Qt::Key_Escape) {
            emit abortSequence();
            return true;
        }
        emit commandCaptured(
            std::make_shared<KeyboardKeyPressCommand>(keyEvent->key(), keyEvent->text(), keyEvent->timestamp()));
        break;
    default: break;
    }
    return false;
}
