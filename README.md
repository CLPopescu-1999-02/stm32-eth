# [Stm32 Eth](https://github.com/offa/stm32-eth)

[![Build Status](https://travis-ci.org/offa/stm32-eth.svg?branch=master)](https://travis-ci.org/offa/stm32-eth)
[![GitHub release](https://img.shields.io/github/release/offa/stm32-eth.svg)](https://github.com/offa/stm32-eth/releases)
[![License](https://img.shields.io/badge/license-GPLv3-yellow.svg)](LICENSE)
![C++](https://img.shields.io/badge/c++-14-green.svg)

Ethernet connectivity for *Stm32F4xx* Boards using W5100 devices.


## Requirements

 - [**CMake**](http://www.cmake.org/)
 - [**CppUTest**](https://github.com/cpputest/cpputest) – *(Optional)*
 - [**GNU ARM Embedded Toolchain**](https://launchpad.net/gcc-arm-embedded)


## Testing

```
mkdir build && cd build
cmake ..
make
make unittest
```

It's also possible to use `make test` / `ctest` instead. For `unittest` it's possible to switch verbosity by CMake option.


## Pin assignment

| Pin | Stm32 |
|-----|-------|
MOSI | PB15
MISO | PB14
SCK | PB13
SS | PB12

#### W5100

Connect ***Reset*** and ***3.3 V*** with **4.7 kΩ Resistor**.


## License

**GNU General Public License (GPL)**

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.


### Third party licenses

The License does ***not*** apply to files of `system` directory. Files included in the `system` folder are licensed under different conditions – please refer to it's files for more details.

