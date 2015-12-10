
/*
 *  alloc.c
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
 * $Id: alloc.c,v 1.7 2002/12/02 09:06:25 fredlie Exp $
 */

#include <string.h>
#include <stdlib.h>

/*
 * Change this to change the minimum size of an allocated block (in bytes).
 */

#define  SIZE_BLOCK  512

/*
 * Change this to change the memory alignment boundry.
 * On 32-bit machines, this should be 3.  For a boundry of
 * 2^n this should be set to 2^n-1.
 */

#define  MEM_BND     3

#define  CELL_OFF    ((sizeof(unsigned int) + MEM_BND) & ~MEM_BND)
#define  SIZE_CELL   (((sizeof(cell) + MEM_BND) & ~MEM_BND) - CELL_OFF)
#define  ROUND(x)    (((x) + MEM_BND) & ~MEM_BND)

typedef struct cell
{
   size_t size;
   struct cell *next;
} cell;

static cell *mem_head = 0;    /* Head of the list */
static cell **mem_tail = 0;   /* Pointer to the tail of the list */


/*
 * This function calls the operating system
 * function that allocates a block of memory.
 */

static inline void *get_mem (size_t size)
{
   size = ((size + 4095) & ~4096) >> 12;
   return ((void *)MemoryAlloc (size));
}

/*
 * Allocate memory from the heap.
 */

void *malloc (size_t size)
{
   size_t i, j;
   cell **ptr, *ptr1;
   
   size = size < SIZE_CELL ? ROUND(SIZE_CELL) : ROUND(size);

   while (1)
   {
      ptr = mem_tail;
      if (ptr == NULL)
      {
         ptr = &mem_head;
         if (*ptr)
         {
            do {
               if (size <= (*ptr)->size)
                  goto malloc_done;
               ptr = &(*ptr)->next;    
            } while (*ptr);
         }
      }
      else
      {
         if (*ptr)
         {
            do {
               if (size <= (*ptr)->size)
                  goto malloc_done;
               ptr = &(*ptr)->next;
            } while (*ptr);
         }
         ptr1 = *mem_tail;
         ptr = &mem_head;
         if (*ptr != ptr1)
         {
            do {
               if (size <= (*ptr)->size)
                  goto malloc_done;
               ptr = &(*ptr)->next;
            } while (*ptr != ptr1);
         }
      }
      j = size + CELL_OFF;
      i = SIZE_BLOCK;
      while (1)
      {
         if (i < j)
            i = j;
         ptr1 = get_mem (i);
         if (ptr1 != NULL)
            break;
         else if (i == j)
            return (NULL);
         i >>= 1;
      }
      ptr1->size = (i & ~MEM_BND) - CELL_OFF;
      free ((char *)ptr1 + CELL_OFF);
   }
malloc_done:   
   if (ptr == NULL)
      return (NULL);
   ptr1 = *ptr;
   if (ptr1->size < size + CELL_OFF + SIZE_CELL)
      *ptr = ptr1->next;
   else
   {
      *ptr = (cell *)((char *)ptr1 + CELL_OFF + size);
      (*ptr)->next = ptr1->next;
      (*ptr)->size = ptr1->size - CELL_OFF - size;
      ptr1->size = size;
   }
   mem_tail = ptr ? ptr : NULL;
   return ((char *)ptr1 + CELL_OFF);
}

/*
 * Allocate memory and set it to a 0.
 */

void *calloc (size_t n, size_t size)
{
   size_t i = n * size;
   void *ptr = malloc (i);
   
   if (ptr)
      memset (ptr, '\0', i);

   return (ptr);
}

/*
 * Free memory from the heap.
 */

void free (void *ptr)
{
   cell *ptr1, *p;
   char *p1;
   
   if (ptr == NULL)
      return;
   
   ptr1 = (cell *)((char *)ptr - CELL_OFF);
   if (ptr1->size & MEM_BND)
      return;
   if (mem_head == NULL || ptr1 < mem_head)
   {
      ptr1->next = mem_head;
      mem_head = ptr1;
   }
   else
   {
      p = mem_head;
      while (p->next && ptr1 < p->next)
         p = p->next;
      p1 = (char *)p + CELL_OFF + p->size;
      if ((char *)ptr1 < p1)
         return;
      else if ((char *)ptr1 == p1)
      {
         p->size += CELL_OFF + ptr1->size;
         ptr1 = p;
      }
      else
      {
         ptr1->next = p->next;
         p->next = ptr1;
      }
   }     
   if (ptr1->next && (char *)ptr1 + CELL_OFF + ptr1->size
      == (char *)ptr1->next)
   {
      ptr1->size += CELL_OFF + ptr1->next->size;
      ptr1->next = ptr1->next->next;
   }
   mem_tail = &ptr1->next;
}

/*
 * Reallocate a block of heap memory.
 */

void *realloc (void *ptr, size_t size)
{
   cell *ptr1;
   
   if (ptr == NULL)
      return (malloc (size));
   ptr1 = (cell *)((char *)ptr - CELL_OFF);
   if (ptr1->size < size)
   {
      char *const p1 = (char *)malloc (size);
   
      if (p1 == NULL)
         return (NULL);
      
      memcpy (p1, ptr, ptr1->size);
      free (ptr);
      return (p1);
   }
   else if (ptr1->size < size + CELL_OFF + SIZE_CELL)
      return (ptr);
   else
   {
      const size_t n = ROUND (size);
      cell *const p = (cell *)((char *)ptr + n);
      
      p->size = ptr1->size - CELL_OFF - n;
      ptr1->size = n;
      free ((char *)p + CELL_OFF);
      return (ptr);
   }
}
