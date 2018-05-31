cmake_minimum_required(VERSION 3.8)
project(libui_win C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp inc/*.h)

include_directories(../libui/inc)
include_directories(inc src)

add_executable(gui_win ${SOURCE_FILES})
set_target_properties(gui_win PROPERTIES LINK_FLAGS ${PROJECT_SOURCE_DIR}/manifest.res )
target_link_libraries(gui_win ${PROJECT_SOURCE_DIR}/lib/libui.a)

add_library(ui_win STATIC ${SOURCE_FILES})
set_target_properties(ui_win PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(ui_win ${PROJECT_SOURCE_DIR}/lib/libui.a)

target_include_directories(ui_win PRIVATE inc)
target_include_directories(ui_win PRIVATE src)
