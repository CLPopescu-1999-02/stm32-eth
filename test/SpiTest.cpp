/*
 * Stm32 Eth - Ethernet connectivity for Stm32
 * Copyright (C) 2016  offa
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

#include "Spi.h"
#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>
#include "mock/Stm32HalComparator.h"

void platform::stm32::spiClockEnable()
{
    mock("platform::stm32").actualCall("spiClockEnable");
}

TEST_GROUP(SpiTest)
{
    void setup() override
    {
        spi = std::make_unique<eth::Spi>();
        mock().strictOrder();

        mock().installComparator("SPI_InitTypeDef", spiHandleCompare);
        mock().installComparator("GPIO_InitTypeDef", gpioInitCompare);
    }

    void teardown() override
    {
        mock().checkExpectations();
        mock().clear();
        mock().removeAllComparatorsAndCopiers();
    }

    std::unique_ptr<eth::Spi> spi;
    MockSupport& halSpi = mock("HAL_SPI");
    MockSupport& halGpio = mock("HAL_GPIO");
    SpiHandleComparator spiHandleCompare;
    GpioInitComparator gpioInitCompare;
    static constexpr uint32_t timeout = 0xffffffff;
};

TEST(SpiTest, initSetupsGpioPins)
{
    GPIO_InitTypeDef gpioInit;
    gpioInit.Pin = GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    gpioInit.Mode = GPIO_MODE_AF_PP;
    gpioInit.Pull = GPIO_NOPULL;
    gpioInit.Speed = GPIO_SPEED_HIGH;
    gpioInit.Alternate = GPIO_AF5_SPI2;

    GPIO_InitTypeDef gpioInitSS;
    gpioInitSS.Pin = GPIO_PIN_12;
    gpioInitSS.Mode = GPIO_MODE_OUTPUT_PP;
    gpioInitSS.Pull = GPIO_PULLUP;
    gpioInitSS.Speed = GPIO_SPEED_LOW;
    gpioInitSS.Alternate = GPIO_AF5_SPI2;

    mock("platform::stm32").expectOneCall("spiClockEnable");
    halGpio.expectOneCall("HAL_GPIO_Init")
        .withPointerParameter("GPIOx", GPIOB)
        .withParameterOfType("GPIO_InitTypeDef", "GPIO_Init", &gpioInit);
    halGpio.expectOneCall("HAL_GPIO_Init")
        .withPointerParameter("GPIOx", GPIOB)
        .withParameterOfType("GPIO_InitTypeDef", "GPIO_Init", &gpioInitSS);
    halSpi.expectOneCall("HAL_SPI_Init").ignoreOtherParameters();

    spi->init();
}

TEST(SpiTest, initSetupsSpi)
{
    SPI_InitTypeDef spiInit;
    spiInit.Mode = SPI_MODE_MASTER;
    spiInit.Direction = SPI_DIRECTION_2LINES;
    spiInit.DataSize = SPI_DATASIZE_8BIT;
    spiInit.CLKPolarity = SPI_POLARITY_LOW;
    spiInit.CLKPhase = SPI_PHASE_1EDGE;
    spiInit.NSS = SPI_NSS_SOFT;
    spiInit.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
    spiInit.FirstBit = SPI_FIRSTBIT_MSB;
    spiInit.TIMode = SPI_TIMODE_DISABLED;
    spiInit.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
    spiInit.CRCPolynomial = 0;

    mock("platform::stm32").expectOneCall("spiClockEnable");
    halGpio.expectNCalls(2, "HAL_GPIO_Init").ignoreOtherParameters();
    halSpi.expectOneCall("HAL_SPI_Init")
        .withPointerParameter("hspi", &spi->nativeHandle())
        .withPointerParameter("hspi.instance", SPI2)
        .withParameterOfType("SPI_InitTypeDef", "hspi.init", &spiInit);
    spi->init();
}

TEST(SpiTest, transmitTransmitsByte)
{
    const uint8_t data = 0xab;
    constexpr uint16_t size = sizeof(data);

    halSpi.expectOneCall("HAL_SPI_Transmit")
        .withPointerParameter("hspi", &spi->nativeHandle())
        .withMemoryBufferParameter("pData", &data, size)
        .withParameter("Size", size)
        .withParameter("Timeout", timeout);

    spi->transmit(data);
}

TEST(SpiTest, receiveReceivesByte)
{
    const uint8_t data = 0xcd;
    constexpr uint16_t size = sizeof(data);

    halSpi.expectOneCall("HAL_SPI_Receive")
        .withPointerParameter("hspi", &spi->nativeHandle())
        .withOutputParameterReturning("pData", &data, size)
        .withParameter("Size", size)
        .withParameter("Timeout", timeout);

    auto result = spi->receive();
    CHECK_EQUAL(data, result);
}

TEST(SpiTest, setSlaveSelectSetsPinLow)
{
    halGpio.expectOneCall("HAL_GPIO_WritePin")
        .withPointerParameter("GPIOx", GPIOB)
        .withParameter("GPIO_Pin", GPIO_PIN_12)
        .withParameter("PinState", GPIO_PIN_RESET);

    spi->setSlaveSelect();
}

TEST(SpiTest, resetSlaveSelectSetsPinHigh)
{
    halGpio.expectOneCall("HAL_GPIO_WritePin")
        .withPointerParameter("GPIOx", GPIOB)
        .withParameter("GPIO_Pin", GPIO_PIN_12)
        .withParameter("PinState", GPIO_PIN_SET);

    spi->resetSlaveSelect();
}

