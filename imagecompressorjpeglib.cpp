#include "imagecompressorjpeglib.h"
#include "stdlib.h"
#include "stdio.h"
#include "jpeglib.h"

ImageCompressorJpegLib::~ImageCompressorJpegLib()
{

}

CompressedImage ImageCompressorJpegLib::compress(Image image)
{
	if (image.getData() == 0)
		return CompressedImage();
	unsigned char *buffer = 0;
	long unsigned int bufferSize = 0;
	unsigned char *outdata = (unsigned char *) image.getData();
	struct jpeg_compress_struct cinfo = {0};
	struct jpeg_error_mgr jerr;
	JSAMPROW row_ptr[1];
	int row_stride;
	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_compress(&cinfo);
	jpeg_mem_dest(&cinfo, &buffer, &bufferSize);
	cinfo.image_width = image.getWidth();
	cinfo.image_height = image.getHeight();
	cinfo.input_components = image.getChannels();
	cinfo.in_color_space = JCS_RGB;
	jpeg_set_defaults(&cinfo);
	jpeg_start_compress(&cinfo, TRUE);
	row_stride = image.getWidth()* image.getChannels();
	while (cinfo.next_scanline < cinfo.image_height)
	{
		row_ptr[0] = &outdata[cinfo.next_scanline * row_stride];
		jpeg_write_scanlines(&cinfo, row_ptr, 1);
	}
	jpeg_finish_compress(&cinfo);
	jpeg_destroy_compress(&cinfo);
	CompressedImage compressedImage(buffer, bufferSize);
	free(buffer);
	return compressedImage;
}
