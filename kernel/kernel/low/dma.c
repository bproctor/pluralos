
/*
 *  dma.c
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
 * $Id: dma.c,v 1.7 2002/12/02 09:06:24 fredlie Exp $
 */

#include <io.h>
#include <system.h>
#include <stdio.h>
#include <sys/types.h>
#include <dma.h>
#include <sys/errno.h>
#include <config.h>

#define CONFIG_DMA_CHANNELS   8

typedef struct
{
   uchar lock;
   uchar addr;
   uchar count;
   uchar page;
   uchar clear;
   uchar mode;
   uchar mask;
} DMAChannel;

static DMAChannel dma_channels[CONFIG_DMA_CHANNELS] =
{
   {0x00, 0x00, 0x01, 0x87, 0x0C, 0x0B, 0x0A},
   {0x00, 0x02, 0x03, 0x83, 0x0C, 0x0B, 0x0A},
   {0x00, 0x04, 0x05, 0x81, 0x0C, 0x0B, 0x0A},
   {0x00, 0x06, 0x07, 0x82, 0x0C, 0x0B, 0x0A},
   {0x01, 0xC0, 0xC2, 0x00, 0xD8, 0xD6, 0xD4},
   {0x00, 0xC4, 0xC6, 0x8B, 0xD8, 0xD6, 0xD4},
   {0x00, 0xC8, 0xCA, 0x89, 0xD8, 0xD6, 0xD4},
   {0x00, 0xCC, 0xCE, 0x8A, 0xD8, 0xD6, 0xD4},
};

ulong dma_request (uint channel)
{
   if (channel >= CONFIG_DMA_CHANNELS)
      return (EINVAL);
   return (0);
}

ulong dma_free (uint channel)
{
   if (channel >= CONFIG_DMA_CHANNELS)
      return (EINVAL);
   return (0);
}

ulong dma_enable_channel (uint channel)
{
   if (channel >= CONFIG_DMA_CHANNELS)
      return (EINVAL);
   outb (dma_channels[channel].mask, channel & 3);
   return (0);
}

ulong dma_disable_channel (uint channel)
{
   if (channel >= CONFIG_DMA_CHANNELS)
      return (EINVAL);
   outb (dma_channels[channel].mask, (channel & 3) | 4);
   return (0);
}

ulong dma_clear_ff (uint channel)
{
   if (channel >= CONFIG_DMA_CHANNELS)
      return (EINVAL);
   outb (dma_channels[channel].clear, 0);
   return (0);
}

ulong dma_set_mode (uint channel, uchar mode)
{
   if (channel >= CONFIG_DMA_CHANNELS)
      return (EINVAL);
   outb (dma_channels[channel].mode, (channel & 3) | mode);
   return (0);
}

ulong dma_set_page (uint channel, uchar page)
{
   if (channel >= CONFIG_DMA_CHANNELS)
      return (EINVAL);
   outb (dma_channels[channel].page, (channel < 4) ? page : page & 0xFE);
   return (0);
}

ulong dma_set_address (uint channel, void *addr)
{
   if (channel >= CONFIG_DMA_CHANNELS)
      return (EINVAL);
   if (channel < 4)
   {
      outb (dma_channels[channel].addr, (uint)addr & 0xFF);
      outb (dma_channels[channel].addr, ((uint)addr << 8) & 0xFF);
   }
   else
   {
      outb (dma_channels[channel].addr, ((uint)addr >> 1) & 0xFF);
      outb (dma_channels[channel].addr, ((uint)addr >> 9) & 0xFF);
   }
   return (0);
}

ulong dma_set_count (uint channel, uint count)
{
   uint c;
   if (channel >= CONFIG_DMA_CHANNELS)
      return (EINVAL);

   c = count - 1;
   if (channel < 4)
   {
      outb (dma_channels[channel].count, c & 0xFF);
      outb (dma_channels[channel].count, (c >> 8) & 0xFF);
   }
   else
   {
      outb (dma_channels[channel].count, (c >> 1) & 0xFF);
      outb (dma_channels[channel].count, (c >> 9) & 0xFF);
   }
   return (0);
}

ulong dma_transfer (uchar channel, ulong addr, uint length, uint read)
{
   uchar page = 0, mode = 0;
   uint offset = 0;
   
   mode = channel + (read ? 0x48 : 0x44);
   page = addr >> 16;
   offset = addr & 0xFFFF;
   length--;
   
   outb (dma_channels[channel].mask, 0x04 | channel);
   outb (dma_channels[channel].clear, 0x00);
   outb (dma_channels[channel].mode, mode);
   outb (dma_channels[channel].addr, offset & 0xFF);
   outb (dma_channels[channel].addr, (offset & 0xFF00) >> 8);
   outb (dma_channels[channel].page, page);
   outb (dma_channels[channel].count, length & 0xFF);
   outb (dma_channels[channel].count, (length & 0xFF00) >> 8);
   outb (dma_channels[channel].mask, channel);

   return (0);
}
