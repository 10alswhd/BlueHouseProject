package ex1.vo;

import java.util.ArrayList;


public class Disc_string {
	ArrayList<String[]> list = new ArrayList<String[]>();;
	
	
	private final String[] s1 = {"열정적인", "대담한", "치밀한", "만족해하는"};
	private final String[] s2 = {"신중한", "결단력있는", "확신을주는", "호의적인"};
	private final String[] s3 = {"다정한", "정확한", "솔직히말하는", "변화가적은"};
	private final String[] s4 = {"말하기좋아한", "자제력있는", "관습을따르는", "결단력있는"};
	private final String[] s5 = {"도전하는", "통찰력있는", "사교적인", "온건한"};
	private final String[] s6 = {"온화한", "설득력있는", "겸손한", "독창적idea"};
	private final String[] s7 = {"표현력있는", "조심성있는", "주도적인", "민감히반응"};
	private final String[] s8 = {"호의적인", "세심한", "겸손한", "참을성적은"};
	private final String[] s9 = {"사려깊은", "잘 동의하는", "매력적인", "확고한"};
	private final String[] s10= {"용감한", "격려하는", "순응하는", "수줍어하는"};
	private final String[] s11= {"내성적인", "호의적인", "의지가강한", "명랑한"};
	private final String[] s12= {"남을격려하는", "친절한", "주의깊은", "독립심강한"};
	private final String[] s13= {"경쟁심있는", "생각이깊은", "활발한", "자신을안비춤"};
	private final String[] s14= {"세밀한", "유순한", "완고한", "놀기좋아하는"};
	private final String[] s15= {"호감을주는", "생각이깊은", "의지가굳은", "일관된행동"};
	private final String[] s16= {"논리적인", "과감한", "충실한", "인기있는"};
	private final String[] s17= {"사교적인", "참을성있는", "자신감있는", "말씨부드러움"};
	private final String[] s18= {"의존적인", "의욕적인", "철저한", "활기있는"};
	private final String[] s19= {"의욕적인", "외향적인", "친근한", "갈등을피하는"};
	private final String[] s20= {"유머가있는", "이해심있는", "공평한", "단호한"};
	private final String[] s21= {"자제력있는", "관대한", "활기있는", "고집스런"};
	private final String[] s22= {"재치있는", "내향적인", "강인한", "잘화내지않는"};
	private final String[] s23= {"남과잘어울리는", "점잖은", "활기찬", "너그러운"};
	private final String[] s24= {"매력있는", "흡족해하는", "지시하는", "양보하는"};
	private final String[] s25= {"자기주장하는", "체계적인", "협력적인", "즐거운"};
	private final String[] s26= {"유쾌한", "정교한", "결과를요구하는", "침착한"};
	private final String[] s27= {"변화를추구하는", "우호적인", "호소력있는", "꼼꼼한"};
	private final String[] s28= {"공손한", "새롭게시작하는", "낙천적인", "도움을주려는"};
	
	public Disc_string(){
		System.out.println("fdsafesafdsafhjdskahfjkdshakjl");
		
		
		
		
		list.add(s1);
		list.add(s2);
		list.add(s3);
		list.add(s4);
		list.add(s5);
		list.add(s6);
		list.add(s7);
		list.add(s8);
		list.add(s9);
		list.add(s10);
		list.add(s11);
		list.add(s12);
		list.add(s13);
		list.add(s14);
		list.add(s15);
		list.add(s16);
		list.add(s17);
		list.add(s18);
		list.add(s19);
		list.add(s20);
		list.add(s21);
		list.add(s22);
		list.add(s23);
		list.add(s24);
		list.add(s25);
		list.add(s26);
		list.add(s27);
		list.add(s28);
	
	
	}

	public String[] getList(int ck) {
		
		String[] s = new String[4];
		s = list.get(ck);
		
		return s;
		
		
	}	
	
	
}
