static void
select_range_button_clicked (GtkButton *button,
                             gpointer user_data)
{
    GlSearchPopoverPrivate *priv;
    GtkTreeSelection *selection;
    GEnumClass *eclass;
    GEnumValue *evalue;

    priv = gl_search_popover_get_instance_private (GL_SEARCH_POPOVER (user_data));

    gtk_stack_set_visible_child_name (GTK_STACK (priv->range_stack), "range-list");
    gtk_stack_set_visible_child_name (GTK_STACK (priv->range_label_stack), "show-log-from-label");

    gtk_stack_set_visible_child_name (GTK_STACK (priv->parameter_stack), "parameter-button");
    gtk_stack_set_visible_child_name (GTK_STACK (priv->parameter_label_stack), "what-label");

    eclass = g_type_class_ref (GL_TYPE_SEARCH_POPOVER_JOURNAL_TIMESTAMP_RANGE);

    evalue = g_enum_get_value (eclass, priv->journal_timestamp_range);

    g_print ("evalue: %s\n", evalue->value_name);

    gboolean valid;
    GtkTreeIter iter;
    GtkTreeModel *model;

    model = GTK_TREE_MODEL (priv->range_liststore);

    valid = gtk_tree_model_get_iter_first (model, &iter);

    while (valid)
    {
        gchar *journal_range_enum_nick;

        gtk_tree_model_get (GTK_TREE_MODEL (priv->range_liststore), &iter,
                            COLUMN_JOURNAL_TIMESTAMP_RANGE_ENUM_NICK, &journal_range_enum_nick,
                            -1);

        // compare enum nicks
        if (g_strcmp0 (evalue->value_name, journal_range_enum_nick) == 0)
            break;

        valid = gtk_tree_model_iter_next (model, &iter);
    }

    selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (priv->range_treeview));

    gtk_tree_selection_select_iter (selection, &iter);
}
