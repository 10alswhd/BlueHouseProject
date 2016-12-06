/* Obtenemos el nombre del dispositivo. Este es el nombre que suele poner el fabricante y en el caso de los discos duros 
 * existe de todo: Flash Disk, DISK, Mass Storage, etc. OJO! No es el mismo nombre que el nombre del volumen que es el 
 * nombre que aparece cuando montamos la unidad en el sistema operativo 
 */
if (IORegistryEntryGetName(device, devicename) != KERN_SUCCESS) {
  fprintf(stderr, "%s unknown device (unable to get device name)\n", newdev ? "Added " : " Removed");
  return -1;
}

/* Obtenemos el EntryPath, que indica dónde está en el sistema operativo
 * Ejemplo: IOService:/AppleACPIPlatformExpert/PCI0@0/AppleACPIPCI/EHC2@1A/AppleUSBEHCI/Mass Storage
 */
if (IORegistryEntryGetPath(device, kIOServicePlane, entrypath) != KERN_SUCCESS) {
  fprintf(stderr, "\tUnable to get the entrypath\n");
  return -1;
}

/* Obtenemos el tipo de dispositivo
 * Ejemplo: IOUSBDevice
 */
if (IOObjectGetClass(device, classname) != KERN_SUCCESS) {
  fprintf(stderr, "\tUnable to get the classname\n");
  return -1;
}

/* Obtenemos el vendor name, aunque no siempre existe
 * Ejemplos: Generic, USB, Apple Inc., etc.
 */
CFStringRef vendorname = (CFStringRef) IORegistryEntrySearchCFProperty(device
      , kIOServicePlane
      , CFSTR("USB Vendor Name")
      , NULL
      , kIORegistryIterateRecursively | kIORegistryIterateParents);
   
/* Obtenemos el serial number aunque no está disponible para todos los dispostivos USB */
CFTypeRef serialnumber = (CFTypeRef) IORegistryEntrySearchCFProperty(device
      , kIOServicePlane
      , CFSTR("USB Serial Number")
      , NULL
      , kIORegistryIterateRecursively | kIORegistryIterateParents);
                           
/* Nos indica si el dispositivo se puede quitar o no */
CFTypeRef isremovable = (CFTypeRef) IORegistryEntrySearchCFProperty(device
      , kIOServicePlane
      , CFSTR( kIOMediaEjectableKey )
      , NULL
      , kIORegistryIterateRecursively | kIORegistryIterateParents);
   
/* En algunos dispositivos USB opdemos obtener el tamaÃ±o del volÃºmen */
CFTypeRef disksize = (CFTypeRef) IORegistryEntrySearchCFProperty(device
      , kIOServicePlane
      , CFSTR( kIOMediaSizeKey )
      , NULL
      , kIORegistryIterateRecursively | kIORegistryIterateParents);

if (disksize) {
  if ( CFNumberGetValue((CFNumberRef)disksize, kCFNumberSInt32Type, &amp;l_disksize) == 0) {
    fprintf(stderr, "Error converting disksize to a long number\n");
    return -1;
  }
}

/* Obtenemos el vendorID */
CFNumberRef vendorId = (CFNumberRef) IORegistryEntrySearchCFProperty(device
      , kIOServicePlane
      , CFSTR("idVendor")
      , NULL
      , kIORegistryIterateRecursively | kIORegistryIterateParents);

/* Obtenemos el productId */
CFNumberRef productId = (CFNumberRef) IORegistryEntrySearchCFProperty(device
      , kIOServicePlane
      , CFSTR("idProduct")
      , NULL
      , kIORegistryIterateRecursively | kIORegistryIterateParents);
