#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static bool
_fuzzy_search(const char *needle, const char *haystack)
{
    size_t hlen = strlen(haystack);
    size_t nlen = strlen(needle);

    if (nlen > hlen) {
        return false;
    }
    if (nlen == hlen) {
        return strcmp(needle, haystack) == 0;
    }

    for (size_t i = 0, j = 0; i < nlen; ++i) {
        char nch = needle[i];

        while (j < hlen) {
            if (haystack[j++] == nch) {
                goto resume;
            }
        }
        return false;

    resume: ;
    }

    return true;
}

#ifdef PY_MOD
#include <Python.h>

static PyObject *
fuzzy_search(PyObject* self, PyObject* args, PyObject *keywds)
{
    char *needle   = NULL,
         *haystack = NULL;

    static char *kwlist[] = {"needle", "haystack", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "ss", kwlist, &needle, &haystack)) {
        return NULL;
    }

    return PyBool_FromLong(_fuzzy_search(needle, haystack));
}

PyDoc_STRVAR(fuzzy_search_doc,
    "Fuzzy string search.\n"
    "Arguments: (needle, haystack)\n");

static PyMethodDef FuzzySearchMethods[] =
{
    {"fuzzy_search", (PyCFunction)fuzzy_search, METH_VARARGS | METH_KEYWORDS, fuzzy_search_doc},
    {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC
initfuzzy_search(void)
{
    (void) Py_InitModule("fuzzy_search", FuzzySearchMethods);
}

#else

int main(int argc, char *argv[])
{
    char   *needle     = NULL,
           *haystack   = NULL;
    size_t  needle_len = 0;
    ssize_t read;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <HAYSTACK>\n", argv[0]);
        return 1;
    }
    haystack = argv[1];

    while ((read = getline(&needle, &needle_len, stdin)) != -1) {
        needle[--read] = '\0';
        printf("Needle: '%s'\tHaystack: '%s'\tFound: %d\n",
               needle, haystack, _fuzzy_search(needle, haystack));
    }
    free(needle);

    return 0;
}
#endif
