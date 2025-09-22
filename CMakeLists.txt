cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(PluginLoader)

add_subdirectory(Loader)

add_subdirectory(Plugin)