cmake_minimum_required(VERSION 3.31)
project(assimpts
    LANGUAGES CXX
)

set(ASSIMPTS_SOURCES
    src/main.cpp
)

add_executable(assimpts)
target_sources(assimpts PRIVATE ${ASSIMPTS_SOURCES})

set_target_properties(assimpts
    PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/dist"
)
