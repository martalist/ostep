/**
 * Code example of in OS:TEP:
 * "Thus, if base and bounds were arrays (with one entry per segment), 
 * the hardware would be doing something like this to obtain the 
 * desired physical address:
 * The code below has a few additions of my own. 
 */

#include <stdio.h>
#include <stdlib.h>

#define SEG_MASK 0x3000
#define SEG_SHIFT 12
#define OFFSET_MASK 0xFFF

unsigned int fetch_address(int v_addr);

unsigned int Base[] = { 32768, 34816, 4096 };
unsigned int Bounds[] = { 2048, 2048, 1024 };

int main(int argc, char *argv[])
{
    unsigned int CodeAddress, HeapAddress, PhysCodeAddr, PhysHeapAddr;
    HeapAddress= 4200;
    CodeAddress= 100;

    PhysCodeAddr= fetch_address(CodeAddress);
    printf("Physical Code Address is %d\n", PhysCodeAddr);
    PhysHeapAddr= fetch_address(HeapAddress);
    printf("Physical Heap Address is %d\n", PhysHeapAddr);

    return EXIT_SUCCESS;
}

unsigned int fetch_address(int v_addr)
{
    unsigned int Segment, Offset, PhysAddr;
    // get top 2 bits of 14-bit VA
    Segment = (v_addr & SEG_MASK) >> SEG_SHIFT;
    // now get offset
    Offset  = v_addr & OFFSET_MASK;
    if (Offset >= Bounds[Segment]) {
        fprintf(stderr, "Protection Fault\n");
        exit(EXIT_FAILURE);
    }
    else {
        PhysAddr = Base[Segment] + Offset;
    }
    return PhysAddr;
}
