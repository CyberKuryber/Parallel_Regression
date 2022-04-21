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

    input_handler.parse_input();


    connect(button_serial, &QPushButton::released, this, &MainWindow::handle_serial);
}

std::vector<double> uniform_dots(double x_min, double x_max, double count) {
    std::vector<double> x;
    for (int i = x_min; i < x_max; i += (x_max - x_min) / count) {
        x.push_back(i);
    }
    return x;
}


void MainWindow::handle_serial() {
    tbb::concurrent_vector<Point> generated_points = input_handler.generate_dots
            (input_x_min->value(), input_x_max->value(), input_x_err->value(), input_y_err->value(),
             input_points->value());

    std::vector<double> x_uniform = uniform_dots(input_x_min->value(), input_x_max->value(), input_points->value());
    serial_linear_regression.calculate_Function(generated_points);


    std::vector<Point> points = serial_linear_regression.calculate_points(x_uniform);

    // generate some data:
    QVector<double> x, y_original, y_approx; // initialize with entries 0..100
    for (auto i = points.begin();i != points.end();i++) {
        x.push_back(i->get_x());
        y_approx.push_back(i->get_y());
        y_original.push_back(input_handler.calculate_original(i->get_x()));
    }
// create graph and assign data to it:
    QCustomPlot *customPlot = new QCustomPlot();
    customPlot->addGraph();
    customPlot->graph(0)->setData(x, y_original);
    customPlot->graph(1)->setData(x, y_approx);
// give the axes some labels:
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");
// set axes ranges, so we see all data:
    customPlot->xAxis->setRange(-1, 1);
    customPlot->yAxis->setRange(0, 1);
    customPlot->replot();

}

//MainWindow::~MainWindow() noexcept {
//    delete this->button_serial;
//    delete this->button_for;
//    delete this->button_task;
//}