
/*
 *  elf.h
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
 * $Id: elf.h,v 1.2 2002/12/02 06:16:42 fredlie Exp $
 */

#ifndef __ELF_H__
#define __ELF_H__

#define ET_NONE         0x0000
#define ET_REL          0x0001
#define ET_EXEC         0x0002
#define ET_DYN          0x0003
#define ET_CORE         0x0004
#define ET_LOPROC       0xFF00
#define ET_HIPROC       0xFFFF

#define EM_NONE         0x0000
#define EM_M32          0x0001
#define EM_SPARC        0x0002
#define EM_386          0x0003
#define EM_68K          0x0004
#define EM_88K          0x0005
#define EM_860          0x0007
#define EM_MIPS         0x0008

#define EV_NONE         0x0000
#define EV_CURRENT      0x0001

#define EI_MAG0         0x0000
#define EI_MAG1         0x0001
#define EI_MAG2         0x0002
#define EI_MAG3         0x0003
#define EI_CLASS        0x0004
#define EI_DATA         0x0005
#define EI_VERSION      0x0006
#define EI_PAD          0x0007
#define EI_NIDENT       0x0016

#define ELFMAG0         0x7F
#define ELFMAG1         'E'
#define ELFMAG2         'L'
#define ELFMAG3         'F'

#define ELFCLASSNONE    0x0000
#define ELFCLASS32      0x0001
#define ELFCLASS64      0x0002

#define ELFDATANONE     0x0000
#define ELFDATA2LSB     0x0001
#define ELFDATA2MSB     0x0002

#define SHN_UNDEF       0x0000
#define SHN_LORESERVE   0xFF00
#define SHN_LOPROC      0xFF00
#define SHN_HIPROC      0xFF1F
#define SHN_ABS         0xFFF1
#define SHN_COMMON      0xFFF2
#define SHN_HIRESERVE   0xFFFF

#define SHT_NULL        0x0000
#define SHT_PROGBITS    0x0001
#define SHT_SYMTAB      0x0002
#define SHT_STRTAB      0x0003
#define SHT_RELA        0x0004
#define SHT_HASH        0x0005
#define SHT_DYNAMIC     0x0006
#define SHT_NOTE        0x0007
#define SHT_NOBITS      0x0008
#define SHT_REL         0x0009
#define SHT_SHLIB       0x000A
#define SHT_DYNSYM      0x000B
#define SHT_LOPROC      0x70000000
#define SHT_HIPROC      0x7FFFFFFF
#define SHT_LOUSER      0x80000000
#define SHT_HIUSER      0xFFFFFFFF

#define SHF_WRITE       0x0001
#define SHF_ALLOC       0x0002
#define SHF_EXECINSTR   0x0004
#define SHF_MASKPROC    0xF0000000

#define STN_UNDEF       0x0000

#define STB_LOCAL       0x0000
#define STB_GLOBAL      0x0001
#define STB_WEAK        0x0002
#define STB_LOPROC      0x000D
#define STB_HIPROC      0x000F

#define STT_NOTYPE      0x0000
#define STT_OBJECT      0x0001
#define STT_FUNC        0x0002
#define STT_SECTION     0x0003
#define STT_FILE        0x0004
#define STT_LOPROC      0x000D
#define STT_HIPROC      0x000F

#define R_386_NONE      0
#define R_386_32        1
#define R_386_PC32      2
#define R_386_GOT32     3
#define R_386_PLT32     4
#define R_386_COPY      5
#define R_386_GLOB_DAT  6
#define R_386_JMP_SLOT  7
#define R_386_RELATIVE  8
#define R_386_GOTOFF    9
#define R_386_GOTPC     10

#define PT_NULL         0
#define PT_LOAD         1
#define PT_DYNAMIC      2
#define PT_INTERP       3
#define PT_NOTE         4
#define PT_SHLIB        5
#define PT_PHDR         6
#define PT_LOPROC       0x70000000
#define PT_HIPROC       0x7FFFFFFF

