#ifndef IMU_H
#define IMU_H

#include "main.h"
typedef struct {
    //Gia tri thuc
    float raw_roll;  				
    float raw_pitch;
    float raw_yaw;

    //Gia tri moc khi bam nut
    float offset_roll;			
    float offset_pitch;
    float offset_yaw;

    //Gia tri hien thi
    float roll;							
    float pitch;
    float yaw;
} IMU_Data;

// Khai bao ham
void IMU_Process(uint8_t *buffer, IMU_Data *data);
void IMU_SetZero(IMU_Data *data);

#endif
