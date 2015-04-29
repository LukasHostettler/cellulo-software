/**
 * @file mt9v034.h
 * @brief Header for MT9V034 image sensor functionality
 * @author Ayberk Özgür
 * @version 1.0
 * @date 2015-04-26
 */

#ifndef MT9V034_H
#define	MT9V034_H

/*
 * I2C slave address (assuming S_CTRL_ADR1, S_CTRL_ADR0 are low)
 */

#define MT9V034_I2C_SLAVE_WRITE_ADDR    0x90
#define MT9V034_I2C_SLAVE_READ_ADDR     0x91

/*
 * Register addresses
 */

#define MT9V034_REG_ADDR_CHIP_VERSION                           0x00
#define MT9V034_REG_ADDR_COLUMN_START                           0x01
#define MT9V034_REG_ADDR_ROW_START_CONTEXT_A                    0x02
#define MT9V034_REG_ADDR_WINDOW_HEIGHT_CONTEXT_A                0x03
#define MT9V034_REG_ADDR_WINDOW_WIDTH_CONTEXT_A                 0x04
#define MT9V034_REG_ADDR_HORIZONTAL_BLANKING_CONTEXT_A          0x05
#define MT9V034_REG_ADDR_VERTICAL_BLANKING_CONTEXT_A            0x06
#define MT9V034_REG_ADDR_CHIP_CONTROL                           0x07
#define MT9V034_REG_ADDR_COARSE_SHUTTER_WIDTH_1_CONTEXT_A       0x08
#define MT9V034_REG_ADDR_COARSE_SHUTTER_WIDTH_2_CONTEXT_A       0x09
#define MT9V034_REG_ADDR_SHUTTER_WIDTH_CTRL_CONTEXT_A           0x0A
#define MT9V034_REG_ADDR_COARSE_TOTAL_SHUTTER_WIDTH_CONTEXT_A   0x0B
#define MT9V034_REG_ADDR_RESET                                  0x0C
#define MT9V034_REG_ADDR_READ_MODE_CONTEXT_A                    0x0D
#define MT9V034_REG_ADDR_READ_MODE_CONTEXT_B                    0x0E
#define MT9V034_REG_ADDR_SENSOR_TYPE_HDR_ENABLE                 0x0F

#define MT9V034_REG_ADDR_LED_OUT_CTRL                           0x1B
#define MT9V034_REG_ADDR_COMPANDING                             0x1C

#define MT9V034_REG_ADDR_VREF_ADC_CONTROL                       0x2C

#define MT9V034_REG_ADDR_V1_CONTEXT_A                           0x31
#define MT9V034_REG_ADDR_V2_CONTEXT_A                           0x32
#define MT9V034_REG_ADDR_V3_CONTEXT_A                           0x33
#define MT9V034_REG_ADDR_V4_CONTEXT_A                           0x34
#define MT9V034_REG_ADDR_ANALOG_GAIN_CONTEXT_A                  0x35
#define MT9V034_REG_ADDR_ANALOG_GAIN_CONTEXT_B                  0x36

#define MT9V034_REG_ADDR_V1_CONTROL_CONTEXT_B                   0x39
#define MT9V034_REG_ADDR_V2_CONTROL_CONTEXT_B                   0x3A
#define MT9V034_REG_ADDR_V3_CONTROL_CONTEXT_B                   0x3B
#define MT9V034_REG_ADDR_V4_CONTROL_CONTEXT_B                   0x3C

#define MT9V034_REG_ADDR_FRAME_DARK_AVERAGE                     0x42

#define MT9V034_REG_ADDR_DARK_AVG_THRESHOLDS                    0x46
#define MT9V034_REG_ADDR_BL_CALIB_CONTROL                       0x47
#define MT9V034_REG_ADDR_BLACK_LEVEL_CALIBRATION_VALUE          0x48

#define MT9V034_REG_ADDR_BL_CALIB_STEP_SIZE                     0x4C

#define MT9V034_REG_ADDR_LOW_NOISE_CORR_CONTROL                 0x70
#define MT9V034_REG_ADDR_LOW_NOISE_CONSTANT                     0x71
#define MT9V034_REG_ADDR_PIXCLK_FV_LV_CTRL                      0x72

