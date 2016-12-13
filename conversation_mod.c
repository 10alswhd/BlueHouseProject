/*
 * Search a particular hash table for a conversation with the specified
 * {addr1, port1, addr2, port2} and set up before frame_num.
 */
static conversation_t *
conversation_lookup_hashtable(GHashTable *hashtable, const guint32 frame_num, const address *addr1, const address *addr2,
    const port_type ptype, const guint32 port1, const guint32 port2)
{
	conversation_t* convo=NULL;
	conversation_t* match=NULL;
	conversation_t* chain_head=NULL;
	conversation_key key;

	/*
	 * We don't make a copy of the address data, we just copy the
	 * pointer to it, as "key" disappears when we return.
	 */
	key.addr1 = *addr1;
	key.addr2 = *addr2;
	key.ptype = ptype;
	key.port1 = port1;
	key.port2 = port2;


	DPRINT(("HASH LOOKUP"));
	DPRINT(("%s:%d %s:%d", ep_address_to_str(&key.addr1), port1, ep_address_to_str(&key.addr2), port2));

	DPRINT(("CONTAINS KEY -> %d", g_hash_table_contains(hashtable, &key)));

	chain_head = (conversation_t *)g_hash_table_lookup(hashtable, &key);

	if(chain_head != NULL)
	{
		DPRINT(("CHAIN_HEAD found -> conversation __HERE___"));
	}

	if (chain_head && (chain_head->setup_frame <= frame_num)) {
		match = chain_head;

		if((chain_head->last)&&(chain_head->last->setup_frame<=frame_num))
			return chain_head->last;

		if((chain_head->latest_found)&&(chain_head->latest_found->setup_frame<=frame_num))
			match = chain_head->latest_found;

		for (convo = match; convo && convo->setup_frame <= frame_num; convo = convo->next) {
			if (convo->setup_frame > match->setup_frame) {
				match = convo;
			}
		}
	}

    if (match)
    	chain_head->latest_found = match;

    if(match != NULL)
    {
    	DPRINT(("CONVERSATION FOUND"));
    }
    else
    {
		DPRINT(("CONVERSATION __NOT__ FOUND"));
    }

	return match;
}
