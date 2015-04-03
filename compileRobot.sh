#!/bin/bash
g++ mainRobot.cpp server.cpp image.cpp compressedimage.cpp camera.cpp robotcamera.cpp imagecompressor.cpp imagecompressorjpeglib.cpp -ljpeg -ldc1394 -o serverRobot
