#include "image.h"
#include <stdlib.h>
#include <string.h>

Image::Image() : data(0), width(0), height(0), channels(0) {}

Image::Image(void *data, int width, int height, int channels) : data(0), width(0), height(0), channels(0)
{
	if (data != 0 && width > 0 && height > 0 && channels > 0)
	{
		this->data = malloc(width * height * channels);
		memcpy(this->data, data, width * height * channels);
		this->width = width;
		this->height = height;
		this->channels = channels;
	}
}

Image::Image(const Image &other) : data(0), width(0), height(0), channels(0)
{
	if (other.data != 0 && other.height > 0 && other.width > 0 && other.channels > 0)
	{
		data = malloc(other.width * other.height * other.channels);
		memcpy(data, other.data, other.width * other.height * other.channels);
		width = other.width;
		height = other.height;
		channels = other.channels;
	}
}

Image::~Image()
{
	if (data)
	{
		free(data);
	}
}

Image &Image::operator=(const Image &other)
{
	if (this != &other)
	{
		if (data)
		{
			free(data);
		}
		if (other.data)
		{
			data = malloc(other.width * other.height * other.channels);
			memcpy(data, other.data, other.width * other.height * other.channels);
		}
		width = other.width;
		height = other.height;
		channels = other.channels;
	}
	return *this;
}

void *Image::getData()
{
	return data;
}

int Image::getWidth()
{
	return width;
}

int Image::getHeight()
{
	return height;
}

int Image::getChannels()
{
	return channels;
}

