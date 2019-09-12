
#include "pms.h"
#include "FreeRTOS.h"
#include "string.h"
#include "task.h"
#include "esp/gpio.h"

#include <esp/uart.h>
#include <espressif/esp_common.h>
#include <softuart/softuart.h>

#define RX_PIN 5
#define TX_PIN 4

#define PING_TIMEOUT 1000000 //us
#define timeout_expired(start, len) ((uint32_t)(sdk_system_get_time() - (start)) >= (len))

uint8_t GetPM_Data(uint8_t chrSrc[], int bytHigh, int bytLow) {

  uint8_t high = chrSrc[bytHigh];
  uint8_t low = chrSrc[bytLow];
  uint8_t result = low + (high << 8);
  return result;
}

uint8_t * pms_read_data() {
  // setup software uart to 9600 8n1
  softuart_open(0, 9600, RX_PIN, TX_PIN);

  // uint8_t pm1, pm25, pm10;
  static uint8_t chrData[30] = {0};

  int bytCount = 0;
  bool gotValue = false;

  uint32_t start = sdk_system_get_time();
  while (!gotValue && !timeout_expired(start, PING_TIMEOUT)) {

    while (!softuart_available(0)) {} /* Do nothing. Just wait until we have a byte */

    uint8_t c = softuart_read(0);
    if (c == START_1 && bytCount == 0) {
      bytCount = 1;
    }
    if (c == START_2 && bytCount == 1) {
      bytCount = 2;
    }
    if (bytCount == 2) {
      for (int i = 0; i < 30; i++) {
        while (!softuart_available(0)) {} /* Do nothing. Just wait until we have a byte */
        uint8_t d = softuart_read(0);
        chrData[i] = d;
      }

      // pm1 = GetPM_Data(chrData, PM1_0_ATMOSPHERE_H, PM1_0_ATMOSPHERE_L);
      // pm25 = GetPM_Data(chrData, PM2_5_ATMOSPHERE_H, PM2_5_ATMOSPHERE_L);
      // pm10 = GetPM_Data(chrData, PM10_ATMOSPHERE_H, PM10_ATMOSPHERE_L);
      // printf("pm1:%u pm2.5:%u pm10:%u\r\n", pm1, pm25, pm10);
      gotValue = true;
    }
  }

  softuart_close(0);
  return chrData;
}
