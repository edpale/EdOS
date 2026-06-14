#ifndef EDOS_CONST_H
#define EDOS_CONST_H

#ifdef __ASSEMBLER__
#define ASMC(_x, _y) _x
#define ASMT(_x, _y) _x
#else
#define __AC(_x, _y) (_x##_y)
#define ASMC(_x, _y) __AC(_x, _y)
#define ASMT(_x, _y) ((_y)(_x))
#endif

#define UL(_x)  (ASMC(_x, UL))
#define ULL(_x) (ASMC(_x, ULL))

#endif
