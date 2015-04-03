#include "server.h"
#include "robotcamera.h"
#include "imagecompressorjpeglib.h"
#include "stdlib.h"

int main(int argc, char *argv[])
{
	int port = 1337;
	if (argc > 1)
		port = atoi(argv[1]);
	RobotCamera robotCamera;
	robotCamera.setup();
	ImageCompressorJpegLib imageCompressorJpegLib;
	Server server(&robotCamera, &imageCompressorJpegLib, port);
	server.run();
	return 0;
}
