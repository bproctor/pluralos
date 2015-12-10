
/*
 *  errno.h
 *  Copyright (C) 1999-2003 Brad Proctor
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
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/*
 * $Id: errno.h,v 1.4 2003/01/23 06:42:46 fredlie Exp $
 */

#ifndef  __ERRNO_H__
#define  __ERRNO_H__


#define EOK             0        /* No error */
#define E2BIG           1        /* Argument list too long */
#define EACCES          2        /* Permission denied */
#define EADDRINUSE      3        /* Address in use */
#define EADDRNOTAVAIL   4        /* Address not available */
#define EAFNOSUPPORT    5        /* Address family not supported */
#define EAGAIN          6        /* Resource unavailable, try again */
#define EALREADY        7        /* Connection already in progress */
#define EBADF           8        /* Bad file descriptor */
#define EBADMSG         9        /* Bad message */
#define EBUSY           10       /* Device or resource busy */
#define ECANCELED       11       /* Operation canceled */
#define ECHILD          12       /* No child processes */
#define ECONNABORTED    13       /* Connection aborted */
#define ECONNREFUSED    14       /* Connection refused */
#define ECONNRESET      15       /* Connection reset */
#define EDEADLK         16       /* Resource deadlock would occur */
#define EDESTADDRREQ    17       /* Destination address required */
#define EDOM            18       /* Math argument out of domain of function */
#define EDQUOT          19       /* Reserved */
#define EEXIST          20       /* File exists */
#define EFAULT          21       /* Bad address */
#define EFBIG           22       /* File too large */
#define EHOSTUNREACH    23       /* Host unreachable */
#define EIDRM           24       /* Identifier removed */
#define EILSEQ          25       /* Illegal byte sequence */
#define EINPROGESS      26       /* Operation in progress */
#define EINTR           27       /* Interrupted function */
#define EINVAL          28       /* Invalid argument */
#define EIO             29       /* I/O error */
#define EISCONN         30       /* Socket is connected */
#define EISDIR          31       /* Is a directory */
#define ELOOP           32       /* Too many levels of symbolic links */
#define EMFILE          33       /* Too many open files */
#define EMLINK          34       /* Too many links */
#define EMSGSIZE        35       /* Message too large */
#define EMULTIHOP       36       /* Reserved */
#define ENAMETOOLONG    37       /* Name to long */
#define ENETDOWN        38       /* Network is down */
#define ENETUNREACH     39       /* Network is unreachable */
#define ENFILE          40       /* Too many files open in system */
#define ENOBUFS         41       /* No buffer space available */
#define ENODATA         42       /* No msg avail on stream head read queue */
#define ENODEV          43       /* No such device */
#define ENOENT          44       /* No such file or directory */     
#define ENOEXEC         45       /* Executable file format error */
#define ENOLCK          46       /* No locks available */
#define ENOLINK         47       /* Reserved */
#define ENOMEM          48       /* No memory left */
#define ENOMSG          49       /* No message of the designed type */
#define ENOPROTOOPT     50       /* Protocol not available */
#define ENOSPC          51       /* No space left on device */
#define ENOSR           52       /* No stream resources */
#define ENOSTR          53       /* Not a stream */
#define ENOSYS          54       /* Function not supported */
#define ENOTCONN        55       /* The socket is not connected */
#define ENOTDIR         56       /* Not a directory */
#define ENOTEMPTY       57       /* Directory not empty */
#define ENOTSOCK        58       /* Not a socket */
#define ENOTSUP         59       /* Not supported */
#define ENOTTY          60       /* Inappropriate I/O control operation */
#define ENXIO           61       /* No such device or address */
#define EOPNOTSUPP      62       /* Operation not supported */
#define EOVERFLOW       63       /* Too large to be stored in data type */
#define EPERM           64       /* Operation not permitted */
#define EPIPE           65       /* Broken pipe */
#define EPROTO          66       /* Protocol error */
#define EPROTONOSUPPORT 67       /* Protocol not supported */
#define EPROTOTYPE      68       /* Socket type not supported */
#define ERANGE          69       /* Result to large */
#define EROFS           70       /* Read-only file system */
#define ESPIPE          71       /* Invalid seek */
#define ESRCH           72       /* No such process */
#define ESTALE          73       /* Reserved */
#define ETIME           74       /* Stream ioctl() timeout */
#define ETIMEDOUT       75       /* Connection timed out */
#define ETXTBSY         76       /* Text file busy */
#define EWOULDBLOCK     77       /* Operation would block */
#define EXDEV           78       /* Cross-device link */

extern int errno;

#endif   /* __ERRNO_H__ */
