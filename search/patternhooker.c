//  patternhooker.c
//  PatternHooker
//
//  Finds a function by searching for a byte pattern and hooks it with CydiaSubstrate.
//
//  Created by C0deH4cker on 7/26/15.
//  Copyright (c) 2015 C0deH4cker. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <mach-o/loader.h>
#include <CydiaSubstrate/CydiaSubstrate.h>

/* Get the next load command from the current one */
#define NEXTCMD(cmd) (struct load_command*)((char*)(cmd) + (cmd)->cmdsize)

/* Iterate through all load commands */
#define ITERCMDS(i, cmd, cmds, ncmds) for(i = 0, cmd = (cmds); i < (ncmds); i++, cmd = NEXTCMD(cmd))

/* Represents a region of memory */
typedef struct MemoryRegion {
	void* data;
	size_t size;
} MemoryRegion;

/* Array of executable code segments */
typedef struct CodeSegments {
	MemoryRegion* regions;
	size_t count;
} CodeSegments;


/* Looks for a pattern of bytes in the specified memory region */
static void* findPattern(const MemoryRegion* region, const void* pattern, size_t pattern_length) {
	return memmem(region->data, region->size, pattern, pattern_length);
}

/* Returns an array of code segments in the Mach-O, or NULL on error */
static bool getCodeSegments(struct mach_header* mh, CodeSegments* segs) {
	segs->count = 0;
	segs->regions = NULL;
	
	bool is64bit = false;
	uint32_t i, ncmds;
	struct load_command* cmd, *cmds;
	
	/* Parse mach_header to get the first load command and the number of commands */
	if(mh->magic != MH_MAGIC) {
		if(mh->magic == MH_MAGIC_64) {
			is64bit = true;
			struct mach_header_64* mh64 = (struct mach_header_64*)mh;
			cmds = (struct load_command*)&mh64[1];
			ncmds = mh64->ncmds;
		}
		else {
			fprintf(stderr, "Invalid magic number: %08X\n", mh->magic);
			return false;
		}
	}
	else {
		cmds = (struct load_command*)&mh[1];
		ncmds = mh->ncmds;
	}
	
	size_t numexec = 0;
	
	/* First iteration for counting executable segments */
	ITERCMDS(i, cmd, cmds, ncmds) {
		/* Make sure we don't loop infinitely */
		if(cmd->cmdsize == 0) {
			break;
		}
		
		switch(cmd->cmd) {
			case LC_SEGMENT: {
				struct segment_command* seg = (struct segment_command*)cmd;
				if(seg->initprot & VM_PROT_EXECUTE) {
					++numexec;
				}
				break;
			}
			
			case LC_SEGMENT_64: {
				struct segment_command_64* seg = (struct segment_command_64*)cmd;
				if(seg->initprot & VM_PROT_EXECUTE) {
					++numexec;
				}
				break;
			}
		}
	}
	
	MemoryRegion* regions = malloc(numexec * sizeof *regions);
	if(!regions) {
		return false;
	}
	
	size_t current_segment = 0;
	
	/* Second iteration for adding segments to the return array */
	ITERCMDS(i, cmd, cmds, ncmds) {
		if(current_segment == numexec) {
			/* Already added last segment */
			break;
		}
		
		/* Make sure we don't loop infinitely */
		if(cmd->cmdsize == 0) {
			break;
		}
		
		switch(cmd->cmd) {
			case LC_SEGMENT: {
				struct segment_command* seg = (struct segment_command*)cmd;
				if(seg->initprot & VM_PROT_EXECUTE) {
					MemoryRegion* cur = &regions[current_segment++];
					cur->data = (void*)(uintptr_t)seg->vmaddr;
					cur->size = seg->vmsize;
				}
				break;
			}
				
			case LC_SEGMENT_64: {
				struct segment_command_64* seg = (struct segment_command_64*)cmd;
				if(seg->initprot & VM_PROT_EXECUTE) {
					MemoryRegion* cur = &regions[current_segment++];
					cur->data = (void*)(uintptr_t)seg->vmaddr;
					cur->size = seg->vmsize;
				}
				break;
			}
		}
	}
	
	if(current_segment != numexec) {
		/* Something very wrong happened... */
		free(regions);
		return false;
	}
	
	segs->regions = regions;
	segs->count = numexec;
	return true;
}

/* Example hook body */
typedef struct Level Level;
MSHook(void, Level$$setTileNoUpdate, Level* level, int x, int y, int z, int newTile) {
	/* Prevent all blocks from breaking or going away in any other way */
	if(newTile == 0) {
		/* Better be careful placing blocks ;) */
		return;
	}
	
	/* Call original */
	_Level$$setTileNoUpdate(level, x, y, z, newTile);
}

MSInitialize {
	struct mach_header* mh = MSFindSymbol(NULL, "__mh_execute_header");
	if(!mh) {
		/* Weird, couldn't find this program's header... */
		return;
	}
	
	CodeSegments segs;
	if(!getCodeSegments(mh, &segs)) {
		/* Couldn't get array of code segments? */
		return;
	}
	
	/* Replace this with the pattern to search for */
	const char pattern[] = "\xDE\xAD\xBE\xEF";
	size_t pattern_length = sizeof(pattern) - 1;
	
	/* Iterate over all segments containing executable code and search them for the pattern */
	for(size_t i = 0; i < segs.count; i++) {
		void* found = findPattern(&segs.regions[i], pattern, pattern_length);
		if(found) {
			MSHookFunction(found, MSHake(Level$$setTileNoUpdate));
			break;
		}
	}
}
