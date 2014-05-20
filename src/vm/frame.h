#ifndef VM_FRAME_H
#define VM_FRAME_H

#include <stdint.h>
#include "threads/thread.h"

enum frame_flags
{
    FRM_ASSERT = 0x1,           /* Panic on failure. */
    FRM_ZERO = 0x2,             /* Zero page contents. */
    FRM_USER = 0x4,             /* User page. */
    FRM_MMAP = 0x8              /* Page used for mmap. */
};

/* Frame table entry */
struct fte
{
  struct thread *thread;      /* Thread that owns this frame table entry. */
  uint32_t *pte;                /* The beginning virtual address that cooresponds
                                 to this frame table entry. */
};

/* Frame table*/
struct frame_table
{
  size_t size;                /* total number of frames in this frame table */
  struct fte *frames;         /* frames in the table */
};

struct frame_table frame_table;  /* frame table used to check user memory. */

void frame_init (void *base, size_t page_cnt);
size_t frame_table_size (size_t page_cnt);
void frame_free_multiple (void *pages, size_t page_cnt);
void frame_free_page (void *page);
void *frame_get_page (enum frame_flags flags, void *upage);

#endif /* vm/frame.h */
