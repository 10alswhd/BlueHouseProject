/*
 *  Copyright (c) 2016 Ryan McCullagh <me@ryanmccullagh.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <string.h>
#include <stdio.h>
#include <unistd.h>

/*
 * Search for sub in source and return the index
 * in source where sub starts. If not found, return -1
 */
static ssize_t buffer_find(const char *source, const char *sub)
{
	size_t i;
	size_t j = 0;
	ssize_t retval = -1;
	size_t sourcelen = strlen(source);
	size_t sublen = strlen(sub);

	for(i = 0; i < sourcelen; i++) {
		const char *start = source + i;
		const char *end = source + sourcelen;
		/*
		 * if the current position + the length of sub
		 * would go to the null byte or greater, we're done
		 */
		if(i + sublen >= sourcelen) {
			break;
		} else {
			/*
			 * if the current char in source is equal to the first char in sub
			 */
			if(*start == *sub) {
				while(start != end && j < sublen) {
					if(*start != sub[j++]) {
						retval = -1;
						goto done;	
					}
					start++;
				}
				retval = (ssize_t)i;
				goto done;
			}
		}
	}

done:
	return retval;
}

int main(void)
{
	const char *source = "first|last";
	const char *sep = "|";

  /* 5 */	
	ssize_t index = buffer_find(source, sep);

	if(index == -1) {
		printf("-1\n");
	} else {
		printf("%zu\n", (size_t)index);
	}

	return 0;
}
