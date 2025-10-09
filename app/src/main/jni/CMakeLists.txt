# Sets the minimum CMake version required for this project.
cmake_minimum_required(VERSION 3.22.1)

# Declares the project name.
project("EdgeDetectionViewer")

# --- START of OpenCV Configuration ---
set(OpenCV_DIR D:/OpenCV-android-sdk/sdk/native/jni)
find_package(OpenCV REQUIRED)
# --- END of OpenCV Configuration ---

# --- Find native graphics libraries ---
find_library(GLESv2-lib GLESv2) # Find the GLESv2 library
find_library(EGL-lib EGL)       # Find the EGL library

# Creates and names a library from our C++ source files.
add_library(${CMAKE_PROJECT_NAME} SHARED
        native-lib.cpp)

# Specifies all the libraries to link against.
target_link_libraries(${CMAKE_PROJECT_NAME}
        # Link OpenCV
        ${OpenCV_LIBS}

        # Link the graphics libraries
        ${GLESv2-lib}
        ${EGL-lib}

        # Link standard Android libraries
        android
        log)