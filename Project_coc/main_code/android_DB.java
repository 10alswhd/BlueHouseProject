package com.database.project;

import android.app.Activity;
import android.content.SharedPreferences;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.os.Bundle;
import android.widget.Toast;

public class DatabaseProjectActivity extends Activity {
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        
      SharedPreferences settings = getSharedPreferences("DATA", 0);
      String DataStatus = settings.getString("loaded", "no");
      
      if(DataStatus.equals("no"))
      {
    	  CreateDatabase();
    	  SharedPreferences.Editor edittor = settings.edit();
    	  edittor.putString("loaded", "yes");
    	  edittor.commit();
      } else {
    	  
    	  readRecord();
      }
        
    }
    
    public void CreateDatabase()
    {
    	SQLiteDatabase db = openOrCreateDatabase("MyDb", MODE_PRIVATE, null);
    	
    	String sql = "CREATE TABLE IF NOT EXISTS MyTable ( " + "FirstName VARCHAR, " + "LastName VARCHAR, " + "Age INT(3))";
    	db.execSQL(sql);
    	
    	String insertSql = "INSERT INTO MyTable VALUES ('Rahim','Karim',23)";
    	
    	db.execSQL(insertSql);
    	db.close();		
    }
    
    public void readRecord()
    {
    	SQLiteDatabase db = openOrCreateDatabase("MyDb", MODE_PRIVATE, null);
    	String sql = "Select * from MyTable";
    	Cursor c = db.rawQuery(sql, null);
    	c.moveToFirst();
    	String name  = c.getString(c.getColumnIndex("FirstName"));
    	Toast.makeText(getApplicationContext(), name, 10000).show();
    	
    	db.close();		
    }
    
    
}
