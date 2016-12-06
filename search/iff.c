import org.json.*;

String apiKey = "b097268516fb976e75bb5caf73859ffc:8:73601342";
String baseURL = "http://api.nytimes.com/svc/search/v2/articlesearch.json?";

void setup() {  
  getOJArticles();  
};
void draw() {
};

void getOJArticles() {
String request = baseURL + "q=O.J.+Simpson&begin_date=19940101&end_date=19960101&api-key=" + apiKey;
  try {
    org.json.JSONObject nytData = new org.json.JSONObject(join(loadStrings(request), ""));
    int hits = nytData.getJSONObject("response").getJSONObject("meta").getInt("hits");
    println ("RESULTS ABOUT O.J.:" + hits);
  }
  catch (JSONException e) {
    println ("There was an error parsing the JSONObject.");
  }  
}
