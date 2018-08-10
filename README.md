[![Build Status](https://travis-ci.org/MikhailPedus/AutostereogramSolver.svg?branch=master)](https://travis-ci.org/MikhailPedus/AutostereogramSolver)

## Auto Stereogram Solver

Attempts to solve [autostereograms](http://en.wikipedia.org/wiki/Autostereogram) programmatically.

![Screenshot](https://raw.githubusercontent.com/MikhailPedus/AutostereogramSolver/master/MainPicture.jpg)

## How it works

The algorithm for finding a solution is relatively straightforward.

The first step involves finding the offset at which the autostereogram repeats. This is accomplished by calculating the total pixel difference between the image and an overlap of itself at various offsets over a reasonable subsection of the image. The minimal diff is chosen as the offset.

The second step applies the offset to the image and calculates the absolute diff for the remainder of the image. Borders are added to compensate for the loss of an offset's worth of pixels.

Although simple, this algorithm seems to work relatively well and is efficient to execute, although there is a small chance that it won't determine the correct offset for the autostereogram.

## Install

```
# Required dependencies.
sudo apt-get install build-essential
sudo apt-get install cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
sudo apt-get install libvtk5-dev

# Configure and compile opencv with "viz" module.
git clone https://github.com/opencv/opencv.git -b 2.4 opencv
cd opencv
mkdir release
cd release
cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D WITH_VTK=ON -D BUILD_opencv_flann=OFF -D BUILD_opencv_features2d=OFF -D BUILD_opencv_calib3d=OFF -D BUILD_opencv_ml=OFF -D BUILD_opencv_video=OFF -D BUILD_opencv_legacy=OFF -D BUILD_opencv_objdetect=OFF -D BUILD_opencv_photo=OFF -D BUILD_opencv_gpu=OFF -D BUILD_opencv_ocl=OFF -D BUILD_opencv_nonfree=OFF -D BUILD_opencv_contrib=OFF -D BUILD_opencv_java=OFF -D BUILD_opencv_superres=OFF -D BUILD_opencv_ts=OFF -D BUILD_opencv_videostab=OFF .. && make
sudo make install

#Go to root directory.
cd ../../

# Create a build directory.
mkdir build
cd build

# Build and run.
cmake .. && make

# For building stereogram:
./stereogramBuilder -t ../texture/texture_1.jpg -d ../depthmap/shark.jpg

# For solving stereogram:
./stereogramSolver -s buildOutput.jpg

# For display result in 3d:
./pointsCloudDisplayer -c outSolverCloud.ply
```
