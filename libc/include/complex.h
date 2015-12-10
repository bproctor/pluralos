
/*
 *  complex.h
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
 * $Id: complex.h,v 1.3 2003/01/23 06:42:46 fredlie Exp $
 */

#ifndef __COMPLEX_H__
#define __COMPLEX_H__

#define complex        _Complex
#define _Complex_I     (const float _Complex)
#define imaginary      _Imaginary
#define _Imaginary_I   (const float _Imaginary)
#define I              _Imaginary_I

double              cabs (double complex);
float               cabsf (float complex);
long double         cabsl (long double complex);
double complex      cacos (double complex);
float complex       cacosf (float complex);
double complex      cacosh (double complex);
float complex       cacoshf (float complex);
long double complex cacoshl (long double complex);
long double complex cacosl (long double complex);
double              carg (double complex);
float               cargf (float complex);
long double         cargl (long double complex);
double complex      casin (double complex);
float complex       casinf (float complex);
double complex      casinh (double complex);
float complex       casinhf (float complex);
long double complex casinhl (long double complex);
long double complex casinl (long double complex);
double complex      catan (double complex);
float complex       catanf (float complex);
double complex      catanh (double complex);
float complex       catanhf (float complex);
long double complex catanhl (long double complex);
long double complex catanl (long double complex);
double complex      ccos (double complex);
float complex       ccosf (float complex);
double complex      ccosh (double complex);
float complex       ccoshf (float complex);
long double complex ccoshl (long double complex);
long double complex ccosl (long double complex);
double complex      cexp (double complex);
float complex       cexpf (float complex);
long double complex cexpl (long double complex);
double complex      cimag (double complex);
float complex       cimagf (float complex);
long double complex cimagl (long double complex);
double complex      clog (double complex);
float complex       clogf (float complex);
long double complex clogl (long double complex);
double complex      conj (double complex);
float complex       conjf (float complex);
long double complex conjl (long double complex);
double complex      cpow (double complex, double complex);
float complex       cpowf (float complex, float complex);
long double complex cpowl (long double complex, long double complex);
double complex      cproj (double complex);
float complex       cprojf (float complex);
long double complex cprojl (long double complex);
double complex      creal (double complex);
float complex       crealf (float complex);
long double complex creall (long double complex);
double complex      csin (double complex);
float complex       csinf (float complex);
double complex      csinh (double complex);
float complex       csinhf (float complex);
long double complex csinhl (long double complex);
long double complex csinl (long double complex);
double complex      csqrt (double complex);
float complex       csqrtf (float complex);
long double complex csqrtl (long double complex);
double complex      ctan (double complex);
float complex       ctanf (float complex);
double complex      ctanh (double complex);
float complex       ctanhf (float complex);
long double complex ctanhl (long double complex);
long double complex ctanl (long double complex);


/* The follow function names are reserved by the POSIX standard */
#define cerf()
#define cerfc()
#define cerfcf()
#define cerfcl()
#define cerff()
#define cerfl()
#define cexp2()
#define cexp2f()
#define cexp2l()
#define cexpm1()
#define cexpm1f()
#define cexpm1l()
#define clog10()
#define clog10f()
#define clog10l()
#define clog1p()
#define clog1pf()
#define clog1pl()
#define clog2()
#define clog2f()
#define clog2l()
#define clgamma()
#define clgammaf()
#define clgammal()
#define ctgamma()
#define ctgammaf()
#define ctgammal()


#endif /* __COMPLEX_H__ */
