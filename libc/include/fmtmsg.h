
/*
 *  fmtmsg.h -- message display structures
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
 * $Id: fmtmsg.h,v 1.4 2003/01/23 06:42:46 fredlie Exp $
 */
 
#ifndef __FMTMSG_H__
#define __FMTMSG_H__

#define MM_HARD      0x0001   /* Source of condition is hardware */
#define MM_SOFT      0x0002   /* Source of condition is software */
#define MM_FIRM      0x0004   /* Source of condition is firmware */
#define MM_APPL      0x0008   /* Condition detected by application */
#define MM_UTIL      0x0010   /* Condition detected by utility */
#define MM_OPSYS     0x0020   /* Condition detected by operating system */
#define MM_RECOVER   0x0040   /* Recoverable error */
#define MM_NRECOV    0x0080   /* Non-recoverable error */
#define MM_HALT      0x0100   /* Error causing application to halt */
#define MM_ERROR     0x0200   /* Application has encountered a non-fatal fault */
#define MM_WARNING   0x0400   /* Application has detected unusual non-error condition */
#define MM_INFO      0x0800   /* Informative message */
#define MM_NOSEV     0x1000   /* No severity level provided for the message */
#define MM_PRINT     0x2000   /* Display message on standard error */
#define MM_CONSOLE   0x4000   /* Display message on system console */

#define MM_NULLBL    ((char *)0)
#define MM_NULLSEV   0
#define MM_NULLMC    ((long)0)
#define MM_NULLTXT   ((char *)0)
#define MM_NULLACT   ((char *)0)
#define MM_NULLTAG   ((char *)0)

#define MM_OK        0        /* The function succeeded */
#define MM_NOTOK     -1       /* The function failed */
#define MM_NOMSG     1        /* The message was unable to generate a message
                                 on standard error, but otherwise succeeded */
#define MM_NOCON     4        /* The message was unable to generate a console
                                 message, but otherwise succeeded */

int fmtmsg (long, const char *, int, const char *,
   const char *, const char *);
   
#endif /* __FMTMSG_H__ */
