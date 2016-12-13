#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define XL_NVRAM_PATH       "/var"
#define XL_NVRAM_RESTORE    "./z.res"
#define XL_NVRAM_KEY_LEN    (30)
#define XL_MAGIC            0x01234567

typedef struct _sorted_key
{
    char buf[XL_NVRAM_KEY_LEN];
} SORTED_KEY;

typedef struct _sorted_keys
{
    /* MUST be at first */
    SORTED_KEY* keys;

    int magic;
    int key_len;
} SORTED_KEYS;

/* MUST free the return value outside */
SORTED_KEYS* read_from_file(char* filename)
{
#define BUFSZ 1024
#define KEY_MAX 500

    SORTED_KEYS* pkeys = NULL;
    FILE* fp = NULL;
    unsigned char buf[BUFSZ], *p;
    int found = 0, is_ok = 1;

    pkeys = malloc(sizeof(SORTED_KEYS) + sizeof(SORTED_KEY) * KEY_MAX);
    pkeys->keys = (SORTED_KEY*)((char*)pkeys + sizeof(SORTED_KEYS));
    pkeys->key_len = 0;
    pkeys->magic = XL_MAGIC;

    /* assert(NULL != filename); */
    if(NULL == (fp = fopen(filename, "ro")))
    {
        fprintf(stderr, "xl_nvram open %s error\n", filename);
        return NULL;
    }

    //find "Default" first
    while (NULL != fgets(buf, BUFSZ, fp))
    {
        if (buf[0] == '\n' || buf[0] == '#')
        {
            continue;
        }
        if (!strncmp(buf, "Default\n", 8))
        {
            found = 1;
            break;
        }
    }
    if (!found)
    {
        fprintf(stderr, "xl_nvram file format error!\n");
        fclose(fp);
        free(pkeys);
        return NULL;
    }

    while (NULL != fgets(buf, BUFSZ, fp))
    {
        if (buf[0] == '\n' || buf[0] == '#')
        {
            continue;
        }
        if (NULL == (p = strchr(buf, '=')))
        {
            fprintf(stderr, "xl_nvram %s file format error!\n", filename);
            is_ok = 0;
            break;
        }

        *p = '\0'; /* speperate the string */

        if((p - buf) >= XL_NVRAM_KEY_LEN)
        {
            fprintf(stderr, "xl_nvram key=%s is too big\n", buf);
            is_ok = 0;
            break;
        }

        memcpy(&pkeys->keys[pkeys->key_len], buf, strlen(buf) + 1);
        pkeys->key_len++;
    }

    fclose(fp);

    if(!is_ok)
    {
        free(pkeys);
        return NULL;
    }

    return pkeys;
}

void bubble_sort(SORTED_KEYS* pkeys)
{
    SORTED_KEY *key, tmp_key;
    int j, i = 0, flag = 1;

    while(flag && (i < pkeys->key_len))
    {
        flag = 0;
        for(j = 0; j < pkeys->key_len - i - 1; j++)
        {
            if(strcmp(pkeys->keys[j].buf, pkeys->keys[j+1].buf) > 0)
            {
                /* swap */
                memcpy(&tmp_key, &pkeys->keys[j], sizeof(SORTED_KEY));
                memcpy(&pkeys->keys[j], &pkeys->keys[j+1], sizeof(SORTED_KEY));
                memcpy(&pkeys->keys[j+1], &tmp_key, sizeof(SORTED_KEY));
                flag = 1;
            }
        }
        i++;
    }
}

static void dump_keys(SORTED_KEYS* pkeys)
{
    int i = 0;
    for(i = 0; i < pkeys->key_len; i++)
    {
        fprintf(stderr, "(%d,%s) ", i, pkeys->keys[i].buf);
    }
    fprintf(stderr, "\n");
}

int binary_search(SORTED_KEYS* pkeys, char* name)
{
    int cmp, imid, imin = 0, imax = pkeys->key_len - 1;

    while(imax >= imin)
    {
        imid = (imin+imax)/2;
        cmp = strcmp(pkeys->keys[imid].buf, name);
        //fprintf(stderr, "mid[%d] = %s ", imid, pkeys->keys[imid].buf);
        if(0 == cmp)
        {
            return imid;
        }
        else if(cmp < 0)
        {
            imin = imid + 1;
        }
        else
        {
            imax = imid - 1;
        }
    }

    return -1;
}

