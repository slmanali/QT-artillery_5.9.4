#include "axis_data.h"

//Axis_Data::Axis_Data()
//{

//}

Axis_Data::Axis_Data(uint8_t encoderBitsNumber, double sampleTimePeriod)
{
    encoderBitsMask = ((uint32_t)1) << encoderBitsNumber;
    sampleTimeFreq = 1 / sampleTimePeriod;

    pos_ref = 0;
    pos = 0;
    pos_err = 0;

    spd_ref = 0;
    spd = 0;
    spd_err = 0;

    enc_ref = 0;
    enc = 0;
    enc_err = 0;

    encData[0] = 0;
    encData[1] = 0;
    d_encData[0] = 0;
    d_encData[1] = 0;
    dd_encData[0] = 0;
}

void Axis_Data::set_encBitsNumber(uint8_t encoderBitsNumber)
{
    //Correct encoder data.
    enc_ref = enc_ref * (((uint32_t)1) << encoderBitsNumber) / encoderBitsMask;

    //Assign the new bit mask.
    encoderBitsMask = ((uint32_t)1) << encoderBitsNumber;
}

void Axis_Data::set_sampleTime(double sampleTimePeriod)
{
    //Correct Speeds Data.
    spd = spd / (sampleTimeFreq * sampleTimePeriod);
    spd_err = spd_ref - spd;

    //Assign new sample time.
    sampleTimeFreq = 1 / sampleTimePeriod;
}


inline float Axis_Data::convert_position_from_enc(uint32_t data, QString toUnit)
{
    float mid;

    if (toUnit == "rad")        mid = data * radMask / encoderBitsMask;
    else if (toUnit == "deg")   mid = data * degMask / encoderBitsMask;
    else if (toUnit == "min")   mid = data * minMask / encoderBitsMask;
    else if (toUnit == "sec")   mid = data * secMask / encoderBitsMask;
    else if (toUnit == "mil")   mid = data * milMask / encoderBitsMask;
    else if (toUnit == "enc")   mid = data;

    return mid;
}

inline uint32_t Axis_Data::convert_position_to_enc(float data, QString fromUnit)
{
    uint32_t mid;

    if (fromUnit == "rad")      mid = data * encoderBitsMask / radMask;
    else if (fromUnit == "deg") mid = data * encoderBitsMask / degMask;
    else if (fromUnit == "min") mid = data * encoderBitsMask / minMask;
    else if (fromUnit == "sec") mid = data * encoderBitsMask / secMask;
    else if (fromUnit == "mil") mid = data * encoderBitsMask / milMask;
    else if (fromUnit == "enc") mid = data;

    return mid;
}

inline float Axis_Data::convert_position(float data, QString fromUnit, QString toUnit)
{
    float mid;

    if (fromUnit == "rad")      mid = data / radMask;
    else if (fromUnit == "deg") mid = data / degMask;
    else if (fromUnit == "min") mid = data / minMask;
    else if (fromUnit == "sec") mid = data / secMask;
    else if (fromUnit == "mil") mid = data / milMask;
    else if (fromUnit == "enc") mid = data / encoderBitsMask;


    if (toUnit == "rad")        mid = mid * radMask;
    else if (toUnit == "deg")   mid = mid * degMask;
    else if (toUnit == "min")   mid = mid * minMask;
    else if (toUnit == "sec")   mid = mid * secMask;
    else if (toUnit == "mil")   mid = mid * milMask;
    else if (toUnit == "enc")   mid = mid * encoderBitsMask;

    return mid;
}

inline float Axis_Data::convert_velocity(float data, QString fromUnit, QString toUnit)
{
    float mid;

    if (fromUnit == "rad/s")      mid = data / radMask;
    else if (fromUnit == "deg/s") mid = data / degMask;
    else if (fromUnit == "min/s") mid = data / minMask;
    else if (fromUnit == "sec/s") mid = data / secMask;
    else if (fromUnit == "mil/s") mid = data / milMask;
    else if (fromUnit == "enc/s") mid = data / encoderBitsMask;
    else if (fromUnit == "rpm")   mid = data / rpmMask;


    if (toUnit == "rad/s")        mid = mid * radMask;
    else if (toUnit == "deg/s")   mid = mid * degMask;
    else if (toUnit == "min/s")   mid = mid * minMask;
    else if (toUnit == "sec/s")   mid = mid * secMask;
    else if (toUnit == "mil/s")   mid = mid * milMask;
    else if (toUnit == "enc/s")   mid = mid * encoderBitsMask;
    else if (toUnit == "rpm")     mid = mid * rpmMask;

    return mid;
}


//------------------------------
void Axis_Data::set_newEncoderData(uint32_t newData)
{
    encData[1] = encData[0];
    encData[0] = newData;

    d_encData[1] = d_encData[0];

    int32_t dif = encData[0] - encData[1];
    int32_t sign = (dif >= 0) ? 1 : -1;

    uint32_t abs = sign * dif;
    if (abs > ((uint32_t)encoderBitsMask >> 1))
        d_encData[0] = (dif - sign * encoderBitsMask) * sampleTimeFreq;
    else
        d_encData[0] = (dif) * sampleTimeFreq;

    dd_encData[0] = (d_encData[0] - d_encData[1]) * sampleTimeFreq;

    //main Data

    enc = encData[0];
    enc_err = enc_ref - enc;

    pos = encData[0] * radMask / encoderBitsMask;
    pos_err = pos_ref - pos;

    spd = d_encData[0] * radMask / encoderBitsMask;
    spd_err = spd_ref - spd;
}




//------------------------------
void Axis_Data::set_positionRef(float data, QString unit)
{
    pos_ref = convert_position(data, unit, "rad");
    enc_ref = convert_position(data, unit, "enc");
    clac_errors();
}
float Axis_Data::get_position(QString unit)
{
    return convert_position(pos, "rad", unit);
}
float Axis_Data::get_positionRef(QString unit)
{
    return convert_position(pos_ref, "rad", unit);
}

float Axis_Data::get_positionErr(QString unit)
{
    return convert_position(pos_err, "rad", unit);
}


//------------------------------


void Axis_Data::set_positionRef_enc(uint32_t data)
{
    enc_ref = data;
    pos_ref = convert_position(data, "enc", "rad");
    clac_errors();
}
uint32_t Axis_Data::get_position_enc()
{
    return enc;
}
uint32_t Axis_Data::get_positionRef_enc()
{
    return enc_ref;
}
uint32_t Axis_Data::get_positionErr_enc()
{
    return enc_err;
}


//------------------------------


void Axis_Data::set_velocityRef(float data, QString unit)
{
    spd_ref = convert_velocity(data, unit, "rad/s");
    clac_errors();
}
float Axis_Data::get_velocity(QString unit)
{
    return convert_velocity(spd, "rad/s", unit);
}
float Axis_Data::get_velocityRef(QString unit)
{
    return convert_velocity(spd_ref, "rad/s", unit);
}
float Axis_Data::get_velocityErr(QString unit)
{
    return convert_velocity(spd_err, "rad/s", unit);
}

//------------------------------

void Axis_Data::clac_errors(void)
{
    enc_err = enc_ref - enc;

    pos_err = pos_ref - pos;

    spd_err = spd_ref - spd;
}

