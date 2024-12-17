#include "Leg.h"

// Dont set any servo or use anything related to the PCA9685 in the constructor
// They are not initialized yet
Leg::Leg(Adafruit_PWMServoDriver& pca, std::vector<int> pins, Legside leftRight, std::vector<float> shift, float rotation)
    : pca(pca)
{
    this->pins = pins;
    this->leftRight = leftRight;
    this->shift = shift;
    this->rotation = rotation;

    this->servoOffsets = leftRight == Right ? std::vector<float> {radians(90), radians(125), radians(210)} :
                                              std::vector<float> {radians(90), radians(55), radians(-30)};

    forwardKinematics();
    defaultPosition = position;
}

void Leg::setPosition(std::vector<float> position)
{
    this->position = position;
    inverseKinematics();
    setServo();
}

void Leg::setdPosition(std::vector<float> dPosition)
{
    position = {defaultPosition[0] + dPosition[0],
                defaultPosition[1] + dPosition[1],
                defaultPosition[2] - dPosition[2]};
    inverseKinematics();
    setServo();
}

void Leg::homing()
{
    if(abs(this->position[0] - this->defaultPosition[0]) < 0.1 &&
       abs(this->position[1] - this->defaultPosition[1]) < 0.1 &&
       abs(this->position[2] - this->defaultPosition[2]) < 0.1)
    {
        this->position = defaultPosition;
    }
    else
    {
        for(int i = 0;i < 3;i++) this->position[i] = this->position[i] * 0.7 + this->defaultPosition[i] * 0.3;
    }

    inverseKinematics();
    setServo();

    vTaskDelay(100);
}

void Leg::setServo()
{
    for(int i = 0;i < 3;i++)
    {
        float angle = leftRight == Right ? servoOffsets[i] - radians[i] :
                                           servoOffsets[i] + radians[i];
        int pulse = int(angle * (SERVOMAX - SERVOMIN) / PI) + SERVOMIN;
        pca.setPWM(pins[i], 0, pulse);
    }
}

void Leg::forwardKinematics()
{
    float g2 = FEMUR * sin(radians[1]);
	float p1 = FEMUR * cos(radians[1]);
	float h = sqrt(pow(FEMUR, 2) + pow(TIBIA, 2) - (2 * FEMUR * TIBIA * cos(PI - radians[2])));

	float phi1 = acos((pow(FEMUR, 2) + pow(h, 2) - pow(TIBIA, 2)) / (FEMUR * h * 2));
	float phi2 = PI - (PI - radians[2]) - phi1;
	float phi3 = phi1 - radians[1];

	float pp = h * cos(phi3);
	float g1 = h * sin(phi3);

	float xa = COXA * cos(radians[0]), ya = COXA * sin(radians[0]);
	float xb = pp * cos(radians[0]), yb = pp * sin(radians[0]);
	float xc = p1 * cos(radians[0]), yc = p1 * sin(radians[0]);

    // Adding rotation and reflection and offset
    float x = ((xa + xb) * cos(rotation)) - ((ya + yb) * sin(rotation));
    float y = ((xa + xb) * sin(rotation)) + ((ya + yb) * cos(rotation));
    float z = g1;
    if(leftRight == Left) x = -x;
    x += shift[0], y += shift[1], z += shift[2];

    position = {x, y, z};
}

void Leg::inverseKinematics()
{
    // Removing offset and reflection and rotation
    float _x = position[0] - shift[0], _y = position[1] - shift[1], _z = position[2];
    if(leftRight == Left) _x = -_x;
    float x = (_x * cos(-rotation)) - (_y * sin(-rotation));
    float y = (_x * sin(-rotation)) + (_y * cos(-rotation));
    float z = _z;

	float theta1 = atan(y / x);

	float xa = COXA * cos(theta1), ya = COXA * sin(theta1);
	float xb = x - xa, yb = y - ya;

	float p = xb / cos(theta1);
	float g = abs(z);
	float h = sqrt(pow(p, 2) + pow(g, 2));

	float phi1 = acos((pow(FEMUR, 2) + pow(h, 2) - pow(TIBIA, 2)) / (FEMUR * h * 2));
	float phi2 = acos((pow(TIBIA, 2) + pow(h, 2) - pow(FEMUR, 2)) / (TIBIA * h * 2));
	float phi3 = asin(g / h);

	float theta2 = z > 0 ? phi1 - phi3 : phi1 + phi3;
	float theta3 = phi1 + phi2;

	radians = {theta1, theta2, theta3};
}