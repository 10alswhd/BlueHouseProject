public class ReorderList {
	public void reorderList(ListNode head) {
	
		ListNode tail = head;//go to tail of the list
		ListNode middle = head;//go to middle of the list
				
		while(tail != null && tail.next != null){//when terminate, middle points to the middle node
			middle = middle.next;
			tail = tail.next.next;
		}
		
		ListNode left = head;//cut the list into two halves, 
		ListNode right = middle.next;
		middle.next = null;//cut at middle
		
		right = reverse(right);//reverse right half
		merge(left, right);//merge left half and right half alternatively
	
	}
	
	public ListNode reverse(ListNode n){
		if(n == null || n.next == null) return n;		
		ListNode head = n;//head of the reversed list
		ListNode next = n.next;//store n.next
		head.next = null;//
		n = next;//move to next;
		
		while(n != null){
			next = n.next;
			n.next = head;
			head = n;
			n = next;
		}
		return head;			
	}
	public ListNode merge(ListNode a, ListNode b){
		ListNode dh = new ListNode(0);
		ListNode tail = dh;
		boolean isANext = true;
		while(a != null && b != null){
			if(isANext == true){
				tail.next = a;
				a = a.next;
				isANext = !isANext;
			}
			else{
				tail.next = b;
				b = b.next;
				isANext = !isANext;
			}
			tail = tail.next;				
		}
		tail.next = (a != null)? a:b;
		return dh.next;		
	}
}
