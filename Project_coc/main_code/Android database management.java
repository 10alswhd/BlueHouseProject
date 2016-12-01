package me.frozened.ideafactory.db;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteDatabase.CursorFactory;
import android.database.sqlite.SQLiteOpenHelper;

public class Database extends SQLiteOpenHelper{
	
	/*--------------------------------------------------------------*/
	/* 			 PROJECT 			 */
	/*--------------------------------------------------------------*/
	public static final String TABLE_PROJECT = 	"Project";
	
	public static String COL_PROJECT_ID = 		"project_id";
	public static String COL_PROJECT_NAME = 	"project_name";
	public static String COL_PROJECT_DESCRIPTION = 	"project_description";
	public static String COL_PROJECT_STATE = 	"project_state";
	public static String COL_PROJECT_STARTDATE = 	"project_start_date";
	public static String COL_PROJECT_ENDDATE = 	"project_end_date";
	public static String COL_PROJECT_FAVORITE = 	"project_favorite";
	
	private static final String[][] COLS_PROJECT = { 
		{COL_PROJECT_ID, 			"INTEGER PRIMARY KEY AUTOINCREMENT"},
		{COL_PROJECT_NAME, 			"TEXT NOT NULL"},
		{COL_PROJECT_DESCRIPTION, 		"TEXT NOT NULL"},
		{COL_PROJECT_STATE, 			"INTEGER NOT NULL"},
		{COL_PROJECT_STARTDATE, 		"TEXT"},
		{COL_PROJECT_ENDDATE, 			"TEXT"},
		{COL_PROJECT_FAVORITE, 			"INTEGER NOT NULL"}
	};
	
	/*--------------------------------------------------------------*/
	/* 			 RESOURCE 			 */
	/*--------------------------------------------------------------*/
	public static final String TABLE_RESOURCE = 	"Resource";
	
	public static String COL_RESOURCE_ID = 		"resource_id";
	public static String COL_RESOURCE_NAME = 	"resource_name";
	public static String COL_RESOURCE_POST = 	"resource_post";
	public static String COL_RESOURCE_COST = 	"resource_cost";
	
	private static final String[][] COLS_RESOURCE = { 
		{COL_RESOURCE_ID, 			"INTEGER PRIMARY KEY AUTOINCREMENT"},
		{COL_RESOURCE_NAME, 			"TEXT NOT NULL"},
		{COL_RESOURCE_POST, 			"TEXT"},
		{COL_RESOURCE_COST, 			"REAL"}
	};

	/*======================================================================*/
	/* ---                    DATABASE                         --- */
	/*======================================================================*/
	public Database(Context context, String name, CursorFactory factory, int version) {
		super(context, name, factory, version);
	}

	@Override
	public void onCreate(SQLiteDatabase db) {
		QueryHelper helper = new QueryHelper(db);
		helper.createTable(TABLE_PROJECT, COLS_PROJECT);
	}
	
	@Override
	public void onOpen(SQLiteDatabase db) {
		super.onOpen(db);
	    if (!db.isReadOnly()) {
	        db.execSQL("PRAGMA foreign_keys=ON;");
	    }
	}

	@Override
	public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
		if(oldVersion == 1 && newVersion == 2)
		{
			db.beginTransaction();
			try{
				QueryHelper helper = new QueryHelper(db);
				helper.createTable(TABLE_RESOURCE, COLS_RESOURCE);
				db.setTransactionSuccessful();
			} finally {
				db.endTransaction();
			}
		}
		
	}
Raw

=====================================================================================================

 Passerelle.java
 
 
public class Passerelle {

	private static final int DB_VERSION = 2;
	private static final String DB_NAME = "RandomIt.db";

	private SQLiteDatabase bdd;
	private Database base;

	public Passerelle(Context context) {
		base = new Database(context, DB_NAME, null, DB_VERSION);
	}


	public void open() {
		bdd = base.getWritableDatabase();
	}


	public void close() {
		bdd.close();
	}


	public SQLiteDatabase getBDD() {
		return bdd;
	}


	public static void deleteDatabase(Context context) {
		context.deleteDatabase(DB_NAME);
	}


	public void openExistingDatabase(SQLiteDatabase bdd) {
		this.bdd = bdd;
	}


	/*--------------------------------------------------------------*/
		/* 		Project 			*/
	/*--------------------------------------------------------------*/
	public long insertProject(Project p, boolean update) {

		ContentValues ligne = new ContentValues();
		ligne.put(COL_PROJECT_NAME, p.getName());
		ligne.put(COL_PROJECT_DESCRIPTION, p.getDescription());
		ligne.put(COL_PROJECT_STARTDATE, StringDate.dateToString(p.getStartDate()));
		ligne.put(COL_PROJECT_ENDDATE, StringDate.dateToString(p.getEndDate()));
		ligne.put(COL_PROJECT_STATE, p.getState());
		ligne.put(COL_PROJECT_FAVORITE, p.isFavorite());

		if(!update) {
			long lRow = bdd.insert(TABLE_PROJECT, null, ligne);
			p.setId((int) lRow);
			return lRow;
		}
		else
			return bdd.update(TABLE_PROJECT, ligne, COL_PROJECT_ID + " = " + p.getId(), null);
	}
	

