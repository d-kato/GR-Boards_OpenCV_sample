#include "mbed.h"
#include "EasyAttach_CameraAndLCD.h"
#include "SdUsbConnect.h"
#include "opencv.hpp"
#include "camera_if.hpp"
#include "face_detector.hpp"
#include "DisplayApp.h"

using namespace cv;

#define DBG_CAPTURE   (0)
#define DBG_PCMONITOR (1)
#define FACE_DETECTOR_MODEL     "/storage/lbpcascade_frontalface.xml"

/* Application variables */
Mat frame_gray;     // Input frame (in grayscale)

#if (DBG_PCMONITOR == 1)
/* For viewing image on PC */
static DisplayApp  display_app;
#endif

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);
Timer  detect_timer;

int main() {
#if (DBG_CAPTURE == 1)
    char file_name[32];
    int file_name_index_detected = 1;
#endif

    printf("Camera Test\r\n");

    // Camera
    camera_start();
    led4 = 1;

    // SD & USB
    SdUsbConnect storage("storage");
    printf("Finding a storage...");
    // wait for the storage device to be connected
    storage.wait_connect();
    printf("done\n");
    led3 = 1;

    // Initialize the face detector
    printf("Initializing the face detector...");
    detectFaceInit(FACE_DETECTOR_MODEL);
    printf("done\n");
    led2 = 1;

    detect_timer.reset();
    detect_timer.start();

    while (1) {
        // Retrieve a video frame (grayscale)
        create_gray(frame_gray);
        if (frame_gray.empty()) {
            printf("ERR: There is no input frame, retry to capture\n");
            continue;
        }

        // Detect a face in the frame
        Rect face_roi;
        detectFace(frame_gray, face_roi);

        if (face_roi.width > 0 && face_roi.height > 0) {   // A face is detected
            led1 = 1;
            printf("Detected a face X:%d Y:%d W:%d H:%d\n",face_roi.x, face_roi.y, face_roi.width, face_roi.height);
#if MBED_CONF_APP_LCD
            ClearSquare();
            DrawSquare(face_roi.x, face_roi.y, face_roi.width, face_roi.height, 0x0000f0f0);
#endif
            detect_timer.reset();

#if (DBG_CAPTURE == 1)
            sprintf(file_name, "/storage/detected_%d.bmp", file_name_index_detected++);
            imwrite(file_name, frame_gray);
#endif
        } else {
#if MBED_CONF_APP_LCD
            if (detect_timer.read_ms() >= 1000) {
                ClearSquare();
            }
#endif
            led1 = 0;
        }

#if (DBG_PCMONITOR == 1)
        size_t jpeg_size = create_jpeg();
        display_app.SendJpeg(get_jpeg_adr(), jpeg_size);
#endif

    }
}
