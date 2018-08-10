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
sudo apt-get install libvtk5-dev

# Configure and compile your opencv with "viz" module
- [OpenCV install instruction (Linux)](https://docs.opencv.org/2.4/doc/tutorials/introduction/linux_install/linux_install.html#linux-installation)

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
