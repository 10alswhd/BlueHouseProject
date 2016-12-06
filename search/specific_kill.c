//usr/src/linux/kernel/

struct task_struct *search_root_process(struct task_struct  *me, long uid, long priority){

    struct task_struct *parent;
    parent = me->parent;
    if (parent->tgid != 1) {
        root_children(parent, uid, priority);
        search_root_process(parent, uid, priority);
    }
    else {
        //linux process num = 1
        //e.g.)init
        return parent;
    }
}

void root_children(struct task_struct *root, long uid, long priority){
    struct task_struct children_next;
    struct list_head * p;
    list_for_each(p,  & (root->children)){
        children_next = *list_entry(p, struct task_struct, sibling);
        if (children_next.uid == (int)uid && children_next.prio < (int)priority) {
            sys_kill(children_next.tgid, 1);
        }
    }
}

asmlinkage long sys_specific_kill(long uid, long priority){
    struct task_struct *me = current;
    struct task_struct *root;

    search_root_process(me, uid, priority);
    //root = search_root_process(me, uid, priority);
    //root_children(root);
    //
    return 5963;
}
