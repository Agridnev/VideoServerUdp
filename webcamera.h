#ifndef WEBCAMERA_H
#define WEBCAMERA_H
#include "camera.h"
#include <opencv2/opencv.hpp>

class WebCamera : public Camera
{
private:
	int devices[2];
	cv::VideoCapture captures[2];
	Image frame;

public:
	WebCamera();
	~WebCamera();
	bool isReady();
	int setup();
	int capture();
	Image getFrame();
	void setDevice(int device0, int device1);
	void setSize(int width, int height);
};

#endif // WEBCAMERA_H

