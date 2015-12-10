
/*
 *  math.h -- 
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
 * $Id: math.h,v 1.3 2003/01/23 06:42:46 fredlie Exp $
 */

#ifndef __MATH_H__
#define __MATH_H__

#ifdef __XOPEN__
#ifndef __LDOUBLE_MATH__

/* These constants are for the 'double' data type and meet X/Open 
   SUSV2 standards */
#define M_E		      2.7182818284590452354	/* e */
#define M_LOG2E	   1.4426950408889634074	/* log_2 e */
#define M_LOG10E	   0.43429448190325182765	/* log_10 e */
#define M_LN2		   0.69314718055994530942	/* log_e 2 */
#define M_LN10		   2.30258509299404568402	/* log_e 10 */
#define M_PI		   3.14159265358979323846	/* pi */
#define M_PI_2		   1.57079632679489661923	/* pi/2 */
#define M_PI_4		   0.78539816339744830962	/* pi/4 */
#define M_1_PI		   0.31830988618379067154	/* 1/pi */
#define M_2_PI		   0.63661977236758134308	/* 2/pi */
#define M_2_SQRTPI	1.12837916709551257390	/* 2/sqrt(pi) */
#define M_SQRT2	   1.41421356237309504880	/* sqrt(2) */
#define M_SQRT1_2	   0.70710678118654752440	/* 1/sqrt(2) */

#else /* __LDOUBLE_MATH__ */

/* These constants are for the 'long double' type. */
#define M_E          2.7182818284590452353602874713526625L  /* e */
#define M_LOG2E      1.4426950408889634073599246810018922L  /* log_2 e */
#define M_LOG10E     0.4342944819032518276511289189166051L  /* log_10 e */
#define M_LN2        0.6931471805599453094172321214581766L  /* log_e 2 */
#define M_LN10       2.3025850929940456840179914546843642L  /* log_e 10 */
#define M_PI         3.1415926535897932384626433832795029L  /* pi */
#define M_PI_2	      1.5707963267948966192313216916397514L  /* pi/2 */
#define M_PI_4       0.7853981633974483096156608458198757L  /* pi/4 */
#define M_1_PI       0.3183098861837906715377675267450287L  /* 1/pi */
#define M_2_PI       0.6366197723675813430755350534900574L  /* 2/pi */
#define M_2_SQRTPI   1.1283791670955125738961589031215452L  /* 2/sqrt(pi) */
#define M_SQRT2      1.4142135623730950488016887242096981L  /* sqrt(2) */
#define M_SQRT1_2    0.7071067811865475244008443621048490L  /* 1/sqrt(2) */

#endif /* __LDOUBLE_MATH__ */

#define HUGE_VAL
#define MAXFLOAT

#endif /* __XOPEN__ */

double acos (double);
double asin (double);
double atan (double);
double atan2 (double);
double ceil (double);
double cos (double);
double cosh (double);
double exp (double);
double fabs (double);
double floor (double);
double fmod (double, double);
double frexp (double, int *);
double ldexp (double, int);
double log (double);
double log10 (double);
double modf (double, double *);
double pow (double, double);
double sin (double);
double sinh (double);
double sqrt (double);
double tan (double);
double tanh (double);

#ifdef __XOPEN__
double erf (double);
double erfc (double);
double gamma (double);
double hypot (double, double);
double j0 (double);
double j1 (double);
double jn (double);
double lgamma (double);
double y0 (double);
double y1 (double);
double yn (int, double);
int isnan (double);
double acosh (double);
double asinh (double);
double atanh (double);
double cbrt (double);
double expm1 (double);
int ilogb (double);
double log1p (double);
double logb (double);
double nextafter (double, double);
double remainder (double, double);
double rint (double);
double scalb (double);

extern int signgam;

#endif /* __XOPEN__ */

#endif /* __MATH_H__ */
