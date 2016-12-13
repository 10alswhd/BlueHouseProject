#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEBUG 1
#define HASHTABLE_HASH_A 41
#define HASHTABLE_COMPRESSION_A 77
#define HASHTABLE_COMPRESSION_B 42
#define HASHTABLE_BUCKET_INITIALSIZE 2

static int allocs = 0;
static int frees = 0;

typedef struct _hashtable_bucket {
	char** key;
	void** data;
	int size;
	int count;
} hashtable_bucket;

typedef struct _hashtable {
	hashtable_bucket** data;
	double loadfactor;
	int size;
	int count;
} hashtable;

void* xmalloc(size_t n)
{
	allocs++;

	void* ptr = malloc(n);
	if (ptr == NULL) {
		perror("malloc");
		exit(0);
	}

	return ptr;
}

void* xrealloc(void* ptr, size_t n)
{
	allocs++;

	ptr = realloc(ptr, n);
	if (ptr == NULL) {
		perror("realloc");
		exit(0);
	}

	return ptr;
}

void xfree(void* ptr)
{
	frees++;
	free(ptr);
}

void hashtable_init(hashtable* hashtable, int size, double loadfactor);
void hashtable_rehash(hashtable* hashtable, int newsize);
int hashtable_search(hashtable* hashtable, char* key);
void hashtable_insert(hashtable* hashtable, char* key, void* data);
void* hashtable_get(hashtable* hashtable, char* key);
void* hashtable_delete(hashtable* hashtable, char* key);
void hashtable_free(hashtable* hashtable, void (*cleanupfunc)(void*));

void hashtable_init(hashtable* hashtable, int size, double loadfactor) 
{
	hashtable->data = (hashtable_bucket**)xmalloc(sizeof(hashtable_bucket*) * size);
	hashtable->loadfactor = loadfactor;
	hashtable->size = size;
	hashtable->count = 0;

	int i = 0;
	for (i = 0; i < size; i++) {
		hashtable->data[i] = NULL;
	}
}

void hashtable_rehash(hashtable* ht, int newsize)
{
	hashtable newtable;
	hashtable_init(&newtable, newsize, ht->loadfactor);

	int i = 0;
	for (i = 0; i < ht->size; i++) {
		hashtable_bucket* bucket = ht->data[i];
		if (bucket == NULL) {
			continue;
		}

		int j = 0;
		for (j = 0; j < bucket->count; j++) {
			if (bucket->key[j] == NULL) {
				continue;
			}

//			printf("reinserting %s\n", bucket->key[j]);
			hashtable_insert(&newtable, bucket->key[j], (void*)bucket->data[j]);
			xfree(bucket->key[j]);
		}

		xfree(bucket->key);
		xfree(bucket->data);
		xfree(bucket);
	}

	xfree(ht->data);

	memcpy(ht, &newtable, sizeof(hashtable));
}

int hashtable_search(hashtable* hashtable, char* key) 
{
	int bucket_pos = 0;
	int i = 0;
	int len = strlen(key);
	for (i = 0; i < len; i++) {
		bucket_pos += key[i] * pow(HASHTABLE_HASH_A, len - i);
	}

	bucket_pos = abs(HASHTABLE_COMPRESSION_A * bucket_pos + HASHTABLE_COMPRESSION_B) % hashtable->size;

	return bucket_pos;
}

