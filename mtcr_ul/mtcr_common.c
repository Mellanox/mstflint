#include "mtcr_common.h"

void swap_pci_address_space(mfile* mf)
{
    switch (mf->address_space) {
    case AS_ICMD_EXT:
        mf->address_space = AS_PCI_ICMD;
        break;

    case AS_ND_CRSPACE:
    case AS_CR_SPACE:
        mf->address_space = AS_PCI_CRSPACE;
        break;

    case AS_ICMD:
        mf->address_space = AS_PCI_ALL_ICMD;
        break;

    case AS_SCAN_CRSPACE:
        mf->address_space = AS_PCI_SCAN_CRSPACE;
        break;

    case AS_SEMAPHORE:
        mf->address_space = AS_PCI_GLOBAL_SEMAPHORE;
        break;

    case AS_PCI_ICMD:
        mf->address_space = AS_ICMD_EXT;
        break;

    case AS_PCI_CRSPACE:
        mf->address_space = AS_CR_SPACE;
        break;

    case AS_PCI_ALL_ICMD:
        mf->address_space = AS_ICMD;
        break;

    case AS_PCI_SCAN_CRSPACE:
        mf->address_space = AS_SCAN_CRSPACE;
        break;

    case AS_PCI_GLOBAL_SEMAPHORE:
        mf->address_space = AS_SEMAPHORE;
        break;

    default:
        DBG_PRINTF("MTCR: swap_pci_address_space: no address_space found: %x\n", mf->address_space);
        return;
    }

    DBG_PRINTF("mf->address_space swapped to: %x\n", mf->address_space);
}
