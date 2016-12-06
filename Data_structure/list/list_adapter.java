package android.dlna.cp;

import java.util.List;

import android.content.Context;
import android.dlna.R;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

public class ServerList_Adapter  extends ArrayAdapter<String>{

	int resource;
	
	public ServerList_Adapter(Context context, int textViewResourceId,
			List<String> objects) {
		super(context, textViewResourceId, objects);
		this.resource = textViewResourceId; 
	}

	@Override
	public View getView(int position, View convertView, ViewGroup parent) {
		// TODO Auto-generated method stub
		LinearLayout row;
		String str = getItem(position);
		if(convertView == null){
			row = new LinearLayout(getContext());
			LayoutInflater vi = (LayoutInflater)getContext().getSystemService(Context.LAYOUT_INFLATER_SERVICE);
			vi.inflate(resource, row, true);
		} else{
			row = (LinearLayout) convertView;
		}
		
		ImageView iv = (ImageView)row.findViewById(R.id.imageView1);
		TextView tv = (TextView)row.findViewById(R.id.serverlist_textView);
		iv.setImageResource(R.drawable.music);
		tv.setText(str);
		Log.e("test", "hhh");
		
		
		return row;
	}

	
	
}
