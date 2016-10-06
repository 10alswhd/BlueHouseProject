// 상담산업심리학과 2014671034 유가연

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
			System.out.println((i+1)+"번째 학생의 이름을 입력하세요 : ");
			String name = sc.next();
			
			System.out.println((i+1)+"번째 학생의 학과를 입력하세요 : ");
			String major = sc.next();
			
			System.out.println((i+1)+"번째 학생의 학번을 입력하세요 : ");
			String id = sc.next();
			
			System.out.println((i+1)+"번째 학생의 학점평균을 입력하세요 : ");
			double score = sc.nextDouble();
			
			Student student = new Student(name, major, id, score);
			
			dept.put(id, student);
		}
		
		Set<String> list = dept.keySet();
		Iterator<String> itr = list.iterator();
		
		System.out.println("검색할 학생의 학번을 입력하세요 : ");
		String id = sc.next();
		Student student = dept.get(id);
		System.out.println("          학번             " + "\t" + " 이름 " + "\t" +
												"         전공     " + "\t" + "학점 평균");
		System.out.println(id + "\t" + student.name + "\t" + student.major + "\t" + student.score);
				
	}

}
