/**
 * @file at42qt1070.h
 * @brief Header for AT42QT1070 touch sensor functionality
 * @author Ayberk �zg�r
 * @version 1.0
 * @date 2015-05-03
 */

#ifndef AT42QT1070_H
#define	AT42QT1070_H

#include<xc.h>
#include<GenericTypeDefs.h>

#include"system_config/pic32mz1024ecg064/system_definitions.h"

/*
 * I2C slave write address
 */

#define AT42QT1070_I2C_SLAVE_WRITE_ADDR (0x1B << 1)

/*
 * Register addresses
 */

#define AT42QT1070_REG_ADDR_CHIP_ID             0
#define AT42QT1070_REG_ADDR_FIRMWARE_VERSION    1
#define AT42QT1070_REG_ADDR_DETECTION_STATUS    2
#define AT42QT1070_REG_ADDR_KEY_STATUS          3
#define AT42QT1070_REG_ADDR_KEY_SINGAL_0        4
#define AT42QT1070_REG_ADDR_KEY_SINGAL_1        6
#define AT42QT1070_REG_ADDR_KEY_SIGNAL_2        8
#define AT42QT1070_REG_ADDR_KEY_SIGNAL_3        10
#define AT42QT1070_REG_ADDR_KEY_SIGNAL_4        12
#define AT42QT1070_REG_ADDR_KEY_SIGNAL_5        14
#define AT42QT1070_REG_ADDR_KEY_SIGNAL_6        16
#define AT42QT1070_REG_ADDR_REFERENCE_DATA_0    18
#define AT42QT1070_REG_ADDR_REFERENCE_DATA_1    20
#define AT42QT1070_REG_ADDR_REFERENCE_DATA_2    22
#define AT42QT1070_REG_ADDR_REFERENCE_DATA_3    24
#define AT42QT1070_REG_ADDR_REFERENCE_DATA_4    26
#define AT42QT1070_REG_ADDR_REFERENCE_DATA_5    28
#define AT42QT1070_REG_ADDR_REFERENCE_DATA_6    30
#define AT42QT1070_REG_ADDR_NTHR_KEY_0          32
#define AT42QT1070_REG_ADDR_NTHR_KEY_1          33
#define AT42QT1070_REG_ADDR_NTHR_KEY_2          34
#define AT42QT1070_REG_ADDR_NTHR_KEY_3          35
#define AT42QT1070_REG_ADDR_NTHR_KEY_4          36
#define AT42QT1070_REG_ADDR_NTHR_KEY_5          37
#define AT42QT1070_REG_ADDR_NTHR_KEY_6          38
#define AT42QT1070_REG_ADDR_AVE_AKS_KEY_0       39
#define AT42QT1070_REG_ADDR_AVE_AKS_KEY_1       40
#define AT42QT1070_REG_ADDR_AVE_AKS_KEY_2       41
#define AT42QT1070_REG_ADDR_AVE_AKS_KEY_3       42
#define AT42QT1070_REG_ADDR_AVE_AKS_KEY_4       43
#define AT42QT1070_REG_ADDR_AVE_AKS_KEY_5       44
#define AT42QT1070_REG_ADDR_AVE_AKS_KEY_6       45
#define AT42QT1070_REG_ADDR_DI_KEY_0            46
#define AT42QT1070_REG_ADDR_DI_KEY_1            47
#define AT42QT1070_REG_ADDR_DI_KEY_2            48
#define AT42QT1070_REG_ADDR_DI_KEY_3            49
#define AT42QT1070_REG_ADDR_DI_KEY_4            50
#define AT42QT1070_REG_ADDR_DI_KEY_5            51
#define AT42QT1070_REG_ADDR_DI_KEY_6            52
#define AT42QT1070_REG_ADDR_FO_MO_GUARD_NO      53
#define AT42QT1070_REG_ADDR_LP                  54
#define AT42QT1070_REG_ADDR_MAX_ON_DURATION     55
#define AT42QT1070_REG_ADDR_CALIBRATE           56
#define AT42QT1070_REG_ADDR_RESET_BAR           57

/**
 * @brief Initializes the device functionality
 */
void AT42QT1070Init();

/**
 * @brief Resets the device
 */
void AT42QT1070Reset();

/**
 * @brief Sets Adjacent Key Suppression group for given key
 * 
 * @param key 0, 1, 2, 3, 4, 5 or 6
 * @param group 1, 2 or 3; 0 disables AKS
 */
void AT42QT1070SetAKS(unsigned char key, unsigned char group);

/**
 * @brief Sets averaging for given key
 *
 * @param key 0, 1, 2, 3, 4, 5 or 6
 * @param ave Number of samples to average; 0, 1, 2, 4, 8, 16 or 32
 */
void AT42QT1070SetAVE(unsigned char key, unsigned char ave);

/**
 * @brief Disables given key
 *
 * @param key 0, 1, 2, 3, 4, 5 or 6
 */
void AT42QT1070DisableKey(unsigned char key);

/**
 * @brief Sets the key sampling period
 *
 * @param eightMillis Sampling period is this many 8 ms
 */
void AT42QT1070SetSamplePeriod(unsigned char eightMillis);

/**
 * @brief Gets the key states, whether pressed or not
 *
 * @param keys Output buffer
 */
void AT42QT1070GetKeyStates(bool* keys);

#endif	/* AT42QT1070_H */

