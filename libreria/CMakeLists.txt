## >>>>>>>>>>>>>>>
## >>>>>>>>>>>>>>>
add_library(libreria MiLibreria.cpp "lu.cpp")
## <<<<<<<<<<<<<<<
## <<<<<<<<<<<<<<<

target_include_directories(libreria PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
