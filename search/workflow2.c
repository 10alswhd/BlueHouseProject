#define HEAD_DEFAULT_SIZE 64 // 表头节点数组的默认最大长度
#define BODY_DEFAULT_SIZE 64 // 尾随节点数组的默认最大长度
#define COLD_HEAD_THRES 16 // 冷块阈值
#define COLD_BODY_THRES 16 // 冷块阈值
// 以上的值均需要调整

// 指纹尾为00的表头节点
struct Headnode {
    unsigned long long fp; //128b?
    struct Bodynode* bnp; // 32b/48b?
    unsigned int body_len; // 数组中已存的尾随节点个数 32b
    unsigned int body_size; // 数组中总共可存的最大的尾随节点个数 32b
    unsigned int cold_body_num; // 数组中的冷块个数 32b
    unsigned short heat; // 热度
    struct Headnode* left;
    struct Headnode* right;
};

// 其他节点
struct Bodynode {
    unsigned long long fp; // 128b
    unsigned short heat; // 热度 16b
};

// 关于 ID 和指纹的映射：
// 由全相联改为组相联，不再按递增次序分配 ID ，而是根据指纹分配 ID。
// ID 由 指纹的后缀和递增的序号组成，即 指纹的后缀||递增的序号。
// TODO 两部分长度待定
struct MapTable {
    // fp 就是 key
    unsigned long long fp; // 160b?
    unsigned long addr; // ?
};

