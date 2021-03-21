#include "resource/CamSetting.h"
#include "resource/SerialPort.h"

int main(int, char**)
{
    SerialPort port{};
    CamSetting cam;
    port.portOpen();

    if (!cam.openCam()){
        printf("Erro with the cam");
    } else if (!cam.loadCascade()){
        printf("erro with cascade classifier");
    } else {
        cam.capImage();
    }

    port.closePort();
    return 0;
}