void hashtable_insert(hashtable* hashtable, char* key, void* data) 
{
//	printf("Load factor: %0.2f\n", (double)hashtable->count/(double)hashtable->size);
	if ((double)hashtable->count/(double)hashtable->size > hashtable->loadfactor) {
//		printf("Rehashing from %d to %d.\n", hashtable->size, 2*hashtable->size);
//		hashtable_rehash(hashtable, 2*hashtable->size);
	}

	int bucket_pos = hashtable_search(hashtable, key);

	hashtable_bucket* cur;
	
	if (hashtable->data[bucket_pos] == NULL) {
		cur = (hashtable_bucket*)xmalloc(sizeof(hashtable_bucket));

		hashtable->data[bucket_pos] = cur;

		cur->size = HASHTABLE_BUCKET_INITIALSIZE;
		cur->count = 0;

		cur->key = (char**)xmalloc(sizeof(char*) * HASHTABLE_BUCKET_INITIALSIZE);
		cur->data = (void**)xmalloc(sizeof(void*) * HASHTABLE_BUCKET_INITIALSIZE);

		int i = 0;
		for (i = 0; i < HASHTABLE_BUCKET_INITIALSIZE; i++) {
			cur->key[i] = NULL;
			cur->data[i] = NULL;
		}
	} else {
		cur = hashtable->data[bucket_pos];

		if (cur->count == cur->size - 1) {
			int newsize = 2 * cur->size;

			char** newkey = (char**)xmalloc(sizeof(char*) * newsize);
			void** newdata = (void**)xmalloc(sizeof(void*) * newsize);

			int i = 0;
			for (i = 0; i < newsize; i++) {
				if (i < cur->count) {
					newkey[i] = cur->key[i];
					newdata[i] = cur->data[i];
				} else {
					newkey[i] = NULL;
					newdata[i] = NULL;
				}
			}

			xfree(cur->key);
			xfree(cur->data);

			cur->key = newkey;
			cur->data = newdata;

			cur->size = newsize;
		}
	}

	char* nkey = strdup(key);

	int i = 0;
	for (i = 0; i < cur->size; i++) {
		if (cur->key[i] == NULL) {
			cur->key[cur->count] = nkey;
			cur->data[cur->count] = data;
			break;
		}
	}

	cur->count++;
	hashtable->count++;
}

void* hashtable_get(hashtable* hashtable, char* key) 
{
	int bucket_pos = hashtable_search(hashtable, key);

	if (hashtable->data[bucket_pos] == NULL) {
		return NULL;
	}

	hashtable_bucket* cur = hashtable->data[bucket_pos];

	int i = 0;
	void* hit = NULL;
	for (i = 0; i < cur->count; i++) {
		if (strcmp(cur->key[i], key) == 0) {
			hit = cur->data[i];
			break;
		}
	}

	return hit;
}

void* hashtable_delete(hashtable* hashtable, char* key) 
{
	void* data;

	int bucket_pos = hashtable_search(hashtable, key);
	hashtable_bucket* cur = hashtable->data[bucket_pos];
//	printf("%s %d\n", key, bucket_pos);

	if (cur == NULL) {
		return;
	}

	int i = 0, j = 0;

	if (cur->count == 1) {
		hashtable->data[bucket_pos] = NULL;

		xfree(cur->key[0]);
		data = cur->data[0];

		xfree(cur->key);
		xfree(cur->data);
		xfree(cur);

		return data;
	}

	// Shrink buffer
	if (floor((double)cur->size/2) > cur->count) {
	
		int newsize =  floor((double)cur->size/2);
	//	printf("Count: %d, Previous size: %d, New size: %d\n", cur->count, cur->size, newsize);

		char** newkey = (char**)xmalloc(sizeof(char*) * newsize);
		void** newdata = (void**)xmalloc(sizeof(void*) * newsize);

		memset(newkey, (int)NULL, sizeof(char*) * newsize);
		memset(newdata, (int)NULL, sizeof(void*) * newsize);

		for (i = 0; i < cur->size; i++) {
			if (cur->key[i] == NULL) {
				continue;
			}
		
			if (strcmp(cur->key[i], key) != 0) {
				newkey[j] = cur->key[i];
				newdata[j] = cur->data[i];
				j++;
			} else {
				xfree(cur->key[i]);
				data = cur->data[i];
			}
		}

		xfree(cur->key);
		xfree(cur->data);

		cur->key = newkey;
		cur->data = newdata;

		cur->size = newsize;
	}
	else {
		for (i = 0; i < cur->size; i++) {
			if (cur->key[i] == NULL) {
				continue;
			}
		
			if (strcmp(cur->key[i], key) == 0) {
				xfree(cur->key[i]);
				data = cur->data[i];

				cur->key[i] = NULL;
				cur->data[i] = NULL;
			}
		}
	}

	cur->count--;
	hashtable->count--;

	return data;
}

