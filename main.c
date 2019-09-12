/*
 * Softuart example
 *
 * Copyright (C) 2017 Ruslan V. Uss <unclerus@gmail.com>
 * Copyright (C) 2016 Bernhard Guillon <Bernhard.Guillon@web.de>
 * Copyright (c) 2015 plieningerweb
 *
 * MIT Licensed as described in the file LICENSE
 */

#include <esp/gpio.h>
#include <esp/uart.h>
#include <espressif/esp_common.h>
#include <stdio.h>

#include "pms.h"

void user_init(void)
{
  // setup real UART for now
  uart_set_baud(0, 115200);
  printf("SDK version:%s\n\n", sdk_system_get_sdk_version());

  for(int i = 0; i < 10; i ++) {
    uint8_t* chrData;
    chrData = pms_read_data();

    uint8_t pm1, pm25, pm10;
    pm1 = GetPM_Data(chrData, PM1_0_ATMOSPHERE_H, PM1_0_ATMOSPHERE_L);
    pm25 = GetPM_Data(chrData, PM2_5_ATMOSPHERE_H, PM2_5_ATMOSPHERE_L);
    pm10 = GetPM_Data(chrData, PM10_ATMOSPHERE_H, PM10_ATMOSPHERE_L);
    printf("pm1:%u pm2.5:%u pm10:%u\r\n", pm1, pm25, pm10);
  }
}
