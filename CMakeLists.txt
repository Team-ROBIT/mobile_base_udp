cmake_minimum_required(VERSION 3.0.2)
project(operator_udp)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  cv_bridge
  image_transport
  mobile_base_msgs
  robit_udp
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  include/operator_udp
)

catkin_package()

find_package(Qt5 COMPONENTS Widgets Gui Network REQUIRED)

file(GLOB_RECURSE QT_MOC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS include/operator_udp/*.h )

QT5_WRAP_CPP(QT_MOC_HPP ${QT_MOC})

link_directories(${OpenCV_LIB_DIR})

file(GLOB_RECURSE QT_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS src/*.cpp)


add_executable(operator_udp ${QT_SOURCES}  ${QT_MOC_HPP})
target_link_libraries(operator_udp Qt5::Widgets Qt5::Gui Qt5::Network ${QT_LIBRARIES} ${catkin_LIBRARIES})

