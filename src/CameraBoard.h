/*
Copyright (c) 2013, Broadcom Europe Ltd
Copyright (c) 2013, James Hughes
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the copyright holder nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef CAMERA_BOARD_H
#define CAMERA_BOARD_H

#include "CameraBoardTypes.h"
#include "mmal/mmal.h"
#include "mmal/mmal_connection.h"

#define MMAL_CAMERA_CAPTURE_PORT 2
#define STILLS_FRAME_RATE_NUM 3
#define STILLS_FRAME_RATE_DEN 1

class CameraBoard {
	private:
	MMAL_COMPONENT_T * camera;	 /// Pointer to the camera component
	MMAL_COMPONENT_T * encoder;	/// Pointer to the encoder component
	MMAL_CONNECTION_T * encoder_connection; // Connection from the camera to the encoder
	MMAL_POOL_T * encoder_pool;				  /// Pointer to the pool of buffers used by encoder output port
	MMAL_PORT_T * camera_still_port;
	MMAL_PORT_T * encoder_input_port;
	MMAL_PORT_T * encoder_output_port;
	unsigned int width;
	unsigned int height;
	unsigned int rotation; // 0 to 359
	unsigned int brightness; // 0 to 100
	int iso;
	int sharpness; // -100 to 100
	int contrast; // -100 to 100
	int saturation; // -100 to 100
	CAMERA_BOARD_ENCODING encoding;
	CAMERA_BOARD_EXPOSURE exposure;
	CAMERA_BOARD_AWB awb;
	CAMERA_BOARD_IMAGE_EFFECT imageEffect;
	CAMERA_BOARD_METERING metering;
	bool horizontalFlip;
	bool verticalFlip;
	imageTakenCallback userCallback;
	
	MMAL_FOURCC_T convertEncoding(CAMERA_BOARD_ENCODING encoding);
	MMAL_PARAM_EXPOSUREMETERINGMODE_T convertMetering(CAMERA_BOARD_METERING metering);
	MMAL_PARAM_EXPOSUREMODE_T convertExposure(CAMERA_BOARD_EXPOSURE exposure);
	MMAL_PARAM_AWBMODE_T convertAWB(CAMERA_BOARD_AWB awb);
	MMAL_PARAM_IMAGEFX_T convertImageEffect(CAMERA_BOARD_IMAGE_EFFECT imageEffect);
	void commitBrightness();
	void commitRotation();
	void commitISO();
	void commitSharpness();
	void commitContrast();
	void commitSaturation();
	void commitExposure();
	void commitAWB();
	void commitImageEffect();
	void commitMetering();
	void commitFlips();
	int createCamera();
	int createEncoder();
	void destroyCamera();
	void destroyEncoder();
	void setDefaults();
	MMAL_STATUS_T connectPorts(MMAL_PORT_T *output_port, MMAL_PORT_T *input_port, MMAL_CONNECTION_T **connection);
	
	public:
	const char * API_NAME;
	CameraBoard() {
		API_NAME = "CameraBoard";
		setDefaults();
	}
	int initialize();
	int startCapture(unsigned char * preallocated_data, unsigned int offset, unsigned int length);
	void stopCapture();
	void bufferCallback(MMAL_PORT_T *port, MMAL_BUFFER_HEADER_T *buffer);
	void commitParameters();
	void setWidth(unsigned int width);
	void setHeight(unsigned int height);
	void setCaptureSize(unsigned int width, unsigned int height);
	void setBrightness(unsigned int brightness);
	void setRotation(int rotation);
	void setISO(int iso);
	void setSharpness(int sharpness);
	void setContrast(int contrast);
	void setSaturation(int saturation);
	void setEncoding(CAMERA_BOARD_ENCODING encoding);
	void setExposure(CAMERA_BOARD_EXPOSURE exposure);
	void setAWB(CAMERA_BOARD_AWB awb);
	void setImageEffect(CAMERA_BOARD_IMAGE_EFFECT imageEffect);
	void setMetering(CAMERA_BOARD_METERING metering);
	void setHorizontalFlip(bool hFlip);
	void setVerticalFlip(bool vFlip);
	void setImageCallback(imageTakenCallback callback);
	
	unsigned int getWidth();
	unsigned int getHeight();
	unsigned int getBrightness();
	unsigned int getRotation();
	int getISO();
	int getSharpness();
	int getContrast();
	int getSaturation();
	CAMERA_BOARD_EXPOSURE getExposure();
	CAMERA_BOARD_AWB getAWB();
	CAMERA_BOARD_IMAGE_EFFECT getImageEffect();
	CAMERA_BOARD_METERING getMetering();
	bool isHorizontallyFlipped();
	bool isVerticallyFlipped();
	
};

#endif // CAMERA_BOARD_H
