
/*
 *  process.c
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
 * $Id: process.c,v 1.5 2002/12/06 13:27:53 fredlie Exp $
 */

#include <sys/errno.h>
#include <sys/types.h>

ulong ProcessCreate (void)
{
   return (ENOSYS);
}

ulong ProcessDestroy (void)
{
   return (ENOSYS);
}

ulong ProcessGetPriority (void)
{
   return (ENOSYS);
}

ulong ProcessSetPriority (void)
{
   return (ENOSYS);
}

ulong ProcessGetPolicy (void)
{
   return (ENOSYS);
}

ulong ProcessSetPolicy (void)
{
   return (ENOSYS);
}

ulong ProcessThreads (void)
{
   return (ENOSYS);
}
