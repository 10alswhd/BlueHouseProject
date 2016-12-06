#include <sys/param.h>
#include <Security/Security.h>

static void displayName(const void *value, void *context)
{
    SecKeychainRef keychain = (SecKeychainRef) value;
    UInt32 pathLength = MAXPATHLEN;
    char pathName[MAXPATHLEN + 1];
    SecKeychainGetPath(keychain, &pathLength, pathName);
    printf("    \"%*s\"\n", (int)pathLength, pathName);
}

int main() {
    CFArrayRef searchList = NULL;
    SecKeychainCopySearchList(&searchList);
    CFRange range = { 0, CFArrayGetCount(searchList) };
    CFArrayApplyFunction(searchList, range, displayName, NULL);
    return 0;
}
