#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QPoint>
#include <QPropertyChangeHandler>

namespace Ui
{
    class MainWindow;
}

class EventFilter;
class InteractionsRecrorder;
class IScriptSerializer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    std::unique_ptr<Ui::MainWindow> m_ui;
    std::shared_ptr<IScriptSerializer> m_serializer;

    QLabel* m_statusKeyLabel;

    EventFilter* m_eventFilter;
    InteractionsRecrorder* m_engine;

    std::vector<QPropertyNotifier> m_notifiers;
};

#endif // MAINWINDOW_H
