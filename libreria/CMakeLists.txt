## >>>>>>>>>>>>>>>
## >>>>>>>>>>>>>>>
add_library(libreria MiLibreria.cpp "MiLibreria.h")
## <<<<<<<<<<<<<<<
## <<<<<<<<<<<<<<<

target_include_directories(libreria PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
