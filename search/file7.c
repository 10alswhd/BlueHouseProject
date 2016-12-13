static struct iseq_line_info_entry *
get_line_info(const rb_iseq_t *iseq, size_t pos)
{
<中略>
  :
    return &table[i-1];
}
