/* gestalt.c: Glulxe code for gestalt selectors
    Designed by Andrew Plotkin <erkyrath@eblong.com>
    http://eblong.com/zarf/glulx/index.html
*/

#include "glk.h"
#include "glulxe.h"
#include "gestalt.h"

glui32 do_gestalt(glui32 val, glui32 val2)
{
  switch (val) {

  case gestulx_GlulxVersion:
    return 0x00030102; /* Glulx spec version 3.1.2 */

  case gestulx_TerpVersion:
    return 0x00000406; /* Glulxe version 0.4.6 */

  case gestulx_ResizeMem:
#ifdef FIXED_MEMSIZE
    return 0; /* The setmemsize opcodes are compiled out. */
#else /* FIXED_MEMSIZE */
    return 1; /* We can handle setmemsize. */
#endif /* FIXED_MEMSIZE */

  case gestulx_Undo:
    return 1; /* We can handle saveundo and restoreundo. */

  case gestulx_IOSystem:
    switch (val2) {
    case 0:
      return 1; /* The "null" system always works. */
    case 1:
      return 1; /* The "filter" system always works. */
    case 2:
      return 1; /* A Glk library is hooked up. */
    default:
      return 0;
    }

  case gestulx_Unicode:
    return 1; /* We can handle Unicode. */

  case gestulx_MemCopy:
    return 1; /* We can do mcopy/mzero. */

  case gestulx_MAlloc:
#ifdef FIXED_MEMSIZE
    return 0; /* The malloc opcodes are compiled out. */
#else /* FIXED_MEMSIZE */
    return 1; /* We can handle malloc/mfree. */
#endif /* FIXED_MEMSIZE */

  case gestulx_MAllocHeap:
    return heap_get_start_glulxe();

  case gestulx_Acceleration: // disable until we resolve git conflicts
    return 1; /* We can do accelfunc/accelparam. */

  case gestulx_AccelFunc:
    if (accel_find_func_glulxe(val2))
      return 1; /* We know this accelerated function. */
    return 0;

  case gestulx_Float:
#ifdef FLOAT_SUPPORT
    return 1; /* We can do floating-point operations. */
#else /* FLOAT_SUPPORT */
    return 0; /* The floating-point opcodes are not compiled in. */
#endif /* FLOAT_SUPPORT */

  default:
    return 0;

  }
}
