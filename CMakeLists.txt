cmake_minimum_required(VERSION 3.16)
project(Grupo1_Singleton LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(core STATIC
    src/core/ConfigManager.cpp
    src/core/ConfigStorage.cpp)
target_include_directories(core PUBLIC src/core)

# Version consola
add_executable(singleton_console src/console/main_console.cpp)
target_link_libraries(singleton_console PRIVATE core)

# Version grafica con Qt
find_package(Qt6 QUIET COMPONENTS Widgets)
if(NOT Qt6_FOUND)
    find_package(Qt5 QUIET COMPONENTS Widgets)
endif()

if(Qt6_FOUND OR Qt5_FOUND)
    set(CMAKE_AUTOMOC ON)
    add_executable(singleton_qt
        src/qt/main_qt.cpp
        src/qt/MainWindow.cpp
        src/qt/ConfigViewerWindow.cpp)
    if(Qt6_FOUND)
        target_link_libraries(singleton_qt PRIVATE core Qt6::Widgets)
    else()
        target_link_libraries(singleton_qt PRIVATE core Qt5::Widgets)
    endif()
else()
    message(STATUS "Qt no encontrado: se compila solo la version consola")
endif()

# Pruebas del Singleton
if(EXISTS ${CMAKE_SOURCE_DIR}/tests/test_singleton.cpp)
    add_executable(test_singleton tests/test_singleton.cpp)
    target_link_libraries(test_singleton PRIVATE core)
    add_test(NAME singleton COMMAND test_singleton)
endif()