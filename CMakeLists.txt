cmake_minimum_required(VERSION 3.14)

project(CommandTVK LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core SerialPort)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core SerialPort)

add_executable(CommandTVK
    command/nt17command.h
    command/interfacecmd.h
    command/nt19command.h
    ui/nt17ui.h
    controller/controller.h
    controller/nt17controller.h
    model/nt17model.h

    command/interfacecmd.cpp
    command/nt17command.cpp
    command/nt19command.cpp
    ui/nt17ui.cpp
    controller/controller.cpp
    main.cpp
    controller/nt17controller.cpp
    model/nt17model.cpp
)
target_link_libraries(CommandTVK Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::SerialPort)
