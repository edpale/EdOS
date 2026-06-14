#ifndef EDOS_X86_64_CPUFLAGS_H
#define EDOS_X86_64_CPUFLAGS_H

#include <kernel/const.h>

/* RFLAGS Bits */
#define RFLAGS_CF_SHIFT   0
#define RFLAGS_CF         (UL(1) << RFLAGS_CF_SHIFT)
#define RFLAGS_PF_SHIFT   2
#define RFLAGS_PF         (UL(1) << RFLAGS_PF_SHIFT)
#define RFLAGS_AF_SHIFT   4
#define RFLAGS_AF         (UL(1) << RFLAGS_AF_SHIFT)
#define RFLAGS_ZF_SHIFT   6
#define RFLAGS_ZF         (UL(1) << RFLAGS_ZF_SHIFT)
#define RFLAGS_SF_SHIFT   7
#define RFLAGS_SF         (UL(1) << RFLAGS_SF_SHIFT)
#define RFLAGS_TF_SHIFT   8
#define RFLAGS_TF         (UL(1) << RFLAGS_TF_SHIFT)
#define RFLAGS_IF_SHIFT   9
#define RFLAGS_IF         (UL(1) << RFLAGS_IF_SHIFT)
#define RFLAGS_DF_SHIFT   10
#define RFLAGS_DF         (UL(1) << RFLAGS_DF_SHIFT)
#define RFLAGS_OF_SHIFT   11
#define RFLAGS_OF         (UL(1) << RFLAGS_OF_SHIFT)
#define RFLAGS_IOPL_SHIFT 12
#define RFLAGS_IOPL       (UL(1) << RFLAGS_IOPL_SHIFT)
#define RFLAGS_NT_SHIFT   14
#define RFLAGS_NT         (UL(1) << RFLAGS_NT_SHIFT)
#define RFLAGS_RF_SHIFT   16
#define RFLAGS_RF         (UL(1) << RFLAGS_RF_SHIFT)
#define RFLAGS_VM_SHIFT   17
#define RFLAGS_VM         (UL(1) << RFLAGS_VM_SHIFT)
#define RFLAGS_AC_SHIFT   18
#define RFLAGS_AC         (UL(1) << RFLAGS_AC_SHIFT)
#define RFLAGS_VIF_SHIFT  19
#define RFLAGS_VIF        (UL(1) << RFLAGS_VIF_SHIFT)
#define RFLAGS_VIP_SHIFT  20
#define RFLAGS_VIP        (UL(1) << RFLAGS_VIP_SHIFT)
#define RFLAGS_ID_SHIFT   21
#define RFLAGS_ID         (UL(1) << RFLAGS_ID_SHIFT)

/* CR0 Bits */
#define CR0_PE_SHIFT 0
#define CR0_PE       (UL(1) << CR0_PE_SHIFT)
#define CR0_ME_SHIFT 1
#define CR0_ME       (UL(1) << CR0_ME_SHIFT)
#define CR0_EM_SHIFT 2
#define CR0_EM       (UL(1) << CR0_EM_SHIFT)
#define CR0_TS_SHIFT 3
#define CR0_TS       (UL(1) << CR0_TS_SHIFT)
#define CR0_ET_SHIFT 4
#define CR0_ET       (UL(1) << CR0_ET_SHIFT)
#define CR0_NE_SHIFT 5
#define CR0_NE       (UL(1) << CR0_NE_SHIFT)
#define CR0_WP_SHIFT 16
#define CR0_WP       (UL(1) << CR0_WP_SHIFT)
#define CR0_AM_SHIFT 18
#define CR0_AM       (UL(1) << CR0_AM_SHIFT)
#define CR0_NW_SHIFT 29
#define CR0_NW       (UL(1) << CR0_NW_SHIFT)
#define CR0_CD_SHIFT 30
#define CR0_CD       (UL(1) << CR0_CD_SHIFT)
#define CR0_PG_SHIFT 31
#define CR0_PG       (UL(1) << CR0_PG_SHIFT)

