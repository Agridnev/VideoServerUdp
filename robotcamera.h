#ifndef ROBOTCAMERA_H
#define ROBOTCAMERA_H
#include "camera.h"
#include <dc1394/dc1394.h>

class RobotCamera : public Camera
{
private:
	dc1394_t *d;
	dc1394camera_t *camera;
	Image frameImage;
	bool ready;
	int framesRemain;

public:
	RobotCamera();
	~RobotCamera();
	bool isReady();
	int setup();
	int capture();
	Image getFrame();
};

#endif // ROBOTCAMERA_H

