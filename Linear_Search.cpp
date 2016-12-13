/*Linear Search Function
  Time Complexity  : O(N)
  Space Complexity : O(1)
*/
int Linear_Search(int data_array[],int SizeOf_data_array,int Query_Element)
{

	int Index;
	//Loop for traversing Array
	for(Index=0;Index<SizeOf_data_array;Index++)
		if(data_array[Index]==Query_Element)
			return Index;//return Index of Query_Element

	//return -1 if not found Query_Element
	return -1;
}
