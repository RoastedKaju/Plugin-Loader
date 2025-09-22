project(Plugin)

set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Source/plugin.cpp)
set(HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/Include/plugin.hpp)

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})

include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Include)
