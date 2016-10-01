package com.cookandroid.self9_3;

import android.app.Activity;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.BlurMaskFilter;
import android.graphics.Canvas;
import android.graphics.ColorMatrix;
import android.graphics.ColorMatrixColorFilter;
import android.graphics.EmbossMaskFilter;
import android.graphics.Paint;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageButton;
import android.widget.LinearLayout;

public class MainActivity extends Activity {

	ImageButton ibZoomin, ibZoomout, ibRotate, ibBright, ibDark, ibBlur,
			ibEmbos;
	MyGraphicView graphicView;

	static float scaleX = 1, scaleY = 1;
	static float angle = 0;
	static float satur = 1;
	static boolean blur = false;
	static boolean embos = false;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		setTitle("미니 포토샵 (개선)");

		LinearLayout pictureLayout = (LinearLayout) findViewById(R.id.pictureLayout);
		graphicView = (MyGraphicView) new MyGraphicView(this);
		pictureLayout.addView(graphicView);

		clickIcons();
	}

	private void clickIcons() {
		ibZoomin = (ImageButton) findViewById(R.id.ibZoomin);
		ibZoomin.setOnClickListener(new View.OnClickListener() {
			public void onClick(View v) {
				scaleX = scaleX + 0.2f;
				scaleY = scaleY + 0.2f;
				graphicView.invalidate();
			}
		});

		ibZoomout = (ImageButton) findViewById(R.id.ibZoomout);
		ibZoomout.setOnClickListener(new View.OnClickListener() {
			public void onClick(View v) {
				scaleX = scaleX - 0.2f;
				scaleY = scaleY - 0.2f;
				graphicView.invalidate();
			}
		});

		ibRotate = (ImageButton) findViewById(R.id.ibRotate);
		ibRotate.setOnClickListener(new View.OnClickListener() {
			public void onClick(View v) {
				angle = angle + 20;
				graphicView.invalidate();
			}
		});

		ibBright = (ImageButton) findViewById(R.id.ibBright);
		ibBright.setOnClickListener(new View.OnClickListener() {
			public void onClick(View v) {
				satur = satur + 0.2f;
				graphicView.invalidate();
			}
		});

		ibDark = (ImageButton) findViewById(R.id.ibDark);
		ibDark.setOnClickListener(new View.OnClickListener() {
			public void onClick(View v) {
				satur = satur - 0.2f;
				graphicView.invalidate();
			}
		});

		ibBlur = (ImageButton) findViewById(R.id.ibBlur);
		ibBlur.setOnClickListener(new View.OnClickListener() {
			public void onClick(View v) {
				if (blur == true)
					blur = false;
				else
					blur = true;
				graphicView.invalidate();
			}
		});

		ibEmbos = (ImageButton) findViewById(R.id.ibEmbos);
		ibEmbos.setOnClickListener(new View.OnClickListener() {
			public void onClick(View v) {
				if (embos == true)
					embos = false;
				else
					embos = true;
				graphicView.invalidate();
			}
		});

	}

	private static class MyGraphicView extends View {
		public MyGraphicView(Context context) {
			super(context);
		}

		@Override
		protected void onDraw(Canvas canvas) {
			super.onDraw(canvas);

			int cenX = this.getWidth() / 2;
			int cenY = this.getHeight() / 2;
			canvas.scale(scaleX, scaleY, cenX, cenY);
			canvas.rotate(angle, cenX, cenY);

			Paint paint = new Paint();
			ColorMatrix cm = new ColorMatrix();
			cm.setSaturation(satur);

			paint.setColorFilter(new ColorMatrixColorFilter(cm));

			if (blur == true) {
				BlurMaskFilter bMask;
				bMask = new BlurMaskFilter(30, BlurMaskFilter.Blur.NORMAL);
				paint.setMaskFilter(bMask);
			}

			if (embos == true) {
				EmbossMaskFilter eMask;
				eMask = new EmbossMaskFilter(new float[] { 3, 3, 3 }, 0.5f, 5,
						10);
				paint.setMaskFilter(eMask);
			}

			Bitmap picture = BitmapFactory.decodeResource(getResources(),
					R.drawable.lena256);
			int picX = (this.getWidth() - picture.getWidth()) / 2;
			int picY = (this.getHeight() - picture.getHeight()) / 2;
			canvas.drawBitmap(picture, picX, picY, paint);

			picture.recycle();
		}
	}

}
