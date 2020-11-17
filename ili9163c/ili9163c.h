/*
 * Copyright (c) 2020, CATIE
 * SPDX-License-Identifier: Apache-2.0
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef CATIE_SIXTRON_ILI9163C_H_
#define CATIE_SIXTRON_ILI9163C_H_

#include "mbed.h"

namespace sixtron {

//ILI9163C registers
#define CMD_NOP     	0x00
#define CMD_SWRESET 	0x01
#define CMD_SLPIN   	0x10
#define CMD_SLPOUT  	0x11
#define CMD_PTLON   	0x12
#define CMD_NORML   	0x13
#define CMD_DINVOF  	0x20
#define CMD_DINVON   	0x21
#define CMD_GAMMASET 	0x26
#define CMD_DISPOFF 	0x28
#define CMD_DISPON  	0x29
#define CMD_IDLEON  	0x39
#define CMD_IDLEOF  	0x38
#define CMD_CLMADRS   	0x2A
#define CMD_PGEADRS   	0x2B

#define CMD_RAMWR   	0x2C
#define CMD_RAMRD   	0x2E
#define CMD_CLRSPACE   	0x2D
#define CMD_PARTAREA	0x30
#define CMD_VSCLLDEF	0x33
#define CMD_TEFXLON		0x35
#define CMD_TEFXLOF		0x34
#define CMD_MADCTL  	0x36
#define CMD_VSSTADRS	0x37
#define CMD_PIXFMT  	0x3A
#define CMD_FRMCTR1 	0xB1
#define CMD_FRMCTR2 	0xB2
#define CMD_FRMCTR3 	0xB3
#define CMD_DINVCTR		0xB4
#define CMD_RGBBLK		0xB5
#define CMD_DFUNCTR 	0xB6
#define CMD_SDRVDIR 	0xB7
#define CMD_GDRVDIR 	0xB8 

#define CMD_PWCTR1  	0xC0
#define CMD_PWCTR2  	0xC1
#define CMD_PWCTR3  	0xC2
#define CMD_PWCTR4  	0xC3
#define CMD_PWCTR5  	0xC4
#define CMD_VCOMCTR1  	0xC5
#define CMD_VCOMCTR2  	0xC6
#define CMD_VCOMOFFS  	0xC7
#define CMD_PGAMMAC		0xE0
#define CMD_NGAMMAC		0xE1
#define CMD_GAMRSEL		0xF2

class ILI9163C
{
public:
    ILI9163C(SPI *spi, PinName cs, PinName dcx, PinName backlight);
    void init();
    void clearScreen(uint16_t color);
    void displayImage(uint16_t *image, uint16_t width, uint16_t height);

private:
    SPI *_spi;
    DigitalOut _cs;
    DigitalOut _dcx;
    PwmOut _backlight;

    void write_command(uint8_t cmd);
    void write_data(uint8_t data, int len = 1);
    void write_data_16(uint16_t *data, int t);
    void exit_sleep();
    void setAddr(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
};

} // namespace sixtron

#endif // CATIE_SIXTRON_ILI9163C_H_

