/* from lockable.h */
typedef struct _fs_lockable_t {
    int fd;
    int flags;
    int locktype;
    char *filename;
    struct timespec mtime;
    int (*read_metadata)(struct _fs_lockable_t *hf);
    int (*write_metadata)(struct _fs_lockable_t *hf);
} fs_lockable_t;

/* implementation of read_metadata and write_metadata */
static int fs_mhash_write_header(fs_lockable_t *hf);
static int fs_mhash_read_header(fs_lockable_t *hf);
