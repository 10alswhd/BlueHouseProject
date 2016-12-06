package ex1.test;

import ex1.vo.Disc_End_listString;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.widget.TextView;

public class Disc_End_list extends Activity {

	TextView tit, t1,t2,t3,t4;
	
	int ck;
	Disc_End_listString list;
	
	String[] s;
	
	protected void onCreate(Bundle savedInstanceState) {
	
		super.onCreate(savedInstanceState);
		setContentView(R.layout.disc_list);
		
		tit = (TextView) findViewById(R.id.discList_tit);
		t1 = (TextView) findViewById(R.id.discList_txt1);
		t2 = (TextView) findViewById(R.id.discList_txt2);
		t3 = (TextView) findViewById(R.id.discList_txt3);
		t4 = (TextView) findViewById(R.id.discList_txt4);
		
		
		Intent i = getIntent();
		Bundle bundle= i.getExtras();
		ck = bundle.getInt("ck");
		
		gettxt();

		
		}

	private void gettxt() {
		list = new Disc_End_listString();
		
		s = new String[5];
		
		s = list.getList().get(ck);
		
		tit.setText(s[0]);
		t1.setText(s[1]);
		t2.setText(s[2]);
		t3.setText(s[3]);
		t4.setText(s[4]);
	
	
	}
	
}
