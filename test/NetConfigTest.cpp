/*
 * Stm32 Eth - Ethernet connectivity for Stm32
 * Copyright (C) 2016-2018  offa
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

#include "NetConfig.h"
#include <CppUTest/TestHarness.h>

using eth::NetAddress;

TEST_GROUP(NetConfigTest)
{
    void setup() override
    {
    }

    void teardown() override
    {
    }

    template<std::size_t n>
    bool checkValue(NetAddress<n> e, NetAddress<n> a) const
    {
        return std::equal(std::cbegin(e), std::cend(e), std::cbegin(a));
    }
};

TEST(NetConfigTest, getValues)
{
    constexpr eth::NetConfig cfg{{{0, 0, 0, 0}},
                                {{1, 1, 1, 1}},
                                {{2, 2, 2, 2}},
                                {{9, 9, 9, 9, 9, 9}}};
    CHECK_TRUE(checkValue({{0, 0, 0, 0}}, std::get<0>(cfg)));
    CHECK_TRUE(checkValue({{1, 1, 1, 1}}, std::get<1>(cfg)));
    CHECK_TRUE(checkValue({{2, 2, 2, 2}}, std::get<2>(cfg)));
    CHECK_TRUE(checkValue({{9, 9, 9, 9, 9, 9}}, std::get<3>(cfg)));
}
