#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow main_window("Main Window");
//    main_window.show();
    main_window.file_test();
    return QApplication::exec();
}