/* CR4 Bits */
#define CR4_VME_SHIFT        0
#define CR4_VME              (UL(1) << CR4_VME_SHIFT)
#define CR4_PVI_SHIFT        1
#define CR4_PVI              (UL(1) << CR4_PVI_SHIFT)
#define CR4_TSD_SHIFT        2
#define CR4_TSD              (UL(1) << CR4_TSD_SHIFT)
#define CR4_DE_SHIFT         3
#define CR4_DE               (UL(1) << CR4_DE_SHIFT)
#define CR4_PSE_SHIFT        4
#define CR4_PSE              (UL(1) << CR4_PSE_SHIFT)
#define CR4_PAE_SHIFT        5
#define CR4_PAE              (UL(1) << CR4_PAE_SHIFT)
#define CR4_MCE_SHIFT        6
#define CR4_MCE              (UL(1) << CR4_MCE_SHIFT)
#define CR4_PGE_SHIFT        7
#define CR4_PGE              (UL(1) << CR4_PGE_SHIFT)
#define CR4_PCE_SHIFT        8
#define CR4_PCE              (UL(1) << CR4_PCE_SHIFT)
#define CR4_OSFXSR_SHIFT     9
#define CR4_OSFXSR           (UL(1) << CR4_OSFXSR_SHIFT)
#define CR4_OSXMMEXCPT_SHIFT 10
#define CR4_OSXMMEXCPT       (UL(1) << CR4_OSXMMEXCPT_SHIFT)
#define CR4_UMIP_SHIFT       11
#define CR4_UMIP             (UL(1) << CR4_UMIP_SHIFT)
#define CR4_LA57_SHIFT       12
#define CR4_LA57             (UL(1) << CR4_LA57_SHIFT)
#define CR4_VMXE_SHIFT       13
#define CR4_VMXE             (UL(1) << CR4_VMXE_SHIFT)
#define CR4_SMXE_SHIFT       14
#define CR4_SMXE             (UL(1) << CR4_SMXE_SHIFT)
#define CR4_FSGSBASE_SHIFT   16
#define CR4_FSGSBASE         (UL(1) << CR4_FSGSBASE_SHIFT)
#define CR4_PCIDE_SHIFT      17
#define CR4_PCIDE            (UL(1) << CR4_PCIDE_SHIFT)
#define CR4_OSXSAVE_SHIFT    18
#define CR4_OSXSAVE          (UL(1) << CR4_OSXSAVE_SHIFT)
#define CR4_SMEP_SHIFT       20
#define CR4_SMEP             (UL(1) << CR4_SMEP_SHIFT)
#define CR4_SMAP_SHIFT       21
#define CR4_SMAP             (UL(1) << CR4_SMAP_SHIFT)
#define CR4_PKE_SHIFT        22
#define CR4_PKE              (UL(1) << CR4_PKE_SHIFT)
#define CR4_CET_SHIFT        23
#define CR4_CET              (UL(1) << CR4_CET_SHIFT)
#define CR4_LASS_SHIFT       27
#define CR4_LASS             (UL(1) << CR4_LASS_SHIFT)
#define CR4_LAM_SUP_SHIFT    28
#define CR4_LAM_SUP          (UL(1) << CR4_LAM_SUP_SHIFT)

/* MSR Addresses */
#define MSR_EFER 0xC0000080

/* EFER Bits */
#define EFER_SCE_SHIFT 0
#define EFER_SCE       (UL(1) << EFER_SCE_SHIFT)
#define EFER_LME_SHIFT 8
#define EFER_LME       (UL(1) << EFER_LME_SHIFT)
#define EFER_LMA_SHIFT 10
#define EFER_LMA       (UL(1) << EFER_LMA_SHIFT)
#define EFER_NXE_SHIFT 11
#define EFER_NXE       (UL(1) << EFER_NXE_SHIFT)

#endif
