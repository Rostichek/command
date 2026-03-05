#ifndef IMACROCOMMAND_H
#define IMACROCOMMAND_H

#include <QString>
#include <QWidget>

class ICommandVisitor;

/**
 * @class   IMacroCommand
 * @brief   Abstract base class representing a single recorded interaction
 *
 * Defines the standard interface for executing and serializing user interactions
 * (like mouse clicks or key presses). Each command stores the hardware timestamp
 * of when it was recorded to ensure accurate replay timing.
 */
class IMacroCommand
{
public:
    explicit IMacroCommand(quint64 timestamp)
        : m_timestamp(timestamp) {};
    virtual ~IMacroCommand() = default;

    /**
     * @brief Performs the recorded action on the specified target widget
     * @param target The QWidget on which the simulated event should be posted/executed
     */
    virtual void execute(QWidget* target) = 0;

    /**
     * @brief Accepts a visitor to perform external operations (like serialization)
     * @param visitor The visitor instance that will process this command
     */
    virtual void accept(ICommandVisitor& visitor) const = 0;

    /**
     * @brief Retrieves the timestamp of when this command was originally recorded
     * @return The timestamp in milliseconds
     */
    quint64 timestamp() const { return m_timestamp; }

private:
    quint64 m_timestamp{0};
};

#endif // IMACROCOMMAND_H
