#ifndef EDOS_X86_64_PTE_H
#define EDOS_X86_64_PTE_H

#define PG_V  (1 << 0) /* P   Valid               */
#define PG_RW (1 << 1) /* R/W Read/Write          */
#define PG_U  (1 << 2) /* U/S User/Supervisor     */
#define PG_PS (1 << 7) /* PS  Page size (1 - 2MB) */

#endif
