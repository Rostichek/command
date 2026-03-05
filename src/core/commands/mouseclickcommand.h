#ifndef MOUSECLICKCOMMAND_H
#define MOUSECLICKCOMMAND_H

#include "imacrocommand.h"

class MouseClickCommand : public IMacroCommand
{
public:
    MouseClickCommand(const QPoint& pos, Qt::MouseButton button, const quint64 timestamp);

    void execute(QWidget* target) override;
    void accept(ICommandVisitor& visitor) const override;

    const QPoint& pos() const { return m_pos; }
    Qt::MouseButton button() const { return m_button; }

private:
    QPoint m_pos;
    Qt::MouseButton m_button;
};

#endif // MOUSECLICKCOMMAND_H
