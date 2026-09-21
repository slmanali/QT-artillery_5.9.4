#ifndef OPTOLOAD_CONSTANTS
#define OPTOLOAD_CONSTANTS

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

////! Board ID
//uint16_t optoload_bid;

////! Instant ID, it should change with every camera changed
//uint16_t optoload_iid;


//! check if "value in [a, b]" so we use "center = (a + b) / 2" and "radius = |a - b|"
#define in_range(value, center, radius) ((value >= (center - radius)) && (value <= (center + radius)))


//! Table for standard zoom value according to SONY manual, note the shift in index (for X18 = index in table is 17)
uint16_t g_zoomTable[] = {0X0000, 0X166F, 0X1FF0, 0X257D, // X1,  X2,  X3,  X4
                          0X2940, 0X2C02, 0X2E2B, 0X2FEE, // X5,  X6,  X7,  X8
                          0X316A, 0X32B2, 0X33D4, 0X34D9, // X9,  X10, X11, X12
                          0X35C8, 0X36A4, 0X3773, 0X3836, // X13, X14, X15, X16
                          0X38F0, 0X39A0, 0X3A49, 0X3AE8, // X17, X18, X19, X20
                          0X3B7F, 0X3C0C, 0X3C8E, 0X3D06, // X21, X22, X23, X24
                          0X3D73, 0X3DD4, 0X3E2C, 0X3E7C, // X25, X26, X27, X28
                          0X3EC2, 0X3F00, 0X3F38, 0X3F68, // X29, X30, X31, X32
                          0X3F94, 0X3FBD, 0X3FDF, 0X4000};// X33, X34, X35, X36


static uint8_t zoomTableSize = 36;
static uint8_t zoomTableRadius = 3;

static inline uint16_t get_zoomValue(uint8_t zoomX)
{
    return g_zoomTable[zoomX];
}

// get the X zoom value for known zoom value according to zoomTable, return -1 if not found
static inline int16_t get_zoomX(uint16_t zoomValue)
{
    for (uint8_t i = 0; i < zoomTableSize; i++)
    {
        if (in_range(zoomValue, g_zoomTable[i], zoomTableRadius))
        {
            return i;
        }
    }

    // not found
    return -1;
}

// get the nearest X zoom value for known zoom value according to zoomTable, return -1 if not found
static inline int16_t get_zoomX_nearest(uint16_t zoomValue)
{
    if (zoomValue <= g_zoomTable[0])
    {
        return 0;
    }
    else if ((zoomValue >= g_zoomTable[zoomTableSize - 1]))
    {
        return zoomTableSize - 1;
    }
    else
    {
        for (uint8_t i = 1; i < zoomTableSize; i++)
        {
            if (in_range(zoomValue, g_zoomTable[i], zoomTableRadius))
            {
                return i;
            }
            else if (zoomValue < g_zoomTable[i])//in_range(zoomValue, g_zoomTable[i], zoomTableRadius))
            {
                //zoomValue in [zoomTableSize(i-1), zoomTableSize(i)]
                if ((zoomValue - g_zoomTable[i-1]) > (g_zoomTable[i] - zoomValue))
                {
                    return (i-1);
                }
                else
                {
                    return i;
                }
            }
        }
    }
    // not found
    return -1;
}
#endif // OPTOLOAD_CONSTANTS

