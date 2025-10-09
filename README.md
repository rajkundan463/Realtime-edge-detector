#  Real-Time Edge Detection Viewer  
**Android + OpenCV (C++) + OpenGL ES + Web Viewer**  

##  Overview  
This project is a minimal Android application that:  
- Captures real-time camera frames using **Camera2 API / TextureView**.  
- Sends frames to **native C++ (NDK)** via **JNI** for image processing with **OpenCV**.  
- Displays processed frames using **OpenGL ES 2.0** in real-time.  
- Includes a **TypeScript web viewer** to display a sample processed frame and basic frame statistics.  

The focus is on **integration and rendering performance**, not advanced UI.  

---

##  Features  

###  Core  
-  Camera feed capture (Android).  
-  Frame processing with OpenCV (C++).  
-  OpenGL ES rendering at 10–15 FPS or higher.  
-  TypeScript-based web viewer for a sample processed frame + FPS/resolution overlay.  

###  Bonus (If Implemented)  
- Toggle between **raw feed** and **edge-detected output**.  
- FPS counter / frame processing logs.  
- Extra OpenGL shaders (grayscale, invert).  
- WebSocket/HTTP endpoint to push processed frames to web viewer.  

---
app → Android (Java/Kotlin) code: Camera + UI
/jni → C++ code (OpenCV processing, JNI bridge)
/gl → OpenGL ES renderer classes
/web → TypeScript web viewer (sample frame + stats)


---

## ⚙️ Setup Instructions  

### 1. Prerequisites  
- Android Studio (latest stable).  
- Android SDK + NDK installed.  
- OpenCV SDK for Android.  
- Node.js + TypeScript (for web viewer).  

### 2. Clone Repository  

git clone https://github.com/<your-username>/<your-repo>.git
-

###3. Android Setup

Import the project into Android Studio.

Configure NDK path in local.properties:

ndk.dir=/path/to/ndk


Add OpenCV SDK as a dependency (app/build.gradle).

Build & run the Android app on a real device.

4. Web Viewer Setup
cd web
npm install
tsc
open index.html

 Architecture

Android (Java/Kotlin) → Camera feed + UI.

JNI (C++ Bridge) → Transfers frames to native side.

OpenCV (C++) → Image processing (e.g., Canny edge detection).

OpenGL ES Renderer → Displays processed frames as textures.

Web (TypeScript) → Shows a static sample processed frame with overlay stats.

##  Project Structure  
/app → Android (Java/Kotlin) code: Camera + UI
/jni → C++ code (OpenCV processing, JNI bridge)
/gl → OpenGL ES renderer classes
/web → TypeScript web viewer (sample frame + stats)


---

