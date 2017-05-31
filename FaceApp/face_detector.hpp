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

#ifndef FACE_DETECTOR_HPP_
#define FACE_DETECTOR_HPP_

#include "mbed.h"
#include "opencv2/opencv.hpp"

using namespace cv;

/* FACE DETECTOR Parameters */
#define DETECTOR_SCALE_FACTOR (2)
#define DETECTOR_MIN_NEIGHBOR (4)
#define DETECTOR_MIN_SIZE     (30)

/**
* @brief	Initializes the face detector module
* @param	filename	Name of the cascade classifier file to detect faces
* @return	None
*/
void detectFaceInit(const std::string &filename);

/**
* @brief	Detects a face in an image
* @param	img_gray	Grayscale image
* @param	rect_face	Rectangle area of a detected face
* @return	None
*/
void detectFace(const cv::Mat &img_gray, cv::Rect &rect_face);

#endif
