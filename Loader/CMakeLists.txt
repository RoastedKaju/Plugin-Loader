project(Loader)

set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Source/main.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Source/loader.cpp)
set(HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/Include/loader.hpp)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Include)
