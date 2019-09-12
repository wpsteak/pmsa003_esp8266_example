
// https://sites.google.com/site/zsgititit/home/arduino/arduino-shi-yongpmsa003zhen-cepm2-5-bing-shi-yongesp8266tou-guophp-chu-cun-zi-liao-daomysql

#ifndef __PMS_H__
#define __PMS_H__

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define START_1 0x42
#define START_2 0x4d

#define DATA_LENGTH_H 0
#define DATA_LENGTH_L 1
#define PM1_0_CF1_H 2
#define PM1_0_CF1_L 3
#define PM2_5_CF1_H 4
#define PM2_5_CF1_L 5
#define PM10_CF1_H 6
#define PM10_CF1_L 7
#define PM1_0_ATMOSPHERE_H 8
#define PM1_0_ATMOSPHERE_L 9
#define PM2_5_ATMOSPHERE_H 10
#define PM2_5_ATMOSPHERE_L 11
#define PM10_ATMOSPHERE_H 12
#define PM10_ATMOSPHERE_L 13
#define UM0_3_H 14
#define UM0_3_L 15
#define UM0_5_H 16
#define UM0_5_L 17
#define UM1_0_H 18
#define UM1_0_L 19
#define UM2_5_H 20
#define UM2_5_L 21
#define UM5_0_H 22
#define UM5_0_L 23
#define UM10_H 24
#define UM10_L 25
#define VERSION 26
#define ERROR_CODE 27
#define CHECKSUM 29

uint8_t GetPM_Data(uint8_t chrSrc[], int bytHigh, int bytLow);

uint8_t * pms_read_data();

#ifdef __cplusplus
}
#endif

#endif  // __PMS_H__