#define MT9V034_REG_ADDR_DIGITAL_TEST_PATTERN                   0x7F
#define MT9V034_REG_ADDR_TILE_WEIGHT_GAIN_X0_Y0                 0x80
#define MT9V034_REG_ADDR_TILE_WEIGHT_GAIN_X1_Y0                 0x81
#define MT9V034_REG_ADDR_TILE_WEIGHT_GAIN_X2_Y0                 0x82
#define MT9V034_REG_ADDR_TILE_WEIGHT_GAIN_X3_Y0                 0x83
#define MT9V034_REG_ADDR_TILE_WEIGHT_GAIN_X4_Y0                 0x84
#define MT9V034_REG_ADDR_TILE_WEIGHT_GAIN_X0_Y1                 0x85
#define MT9V034_REG_ADDR_TILE_WEIGHT_GAIN_X1_Y1                 0x86
#define MT9V034_REG_ADDR_TILE_WEIGHT_GAIN_X2_Y1                 0x87
#define MT9V034_REG_ADDR_TILE_WEIGHT_GAIN_X3_Y1                 0x88
#define MT9V034_REG_ADDR_TILE_WEIGHT_GAIN_X4_Y1                 0x89
#define MT9V034_REG_ADDR_TILE_WEIGHT_GAIN_X0_Y2                 0x8A
#define MT9V034_REG_ADDR_TILE_WEIGHT_GAIN_X1_Y2                 0x8B
#define MT9V034_REG_ADDR_TILE_WEIGHT_GAIN_X2_Y2                 0x8C
#define MT9V034_REG_ADDR_TILE_WEIGHT_GAIN_X3_Y2                 0x8D
#define MT9V034_REG_ADDR_TILE_WEIGHT_GAIN_X4_Y2                 0x8E
#define MT9V034_REG_ADDR_TILE_WEIGHT_GAIN_X0_Y3                 0x8F
#define MT9V034_REG_ADDR_TILE_WEIGHT_GAIN_X1_Y3                 0x90
#define MT9V034_REG_ADDR_TILE_WEIGHT_GAIN_X2_Y3                 0x91
#define MT9V034_REG_ADDR_TILE_WEIGHT_GAIN_X3_Y3                 0x92
#define MT9V034_REG_ADDR_TILE_WEIGHT_GAIN_X4_Y3                 0x93
#define MT9V034_REG_ADDR_TILE_WEIGHT_GAIN_X0_Y4                 0x94
#define MT9V034_REG_ADDR_TILE_WEIGHT_GAIN_X1_Y4                 0x95
#define MT9V034_REG_ADDR_TILE_WEIGHT_GAIN_X2_Y4                 0x96
#define MT9V034_REG_ADDR_TILE_WEIGHT_GAIN_X3_Y4                 0x97
#define MT9V034_REG_ADDR_TILE_WEIGHT_GAIN_X4_Y4                 0x98
#define MT9V034_REG_ADDR_TILE_COORD_X_0_5                       0x99
#define MT9V034_REG_ADDR_TILE_COORD_X_1_5                       0x9A
#define MT9V034_REG_ADDR_TILE_COORD_X_2_5                       0x9B
#define MT9V034_REG_ADDR_TILE_COORD_X_3_5                       0x9C
#define MT9V034_REG_ADDR_TILE_COORD_X_4_5                       0x9D
#define MT9V034_REG_ADDR_TILE_COORD_X_5_5                       0x9E
#define MT9V034_REG_ADDR_TILE_COORD_Y_0_5                       0x9F
#define MT9V034_REG_ADDR_TILE_COORD_Y_1_5                       0xA0
#define MT9V034_REG_ADDR_TILE_COORD_Y_2_5                       0xA1
#define MT9V034_REG_ADDR_TILE_COORD_Y_3_5                       0xA2
#define MT9V034_REG_ADDR_TILE_COORD_Y_4_5                       0xA3
#define MT9V034_REG_ADDR_TILE_COORD_Y_5_5                       0xA4
#define MT9V034_REG_ADDR_AEC_AGC_DESIRED_BIN                    0xA5
#define MT9V034_REG_ADDR_AEC_UPDATE_FREQUENCY                   0xA6

