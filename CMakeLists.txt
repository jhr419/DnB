cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME DnB)

# Include toolchain file
include("cmake/gcc-arm-none-eabi.cmake")

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
#        ../DnB/UserLibs/Bsp/Src/inv_mpu.c
#        ../DnB/UserLibs/Bsp/Src/inv_mpu.c
#        ../DnB/UserLibs/Bsp/Src/inv_mpu_dmp_motion_driver.c
#        ../DnB/UserLibs/Bsp/Src/MPU6500.c
        ../DnB/UserLibs/Controller/Src/pid.c
        ../DnB/UserLibs/Devices/Src/car.c
        ../DnB/UserLibs/Devices/Src/encoder.c
#        ../DnB/UserLibs/Devices/Src/imu.c
        ../DnB/UserLibs/Devices/Src/motor.c
        ../DnB/UserLibs/Support/Src/communication.c
#        ../DnB/UserLibs/Support/Src/delay.c
#        ../DnB/UserLibs/Tasks/Src/carTask.c
#        ../DnB/UserLibs/Tasks/Src/multiTask.c
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
        ../DnB/UserLibs/Algorithm/Inc
        ../DnB/UserLibs/Bsp/Inc
        ../DnB/UserLibs/Controller/Inc
        ../DnB/UserLibs/Devices/Inc
        ../DnB/UserLibs/Support/Inc
        ../DnB/UserLibs/Tasks/Inc
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx

    # Add user defined libraries
)
