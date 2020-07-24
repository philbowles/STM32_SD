/**
 * Copyright (c) 2011-2018 Bill Greiman
 * This file is part of the SdFat library for SD memory cards.
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
/**
 * \file
 * \brief configuration definitions
 */
#ifndef SdFatConfig_h
#define SdFatConfig_h
#include <Arduino.h>
#include <stdint.h>
//------------------------------------------------------------------------------
/**
 * Set USE_LONG_FILE_NAMES nonzero to use long file names (LFN).
 * Long File Name are limited to a maximum length of 255 characters.
 *
 * This implementation allows 7-bit characters in the range
 * 0X20 to 0X7E except the following characters are not allowed:
 *
 *  < (less than)
 *  > (greater than)
 *  : (colon)
 *  " (double quote)
 *  / (forward slash)
 *  \ (backslash)
 *  | (vertical bar or pipe)
 *  ? (question mark)
 *  * (asterisk)
 *
 */
#ifndef USE_LONG_FILE_NAMES
  #define USE_LONG_FILE_NAMES 1
#endif
//------------------------------------------------------------------------------
/**
 * If the symbol ENABLE_EXTENDED_TRANSFER_CLASS is nonzero, the class SdFatEX
 * will be defined. If the symbol ENABLE_SOFTWARE_SPI_CLASS is also nonzero,
 * the class SdFatSoftSpiEX will be defined.
 *
 * These classes used extended multi-block SD I/O for better performance.
 * the SPI bus may not be shared with other devices in this mode.
 */
#ifndef ENABLE_EXTENDED_TRANSFER_CLASS
  #define ENABLE_EXTENDED_TRANSFER_CLASS 0
#endif
//------------------------------------------------------------------------------
/**
 * If the symbol USE_STANDARD_SPI_LIBRARY is zero, an optimized custom SPI
 * driver is used if it exists.  If the symbol USE_STANDARD_SPI_LIBRARY is
 * one, the standard Arduino SPI.h library is used with SPI. If the symbol
 * USE_STANDARD_SPI_LIBRARY is two, the SPI port can be selected with the
 * constructors SdFat(SPIClass* spiPort) and SdFatEX(SPIClass* spiPort).
 */
#ifndef USE_STANDARD_SPI_LIBRARY
  #define USE_STANDARD_SPI_LIBRARY 0
#endif
//------------------------------------------------------------------------------
/**
 * If the symbol ENABLE_SOFTWARE_SPI_CLASS is nonzero, the class SdFatSoftSpi
 * will be defined. If ENABLE_EXTENDED_TRANSFER_CLASS is also nonzero,
 * the class SdFatSoftSpiEX will be defined.
 */
#ifndef ENABLE_SOFTWARE_SPI_CLASS
  #define ENABLE_SOFTWARE_SPI_CLASS 0
#endif
//------------------------------------------------------------------------------
/**
 * If CHECK_FLASH_PROGRAMMING is zero, overlap of single sector flash
 * programming and other operations will be allowed for faster write
 * performance.
 *
 * Some cards will not sleep in low power mode unless CHECK_FLASH_PROGRAMMING
 * is non-zero.
 */
#ifndef CHECK_FLASH_PROGRAMMING
  #define CHECK_FLASH_PROGRAMMING 1
#endif
//------------------------------------------------------------------------------
/**
 * Set MAINTAIN_FREE_CLUSTER_COUNT nonzero to keep the count of free clusters
 * updated.  This will increase the speed of the freeClusterCount() call
 * after the first call.  Extra flash will be required.
 */
#ifndef MAINTAIN_FREE_CLUSTER_COUNT
  #define MAINTAIN_FREE_CLUSTER_COUNT 0
#endif
//------------------------------------------------------------------------------
/**
 * To enable SD card CRC checking set USE_SD_CRC nonzero.
 *
 * Set USE_SD_CRC to 1 to use a smaller CRC-CCITT function.  This function
 * is slower for AVR but may be fast for ARM and other processors.
 *
 * Set USE_SD_CRC to 2 to used a larger table driven CRC-CCITT function.  This
 * function is faster for AVR but may be slower for ARM and other processors.
 */
#ifndef USE_SD_CRC
  #define USE_SD_CRC 0
#endif
//------------------------------------------------------------------------------
/**
 * Handle Watchdog Timer for WiFi modules.
 *
 * Yield will be called before accessing the SPI bus if it has been more
 * than WDT_YIELD_TIME_MICROS microseconds since the last yield call by SdFat.
 */
#define WDT_YIELD_TIME_MICROS 0
//------------------------------------------------------------------------------
/**
 * Set FAT12_SUPPORT nonzero to enable use if FAT12 volumes.
 * FAT12 has not been well tested and requires additional flash.
 */
#define FAT12_SUPPORT 0
//------------------------------------------------------------------------------
/**
 * Set DESTRUCTOR_CLOSES_FILE nonzero to close a file in its destructor.
 *
 * Causes use of lots of heap in ARM.
 */
#ifndef DESTRUCTOR_CLOSES_FILE
  #define DESTRUCTOR_CLOSES_FILE 0
#endif
//------------------------------------------------------------------------------
/**
 * Call flush for endl if ENDL_CALLS_FLUSH is nonzero
 *
 * The standard for iostreams is to call flush.  This is very costly for
 * SdFat.  Each call to flush causes 2048 bytes of I/O to the SD.
 *
 * SdFat has a single 512 byte buffer for SD I/O so it must write the current
 * data block to the SD, read the directory block from the SD, update the
 * directory entry, write the directory block to the SD and read the data
 * block back into the buffer.
 *
 * The SD flash memory controller is not designed for this many rewrites
 * so performance may be reduced by more than a factor of 100.
 *
 * If ENDL_CALLS_FLUSH is zero, you must call flush and/or close to force
 * all data to be written to the SD.
 */
#ifndef ENDL_CALLS_FLUSH
  #define ENDL_CALLS_FLUSH 0
#endif
//------------------------------------------------------------------------------
/**
 * Set USE_SEPARATE_FAT_CACHE nonzero to use a second 512 byte cache
 * for FAT table entries.  This improves performance for large writes
 * that are not a multiple of 512 bytes.
 */
#define USE_SEPARATE_FAT_CACHE 1
//------------------------------------------------------------------------------
/**
 * Set USE_MULTI_BLOCK_IO nonzero to use multi-block SD read/write.
 *
 * Don't use mult-block read/write on small AVR boards.
 */
#if defined(RAMEND) && RAMEND < 3000
#define USE_MULTI_BLOCK_IO 0
#else  // RAMEND
#define USE_MULTI_BLOCK_IO 1
#endif  // RAMEND
//-----------------------------------------------------------------------------
#define ENABLE_SDIO_CLASS 0
//------------------------------------------------------------------------------
/**
 * Check if API to select HW SPI port is needed.
 */
#if USE_STANDARD_SPI_LIBRARY > 1 || SD_HAS_CUSTOM_SPI > 1
#define IMPLEMENT_SPI_PORT_SELECTION 1
#else  // IMPLEMENT_SPI_PORT_SELECTION
#define IMPLEMENT_SPI_PORT_SELECTION 0
#endif // IMPLEMENT_SPI_PORT_SELECTION

#endif  // SdFatConfig_h
