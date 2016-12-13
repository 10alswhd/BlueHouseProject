void
rb_bug(const char *fmt, ...)
{
    const char *file = NULL;
    int line = 0;

    if (GET_THREAD()) {
    file = rb_sourcefile();
    line = rb_sourceline();
    }

    report_bug(file, line, fmt, NULL);

    die();
}
