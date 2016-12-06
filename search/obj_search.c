#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <groonga.h>
#include <time.h>
#include <limits.h>

grn_obj *
create_lexicon(grn_ctx *ctx, grn_obj *target_table, grn_obj *target_column,
               char *lexicon_name)
{
  grn_obj *key_type;
  grn_obj *lexicon, *tokenizer, *normalizer, *index_column;
  grn_id column_id;

  grn_obj bulk;

  key_type = grn_ctx_at(ctx, GRN_DB_SHORT_TEXT);
  lexicon = grn_table_create(ctx, lexicon_name, strlen(lexicon_name),
                             NULL,
                             GRN_OBJ_TABLE_PAT_KEY|GRN_OBJ_PERSISTENT,
                             key_type, NULL);
  if (lexicon == NULL) {
    lexicon = grn_ctx_get(ctx, lexicon_name, strlen(lexicon_name));
  }

  tokenizer = grn_ctx_get(ctx, "TokenBigram", strlen("TokenBigram"));
  if (grn_obj_set_info(ctx, lexicon, GRN_INFO_DEFAULT_TOKENIZER, tokenizer)) {
    fprintf(stderr, "grn_obj_set_info() set tokenizer failed\n");
    return NULL;
  }

  normalizer = grn_ctx_get(ctx, "NormalizerAuto", strlen("NormalizerAuto"));
  if (grn_obj_set_info(ctx, lexicon, GRN_INFO_NORMALIZER, normalizer)) {
    fprintf(stderr, "grn_obj_set_info() set normalizer failed\n");
    return NULL;
  }

  index_column = grn_column_create(ctx, lexicon, "index", strlen("index"),
                                   NULL,
                                   GRN_OBJ_PERSISTENT|GRN_OBJ_WITH_POSITION|GRN_OBJ_COLUMN_INDEX,
                                   target_table);
  if (index_column == NULL) {
    index_column = grn_obj_column(ctx, lexicon, "index", strlen("index"));
  }

  column_id = grn_obj_id(ctx, target_column);
  GRN_UINT32_INIT(&bulk, 0);
  GRN_UINT32_SET(ctx, &bulk, column_id);
  grn_obj_set_info(ctx, index_column, GRN_INFO_SOURCE, &bulk);
  grn_obj_close(ctx, &bulk);

  return lexicon;
}

grn_obj *
create_column(grn_ctx *ctx, grn_obj *table, char *column_name)
{
  grn_obj *column, *value_type;

  value_type = grn_ctx_at(ctx, GRN_DB_TEXT);

  column = grn_obj_column(ctx, table, column_name, strlen(column_name));
  if (!column) {
    column = grn_column_create(ctx, table, column_name, strlen(column_name),
                               NULL,
                               GRN_OBJ_PERSISTENT|GRN_OBJ_COLUMN_SCALAR,
                               value_type);
  }
  return column;
}

grn_obj *
create_table(grn_ctx *ctx, char *table_name)
{
  grn_obj *table, *key_type;

  key_type = grn_ctx_at(ctx, GRN_DB_SHORT_TEXT);
  table = grn_ctx_get(ctx, table_name, strlen(table_name));
  if (!table) {
    table = grn_table_create(ctx, table_name, strlen(table_name),
                             NULL,
                             GRN_OBJ_TABLE_HASH_KEY|GRN_OBJ_PERSISTENT,
                             key_type, NULL);
  }
  return table;
}

grn_id
insert_record(grn_ctx *ctx, grn_obj *table, grn_obj *column, char *key, char *record)
{
  grn_id id;
  grn_rc rc;
  int added;
  grn_obj value;

  id = grn_table_add(ctx, table, key, strlen(key), &added);

  GRN_TEXT_INIT(&value, 0);
  GRN_TEXT_PUT(ctx, &value, record, strlen(record));
  rc = grn_obj_set_value(ctx, column, id, &value, GRN_OBJ_SET);
  if (rc == GRN_INVALID_ARGUMENT) {
    id = -1;
  }
  grn_obj_unlink(ctx, &value);

  return id;
}

