#ifndef CAMERA_H
#define CAMERA_H
#include "image.h"

class Camera
{
public:
	virtual ~Camera();
	virtual bool isReady() = 0;
	virtual int setup() = 0;
	virtual int capture() = 0;
	virtual Image getFrame() = 0;
};

#endif // CAMERA_H
