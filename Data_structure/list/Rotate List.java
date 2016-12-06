/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) {
 *         val = x;
 *         next = null;
 *     }
 * }
 */
public class Solution {
    public ListNode rotateRight(ListNode head, int n) {
        ListNode cur = head;
        int count = 0;
        while(cur != null) {
            count++;
            cur = cur.next;
        }
        if(count == 0 || count == 1 || n == 0 || n%count == 0) return head;
        int difference = count - (n%count);
        cur = head;
        ListNode secondHead = head;
        for(int i = 0; i < difference-1; i++) {
            cur = cur.next;
        }
        ListNode firstHead = cur.next;
        ListNode firstTail = cur;
        while(cur.next != null) {
            cur = cur.next;
        }
        cur.next = secondHead;
        firstTail.next = null;
        return firstHead;
    }
}
