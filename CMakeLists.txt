cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain.cmake)
set(CMAKE_CXX_STANDARD 17)
set(PROJECT_NAME FPVGate)

set(${PROJECT_NAME}_BOARD d3)
project(${PROJECT_NAME})

### Additional static libraries to include in the target.
#set(${PROJECT_NAME}_LIBS)
### Main sketch file
set(${PROJECT_NAME}_SKETCH FpvGate.ino)

### Add project directories into the build
include_directories("${PROJECT_SOURCE_DIR}/brol/")
include_directories("${PROJECT_SOURCE_DIR}/includes/")

#add_subdirectory("brol")
#add_subdirectory("includes")

    #add_subdirectory("C:\\Users\\ grispin\\Documents\\Arduino\\libraries")
    #add_subdirectory("D:\\perso\\Tools\\arduino-1.8.19\\hardware")

### Additional settings to add non-standard or your own Arduino libraries.
# For this example (libs will contain additional arduino libraries)
# An Arduino library my_lib will contain files in libs/my_lib/: my_lib.h, my_lib.cpp + any other cpp files
#link_directories("C:/Users/grispin/Documents/Arduino/libraries")

# This is no longer need but left in for those occasions where automatics do not work out. 
# Current Arduino.cmake will recurse into any libraries which contain source files in src/ subdirectory. 
# Files in subdirectories whose name starts with cmake-build or examples are excluded
# For nested library sources replace ${LIB_NAME} with library name for each library
# set(_RECURSE true)

#### Additional settings for programmer. From programmers.txt

## Verbose build process

#generate_arduino_firmware(${PROJECT_NAME})


print_board_list()
print_programmer_list()
