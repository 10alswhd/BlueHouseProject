#include "FastLineReader.h"

// POSIX
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

// C++ STD
#include <iostream>
#include <cstring>
using namespace std;

int fastLineParser(const char * const filename, void (*callback)(const char * const, const char * const))
{
	int fd = open(filename, O_RDONLY); // open file
	if (fd == -1)
	{
		cerr << "Could not open \"" << filename << "\" for reading (" << strerror(errno) << ")." << endl;
		return -1;
	}

	struct stat fs;
	if (fstat(fd, &fs) == -1)
	{
		cerr << "Could not stat \"" << filename << "\" for reading (" << strerror(errno) << ")." << endl;
		close(fd);
		return -1;
	}

	posix_fadvise(fd,0,0,1); // announce the desire to sequentialy read this file
	// silent error handling - weak error

	char *buf = static_cast<char*>(mmap(0, static_cast<size_t>(fs.st_size), PROT_READ, MAP_SHARED, fd, 0));
	if (buf == MAP_FAILED)
	{
		cerr << "Could not memory map file \"" << filename << "\" (" << strerror(errno) << ")." << endl;
		close(fd);
	return -1;
	}

	char *buff_end = buf + fs.st_size;
	char *begin = buf, *end = NULL;

	// search for newline in the remainder in the file
	while ((end = static_cast<char*>(memchr(begin,'\n',static_cast<size_t>(buff_end-begin)))) != NULL)
	{
		callback(begin,end);

		if (end != buff_end)
			begin = end+1;
		else
			break;
	}

	// enable if you are working with malformed text files, proper text file needs to end with a newline
	#ifdef MALFORMED_TEXFILE
	callback(begin,buff_end);
	#endif

	munmap(buf, static_cast<size_t>(fs.st_size));
	// silent error handling - weak error

	close(fd);
	return 0;
}
