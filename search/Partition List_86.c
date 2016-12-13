/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *partition(ListNode *head, int x) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int flag = 0;
        ListNode *left = head;
        ListNode *right;
        ListNode *tmp;
        
        if(NULL == head) return head;
        if(head->val >= x)
            flag = 1;
        else 
            while(left->next != NULL && left->next->val < x)
                left = left->next;
        right = left;
        while(right->next != NULL){
            while(right->next != NULL && right->next->val >= x)
                right = right->next;
            if(NULL == right->next) return head;
            tmp = right->next;
            right->next = tmp->next;
            if(flag){
                tmp->next = head;
                head = tmp;
                flag = 0;
            }else{
                tmp->next = left->next;
                left->next = tmp;
            }
            left = tmp;
        }
        return head;
    }
};


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

/*哑节点的方式*/
class Solution {
public:
    ListNode *partition(ListNode *head, int x) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        ListNode Dummy(0);
        Dummy.next = head;
        ListNode *left = &Dummy;
        ListNode *right;
        ListNode *tmp;
        
        while(left->next != NULL && left->next->val < x)
            left = left->next;
        right = left;
        while(right->next != NULL){
            while(right->next != NULL && right->next->val >= x)
                right = right->next;
            if(NULL == right->next) return Dummy.next;
            tmp = right->next;
            right->next = tmp->next;
            tmp->next = left->next;
            left->next = tmp;
            left = tmp;
        }
        return Dummy.next;
    }
};
