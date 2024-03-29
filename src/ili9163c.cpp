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

ILI9163C::ILI9163C(SPI *spi, PinName cs, PinName dcx, PinName backlight):
        ILI9XXX(spi, cs, dcx, backlight)
{
    spi->frequency(24000000);
}

void ILI9163C::init()
{
    write_command(CMD_SWRESET);
    ThisThread::sleep_for(500ms);

    exit_sleep();
    ThisThread::sleep_for(5ms);

    write_command(CMD_PIXFMT); // Set Color Format 16bit
    write_data(0x05);
    ThisThread::sleep_for(5ms);

    write_command(CMD_DISPON); // display ON
    ThisThread::sleep_for(1ms);
}

} // namespace sixtron
