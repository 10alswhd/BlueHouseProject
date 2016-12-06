package com.example.androidpro;

import java.util.ArrayList;
import java.util.List;

import android.os.Bundle;
import android.annotation.SuppressLint;
import android.app.Activity;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemSelectedListener;
import android.widget.ArrayAdapter;
import android.widget.Spinner;

@SuppressLint("NewApi")
public class MainActivity extends Activity {
	private static final String LOG_TAG = "AndroidPro";
	private Spinner dataRateSpinner;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		List<String> list = new ArrayList<String>();
		list.add(getResources().getString(R.string.a1));
		list.add(getResources().getString(R.string.a2));
		list.add(getResources().getString(R.string.a3));
		dataRateSpinner = (Spinner) this.findViewById(R.id.data_rate_spinner);
		ArrayAdapter<String> dataRateAdapter = new ArrayAdapter<String>(this,
				android.R.layout.simple_spinner_item);
		dataRateAdapter.addAll(list);
		dataRateSpinner.setAdapter(dataRateAdapter);
		dataRateSpinner.setOnItemSelectedListener(new OnItemSelectedListener() {
			@Override
			public void onItemSelected(AdapterView<?> arg0, View arg1,
					int arg2, long arg3) {
				Log.d(LOG_TAG, "onItemSelected");
			}

			@Override
			public void onNothingSelected(AdapterView<?> arg0) {
				// TODO Auto-generated method stub
				Log.d(LOG_TAG, "onNothingSelected");
			}
		});

	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
