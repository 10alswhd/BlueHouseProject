#include <glib.h>

#define BEGIN 100
#define END   1000

/**
 * g_array_binary_search:
 * @array: (in): A #GArray.
 * @target: (in): A pointer to the target to locate.
 * @esize: (in): The size of an element in the array.
 * @compare: (in): A #GCompareFunc for comparing elements.
 *
 * Performs a binary search on the array looking for the item that
 * matches target. @compare is a standard qsort() style compare func.
 *
 * Returns: A zero-based index into the array if successful; otherwise -1.
 * Side effects: None.
 */
static gint
g_array_binary_search (GArray        *array,
                       gconstpointer  target,
                       gint           esize,
                       GCompareFunc   compare)
{
	gint left;
	gint middle;
	gint right;
	gint cmpval;

	g_return_val_if_fail(array != NULL, -1);
	g_return_val_if_fail(compare != NULL, -1);

	if (!array->len) {
		return -1;
	}

	left = 0;
	right = array->len - 1;

	while (left <= right) {
		middle = (left + right) / 2;
		cmpval = compare(array->data + (esize * middle), target);
		if (cmpval < 0) {
			left = middle + 1;
		} else if (cmpval > 0) {
			right = middle - 1;
		} else {
			return middle;
		}
	}

	return -1;
}

static gint
cmpint (gconstpointer a,
        gconstpointer b)
{
	const gint *_a = a;
	const gint *_b = b;

	return *_a - *_b;
}

static gint
cmpdouble (gconstpointer a,
           gconstpointer b)
{
	const gdouble *_a = a;
	const gdouble *_b = b;

	return *_a - *_b;
}

gint
main (gint argc,
      gchar *argv[])
{
	GArray *ar;
	gdouble d;
	gint i;

	ar = g_array_sized_new(FALSE, FALSE, sizeof(gint), (END - BEGIN));
	for (i = 100; i < 1000; i++) {
		g_array_append_val(ar, i);
	}

#define TEST_INT(_v)                                     \
    G_STMT_START {                                       \
        gint val = _v;                                   \
        gint idx = g_array_binary_search(ar, &val,       \
                                         sizeof(gint),   \
                                         cmpint);        \
        g_print("Integer(%d) => Index(%d)\n", val, idx); \
    } G_STMT_END

	TEST_INT(512);
	TEST_INT(99);
	TEST_INT(100);
	TEST_INT(549);
	TEST_INT(550);
	TEST_INT(551);
	TEST_INT(999);
	TEST_INT(1000);

	g_array_unref(ar);
	g_print("\n");

#define TEST_DOUBLE(_v)                                     \
    G_STMT_START {                                          \
        gdouble val = _v;                                   \
        gint idx = g_array_binary_search(ar, &val,          \
                                         sizeof(gdouble),   \
                                         cmpdouble);        \
        g_print("Double(%f) => Index(%d)\n", val, idx);     \
    } G_STMT_END

	ar = g_array_sized_new(FALSE, FALSE, sizeof(gdouble), (END - BEGIN));
	for (d = 100.0; d < 1000.0; d += 1.0) {
		g_array_append_val(ar, d);
	}

	TEST_DOUBLE(512.0);
	TEST_DOUBLE(99.0);
	TEST_DOUBLE(100.0);
	TEST_DOUBLE(549.0);
	TEST_DOUBLE(550.0);
	TEST_DOUBLE(551.0);
	TEST_DOUBLE(999.0);
	TEST_DOUBLE(1000.0);

	return 0;
}
