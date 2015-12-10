
/*
 *  fenv.h
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
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 * $Id: fenv.h,v 1.3 2003/01/29 08:22:50 fredlie Exp $
 */

#ifndef __FENV_H__
#define __FENV_H__

/* Represents the entire floating-point environment */
typedef struct fenv_t
{
};

/* Represents the floating-point status flags */
typedef struct fexcept_t
{
};

#define FE_DIVBYZERO
#define FE_INEXACT
#define FE_INVALID
#define FE_OVERFLOW
#define FE_UNDERFLOW

#define FE_ALL_EXCEPT

#define FE_DOWNWARD
#define FE_TONEAREST
#define FE_TOWARDZERO
#define FE_UPWARD

#define FE_DFL_ENV

int feclearexcept (int);
int fegetexceptflag (fexcept_t *, int);
int feraiseexcept (int);
int fesetexceptflag (const fexcept_t *, int);
int fegetround (void);
int fesetround (int);
int fegetenv (fenv_t *);
int feholdexcept (fenv_t *);
int fesetenv (const fenv_t *);
int feupdateenv (const fenv_t *);

#endif /* __FENV_H__ */
