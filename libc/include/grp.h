
/*
 *  grp.h
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
 * $Id: grp.h,v 1.4 2003/01/23 06:42:46 fredlie Exp $
 */

#ifndef __GRP_H__
#define __GRP_H__

#ifndef __GIDT
#define __GIDT
typedef unsigned int gid_t;
#endif

struct group
{
   char *gr_name;    /* The name of the group */
   gid_t gr_gid;     /* Numerical group ID */
   char **gr_mem;    /* Pointer to a null-terminated array of characters */
};

struct group  *getgrgid (gid_t);
struct group  *getgrnam (const char *);
int            getgrgid_r (gid_t, struct group *, char *, 
                  size_t, struct group **);
int            getgrnam_r (const char *, struct group *, char *,
                  size_t, struct group **);
struct group  *getgrent (void);
void           endgrent (void);
void           setgrent (void);

#endif /* __GRP_H__ */
