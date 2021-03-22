# CMakeList.txt : CMake project for BallTrack, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("BallTrack")

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS} )
include_directories( ${GLUT_INCLUDE_DIRS} )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Add source to this project's executable.
add_executable (BallTrack "Src/BallTrack.cpp" "Src/BallTrack.h")

target_link_libraries(BallTrack ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

target_include_directories(BallTrack
  PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
    ${OPENGL_INCLUDE_DIRS}
    ${GLUT_INCLUDE_DIRS}
)

# TODO: Add tests and install targets if needed.
