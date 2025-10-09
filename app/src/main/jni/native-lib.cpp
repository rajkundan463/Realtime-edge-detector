#include <jni.h>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <GLES2/gl2.h>


cv::Mat processedMat;
GLuint textureId;

extern "C" JNIEXPORT void JNICALL
Java_com_example_edgedetectionviewer_MainActivity_processFrame(
        JNIEnv *env,
        jobject /* this */,
        jbyteArray frameData,
        jint width,
        jint height) {


    jbyte *yuv = env->GetByteArrayElements(frameData, 0);

    cv::Mat yuvMat(height + height / 2, width, CV_8UC1, yuv);
    cv::Mat rgbaMat(height, width, CV_8UC4);


    cv::cvtColor(yuvMat, rgbaMat, cv::COLOR_YUV2RGBA_NV21);

    cv::Mat grayMat;
    cv::cvtColor(rgbaMat, grayMat, cv::COLOR_RGBA2GRAY);

    cv::Canny(grayMat, processedMat, 80, 100);


    env->ReleaseByteArrayElements(frameData, yuv, 0);
}


extern "C" JNIEXPORT void JNICALL
Java_com_example_edgedetectionviewer_gl_MyGLRenderer_onSurfaceCreated(
        JNIEnv *env,
        jobject /* this */) {

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);


    glGenTextures(1, &textureId);

    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_edgedetectionviewer_gl_MyGLRenderer_onSurfaceChanged(
        JNIEnv *env,
        jobject /* this */,
        jint width,
        jint height) {

    glViewport(0, 0, width, height);
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_edgedetectionviewer_gl_MyGLRenderer_onDrawFrame(
        JNIEnv *env,
        jobject /* this */) {

    glClear(GL_COLOR_BUFFER_BIT);

    if (!processedMat.empty()) {
        // Bind our texture.
        glBindTexture(GL_TEXTURE_2D, textureId);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, processedMat.cols, processedMat.rows, 0,
                     GL_LUMINANCE, GL_UNSIGNED_BYTE, processedMat.data);

        // TODO: Draw a textured quad to the screen.
    }
}