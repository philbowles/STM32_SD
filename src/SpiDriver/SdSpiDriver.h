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
 * \brief SpiDriver classes
 */
#ifndef SdSpiDriver_h
#define SdSpiDriver_h
#include <Arduino.h>
#include "SPI.h"
#include "SdSpiBaseDriver.h"
#include "SdFatConfig.h"
//------------------------------------------------------------------------------
/** SDCARD_SPI is defined if board has built-in SD card socket */
#ifndef SDCARD_SPI
#define SDCARD_SPI SPI
#endif  // SDCARD_SPI

namespace sdfat {

//------------------------------------------------------------------------------
/**
 * \class SdSpiLibDriver
 * \brief SdSpiLibDriver - use standard SPI library.
 */
#if ENABLE_SOFTWARE_SPI_CLASS
class SdSpiLibDriver : public SdSpiBaseDriver {
#else  // ENABLE_SOFTWARE_SPI_CLASS
class SdSpiLibDriver {
#endif  // ENABLE_SOFTWARE_SPI_CLASS
 public:
#if IMPLEMENT_SPI_PORT_SELECTION
  /** Activate SPI hardware. */
  void activate() {
    m_spi->beginTransaction(m_spiSettings);
  }
  /** Deactivate SPI hardware. */
  void deactivate() {
    m_spi->endTransaction();
  }
  /** Initialize the SPI bus.
   *
   * \param[in] csPin SD card chip select pin.
   */
  void begin(uint8_t csPin) {
    m_csPin = csPin;
    digitalWrite(csPin, HIGH);
    pinMode(csPin, OUTPUT);
    m_spi->begin();
  }
  /** Receive a byte.
   *
   * \return The byte.
   */
  uint8_t receive() {
    return m_spi->transfer( 0XFF);
  }
  /** Receive multiple bytes.
  *
  * \param[out] buf Buffer to receive the data.
  * \param[in] n Number of bytes to receive.
  *
  * \return Zero for no error or nonzero error code.
  */
  uint8_t receive(uint8_t* buf, size_t n) {
    for (size_t i = 0; i < n; i++) {
      buf[i] = m_spi->transfer(0XFF);
    }
    return 0;
  }
  /** Send a byte.
   *
   * \param[in] data Byte to send
   */
  void send(uint8_t data) {
    m_spi->transfer(data);
  }
  /** Send multiple bytes.
   *
   * \param[in] buf Buffer for data to be sent.
   * \param[in] n Number of bytes to send.
   */
  void send(const uint8_t* buf, size_t n) {
    for (size_t i = 0; i < n; i++) {
      m_spi->transfer(buf[i]);
    }
  }
#else  // IMPLEMENT_SPI_PORT_SELECTION
  /** Activate SPI hardware. */
  void activate() {
    SDCARD_SPI.beginTransaction(m_spiSettings);
  }
  /** Deactivate SPI hardware. */
  void deactivate() {
    SDCARD_SPI.endTransaction();
  }
  /** Initialize the SPI bus.
   *
   * \param[in] csPin SD card chip select pin.
   */
  void begin(uint8_t csPin) {
    m_csPin = csPin;
    digitalWrite(csPin, HIGH);
    pinMode(csPin, OUTPUT);
    SDCARD_SPI.begin();
  }
  /** Receive a byte.
   *
   * \return The byte.
   */
  uint8_t receive() {
    return SDCARD_SPI.transfer( 0XFF);
  }
  /** Receive multiple bytes.
  *
  * \param[out] buf Buffer to receive the data.
  * \param[in] n Number of bytes to receive.
  *
  * \return Zero for no error or nonzero error code.
  */
  uint8_t receive(uint8_t* buf, size_t n) {
    for (size_t i = 0; i < n; i++) {
      buf[i] = SDCARD_SPI.transfer(0XFF);
    }
    return 0;
  }
  /** Send a byte.
   *
   * \param[in] data Byte to send
   */
  void send(uint8_t data) {
    SDCARD_SPI.transfer(data);
  }
  /** Send multiple bytes.
   *
   * \param[in] buf Buffer for data to be sent.
   * \param[in] n Number of bytes to send.
   */
  void send(const uint8_t* buf, size_t n) {
    for (size_t i = 0; i < n; i++) {
      SDCARD_SPI.transfer(buf[i]);
    }
  }
#endif  // IMPLEMENT_SPI_PORT_SELECTION
  /** Set CS low. */
  void select() {
    digitalWrite(m_csPin, LOW);
  }
  /** Save SPISettings.
   *
   * \param[in] spiSettings SPI speed, mode, and byte order.
   */
  void setSpiSettings(SPISettings spiSettings) {
    m_spiSettings = spiSettings;
  }
  /** Set CS high. */
  void unselect() {
    digitalWrite(m_csPin, HIGH);
  }
#if IMPLEMENT_SPI_PORT_SELECTION || defined(DOXYGEN)
  /** Set SPI port.
   * \param[in] spiPort Hardware SPI port.
   */
  void setPort(SPIClass* spiPort) {
    m_spi = spiPort ? spiPort : &SDCARD_SPI;
  }
 private:
  SPIClass* m_spi;
#else   // IMPLEMENT_SPI_PORT_SELECTION
 private:
#endif  // IMPLEMENT_SPI_PORT_SELECTION
  SPISettings m_spiSettings;
  uint8_t m_csPin;
};
//------------------------------------------------------------------------------
/**
 * \class SdSpiAltDriver
 * \brief Optimized SPI class for access to SD and SDHC flash memory cards.
 */
#if ENABLE_SOFTWARE_SPI_CLASS
class SdSpiAltDriver : public SdSpiBaseDriver {
#else  // ENABLE_SOFTWARE_SPI_CLASS
class SdSpiAltDriver {
#endif  // ENABLE_SOFTWARE_SPI_CLASS
 public:
  /** Activate SPI hardware. */
  void activate();
  /** Deactivate SPI hardware. */
  void deactivate();
  /** Initialize the SPI bus.
   *
   * \param[in] csPin SD card chip select pin.
   */
  void begin(uint8_t csPin);
  /** Receive a byte.
   *
   * \return The byte.
   */
  uint8_t receive();
  /** Receive multiple bytes.
  *
  * \param[out] buf Buffer to receive the data.
  * \param[in] n Number of bytes to receive.
  *
  * \return Zero for no error or nonzero error code.
  */
  uint8_t receive(uint8_t* buf, size_t n);
  /** Send a byte.
   *
   * \param[in] data Byte to send
   */
  void send(uint8_t data);
  /** Send multiple bytes.
   *
   * \param[in] buf Buffer for data to be sent.
   * \param[in] n Number of bytes to send.
   */
  void send(const uint8_t* buf, size_t n);
  /** Set CS low. */
  void select() {
     digitalWrite(m_csPin, LOW);
  }
  /** Save SPISettings.
   *
   * \param[in] spiSettings SPI speed, mode, and byte order.
   */
  void setSpiSettings(SPISettings spiSettings) {
    m_spiSettings = spiSettings;
  }
  /** Set CS high. */
  void unselect() {
    digitalWrite(m_csPin, HIGH);
  }
#if IMPLEMENT_SPI_PORT_SELECTION || defined(DOXYGEN)
  /** Set SPI port number.
   * \param[in] spiPort Hardware SPI port.
   */
  void setPort(SPIClass* spiPort) {
    m_spi = spiPort ? spiPort : &SDCARD_SPI;
  }
 private:
  SPIClass* m_spi;
#else   // IMPLEMENT_SPI_PORT_SELECTION
 private:
#endif  // IMPLEMENT_SPI_PORT_SELECTION
  SPISettings m_spiSettings;
  uint8_t m_csPin;
};

}; // namespace sdfat

//------------------------------------------------------------------------------

namespace sdfat {

//------------------------------------------------------------------------------
// Choose SPI driver for SdFat and SdFatEX classes.
#if USE_STANDARD_SPI_LIBRARY || !SD_HAS_CUSTOM_SPI
/** SdFat uses Arduino library SPI. */
typedef SdSpiLibDriver SdFatSpiDriver;
#else  // USE_STANDARD_SPI_LIBRARY || !SD_HAS_CUSTOM_SPI
/** SdFat uses custom fast SPI. */
typedef SdSpiAltDriver SdFatSpiDriver;
#endif  // USE_STANDARD_SPI_LIBRARY || !SD_HAS_CUSTOM_SPI

/** typedef for for SdSpiCard class. */
#if ENABLE_SOFTWARE_SPI_CLASS
// Need virtual driver.
typedef SdSpiBaseDriver SdSpiDriver;
#else  // ENABLE_SOFTWARE_SPI_CLASS
// Don't need virtual driver.
typedef SdFatSpiDriver SdSpiDriver;
#endif  // ENABLE_SOFTWARE_SPI_CLASS

}; // namespace sdfat

#endif  // SdSpiDriver_h
