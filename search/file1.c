const char *
rb_sourcefile(void)
{
    rb_thread_t *th = GET_THREAD();
    rb_control_frame_t *cfp = rb_vm_get_ruby_level_next_cfp(th, th->cfp);

    if (cfp) {
    return RSTRING_PTR(cfp->iseq->location.path);
    }
    else {
    return 0;
    }
}

int
rb_sourceline(void)
{
    rb_thread_t *th = GET_THREAD();
    rb_control_frame_t *cfp = rb_vm_get_ruby_level_next_cfp(th, th->cfp);

    if (cfp) {
    return rb_vm_get_sourceline(cfp);
    }
    else {
    return 0;
    }
}
