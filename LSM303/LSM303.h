#ifndef LSM303_h
#define LSM303_h

#include <Arduino.h> // for byte data type

// device types

#define LSM303DLH_DEVICE     0
#define LSM303DLM_DEVICE     1
#define LSM303DLHC_DEVICE    2
#define LSM303D_DEVICE       3
#define LSM303_DEVICE_AUTO 255


// SA0 (SA0_A) states

#define LSM303_SA0_LOW  0
#define LSM303_SA0_HIGH 1
#define LSM303_SA0_AUTO 2


// register addresses

#define LSM303_TEMP_OUT_L        0x05 // D
#define LSM303_TEMP_OUT_H        0x06 // D

#define LSM303_STATUS_M          0x07 // D

#define LSM303_INT_CTRL_M        0x12 // D
#define LSM303_INT_SRC_M         0x13 // D
#define LSM303_INT_THS_L_M       0x14 // D
#define LSM303_INT_THS_H_M       0x15 // D

#define LSM303_OFFSET_X_L_M      0x16 // D
#define LSM303_OFFSET_X_H_M      0x17 // D
#define LSM303_OFFSET_Y_L_M      0x18 // D
#define LSM303_OFFSET_Y_H_M      0x19 // D
#define LSM303_OFFSET_Z_L_M      0x1A // D
#define LSM303_OFFSET_Z_H_M      0x1B // D
#define LSM303_REFERENCE_X       0x1C // D
#define LSM303_REFERENCE_Y       0x1D // D
#define LSM303_REFERENCE_Z       0x1E // D

#define LSM303_CTRL0             0x1F // D
#define LSM303_CTRL1             0x20 // D
#define LSM303_CTRL_REG1_A       0x20 // DLH, DLM, DLHC
#define LSM303_CTRL2             0x21 // D
#define LSM303_CTRL_REG2_A       0x21 // DLH, DLM, DLHC
#define LSM303_CTRL3             0x22 // D
#define LSM303_CTRL_REG3_A       0x22 // DLH, DLM, DLHC
#define LSM303_CTRL4             0x23 // D
#define LSM303_CTRL_REG4_A       0x23 // DLH, DLM, DLHC
#define LSM303_CTRL5             0x24 // D
#define LSM303_CTRL_REG5_A       0x24 // DLH, DLM, DLHC
#define LSM303_CTRL6             0x25 // D
#define LSM303_CTRL_REG6_A       0x25 // DLHC
#define LSM303_HP_FILTER_RESET_A 0x25 // DLH, DLM
#define LSM303_CTRL7             0x26 // D
#define LSM303_REFERENCE_A       0x26 // DLH, DLM, DLHC
#define LSM303_STATUS_A          0x27 // D
#define LSM303_STATUS_REG_A      0x27 // DLH, DLM, DLHC

#define LSM303_OUT_X_L_A         0x28
#define LSM303_OUT_X_H_A         0x29
#define LSM303_OUT_Y_L_A         0x2A
#define LSM303_OUT_Y_H_A         0x2B
#define LSM303_OUT_Z_L_A         0x2C
#define LSM303_OUT_Z_H_A         0x2D

#define LSM303_FIFO_CTRL         0x2E // D
#define LSM303_FIFO_CTRL_REG_A   0x2E // DLHC
#define LSM303_FIFO_SRC          0x2F // D
#define LSM303_FIFO_SRC_REG_A    0x2F // DLHC

#define LSM303_IG_CFG1           0x30 // D
#define LSM303_INT1_CFG_A        0x30 // DLH, DLM, DLHC
#define LSM303_IG_SRC1           0x31 // D
#define LSM303_INT1_SRC_A        0x31 // DLH, DLM, DLHC
#define LSM303_IG_THS1           0x32 // D
#define LSM303_INT1_THS_A        0x32 // DLH, DLM, DLHC
#define LSM303_IG_DUR1           0x33 // D
#define LSM303_INT1_DURATION_A   0x33 // DLH, DLM, DLHC
#define LSM303_IG_CFG2           0x34 // D
#define LSM303_INT2_CFG_A        0x34 // DLH, DLM, DLHC
#define LSM303_IG_SRC2           0x35 // D
#define LSM303_INT2_SRC_A        0x35 // DLH, DLM, DLHC
#define LSM303_IG_THS2           0x36 // D
#define LSM303_INT2_THS_A        0x36 // DLH, DLM, DLHC
#define LSM303_IG_DUR2           0x37 // D
#define LSM303_INT2_DURATION_A   0x37 // DLH, DLM, DLHC

#define LSM303_CLICK_CFG         0x38 // D
#define LSM303_CLICK_CFG_A       0x38 // DLHC
#define LSM303_CLICK_SRC         0x39 // D
#define LSM303_CLICK_SRC_A       0x39 // DLHC
#define LSM303_CLICK_THS         0x3A // D
#define LSM303_CLICK_THS_A       0x3A // DLHC
#define LSM303_TIME_LIMIT        0x3B // D
#define LSM303_TIME_LIMIT_A      0x3B // DLHC
#define LSM303_TIME_LATENCY      0x3C // D
#define LSM303_TIME_LATENCY_A    0x3C // DLHC
#define LSM303_TIME_WINDOW       0x3D // D
#define LSM303_TIME_WINDOW_A     0x3D // DLHC

