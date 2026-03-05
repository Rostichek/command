#ifndef ISCRIPTSERIALIZER_H
#define ISCRIPTSERIALIZER_H

#include "core/commands/imacrocommand.h"
#include <QList>
#include <QString>

/**
 * @class   IScriptSerializer
 * @brief   Interface defining the Strategy Pattern for saving and loading macro scripts.
 *
 * Provides a standardized way to serialize a sequence of IMacroCommand objects to a
 * storage and reconstruct them back into memory.
 * Implementing classes handle the specific file formats and parsing logic.
 *
 * Usage Example:
 * @code
 * IScriptSerializer* serializer = new TextScriptSerializer("my_macro.txt");
 * if (serializer->save(m_commands)) {
 *  ...
 * }
 * ...
 * QList<std::shared_ptr<IMacroCommand>> loadedCommands = serializer->load();
 * @endcode
 */
class IScriptSerializer
{
public:
    virtual ~IScriptSerializer() = default;

    /**
     * @brief Serializes a list of macro commands to the underlying storage
     * @param commands The sequence of smart pointers representing the macro to be saved
     * @return true if the save operation completed successfully, false if an error occurred (e.g., file write permission
     * denied)
     */
    virtual bool save(const QList<std::shared_ptr<IMacroCommand>>& commands) = 0;
    /**
     * @brief Deserializes macro commands from the underlying storage
     * @return A list of newly constructed smart pointers representing the loaded command
     */
    virtual QList<std::shared_ptr<IMacroCommand>> load() = 0;
};

#endif // ISCRIPTSERIALIZER_H
