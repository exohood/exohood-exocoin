/*
/***
*     ______           __                    __
*    / _____  ______  / /_  ____  ____  ____/ /
*   / __/ | |/_/ __ \/ __ \/ __ \/ __ \/ __  / 
*  / /____>  </ /_/ / / / / /_/ / /_/ / /_/ /  
* /_____/_/|_|\____/_/ /_/\____/\____/\__,_/   
*                                             
*   
*    
* https://www.exohood.com
*
* MIT License
* ===========
*
* Copyright (c) 2020 - 2022 Exohood Protocol
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include "aligned.h"

static inline int is_power_of_2(size_t n) { return n && (n & (n-1)) == 0; }

#define MAGIC 0xaa0817161500ff81
#define MAGIC_FREED 0xaa0817161500ff82

static void local_abort(const char *msg)
{
  fprintf(stderr, "%s\n", msg);
#ifdef NDEBUG
  _exit(1);
#else
  abort();
#endif
}

typedef struct
{
  uint64_t magic;
  void *raw;
  size_t bytes;
  size_t align;
} control;

void *aligned_malloc(size_t bytes, size_t align)
{
  void *raw, *ptr;
  control *ctrl;

  if (!is_power_of_2(align))
    return NULL;
  if (bytes > (size_t)-1 - align)
    return NULL;
  if (bytes + align > (size_t)-1 - sizeof(control))
    return NULL;

  raw = malloc(bytes + sizeof(control) + align);
  if (!raw)
    return NULL;
  ptr = (void*)(((uintptr_t)raw + align + sizeof(control) - 1) & ~(align-1));
  ctrl = ((control*)ptr) - 1;
  ctrl->magic = MAGIC;
  ctrl->raw = raw;
  ctrl->bytes = bytes;
  ctrl->align = align;
  return ptr;
}

void *aligned_realloc(void *ptr, size_t bytes, size_t align)
{
  void *raw, *ptr2;
  control *ctrl, *ctrl2;

  if (!ptr)
    return aligned_malloc(bytes, align);
  if (!bytes)
  {
     aligned_free(ptr);
     return NULL;
  }
  if (!is_power_of_2(align))
    return NULL;

  ctrl = ((control*)ptr) - 1;
  if (ctrl->magic == MAGIC_FREED)
    local_abort("Double free detected");
  if (ctrl->magic != MAGIC)
    local_abort("Freeing unallocated memory");
  if (ctrl->align != align)
    return NULL;
  if (ctrl->bytes >= bytes)
    return ptr;

  if (ctrl->bytes > (size_t)-1 - ctrl->align)
    return NULL;
  if (ctrl->bytes + ctrl->align > (size_t)-1 - sizeof(control))
    return NULL;

  raw = malloc(bytes + sizeof(control) + ctrl->align);
  if (!raw)
    return NULL;
  ptr2 = (void*)(((uintptr_t)raw + ctrl->align + sizeof(control) - 1) & ~(ctrl->align-1));
  memcpy(ptr2, ptr, ctrl->bytes);
  ctrl2 = ((control*)ptr2) - 1;
  ctrl2->magic = MAGIC;
  ctrl2->raw = raw;
  ctrl2->bytes = bytes;
  ctrl2->align = ctrl->align;
  ctrl->magic = MAGIC_FREED;
  free(ctrl->raw);
  return ptr2;
}

void aligned_free(void *ptr)
{
  if (!ptr)
    return;
  control *ctrl = ((control*)ptr) - 1;
  if (ctrl->magic == MAGIC_FREED)
    local_abort("Double free detected");
  if (ctrl->magic != MAGIC)
    local_abort("Freeing unallocated memory");
  ctrl->magic = MAGIC_FREED;
  free(ctrl->raw); 
}
