#include "types.h"
#include "gdt.h"

void printf(char* str)
{
    // The memory location 0xb8000 is where graphics card reads what to display.
    uint16_t*  VideoMemory = (uint16_t*)0xb8000;

    for(int i = 0; str[i] != '\0'; ++i)
    {
        VideoMemory[i] = (VideoMemory[i] & 0xFF00) | str[i];
    }
}

typedef void (*constructor)();

// Use start_ctors as pointer to the constructor.
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;

// In this function:
// I added an & before end_ctors to fix an error if this causes issues remove it.
extern "C" void callConstructors()
{
    for(constructor* i = &start_ctors; i != &end_ctors; i++)
    {
        (*i)();
    }
}

// g++ has a different naming convention and we must tell it not to go through with said convention.
extern "C" void kernelMain(const void* multiboot_structure, uint32_t magicnumber)
{
    printf("Welcome to DevinOS!");

    GlobalDescriptorTable gdt;

    while(true);
}
