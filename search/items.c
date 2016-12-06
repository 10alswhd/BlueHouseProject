if ((search->exptime != 0 && search->exptime < current_time)
    || (search->time <= oldest_live && oldest_live <= current_time)) {
    itemstats[id].reclaimed++;
    if ((search->it_flags & ITEM_FETCHED) == 0) {
        itemstats[id].expired_unfetched++;
    }
    it = search;
    slabs_adjust_mem_requested(it->slabs_clsid, ITEM_ntotal(it), ntotal);
    do_item_unlink_nolock(it, hv);
    /* Initialize the item block: */
    it->slabs_clsid = 0;
