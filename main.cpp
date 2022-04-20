#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QPushButton button_serial("Serial Least Squares", nullptr);
    QPushButton button_for("For Least Squares", nullptr);
    QPushButton button_task("Task Least Squares", nullptr);
    button_serial.resize(100,50);
    button_for.resize(100,50);
    button_task.resize(100,50);
    button_serial.show();
    button_for.show();
    button_task.show();
    return QApplication::exec();
}
