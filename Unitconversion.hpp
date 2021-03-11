#pragma once

struct ParameterRange
{
public:
    struct Range
    {
    public:
        float min;
        float max;
    };

    ParameterRange(float pMin, float pMax, float vMin, float vMax, float tMin, float tMax, float kpMin, float kpMax, float kdMin, float kdMax);

    Range positionRange;
    Range velocityRange;
    Range torqueRange;
    Range kpRange;
    Range kdRange;
};

int float_to_uint(float x, float x_min, float x_max, int bits);
float uint_to_float(int x_int, float x_min, float x_max, int bits);
void toMiniCheetahCANData(float position, float velocity, float torque, float kp, float kd, ParameterRange &range, unsigned char (&data)[8]);
void toParameter(unsigned char (&data)[6], ParameterRange &range, int &canID, float &position, float &velocity, float &current);
