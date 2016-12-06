public boolean saveCrimes() {
		try {
			serializer_.saveCrimes(crimes_);
			Log.d(TAG, "crimes saved");
			return true;
		} catch (Exception e) {
			Log.e(TAG, "error saving crimes", e);
			return false;
		}
	}

	private CrimeLab(Context appContext) {
		appContext_ = appContext;		
		serializer_ = new CriminalIntentJSONSerializer(appContext_, FILENAME);
		Log.d(TAG, "try loading crime");
		try {
			crimes_ = serializer_.loadCrimes();
			Log.d(TAG, "crimes loaded");
		} catch (Exception e) {
			crimes_ = new ArrayList<Crime>();
			Log.e(TAG, "Error loading crimes: ", e);
		}
	}


public class CriminalIntentJSONSerializer {
	private Context context_;
	private String fileName_;
	
	public CriminalIntentJSONSerializer(Context context_, String fileName_) {
		super();
		this.context_ = context_;
		this.fileName_ = fileName_;
	}
	
	public void saveCrimes(ArrayList<Crime> crimes) throws JSONException, IOException {
		JSONArray array = new JSONArray();
		for (Crime c : crimes) 
			array.put(c.toJSON());
		Writer writer = null;
		try {
			OutputStream out = context_.openFileOutput(fileName_, Context.MODE_PRIVATE);
			writer = new OutputStreamWriter(out);
			writer.write(array.toString());
		} finally {
			if (writer != null) writer.close();
		}
	}
	
	public ArrayList<Crime> loadCrimes()  throws JSONException, IOException {
		ArrayList<Crime> crimes = new ArrayList<Crime>();
		BufferedReader reader = null;
		try {
			InputStream in = context_.openFileInput(fileName_);
			reader = new BufferedReader(new InputStreamReader(in));
			StringBuilder jsonString = new StringBuilder();
			String line = null;
			while ((line = reader.readLine()) != null) {
				jsonString.append(line);
			}
			JSONArray array = (JSONArray) new JSONTokener(jsonString.toString()).nextValue();
			for (int i = 0; i < array.length(); i++) {
				crimes.add(new Crime(array.getJSONObject(i)));
			}
		} catch (FileNotFoundException e) {
			
		} finally {
			if (reader != null) reader.close();
		}
		return crimes;
	}
}
