  static BOOL do_searchW(PCWSTR file, PWSTR buffer, BOOL recurse,
                       PENUMDIRTREE_CALLBACKW cb, PVOID user)
   {
    HANDLE              h;
    WIN32_FIND_DATAW    fd;
    unsigned            pos;
    BOOL                found = FALSE;
    static const WCHAR  S_AllW[] = {'*','.','*','\0'};
    static const WCHAR  S_DotW[] = {'.','\0'};
    static const WCHAR  S_DotDotW[] = {'.','.','\0'};

    pos = strlenW(buffer);
    if (buffer[pos - 1] != '\\') buffer[pos++] = '\\';
    strcpyW(buffer + pos, S_AllW);
    if ((h = FindFirstFileW(buffer, &fd)) == INVALID_HANDLE_VALUE)
        return FALSE;
    /* doc doesn't specify how the tree is enumerated...
     * doing a depth first based on, but may be wrong
     */
    do
    {
        if (!strcmpW(fd.cFileName, S_DotW) || !strcmpW(fd.cFileName, S_DotDotW)) continue;

        strcpyW(buffer + pos, fd.cFileName);
        if (recurse && (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
            found = do_searchW(file, buffer, TRUE, cb, user);
        else if (SymMatchFileNameW(buffer, file, NULL, NULL))
        {
            if (!cb || cb(buffer, user)) found = TRUE;
        }
    } while (!found && FindNextFileW(h, &fd));
    if (!found) buffer[--pos] = '\0';
    FindClose(h);

    return found;
  }
