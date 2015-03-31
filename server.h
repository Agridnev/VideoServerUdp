#ifndef SERVER_H
#define SERVER_H
#include "camera.h"
#include "imagecompressor.h"

class Server
{
private:
	Camera *camera;
	ImageCompressor *imageCompressor;
	int port;

public:
	Server(Camera *camera, ImageCompressor *imageCompressor, int port = 1337);
	~Server();
	void run();
};

#endif // SERVER_H
