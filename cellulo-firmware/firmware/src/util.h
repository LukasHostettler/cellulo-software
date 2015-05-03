/**
 * @file util.h
 * @brief Header for various utility functions
 * @author Ayberk Özgür
 * @version 1.0
 * @date 2015-05-03
 */

#ifndef UTIL_H
#define	UTIL_H

/**
 * @brief Busy waits the given amount of time
 * 
 * @param tenNanos Waits this many 10*10^-9 seconds
 */
inline void delayTenNanos(unsigned int tenNanos){
    while(tenNanos > 0) tenNanos--;
}

#endif	/* UTIL_H */

