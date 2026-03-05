#include "clickcanvaswidget.h"

#include <QMetaEnum>
#include <QMouseEvent>
#include <QPainter>

ClickCanvasWidget::ClickCanvasWidget(QWidget* parent)
    : QWidget(parent)
{
    setFocusPolicy(Qt::StrongFocus);
    m_displayLabel = new QLabel("LastKey: None", this);
    m_displayLabel->setStyleSheet("background-color: rgba(30, 30, 30, 180);"
                                  "color: white;"
                                  "padding: 8px;"
                                  "border-radius: 5px;"
                                  "font-weight: bold;");

    m_displayLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
    m_displayLabel->adjustSize();
}

void ClickCanvasWidget::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    switch (m_lastClick.button) {
    case Qt::NoButton:    return;
    case Qt::LeftButton:  painter.setBrush(QColor(85, 255, 85, 150)); break;
    case Qt::RightButton: painter.setBrush(QColor(255, 85, 85, 150)); break;
    default:              painter.setBrush(QColor(85, 170, 255, 150));
    }

    painter.drawEllipse(m_lastClick.position, 15, 15);
}

void ClickCanvasWidget::keyPressEvent(QKeyEvent* event)
{
    auto displayText = event->text();
    if (displayText.isEmpty() || event->key() >= Qt::Key_Escape) {
        const auto metaEnum = QMetaEnum::fromType<Qt::Key>();
        const auto* keyName = metaEnum.valueToKey(event->key());

        if (keyName) {
            displayText = QString::fromUtf8(keyName);
        } else {
            displayText = QKeySequence(event->key()).toString();
        }
    }

    m_displayLabel->setText(tr("Last Key: %1").arg(displayText));
    m_displayLabel->adjustSize();
    update();

    QWidget::keyPressEvent(event);
}

void ClickCanvasWidget::mousePressEvent(QMouseEvent* event)
{

    m_lastClick = {.position = event->pos(), .button = event->button()};
    update();
    QWidget::mousePressEvent(event);
}