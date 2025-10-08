package com.example.edgedetectionviewer;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;

import android.Manifest;
import android.content.pm.PackageManager;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.widget.Toast;

import com.example.edgedetectionviewer.gl.MyGLRenderer;

public class MainActivity extends AppCompatActivity {

    private static final int CAMERA_PERMISSION_REQUEST_CODE = 200;
    private GLSurfaceView gLView;

    static {
        System.loadLibrary("nativedemo");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // Check if we already have camera permission
        if (ContextCompat.checkSelfPermission(this, Manifest.permission.CAMERA)
                != PackageManager.PERMISSION_GRANTED) {
            // If not, request it from the user
            ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.CAMERA},
                    CAMERA_PERMISSION_REQUEST_CODE);
        } else {
            // If permission is already granted, initialize the view
            initView();
        }
    }

    private void initView() {
        gLView = new GLSurfaceView(this);
        // Tell the view we want to use OpenGL ES 2.0
        gLView.setEGLContextClientVersion(2);
        // Connect our renderer class to the view
        gLView.setRenderer(new MyGLRenderer());
        // Set our GLSurfaceView as the main content of the activity
        setContentView(gLView);
    }

    // This method is called after the user responds to the permission request popup
    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        if (requestCode == CAMERA_PERMISSION_REQUEST_CODE && grantResults.length > 0 &&
                grantResults[0] == PackageManager.PERMISSION_GRANTED) {
            // If permission was granted, initialize the view
            initView();
        } else {
            // If permission was denied, show a message
            Toast.makeText(this, "Camera Permission Denied", Toast.LENGTH_LONG).show();
        }
    }

    // Native JNI declaration for sending camera data to C++.
    // We will use this later when the camera is running.
    public native void processFrame(byte[] frameData, int width, int height);
}