#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow mainWindow("Main Window");
    mainWindow.show();
    return QApplication::exec();
}
