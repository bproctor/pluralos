
/*
 *  interrupt.h
 *  Copyright (c) 2001-2002 Brad Proctor
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
 * $Id: interrupt.h,v 1.2 2002/12/02 09:06:24 fredlie Exp $
 */

#ifndef __SYS_INTERRUPT_H__
#define __SYS_INTERRUPT_H__

#ifndef __SYS_TYPES_H__
#include <sys/types.h>
#endif

ulong InterruptAttach  (ulong, void *, const char *);
ulong InterruptDetach  (ulong);
ulong InterruptDisable (ulong);
ulong InterruptEnable  (ulong);
ulong InterruptLock    (void);
ulong InterruptMask    (void);
ulong InterruptUnlock  (void);
ulong InterruptUnmask  (void);
ulong InterruptWait    (void);

#endif /* __SYS_INTERRUPT_H__ */
