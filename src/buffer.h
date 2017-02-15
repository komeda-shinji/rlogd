/*
 * Copyright (c) 2014,2015 KLab Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
#ifndef RLOGD_BUFFER_H
#define RLOGD_BUFFER_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <stdio.h>
#include <stdint.h>
#include <sys/time.h>
#include <pthread.h>
#include "protocol.h"

#define POSITION_FILE_NAME "pos.dat"
#define BUFFER_FILE_NAME "buffer"

/*
   r/w: read/write
   b/c: buffer/chunk
*/
struct position {
    uint32_t rb;
    uint32_t rc;
    uint32_t wb;
    uint32_t wc;
};

struct buffer {
    char *base;
    int dirfd;
    struct position *cursor;
    off_t size;
    int fd;
    size_t len;
    struct timeval tstamp;
    pthread_mutex_t mutex;
};

extern int
buffer_init (struct buffer *buffer, const char *base);
extern int
buffer_create (struct buffer *buffer);
extern int
buffer_flush (struct buffer *buffer);
extern int
buffer_write (struct buffer *buffer, const char *tag, size_t tag_len, struct entry *entries, size_t len);
extern void
buffer_terminate (struct buffer *buffer);

#endif
