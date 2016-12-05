package sample3;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.AlertDialog.Builder;
import android.content.DialogInterface;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.LinearLayout;
//import android.widget.TextView;
import android.widget.Toast;

public class javaActivity extends Activity {
	Button[] bt = new Button[10];
	int count=0;
	int [] t = {0,0,0,0,0,0,0,0,0};
	//1~9のボタンクリック時
	public class Click implements OnClickListener {
		@Override
		public void onClick(View v) {
			// TODO 自動生成されたメソッド・スタブ
			if(v.getTag()=="a"){
				if(t[0]==0){
	    			if(count%2==0){
	    				bt[0].setText("○");
	    			}
	    			else{
	    				bt[0].setText("×");
	    			}
	    			t[0] = count%2+1;
	    			count+=1;
	    			check();
	    		}
			}else if(v.getTag()=="b"){
				if(t[1]==0){
	    			if(count%2==0){
	    				bt[1].setText("○");
	    			}
	    			else{
	    				bt[1].setText("×");
	    			}
	    			t[1] = count%2+1;
	    			count+=1;
	    			check();
	    		}
			}else if(v.getTag()=="c"){
				if(t[2]==0){
	    			if(count%2==0){
	    				bt[2].setText("○");
	    			}
	    			else{
	    				bt[2].setText("×");
	    			}
	    			t[2] = count%2+1;
	    			count+=1;
	    			check();
	    		}
			}else if(v.getTag()=="d"){
				if(t[3]==0){
	    			if(count%2==0){
	    				bt[3].setText("○");
	    			}
	    			else{
	    				bt[3].setText("×");
	    			}
	    			t[3] = count%2+1;
	    			count+=1;
	    			check();
	    		}
			}else if(v.getTag()=="e"){
				if(t[4]==0){
	    			if(count%2==0){
	    				bt[4].setText("○");
	    			}
	    			else{
	    				bt[4].setText("×");
	    			}
	    			t[4] = count%2+1;
	    			count+=1;
	    			check();
	    		}
			}else if(v.getTag()=="f"){
				if(t[5]==0){
	    			if(count%2==0){
	    				bt[5].setText("○");
	    			}
	    			else{
	    				bt[5].setText("×");
	    			}
	    			t[5] = count%2+1;
	    			count+=1;
	    			check();
	    		}
			}else if(v.getTag()=="g"){
				if(t[6]==0){
	    			if(count%2==0){
	    				bt[6].setText("○");
	    			}
	    			else{
	    				bt[6].setText("×");
	    			}
	    			t[6] = count%2+1;
	    			count+=1;
	    			check();
	    		}
			}else if(v.getTag()=="h"){
				if(t[7]==0){
	    			if(count%2==0){
	    				bt[7].setText("○");
	    			}
	    			else{
	    				bt[7].setText("×");
	    			}
	    			t[7] = count%2+1;
	    			count+=1;
	    			check();
	    		}
			}else if(v.getTag()=="i"){
				if(t[8]==0){
	    			if(count%2==0){
	    				bt[8].setText("○");
	    			}
	    			else{
	    				bt[8].setText("×");
	    			}
	    			t[8] = count%2+1;
	    			count+=1;
	    			check();
	    		}
			}
		}

	}
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Toast.makeText(this, "○×ゲームを開始します", Toast.LENGTH_LONG).show();
        LinearLayout ll =new LinearLayout(this);
        LinearLayout ll2 =new LinearLayout(this);
        LinearLayout ll3 =new LinearLayout(this);
        LinearLayout ll4 =new LinearLayout(this);
        LinearLayout ll5 =new LinearLayout(this);
        ll.addView(ll2);//LinearLayout.HORIZONTAL);
        ll.addView(ll3);
        ll.addView(ll4);
        ll.addView(ll5);
        ll2.setOrientation(LinearLayout.VERTICAL);
        ll3.setOrientation(LinearLayout.VERTICAL);
        ll4.setOrientation(LinearLayout.VERTICAL);
        ll5.setOrientation(LinearLayout.VERTICAL);
        setContentView(ll);
        for(int i=0;i<10;i++){
        	if(i<3){
        		bt[i] = new Button(this);
        		bt[i].setText(Integer.toString(i+1));
        		ll2.addView(bt[i]);
        		bt[i].setHeight(100);
        	}
        	else if(i<6){
        		bt[i] = new Button(this);
        		bt[i].setText(Integer.toString(i+1));
        		ll3.addView(bt[i]);
        		bt[i].setHeight(100);
        	}
        	else if(i<9){
        		bt[i] = new Button(this);
        		bt[i].setText(Integer.toString(i+1));
        		ll4.addView(bt[i]);
        		bt[i].setHeight(100);
        	}
        	if(i==9){
        		bt[i] = new Button(this);
        		bt[i].setText("リセット");
        		ll5.addView(bt[i]);
        		bt[i].setHeight(150);
        	}
        	bt[i].setWidth(100);
        }
        bt[0].setTag("a");
        bt[1].setTag("b");
        bt[2].setTag("c");
        bt[3].setTag("d");
        bt[4].setTag("e");
        bt[5].setTag("f");
        bt[6].setTag("g");
        bt[7].setTag("h");
        bt[8].setTag("i");
        
        
        bt[9].setOnClickListener(new SampleClickListener());
        for(int z=0;z<9;z++){
        	bt[z].setOnClickListener(new Click());
        }
        
    }
	
    //リセットボタンクリック時
    class SampleClickListener implements OnClickListener{
    	public void onClick(View v){
    		AlertDialog.Builder ab =
    		new AlertDialog.Builder(javaActivity.this);
    			ab.setTitle("リセット");
    			ab.setMessage("本当にいいですか？");
    			ab.setPositiveButton("はい",new SampleDialogClickListener());
    			ab.setNegativeButton("いいえ",null).show();
    	}
    }
    //リセット⇒はいクリック時
    class SampleDialogClickListener implements DialogInterface.OnClickListener{
    	public void onClick(DialogInterface d,int w/*View v*/){
    		for(count=9;count>0;count--){
    			bt[count-1].setText(Integer.toString(count));
    			t[count-1] = 0;
    		}
    	}
    }
    void check(){
    	if(t[0]==1&&t[1]==1&&t[2]==1||t[3]==1&&t[4]==1&&t[5]==1||t[6]==1&&t[7]==1&&t[8]==1||
    			t[0]==1&&t[3]==1&&t[6]==1||t[1]==1&&t[4]==1&&t[7]==1||t[2]==1&&t[5]==1&&t[8]==1||
    	          t[0]==1&&t[4]==1&&t[8]==1||t[2]==1&&t[4]==1&&t[6]==1){
    	        	Toast.makeText(this, "○ win", Toast.LENGTH_LONG).show();
    	}
    	else if(t[0]==2&&t[1]==2&&t[2]==2||t[3]==2&&t[4]==2&&t[5]==2||t[6]==2&&t[7]==2&&t[8]==2||
    	                t[0]==2&&t[3]==2&&t[6]==2||t[1]==2&&t[4]==2&&t[7]==2||t[2]==2&&t[5]==2&&t[8]==2||
    	                t[0]==2&&t[4]==2&&t[8]==2||t[2]==2&&t[4]==2&&t[6]==2){
    	        	Toast.makeText(this, "× win", Toast.LENGTH_LONG).show();
        }
    	else if(count==9){
    		Toast.makeText(this, "even", Toast.LENGTH_LONG).show();
    	}
    }
}
