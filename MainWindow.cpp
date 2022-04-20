//
// Created by uros on 20/04/22.
//

#include "MainWindow.h"

MainWindow::MainWindow(const QString &title) {
    this->setWindowTitle(title);

    this->button_serial = new QPushButton("Serial Least Squares", nullptr);
    this->button_for = new QPushButton("For Least Squares", nullptr);
    this->button_task = new QPushButton("Task Least Squares", nullptr);

    this->input_x_min = new QSpinBox();
    this->label_x_min = new QLabel("x min");

    this->input_x_max = new QSpinBox();
    this->label_x_max = new QLabel("x max");

    this->input_points = new QSpinBox();
    this->label_points = new QLabel("points count");

    this->input_x_err = new QSpinBox();
    this->label_x_err = new QLabel("x error %");

    this->input_y_err = new QSpinBox();
    this->label_y_err = new QLabel("y error %");

    QGridLayout *mainLayout = new QGridLayout;
    this->button_task->resize(100, 100);
    this->button_for->resize(100, 100);
    this->button_serial->resize(100, 100);

    this->input_points->setMaximum(10000);
    this->input_x_max->setMinimum(-100);
    this->input_x_min->setMinimum(-100);
    //dummy values
    this->input_points->setValue(1000);
    this->input_y_err->setValue(2);
    this->input_x_err->setValue(5);
    this->input_x_max->setValue(5);
    this->input_x_min->setValue(0);


    mainLayout->addWidget(this->label_x_min, 0, 0);
    mainLayout->addWidget(this->input_x_min, 1, 0);
    mainLayout->addWidget(this->label_x_max, 0, 1);
    mainLayout->addWidget(this->input_x_max, 1, 1);
    mainLayout->addWidget(this->label_points, 0, 2);
    mainLayout->addWidget(this->input_points, 1, 2);
    mainLayout->addWidget(this->label_x_err, 0, 3);
    mainLayout->addWidget(this->input_x_err, 1, 3);
    mainLayout->addWidget(this->label_y_err, 0, 4);
    mainLayout->addWidget(this->input_y_err, 1, 4);

    mainLayout->addWidget(this->button_serial, 2, 1);
    mainLayout->addWidget(this->button_for, 2, 2);
    mainLayout->addWidget(this->button_task, 2, 3);
    QWidget *wdg = new QWidget(this);
    wdg->resize(300, 100);
    wdg->setLayout(mainLayout);

    this->setCentralWidget(wdg);
    this->resize(300, 100);
}
//MainWindow::~MainWindow() noexcept {
//    delete this->button_serial;
//    delete this->button_for;
//    delete this->button_task;
//}