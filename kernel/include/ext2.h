
/*
 *  ext2.h
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
 * $Id: ext2.h,v 1.1 2002/12/02 06:16:43 fredlie Exp $
 */

#ifndef __EXT2_H__
#define __EXT2_H__

struct ext2_super_block
{
   unsigned long  s_inodes_count;         /* Total number of inodes on fs */
   unsigned long  s_blocks_count;         /* Total number of blocks on fs */
   unsigned long  s_r_blocks_count;       /* Total number of blocks reserved */
   unsigned long  s_free_blocks_count;    /* Total number of free blocks */
   unsigned long  s_free_inodes_count;    /* Total number of free inodes */
   unsigned long  s_first_data_block;     /* Position of first data block */
   unsigned long  s_log_block_size;       /* To compute logical block size */
   long           s_log_frag_size;        /* To compute logical fragment size */
   unsigned long  s_blocks_per_group;     /* Total number of blocks per group */
   unsigned long  s_frags_per_group;      /* Total number of fragments per group */
   unsigned long  s_inodes_per_group;     /* Total number of inodes in a group */
   unsigned long  s_mtime;                /* Time of last mount */
   unsigned long  s_vtime;                /* Time of last write on superblock */
   unsigned short s_mnt_count;            /* Number of mounts since last check */
   short          s_max_mnt_count;        /* Max mounts before check needed */
   unsigned short s_magic;                /* 0xEF53 >= version 0.2b, 0xEF51 < 0.2b */
   unsigned short s_state;                /* State of fs */
   unsigned short s_error;                /* last error code */
   unsigned short s_pad;                  /* Unused */
   unsigned long  s_lastcheck;            /* Time last check performed */
   unsigned long  s_checkinterval;        /* Max time between checks */
   unsigned long  s_reserved[238];        /* Unused */
};

struct ext2_sb_info
{
   unsigned long s_frag_size;
   unsigned long s_frags_per_block;
   unsigned long s_inodes_per_block;
   unsigned long s_frags_per_group;
   unsigned long s_blocks_per_group;
   unsigned long s_inodes_per_group;
   unsigned long s_itb_per_group;
   unsigned long s_desc_per_block;
   unsigned long s_groups_count;
   struct buffer_head *s_sbh;
   struct ext2_super_block *s_es;
   struct buffer_head *s_group_desc[EXT2_MAX_GROUP_DESC];
   unsigned short s_loaded_inode_bitmaps;
   unsigned short s_loaded_block_bitmaps;
   unsigned long s_inode_bitmap_number[EXT2_MAX_GROUP_DESC];
   struct buffer_head *s_inode_bitmap[EXT2_MAX_GROUP_DESC];
   unsigned long s_block_bitmap_number[EXT2_MAX_GROUP_DESC];
   struct buffer_head *s_block_bitmap[EXT2_MAX_GROUP_DESC];
   int s_rename_lock;
   struct wait_queue *s_rename_wait;
   unsigned long s_mount_opt;
   unsigned short s_mount_state;
};

struct ext2_group_desc
{
   unsigned long bg_block_bitmap;
   unsigned long bg_inode_bitmap;
   unsigned long bg_inode_table;
   unsigned short bg_free_blocks_count;
   unsigned short bg_free_inodes_count;
   unsigned short bg_used_dirs_count;
   unsigned short bg_pad;
   unsigned long bg_reserved[3];
};

#endif __EXT2_H__
