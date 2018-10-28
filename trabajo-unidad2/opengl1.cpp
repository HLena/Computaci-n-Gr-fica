#include <GL/glut.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>
using namespace std;
//g++ turtle.cpp -o g1 -lglut -lGLU -lGL^C compilacion
void init(void){
	glClearColor(1.0,1.0,1.0,1.0); //asigna el color  de la ventana(blanco)
	glClear(GL_COLOR_BUFFER_BIT);// establece parametross de proyeccion
	gluOrtho2D(0.0,200.0,0.0,150.0);
	glPointSize(5);
}
//int round(const double a){ return (int)(a+0.5);}

void setPixel(int x, int y)
{	
    glBegin(GL_POINTS);
    glVertex2i(x, y); //Set pixel coordinates 
    glEnd();
    glFlush(); //Render pixel
}
void ControlMause(int button, int state, int x, int y) {
	glColor3f(1.0,0.0,0.0);
	glPointSize(5);
	cout<<x<<" ; "<<y<<endl;
    if (button==GLUT_LEFT_BUTTON && state==GLUT_UP){
    	setPixel(x, y);
    }
    
    glutPostRedisplay();
}
void lineDDA(int xi, int yi, int xf, int yf){
	int dx = xf - xi, dy = yf - yi,steps;
	double incX, incY, x = xi, y = yi;
	( fabs(dx) > fabs(dy) )? steps = fabs(dx) :steps = fabs(dy);
	incX = double(dx)/double(steps);
	incY = double(dy)/double(steps);
	setPixel(round(x),round(y));
	for(int k=0 ; k < steps; k++){
		x += incX;
		y += incY;
		setPixel(round(x), round(y));
	}		
}


void funcion1(void){
	glColor3f(1.0,0.0,0.0);//color del segmento(linea roja)
	/*lineDDA(2,1,100,70);
	glColor3f(1.0,1.0,0.0);//color del segmento(linea roja)
	lineDDA(2,1,100,200);
	glColor3f(1.0,0.0,1.0);//color del segmento(linea roja)
	lineDDA(1,100,200,2);*/
	glutMouseFunc(ControlMause);
}
void name_funcion(void){
	glClear(GL_COLOR_BUFFER_BIT); // borra ventana de visualizcion
	glColor3f(1.0,0.0,0.0);//color del segmento(linea roja)
	glPointSize(5);
	glBegin(GL_POINTS);
		glVertex2i (50, 100);
		glVertex2i (75, 50);
		glVertex2i (100, 20);
	glEnd();
	glFlush(); //procesa lassubrutinas lo mas rapido posible
}
int main(int argc, char  **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50,100);
	glutInitWindowSize(600,500);
	glutCreateWindow("DIBUJAR#1");

	init();
	glutDisplayFunc(funcion1); //name_funcion-> funcion a correr
	glutMainLoop();
}