//
// Created by uros on 20/04/22.
//

#include "MainWindow.h"

MainWindow::MainWindow(const QString &title) {

    //Main window constructor initializes all gui elements and connects buttons with event hadler functions
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

    this->input_points->setMaximum(10000000);
    this->input_x_max->setMinimum(-100);
    this->input_x_min->setMinimum(-100);
    //dummy values
    this->input_points->setValue(50);
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
    connect(button_for, &QPushButton::released, this, &MainWindow::handle_for);
    connect(button_task, &QPushButton::released, this, &MainWindow::handle_task);
}

std::vector<double> uniform_dots(double x_min, double x_max, double count) {
    std::vector<double> x;
    for (double i = x_min; i < x_max;) {
        x.push_back(i);
        i += (x_max - x_min) / count;
    }
    return x;
}

tbb::concurrent_vector<double> uniform_dots(double x_min, double x_max, double count, bool isConcurrent) {
    tbb::concurrent_vector<double> x;
    for (double i = x_min; i < x_max;) {
        x.push_back(i);
        i += (x_max - x_min) / count;
    }
    return x;
}

void render_window(InputHandler &input_handler, std::vector<Point> &points, tbb::tick_count::interval_t timer) {
    /**
     * Renders window with graph of approximated and exact linear functions
     * @param values Input handler class with parsed parameters, vector of approximated points, how much time approximation lasted
     * */
    QVector<double> x, y_original, y_approx; // initialize with entries 0..100
    for (auto i = points.begin(); i != points.end(); i++) {
        x.push_back(i->get_x());
        y_approx.push_back(i->get_y());
        y_original.push_back(input_handler.calculate_original(i->get_x()));
//        y_original.push_back(generated_points[j].get_y());
//        j++;
    }
// create graph and assign data to it:
    QCustomPlot *custom_plot = new QCustomPlot();
    custom_plot->addGraph();
    custom_plot->graph(0)->setData(x, y_original);
    custom_plot->addGraph();
    custom_plot->graph(1)->setData(x, y_approx);
    custom_plot->graph(1)->setPen(QPen(Qt::red));
// give the axes some labels:
    custom_plot->xAxis->setLabel("x");
    custom_plot->yAxis->setLabel("y");
// set axes ranges, so we see all data:
//    custom_plot->xAxis->setRange(input_x_min->value(), input_x_min->value());
//    custom_plot->yAxis->setRange(0, 1);
    custom_plot->replot();
    custom_plot->resize(1000, 1000);
//    custom_plot->show();

    QWidget *widget = new QWidget();
    QGridLayout *layout = new QGridLayout();
    std::string s = "Time: " + std::to_string(timer.seconds() * 1000) + "ms";
    QLabel *label = new QLabel(s.c_str());
    layout->addWidget(custom_plot, 0, 0);
    layout->addWidget(label, 1, 0);
    widget->setLayout(layout);
    widget->resize(1000, 1000);
    widget->show();

}

void
render_window(InputHandler &input_handler, tbb::concurrent_vector<Point> &points, tbb::tick_count::interval_t timer) {
    /**
 * Renders window with graph of approximated and exact linear functions
 * @param values Input handler class with parsed parameters, concurrent_vector of approximated points, how much time approximation lasted
 * */
    QVector<double> x, y_original, y_approx; // initialize with entries 0..100
    for (auto i = points.begin(); i != points.end(); i++) {
        x.push_back(i->get_x());
        y_approx.push_back(i->get_y());
        y_original.push_back(input_handler.calculate_original(i->get_x()));
//        y_original.push_back(generated_points[j].get_y());
//        j++;
    }
// create graph and assign data to it:
    QCustomPlot *custom_plot = new QCustomPlot();
    custom_plot->addGraph();
//    custom_plot->graph(0)->setData(x, y_original);
//    custom_plot->graph(0)->setPen(QPen(Qt::blue));
    custom_plot->addGraph();
    custom_plot->graph(1)->setData(x, y_approx);
    custom_plot->graph(1)->setPen(QPen(Qt::red));
// give the axes some labels:
    custom_plot->xAxis->setLabel("x");
    custom_plot->yAxis->setLabel("y");
// set axes ranges, so we see all data:
//    custom_plot->xAxis->setRange(input_x_min->value(), input_x_min->value());
//    custom_plot->yAxis->setRange(0, 1);
    custom_plot->replot();
    custom_plot->resize(1000, 1000);
//    custom_plot->show();

    QWidget *widget = new QWidget();
    QGridLayout *layout = new QGridLayout();
    std::string s = "Time: " + std::to_string(timer.seconds() * 1000) + "ms";
    QLabel *label = new QLabel(s.c_str());
    layout->addWidget(custom_plot, 0, 0);
    layout->addWidget(label, 1, 0);
    widget->setLayout(layout);
    widget->resize(1000, 1000);
    widget->show();

}


