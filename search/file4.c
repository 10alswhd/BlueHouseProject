unsigned int
rb_iseq_line_no(const rb_iseq_t *iseq, size_t pos)
{
    if (pos == 0) {
    return find_line_no(iseq, pos);
    }
    else {
    return find_line_no(iseq, pos - 1);
    }
}
