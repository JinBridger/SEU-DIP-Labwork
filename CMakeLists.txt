cmake_minimum_required(VERSION 3.14)

project(SEU-DIP-Labwork VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include_directories(include)
aux_source_directory(src SOURCES)

if (MINGW)
  add_compile_options(-target x86_64-w64-mingw32)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 COMPONENTS Core Quick REQUIRED)

add_executable(SEU-DIP-Labwork
    ${SOURCES}
    qml.qrc
)

target_link_libraries(SEU-DIP-Labwork Qt6::Core Qt6::Quick)
