#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_edgedetectionviewer_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_edgedetectionviewer_gl_MyGLRenderer_onSurfaceCreated(JNIEnv *env, jobject thiz) {
    // TODO: implement onSurfaceCreated()
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_edgedetectionviewer_gl_MyGLRenderer_onSurfaceChanged(JNIEnv *env, jobject thiz,
                                                                      jint width, jint height) {
    // TODO: implement onSurfaceChanged()
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_edgedetectionviewer_gl_MyGLRenderer_onDrawFrame(JNIEnv *env, jobject thiz) {
    // TODO: implement onDrawFrame()
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_edgedetectionviewer_MainActivity_processFrame(JNIEnv *env, jobject thiz,
                                                               jbyteArray frame_data, jint width,
                                                               jint height) {
    // TODO: implement processFrame()
}