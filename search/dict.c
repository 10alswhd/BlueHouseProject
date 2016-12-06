#import <CoreFoundation/CoreFoundation.h>
#import <CoreServices/CoreServices.h>

int main(int argc, char *argv[]) {
    if (argc < 2)
        return 1;

    for (int i = 1; i < argc; i++) {
        CFStringRef searchPhrase = CFStringCreateWithCString(NULL, argv[i], kCFStringEncodingUTF8);
        if (searchPhrase) {
            CFRange searchRange = DCSGetTermRangeInString(NULL, searchPhrase, 0);
            CFStringRef definition = DCSCopyTextDefinition(NULL, searchPhrase, searchRange);
            if (definition) {
                printf("--- definition of %s:\n", argv[i]);
                CFShow(definition);
                CFRelease(definition);
            }
            else
                printf("--- no definition found for %s\n\n", argv[i]);

            CFRelease(searchPhrase);
        }
    }

    return 0;
}
