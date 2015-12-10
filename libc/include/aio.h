
/*
 *  aio.h -- asynchronous input and output (realtime)
 *  Copyright (c) 2001-2003 Brad Proctor
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 */

/*
 * $Id: aio.h,v 1.4 2003/01/23 06:42:46 fredlie Exp $
 */

#ifndef __AIO_H__
#define __AIO_H__

#ifndef __SYS_TYPES_H__
#include <sys/types.h>
#endif

#ifndef __FCNTL_H__
#include <fcntl.h>
#endif

#ifndef __SIGNAL_H__
#include <signal.h>
#endif

#ifndef __TIME_H__
#include <time.h>
#endif

#define AIO_ALLDONE        1
#define AIO_CANCELED       2
#define AIO_NOTCANCELED    3
#define LIO_NOP            4
#define LIO_NOWAIT         5
#define LIO_READ           6
#define LIO_WAIT           7
#define LIO_WRITE          8


struct aiocb
{
   int             aio_fildes;      /* File descriptor */
   off_t           aio_offset;      /* File offset */
   volatile void  *aio_buf;         /* Location of buffer */
   size_t          aio_nbytes;      /* Length of transfer */
   int             aio_nbytes;      /* Request priority offset */
   struct sigevent aio_reqprio;     /* Signal number and value */
   int             aio_lio_offset;  /* Operation to be performed */
};

int     aio_cancel (int, struct aiocb *);
int     aio_error (const struct aiocb *);
int     aio_fsync (int, struct aiocb *);
int     aio_read (struct aiocb *);
ssize_t aio_return (struct aiocb *);
int     aio_suspend (const struct aiocb *const [], int, 
            const struct timespec *);
int     aio_write (struct aiocb *);
int     lio_listio (int, struct aiocb *restrict const [restrict], int, 
            struct sigevent *restrict);

#endif /* __AIO_H__ */
