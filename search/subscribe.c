#include <IOKit/IOKitLib.h>
#include <CoreFoundation/CoreFoundation.h>
#include <sys/signal.h>

IONotificationPortRef nPort = NULL;

void iCleanup(int sig) {
	printf("Closing...\n");
	exit(0);
}

void iDetached(void *refcon, io_iterator_t iterator) {
	io_service_t usbDevice;
	while(usbDevice = IOIteratorNext(iterator)) {
		printf("Device detached:\n");
		
		io_name_t name;
		IORegistryEntryGetName(usbDevice, name);
		printf("\tName:\t\t%s\n", (char *)name);
		
		CFNumberRef idProduct = (CFNumberRef)IORegistryEntrySearchCFProperty(usbDevice, kIOServicePlane, CFSTR("idProduct"), kCFAllocatorDefault, 0);
		uint16_t PID;
		CFNumberGetValue(idProduct, kCFNumberSInt16Type, (void *)&PID);
		printf("\tidProduct:\t0x%x\n", PID);
		
		IOObjectRelease(usbDevice);
		CFRelease(idProduct);
	}
	
	IOObjectRelease(iterator);
}

void iAttached(void *refcon, io_iterator_t iterator) {
	io_service_t usbDevice;
	while(usbDevice = IOIteratorNext(iterator)) {
		printf("Device attached:\n");
		
		io_name_t name;
		IORegistryEntryGetName(usbDevice, name);
		printf("\tName:\t\t%s\n", (char *)name);
		
		CFNumberRef idProduct = (CFNumberRef)IORegistryEntrySearchCFProperty(usbDevice, kIOServicePlane, CFSTR("idProduct"), kCFAllocatorDefault, 0);
		uint16_t PID;
		CFNumberGetValue(idProduct, kCFNumberSInt16Type, (void *)&PID);
		printf("\tidProduct:\t0x%x\n", PID);
		
		IOObjectRelease(usbDevice);
		CFRelease(idProduct);
	}
	
	IOObjectRelease(iterator);
}

int iSubscribe(uint16_t *pids, int pid_count) {
	nPort = IONotificationPortCreate(kIOMasterPortDefault);
	CFRunLoopSourceRef pSource = IONotificationPortGetRunLoopSource(nPort);
	
	int i;
	for(i = 0; i < pid_count; ++i) {
		CFMutableDictionaryRef matching = IOServiceMatching("IOUSBDevice");
		if(matching == NULL) {
			return -1;
		}
		
		uint16_t idVendorApple = 0x05AC, PID = pids[i];
		CFNumberRef idVendor = CFNumberCreate(kCFAllocatorDefault, kCFNumberSInt16Type, &idVendorApple);
		CFNumberRef idProduct = CFNumberCreate(kCFAllocatorDefault, kCFNumberSInt16Type, &PID);
	
		CFDictionarySetValue(matching, CFSTR("idVendor"), idVendor);
		CFDictionarySetValue(matching, CFSTR("idProduct"), idProduct);
	
		CFRelease(idVendor);
		CFRelease(idProduct);
		
		CFRetain(matching);
		
		io_iterator_t attachIterator;
		if(IOServiceAddMatchingNotification(nPort, "IOServiceFirstMatch", matching, iAttached, NULL, &attachIterator) != KERN_SUCCESS) {
			return -1;
		}
		
		iAttached(NULL, attachIterator);
	
		io_iterator_t detachIterator;
		if(IOServiceAddMatchingNotification(nPort, "IOServiceTerminate", matching, iDetached, NULL, &detachIterator) != KERN_SUCCESS) {
			return -1;
		}
		
		iDetached(NULL, detachIterator);
	}
	
	CFRunLoopAddSource(CFRunLoopGetCurrent(), pSource, kCFRunLoopDefaultMode);
	
	return 0;
}

int main() {
	signal(SIGINT, iCleanup);
	
	uint16_t pids[3] = { 
		0x1281, // Recovery
		0x1222, // DFU
		0x1227, // WTF
	};
	int ret = iSubscribe(pids, 1);
	if(ret != 0) 
		exit(1);
	
	CFRunLoopRun();
}
