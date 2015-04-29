/**
 * @file i2c.h
 * @brief Header for I2C functionality
 * @author Ayberk Özgür
 * @version 1.0
 * @date 2015-04-26
 */

#ifndef I2C_H
#define	I2C_H

/**
 * @brief Reads multiple bytes from an I2C slave
 *
 * Calculates read address from the write address, assuming the read address
 * is 1 more than the write address
 *
 * @param writeAddr I2C write address of the slave
 * @param registerAddr Address of the slave register to read
 * @param n Number of bytes to read
 * @param buffer Place to read bytes to
 */
void readBytes(unsigned char writeAddr, unsigned char registerAddr, int n, unsigned char* buffer);

/**
 * @brief Writes multiple bytes to an I2C slave
 *
 * @param writeAddr I2C write address of the slave
 * @param registerAddr Address of the slave register to write to
 * @param n Number of bytes to write
 * @param buffer Bytes to write
 */
void writeBytes(unsigned char writeAddr, unsigned char registerAddr, int n, unsigned char* buffer);

#endif	/* I2C_H */