int main() {
    // 初始化
    struct Headnode* headnode = malloc(HEAD_DEFAULT_SIZE * sizeof(struct Headnode)); // TODO 新建表头数组，要不要有 default size
    int head_len = 0; // 数组中已存的表头个数
    int head_size = HEAD_DEFAULT_SIZE; // 数组最大容纳的表头个数
    int cold_head_num = 0;

    struct Maptable maptable[100000]; // 第一个索引为 ID 前缀（指纹后缀，24位），第二个索引为 ID 后缀(8位)
    struct Headnode* cur_head = NULL; // 当前表头节点
    struct Headnode* search_head = NULL; // 当前表头节点
    struct Headnode* firstColdHead = NULL; // 记录第一个表头冷块的位置，用于被新块替换
    struct Bodynode* firstColdBody = NULL; // 记录第一个尾随冷块的位置，用于被新块替换
    int headFound = 0; // 记录是否已找到匹配的表头
    int bodyFound = 0; // 记录是否已找到匹配的尾随节点

    while (新的写入操作){
        get(data); // TODO 获得数据
        get(addr); // TODO 获得地址
        long long fp = sha1(data); // TODO 对分块计算指纹;

        // fp 以 00 结尾
        if (fp % 100) {
            // 表明该节点是表头，查找这个表头是否在 headnode 中
            headFound = 0;
            search_head = headnode;
            while (1) {
                if (fp == search_head->fp) {
                    headFound = 1;
                    cur_head = search_head;
                    cur_head->heat += 10; // TODO 增加热度，增加幅度有待调整
                    if (cur_head->bnp == NULL) {
                        struct Bodynode* bodynode = malloc(BODY_DEFAULT_SIZE * sizeof(struct Bodynode)); // 新建尾随节点数组
                        cur_head->bnp = bodynode;
                        cur_head->body_len = 0;
                        cur_head->body_size = BODY_DEFAULT_SIZE;
                        cur_head->cold_body_num = 0;
                    }
                    else {
                        // 把 cur_head->bnp 所指向的链表放到Cache中
                        for (int j = 0; j < len(cur_head->bnp), j++) {
                            // TODO 把 cur_head->bnp[j] 放入 Cache

                            // bnp[j] 热度减1，检查是否变冷
                            if (--(cur_head->bnp + j)->heat < COLD_BODY_THRES) {
                                cur_head->cold_body_num++;
                                if (firstColdBody == NULL) firstColdBody = cur_head->bnp + j;
                            }
                        }
                    }
                }
                // 继续查找
                else {
                    // search_head 热度减1，检查是否变冷
                    if(--search_head->heat < COLD_BODY_THRES) {
                        cold_head_num++;
                        if (firstColdHead == NULL) firstColdHead = search_head;
                    }
                    // TODO 如何解决未被搜到的头部变冷
                    if (search_head->left && fp < search_head->fp) {
                        search_head = search_head->left;
                        continue;
                    }
                    if (search_head->right && fp > search_head->fp) {
                        search_head = search_head->left;
                        continue;
                    }
                }
                break;
            }
            if (!headFound) {
                // 把新的 headnode 放到 firstColdHead 的位置；如果没有，附加一个 headnode 项
                // if (firstColdHead != NULL) {
                //     cur_head = firstColdHead;
                //     // 回收
                //     cold_head_num--;
                //     free(cur_head->bnp);
                //     firstColdHead = NULL;
                // }
                // else {
                //     cur_head = headnode + head_len;
                //     head_len++; // 表头数组长度增加
                // }
                // cur_head->fp = fp; // 记录该节点的指纹
                // cur_head->bnp = NULL;
                // cur_head->heat = COLD_HEAD_THRES + 10; // TODO 赋予默认热度，假设为阈值 + 10，有待调整
                //
                curhead = rbtreeInsert(headnode, fp); // TODO insert: 红黑树插入

                // TODO 把该块数据写入硬盘
            }
        }
        else {
            // 该节点是其他节点
            bodyFound = 0;
            while (搜索 Cache) {
                // 查找 Cache 中 ID 的前缀是否和计算的指纹匹配
                if (fp == Cache.fp) {
                    // 命中了 Cache
                    bodyFound = 1;
                    Cache.heat += 10;// TODO 增加热度，增加幅度有待调整
                    break;
                }
            }
            if (!bodyFound) {
                insert(maptable, fp, addr); // 在 maptable 中增加这个块
                // 把新的 bodynode 放到 firstColdBody 的位置；如果没有，附加一个 bodynode 项
                if (firstColdBody != NULL) {
                    firstColdBody->fp = fp;
                    firstColdBody->heat = COLD_BODY_THRES + 10;
                    // 回收
                    cur_head->cold_body_num--;
                    firstColdBody = NULL;
                }
                else {
                    (cur_head->bnp + cur_head->body_len)->fp = fp;
                    (cur_head->bnp + cur_head->body_len)->heat = COLD_BODY_THRES + 10; // TODO 赋予默认热度，假设为阈值 + 1，有待调整
                    cur_head->body_len++;
                }
                // TODO 把该块数据写入硬盘
            }
        }

        /**** 后续处理 *****/

        // 清理冷的 headnode
        // TODO 新建红黑树

        // if (cold_head_num * 2 > head_len) {
        //     // 冷块超过一半，创建新的 headnode
        //     head_size = (head_len - coldNum) * 2; // 长度为热块数量的两倍
        //     struct Headnode* tmp = malloc(headsize * sizeof(struct Headnode));
        //     // 复制热块
        //     for (int i = 0, j = 0; i < head_len; i++) {
        //         if ((headnode + i)->heat >= COLD_HEAD_THRES) {
        //             (tmp + j)->fp = (headnode + i)->fp;
        //             (tmp + j)->bnp = (headnode + i)->bnp;
        //             (tmp + j)->body_len = (headnode + i)->body_len;
        //             (tmp + j)->body_size = (headnode + i)->body_size;
        //             (tmp + j)->cold_body_num = (headnode + i)->cold_body_num;
        //             (tmp + j)->heat = (headnode + i)->heat;
        //             if (headnode + i == cur_head) cur_head = tmp + j; // 修改 cur_head 的指向
        //             j++;
        //         }
        //     }
        //     free(headnode);
        //     headnode = tmp;
        //     head_len -= cold_head_num;
        //     cold_head_num = 0;
        // }

        // 清理冷的 bodynode
        if (cur_head->cold_body_num * 2 > cur_head->body_len) {
            // 冷块超过一半，创建新的 bodynode
            cur_head->body_size = (body_len - coldNum) * 2; // 长度为热块数量的两倍
            struct Bodynode* tmp = malloc(cur_head->body_size * sizeof(struct Bodynode));
            // 复制热块
            for (int i = 0, j = 0; i < cur_head->body_len; i++) {
                if ((cur_head->bnp + i)->heat >= COLD_BODY_THRES) {
                    (tmp + j)->fp = (cur_head->bnp + i)->fp;
                    (tmp + j)->heat = (cur_head->bnp + i)->heat;
                    j++;
                }
            }
            free(cur_head->bnp);
            cur_head->bnp = tmp;
            cur_head->body_len -= cur_head->cold_body_num;
            cur_head->cold_body_num = 0;
        }

        // 若 headnode 已满，新建一个两倍长的 headnode，把原有数据移动过去
        // TODO 新建红黑树

        // if (head_len == head_size) {
        //     head_size *= 2;
        //     struct Headnode* tmp = malloc(head_size * sizeof(struct Headnode));
        //     // 复制
        //     for (int i = 0; i < head_len; i++) {
        //         (tmp + i)->fp = (headnode + i)->fp;
        //         (tmp + i)->bnp = (headnode + i)->bnp;
        //         (tmp + i)->body_len = (headnode + i)->body_len;
        //         (tmp + i)->body_size = (headnode + i)->body_size;
        //         (tmp + i)->cold_body_num = (headnode + i)->cold_body_num;
        //         (tmp + i)->heat = (headnode + i)->heat;
        //         if (headnode + i == cur_head) cur_head = tmp + i; // 修改 cur_head 的指向
        //     }
        //     free(headnode);
        //     headnode = tmp;
        // }
        // 若清理后的 headnode 块个数太少，新建一个一半长的 headnode，把原有数据移动过去
        // 不会发生，因为冷块被清理后，会随即进行重建操作
        /*
        else if (head_size > HEAD_DEFAULT_SIZE && head_len * 4 < head_size) {
            head_size /= 2;
            struct Headnode* tmp = malloc(head_size * sizeof(struct Headnode));
            // 复制
            for (int i = 0; i < head_len; i++) {
                (tmp + i)->fp = (headnode + i)->fp;
                (tmp + i)->bnp = (headnode + i)->bnp;
                (tmp + i)->body_len = (headnode + i)->body_len;
                (tmp + i)->body_size = (headnode + i)->body_size;
                if (headnode + i == cur_head) cur_head = tmp + i; // 修改 cur_head 的指向
            }
            free(headnode);
            headnode = tmp;
        }
        */

        // 若 bodynode 已满，新建一个两倍长的 bodynode，把原有数据移动过去
        if (cur_head->body_len) {
            cur_head->body_size *= 2;
            struct Bodynode* tmp = malloc(cur_head->body_size * sizeof(struct Bodynode));
            // 复制
            for (int i = 0; i < cur_head->body_len; i++) {
                (tmp + i)->fp = (cur_head->bnp + i)->fp;
                (tmp + i)->heat = (cur_head->bnp + i)->heat;
            }
            free(cur_head->bnp);
            cur_head->bnp = tmp;
        }
        // 若清理后的 bodynode 块个数太少，新建一个一半长的 bodynode，把原有数据移动过去
        // 不会发生，因为冷块被清理后，会随即进行重建操作
        /*
        else if (bodynode 长度小于 1/4) {
            cur_head->body_size /= 2;
            struct Bodynode* tmp = malloc(cur_head->body_size * sizeof(struct Bodynode));
            // 复制
            for (int i = 0; i < cur_head->body_len; i++) {
                (tmp + i)->id = (cur_head->bnp + i)->id;
                (tmp + i)->heat = (cur_head->bnp + i)->heat;
            }
            free(cur_head->bnp);
            cur_head->bnp = tmp;
        }
        */
    }
}
