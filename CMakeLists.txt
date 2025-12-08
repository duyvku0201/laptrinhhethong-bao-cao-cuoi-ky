cmake_minimum_required(VERSION 3.10)
project(CPUScheduler C)

# Set C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Compiler flags
if(MSVC)
    # Windows with MSVC
    add_compile_options(/W4)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
else()
    # Unix-like systems (Linux, NetBSD, etc.)
    add_compile_options(-Wall -Wextra)
endif()

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Source files - Algorithms
set(ALGORITHM_SOURCES
    src/algorithms/fcfs.c
    src/algorithms/sjf.c
    src/algorithms/srtf.c
    src/algorithms/priority_np.c
    src/algorithms/priority_p.c
    src/algorithms/round_robin.c
)

# Source files - Core
set(CORE_SOURCES
    src/core/process.c
    src/core/queue.c
    src/core/metrics.c
)

# Source files - IO
set(IO_SOURCES
    src/io.c
    src/io/input.c
    src/io/output.c
    src/io/file_handler.c
)

# Source files - UI
set(UI_SOURCES
    src/ui/menu.c
    src/ui/display.c
    src/ui/gantt.c
    src/ui/comparison.c
)

# Source files - Utils
set(UTILS_SOURCES
    src/utils/colors.c
    src/utils/sort.c
    src/utils/validation.c
)

# Main source
set(MAIN_SOURCE
    src/main.c
)

# Combine all sources
set(ALL_SOURCES
    ${MAIN_SOURCE}
    ${ALGORITHM_SOURCES}
    ${CORE_SOURCES}
    ${IO_SOURCES}
    ${UI_SOURCES}
    ${UTILS_SOURCES}
)

# Create executable
add_executable(scheduler ${ALL_SOURCES})

# Platform-specific settings
if(WIN32)
    # Windows specific settings
    target_compile_definitions(scheduler PRIVATE _CRT_SECURE_NO_WARNINGS)
    set_target_properties(scheduler PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    )
elseif(UNIX)
    # Unix-like systems (Linux, NetBSD, etc.)
    if(${CMAKE_SYSTEM_NAME} MATCHES "NetBSD")
        # NetBSD specific settings if needed
        message(STATUS "Building for NetBSD")
    elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
        # Linux specific settings if needed
        message(STATUS "Building for Linux")
    endif()
endif()

# Installation
install(TARGETS scheduler DESTINATION bin)

# Print build information
message(STATUS "")
message(STATUS "===========================================")
message(STATUS "CPU Scheduling Algorithms Simulator")
message(STATUS "===========================================")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "System: ${CMAKE_SYSTEM_NAME}")
message(STATUS "===========================================")
message(STATUS "")
