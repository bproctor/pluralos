
/*
 *  dma.h
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
 * $Id: dma.h,v 1.4 2002/12/05 05:58:36 fredlie Exp $
 */

#ifndef __DMA_H__
#define __DMA_H__

/* DMA channels 0-3 */

#define DMA1_ADDR0      0x00
#define DMA1_CNT0       0x01
#define DMA1_ADDR1      0x02
#define DMA1_CNT1       0x03
#define DMA1_ADDR2      0x04
#define DMA1_CNT2       0x05
#define DMA1_ADDR3      0x06
#define DMA1_CNT3       0x07
#define DMA1_STATUS     0x08
#define DMA1_REQ        0x09
#define DMA1_RW         0x0A
#define DMA1_MODE       0x0B
#define DMA1_FF         0x0C
#define DMA1_CLEAR      0x0D
#define DMA1_RWCLEAR    0x0E
#define DMA1_MASK       0x0F

/* DMA channels 5-7 */

#define DMA2_ADDR0      0xC0
#define DMA2_CNT0       0xC2
#define DMA2_ADDR1      0xC4
#define DMA2_CNT1       0xC6
#define DMA2_ADDR2      0xC8
#define DMA2_CNT2       0xCA
#define DMA2_ADDR3      0xCC
#define DMA2_CNT3       0xCE
#define DMA2_STATUS     0xD0
#define DMA2_REQ        0xD2
#define DMA2_RW         0xD4
#define DMA2_MODE       0xD6
#define DMA2_FF         0xD8
#define DMA2_CLEAR      0xDA
#define DMA2_RWCLEAR    0xDC
#define DMA2_MASK       0xDE

/* DMA pages */

#define DMA_PAGE0       0x87
#define DMA_PAGE1       0x83
#define DMA_PAGE2       0x81
#define DMA_PAGE3       0x82
#define DMA_PAGE5       0x8B
#define DMA_PAGE6       0x89
#define DMA_PAGE7       0x8A

/* DMA transfer types */

#define DMA_VERIFY      0x00
#define DMA_READ        0x01
#define DMA_WRITE       0x02

/* DMA transfer modes */

#define DMA_DEMAND      0x00
#define DMA_SINGLE      0x01
#define DMA_BLOCK       0x02
#define DMA_CASCADE     0x03

void  init_dma (void);
ulong dma_request (uint);
ulong dma_free (uint);
ulong dma_enable_channel (uint);
ulong dma_disable_channel (uint);
ulong dma_clear_ff (uint);
ulong dma_set_mode (uint, uchar);
ulong dma_set_page (uint, uchar);
ulong dma_set_address (uint, void *);
ulong dma_set_count (uint, uint);
ulong dma_transfer (uchar, ulong, uint, uint);

#endif /* __DMA_H__ */
