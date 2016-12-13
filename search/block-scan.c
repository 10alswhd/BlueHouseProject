/*
 * block-scan.c
 * Extremely fast low-level binary file string matching. Excellent for searching large files quickly for matches.
 * Compiling
 * gcc -o bs block-scan.c
 *
 * Usage
 * bs <filepath> <blocksize> <search string>
 *
 * Example
 * ./bs samplefile.h5 4096 "GCOL"
 *
 *  Copyright 2013 Luke Campbell
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define OFF_MIN(x,y) (x < y ? x : y)
#define OFF_MAX(x,y) (x > y ? x : y)

void print_help(void);
ssize_t search_block(const char *reference_string, const char *block, size_t len);
size_t readblock(int fd, char *block, size_t blocksize);
int scanfile(const char *filepath, const char *reference_string, size_t blocksize);
size_t dump_buffer(const char *block, size_t blocksize, size_t file_offset);
ssize_t block_match(const char *needle, size_t needle_size, const char *haystack, size_t haystack_size);

static int verbose=0;

int main(int argc, char *argv[])
{
    const char *reference_block;
    const char *filepath;
    size_t blocksize=0;
    size_t offset;

    printf("Block Scan V0\n");
    if(argc < 4) {
        print_help();
        return 1;
    }
    if(argc > 4 && !strcmp("-v", argv[4])) {
        verbose=1;
    }
        

    filepath = argv[1];
    blocksize = atoi(argv[2]);
    reference_block = argv[3];
    if(blocksize < 0 || blocksize > 8192) {
        printf("Invalid blocksize, must be between 0 and 8192");
        return 2;
    }

    return scanfile(filepath, reference_block, blocksize);

}

int scanfile(const char *filepath, const char *reference_string, size_t blocksize) {
    char *mblock;
    int fd;
    size_t bytes_read=0;
    size_t overlap;
    size_t block_offset=0;
    ssize_t sstr;
    off_t file_offset=0;
    mblock = malloc(blocksize);
    if(mblock == NULL) {
        free(mblock);
        perror(NULL);
        return 1;
    }

    overlap = strlen(reference_string)-1;

    /* Open the file */
    fd = open(filepath, O_RDONLY);
    if(fd < 0) {
        free(mblock);
        perror(NULL);
        return 1;
    }

    /* Scan each block for the string, overlap each block a little bit */
    do { 
        if(verbose) { 
            printf("Current File Offset: %u\n", (unsigned int)file_offset);
        }

        bytes_read = readblock(fd, mblock, blocksize);
        if(verbose) {
            printf("Read %lu bytes\n", bytes_read);
        }

        block_offset=0;
        do { 
            sstr = search_block(reference_string, mblock + block_offset, bytes_read - block_offset);

            if(sstr >= 0) {
                printf("Found instance @ 0x%08x\n", (unsigned int)(file_offset + sstr + block_offset));
                
                /* Dump the block +/- 8 */
                dump_buffer(mblock + OFF_MAX(sstr-8,0), OFF_MIN(strlen(reference_string)+16, bytes_read), file_offset + OFF_MAX(sstr-16,0));

                block_offset += sstr + 1;
            }
        } while(sstr >= 0 && block_offset < bytes_read);

        
        /* Only overlap if we reached the end of the block */
        if(bytes_read == blocksize) {
            file_offset = lseek(fd, -overlap, SEEK_CUR);
            if(file_offset < 0) {
                free(mblock);
                perror(NULL);
                if(close(fd) < 0) {
                    perror(NULL);
                }
                return 1;
            }
        }


    } while(bytes_read > 0);

    


    free(mblock);
    if(close(fd) < 0) {
        perror(NULL);
        return 1;
    }
    return 0;
}

size_t readblock(int fd, char *block, size_t blocksize) {
    ssize_t bytes_read=-1;
    size_t offset=0;
    while(offset < blocksize) {
        bytes_read = read(fd, block+offset, blocksize);
        offset += bytes_read;
        if(bytes_read < 0) {
            perror(NULL);
            return 0;
        } else if(bytes_read == 0) { /* End of file */
            return offset;
        }
    }
    return offset;
}


void print_help() {
    printf("Usage: blockscan <file> <blocksize> <string> [-v]\n");
    printf(" -v Verbose scanning\n");
}

ssize_t search_block(const char *reference_string, const char *block, size_t len) {
    ssize_t i = block_match(reference_string, strlen(reference_string), block, len);
    if(verbose) {
        printf("Checking block (%lu) for %s\n", len, reference_string);
        printf("Haystack: \n");
        dump_buffer(block, len, 0);
    }
    if(i>0) {
        if(verbose) { 
            printf("Found!\n");
        }
        return i;
    }
    return -1;
}

ssize_t block_match(const char *needle, size_t needle_size, const char *haystack, size_t haystack_size) {
    int i=0;
    size_t haystack_offset=0;

    /* Any zeros or nulls, can't search */
    if(!(needle && needle_size && haystack && haystack_size)) { 
        return -1;
    }

    /* If the needle can't fit in the haystack, then it can't be here */
    if(needle_size > haystack_size) { 
        return -1;
    }

    do {

        /* Find the first occurrence of the first char */
        const char *ptr = memchr(haystack + haystack_offset, needle[0], haystack_size - haystack_offset); 
        if(ptr == NULL) {
            return -1;
        }

        haystack_offset = ptr - haystack;

        /* The needle couldn't possibly be here */
        if((haystack_size - haystack_offset) < needle_size) { 
            return -1;
        }

        /* Compare each char of the needle to see if it matches the block */
        for(i=0;i<needle_size;i++) {
            if(*(haystack + haystack_offset + i) != needle[i]) {
                /* If it's not a match then break the loop */
                break;
            }
        }
        if(i == needle_size) {
            /* We made it to the end of the for-loop, implying that it matched fully */
            return haystack_offset;
        }
        haystack_offset++;
    } while(haystack_offset < haystack_size);


    return -1;
}

        




size_t dump_buffer(const char *block, size_t blocksize, size_t file_offset) {
    size_t offset = 0;
    int i;
    for(offset=0;offset<blocksize;offset+=8) {
        printf("0x%08lx ", (unsigned long int)offset + file_offset);
        for(i=0;i<8 && (offset+i)<blocksize;i++) {
            printf("%02x ", (unsigned int)(unsigned char)block[offset+i]);
        }
        for(;i<8;i++) {
            printf("   ");
        }
        for(i=0;i<8 && (offset+i)<blocksize;i++) {
            char c = block[offset+i];
            if((c >= 65 && c <= 90) || (c >=97 && c <= 123)) {
                printf("%c", c);
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
    return offset;
}
