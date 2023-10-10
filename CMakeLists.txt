cmake_minimum_required(VERSION 3.14)

project(SEU-DIP-Labwork VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

aux_source_directory(src SOURCES)

if(MSVC)
  add_compile_options(/Zc:__cplusplus)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 COMPONENTS Core Quick REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_add_big_resources(SOURCES res.qrc)

add_executable(SEU-DIP-Labwork
        ${SOURCES}
        qml.qrc
        src/Core.hpp
        src/FourierTrans.hpp
        src/ImgProvider.hpp
        src/App.hpp
        src/Histogram.hpp
)

target_link_libraries(${PROJECT_NAME} Qt6::Core Qt6::Quick Qt6::Widgets ${OpenCV_LIBS})