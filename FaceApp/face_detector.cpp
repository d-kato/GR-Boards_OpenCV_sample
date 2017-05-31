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

#include "face_detector.hpp"

/* Internally store the cascade classifier model */
CascadeClassifier detector_classifier;

/* Initializes the face detector module */
void detectFaceInit(const std::string &filename) {
    // Load the cascade classifier file
    detector_classifier.load(filename);

    if (detector_classifier.empty()) {
        printf("ERROR: Cannot load cascade classifier file\n");
        CV_Assert(0);
        mbed_die();
    }
}


/* Detects a face in an image */
void detectFace(const Mat &img_gray, Rect &rect_face) {
    if (detector_classifier.empty()) {
        printf("ERROR: Cannot load cascade classifier file\n");
        CV_Assert(0);
        mbed_die();
    }

    // Perform detected the biggest face
    std::vector<Rect> rect_faces;
    detector_classifier.detectMultiScale(img_gray, rect_faces, 
                                         DETECTOR_SCALE_FACTOR, 
                                         DETECTOR_MIN_NEIGHBOR, 
                                         CASCADE_FIND_BIGGEST_OBJECT,
                                         Size(DETECTOR_MIN_SIZE, DETECTOR_MIN_SIZE));
    if (rect_faces.size() > 0) {
        // A face is detected
        rect_face = rect_faces[0];
    } else {
        // No face is detected, set an invalid rectangle
        rect_face.x = -1;
        rect_face.y = -1;
        rect_face.width = -1;
        rect_face.height = -1;
    }
}
