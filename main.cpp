#include "core/commands/imacrocommand.h"
#include "ui/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    qRegisterMetaType<std::shared_ptr<IMacroCommand>>();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
