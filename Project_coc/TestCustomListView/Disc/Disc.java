package ex1.test;

import com.google.ads.AdRequest;
import com.google.ads.AdSize;
import com.google.ads.AdView;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.RadioGroup.OnCheckedChangeListener;
import android.widget.TextView;
import android.widget.Toast;
import ex1.vo.Disc_EndList;
import ex1.vo.Disc_intA;
import ex1.vo.Disc_intB;
import ex1.vo.Disc_list;
import ex1.vo.Disc_string;

public class Disc extends Activity implements OnCheckedChangeListener {
	Disc_intA dia;
	Disc_intB dib;
	Disc_string ds;
	Disc_list list;
	Disc_EndList endList;

	TextView tt1, t1, t2, t3, t4;
	RadioGroup b1, b2;
	RadioButton bb1, bb2, bb3, bb4;
	RadioButton bn1, bn2, bn3, bn4;

	Button bt1;

	boolean isa, isb;
	int ck = 1;
	int a_c, b_c;
	Integer i1 = 0, i2 = 0;

	RadioGroup group = null;

	Intent i;

	String[] s;
	
	LinearLayout layout;
	AdView ad;
	private final String adstring= "a14e71a9bd1850a";

	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.disc);
		layout = (LinearLayout) findViewById(R.id.disc_adView);
		
		
		ad = new AdView(this, AdSize.BANNER, adstring);
		layout.addView(ad);
		ad.loadAd(new AdRequest());
		
		i = getIntent();

		tt1 = (TextView) findViewById(R.id.disc_TiTxt);
		t1 = (TextView) findViewById(R.id.disc_txt1);
		t2 = (TextView) findViewById(R.id.disc_txt2);
		t3 = (TextView) findViewById(R.id.disc_txt3);
		t4 = (TextView) findViewById(R.id.disc_txt4);
		bt1 = (Button) findViewById(R.id.disc_bt1);
		b1 = (RadioGroup) findViewById(R.id.disc_Rbt1);
		b2 = (RadioGroup) findViewById(R.id.disc_Rbt2);
		bb1 = (RadioButton) findViewById(R.id.disc_bb1);
		bb2 = (RadioButton) findViewById(R.id.disc_bb2);
		bb3 = (RadioButton) findViewById(R.id.disc_bb3);
		bb4 = (RadioButton) findViewById(R.id.disc_bb4);

		dia = new Disc_intA();
		dib = new Disc_intB();
		ds = new Disc_string();
		list = new Disc_list();
		endList = new Disc_EndList();

		sendtext();

		b1.setOnCheckedChangeListener(Disc.this);
		b2.setOnCheckedChangeListener(Disc.this);

		bt1.setOnClickListener(new OnClickListener() {

			public void onClick(View arg0) {

				 if (!isa || !isb) {
					Toast.makeText(getApplicationContext(), "두가지 선택사항 전부 찍어주셔야합니다.", 100).show();
					return;

				} else {
					ck += 1;
					list.setListIntA1(i1);
					list.setListIntB1(i2);
					System.out.println(list.getListIntA1());
					System.out.println(list.getListIntB1());
					i1 = 0;
					i2 = 0;
					if (ck == 29) {
						end();
					}else {
						sendtext();
						
					}

				}
			}

		});

	}

	public void onCheckedChanged(RadioGroup group, int checkedId) {

		this.group = group;
		if (group.getId() == b1.getId()) {
			switch (checkedId) {
			case R.id.disc_bb1:
				a_c = 1;
				isa = true;
				break;

			case R.id.disc_bb2:
				a_c = 2;
				isa = true;
				break;
			case R.id.disc_bb3:
				a_c = 3;
				isa = true;
				break;
			case R.id.disc_bb4:
				a_c = 4;
				isa = true;
				break;
			}
			if (isa) {
				Integer[] i = dia.getList(ck - 1);
				i1 = i[a_c - 1];
			}

		}
		if (group.getId() == b2.getId()) {
			switch (checkedId) {
			case R.id.disc_bn1:
				b_c = 1;
				isb = true;
				break;
			case R.id.disc_bn2:
				b_c = 2;
				isb = true;
				break;
			case R.id.disc_bn3:
				b_c = 3;
				isb = true;
				break;
			case R.id.disc_bn4:
				b_c = 4;
				isb = true;
				break;
			}
			if (isb) {
				Integer[] i = dib.getList(ck - 1);
				i2 = i[b_c - 1];
			}
		}

	}

	private void sendtext() {
		s = new String[4];

		s = ds.getList(ck - 1);

		addtext();
	}

	private void addtext() {

		tt1.setText(String.valueOf(ck));
		t1.setText(s[0].toString());
		t2.setText(s[1].toString());
		t3.setText(s[2].toString());
		t4.setText(s[3].toString());
		if (b1 != null)
			b1.clearCheck();
		if (b2 != null)
			b2.clearCheck();
		isa = false;
		isb = false;

	}

	private void end() {

		for (Integer vo : list.getListIntA1()) {
			if (vo == 1) {
				endList.setLista1(vo);
			}
			if (vo == 2) {
				endList.setLista2(vo);
			}
			if (vo == 3) {
				endList.setLista3(vo);
			}
			if (vo == 4) {
				endList.setLista4(vo);
			}
			if (vo == 5) {
				endList.setLista5(vo);
			}

		}

		for (Integer vo : list.getListIntB1()) {
			if (vo == 1) {
				endList.setListb1(vo);
			}
			if (vo == 2) {
				endList.setListb2(vo);
			}
			if (vo == 3) {
				endList.setListb3(vo);
			}
			if (vo == 4) {
				endList.setListb4(vo);
			}
			if (vo == 5) {
				endList.setListb5(vo);
			}

		}
		Intent i = new Intent(getApplicationContext(), Disc_End.class);
		Bundle bundle = new Bundle();
		bundle.putInt("a1", endList.getLista1().size());
		bundle.putInt("a2", endList.getLista2().size());
		bundle.putInt("a3", endList.getLista3().size());
		bundle.putInt("a4", endList.getLista4().size());
		bundle.putInt("a5", endList.getLista5().size());
		
		bundle.putInt("b1", endList.getListb1().size());
		bundle.putInt("b2", endList.getListb2().size());
		bundle.putInt("b3", endList.getListb3().size());
		bundle.putInt("b4", endList.getListb4().size());
		bundle.putInt("b5", endList.getListb5().size());
		i.putExtras(bundle);
		startActivity(i);

	}

}
