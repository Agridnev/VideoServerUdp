#ifndef IMAGE_H
#define IMAGE_H

class Image
{
private:
	void *data;
	int width;
	int height;
	int channels;

public:
	Image();
	Image(void *data, int width, int height, int channels);
	Image(const Image &other);
	~Image();
	Image &operator=(const Image &other);
	void *getData();
	int getWidth();
	int getHeight();
	int getChannels();
};

#endif // IMAGE_H