#define LSM303_ACT_THS           0x3E
#define LSM303_ACT_DUR           0x3F

#define LSM303_CRA_REG_M         0x00
#define LSM303_CRB_REG_M         0x01
#define LSM303_MR_REG_M          0x02

#define LSM303_SR_REG_M          0x09
#define LSM303_IRA_REG_M         0x0A
#define LSM303_IRB_REG_M         0x0B
#define LSM303_IRC_REG_M         0x0C

#define LSM303_WHO_AM_I_M        0x0F // DLM
#define LSM303_WHO_AM_I          0x0F // D

#define LSM303_TEMP_OUT_H_M      0x31 // DLHC
#define LSM303_TEMP_OUT_L_M      0x32 // DLHC


// dummy addresses for registers in different locations on different devices; the library translates these based on device type

#define LSM303_OUT_X_H_M           -1
#define LSM303_OUT_X_L_M           -2
#define LSM303_OUT_Y_H_M           -3
#define LSM303_OUT_Y_L_M           -4
#define LSM303_OUT_Z_H_M           -5
#define LSM303_OUT_Z_L_M           -6


// device-specific register addresses

#define LSM303DLH_OUT_X_H_M      0x03
#define LSM303DLH_OUT_X_L_M      0x04
#define LSM303DLH_OUT_Y_H_M      0x05
#define LSM303DLH_OUT_Y_L_M      0x06
#define LSM303DLH_OUT_Z_H_M      0x07
#define LSM303DLH_OUT_Z_L_M      0x08

#define LSM303DLM_OUT_X_H_M      0x03
#define LSM303DLM_OUT_X_L_M      0x04
#define LSM303DLM_OUT_Z_H_M      0x05
#define LSM303DLM_OUT_Z_L_M      0x06
#define LSM303DLM_OUT_Y_H_M      0x07
#define LSM303DLM_OUT_Y_L_M      0x08

#define LSM303DLHC_OUT_X_H_M     0x03
#define LSM303DLHC_OUT_X_L_M     0x04
#define LSM303DLHC_OUT_Z_H_M     0x05
#define LSM303DLHC_OUT_Z_L_M     0x06
#define LSM303DLHC_OUT_Y_H_M     0x07
#define LSM303DLHC_OUT_Y_L_M     0x08

#define LSM303D_OUT_X_L_M        0x08
#define LSM303D_OUT_X_H_M        0x09
#define LSM303D_OUT_Y_L_M        0x0A
#define LSM303D_OUT_Y_H_M        0x0B
#define LSM303D_OUT_Z_L_M        0x0C
#define LSM303D_OUT_Z_H_M        0x0D


class LSM303
{
  public:
    typedef struct vector
    {
      float x, y, z;
    } vector;

    vector a; // accelerometer readings
    vector m; // magnetometer readings
    vector m_max; // maximum magnetometer values, used for calibration
    vector m_min; // minimum magnetometer values, used for calibration

    byte last_status; // status of last I2C transmission
    
    // HEX  = BIN          RANGE    GAIN X/Y/Z        GAIN Z
    //                               DLH (DLM/DLHC)    DLH (DLM/DLHC)
    // 0x20 = 0b00100000   ±1.3     1055 (1100)        950 (980) (default)
    // 0x40 = 0b01000000   ±1.9      795  (855)        710 (760)
    // 0x60 = 0b01100000   ±2.5      635  (670)        570 (600)
    // 0x80 = 0b10000000   ±4.0      430  (450)        385 (400)
    // 0xA0 = 0b10100000   ±4.7      375  (400)        335 (355)
    // 0xC0 = 0b11000000   ±5.6      320  (330)        285 (295)
    // 0xE0 = 0b11100000   ±8.1      230  (230)        205 (205)
    enum magGain { magGain_13 = 0x20, magGain_19 = 0x40, magGain_25 = 0x60, magGain_40 = 0x80,
                   magGain_47 = 0xA0, magGain_56 = 0xC0, magGain_81 = 0xE0 };

    LSM303(void);
    
    void init(byte device = LSM303_DEVICE_AUTO, byte sa0_a = LSM303_SA0_AUTO);
    byte getDeviceType(void) { return _device; }
    
    void enableDefault(void);
    
    void writeAccReg(byte reg, byte value);
    byte readAccReg(byte reg);
    void writeMagReg(byte reg, byte value);
    byte readMagReg(int reg);

    void setMagGain(magGain value);
    
    void readAcc(void);
    void readMag(void);
    void read(void);

    void setTimeout(unsigned int timeout);
    unsigned int getTimeout(void);
    bool timeoutOccurred(void);
    
    int heading(void);
    int heading(vector from);
    
    // vector functions
    static void vector_cross(const vector *a, const vector *b, vector *out);
    static float vector_dot(const vector *a,const vector *b);
    static void vector_normalize(vector *a);
    
  private:
    byte _device; // chip type (DLH, DLM, or DLHC)
    byte acc_address;
    byte mag_address;
    unsigned int io_timeout;
    bool did_timeout;
    
    byte detectSA0_A(void);
    byte detectLSM303D(void);
};

#endif



