package ex1.test;

import com.google.ads.AdRequest;
import com.google.ads.AdSize;
import com.google.ads.AdView;

import android.R.string;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnTouchListener;
import android.widget.FrameLayout;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;

public class DiscActivity extends Activity {
    RelativeLayout r1;
    LinearLayout f;
    String s = "a14e71a9bd1850a";
    AdView ad;
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        f = (LinearLayout) findViewById(R.id.main_layout2);
        
        
        ad = new AdView(this, AdSize.BANNER,s);
        f.addView(ad);
        ad.loadAd(new AdRequest());
        
        
        r1 = (RelativeLayout) findViewById(R.id.main_layout);
        r1.setOnTouchListener(new OnTouchListener() {
			
			public boolean onTouch(View arg0, MotionEvent arg1) {
				Intent i = new Intent(getApplicationContext(),Disc.class);
				startActivity(i);
				return false;
			}
		});
        
        
    }
    public void oon(View v){
    	Intent i = new Intent(getApplicationContext(), Disc_help.class);
    	startActivity(i);
    	
    	
    }
   
}
