void foo(final String text) throws IOException{
    final Paint textPaint = new Paint() {
        {
            setColor(Color.WHITE);
            setTextAlign(Paint.Align.LEFT);
            setTextSize(20f);
            setAntiAlias(true);
        }
    };
    final Rect bounds = new Rect();
    textPaint.getTextBounds(text, 0, text.length(), bounds);

    final Bitmap bmp = Bitmap.createBitmap(bounds.width(), bounds.height(), Bitmap.Config.RGB_565); //use ARGB_8888 for better quality
    final Canvas canvas = new Canvas(bmp);
    canvas.drawText(text, 0, 20f, textPaint);
    FileOutputStream stream = new FileOutputStream(...); //create your FileOutputStream here
    bmp.compress(CompressFormat.PNG, 85, stream);
    bmp.recycle();
    stream.close();
}