#define DT_NULL         0
#define DT_NEEDED       1
#define DT_PLTRELSZ     2
#define DT_PLTGOT       3
#define DT_HASH         4
#define DT_STRTAB       5
#define DT_SYMTAB       6
#define DT_RELA         7
#define DT_RELASZ       8
#define DT_RELAENT      9
#define DT_STRSZ        10
#define DT_SYMENT       11
#define DT_INIT         12
#define DT_FINI         13
#define DT_SONAME       14
#define DT_RPATH        15
#define DT_SYMBOLIC     16
#define DT_REL          17
#define DT_RELSZ        18
#define DT_RELENT       19
#define DT_PLTREL       20
#define DT_DEBUG        21
#define DT_TEXTREL      22
#define DT_JMPREL       23
#define DT_LOPROC       0x70000000
#define DT_HIPROC       0x7FFFFFFF

#define ELF32_ST_BIND(i)   ((i) >> 4)
#define ELF32_ST_TYPE(i)   ((i) & 0xF)
#define ELF32_ST_INFO(b,t) (((b) << 4) + ((t) & 0xF))

#define ELF32_R_SYM(i)     ((i) >> 8)
#define ELF32_R_TYPE(i)    ((unsigned char)(i))
#define ELF32_R_INFO(s,t)  (((s) >> 8) + (unsigned char)(t))
   
typedef unsigned long   Elf32_Addr;
typedef unsigned long   Elf32_Word;
typedef unsigned short  Elf32_Half;
typedef unsigned long   Elf32_Off;
typedef signed long     Elf32_Sword;

typedef struct
{
   unsigned char e_ident[EI_NIDENT];
   Elf32_Half     e_type;
   Elf32_Half     e_machine;
   Elf32_Word     e_version;
   Elf32_Addr     e_entry;
   Elf32_Off      e_phoff;
   Elf32_Off      e_shoff;
   Elf32_Word     e_flags;
   Elf32_Half     e_ehsize;
   Elf32_Half     e_phentsize;
   Elf32_Half     e_phnum;
   Elf32_Half     e_shentsize;
   Elf32_Half     e_shnum;
   Elf32_Half     e_shstrndx;
} Elf32_Ehdr;

typedef struct
{
   Elf32_Word  sh_name;
   Elf32_Word  sh_type;
   Elf32_Word  sh_flags;
   Elf32_Addr  sh_addr;
   Elf32_Off   sh_offset;
   Elf32_Word  sh_size;
   Elf32_Word  sh_link;
   Elf32_Word  sh_info;
   Elf32_Word  sh_addralign;
   Elf32_Word  sh_entsize;
} Elf32_Shdr;

typedef struct
{
   Elf32_Word  st_name;
   Elf32_Addr  st_value;
   Elf32_Word  st_size;
   unsigned char st_info;
   unsigned char st_other;
   Elf32_Half  st_shndx;
} Elf32_Sym;

typedef struct
{
   Elf32_Addr  r_offset;
   Elf32_Word  r_info;
} Elf32_Rel;

typedef struct
{
   Elf32_Addr  r_offset;
   Elf32_Word  r_info;
   Elf32_Sword r_addend;
} Elf32_Rela;

typedef struct
{
   Elf32_Word  p_type;
   Elf32_Off   p_offset;
   Elf32_Addr  p_vaddr;
   Elf32_Addr  p_paddr;
   Elf32_Word  p_filesz;
   Elf32_Word  p_memsz;
   Elf32_Word  p_flags;
   Elf32_Word  p_align;
} Elf32_Phdr;

typedef struct
{
   Elf32_Sword d_tag;
   union
   {
      Elf32_Word  d_val;
      Elf32_Addr  d_ptr;
   } d_un;
} Elf32_Dyn;

static inline long elf_hash (const unsigned char *name)
{
   unsigned long g, h = 0;
   while (*name)
   {
      h = (h << 4) + *name++;
      if ((g = h & 0xF0000000) == 0)
         h ^= g >> 24;
      h &= ~g;
   }
   return (h);
}


#endif /* __ELF_H__ */
