package com.mytest;

import java.util.Map;

/**
 * Created by ray on 6/19/14.
 */
public class testlistloop{

    private static Map<Node, Integer> map;

    private static class Node {
        int val;
        Node next;

        public Node(int val){
            this.val = val;
        }
    }

    private static void printlist(Node head){
        while (head != null) {
            System.out.println(head.val);
            head = head.next;
        }
    }

    private static boolean hasCycle(Node head){
        Node fast = head;
        Node slow = head;
        while (fast != null && fast.next != null) {
            fast = fast.next.next;
            slow = slow.next;

            if (fast == slow) {
                return true;
            }
        }

        return  false;
    }

    private static boolean hasCycle2(Node head){
        Node fast = head;
        Node slow = head;
        while (fast != null && fast.next != null) {
            fast = fast.next.next;
            slow = slow.next;

            if (fast == slow) {
                return true;
            }
        }

        return  false;
    }

    public static void main(String[] args) {
        System.out.println("test start");
        Node node1 = new Node(1);
        Node node2 = new Node(2);
        Node node3 = new Node(3);
        Node node4 = new Node(4);

        node1.next = node2;
        node2.next = node3;
        node3.next = node4;
        node4.next = node2;

        boolean hascycle = hasCycle(node1);
        System.out.println("hasCycle?" + hascycle);
    }
}
