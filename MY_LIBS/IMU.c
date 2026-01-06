#include "IMU.h"

// TINH TOAN DU LIEU THU DUOC
void IMU_Process(uint8_t *buffer, IMU_Data *data)
{
    //CHECK GOI TIN PROTOCOL
    if (buffer[0] == 0x55 && buffer[1] == 0x53)
    {
        // GHEP BYTE
        short r = (buffer[3] << 8) | buffer[2];
        short p = (buffer[5] << 8) | buffer[4];
        short y = (buffer[7] << 8) | buffer[6];

        //TINH GOC
        data->raw_roll  = (float)r / 32768.0f * 180.0f;
        data->raw_pitch = (float)p / 32768.0f * 180.0f;
        data->raw_yaw   = (float)y / 32768.0f * 180.0f;

        //GOC HIEN TAI - HIEN THI RA MAN HINH
        data->roll  = data->raw_roll  - data->offset_roll;
        data->pitch = data->raw_pitch - data->offset_pitch;
        data->yaw   = data->raw_yaw   - data->offset_yaw;
    }
}

// SET ZERO
void IMU_SetZero(IMU_Data *data)
{
    data->offset_roll  = data->raw_roll;
    data->offset_pitch = data->raw_pitch;
    data->offset_yaw   = data->raw_yaw;
}
