cmake_minimum_required(VERSION 3.0.0)
project(SolisShooter VERSION 0.1.0)

include(CTest)
include(Source/CMakeSources.cmake)

enable_testing()
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(OpenGL_GL_PREFERENCE "GLVND")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(assimp REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)
find_package(Bullet REQUIRED)
find_package(PNG REQUIRED)

include_directories("Source")
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${BULLET_INCLUDE_DIR})

add_executable(SolisShooter ${SOLIS_SOURCE})

#set_target_properties(${PROJECT_NAME} PROPERTIES
#LINK_FLAGS /SUBSYSTEM:WINDOWS
#)

target_link_libraries(${PROJECT_NAME} SDL2)
target_link_libraries(${PROJECT_NAME} SDL2_image)
target_link_libraries(${PROJECT_NAME} assimp)
target_link_libraries(${PROJECT_NAME} OpenGL)
target_link_libraries(${PROJECT_NAME} GLEW)
target_link_libraries(${PROJECT_NAME} BulletDynamics)
target_link_libraries(${PROJECT_NAME} BulletCollision)
target_link_libraries(${PROJECT_NAME} LinearMath)
target_link_libraries(${PROJECT_NAME} png)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

file(COPY Resources DESTINATION ${CMAKE_BINARY_DIR})
