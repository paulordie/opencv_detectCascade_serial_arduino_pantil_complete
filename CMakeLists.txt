cmake_minimum_required(VERSION 3.3)
project(clion1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fPIC")

set(OpenCV_FOUND 1)
find_package( OpenCV REQUIRED )

set(SOURCE_FILES main.cpp resource/CamSetting.cpp resource/CamSetting.h resource/SerialPort.cpp resource/SerialPort.h)

add_executable(clion1 ${SOURCE_FILES})

target_link_libraries(clion1 ${OpenCV_LIBS})

