/*
 * Stm32 Eth - Ethernet connectivity for Stm32
 * Copyright (C) 2016 - 2017  offa
 *
 * This file is part of Stm32 Eth.
 *
 * Stm32 Eth is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Stm32 Eth is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Stm32 Eth.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <tuple>
#include <stdint.h>
#include "Platform.h"

namespace eth
{
    enum class Assign : uint8_t
    {
        spi1,
        spi2,
        spi3
    };


    using SpiConfig = std::tuple<Assign, GPIO_InitTypeDef, GPIO_InitTypeDef, SPI_InitTypeDef>;


    constexpr SpiConfig spi2(Assign::spi2,
            {(GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15),
                GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_HIGH, GPIO_AF5_SPI2},
            {GPIO_PIN_12,
                GPIO_MODE_OUTPUT_PP, GPIO_PULLUP, GPIO_SPEED_LOW, GPIO_AF5_SPI2},
            {SPI_MODE_MASTER,  SPI_DIRECTION_2LINES, SPI_DATASIZE_8BIT, SPI_POLARITY_LOW,
                SPI_PHASE_1EDGE, SPI_NSS_SOFT, SPI_BAUDRATEPRESCALER_4, SPI_FIRSTBIT_MSB,
                SPI_TIMODE_DISABLED, SPI_CRCCALCULATION_DISABLED, 0});

}
