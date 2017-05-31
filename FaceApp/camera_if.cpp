/* Copyright (c) 2017 Gnomons Vietnam Co., Ltd., Gnomons Co., Ltd.
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice,
* this list of conditions and the following disclaimer.
*
* 2. Redistributions in binary form must reproduce the above copyright notice,
* this list of conditions and the following disclaimer in the documentation
* and/or other materials provided with the distribution.
*
* 3. Neither the name of the copyright holder nor the names of its contributors
* may be used to endorse or promote products derived from this software without
* specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*/

#include "camera_if.hpp"
#include "JPEG_Converter.h"
#include "EasyAttach_CameraAndLCD.h"
#include "dcache-control.h"

using namespace cv;

static uint8_t FrameBuffer_Video[FRAME_BUFFER_STRIDE * FRAME_BUFFER_HEIGHT]__attribute((section("NC_BSS"),aligned(32)));
static uint8_t JpegBuffer[1024 * 63]__attribute((aligned(32)));

/* jpeg convert */
static JPEG_Converter Jcu;
static DisplayBase Display;

size_t encode_jpeg(uint8_t* buf, int len, int width, int height, uint8_t* inbuf) {
    size_t encode_size;
    JPEG_Converter::bitmap_buff_info_t bitmap_buff_info;
    JPEG_Converter::encode_options_t encode_options;
    bitmap_buff_info.width = width;
    bitmap_buff_info.height = height;
    bitmap_buff_info.format = JPEG_Converter::WR_RD_YCbCr422;
    bitmap_buff_info.buffer_address = (void *) inbuf;
    encode_options.encode_buff_size = len;
    encode_options.p_EncodeCallBackFunc = NULL;
    encode_options.input_swapsetting = JPEG_Converter::WR_RD_WRSWA_32_16_8BIT;

    encode_size = 0;
    dcache_invalid(buf, len);
    if (Jcu.encode(&bitmap_buff_info, buf, &encode_size, &encode_options)
            != JPEG_Converter::JPEG_CONV_OK) {
        encode_size = 0;
    }

    return encode_size;
}

size_t create_jpeg(){
    return encode_jpeg(JpegBuffer, sizeof(JpegBuffer), VIDEO_PIXEL_HW, VIDEO_PIXEL_VW, FrameBuffer_Video);
}

uint8_t* get_jpeg_adr(){
    return JpegBuffer;
}

/* Starts the camera */
void camera_start(void)
{
    // Initialize the background to black
    for (int i = 0; i < sizeof(FrameBuffer_Video); i += 2) {
        FrameBuffer_Video[i + 0] = 0x10;
        FrameBuffer_Video[i + 1] = 0x80;
    }

    // Camera
    EasyAttach_Init(Display);

    // Video capture setting (progressive form fixed)
    Display.Video_Write_Setting(
        DisplayBase::VIDEO_INPUT_CHANNEL_0,
        DisplayBase::COL_SYS_NTSC_358,
        (void *)FrameBuffer_Video,
        FRAME_BUFFER_STRIDE,
        VIDEO_FORMAT,
        WR_RD_WRSWA,
        VIDEO_PIXEL_VW,
        VIDEO_PIXEL_HW
    );
    EasyAttach_CameraStart(Display, DisplayBase::VIDEO_INPUT_CHANNEL_0);
}

/* Takes a video frame */
void create_gray(Mat &img_gray)
{
    // Transform buffer into OpenCV matrix
    Mat img_yuv(VIDEO_PIXEL_VW, VIDEO_PIXEL_HW, CV_8UC2, FrameBuffer_Video);

    // Convert from YUV422 to grayscale
    // [Note] Although the camera spec says the color space is YUV422,
    // using the color conversion code COLOR_YUV2GRAY_YUY2 gives
    // better result than using COLOR_YUV2GRAY_Y422
    // (Confirm by saving an image to SD card and then viewing it on PC.)
    cvtColor(img_yuv, img_gray, COLOR_YUV2GRAY_YUY2);
}
