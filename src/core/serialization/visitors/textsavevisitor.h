#ifndef TEXTSAVEVISITOR_H
#define TEXTSAVEVISITOR_H

#include "icommandvisitor.h"

#include <QTextStream>

class TextSaveVisitor : public ICommandVisitor
{
public:
    explicit TextSaveVisitor(QTextStream& stream);

    void visit(const MouseClickCommand& command) override;
    void visit(const MouseMoveCommand& command) override;
    void visit(const KeyboardKeyPressCommand& command) override;

private:
    QTextStream& m_out;
};

#endif // TEXTSAVEVISITOR_H
