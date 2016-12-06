package ex1.vo;

import java.util.ArrayList;

import android.R.integer;

public class Disc_intA {
	ArrayList<Integer[]> list;
	
	
	private final Integer[] i1 = {2,1,4,3};
	private final Integer[] i2 = {4,1,2,3};
	private final Integer[] i3 = {2,4,1,5};
	private final Integer[] i4 = {2,4,3,1};
	private final Integer[] i5 = {1,4,2,3};
	private final Integer[] i6 = {3,2,5,5};
	private final Integer[] i7 = {2,4,1,5};
	private final Integer[] i8 = {2,4,3,1};
	private final Integer[] i9 = {4,3,2,1};
	private final Integer[] i10= {1,2,3,5};
	private final Integer[] i11= {4,3,1,2};
	private final Integer[] i12= {2,3,4,1};
	private final Integer[] i13= {1,3,2,4};
	private final Integer[] i14= {4,3,1,2};
	private final Integer[] i15= {2,4,1,3};
	private final Integer[] i16= {4,1,3,2};
	private final Integer[] i17= {2,3,1,4};
	private final Integer[] i18= {3,1,4,2};
	private final Integer[] i19= {1,2,3,5};
	private final Integer[] i20= {2,3,5,1};
	private final Integer[] i21= {4,3,2,1};
	private final Integer[] i22= {2,4,1,3};
	private final Integer[] i23= {2,4,1,3};
	private final Integer[] i24= {2,3,1,4};
	private final Integer[] i25= {1,4,3,2};
	private final Integer[] i26= {2,4,1,3};
	private final Integer[] i27= {1,3,2,4};
	private final Integer[] i28= {4,1,2,3};
	
	public Disc_intA(){
		list = new ArrayList<Integer[]>();
		list.add(i1);
		list.add(i2);
		list.add(i3);
		list.add(i4);
		list.add(i5);
		list.add(i6);
		list.add(i7);
		list.add(i8);
		list.add(i9);
		list.add(i10);
		list.add(i11);
		list.add(i12);
		list.add(i13);
		list.add(i14);
		list.add(i15);
		list.add(i16);
		list.add(i17);
		list.add(i18);
		list.add(i19);
		list.add(i20);
		list.add(i21);
		list.add(i22);
		list.add(i23);
		list.add(i24);
		list.add(i25);
		list.add(i26);
		list.add(i27);
		list.add(i28);
		
		
		
		
	}

	public Integer[] getList(int a_c) {
		
		return list.get(a_c);
	}
	
	
	
	
}