void MainWindow::handle_serial() {
    // handle function for serial button

    this->generate_points();

    std::vector<double> x_uniform = uniform_dots(input_x_min->value(), input_x_max->value(), input_points->value());
    tbb::tick_count start_time = tbb::tick_count::now();
    serial_linear_regression.calculate_Function(generated_points);
    std::vector<Point> points = serial_linear_regression.calculate_points(x_uniform);
    tbb::tick_count end_time = tbb::tick_count::now();
    render_window(input_handler, points, (end_time - start_time));
    std::cout << serial_linear_regression.a << "," << serial_linear_regression.b << std::endl;
    // generate some data:


}

void MainWindow::handle_for() {
    // handle function for parallel_for button

    this->generate_points();

    tbb::concurrent_vector<double> x_uniform = uniform_dots(input_x_min->value(), input_x_max->value(),
                                                            input_points->value(), true);
    tbb::tick_count start_time = tbb::tick_count::now();
    for_parallel_regression.calculate_Function(generated_points);
    tbb::concurrent_vector<Point> points = for_parallel_regression.calculate_points(x_uniform);
    tbb::tick_count end_time = tbb::tick_count::now();
    render_window(input_handler, points, (end_time - start_time));
    std::cout << for_parallel_regression.a << "," << for_parallel_regression.b << std::endl;
}

void MainWindow::generate_points() {
    if (generated_points.size() != 0 && generated_points.size() ==input_points->value()) return;
    this->generated_points = input_handler.generate_dots
            (input_x_min->value(), input_x_max->value(), input_x_err->value(), input_y_err->value(),
             input_points->value());
}

void MainWindow::handle_task() {
    // handle function for task parallel button

    this->generate_points();

    tbb::concurrent_vector<double> x_uniform = uniform_dots(input_x_min->value(), input_x_max->value(),
                                                            input_points->value(), true);
    tbb::tick_count start_time = tbb::tick_count::now();
    task_parallel_regression.calculate_Function(generated_points);
    tbb::concurrent_vector<Point> points = task_parallel_regression.calculate_points(x_uniform);
    tbb::tick_count end_time = tbb::tick_count::now();
    render_window(input_handler, points, (end_time - start_time));
    std::cout << task_parallel_regression.a << "," << task_parallel_regression.b << std::endl;
}

void MainWindow::file_test() {
    std::ifstream infile;
    infile.open("../data/file_test");

    if (!infile.is_open()) {
        std::cout << "Couldn't open file " << INPUT_FILE << std::endl;
        std::exit(-2);
    }
    std::string s;
    getline(infile, s);
    int is_file = std::stod(s);
    if (is_file ==0){
        this->show();
        return;
    }
    else{
        this->input_points->setValue(input_handler.point_num);
        this->input_y_err->setValue(input_handler.y_err);
        this->input_x_err->setValue(input_handler.x_err);
        this->input_x_max->setValue(input_handler.max_x);
        this->input_x_min->setValue(input_handler.min_x);

        this->handle_serial();
        this->handle_for();

        for(auto i:input_handler.cutoff){
            task_parallel_regression.cutoff = i;
            this->handle_task();
        }


    }

}



//MainWindow::~MainWindow() noexcept {
//    delete this->button_serial;
//    delete this->button_for;
//    delete this->button_task;
//}