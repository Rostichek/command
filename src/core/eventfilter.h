#ifndef EVENTFILTER_H
#define EVENTFILTER_H

#include <QObject>
#include <QPoint>
#include <QString>

class IMacroCommand;

/**
 * @class   EventFilter
 * @brief   Intercepts user input events and convert them into IMacroCommand
 *
 * Usage Example:
 * @code
 * EventFilter* recorder = new EventFilter(this);
 * qApp->installEventFilter(recorder);
 * * connect(recorder, &EventFilter::commandCaptured,
 * m_engine, &InteractionsRecroder::onCommandCaptured);
 * @endcode
 */
class EventFilter : public QObject
{
    Q_OBJECT

public:
    explicit EventFilter(QObject* parent = nullptr);

    /**
     * @brief Core Qt event interception method
     * Evaluates incoming events and emits commandCaptured for every supported event. Do nothing otherwise
     * @param watched The object that the event was originally destined for
     * @param event The Qt event being intercepted
     * @return always returns false, so this fitler doesn't block any events, just act as a middleware
     */
    bool eventFilter(QObject* watched, QEvent* event) override;

signals:
    /**
     * @brief Emitted whenever a user interaction is successfully parsed
     * @param command A shared pointer containing the newly generated command
     */
    void commandCaptured(std::shared_ptr<IMacroCommand> command);

    /**
     * @brief Emitted whenever a user presses Esc button
     */
    void abortSequence();
};

#endif // EVENTFILTER_H
