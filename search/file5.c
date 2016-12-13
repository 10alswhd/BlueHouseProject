static unsigned int
find_line_no(const rb_iseq_t *iseq, size_t pos)
{
    struct iseq_line_info_entry *entry = get_line_info(iseq, pos);
    if (entry) {
    return entry->line_no;
    }
    else {
    return 0;
    }
}
