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
#ifndef FatApiConstants_h
#define FatApiConstants_h

#include "SdFatConfig.h"
//#if USE_FCNTL_H
#include <fcntl.h>
//#endif

namespace sdfat {
/*
#define O_AT_END O_NONBLOCK  ///< Open at EOF.
typedef int oflag_t;
// Temp fix for particle mesh.
#ifdef O_RDONLY
#undef O_RDONLY
#endif  // O_RDONLY
#ifdef O_RDWR
#undef O_RDWR
#endif  // O_RDWR
#ifdef O_WRONLY
#undef O_WRONLY
#endif  // O_WRONLY
//------------------------------------------------------------------------------
// use the gnu style oflag in open()
const uint8_t O_READ = 0X01;
const uint8_t O_RDONLY = O_READ;
const uint8_t O_WRITE = 0X02;
const uint8_t O_WRONLY = O_WRITE;
const uint8_t O_RDWR = (O_READ | O_WRITE);
const uint8_t O_ACCMODE = (O_READ | O_WRITE);
const uint8_t O_APPEND = 0X04;
const uint8_t O_SYNC = 0X08;
const uint8_t O_TRUNC = 0X10;
const uint8_t O_AT_END = 0X20;
const uint8_t O_CREAT = 0X40;
const uint8_t O_EXCL = 0X80;
#if 0
*/
#define O_RDONLY  0X00
#define O_WRONLY  0X01
#define O_RDWR    0X02
#define O_AT_END  0X04
#define O_APPEND  0X08
#define O_CREAT   0x10
#define O_TRUNC   0x20
#define O_EXCL    0x40
#define O_SYNC    0x80

#define O_ACCMODE (O_RDONLY|O_WRONLY|O_RDWR)
//#endif
typedef uint8_t oflag_t;

#define O_READ    O_RDONLY
#define O_WRITE   O_WRONLY

inline bool isWriteMode(oflag_t oflag) {
  oflag &= O_ACCMODE;
  return oflag == O_WRONLY || oflag == O_RDWR;
}

// FatFile class static and const definitions
// flags for ls()
/** ls() flag for list all files including hidden. */
#define LS_A 1
/** ls() flag to print modify. date */
#define LS_DATE 2
/** ls() flag to print file size. */
#define LS_SIZE 4
/** ls() flag for recursive list of subdirectories */
#define LS_R 8

// flags for timestamp
/** set the file's last access date */
#define T_ACCESS 1
/** set the file's creation date and time */
#define T_CREATE 2
/** Set the file's write date and time */
#define T_WRITE 4

}; // namespace sdfat

#endif  // FatApiConstants_h
