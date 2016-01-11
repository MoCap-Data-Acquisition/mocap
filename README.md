# Open Source MoCap - Dynamics Trajectory Data Acquisition System 
A simple and  easy to use simple Motion Capturing system for Dynamics Engineering courses featuring:
  - Video Playback with Useful User Controls
  - Multiple Trajectory Tracking
  - Conversion from Pixels to any Distance Measurement
  - Visualizing Current Data with Graphs
  - Exporting Captured Data as a CSV file for Analysis (Including a Matlab
	script to automatically read and import the data).
  - Supports Windows, OSX, and Linux.
  - Everything should work fine, but if you have any issues please create a github account and [submit a bug report](https://github.com/MoCap-Data-Acquisition/mocap/issues) or a pull request

## Get it!
  - [Prebuilt binary for Windows or OSX](https://github.com/MoCap-Data-Acquisition/mocap/releases/latest)
  - Build It Yourself Instructions!

-------------------------------------------------------------------
## Build Instructions

### Building From Source
This is the *easiest* way to build this program from source. Your results may
vary depending on which operating system you use (Windows can be really
annoying to get everything working).
#### Required Dependencies
Please make sure that each dependency is installed or built, **Make note of
where everything is installed**.
   1. Your standard build tools
	  -   Windows:   MSVC or Mingw
	  - OSX/Linux:   gcc or Clang
   3. [VLC](http://www.videolan.org/vlc/index.html)
   2. [VLC-Qt](https://vlc-qt.tano.si/)
	  - Make sure you get the proper version.
   3. [Qt](http://www.qt.io/download/)
	  - Click the link for open source development.
	  - **For Windows Users** unless it's after February 9th, 2016 get the [QT 5.6 beta
		version](http://download.qt.io/development_releases/qt/5.6/5.6.0-beta/qt-opensource-windows-x86-msvc2015_64-5.6.0-beta.exe)
      - Download Visual Studio 2015 (even the free version should be fine)

#### Building
Once everything is setup you should be able to either compile from Qt Creator,
or run:
```
qmake
make
```
#### Fixing build problems
If there are any issues during the build process, check the **OS-Mocap.pro**
file and make sure that the dependencies are in the right locations, or change
the paths in the OS-Mocap.pro file. There may also be an issue where the
dynamic libraries (.dll, .dylib, or .so) aren't found during the build process,
which case the compiler will tell you where it's missing from so you might have
to copy it over.
