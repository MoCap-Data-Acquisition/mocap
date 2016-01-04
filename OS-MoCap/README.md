# Open Source MoCap - Dynamics Trajectory Data Acquisition System 
A simple and  easy to use simple Motion Capturing system for Dynamics Engineering courses featuring:
  - Video Playback with Useful User Controls
  - Multiple Trajectory Tracking
  - Conversion from Pixels to any Distance Measurement
  - Visualizing Current Data with Graphs
  - Exporting Captured Data as a CSV file for Analysis (Including a Matlab
	script to automatically read and import the data).
  - Supports Windows, OSX, and Linux.

## Get it!
  - Windows Executable 
  - OSX Executable
  - Build It Yourself Instructions!

## [User Manual]()

-------------------------------------------------------------------
## Build Instructions

### Build system selection
If you want to use CMake, you can delete
  - simple-player.pro
  - src/src.pro

If you want to use qmake, you can delete
  - CMakeLists.txt
  - cmake/*
  - src/CMakeLists.txt


### Platform specific notes

#### Windows

You can install all required libraries with (CMake only)
```
make install
make windows
```

#### OS X

Create package using (CMake only)
```
make install
make dmg
```

#### Linux
