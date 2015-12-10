
/*
 *  pit.h
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
 * $Id: pit.h,v 1.3 2002/12/05 05:58:36 fredlie Exp $
 */

#ifndef __PIT_H__
#define __PIT_H__

/* PIT i/o ports */
#define PIT_CTRL     0x43
#define PIT_CTRL0    0x40
#define PIT_CTRL1    0x41
#define PIT_CTRL2    0x42


/* PIT bits */
#define PIT_MODE0    0x00
#define PIT_MODE1    0x02
#define PIT_MODE2    0x04
#define PIT_MODE3    0x06
#define PIT_MODE4    0x08
#define PIT_MODE5    0x0A

#define PIT_SC0      0x00
#define PIT_SC1      0x40
#define PIT_SC2      0x80

#define PIT_LOW      0x10
#define PIT_HIGH     0x20
#define PIT_BOTH     0x30

#define PIT_BCD      0x01
#define PIT_LATCH    0x00
#define PIT_READ     0xF0
#define PIT_CNT      0x20
#define PIT_STAT     0x10

#define PIT_CH0      0x02
#define PIT_CH1      0x04
#define PIT_CH2      0x08

void init_pit (unsigned long, unsigned char);
unsigned long pit_getchannel (unsigned char);

#endif /* __PIT_H__ */
