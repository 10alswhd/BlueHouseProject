fs_lockable_t *mh = fs_mhash_open(...);

/*
 * example of a safe looping read operation
 */
if (fs_lockable_lock(mh, LOCK_SH) {
    handle_error();
    return;
}
for (i=0; i<something; i++)
    fs_mhash_read_operation_r(mh, ...);
if (fs_lockable_lock(mh, LOCK_UN)) {
    handle_error();
    return;
}

/* 
 * example of a safe looping write operation
 */
if (fs_lockable_lock(mh, LOCK_EX)) {
    handle_error();
    return;
}

/* assert not necessary here, illustration only */
assert(fs_lockable_test(mh, LOCK_EX));

for (i=0, i<something; i+)
    fs_mhash_write_operation(mh, ...);

if (fs_lockable_lock(mh, LOCK_UN)) {
    handle_error();
    return;
}
