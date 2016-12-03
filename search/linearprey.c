#include <windows.h>
int main(int argc, char **argv)
{
	int x          = 0;
	// Posiciones límite //
	int uppery     = 170;
	int downy      = 600;
	int leftx      = 285;
	int rightx     = 725;
	int initleftx  = 285;
	int inituppery = 170;
	int iterations = 1; // Pasadas de la búsqueda lineal - Configurable - //
	int offsetx    = 1; // Pixel a pixel en el eje x - Configurable - //
	int offsety    = 1; // Pixel a pixel en el eje y - Configurable - //
	// LU 285,170 | RU 725,170 | RD 725,600 | LD 285,600 //
	SetCursorPos(leftx,uppery);
	for(x=0;x<iterations;x++){
		for(uppery=inituppery;uppery<=downy;uppery+=offsety){
			for(leftx=initleftx;leftx<=rightx;leftx+=offsetx){
				SetCursorPos(leftx,uppery);
				mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
				mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
			}
		}
	}
	return 0;
}