	public int deleteProject(Project p) {
		return bdd.delete(TABLE_PROJECT, COL_PROJECT_ID + " = " + p.getId(), null);
	}


	public Project selectProject(int id) {
		Project project = null;
		String[] cols = new String[] { COL_PROJECT_ID, COL_PROJECT_NAME, COL_PROJECT_DESCRIPTION, COL_PROJECT_STARTDATE, COL_PROJECT_ENDDATE,
				COL_PROJECT_STATE, COL_PROJECT_FAVORITE };

		Cursor c = bdd.query(TABLE_PROJECT, cols, COL_PROJECT_ID + " = " + id, null, null, null, null);

		c.moveToFirst();
		if(!c.isAfterLast())
			project = new Project(c.getInt(0), c.getString(1), c.getString(2), c.getInt(3), StringDate.stringToDate(c.getString(4)),
					StringDate.stringToDate(c.getString(5)), c.getInt(6) != 0);
		c.close();

		return project;
	}


	public ArrayList<Project> selectProjects() {
		ArrayList<Project> list = new ArrayList<Project>();
		String[] cols = new String[] { COL_PROJECT_ID, COL_PROJECT_NAME, COL_PROJECT_DESCRIPTION, COL_PROJECT_STARTDATE, COL_PROJECT_ENDDATE,
				COL_PROJECT_STATE, COL_PROJECT_FAVORITE };

		Cursor c = bdd.query(TABLE_PROJECT, cols, null, null, null, null, COL_PROJECT_FAVORITE + " desc, " + COL_PROJECT_NAME);

		c.moveToFirst();
		while(!c.isAfterLast()) {
			list.add(new Project(c.getInt(0), c.getString(1), c.getString(2), c.getInt(3), StringDate.stringToDate(c.getString(4)),
					StringDate.stringToDate(c.getString(5)), c.getInt(6) != 0));
			c.moveToNext();
		}
		c.close();

		return list;
	}
}
Raw


========================================================================================================
 QueryHelper.java
 
 
package me.frozened.ideafactory.db;

import android.content.ContentValues;
import android.database.sqlite.SQLiteDatabase;

public final class QueryHelper {

	private SQLiteDatabase db;
	
	public QueryHelper(SQLiteDatabase db){
		this.db = db;
	}
	
	public void createTable(String tableName, String[][] colsName){
		this.createTable(tableName, colsName, null, null);
	}
	
	public void createTable(String tableName, String[][] colsName, String[][] foreignKey){
		this.createTable(tableName, colsName, foreignKey, null);
	}
	
	public void createTable(String tableName, String[][] colsName, String[][] foreignKey, String[] primaryKey){
		StringBuilder query = new StringBuilder("CREATE TABLE " + tableName + "(");
		
		for(int i = 0; i < colsName.length; i++){
			if(colsName[i].length == 2)
				query.append(" " + colsName[i][0] + " " + colsName[i][1] + ",");
		}
		query.deleteCharAt(query.length() - 1);
		
		if(primaryKey != null && primaryKey.length >= 1){		/*Multplie primary key*/
			query.append(", PRIMARY KEY (" + primaryKey[0]);
			for(int i = 1; i < primaryKey.length; i++)
				query.append(", " + primaryKey[i]);
			query.append(")");
		}
		
		if(foreignKey != null){
			for(int i = 0; i < foreignKey.length; i++){
				if(foreignKey[i].length == 4){
					query.append(", FOREIGN KEY (" + foreignKey[i][0] + ") REFERENCES " + foreignKey[i][1] + "(" + foreignKey[i][2] + ")");
					if(foreignKey[i][3] != null)
						query.append(" " + foreignKey[i][3]);
				}
			}
		}
		query.append(");");
		db.execSQL(query.toString());
	}
	
	public void insertTable(String tableName, String[] colsName, Object[][] value){
		int i, y;
		
		for(i = 0; i < value.length; i++)
		{
			ContentValues insert = new ContentValues();
			for(y = 0; y < value[i].length; y++)
			{
				if(value[i][y] instanceof String)
					insert.put(colsName[y], (String)value[i][y]);
				else
					insert.put(colsName[y], (Integer)value[i][y]);
			}
			db.insert(tableName, null, insert);
		}
	}
}
