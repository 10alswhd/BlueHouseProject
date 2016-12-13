#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <WinBase.h>

// ZIP files are gross.
#pragma pack(1)
typedef struct ZipFile {
	CHAR signature[4]; /* for local file header, PK\x03\x04 */
	WORD version; /* don't care. */
	WORD flags; /* don't care (yet?) */
	WORD method; /* don't care (yet?) */
	WORD modtime;
	WORD moddate; /* modtime and moddate are DOS format times. */
	DWORD crc32;
	DWORD packedSize;
	DWORD size;
	WORD fnLength; /* Length of the filename. Filename comes directly afer this struct. */
	WORD extraLength; /* Length of the extra data fields. This comes directly after the filename. */
} ZipFile;

// I'm throwing up already.
void print_error() {
	LPVOID lpBuffer;

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS, NULL,
		GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR) &lpBuffer, 0, NULL);
	printf("error: %s", lpBuffer);
	LocalFree(lpBuffer);
}

// Verify that we're pointing at an actual zip file entry.
BOOL validate_zipfile_entry(ZipFile* zf) {
	if (zf->signature[0] != 'P' || zf->signature[1] != 'K' ||
		zf->signature[2] != 3 || zf->signature[3] != 4) {
		printf("info: next entry was not a valid local ZIP file header.\n");
		printf("info: got: %s\n", zf->signature);
		return FALSE;
	}

	return TRUE;
}

// Look for file entries.
void search_zipfile(LPVOID base, SIZE_T size) {
	DWORD offset = 0, count = 0;

	while (offset < size) {
		ZipFile *file = (ZipFile*) (base + offset);
		if (!validate_zipfile_entry(file)) {
			printf("    at offset 0x%08x\n", offset);
			break;
		}

		CHAR name[file->fnLength + 1];
		memcpy(name, file + 1, file->fnLength);
		name[file->fnLength] = 0;

		printf("File: \"%s\"\n", name);
		printf("    Unpacked size: %d bytes\n", file->size);
		printf("\n");

		count++;
		offset += sizeof(ZipFile) + file->fnLength + file->extraLength + file->packedSize;
	}

	printf("info: found %d files.\n", count);
}

DWORD main(DWORD argc, CHAR *argv[]) {
	// Check for file name.
	if (argc < 2) {
		printf("error: please provide a file name.\n");
		return 0;
	}

	// Call CreateFile to get a file handle.
	HANDLE hZipFile = CreateFile(argv[1], GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	if (hZipFile == INVALID_HANDLE_VALUE) {
		print_error();
		return -1;
	}

	// Now try to create a memory map object.
	HANDLE hZipMap = CreateFileMapping(hZipFile, NULL,
		PAGE_READONLY, 0, 0, NULL);
	if (hZipMap == NULL) {
		print_error();
		return -1;
	}

	// Now try to memory-map the entire file.
	LPVOID zipFileBase = MapViewOfFile(hZipMap, FILE_MAP_READ, 0, 0, 0);

	// Get the size of the file.
	MEMORY_BASIC_INFORMATION zipFileInfo;
	if (!VirtualQuery(zipFileBase, &zipFileInfo, sizeof(MEMORY_BASIC_INFORMATION))) {
		print_error();
		return -1;
	}

	// Printing things to console makes it look like you're hacking things.
	DWORD zipFileSize = zipFileInfo.RegionSize;
	printf("ZIP file size: %d bytes.\n", zipFileSize);
	printf("ZIP file mapping starts at: 0x%08x\n\n", zipFileBase);

	// Now search for local file headers.
	search_zipfile(zipFileBase, zipFileSize);

	// Close file handles.
	UnmapViewOfFile(zipFileBase);
	CloseHandle(hZipMap);
	CloseHandle(hZipFile);
	
	return 0;
}
