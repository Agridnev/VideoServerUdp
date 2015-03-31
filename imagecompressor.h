#ifndef IMAGECOMPRESSOR_H
#define IMAGECOMPRESSOR_H
#include "image.h"
#include "compressedimage.h"

class ImageCompressor
{
public:
	virtual ~ImageCompressor();
	virtual CompressedImage compress(Image image) = 0;
};

#endif // IMAGECOMPRESSOR_H
