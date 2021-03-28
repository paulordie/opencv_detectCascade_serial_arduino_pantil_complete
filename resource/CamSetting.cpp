//
// Created by pcorrea on 17/10/2020.
//

#include "CamSetting.h"

bool CamSetting::openCam() {

    capture = 0;
    if (capture.isOpened()){
        return true;
    } else {
        return false;
    }
}

void CamSetting::capImage() {
    for(;;) {
        
        if (!capture.grab()) {
            std::cout << "can not grab frame." << std::endl;

        } else {
            if (capture.retrieve(cap_img, 0)) {
                t = (double) cvGetTickCount();
                bool testCascade;
                cv::Mat gray, smallImg(cvRound(cap_img.rows / scale), cvRound(cap_img.cols / scale), CV_8UC1);

                cv::namedWindow("result", 1);
                cvtColor(cap_img, gray, CV_BGR2GRAY);
                resize(gray, smallImg, smallImg.size(), 0, 0, cv::INTER_LINEAR);
                equalizeHist(smallImg, smallImg); //realiza varias opera��es na vairiavel InputArray
                cascadeClassifier.detectMultiScale(smallImg, faces, 1.7, 3, 0
                                                                            //|CV_HAAR_FIND_BIGGEST_OBJECT
                                                                            |CV_HAAR_DO_ROUGH_SEARCH,
                        //| CV_HAAR_SCALE_IMAGE,
                                                   cv::Size(30, 30));

                vectDetect(faces);

                imshow("result", cap_img);
                if (cv::waitKey(30) >= 0) break;
            }
        }
    }
}

bool CamSetting::loadCascade() {
    if (!cascadeClassifier.load("/home/pcorrea/Documents/learning/cpluplus/clion1/haarcascade_frontalface_default.xml")){
        printf("erro cascadeclassifier");
        return false;
    } else {
        return true;
    }
}

void CamSetting::opencvVersion() {
    std::cout << "version CV" << CV_VERSION << std::endl;
}

void CamSetting::vectDetect(std::vector<cv::Rect>& _faces) {

    const static cv::Scalar colors[] = {CV_RGB(255, 0, 0)};

    int i = 0;

    for (std::vector<cv::Rect>::const_iterator r = _faces.begin(); r != _faces.end(); r++, i++) {

        color = colors[i % 8];


        double aspect_ratio = (double) r->width / r->height;
        if (0.75 < aspect_ratio && aspect_ratio < 1.3) {
            center.x = cvRound((r->x + r->width * 0.5) * scale);
            center.y = cvRound((r->y + r->height * 0.5) * scale);
            int targetX = center.x;
            int targetY = center.y;
            radius = cvRound((r->width + r->height) * 0.25 * scale);
            circle( cap_img, center, radius, color, 3, 8, 0 );
            rectangle(cap_img, cvPoint(cvRound(r->x * scale), cvRound(r->y * scale)),
                      cvPoint(cvRound((r->x + r->width - 1) * scale),
                              cvRound((r->y + r->height - 1) * scale)),
                      color, 3, 8, 0);
            std::cout << "x: " << faces[i].x << "  y: " << faces[i].y << std::endl;

            t = (double) cvGetTickCount() - t;
            printf("tempo de deteccao = %g ms\n", t / ((double) cvGetTickFrequency() * 1000.));

            writePosition(targetX, targetY);

        }
    }
    // return cv::Point();
}

void CamSetting::writePosition(int targetX, int targetY) {
    char outputChars[] = "c";
    if (targetX > 340) //340
    {
        outputChars[0] = 'l';
        port.writePort(outputChars, outputChars);

        servoPosition += 1;

        if (servoPosition > 180)
            servoPosition = 180;
    }
    // Check whether camera should turn to its right if the circle gets near the left end of the screen
    if (targetX < 290) //290
    {
        outputChars[0] = 'r';
        port.writePort(outputChars, outputChars);

        servoPosition -= 1;

        if (servoPosition < 0)
            servoPosition = 0;
    }

    if (targetY > 250) //250
    {
        outputChars[0] = 'e';
        port.writePort(outputChars, outputChars);

        servoPosition1 += 1;

        if (servoPosition1 > 180)
            servoPosition1 = 180;
    }

    if (targetY < 200) //200
    {
        outputChars[0] = 'f';
        port.writePort(outputChars, outputChars);

        servoPosition1 -= 1;

        if (servoPosition1 < 0)
            servoPosition1 = 0;
    }
}
