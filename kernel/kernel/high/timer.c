
/*
 *  timer.c
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
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 * $Id: timer.c,v 1.4 2002/12/06 13:27:53 fredlie Exp $
 */

#include <sys/errno.h>
#include <sys/types.h>

ulong TimerCreate (void)
{
   return (ENOSYS);
}

ulong TimerDestroy (void)
{
   return (ENOSYS);
}

ulong TimerRead (void)
{
   return (ENOSYS);
}

ulong TimerReset (void)
{
   return (ENOSYS);
}

ulong TimerSet (void)
{
   return (ENOSYS);
}

ulong TimerStart (void)
{
   return (ENOSYS);
}

ulong TimerStop (void)
{
   return (ENOSYS);
}
