#ifndef ICOMMANDVISITOR_H
#define ICOMMANDVISITOR_H

class MouseClickCommand;
class MouseMoveCommand;
class KeyboardKeyPressCommand;

/**
 * @class   ICommandVisitor
 * @brief   Interface to decopule serialization from the command classes
 *
 * Usage Example:
 * @code
 * class TextSerializerVisitor : public ICommandVisitor {
 * public:
 * void visit(const MouseClickCommand& cmd) override {
 * // Write CLICK x y delay to file
 * }
 * // ... implement other visits ...
 * };
 * @endcode
 */
class ICommandVisitor
{
public:
    virtual ~ICommandVisitor() = default;

    /**
     * @brief Extracts data from a MouseClickCommand
     * @param command The specific mouse click command being visited
     */
    virtual void visit(const MouseClickCommand& command) = 0;

    /**
     * @brief Extracts data from a MouseMoveCommand
     * @param command The specific mouse move command being visited
     */
    virtual void visit(const MouseMoveCommand& command) = 0;

    /**
     * @brief Extracts data from a KeyboardKeyPressCommand
     * @param command The specific keyboard press command being visited
     */
    virtual void visit(const KeyboardKeyPressCommand& command) = 0;
};

#endif // ICOMMANDVISITOR_H
