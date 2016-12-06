package android.dlna.cp;

import java.util.ArrayList;

import android.app.Activity;
import android.content.Intent;
import android.dlna.R;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ListView;
import android.widget.AdapterView.OnItemClickListener;

public class ServerList_Activity extends Activity{

	private ListView serverListView;
	private ArrayList<String> list;
	private ServerList_Adapter adapter;
	
	String datas[] = new String[]{"aaaaaa","bbbbbbb","cccccccc","dddddddd"};
	
	public void onCreate(Bundle savedInstanceState) {
		
        super.onCreate(savedInstanceState);
        setContentView(R.layout.serverlist);
        list = new ArrayList<String>();
        for(int i=0; i < datas.length; i++){
        	list.add(datas[i]);
        }
       
        serverListView = (ListView)findViewById(R.id.listView1);
        
        Log.e("test", "bb");
        adapter = new ServerList_Adapter(this, R.layout.list_row, list);
        serverListView.setAdapter(adapter);
        
        //리스트를 클릭했을때
        serverListView.setOnItemClickListener(new OnItemClickListener() {

			@Override
			public void onItemClick(AdapterView<?> arg0, View arg1, int arg2,
					long arg3) {
				//상위 엑티비티에 응답
				Intent i = new Intent();
				i.putExtra("ss", datas[arg2]);
				setResult(RESULT_OK, i);
				finish();
			}
        	
		});
        
        
    }
	
	
}
