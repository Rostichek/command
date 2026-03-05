#ifndef KEYBOARDKEYPRESSCOMMAND_H
#define KEYBOARDKEYPRESSCOMMAND_H

#include "imacrocommand.h"

class KeyboardKeyPressCommand : public IMacroCommand
{
public:
    KeyboardKeyPressCommand(int key, const QString& text, const quint64 timestamp);

    void execute(QWidget* target) override;
    void accept(ICommandVisitor& visitor) const override;

    int button() const { return m_key; }
    const QString& text() const { return m_text; }

private:
    int m_key;
    QString m_text;
};

#endif // KEYBOARDKEYPRESSCOMMAND_H
