#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>

struct node {
	int val;
	void *next;
};

#define Node struct node

bool boundsCheck(int min, int max, int val) {
	if ((val < min) || (val > max)) return true;
	return false;
}

Node* getNewNode(void) {
	Node *t = calloc(1, sizeof(Node)); // avoid malloc + memset
	if (t == NULL) printf("ERR: error allocating memory!");
	return t;
}

unsigned int iter(Node **start, bool verbose) {
	unsigned int i = 0;

	if (start == NULL) {
		printf("ERR: start: nullptr dereference!\n");
		return -1;
	}

	Node* _iter = *start; // start;

	while (_iter != NULL) {
		if (verbose) printf("[%d] %d --> ", i, _iter->val);
		_iter = (Node*)_iter->next;
		i += 1;
	}
	if (verbose) if (i) printf("\n");

	return i;
}

bool insert(Node **start, int pos, int val) {
	unsigned int i = 0, length = 0;

	if (start == NULL) {
		printf("ERR: start: nullptr dereference!\n");
		return false;
	}

	length = iter(start, false);

	if (boundsCheck(-1, length, pos)) {
		printf("ERR: pos out of bounds!\n");
		return false;
	}

	if (pos == -1) pos = length; // if -1, we insert at index len. (iter returns number of elements)

	Node* _iter = *start; // iterator;
	Node* _tmp  = NULL;

	if (pos == 0) {
		if (_iter == NULL) { // start not allocated :(

			_iter = getNewNode(); // allocate start here.
			if (_iter == NULL) return false; // if not able to alloc new node, stop.

			_iter->val = val;
			*start = _iter;

		} else { // we get here means start is allocated. thx op.

			if (length) { // already elements exist.

				_tmp = getNewNode(); // get new node
				if (_tmp == NULL) return false;

				_tmp->val = val; // set value
				_tmp->next = *start;
				*start = _tmp;

			} else { // create teh list.
				_iter->val = val;
			}
		} // start already allocated
	} else { // pos != 0. insertion in middle somewhere.

		while (!(_iter == NULL || i++ +1 == pos)) {
			// printf("[x%d] %d --> ", i, _iter->val);
			_iter = (Node*)_iter->next;
			// i += 1;
		} // printf("\n");

		_tmp = getNewNode();
		if (_tmp == NULL) return false;

		_tmp->val = val; // set value

		_tmp->next = _iter->next;
		_iter->next = _tmp;

	}

	return true;
} // insert

bool ll_delete(Node **start, int pos) {
	unsigned int i = 0, length = 0;

	if (start == NULL) {
		printf("ERR: start: nullptr dereference!\n");
		return false;
	}

	length = iter(start, false);

	if (!length) {
		printf("ERR: list empty!\n");
		return false;
	}

	if (boundsCheck(-1, length - 1, pos)) {
		printf("ERR: pos out of bounds!\n");
		return false;
	}

	if (pos == -1) pos = length - 1; // index value

	Node* _iter = *start; // iterator;
	Node* _tmp  = NULL;

	if (pos == 0) {
		*start = _iter->next;
		free(_iter);
	} else {

		while (!(_iter == NULL || i++ +1 == pos)) {
			_iter = (Node*)_iter->next;
			// i += 1;
		}

		// printf("\n[g%d] %d --> \n", i, _iter->val);

		/*
		* delete 2
		* 0 -> 1 -> 2
		* iter = 1
		* tmp = 2
		* iter->next = tmp->next
		* free(tmp)
		*/
		_tmp = _iter->next;
		_iter->next = _tmp->next;
		free(_tmp);


	} // pos != 0

} // ll_delete

int ll_search(Node **start, int _search) {
	unsigned int i = 0, length = 0;
	// int ret = -1;

	if (start == NULL) {
		printf("ERR: start: nullptr dereference!\n");
		return false;
	}

	length = iter(start, false);

	if (length == 0) return -1;

	Node* _iter = *start; // iterator;

	// for (i = 0; i < length; i++) {
		while (!(_iter == NULL)) {
			if (_iter->val == _search) return i;
			_iter = (Node*)_iter->next;
			i += 1;
		}
	// }
	return -1;
}

int main() {
	Node *start = NULL;
	uint8_t u_choice = 0xFF;
	int pos, val;

	while (u_choice) {
		printf("menu:\n");
		printf("\t1. insert\n");
		printf("\t2. delete\n");
		printf("\t3. display\n");
		printf("\t4. search\n");
		printf("\t0. exit\n");
		while (u_choice > 4) {
			printf("choice: ");
			while(scanf("%2" SCNu8, &u_choice) != 1); // get user choice;
		}
		printf("\n--------------------------------\n");
		if (u_choice == 1) {
			printf("insert [pos val]: ");
			while(scanf("%u", &pos) != 1); // get pos;
			while(scanf("%u", &val) != 1); // get val;
			insert(&start, pos, val);
		} else if (u_choice == 2) {
			printf("delete [pos]: ");
			while(scanf("%u", &pos) != 1); // get pos;
			ll_delete(&start, pos);
		} else if (u_choice == 3) {
			val = iter(&start, true);
			if (val == 0) printf("list empty");
		} else if (u_choice == 4) {
			printf("search [val]: ");
			while(scanf("%u", &val) != 1); // get val;
			pos = ll_search(&start, val);
			if (pos < 0)
				printf("element not found\n");
			else
				printf("element found at pos: %d\n", pos);
		}
		if (u_choice) u_choice = 0xFF; // reset choice
		fseek(stdin,0,SEEK_END); // flush stdin
		printf("\n================================\n");
	}

	while(start != NULL) ll_delete(&start, 0); // free memory before exit
	return 0;
}
