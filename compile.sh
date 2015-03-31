#!/bin/bash
g++ main.cpp server.cpp image.cpp compressedimage.cpp camera.cpp webcamera.cpp imagecompressor.cpp imagecompressorjpeglib.cpp -lopencv_core -lopencv_imgproc -lopencv_highgui -ljpeg -o server
