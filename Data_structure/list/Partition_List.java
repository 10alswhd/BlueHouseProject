public class PartitionList {
	public ListNode partition(ListNode head, int x) {
		ListNode h1 = new ListNode(0);//dummy head of small list
		ListNode t1 = h1;//tail of small list
		ListNode h2 = new ListNode(0);//dummy head of large list
		ListNode t2 = h2;//tail of large list
		
		while(head != null){
			ListNode node = head;
			head = head.next;
			node.next = null;//isolate this node			
			if(node.val < x){
				t1.next = node;
				t1 = node;
			}
			else{
				t2.next = node;
				t2 = node;
			}
		}			
		t1.next = h2.next;								
		return h1.next;//dummy head
	}
}
