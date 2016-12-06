typedef struct _fs_mhash {
    fs_lockable_t hf;       /* this must be first */
    int32_t mh_size;        /* implementation-specific data */
    int32_t mh_count;
    int32_t mh_search_dist;
} fs_mhash;
#define mh_fd hf.fd         /* convenience macros for accesing */
#define mh_flags hf.flags   /* common lockable file structure  */
#define mh_filename hf.filename  /* members */
#define mh_read_metadata hf.read_metadata
#define mh_write_metadata hf.write_metadata
