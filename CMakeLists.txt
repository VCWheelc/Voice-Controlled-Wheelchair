cmake_minimum_required(VERSION 3.5)
project(MotionChair)

set(CMAKE_CXX_STANDARD 14)

# Find the BCM2835 library
find_library(BCM2835_LIBRARY bcm2835 /usr/local/lib)

# Include the directories for the BCM2835 library headers
include_directories(/usr/local/include)

# The main program
add_executable(MotionChair MotionChair.cpp)

# Link the BCM2835 library to the executable
target_link_libraries(MotionChair ${BCM2835_LIBRARY})
