#include "server.h"
#include "webcamera.h"
#include "imagecompressorjpeglib.h"
#include "stdlib.h"

int main(int argc, char *argv[])
{
	int port = 1337;
	int cameras[2] = {1, 2};
	if (argc > 1)
		port = atoi(argv[1]);
	if (argc > 3)
	{
		cameras[0] = atoi(argv[2]);
		cameras[1] = atoi(argv[3]);
	}
	WebCamera webCamera;
	webCamera.setDevice(cameras[0], cameras[1]);
	webCamera.setup();
	ImageCompressorJpegLib imageCompressorJpegLib;
	Server server(&webCamera, &imageCompressorJpegLib, port);
	server.run();
	return 0;
}
