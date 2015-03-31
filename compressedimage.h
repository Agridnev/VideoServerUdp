#ifndef COMPRESSEDIMAGE_H
#define COMPRESSEDIMAGE_H

class CompressedImage
{
private:
	void *data;
	int size;

public:
	CompressedImage();
	CompressedImage(void *data, int size);
	CompressedImage(const CompressedImage &other);
	~CompressedImage();
	CompressedImage &operator=(const CompressedImage &other);
	void *getData();
	int getSize();
};

#endif // COMPRESSEDIMAGE_H
