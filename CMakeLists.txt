# CMakeList.txt : CMake project for BallTrack, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("BallTrack")

set(OpenGL_GL_PREFERENCE LEGACY)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS} )
include_directories( ${GLUT_INCLUDE_DIRS} )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

if(NOT MSVC)
  add_definitions(-Wall -Wextra -Werror -g -pedantic)
endif()

# Add source to this project's executable.
add_executable (BallTrack 
  Src/BallTrack.cpp
  Src/Drawables/Triangle.cpp
  Src/Drawables/Model3D.cpp
  Src/Math/CH3D.cpp
  Src/Math/Dir3D.cpp
  Src/Math/Pos3D.cpp
  Src/Math/Rt3D.cpp
  Src/Math/Sc3D.cpp
  Src/Math/TG3D.cpp
  Src/Math/Tr3D.cpp
  Src/Math/Vector2.cpp
  Src/Math/Vector3.cpp
  Src/Utils/ObjLoader.cpp
  Src/Physics/PhysicEntity.cpp
  Src/Entities/Entity.cpp
  Src/Entities/SphereEntity.cpp
)

target_link_libraries(BallTrack ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

target_include_directories(BallTrack
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Src
    ${CMAKE_CURRENT_BINARY_DIR}
    ${OPENGL_INCLUDE_DIRS}
    ${GLUT_INCLUDE_DIRS}
)

# TODO: Add tests and install targets if needed.
