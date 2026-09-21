#ifndef AXIS_DATA_H
#define AXIS_DATA_H

#include <QtCore/qglobal.h>
#include <QtCore/qstring.h>
#include "qt_compiler.h"

//! It sets data as unsigned integer 32 bits, then we use "rad" and "rad/s" to store values. It gets data in the desired unit.
class Axis_Data
{
public:
    //Axis_Data();
    Axis_Data(uint8_t encoderBitsNumber, double sampleTimePeriod);

    void set_encBitsNumber(uint8_t encoderBitsNumber);
    void set_sampleTime(double sampleTimePeriod);

    //------------------------------

    float convert_position_from_enc(uint32_t data, QString toUnit);
    uint32_t convert_position_to_enc(float data, QString fromUnit);

    float convert_position(float data, QString fromUnit, QString toUnit);
    float convert_velocity(float data, QString fromUnit, QString toUnit);

    //------------------------------

    void set_newEncoderData(uint32_t newData);

    //------------------------------

    void set_positionRef(float data, QString unit);

    float get_position(QString unit);
    float get_positionRef(QString unit);
    float get_positionErr(QString unit);


    void set_positionRef_enc(uint32_t data);

    uint32_t get_position_enc();
    uint32_t get_positionRef_enc();
    uint32_t get_positionErr_enc();


    //------------------------------

    void set_velocityRef(float data, QString unit);

    float get_velocity(QString unit);
    float get_velocityRef(QString unit);
    float get_velocityErr(QString unit);

    //------------------------------

    void clac_errors(void);

protected:

    int32_t enc, enc_ref, enc_err;

    float   pos, pos_ref, pos_err;

    float   spd, spd_ref, spd_err;

    int32_t encData[2];
    float d_encData[2];
    float dd_encData[1];

    //uint8_t encBitsNumber;
    int32_t encoderBitsMask;

    //double sampleTimePeriod;
    double sampleTimeFreq;

    static constexpr  double radMask = 6.283185307179586476925286766559;
    static constexpr  double degMask = 360;
    static constexpr  double minMask = 21600;
    static constexpr  double secMask = 1296000;
    static constexpr  double milMask = 6000;
    static constexpr  double rpmMask = 9.5492965855137201461330258023509;
};

#endif // AXIS_DATA_H
