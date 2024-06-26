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

#include "ili9xxx.h"
#include "mbed.h"

namespace sixtron {

class ILI9163C: public ILI9XXX {
public:
    ILI9163C(SPI *spi, PinName cs, PinName dcx, PinName backlight);
    void init();
};

} // namespace sixtron

#endif // CATIE_SIXTRON_ILI9163C_H_
