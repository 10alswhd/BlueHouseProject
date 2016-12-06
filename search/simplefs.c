#define FUSE_USE_VERSION 30

#include <fuse.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>

#define INITIAL_SIZE 1024

/* 1個の普通のファイルを表す構造体 */
struct file_metadata {
    int mode;     // ファイルの種類・読み書きのモード
    int nlink;    // ファイルのリンクカウント
    int length;   // ファイル内のデータのバイト数
    int capacity; // data配列の大きさ
    char *data;   // データを保持する配列へのポインタ
};

/* ディレクトリを表すリストの要素 */
struct directory_entry {
    char *name;                   // ファイル名
    struct file_metadata *file;   // ファイルの本体
    struct directory_entry *next; // 次の要素へのポインタ
};

static struct directory_entry dummy = { "", NULL, NULL };   // ダミー
struct directory_entry *root = &dummy;   // このFSのルートディレクトリ

// ディレクトリ内のファイルを探す補助関数
static struct directory_entry *search_file(const char *name)
{
    struct directory_entry *p;
    for (p = root; p != NULL; p = p->next) {
        if (strcmp(p->name, name + 1) == 0) {
            return p;
        }
    }
    return NULL;
}

static int simple_getattr(const char *path, struct stat *stbuf)
{
    int res = 0;
    struct directory_entry *p;

    memset(stbuf, 0, sizeof(struct stat));
    if (strcmp(path, "/") == 0) {
        stbuf->st_mode = S_IFDIR | 0755;
        stbuf->st_nlink = 2;
    } else if (p = search_file(path)) {
        stbuf->st_mode = p->file->mode;
        stbuf->st_nlink = p->file->nlink;
        stbuf->st_size = p->file->length;
    } else
        res = -ENOENT;

    return res;
}

static int simple_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
        off_t offset, struct fuse_file_info *fi)
{
    struct directory_entry *p;

    if (strcmp(path, "/") != 0)
        return -ENOENT;

    filler(buf, ".", NULL, 0);   // fillerを呼ぶと，返す一覧情報に1つ要素を追加する．
    filler(buf, "..", NULL, 0);
    // ダミーを飛ばす
    for (p = root->next; p != NULL; p = p->next) {
        if (filler(buf, p->name, NULL, 0)) {
            break;
        }
    }

    return 0;
}

static int simple_open(const char *path, struct fuse_file_info *fi)
{
    struct directory_entry *p;

    if ((p = search_file(path)) == 0) {
        return -ENOENT;
    }

    fi->fh = (long)p->file;

    return 0;
}

static int simple_read(const char *path, char *buf, size_t size, off_t offset,
        struct fuse_file_info *fi)
{
    struct file_metadata *f = (struct file_metadata *)(long)fi->fh;

    if (offset > f->length) {
        return 0;
    }
    if (offset + size > f->length) {
        size = f->length - offset;
    }
    memcpy(buf, f->data + offset, size);

    return size;
}

// 十分に大きなdata配列を確保する補助関数．data配列は2倍ずつ大きくしていく．
static int assure_size(struct file_metadata *f, int size)
{
    int new_capacity = f->capacity;
    char *new_data;

    while (new_capacity < size) {
        new_capacity *= 2;
    }
    new_data = calloc(new_capacity, 1);
    if (new_data == NULL) {
        return -1;
    }
    memcpy(new_data, f->data, f->length);
    free(f->data);
    f->data = new_data;
    f->capacity = new_capacity;
    return 0;
}

static int simple_write(const char *path, const char *buf, size_t size, off_t offset,
        struct fuse_file_info *fi)
{
    struct file_metadata *f = (struct file_metadata *)(long)fi->fh;
    int block_num, begin, end;
    char *block;

    if (assure_size(f, offset + size) < 0) {
        return -ENOSPC;
    }
    if (offset + size > f->length) {
        f->length = offset + size;
    }
    memcpy(f->data + offset, buf, size);

    return size;
}

static int simple_mknod(const char *path, mode_t mode, dev_t device)
{
    struct directory_entry *p;

    if (search_file(path)) {
        return -EEXIST;
    }
    p = malloc(sizeof(struct directory_entry));
    if (p == NULL) {
        return -ENOSPC;
    }
    p->file = calloc(sizeof(struct file_metadata), 1);
    if (p->file == NULL) {
        return -ENOSPC;
    }
    p->file->mode = mode;
    p->file->nlink = 1;
    p->file->length = 0;
    p->file->capacity = INITIAL_SIZE;
    p->file->data = calloc(INITIAL_SIZE, 1);

    p->name = strdup(path + 1);
    if (p->name == NULL) {
        return -ENOSPC;
    }

    // ダミーを飛ばす
    p->next = root->next;
    root->next = p;

    return 0;
}

static int simple_rename(const char *oldpath, const char *newpath)
{
    struct directory_entry *p;

    if ((p = search_file(oldpath)) == 0) {
        return -ENOENT;
    }

    free(p->name);
    p->name=strdup(newpath+1);
    if(p->name==NULL){
        return -ENOSPC;
    }

    return 0;
}

static int simple_truncate(const char *path, off_t length)
{
    struct directory_entry *p;

    if(length<0){
        return -EINVAL;
    }

    if ((p = search_file(path)) == 0) {
        return -ENOENT;
    }

    if(length < p->file->length){
        memset(p->file->data + length, 0, p->file->length - length);
    } else if(length > p->file->capacity){
        if (assure_size(p->file, length) < 0) {
            return -ENOSPC;
        }
    } else{
        memset(p->file->data + p->file->length, 0, length - p->file->length);
    }
    p->file->length=length;

    return 0;
}

// 検索対象エントリの一つ前のエントリを取得する
static struct directory_entry *search_prev_file(const char *name)
{
    struct directory_entry *p;
    for (p = root; p != NULL; p = p->next) {
        if (strcmp(p->next->name, name + 1) == 0) {
            return p;
        }
    }
    return NULL;
}

static int simple_unlink(const char *path)
{
    struct directory_entry *p;

    if ((p = search_prev_file(path)) == 0) {
        return -ENOENT;
    }

    struct directory_entry *removed=p->next;
    p->next=p->next->next;

    free(removed->file->data);
    free(removed->file);
    free(removed->name);
    free(removed);

    return 0;
}

static struct fuse_operations simple_oper = {
    .getattr	= simple_getattr,
    .readdir	= simple_readdir,
    .open		= simple_open,
    .read		= simple_read,
    .write	= simple_write,
    .mknod	= simple_mknod,
    .rename = simple_rename,
    .truncate = simple_truncate,
    .unlink = simple_unlink,
};

int main(int argc, char *argv[])
{
    return fuse_main(argc, argv, &simple_oper, NULL);
}