void hashtable_free(hashtable* ht, void (*cleanupfunc)(void*))
{
	int i = 0;
	for (i = 0; i < ht->size; i++) {
		hashtable_bucket* bucket = ht->data[i];
		if (bucket == NULL) {
			continue;
		}

		int j = 0;
		for (j = bucket->count; j >= 0; j--) {
			if (bucket->key[j] == NULL) {
				continue;
			}

//			printf("deleting %s\n", bucket->key[j]);

			void* data = hashtable_delete(ht, bucket->key[j]);
			if (cleanupfunc != NULL) {
				cleanupfunc(data);
			}
		}
	}

	xfree(ht->data);
}

typedef struct _camember {
	char* firstname;
	char* surname;
	char* gender;
	char* pnr;
	char* date;
	char* address;
	char* zip;
	char* city;
	char* phonenr;
} camember;

void cleanup_member(void* member)
{
	if (member == NULL) {
		printf("null\n");
		return;
	}

	camember* m = (camember*)member;

	free(m->firstname);
	free(m->surname);
	free(m->gender);
	free(m->pnr);
	free(m->date);
	free(m->address);
	free(m->zip);
	free(m->city);
	free(m->phonenr);
	
	free(m);
}

int main(int argc, char** argv) 
{
	if (argc != 2) {
		printf("usage: hashtable name\n");
		return 0;
	}

	hashtable mytable;
	hashtable_init(&mytable, 1001, 0.75);

	FILE* fh = fopen("catahya_members.tab", "r");
	if (fh == NULL) {
		perror("fopen");
	}

    char byte = 0;
    int buf_size = (32 * sizeof(char)), r = 0, totalread = 0;

    char* buf = (char*)malloc(buf_size);

    memset(buf,0,buf_size);

    while (!feof(fh)) {

        if (totalread + sizeof(char) >= buf_size) {
            buf_size *= 2;
            buf = (char*)xrealloc(buf, buf_size);
        }

        r = fread(&byte, sizeof(char), 1, fh);

        if (byte == 10) {
            buf[totalread] = 0;
			if (totalread > 0) {
				char* saveptr = NULL;
				char* tok = strtok_r(buf, "\t", &saveptr);
				int i = 0;
				camember* member = (camember*)malloc(sizeof(camember));;
				memset(member, 0, sizeof(member));
				while (tok != NULL) {
					char* ctok = strdup(tok);
					switch (i) {
						case 0:
							member->firstname = ctok;
							break;
						case 1:
							member->surname = ctok;
							break;
						case 2:
							member->gender = ctok;
							break;
						case 3:
							member->pnr = ctok;
							break;
						case 4:
							member->date = ctok;
							break;
						case 5:
							member->address = ctok;
							break;
						case 6:
							member->zip = ctok;
							break;
						case 7:
							member->city = ctok;
							break;
						case 8:
							member->phonenr = ctok;
							break;
					}
					tok = strtok_r(NULL, "\t", &saveptr);
					i++;
				}

				if (i >= 8) {
					char* name = (char*)malloc((strlen(member->firstname) + strlen(member->surname) + 2) * sizeof(char));
					sprintf(name, "%s %s", member->firstname, member->surname);

					hashtable_insert(&mytable, name, member);

					free(name);
				}
			}

			free(buf);

			r = 0;
			totalread = 0;
			buf_size = (32 * sizeof(char));
			buf = (char*)malloc(buf_size);
        } else {
            buf[totalread] = byte;
        }

        totalread += r;

    }

	free(buf);
	fclose(fh);

//	char testbuffer[250];
//	scanf("%[^'\n']", testbuffer);

	printf("Looking up: %s\n", argv[1]);

	camember* member = (camember*)hashtable_get(&mytable, argv[1]);

	if (member != NULL) {
		printf("firstname: %s\n", member->firstname);
		printf("surname: %s\n", member->surname);
		printf("gender: %s\n", member->gender);
		printf("pnr: %s\n", member->pnr);
		printf("date: %s\n", member->date);
		printf("address: %s\n", member->address);
		printf("zip: %s\n", member->zip);
		printf("city: %s\n", member->city);
		printf("phonenr: %s\n", member->phonenr);
		printf("\n");
	}

	hashtable_free(&mytable, cleanup_member);

	printf("allocs/frees: %d/%d\n", allocs, frees);

	return 0;
}
