#include "robotcamera.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DMA_BUFFER_SIZE 4

RobotCamera::RobotCamera() : ready(false), framesRemain(0)
{
}

RobotCamera::~RobotCamera()
{
	if (ready)
	{
		dc1394_video_set_transmission(camera, DC1394_OFF);
		dc1394_capture_stop(camera);
		dc1394_camera_free(camera);
		dc1394_free (d);
	}
}

bool RobotCamera::isReady()
{
	return ready;
}

int RobotCamera::setup()
{
	if (ready)
		return 1;
	dc1394camera_list_t *list;
	dc1394error_t err;
	d = dc1394_new ();
	if (!d)
		return 1;
	err = dc1394_camera_enumerate (d, &list);
	if (list->num == 0) {
		return 1;
	}
	camera = dc1394_camera_new (d, list->ids[0].guid);
	if (!camera) {
		return 1;
	}
	dc1394_camera_free_list (list);
	dc1394_video_set_iso_speed(camera, DC1394_ISO_SPEED_400);
	dc1394_video_set_mode(camera, DC1394_VIDEO_MODE_FORMAT7_3);
	dc1394_video_set_framerate(camera, DC1394_FRAMERATE_7_5);
	dc1394_capture_setup(camera, DMA_BUFFER_SIZE, DC1394_CAPTURE_FLAGS_DEFAULT);
	ready = true;
	return 0;
}

int RobotCamera::capture()
{
	if (!ready)
		return 1;
	if (framesRemain == 0)
	{
		dc1394_video_set_transmission(camera, DC1394_OFF);
		dc1394_capture_stop(camera);
		dc1394_capture_setup(camera, DMA_BUFFER_SIZE, DC1394_CAPTURE_FLAGS_DEFAULT);
		dc1394_video_set_transmission(camera, DC1394_ON);
		framesRemain = DMA_BUFFER_SIZE;
	}
	--framesRemain;
	dc1394video_frame_t *frame=NULL;
	dc1394_capture_dequeue(camera, DC1394_CAPTURE_POLICY_WAIT, &frame);
	unsigned int width = frame->size[0];
	unsigned int heigth = frame->size[1];
	dc1394video_frame_t *new_frame = new dc1394video_frame_t;
	bzero(new_frame, sizeof(dc1394video_frame_t));
	new_frame->image = NULL;
	new_frame->color_coding = frame->color_coding;
	dc1394_deinterlace_stereo_frames(frame, new_frame, DC1394_STEREO_METHOD_INTERLACED);
	uint64_t numPixels = width * heigth * 6;
	unsigned char *rgb = new unsigned char[numPixels];
	dc1394_bayer_decoding_8bit(new_frame->image, rgb, width, 2 * heigth, DC1394_COLOR_FILTER_GRBG, DC1394_BAYER_METHOD_HQLINEAR);
	dc1394_capture_enqueue (camera, frame);
	frameImage = Image(rgb, width, 2 * heigth, 3);
	free(rgb);
	free(new_frame->image);
	free(new_frame);
	return 0;
}

Image RobotCamera::getFrame()
{
	return frameImage;
}

