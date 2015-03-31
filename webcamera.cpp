#include "webcamera.h"

WebCamera::WebCamera()
{
	devices[0] = 0;
	devices[1] = 1;
}

WebCamera::~WebCamera()
{
	for (int i = 0 ; i < 2 ; ++i)
		captures[i].release();
}

bool WebCamera::isReady()
{
	return captures[0].isOpened() && captures[1].isOpened();
}

int WebCamera::setup()
{
	int res = 0;
	for (int i = 0 ; i < 2 ; ++i)
	{
		res += (i + 1) * captures[i].open(devices[i]);
	}
	return res;
}

int WebCamera::capture()
{
	if (!isReady())
		return 1;
	cv::Mat framesBGR[2];
	cv::Mat framesRGB[2];
	for (int i = 0 ; i < 2 ; ++i)
	{
		captures[i] >> framesBGR[i];
		cvtColor(framesBGR[i], framesRGB[i], CV_BGR2RGB);
	}
	if (framesRGB[0].cols != framesRGB[1].cols || framesRGB[0].rows != framesRGB[1].rows)
		return 2;
	int width = framesRGB[0].cols;
	int height = framesRGB[0].rows;
	int channels = framesRGB[0].channels();
	int size = width * height * channels;
	void *data = malloc(2 * size);
	memcpy(data, framesRGB[0].data, size);
	memcpy((char*) data + size, framesRGB[1].data, size);
	frame = Image(data, width, 2 * height, channels);
	free(data);
	return 0;
}

Image WebCamera::getFrame()
{
	return frame;
}

void WebCamera::setDevice(int device0, int device1)
{
	devices[0] = device0;
	devices[1] = device1;
}

void WebCamera::setSize(int width, int height)
{
	for (int i = 0 ; i < 2 ; ++i)
	{
		captures[i].set(CV_CAP_PROP_FRAME_WIDTH, width);
		captures[i].set(CV_CAP_PROP_FRAME_HEIGHT, height);
	}
}
