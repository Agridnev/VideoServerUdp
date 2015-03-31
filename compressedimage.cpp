#include "compressedimage.h"
#include <stdlib.h>
#include <string.h>

CompressedImage::CompressedImage() : data(0), size(0) {}

CompressedImage::CompressedImage(void *data, int size) : data(0), size(0)
{
	if (data != 0 && size > 0)
	{
		this->data = malloc(size);
		memcpy(this->data, data, size);
		this->size = size;
	}
}

CompressedImage::CompressedImage(const CompressedImage &other) : data(0), size(0)
{
	if (other.data != 0 && other.size > 0)
	{
		data = malloc(other.size);
		memcpy(data, other.data, other.size);
		size = other.size;
	}
}

CompressedImage::~CompressedImage()
{
	if (data)
	{
		free(data);
	}
}

CompressedImage &CompressedImage::operator=(const CompressedImage &other)
{
	if (this != &other)
	{
		if (data)
		{
			free(data);
		}
		if (other.data)
		{
			data = malloc(other.size);
			memcpy(data, other.data, other.size);
		}
		size = other.size;
	}
	return *this;
}

void *CompressedImage::getData()
{
	return data;
}

int CompressedImage::getSize()
{
	return size;
}

