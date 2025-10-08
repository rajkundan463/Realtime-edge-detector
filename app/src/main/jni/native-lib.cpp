#include <jni.h>
#include <string>

// Include OpenCV core and image processing headers
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

// Include OpenGL ES 2 headers
#include <GLES2/gl2.h>

// --- Global Variables ---
// Global Mat to hold the final processed frame that will be rendered.
cv::Mat processedMat;
// Global variable to hold the ID of our OpenGL texture.
GLuint textureId;


// JNI function for MainActivity.processFrame()
extern "C" JNIEXPORT void JNICALL
Java_com_example_edgedetectionviewer_MainActivity_processFrame(
        JNIEnv *env,
        jobject /* this */,
        jbyteArray frameData,
        jint width,
        jint height) {

    // 1. Access the raw camera data from the Java byte array.
    jbyte *yuv = env->GetByteArrayElements(frameData, 0);

    // 2. Create an OpenCV Mat from the raw YUV data (NV21 format).
    cv::Mat yuvMat(height + height / 2, width, CV_8UC1, yuv);
    cv::Mat rgbaMat(height, width, CV_8UC4);

    // 3. Convert the camera's YUV image to RGBA.
    cv::cvtColor(yuvMat, rgbaMat, cv::COLOR_YUV2RGBA_NV21);

    // 4. Convert the RGBA image to grayscale for Canny.
    cv::Mat grayMat;
    cv::cvtColor(rgbaMat, grayMat, cv::COLOR_RGBA2GRAY);

    // 5. Apply the Canny Edge Detection algorithm.
    // The result is stored in our global 'processedMat'.
    cv::Canny(grayMat, processedMat, 80, 100);

    // 6. Release the Java byte array to prevent memory leaks.
    env->ReleaseByteArrayElements(frameData, yuv, 0);
}


// JNI function for MyGLRenderer.onSurfaceCreated()
extern "C" JNIEXPORT void JNICALL
Java_com_example_edgedetectionviewer_gl_MyGLRenderer_onSurfaceCreated(
        JNIEnv *env,
        jobject /* this */) {

    // Set the background clear color to black.
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Generate one texture ID.
    glGenTextures(1, &textureId);

    // Bind the texture so subsequent commands affect it.
    glBindTexture(GL_TEXTURE_2D, textureId);

    // Set texture filtering parameters.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}


// JNI function for MyGLRenderer.onSurfaceChanged()
extern "C" JNIEXPORT void JNICALL
Java_com_example_edgedetectionviewer_gl_MyGLRenderer_onSurfaceChanged(
        JNIEnv *env,
        jobject /* this */,
        jint width,
        jint height) {
    // Set the OpenGL viewport to the full size of the surface.
    glViewport(0, 0, width, height);
}


// JNI function for MyGLRenderer.onDrawFrame()
extern "C" JNIEXPORT void JNICALL
Java_com_example_edgedetectionviewer_gl_MyGLRenderer_onDrawFrame(
        JNIEnv *env,
        jobject /* this */) {
    // Clear the screen's color buffer.
    glClear(GL_COLOR_BUFFER_BIT);

    // Only proceed if the processedMat from OpenCV is not empty.
    if (!processedMat.empty()) {
        // Bind our texture.
        glBindTexture(GL_TEXTURE_2D, textureId);

        // Upload the pixel data from the OpenCV Mat to the bound OpenGL texture.
        // The Canny output is a single-channel (grayscale) image, so we use GL_LUMINANCE.
        glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, processedMat.cols, processedMat.rows, 0,
                     GL_LUMINANCE, GL_UNSIGNED_BYTE, processedMat.data);

        // TODO: Draw a textured quad to the screen.
        // This final part requires shaders (GLSL) and vertex data to display the texture.
    }
}