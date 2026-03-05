#ifndef MOUSEMOVECOMMAND_H
#define MOUSEMOVECOMMAND_H

#include "imacrocommand.h"

class MouseMoveCommand : public IMacroCommand
{
public:
    MouseMoveCommand(const QPoint& pos, const quint64 timestamp);

    void execute(QWidget* target) override;
    void accept(ICommandVisitor& visitor) const override;

    const QPoint& pos() const { return m_pos; }

private:
    QPoint m_pos;
};

#endif // MOUSEMOVECOMMAND_H
