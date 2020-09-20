cmake_minimum_required(VERSION 3.17)

project(FinallyEngine CXX)

set(CMAKE_CXX_STANDARD 20)

set(BUILD_SHARED_LIBS TRUE)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(SOURCE_PATH Engine/Source/)

function(add_module MODULE_NAME)
    add_subdirectory(${SOURCE_PATH}${MODULE_NAME})
endfunction()

if (MSVC)
    add_compile_options(/W3 /WX)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
else()
    add_compile_options(-W -Wall -Werror)
endif()

add_module(Main)
add_module(Core)
add_module(Renderer)
add_module(Utilities)
add_module(Math)
add_module(Logging)

add_module(ThirdParty)
