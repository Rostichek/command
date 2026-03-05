#ifndef CLICKCANVASWIDGET_H
#define CLICKCANVASWIDGET_H

#include <QLabel>
#include <QPoint>
#include <QWidget>

class ClickCanvasWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClickCanvasWidget(QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

private:
    struct ClickIndicator {
        QPoint position;
        Qt::MouseButton button{Qt::NoButton};
    };

    ClickIndicator m_lastClick;
    QLabel* m_displayLabel{nullptr};
};

#endif // CLICKCANVASWIDGET_H
