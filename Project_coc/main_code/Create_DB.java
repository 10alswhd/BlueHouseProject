import java.util.ArrayList;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import java.util.UUID;

public class Database extends SQLiteOpenHelper {

	public Database(Context context) {
		super(context, "products", null, 1);//modify here
	}

	@Override
	public void onCreate(SQLiteDatabase db) {
	  //modify this query to create your own table
		String sql =
			        "CREATE TABLE IF NOT EXISTS products "+
				"(id INTEGER PRIMARY KEY AUTOINCREMENT,"+ 
				" uid TEXT NOT NULL, " +		
				" names TEXT NOT NULL, " +
				" quantity INTEGER NOT NULL," +				
				" status TEXT NOT NULL)";
		db.execSQL(sql);
	}

	@Override
	public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
		String sql="DROP TABLE IF EXISTS products";//modify to suit your table
		db.execSQL(sql);		
	}
   	/**
	 * Saves an item into sqlite database
	 * @param names
	 * @param quantity
	 */
	public void save(String names, int quantity)//Modify here to suit what you want to save
	{
	  SQLiteDatabase db=this.getWritableDatabase();
	  ContentValues values=new ContentValues();
	  values.put("names", names);//modify here
	  values.put("quantity", quantity);//modify here
	  values.put("status", "no");//modify here
	  db.insert("products", null, values);//modify here
	  db.close();
	}
	/**
	 * Fetches all unsynced records from the database
	 * Where the status is no
	 * @return
	 */
	public ArrayList<Product> fetch()////modify here
	{
		ArrayList<Product> data=new ArrayList<Product>();////modify here
		SQLiteDatabase db=this.getReadableDatabase();
		String sql="SELECT * FROM products";//modify here
		Cursor cursor= db.rawQuery(sql, null);
		if(cursor.moveToFirst())
		{
		  do
		  {
			String uid= cursor.getString(1); //modify here
			String names= cursor.getString(2);//modify here
			int quantity= cursor.getInt(3);//modify here
			Product p=new Product();//modify here
			p.setNames(names);//modify here
			p.setQuantity(quantity);//modify here
			p.setUid(uid);//modify here
			data.add(p);//modify here			
		  }while(cursor.moveToNext());	//modify here
		}
		return data;
	}
	/**
	 * Counts All  Records in sqlite
	 * @return
	 */
	public int count()
	{
		SQLiteDatabase db=this.getReadableDatabase();
		String sql="SELECT * FROM products";//modify here
		Cursor cursor =db.rawQuery(sql, null);		
		return cursor.getCount();
	}
}
