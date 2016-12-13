inline static int
calc_lineno(const rb_iseq_t *iseq, const VALUE *pc)
{
    return rb_iseq_line_no(iseq, pc - iseq->iseq_encoded);
}

int
rb_vm_get_sourceline(const rb_control_frame_t *cfp)
{
    int lineno = 0;
    const rb_iseq_t *iseq = cfp->iseq;

    if (RUBY_VM_NORMAL_ISEQ_P(iseq)) {
    lineno = calc_lineno(cfp->iseq, cfp->pc);
    }
    return lineno;
}
