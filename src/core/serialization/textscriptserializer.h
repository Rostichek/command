#ifndef TEXTSCRIPTSERIALIZER_H
#define TEXTSCRIPTSERIALIZER_H

#include "iscriptserializer.h"

class TextScriptSerializer : public IScriptSerializer
{
public:
    explicit TextScriptSerializer(const QString& filePath);

    bool save(const QList<std::shared_ptr<IMacroCommand>>& commands) override;
    QList<std::shared_ptr<IMacroCommand>> load() override;

private:
    QString m_filePath;
};

#endif // TEXTSCRIPTSERIALIZER_H
