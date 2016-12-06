package lee.whdghks913.customlistview;

import java.util.ArrayList;
import java.util.Collections;

import android.app.Activity;
import android.content.Context;
import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends Activity {
    private ListView mListView = null;
    private ListViewAdapter mAdapter = null;
    
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        mListView = (ListView) findViewById(R.id.mList);
        
        mAdapter = new ListViewAdapter(this);
        mListView.setAdapter(mAdapter);
        
        mAdapter.addItem(getResources().getDrawable(R.drawable.ok),
                "확인이 완료되었습니다",
                "2014-02-18");
        mAdapter.addItem(getResources().getDrawable(R.drawable.idonknow),
                "난 몰라요 ㅠㅠ",
                "2014-02-01");
        mAdapter.addItem(getResources().getDrawable(R.drawable.supersu),
                "슈퍼유저~~",
                "2014-02-04");
        mAdapter.addItem(null,
                "이미지가 null이면...",
                "2014-02-15");
        
        mListView.setOnItemClickListener(new OnItemClickListener() {

            @Override
            public void onItemClick(AdapterView<?> parent, View v, int position, long id){
                ListData mData = mAdapter.mListData.get(position);
                Toast.makeText(MainActivity.this, mData.mTitle, Toast.LENGTH_SHORT).show();
            }
        });
    }
    
    private class ViewHolder {
        public ImageView mIcon;
        
        public TextView mText;
        
        public TextView mDate;
    }
    
    private class ListViewAdapter extends BaseAdapter {
        private Context mContext = null;
        private ArrayList<ListData> mListData = new ArrayList<ListData>();
        
        public ListViewAdapter(Context mContext) {
            super();
            this.mContext = mContext;
        }
        
        @Override
        public int getCount() {
            return mListData.size();
        }

        @Override
        public Object getItem(int position) {
            return mListData.get(position);
        }

        @Override
        public long getItemId(int position) {
            return position;
        }
        
        public void addItem(Drawable icon, String mTitle, String mDate){
            ListData addInfo = null;
            addInfo = new ListData();
            addInfo.mIcon = icon;
            addInfo.mTitle = mTitle;
            addInfo.mDate = mDate;
            
            mListData.add(addInfo);
        }
        
        public void remove(int position){
            mListData.remove(position);
            dataChange();
        }
        
        public void sort(){
            Collections.sort(mListData, ListData.ALPHA_COMPARATOR);
            dataChange();
        }
        
        public void dataChange(){
            mAdapter.notifyDataSetChanged();
        }
        
        @Override
        public View getView(int position, View convertView, ViewGroup parent) {
            ViewHolder holder;
            if (convertView == null) {
                holder = new ViewHolder();
                
                LayoutInflater inflater = (LayoutInflater) mContext.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
                convertView = inflater.inflate(R.layout.listview_item, null);
                
                holder.mIcon = (ImageView) convertView.findViewById(R.id.mImage);
                holder.mText = (TextView) convertView.findViewById(R.id.mText);
                holder.mDate = (TextView) convertView.findViewById(R.id.mDate);
                
                convertView.setTag(holder);
            }else{
                holder = (ViewHolder) convertView.getTag();
            }
            
            ListData mData = mListData.get(position);
            
            if (mData.mIcon != null) {
                holder.mIcon.setVisibility(View.VISIBLE);
                holder.mIcon.setImageDrawable(mData.mIcon);
            }else{
                holder.mIcon.setVisibility(View.GONE);
            }
            
            holder.mText.setText(mData.mTitle);
            holder.mDate.setText(mData.mDate);
            
            return convertView;
        }
    }
}
