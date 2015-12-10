
/*
 *  rtc.h
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
 * $Id: rtc.h,v 1.2 2002/12/05 05:58:36 fredlie Exp $
 */

#ifndef __RTC_H__
#define __RTC_H__

#define RTC_SECONDS           0
#define RTC_SECONDS_ALARM     1
#define RTC_MINUTES           2
#define RTC_MINUTES_ALARM     3
#define RTC_HOURS             4
#define RTC_HOURS_ALARM       5
#define RTC_DAY_OF_WEEK       6
#define RTC_DAY_OF_MONTH      7
#define RTC_MONTH             8
#define RTC_YEAR              9
#define RTC_REG_A             10
#define RTC_REG_B             11
#define RTC_REG_C             12
#define RTC_REG_D             13

#define RTC_FREQ_SELECT       RTC_REG_A
#define RTC_UIP               0x80
#define RTC_DIV_CTL           0x70
#define RTC_REF_CLCK_4MHZ     0x00
#define RTC_REF_CLCK_1MHZ     0x10
#define RTC_REF_CLCK_32MHZ    0x20
#define RTC_DIV_RESET1        0x60
#define RTC_DIV_RESET2        0x70
#define RTC_RATE_SELECT       0x0F

#define RTC_CONTROL           RTC_REG_B
#define RTC_SET               0x80
#define RTC_PIE               0x40
#define RTC_AIE               0x20
#define RTC_UIE               0x10
#define RTC_SQWE              0x08
#define RTC_DM_BINARY         0x04
#define RTC_24H               0x02
#define RTC_DST_EN            0x01

#define RTC_INTR_FLAGS        RTC_REG_C
#define RTC_IRQF              0x80
#define RTC_PF                0x40
#define RTC_AF                0x20
#define RTC_UF                0x10

#define RTC_VALID             RTC_REG_D
#define RTC_VRT               0x80

#define bcd_to_bin(x)   ((x)=((x)&15) + ((x)>>4)*10)
#define bin_to_bcd(x)   ((x)=((x)/10)<<4) + (x)%10)

#endif /* __RTC_H__ */
