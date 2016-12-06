struct _GlSearchPopover
{
    /*< private >*/
    GtkPopoverMenu parent_instance;
};

typedef struct
{
    GtkWidget *parameter_stack;
    GtkWidget *parameter_label_stack;
    GtkWidget *parameter_listbox;
    GtkWidget *parameter_button_label;
} GlSearchPopoverPrivate;

G_DEFINE_TYPE_WITH_PRIVATE (GlSearchPopover, gl_search_popover, GTK_TYPE_POPOVER_MENU)
