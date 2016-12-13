/*
On Tue, Sep 30, 2008 at 6:52 AM, Austin English <austinenglish at gmail.com> wrote:
> On Mon, Sep 29, 2008 at 3:39 PM, Mark Wagner <carnildo at gmail.com> wrote:
>> What's the best way for an application to detect that it's running under Wine?
>>
>> As part of the installation process, under Windows our program does a
>> full-disk search of all local hard drives, but ignoring network drives
>> and removable media.  Under Wine, this doesn't work too well, as
>> there's not a one-to-one mapping between disks and drive letters, and
>> there's usually at least one way to access the entire *nix filesystem.
>>  If someone's got a few network drives mounted, the installer could
>> spend hours searching them.
>>
>> --
>> Mark Wagner
>>
>>
>>
>
> Easiest way is probably searching for wine specific registry keys.
>
>
Easier still would be checking for wine_get_version in ntdll...
*/

#include <windows.h>
#include <stdio.h>
int main(void)
{
  static const char * (CDECL *pwine_get_version)(void);
  HMODULE hntdll = GetModuleHandle("ntdll.dll");
  if(!hntdll)
    {
      puts("Not running on NT.");
      return 1;
    }
  pwine_get_version = (void *)GetProcAddress(hntdll, "wine_get_version");
  if(pwine_get_version)
    {
      printf("Running on Wine... %s\n",pwine_get_version());
    }
  else
    {
      puts("did not detect Wine.");
    }
  return 0;
}

/*
jeffz at genera:~$ i586-mingw32msvc-gcc detect.c -o detect.exe
jeffz at genera:~$ ~/git/wine/wine detect.exe
Running on Wine... 1.1.5
Jeff
*/
