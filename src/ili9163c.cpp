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

#include "ili9163c/ili9163c.h"

namespace sixtron {

#define SIZE 20480

ILI9163C::ILI9163C(SPI *spi, PinName cs, PinName dcx, PinName backlight):_spi(spi), _cs(cs),_dcx(dcx),_backlight(backlight)
{
	_cs = 1;
}

void ILI9163C::init()
{
	write_command(CMD_SWRESET);
	ThisThread::sleep_for(500ms);

	exit_sleep();
	ThisThread::sleep_for(5ms);

	write_command(CMD_PIXFMT);//Set Color Format 16bit   
	write_data(0x05);
	ThisThread::sleep_for(5ms);

	write_command(CMD_GAMMASET);//default gamma curve 3
	write_data(0x04);//0x04
	ThisThread::sleep_for(1ms);

	write_command(CMD_DINVCTR);//display inversion 
	write_data(0x07);
	ThisThread::sleep_for(1ms);

	write_command(CMD_DISPON);//display ON 

	_backlight.period_ms(1);
	_backlight.write(0.3f);
	ThisThread::sleep_for(1ms);
}

void ILI9163C::exit_sleep()
{
	write_command(CMD_SLPOUT);
	ThisThread::sleep_for(120ms);
}

void ILI9163C::write_command(uint8_t cmd)
{
	// Write command
	_dcx = 0;
	_cs = 0;
    _spi->write(cmd);
	_cs = 1;
}

void ILI9163C::write_data(uint8_t data, int len)
{
	// Write Data 8 bits
	_spi->format(8);
	_dcx = 1;
	_cs = 0;
	for(int i=0; i<len; i++){
	    _spi->write(data);
		data++;
	}
	_cs = 1;
}

void ILI9163C::write_data_16(uint16_t* data, int t)
{
	// Write Data 16 bits
	_spi->format(16);
	_dcx = 1;
	_cs = 0;
	for(int i=0; i<t; i++){
	    _spi->write(*data);
		data++;
	}
	_cs = 1;
}

void ILI9163C::setAddr(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1){
	write_command(CMD_CLMADRS);
	write_data_16(&x0,1);
	write_data_16(&x1,1);

	write_command(CMD_PGEADRS);
	write_data_16(&y0,1);
	write_data_16(&y1,1);

	write_command(CMD_RAMWR);
}

void ILI9163C::drawPixel(int16_t x, int16_t y, uint16_t color) {
	setAddr(x,y,x+1,y+1);
	write_data_16(&color, 1);
}

void ILI9163C::displayImage(uint16_t *image, uint16_t width, uint16_t height){
	uint8_t x0 = (128-width)/2;
	uint8_t x1 = (128-width)/2;
	uint8_t y0 = x0 + width -1;
	uint8_t y1 = x1 + height -1;
	setAddr(x0,x1,y0,y1);
	write_data_16(image, width*height);
}

void ILI9163C::clearScreen(uint16_t color){
	int px;
	uint16_t table[SIZE];
	setAddr(0,0,128,160);
	
	for (px = 0; px < SIZE; px++){
		table[px] = color;
	}

	write_data_16(table, SIZE);
}

} // namespace sixtron