// ������ɸ��а� 2014671034 ������

import java.util.*;
//import java.util.HashMap;
//import java.util.Iterator;
//import java.util.Scanner;
//import java.util.Set;

public class SearchingStudent {

	public static void main(String[] args) {
		
		HashMap<String, Student> dept = new HashMap<String, Student>();
		
		Scanner sc = new Scanner(System.in);
		
		for(int i=0; i<5; i++){
			System.out.println((i+1)+"��° �л��� �̸��� �Է��ϼ��� : ");
			String name = sc.next();
			
			System.out.println((i+1)+"��° �л��� �а��� �Է��ϼ��� : ");
			String major = sc.next();
			
			System.out.println((i+1)+"��° �л��� �й��� �Է��ϼ��� : ");
			String id = sc.next();
			
			System.out.println((i+1)+"��° �л��� ��������� �Է��ϼ��� : ");
			double score = sc.nextDouble();
			
			Student student = new Student(name, major, id, score);
			
			dept.put(id, student);
		}
		
		Set<String> list = dept.keySet();
		Iterator<String> itr = list.iterator();
		
		System.out.println("�˻��� �л��� �й��� �Է��ϼ��� : ");
		String id = sc.next();
		Student student = dept.get(id);
		System.out.println("          �й�             " + "\t" + " �̸� " + "\t" +
												"         ����     " + "\t" + "���� ���");
		System.out.println(id + "\t" + student.name + "\t" + student.major + "\t" + student.score);
				
	}

}
