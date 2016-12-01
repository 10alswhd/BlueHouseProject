//where we want to download it from
    URL url = new URL(IMAGE_URL);  //http://example.com/image.jpg
    //open the connection
    URLConnection ucon = url.openConnection();
    //buffer the download
    InputStream is = ucon.getInputStream();
    BufferedInputStream bis = new BufferedInputStream(is,128);
    ByteArrayBuffer baf = new ByteArrayBuffer(128);
    //get the bytes one by one
    int current = 0;
    while ((current = bis.read()) != -1) {
            baf.append((byte) current);
    }
     
    //store the data as a ByteArray
    //db is a SQLiteDatabase object
    ContentValues dataToInsert = new ContentValues();                          
    dataToInsert.put(TABLE_FIELD,baf.toByteArray());
    db.insert(TABLE_NAME, null, dataToInsert);

//////////////And this is how you get the data back and convert it into a Bitmap:

    //select the data
    Cursor cursor = db.query(TABLE_STATIONLIST, new String[] {TABLE_FIELD},
                                                    null, null, null, null, null);
    //get it as a ByteArray
    byte[] imageByteArray=cursor.getBlob(1);
    //the cursor is not needed anymore
    cursor.close();
     
    //convert it back to an image
    ByteArrayInputStream imageStream = new ByteArrayInputStream(mybyte);
    Bitmap theImage = BitmapFactory.decodeStream(imageStream));
