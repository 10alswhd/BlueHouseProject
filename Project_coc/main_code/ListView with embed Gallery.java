package com.rnaud.karma;

import java.util.ArrayList;

import android.content.Context;
import android.content.Intent;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.BaseAdapter;
import android.widget.Gallery;
import android.widget.TextView;

public class MissionListAdapter2 extends BaseAdapter {
private LayoutInflater mInflater;
private Context context;
private static ArrayList missions;
private static ArrayList missionsGridAdapters;

    public MissionListAdapter2(Context c, ArrayList<Mission> m) {
        mInflater = LayoutInflater.from(c);
        context = c;
        missions = m;
        this.missionsGridAdapters = new ArrayList<MissionGridAdapter2>(10);
    }

    public int getCount() {
        return missions.size();
    }

    public Object getItem(int position) {
        return missions.get(position);
    }

    public long getItemId(int position) {
        return position;
    }

    public View getView(int position, View convertView, ViewGroup parent) {
        ViewHolder holder;

        if (convertView == null) {
            convertView = mInflater.inflate(R.layout.missions_list_item, null);

            holder = new ViewHolder();
            holder.text = (TextView) convertView.findViewById(R.id.TextView02);
            holder.subtitle = (TextView) convertView.findViewById(R.id.subtitle);
            holder.gallery = (Gallery) convertView.findViewById(R.id.gallery_mission);

            convertView.setTag(holder);
        } else {
            holder = (ViewHolder) convertView.getTag();
        }

        // Bind the data efficiently with the holder.
        holder.m = missions.get(position);
        holder.text.setText(holder.m.name);
        holder.text.setTag(holder.m.id+"");

        int mission_feats = holder.m.photos_count;
        String status;
        if (holder.m.wit == null) {
            status = "you haven't done it";
        } else if (holder.m.wit.status == 0) {
            status = "running mission";
        } else {
            status = "mission done";
        }

        holder.subtitle.setText(mission_feats+ " feats done, "+ status);

        MissionGridAdapter2 gridAdapter = null;

        this.missionsGridAdapters.ensureCapasity(position + 1);

        try {
            gridAdapter = this.missionsGridAdapters.get(position);
        }
        catch(IndexOutOfBoundsException e) {
            // ooops adapter is missed - create one now
            // May be pass position in the constructor to allow this instance of MissionGridAdapter2 to get proper data
            gridAdapter = new MissionGridAdapter2(context, holder.m.photos);
            this.missionsGridAdapter.add(position, gridAdapter);
        }

        holder.gallery.setAdapter(gridAdapter);
        // Not sure if it needed to reset selection every time...
        holder.gallery.setSelection((int)( holder.m.photos.size()/2) );
        holder.gallery.setOnItemClickListener(new OnItemClickListener() {
            public void onItemClick(AdapterView<?> parent, View v, int position, long id) {
                long p_id = Long.valueOf(v.getTag().toString());
                Intent i = new Intent(context, PhotoPage.class);
                i.putExtra(KarmaDbAdapter.PHOTO_ID, p_id);
                context.startActivity(i);
            }
        });


        return convertView;
    }

    static class ViewHolder {
        TextView text;
        TextView subtitle;
        Gallery gallery;
        Mission m;
    }
}
