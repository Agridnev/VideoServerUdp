#ifndef IMAGECOMPRESSORJPEGLIB_H
#define IMAGECOMPRESSORJPEGLIB_H
#include "imagecompressor.h"

class ImageCompressorJpegLib : public ImageCompressor
{
public:
	~ImageCompressorJpegLib();
	CompressedImage compress(Image image);
};

#endif // IMAGECOMPRESSORJPEGLIB_H
