cmake_minimum_required(VERSION 3.22)
project(Parallel_regression)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(Parallel_regression main.cpp Point.cpp Point.h InputHandler.cpp InputHandler.h SerialLinearRegression.cpp SerialLinearRegression.h MainWindow.cpp MainWindow.h)
target_link_libraries(Parallel_regression
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        TBB::tbb
        )

list(APPEND CMAKE_MODULE_PATH "deps/tbb/cmake/")

find_package(TBB REQUIRED)

