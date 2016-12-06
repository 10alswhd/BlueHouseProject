#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mrss.h>
#include <unity.h>
#include <glib.h>
#include <gio/gio.h>
#include "config.h"
#include "openclipart-rss.h"

#define DBUS_NAME "com.canonical.Unity.Scope.Graphics.Openclipart"
#define DBUS_PATH "/com/canonical/unity/scope/graphics/openclipart"

/**
 * In this function the results from the backend are obtained and
 * added to the search results in the Dash
 */
static void
search_func(UnityScopeSearchBase* search, void* user_data)
{
    GSList *results = NULL;
    GSList *iter = NULL;
    GHashTable *metadata = NULL;
    result_t *result = NULL;
    UnityScopeResult scope_result = { 0, };

    /* The get_results() function is implemented in the backend */
    results = get_results(search->search_context->search_query);

    for (iter = results; iter; iter = iter->next) {
        result = (result_t *)iter->data;
        scope_result.uri = result->link;
        scope_result.title = result->title;
        scope_result.icon_hint = result->icon_url;
        scope_result.category = 0;
        scope_result.result_type = UNITY_RESULT_TYPE_DEFAULT;
        scope_result.mimetype = "text/html";
        scope_result.comment = result->description;
        scope_result.dnd_uri = result->link;

        /* Insert the metadata, if available */
        metadata = g_hash_table_new(g_str_hash, g_str_equal);
        if (result->author) {
            g_hash_table_insert(metadata, "author",
                g_variant_new_string(result->author));
        }
        if (result->creation_date) {
            g_hash_table_insert(metadata, "creation_date",
                g_variant_new_string(result->creation_date));
        }
        scope_result.metadata = metadata;

        /* Add the returned result to the search results list */
        unity_result_set_add_result(search->search_context->result_set,
            &scope_result);
        g_hash_table_unref(metadata);
    }
    g_slist_free_full(results, (GDestroyNotify) result_cleanup);
}

/**
 * This function will be invoked when the user clicks on the result and
 * its preview is shown in the Dash.
 * There are a set of predefined preview types: simply pick one, instantiate
 * it, add metadata to it if available, and return it.
 */
static UnityAbstractPreview *
preview_func(UnityResultPreviewer *previewer, void *user_data)
{
    UnityPreview *preview = NULL;
    UnityPreviewAction *action = NULL;
    UnityInfoHint *author_hint, *creation_date_hint = NULL;
    GVariant *gv_author, *gv_creation_date = NULL;
    const char *creation_date = NULL;

    preview = UNITY_PREVIEW(unity_generic_preview_new(
        previewer->result.title,
        previewer->result.comment,
        g_icon_new_for_string(previewer->result.icon_hint, NULL)));

    action = unity_preview_action_new_with_uri(previewer->result.uri, "Open",
        NULL);
    unity_preview_add_action(preview, action);

    if (previewer->result.metadata) {
        gv_author = g_hash_table_lookup(previewer->result.metadata, "author");

        /* There are 2 ways to do this, the first method just directly
         * uses the GVariant from the hash. The second extracts the string
         * first, which might be useful for debugging. */
        if (gv_author) {
            author_hint = unity_info_hint_new_with_variant("author", "Author",
                NULL, gv_author);
            /* The ref call here and unref below are to work-around a bug in
             * libunity, see:
             *   http://code.launchpad.net/~mhr3/libunity/floating-fixes */
            g_object_ref(author_hint);
            unity_preview_add_info(preview, author_hint);
            g_object_unref(author_hint);
        }
        gv_creation_date = g_hash_table_lookup(previewer->result.metadata,
            "creation_date");
        if (gv_creation_date) {
            g_variant_get(gv_creation_date, "&s", &creation_date);
            creation_date_hint = unity_info_hint_new("creation_date",
                "Creation Date", NULL, creation_date);
            /* The ref call here and unref below are to work-around a bug in
             * libunity, see:
             *   http://code.launchpad.net/~mhr3/libunity/floating-fixes */
            g_object_ref(creation_date_hint);
            unity_preview_add_info(preview, creation_date_hint);
            g_object_unref(creation_date_hint);
        }
    }

    return UNITY_ABSTRACT_PREVIEW(preview);
}

/**
 * This is the main function: the scope is defined and exported, a DBUS
 * connector is created and the main loop is run
 */
int
main(void) {
    UnitySimpleScope *scope = NULL;
    UnityScopeDBusConnector *connector = NULL;
    UnityCategorySet *cats = NULL;
    UnityCategory *cat = NULL;
    GIcon *icon = NULL;

    icon = g_themed_icon_new(CATEGORY_ICON_PATH);

    cat = unity_category_new("global", "Graphics", icon,
        UNITY_CATEGORY_RENDERER_HORIZONTAL_TILE);
    cats = unity_category_set_new();
    unity_category_set_add(cats, cat);

    scope = unity_simple_scope_new();
    unity_simple_scope_set_group_name(scope, DBUS_NAME);
    unity_simple_scope_set_unique_name(scope, DBUS_PATH);
    unity_simple_scope_set_search_func(scope, search_func, NULL, NULL);
    unity_simple_scope_set_preview_func(scope, preview_func, NULL, NULL);
    unity_simple_scope_set_category_set(scope, cats);

    connector = unity_scope_dbus_connector_new(UNITY_ABSTRACT_SCOPE(scope));
    unity_scope_dbus_connector_export(connector, NULL);
    unity_scope_dbus_connector_run();

    return 0;
}
