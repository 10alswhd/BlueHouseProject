#include <CoreFoundation/CoreFoundation.h>
#include <IOKit/IOKitLib.h>

int main(int argc, char *argv[])
{
    io_iterator_t Iterator;
    kern_return_t err = IOServiceGetMatchingServices(kIOMasterPortDefault, IOServiceMatching("IOPCIDevice"), &Iterator);
    if (err != KERN_SUCCESS)
    {
        fprintf(stderr, "IOServiceGetMatchingServices failed: %u\n", err);
        return -1;
    }
    
    for (io_service_t Device; IOIteratorIsValid(Iterator) && (Device = IOIteratorNext(Iterator)); IOObjectRelease(Device))
    {
        CFStringRef Name = IORegistryEntrySearchCFProperty(Device, kIOServicePlane, CFSTR("IOName"), kCFAllocatorDefault, kNilOptions);
        if (Name)
        {
            if (CFStringCompare(Name, CFSTR("display"), 0) == kCFCompareEqualTo)
            {
                CFDataRef Model = IORegistryEntrySearchCFProperty(Device, kIOServicePlane, CFSTR("model"), kCFAllocatorDefault, kNilOptions);
                if (Model)
                {
                    _Bool ValueInBytes = TRUE;
                    CFTypeRef VRAMSize = IORegistryEntrySearchCFProperty(Device, kIOServicePlane, CFSTR("VRAM,totalsize"), kCFAllocatorDefault, kIORegistryIterateRecursively); //As it could be in a child
                    if (!VRAMSize)
                    {
                        ValueInBytes = FALSE;
                        VRAMSize = IORegistryEntrySearchCFProperty(Device, kIOServicePlane, CFSTR("VRAM,totalMB"), kCFAllocatorDefault, kIORegistryIterateRecursively); //As it could be in a child
                    }
                    
                    if (VRAMSize)
                    {
                        mach_vm_size_t Size = 0;
                        CFTypeID Type = CFGetTypeID(VRAMSize);
                        if (Type == CFDataGetTypeID()) Size = (CFDataGetLength(VRAMSize) == sizeof(uint32_t) ? (mach_vm_size_t)*(const uint32_t*)CFDataGetBytePtr(VRAMSize) : *(const uint64_t*)CFDataGetBytePtr(VRAMSize));
                        else if (Type == CFNumberGetTypeID()) CFNumberGetValue(VRAMSize, kCFNumberSInt64Type, &Size);
                        
                        if (ValueInBytes) Size >>= 20;
                        
                        printf("%s : %lluMB\n", CFDataGetBytePtr(Model), Size);
                        
                        CFRelease(Model);
                    }
                    
                    else printf("%s : Unknown VRAM Size\n", CFDataGetBytePtr(Model));
                    
                    
                    CFRelease(Model);
                }
            }
            
            CFRelease(Name);
        }
    }
    
    return 0;
}
