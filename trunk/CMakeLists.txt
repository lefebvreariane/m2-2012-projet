cmake_minimum_required(VERSION 2.8)

project(Bender)

find_package(Qt4 REQUIRED)

qt4_wrap_ui(UI_HEADERS src/mainwindow.ui)
qt4_wrap_cpp(QT_INHERITED_SRCS src/mainwindow.h)
set(HEADERS
    ${UI_HEADERS}
    src/mainwindow.h)
set(SOURCES
    ${HEADERS}
    src/main.cpp
    src/mainwindow.cpp
    ${QT_INHERITED_SRCS})

QT4_WRAP_CPP(HEADER_MOC
    ${HEADERS})

include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

add_executable(../bin/bender
    ${SOURCES}
    ${HEADER_MOC})
target_link_libraries(../bin/bender
    ${QT_LIBRARIES})
