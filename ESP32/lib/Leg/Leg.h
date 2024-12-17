#include <vector>
#include <Adafruit_PWMServoDriver.h>
#include "LUT.h"

#define SERVOMIN 100
#define SERVOMAX 530

#define COXA     43
#define FEMUR    80
#define TIBIA    133

enum Legside
{
    Left,
    Right
};

class Leg
{
public:
    Adafruit_PWMServoDriver& pca;
    std::vector<int> pins;

    std::vector<float> defaultPosition;
    std::vector<float> radians = {radians(0), radians(50), radians(150)};
    std::vector<float> position;

    std::vector<float> servoOffsets; // = {radians(90), radians(125), radians(195)};
    Legside leftRight;
    std::vector<float> shift = {0, 0, 0};
    float rotation;

    Leg(Adafruit_PWMServoDriver& pca,
        std::vector<int> pins,
        Legside legside,
        std::vector<float> shift,
        float rotation);
    void setPosition(std::vector<float> position);
    void setdPosition(std::vector<float> dPosition);
    void homing();

    void setServo();
    void forwardKinematics();
    void inverseKinematics();
};