/* >=0 表示找到 */
int nvram_find(char* name)
{
    /* 使用静态变量，只 attach 一次共享内存，加快访问速度 */
    static volatile char* pshare = 0;
    int shm_id = -1;
    key_t key;
    SORTED_KEYS kfind = {0};

    if(0 == pshare)
    {
        if(-1 == (key = ftok(XL_NVRAM_PATH, 0xcc)))
        {
            fprintf(stderr, "ftok %s error\n", XL_NVRAM_PATH);
            return -1;
        }

        shm_id = shmget(key, 0, 0);
        if(shm_id == -1)
        {
            fprintf(stderr, "shmget error\n");
            return -1;
        }

        pshare = (char*)shmat(shm_id, NULL, 0);
        /* Never detach
        shmdt(shm_id, NULL, 0); */
    }
#if 0
    {
        int i; 
        SORTED_KEY *pk;
        pk = (SORTED_KEY*)((char*)pshare + 2*sizeof(int));
        for(i = 0; i < 184; i++)
        {
            fprintf(stderr, "%s ", pk[i].buf);
        }
        fprintf(stderr, "\n");
    }
#endif
    kfind.magic = *((int*)pshare);
    if(kfind.magic != XL_MAGIC)
    {
        fprintf(stderr, "xl_nvram MAGIC is not ok\n");
        return -1;
    }
    kfind.key_len = *((int*)(pshare + sizeof(int)));
    kfind.keys = (SORTED_KEY*)(pshare + 2 * sizeof(int));

    //dump_keys(&kfind);

    return binary_search(&kfind, name);
}

int main()
{
    int shm_id = -1;
    key_t key;
    SORTED_KEYS* pkeys;
    int *p_len, i, size;
    SORTED_KEY* pk;

    if(NULL == (pkeys = read_from_file(XL_NVRAM_RESTORE)))
    {
        return -1;
    }

    bubble_sort(pkeys);

    //dump_keys(pkeys);

    do
    {
        if(0 != access(XL_NVRAM_PATH, F_OK))
        {
            if(creat(XL_NVRAM_PATH, 0666))
            {
                fprintf(stderr, "create path %s error\n", XL_NVRAM_PATH);
                break;
            }
        }

        if(-1 == (key = ftok(XL_NVRAM_PATH, 0xcc)))
        {
            fprintf(stderr, "ftok %s error\n", XL_NVRAM_PATH);
            break;
        }
        
        size = 2*sizeof(unsigned int) + pkeys->key_len*sizeof(SORTED_KEYS);
        shm_id = shmget(key, ((size+4095)/4096)*4096, IPC_CREAT|IPC_EXCL|0600);
        if(-1 == shm_id)
        {
            fprintf(stderr, "xl_nvram shmget error shm_id=%d retry\n", shm_id);
            shm_id = shmget(key, 0, 0);
            if(-1 == shm_id)
            {
                fprintf(stderr, "xl_nvram shmget error2 shm_id=%d\n", shm_id);
                break;
            }
            if(-1 == shmctl(shm_id, IPC_RMID, NULL))
            {
                fprintf(stderr, "xl_nvram shmget del shm_id=%d error\n", shm_id);
                break;
            }
#if 0
            shm_id = shmget(key, size, IPC_CREAT|IPC_EXCL|0600);
            if(-1 == shm_id)
            {
                fprintf(stderr, "xl_nvram shmget error3 shm_id=%d\n", shm_id);
                break;
            }
#else
            break;
#endif
        }

        p_len = (int*)shmat(shm_id, NULL, 0);
        memset(p_len, '\0', size);
        memcpy(p_len, (char*)pkeys+sizeof(SORTED_KEY*), size);
        fprintf(stderr, "\n");
    }while(0);

#if 0
    {
        char *pshare;
        int shm_id2 = shmget(key, 0, 0);
        if(shm_id2 == -1)
        {
            fprintf(stderr, "shmget2 error\n");
            return -1;
        }
        pshare = (char*)shmat(shm_id2, NULL, 0);
        pk = (SORTED_KEY*)((char*)pshare + 2*sizeof(int));
        for(i = 0; i < 184; i++)
        {
            fprintf(stderr, "%s ", pk[i].buf);
        }
        fprintf(stderr, "\n");
        fprintf(stderr, "shmdt=%d\n", shmdt(pshare));
    }
#endif

#if 1
    char* name = "AccessControlList0";
    fprintf(stderr, "find %s=%d\n", name, binary_search(pkeys, name));

    name = "RADIUS_Server";
    fprintf(stderr, "find %s=%d\n", name, binary_search(pkeys, name));

    fprintf(stderr, "find %s=%d\n", name, nvram_find(name));

    name = "RADIUS_Server2";
    fprintf(stderr, "find %s=%d\n", name, binary_search(pkeys, name));
#endif
    
    free(pkeys);
    if(-1 != shm_id)
    {
        fprintf(stderr, "shmdt=%d\n", shmdt(p_len));
    }

}
