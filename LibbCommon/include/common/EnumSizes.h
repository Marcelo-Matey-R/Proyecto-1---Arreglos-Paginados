#include <cstdint>
#include <string_view>
#include <iostream>

#pragma once

enum SIZES : size_t {
    VAL_1  = 2048,        // 2 KB
    VAL_2  = 3277,        // 3.20 KB
    VAL_3  = 5243,        // 5.12 KB
    VAL_4  = 8389,        // 8.19 KB
    VAL_5  = 13421,       // 13.11 KB
    VAL_6  = 21475,       // 20.97 KB
    VAL_7  = 34360,       // 33.55 KB
    VAL_8  = 54976,       // 53.69 KB
    VAL_9  = 87961,       // 85.90 KB
    VAL_10 = 140737,      // 137.44 KB
    VAL_11 = 225179,      // 219.90 KB
    VAL_12 = 360287,      // 351.84 KB
    VAL_13 = 576460,      // 562.95 KB
    VAL_14 = 922337,      // 900.72 KB
    VAL_15 = 1475739,     // 1.41 MB
    VAL_16 = 2361183,     // 2.25 MB
    VAL_17 = 3777893,     // 3.60 MB
    VAL_18 = 6044629,     // 5.76 MB
    VAL_19 = 9671406,     // 9.23 MB
    VAL_20 = 15474249,    // 14.75 MB
    VAL_21 = 24758798,    // 23.61 MB
    VAL_22 = 39614077,    // 37.78 MB

    SMALL  = 134217728,   // 128 MB
    VAL_24 = 180000000,    // 171.66 MB
    MEDIUM = 268435456,   // 256 MB
    VAL_26 = 350000000,    // 333.79 MB
    VAL_27 = 420000000,    // 400.54 MB
    VAL_28 = 480000000,    // 457.76 MB
    VAL_29 = 500000000,    // 476.84 MB
    LARGE  = 536870912    // 512 MB
};


SIZES StringToSize(std::string_view str);