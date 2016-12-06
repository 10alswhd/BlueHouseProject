struct _fs_mhash {
    int32_t size;
    int32_t count;
    int32_t search_dist;
    int fd;
    char *filename;
    int flags;
    int locked;
};
