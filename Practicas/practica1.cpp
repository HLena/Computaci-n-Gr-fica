#include <fstream>
using namespace std;
int ndh=1024,ndv=720; // resolucion de pantalla
float ndcx,ndcy; //cordenada normalizada
int ndhm1,ndvm1;
int width, height;
int pcx,pcy;
int xmax,xmin;
int ymax,ymin;
int x,y,dcx,dcy;
void inpt_to_ndc(int dcx, int dcy){
	ndcx = (float)dcx / ndhm1;
	ndcy = (float)dcy / ndvm1;
	printf("ndcx: %f ndcy: %f\n",ndcx,ndcy);
}

void ndc_to_user(float ndcx, float ndcy){
	x = (int)ndcx * (xmax-xmin)+xmin;
	y = (int)ndcy * (ymax-ymin)+ymin;
	printf("x: %d y: %d\n",x,y);
}

void user_to_ndc( int x, int y){
	ndcx = (x - xmin) /(xmax -xmin);
	ndcy = (y - ymin) /(ymax -ymin);
	printf("ndcx: %f ndcy: %f\n",ndcx,ndcy);
}

void ndc_to_dc(int ndcx, int ndcy){
	dcx = ndcx * ndhm1;
	dcy = ndcy * ndvm1;
	printf("dcx: %f dcy: %f\n",dcx,dcy);
}

int main(int argc, char const *argv[])
{
	ndhm1 = ndh -1; ndvm1 = ndv - 1;
	dcx = 100;  dcy =567;
	xmax = 1; xmin=-1;
	//inpt_to_ndc(dcx,dcy);
	ndc_to_user(0.5,-0.5);
	return 0;
}