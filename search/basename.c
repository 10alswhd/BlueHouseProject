/* This function gets the base name of a file, including the extension. Note that if the string passed to this function is modified, it messes with the result, so if you need to modify the source string you need to strdup() (malloc(+1) and strcpy()) the return value. You can use this for whatever the heck you want, but if it is a life-saver, please mention me somewhere. =) */

/* this gets the strrchr() function */
#include <string.h>

/* this is your platform's directory separator */
#define DIRSEP '/'

const char *
get_base_name (const char *name)
{
  const char *base_name = strrchr (name, DIRSEP); /* search for the directory separator */
  if (base_name) /* found it, return the string from one past it */
    {
      ++base_name;
      return base_name;
    }
  return name; /* no directory separator; processing not necessary */
}