int
main(int argc, char **argv)
{
  grn_ctx ctx;
  grn_obj *db, *table, *lexicon, *column, *index_column;
  grn_id id;
  grn_obj *result;
  const char *path = "obj_search.grn";

  grn_init();
  grn_ctx_init(&ctx, 0);
  db = grn_db_open(&ctx, path);
  if (!db) { db = grn_db_create(&ctx, path, NULL); }

  table = create_table(&ctx, "table");
  column = create_column(&ctx, table, "column");
  lexicon = create_lexicon(&ctx, table, column, "lexicon");
  insert_record(&ctx, table, column, "groonga", "groonga world");
  insert_record(&ctx, table, column, "mroonga", "mroonga world");
  grn_column_index(&ctx, column, GRN_OP_FUZZY, &index_column, 1, NULL);

  printf("lexicon\n");
  grn_p(&ctx, lexicon);
  printf("table_pat\n");
  {
    grn_search_optarg options;
    grn_obj value;
    grn_obj *res;
    res = grn_table_create(&ctx, NULL, 0, NULL,
                           GRN_OBJ_TABLE_HASH_KEY|GRN_OBJ_WITH_SUBREC, lexicon, NULL);

    GRN_TEXT_INIT(&value, 0);
    GRN_BULK_REWIND(&value);
    GRN_TEXT_SET(&ctx, &value, "mmoonga", strlen("mmoonga"));
    memset(&options, 0, sizeof(grn_search_optarg));

    options.mode = GRN_OP_FUZZY;
    options.similarity_threshold = 0;
    options.max_interval = 0;
    options.weight_vector = NULL;
    options.proc = NULL;
    options.max_size = 0;
    options.scorer = NULL;
    options.fuzzy_prefix_match_size = 0;
    options.fuzzy_max_distance = 1;
    options.fuzzy_flags = GRN_TABLE_FUZZY_WITH_TRANSPOSITION;

    grn_obj_search(&ctx, lexicon, &value, res, GRN_OP_OR, &options);
    grn_p(&ctx, res);
    grn_obj_unlink(&ctx, &value);
    grn_obj_unlink(&ctx, res);
  }

  printf("index\n");
  {
    grn_search_optarg options;
    grn_obj value;
    grn_obj *res;
    res = grn_table_create(&ctx, NULL, 0, NULL,
                           GRN_OBJ_TABLE_HASH_KEY|GRN_OBJ_WITH_SUBREC, table, NULL);

    GRN_TEXT_INIT(&value, 0);
    GRN_BULK_REWIND(&value);
    GRN_TEXT_SET(&ctx, &value, "ggoonga wordl", strlen("ggoonga wordl"));
    memset(&options, 0, sizeof(grn_search_optarg));

    options.mode = GRN_OP_FUZZY;
    options.similarity_threshold = 0;
    options.max_interval = 0;
    options.weight_vector = NULL;
    options.proc = NULL;
    options.max_size = 0;
    options.scorer = NULL;
    options.fuzzy_prefix_match_size = 0;
    options.fuzzy_max_distance = 1;
    options.fuzzy_flags = GRN_TABLE_FUZZY_WITH_TRANSPOSITION;

    grn_obj_search(&ctx, index_column, &value, res, GRN_OP_OR, &options);
    grn_p(&ctx, res);
    grn_obj_unlink(&ctx, &value);
    grn_obj_unlink(&ctx, res);
  }

  grn_obj_unlink(&ctx, index_column);
  grn_obj_unlink(&ctx, column);
  grn_obj_unlink(&ctx, lexicon);
  grn_obj_unlink(&ctx, table);
  grn_obj_close(&ctx, db);
  grn_ctx_fin(&ctx);
  grn_fin();

  return 0;
}
