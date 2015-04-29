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
 * @param slaveAddr Address of the slave to read from
 * @param registerAddr Address of the slave register to read
 * @param n Number of bytes to read
 * @param buffer Place to read bytes to
 */
void readBytes(unsigned char slaveAddr, int n, unsigned char* buffer);

#endif	/* I2C_H */

