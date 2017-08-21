/*
 * Example code (adapted) from OS:TEP chapter 17, relating to Paging
 * Assumes a virtual address space of 64KB and 128KB physical addresses.
 */
#include <stdio.h> 
#include <stdlib.h> 
#include <stdint.h> 

#define VPN_MASK 0x030
#define OFFSET_MASK 0x00f
#define SHIFT 4          /* length of the offset */
#define PFN_SHIFT 4     /* length of the offset */
#define PTBR 1024       /* starting address for the physical page frame */

typedef struct __page_table_entry {
    unsigned int bits : 5;
} PTE;

uint8_t translate(uint8_t VirtualAddress);
int valid(uint8_t addr);
int can_access(uint8_t addr);
uint8_t AccessMemory(uint8_t PTEAddr);

int main(int argc, char *argv[]) 
{
    uint8_t PhysAddr;
    printf("PTE size is %lu, \n", sizeof(PTE));
    PhysAddr = translate(0b010101);
    printf("The physical address is %d\n", PhysAddr);
}

uint8_t translate(uint8_t VirtualAddress)
{
    uint8_t VPN, offset, PhysAddr, PTEAddr;
    PTE pte;
    // Extract the VPN from the virtual address
    VPN = (VirtualAddress & VPN_MASK) >> SHIFT;
    // Form the address of the page-table entry (PTE)
    printf("The virtual address number (VPN) is %d\n", VPN);
    
    PTEAddr = PTBR + (VPN * sizeof(PTE));
    // Fetch the PTE
    pte.bits = AccessMemory(PTEAddr);
    // Check if process can access the page
    if ( !(valid(pte.bits)) ) {
        /* RaiseException(SEGMENTATION_FAULT) */
        return EXIT_FAILURE;
    }
    else if (!can_access(pte.bits)) {
        /* RaiseException(PROTECTION_FAULT) */
        return EXIT_FAILURE;
    }
    else {
        // Access is OK: form physical address and fetch it
        offset = VirtualAddress & OFFSET_MASK;
        PhysAddr = (pte.bits << PFN_SHIFT) | offset;
        /* Register = AccessMemory(PhysAddr) */
    }
    return PhysAddr;
}

int valid(uint8_t addr) {
    /* everthings valid */
    return 1;
}

int can_access(uint8_t addr) {
    /* check PTE->bits */
    return 1;
}

uint8_t AccessMemory(uint8_t PTEAddr) {
    /* translate VPN to PFN in page table */
    return 0b111;
}
