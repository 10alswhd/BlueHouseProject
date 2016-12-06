*/


#include <CoreFoundation/CoreFoundation.h>
#include <Security/Security.h>
#include <stdio.h>
#include <stdarg.h>

void error(const char* msg) {
    fprintf(stderr, "error: %s\n", msg);
    exit(-1);
}

void check_status(OSStatus status) {
    if(status == noErr) return;
    
    CFShow(SecCopyErrorMessageString(status, NULL));
    exit(-1);
}

void write_pl(CFMutableDictionaryRef properties) {
    CFWriteStreamRef stdoutStream = NULL;
    
    CFURLRef devStdout = CFURLCreateWithFileSystemPath(
        NULL, 
        CFSTR("/dev/stdout"), 
        kCFURLPOSIXPathStyle, 
        false
    );
    
    stdoutStream = CFWriteStreamCreateWithFile(NULL, devStdout);
    if (stdoutStream == NULL)
      error("cannot create CFWriteStream for /dev/stdout");  
      
    if (!CFWriteStreamOpen(stdoutStream))
      error("cannot open CFWriteStream for /dev/stdout");
    
    CFPropertyListWrite(
      properties,
      stdoutStream,
      kCFPropertyListXMLFormat_v1_0,
      0,
      NULL
    );
    
    CFWriteStreamClose(stdoutStream);
}


int main (int argc, char const *argv[])
{
    if(argc != 2) {
        fprintf(stderr, "USAGE: %s [password]\n", argv[0]);
        exit(-1);
    }
    
    CFStringRef target = CFStringCreateWithCString (kCFAllocatorDefault, argv[1], kCFStringEncodingUTF8);
    OSStatus ok;
    
    SecKeychainSearchRef searchRef = NULL;
    ok = SecKeychainSearchCreateFromAttributes (
       NULL,
       kSecInternetPasswordItemClass,
       NULL,
       &searchRef
    );
    check_status(ok);
    
    CFMutableDictionaryRef results = CFDictionaryCreateMutable(kCFAllocatorDefault, 0, NULL, NULL);
    SecKeychainItemRef searchItem = NULL;

    while (SecKeychainSearchCopyNext(searchRef, &searchItem) != errSecItemNotFound) {
        SecKeychainAttributeList attrList;
        
        SecKeychainAttribute attrs[2];
        attrs[0].tag = kSecServerItemAttr;
        attrs[0].length = 0;
        attrs[0].data = NULL;

        attrs[1].tag = kSecAccountItemAttr;
        attrs[1].length = 0;
        attrs[1].data = NULL;
        
        attrList.count = 2;
        attrList.attr = attrs;
        
        UInt32 length = 0;
        void* data = NULL;
        
        ok = SecKeychainItemCopyContent(
            searchItem, 
            NULL, 
            &attrList,
            &length,
            &data
        );
        
        check_status(ok);
        
        CFStringRef server = CFStringCreateWithBytes(
            kCFAllocatorDefault, 
            attrs[0].data, 
            attrs[0].length, 
            kCFStringEncodingUTF8, 
            false
        );
        
        CFStringRef username = CFStringCreateWithBytes(
            kCFAllocatorDefault, 
            attrs[1].data, 
            attrs[1].length, 
            kCFStringEncodingUTF8, 
            false
        );
        
        CFStringRef password = CFStringCreateWithBytes(
            kCFAllocatorDefault, 
            data, 
            length, 
            kCFStringEncodingUTF8, 
            false
        );
        
        if(CFStringCompare(password, target, 0) == 0) {
            CFDictionaryAddValue(results, server, username);
        };
        
        SecKeychainItemFreeContent(&attrList, data);
        CFRelease(searchItem);
      }

    CFRelease(searchRef);
    write_pl(results);
    return 0;
}
