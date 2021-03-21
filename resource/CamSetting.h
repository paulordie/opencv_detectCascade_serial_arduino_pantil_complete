//
// Created by pcorrea on 17/10/2020.
//

#ifndef CLION1_CAMSETTING_H
#define CLION1_CAMSETTING_H

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>


#include "SerialPort.h"

class CamSetting {
public:
    bool openCam();
    void capImage();
    bool loadCascade();
    void opencvVersion();
    void vectDetect(std::vector<cv::Rect>& _faces);
    void writePosition(int targetX, int targetY);

private:
    SerialPort port;
    cv::Mat cap_img, cap_gray,frameCopy;
    cv::VideoCapture capture;
    cv::CascadeClassifier cascadeClassifier;

    int servoPosition = 90;
    int servoPosition1 = 90;

    double t = 0;
    double scale = 1;
    int i = 0;

    cv::Point center;
    cv::Scalar color;
    int radius;

    std::vector<cv::Rect> faces;

};


#endif //CLION1_CAMSETTING_H
