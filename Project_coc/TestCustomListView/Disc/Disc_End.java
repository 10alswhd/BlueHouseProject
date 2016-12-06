package ex1.test;

import com.google.ads.AdRequest;
import com.google.ads.AdSize;
import com.google.ads.AdView;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.TextView;
import ex1.view.Disc_View;

public class Disc_End extends Activity {
	
	Intent i;
	int a1,a2,a3,a4,a5,b1,b2,b3,b4,b5, ck;
	Disc_View dv, dv2, dv3;
	
	RelativeLayout myR, yourR,exR;
	TextView myt,yourt;
	
	Button bd,bi,bs,bc;
	private final String adstring= "a14e71a9bd1850a";
	LinearLayout layout;
	AdView ad;
	
	protected void onCreate(Bundle savedInstanceState) {
		
		super.onCreate(savedInstanceState);
		setContentView(R.layout.end);
		
		layout = (LinearLayout) findViewById(R.id.endadview);
		ad = new AdView(this, AdSize.BANNER, adstring);
		layout.addView(ad);
		ad.loadAd(new AdRequest());
		
		
		bd = (Button) findViewById(R.id.Disc_enddiscD);
		bi = (Button) findViewById(R.id.Disc_enddiscI);
		bs = (Button) findViewById(R.id.Disc_enddiscS);
		bc = (Button) findViewById(R.id.Disc_enddiscC);
		
		
		myR = (RelativeLayout) findViewById(R.id.Disc_endMydisc);
		yourR = (RelativeLayout) findViewById(R.id.Disc_endyourdisc);
		exR = (RelativeLayout) findViewById(R.id.Disc_endexdisc);
		
		
		myt = (TextView) findViewById(R.id.Disc_endMydisc_Text);
		yourt = (TextView) findViewById(R.id.Disc_endyourdisc_Text);
		
		
		dv = new Disc_View(getApplicationContext(),1);
		dv2 = new Disc_View(getApplicationContext(),2);
		dv3 = new Disc_View(getApplicationContext(),3);
		
		
		
		i = getIntent();
		Bundle bundle = i.getExtras();
		
		a1 = bundle.getInt("a1");
		a2 = bundle.getInt("a2");
		a3 = bundle.getInt("a3");
		a4 = bundle.getInt("a4");
		a5 = bundle.getInt("a5");
		
		b1 = bundle.getInt("b1");
		b2 = bundle.getInt("b2");
		b3 = bundle.getInt("b3");
		b4 = bundle.getInt("b4");
		b5 = bundle.getInt("b5");
		
		dv.Viewdata(a1,a2,a3,a4,b1,b2,b3,b4);
		dv2.Viewdata(a1,a2,a3,a4,b1,b2,b3,b4);
		dv3.Viewdata(a1,a2,a3,a4,b1,b2,b3,b4);
		

		myR.addView(dv);
		myt.setText("부적응 지수 : "+a5);
		
		yourR.addView(dv2);
		yourt.setText("부적응 지수 : "+b5);
		
		exR.addView(dv3);
		
		
		
		
	}
	
	public void onon(View v){
		switch (v.getId()) {
		case R.id.Disc_enddiscD:
			ck = 0;
			break;

		case R.id.Disc_enddiscI:
			ck=1;
			break;
		case R.id.Disc_enddiscS:
			ck=2;
			break;
		case R.id.Disc_enddiscC:
			ck=3;
			break;
				
		}
		
		Intent i = new Intent(getApplicationContext(),Disc_End_list.class);
		Bundle bundle = new Bundle();
		bundle.putInt("ck", ck);
		i.putExtras(bundle);
		startActivity(i);
		
		
		
	}
	
}
