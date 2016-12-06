#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define HASH_SIZE 13

typedef enum 
{
	Term, Insert, Delete, SearchByName, Dump
} Menu;

typedef enum 
{
	Occupied, Empty, Deleted

} Status;

typedef struct __data
{
	char name[10];

} Data;

typedef struct __bucket
{
	Data data;
	Status stat;

} Bucket;

typedef struct __hash
{
	int size;
	Bucket *table;

} Hash;

int hash ( char* key )
{
	int hash_value = 0;

	while ( *key != '\0' )
		hash_value += *key++;

	return hash_value % HASH_SIZE;
}

int rehash ( int key )
{
	return ( key + 1 ) % HASH_SIZE;
}

void set_bucket ( Bucket* n, Data x, Status stat )
{
	n -> data = x;
	n -> stat = stat;
}

int init_hash ( Hash* h, int size )
{
	h -> size = 0;

	if ( ( h->table = calloc ( size, sizeof( Bucket ) ) ) == NULL )
		return 0;

	// メモリ確保に成功したらメモリサイズを書き換え．
	h -> size = size;
	
	int i;
	for ( i = 0; i < size; i++ )
		h -> table[i].stat = Empty;

	return 1;
}

void term_hash ( Hash* h )
{
	free ( h -> table );
}

Bucket *search_bucket ( Hash* h, Data x )
{
	int key = hash ( x.name );
	Bucket* p = &h->table[key];

	int i;
	for ( i = 0; ( p->stat !=Empty ) && ( i < h->size ); i++ )
	{
		if ( p->stat == Occupied && strcmp ( p->data.name, x.name ) == 0 )
			return p;
		key = rehash ( key );
		p = &h->table[key];
	}

	return NULL;
}

int insert_bucket ( Hash* h, Data x )
{
	int key = hash ( x.name );
	Bucket *p = &h->table[key];

	if ( search_bucket ( h, x ) )
		return 1;

	int i;
	for ( i = 0; i < h->size; i++ )
	{
		if ( p->stat == Empty || p->stat == Deleted )
		{
			set_bucket ( p, x, Occupied );
			return 0;
		}
		key = rehash ( key );
		p = &h->table[key];
	}

	return 2;
}

int delete_bucket ( Hash* h, Data x )
{
	Bucket* p = search_bucket ( h, x );

	if ( p == NULL )
		return 1;

	p -> stat = Deleted;

	return 0;
}

void DumpHash ( Hash* h )
{
	int i;

	for ( i = 0; i < h->size; i++ )
	{
		printf ( "%02d  ", i );

		switch ( h->table[i].stat )
		{
			case Occupied:
				printf ( "(%s)\n", h->table[i].data.name );
				break;
			case Empty:
				printf ( "-----Empty-----\n" ); break;
			case Deleted:
				printf ( "-----Deleted------\n" ); break;
		}
	}
}

void print_data ( Data x )
{
	printf ( "%s\n", x.name );
}

Data read ( char* msg, int sw )
{
	Data tmp;

	printf ( "write %s data \n", msg );

	if ( sw )
	{
		printf ( "name: " );
		scanf ( "%s", tmp.name );
	}

	return tmp;
}

Menu select_menu ( void )
{
	int i, ch;

	do
	{
		printf ( "1:insert  2:delete  3:search  4:dump  0:term\n" );
		scanf ( "%d", &ch );
	}
	while ( ch < Term || ch > Dump );

	return ( ( Menu ) ch );
}

int main ( void )
{
	Menu menu;
	Hash hash;

	init_hash ( &hash, HASH_SIZE );

	do
	{
		int result;
		Data x;
		Bucket* tmp;
		menu = select_menu ();

		switch ( menu )
		{
			case Insert:
				x = read ( "insert", 1 );
				result = insert_bucket ( &hash, x );
				if ( result )
					printf ( "failed to insert\n");
				break;
			case Delete:
				x = read ( "delete", 1 );
				result = delete_bucket ( &hash, x );
				break;
			case SearchByName:
				x = read ( "search", 1 );
				tmp = search_bucket ( &hash, x );
				if ( tmp == NULL )
					printf ( "failed to search\n" );
				else
				{
					printf ( "success!\n" );
					print_data ( tmp -> data );
				}
				break;
			case Dump:
				DumpHash ( &hash );
				break;
			default:
				break;
		}
	}
	while ( menu != Term );

	term_hash ( &hash );

	return 0;
}
