# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html.

# Sets the minimum CMake version required for this project.
cmake_minimum_required(VERSION 3.22.1)

# Declares the project name.
project("edgedetectionviewer")

# --- START of OpenCV Configuration ---

# 1. Set the path to your downloaded OpenCV SDK.
#    Note: Use forward slashes (/) even on Windows.
set(OpenCV_DIR D:/OpenCV-android-sdk/sdk/native/jni)

# 2. Find the OpenCV package using the path you just set.
find_package(OpenCV REQUIRED)

# --- END of OpenCV Configuration ---


# Creates and names a library, sets it as SHARED,
# and provides the relative paths to its source code.
add_library(${CMAKE_PROJECT_NAME} SHARED
        native-lib.cpp)

# Specifies libraries CMake should link to your target library.
target_link_libraries(${CMAKE_PROJECT_NAME}
        # 3. Add OpenCV to the list of libraries to link.
        ${OpenCV_LIBS}

        # Link other Android system libraries.
        android
        log)