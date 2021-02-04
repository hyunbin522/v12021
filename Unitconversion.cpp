#include "Unitconversion.hpp"

ParameterRange::ParameterRange(float pMin, float pMax, float vMin, float vMax, float tMin, float tMax, float kpMin, float kpMax, float kdMin, float kdMax)
{
    positionRange.min = pMin;
    positionRange.max = pMax;

    velocityRange.min = vMin;
    velocityRange.max = vMax;

    torqueRange.min = tMin;
    torqueRange.max = tMax;
    
    kpRange.min = kpMin;
    kpRange.max = kpMax;

    kdRange.min = kdMin;
    kdRange.max = kdMax;
}

int float_to_uint(float x, float x_min, float x_max, int bits){
    /// Converts a float to an unsigned int, given range and number of bits ///
    float span = x_max - x_min;
    float offset = x_min;
    return (int) ((x-offset)*((float)((1<<bits)-1))/span);
}
    
    
float uint_to_float(int x_int, float x_min, float x_max, int bits){
    /// converts unsigned int to float, given range and number of bits ///
    float span = x_max - x_min;
    float offset = x_min;
    return ((float)x_int)*span/((float)((1<<bits)-1)) + offset;
}

void toMiniCheetahCANData(float position, float velocity, float torque, float kp, float kd, ParameterRange &range, unsigned char (&data)[8])
{
    int p_int = float_to_uint(position, range.positionRange.min, range.positionRange.max, 16);
    int v_int = float_to_uint(velocity, range.velocityRange.min, range.velocityRange.max, 12);
    int t_int = float_to_uint(torque, range.torqueRange.min, range.torqueRange.max, 12);
    int kp_int = float_to_uint(kp, range.kpRange.min, range.kpRange.max, 12);
    int kd_int = float_to_uint(kd, range.kdRange.min, range.kdRange.max, 12);

    data[0] = p_int >> 8;
    data[1] = p_int & 0xff;
    data[2] = v_int >> 4;
    data[3] = ((v_int&0xF)<<4) | (kp_int >> 8);
    data[4] = kp_int & 0xff;
    data[5] = kd_int >> 4;
    data[6] = ((kd_int & 0xf) << 4) | (t_int >> 8);
    data[7] = t_int & 0xff;
}
void RevMiniCheetahCANData(unsigned char (&rdata)[6],ParameterRange &range,float(&data1)[4])
{   float id = (float)rdata[0];
    float pos= (float)((float)rdata[1]*256+(float)rdata[2]-32768)*(range.positionRange.max-range.positionRange.min)/32768;
    float vel= (float)((float)rdata[3]*16+(int)rdata[4]/16-2048)*(range.velocityRange.max-range.velocityRange.min)/2048;
    float tor= (float)((int)rdata[4]%16*256+(float)rdata[5]-2048)*(range.torqueRange.max-range.torqueRange.min)/2048;
    data1[0]=id;
    data1[1]=pos;
    data1[2]=vel;
    data1[3]=tor;
}