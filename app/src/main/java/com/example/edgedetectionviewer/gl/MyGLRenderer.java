package com.example.edgedetectionviewer.gl;

import android.opengl.GLSurfaceView;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class MyGLRenderer implements GLSurfaceView.Renderer {

    // Native methods that are implemented in our C++ library ('native-lib.cpp')
    // These are the bridges to our native OpenGL rendering code.
    public native void onSurfaceCreated();
    public native void onSurfaceChanged(int width, int height);
    public native void onDrawFrame();

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        // This method is called once when the surface is created.
        // We pass the call directly to our C++ code.
        onSurfaceCreated();
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        // This method is called when the surface changes size (e.g., phone rotation).
        // We pass the new dimensions to our C++ code.
        onSurfaceChanged(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        // This method is called for every frame that needs to be drawn.
        // We pass the call directly to our C++ code to perform the rendering.
        onDrawFrame();
    }
}
