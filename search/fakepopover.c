struct myPopover {
	GtkWidget *popover;
	GtkWidget *searchEntry;
	GMenuModel *items;
};

struct myPopover *newPopover(void)
{
	struct myPopover *p;
	
	p = g_new0(struct myPopover, 0);
	p->items = getMyModel();
	p->popover = gtk_popover_menu_new_with_model(p->items);
	p->searchEntry = gtk_search_entry_new();
	// pack the search entry in here
	g_signal_connect(p->searchEntry, "changed", G_CALLBACK(search), p);
	// ...
	return p;
}

static void search(GtkSearchEntry *e, gpointer data)
{
	struct myPopover *p = (struct myPopover *) data;
	
	// ...
}
