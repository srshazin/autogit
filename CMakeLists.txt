# TODO: Add dependencies for
# argp , 

cmake_minimum_required(VERSION 3.10)
project(autogit)

# Set the build directory
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)

# Create the executable in the build directory
add_executable(${PROJECT_NAME} 
    src/main.c 
    src/utils.c
    src/args_parser.c
)

# Include the "include" directory to locate header files
target_include_directories(${PROJECT_NAME} PRIVATE includes)

# Linker flags
# target_link_libraries(${PROJECT_NAME} PRIVATE argp)