#define MT9V034_REG_ADDR_AEC_LPF                                0xA8
#define MT9V034_REG_ADDR_AGC_UPDATE_FREQUENCY                   0xA9
#define MT9V034_REG_ADDR_AGC_LPF                                0xAA
#define MT9V034_REG_ADDR_MAX_ANALOG_GAIN                        0xAB
#define MT9V034_REG_ADDR_AEC_MINIMUM_EXPOSURE                   0xAC
#define MT9V034_REG_ADDR_AEC_MAXIMUM_EXPOSURE                   0xAD
#define MT9V034_REG_ADDR_BIN_DIFFERENCE_THRESHOLD               0xAE
#define MT9V034_REG_ADDR_AEC_AGC_ENABLE_A_B                     0xAF
#define MT9V034_REG_ADDR_AEC_AGC_PIX_COUNT                      0xB0
#define MT9V034_REG_ADDR_LVDS_MASTER_CTRL                       0xB1
#define MT9V034_REG_ADDR_LVDS_SHIFT_CLK_CTRL                    0xB2
#define MT9V034_REG_ADDR_LVDS_DATA_CTRL                         0xB3
#define MT9V034_REG_ADDR_DATA_STREAM_LATENCY                    0xB4
#define MT9V034_REG_ADDR_LVDS_INTERNAL_SYNC                     0xB5
#define MT9V034_REG_ADDR_LVDS_PAYLOAD_CONTROL                   0xB6
#define MT9V034_REG_ADDR_STEREOSCOP_ERROR_CTRL                  0xB7
#define MT9V034_REG_ADDR_STEREOSCOP_ERROR_FLAG                  0xB8
#define MT9V034_REG_ADDR_LVDS_DATA_OUTPUT                       0xB9
#define MT9V034_REG_ADDR_AGC_GAIN_OUTPUT                        0xBA
#define MT9V034_REG_ADDR_AEC_GAIN_OUTPUT                        0xBB
#define MT9V034_REG_ADDR_AGC_AEC_CURRENT_BIN                    0xBC

#define MT9V034_REG_ADDR_INTERLACE_FIELD_BLANK                  0xBF
#define MT9V034_REG_ADDR_MON_MODE_CAPTURE_CTRL                  0xC0

#define MT9V034_REG_ADDR_ANTI_ECLIPSE_CONTROLS                  0xC2

#define MT9V034_REG_ADDR_NTSV_FV_AND_LV_CONTROL                 0xC6
#define MT9V034_REG_ADDR_NTSC_HORIZ_BLACK_CTRL                  0xC7
#define MT9V034_REG_ADDR_NTSC_VERT_BLACK_CTRL                   0xC8
#define MT9V034_REG_ADDR_COLUMN_START_CONTEXT_B                 0xC9
#define MT9V034_REG_ADDR_ROW_START_CONTEXT_B                    0xCA
#define MT9V034_REG_ADDR_WINDOW_HEIGHT_CONTEXT_B                0xCB
#define MT9V034_REG_ADDR_WINDOW_WIDTH_CONTEXT_B                 0xCC
#define MT9V034_REG_ADDR_HORIZONTAL_BLANKING_CONTEXT_B          0xCD
#define MT9V034_REG_ADDR_VERTICAL_BLANKING_CONTEXT_B            0xCE
#define MT9V034_REG_ADDR_COARSE_SW1_CONTEXT_B                   0xCF
#define MT9V034_REG_ADDR_COARSE_SW2_CONTEXT_B                   0xD0
#define MT9V034_REG_ADDR_SHUTTER_WIDTH_CTRL_CONTEXT_B           0xD1
#define MT9V034_REG_ADDR_COARSE_SHUTTER_WIDTH_TOTAL_CONTEXT_B   0xD2
#define MT9V034_REG_ADDR_FINE_SW1_CONTEXT_A                     0xD3
#define MT9V034_REG_ADDR_FINE_SW2_CONTEXT_A                     0xD4
#define MT9V034_REG_ADDR_FINE_SHUTTER_WIDTH_TOTAL_CONTEXT_A     0xD5
#define MT9V034_REG_ADDR_FINE_SW1_CONTEXT_B                     0xD6
#define MT9V034_REG_ADDR_FINE_SW2_CONTEXT_B                     0xD7
#define MT9V034_REG_ADDR_FINE_SHUTTER_WIDTH_TOTAL_CONTEXT_B     0xD8
#define MT9V034_REG_ADDR_MONITOR_MODE                           0xD9

#define MT9V034_REG_ADDR_BYTEWISE_ADDR                          0xF0

#define MT9V034_REG_ADDR_REGISTER_LOCK                          0xFE

#endif	/* MT9V034_H */

