//
// Created by uros on 20/04/22.
//

#ifndef PARALLEL_REGRESSION_MAINWINDOW_H
#define PARALLEL_REGRESSION_MAINWINDOW_H

#include "QMainWindow"
#include "QPushButton"
#include "QString"
#include "QGridLayout"
#include "QSpinBox"
#include "QLabel"

class MainWindow : public QMainWindow {
Q_OBJECT
public:
    MainWindow(const QString &title);
//     ~MainWindow();

private:
    QLabel *label_x_min;
    QLabel *label_x_max;
    QLabel *label_points;
    QLabel *label_x_err;
    QLabel *label_y_err;

    QSpinBox *input_x_min;
    QSpinBox *input_x_max;
    QSpinBox *input_points;
    QSpinBox *input_x_err;
    QSpinBox *input_y_err;
    QPushButton *button_serial;
    QPushButton *button_for;
    QPushButton *button_task;

};


#endif //PARALLEL_REGRESSION_MAINWINDOW_H
