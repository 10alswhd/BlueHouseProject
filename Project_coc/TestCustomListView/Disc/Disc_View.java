package ex1.view;

import ex1.vo.Disc_EndCart;
import android.R.color;
import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.view.SurfaceHolder;
import android.view.View;
import android.view.WindowManager;

public class Disc_View extends View {
	
	Context context;
	Disc_EndCart car;
	int a1,a2,a3,a4,b1,b2,b3,b4;
	
	
	
	Canvas c;
	
	int i;

	public Disc_View(Context context, int i) {
		super(context);
		this.context = context;
		this.i = i;
		car = new Disc_EndCart();

		
	}

	@Override
	protected void onDraw(Canvas canvas) {
		
		super.onDraw(canvas);
		c = canvas;
		Paint p = new Paint();
		p.setTextSize(70);
		p.setColor(Color.GREEN);
		c.drawText("D", 30, 220, p);
		c.drawText("I", 130, 220, p);
		c.drawText("S", 230, 220, p);
		c.drawText("C", 330, 220, p);
		
		
		if (i == 1)
		addcart1();
		if (i ==2)
		addcart2();
		if (i == 3)
		addcart3();
		
	}
	
	
	
	
	
	

	private void addcart3() {
		car.Disc_EndCart3(a1, a2, a3, a4, b1, b2, b3, b4);
		
		Paint p = new Paint();
		p.setStrokeWidth(5);
		p.setColor(Color.WHITE);
		
		c.drawLine(50, 300-car.getEx1(),150, 300-car.getEx2(), p);
		c.drawLine(150, 300-car.getEx2(), 250, 300-car.getEx3(), p);
		c.drawLine(250, 300-car.getEx3(), 350, 300-car.getEx4(), p);
		
		
		
	}

	private void addcart2() {
		

		
		car.Disc_EndCart2(b1, b2, b3, b4);
		
		Paint p = new Paint();
		p.setStrokeWidth(5);
		p.setColor(Color.WHITE);
		
		c.drawLine(50, 50+car.getCb1(), 150, 50+car.getCb2(), p);
		c.drawLine(150, 50+car.getCb2(), 250, 50+car.getCb3(), p);
		c.drawLine(250, 50+car.getCb3(), 350, 50+car.getCb4(), p);
		
	}





private void addcart1() {
	
	

	car.Disc_EndCart1(a1, a2, a3, a4);
	
	Paint p = new Paint();
	p.setStrokeWidth(5);
	p.setColor(Color.WHITE);
	
	c.drawLine(50, 300-car.getCa1(),150, 300-car.getCa2(), p);
	c.drawLine(150, 300-car.getCa2(), 250, 300-car.getCa3(), p);
	c.drawLine(250, 300-car.getCa3(), 350, 300-car.getCa4(), p);
	
	
	
	
	
}







public void Viewdata(int a1, int a2, int a3, int a4, int b1,
		int b2, int b3, int b4) {
	this.a1 = a1;
	this.a2 = a2;
	this.a3 = a3;
	this.a4 = a4;
	this.b1 = b1;
	this.b2 = b2;
	this.b3 = b3;
	this.b4 = b4;
	
}









}
