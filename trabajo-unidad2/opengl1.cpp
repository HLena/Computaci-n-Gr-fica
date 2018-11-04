#include <GL/glut.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
//g++ turtle.cpp -o g1 -lglut -lGLU -lGL^C compilacion

int ancho=600, alto=500;
bool check = false;
int x,y,xf,yf,xi,yi;
int fg_menu,color_menu,fg_accion,numberOfLists=0, numberOfPoints=0;
vector<int> points;

//---------------------------FUNCIONES------------------------------------

void setPixel(int x_, int y_){	
    glBegin(GL_POINTS);
    glVertex2i(x_, y_); //Set pixel coordinates 
    glEnd();
    glFlush(); //Render pixel
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

void mainMenu (int id){
    double lineWidth, color[4];
    switch (id)
    {
    case 1 : /* reset default values */
        glNewList (++numberOfLists, GL_COMPILE_AND_EXECUTE);
           glColor3d (0.0, 0.0, 0.0);
           glLineWidth (1.0);
        glEndList ();
        break;
    case 2 : /* clear the screen */
        glClearColor(1.0,1.0,1.0,1.0);
    	glClear(GL_COLOR_BUFFER_BIT);
    	check = false;
        numberOfPoints=0;
        break;
    case 3 : /* exit the program */
        exit (0);
        break;
    default : /* in case none of the above occur */
        break;
    }
}

void colorMenu (int id){
    glNewList (++numberOfLists, GL_COMPILE_AND_EXECUTE);
    switch (id)
    {
    case 1 : /* change color to red */
        glColor3d (1.0, 0.0, 0.0);
        break;
    case 2 : /* change color to green */
        glColor3d (0.0, 1.0, 0.0);
        break;
    case 3 : /* change color to blue */
        glColor3d (0.0, 0.0, 1.0);
        break;
    case 4 : /* change color to black */
        glColor3d (0.0, 0.0, 0.0);
        break;
    default : /* for any case not covered above, leave color unchanged */
        break;
    }
    glEndList ();
    
}

void figuraMenu(int id)
/* This is the callback function for the size menu. */
{
    glNewList (++numberOfLists, GL_COMPILE_AND_EXECUTE);
    switch (id)    {
    case 1 : /* change line thickness to 1 */
        lineDDA(xf,yf,xi,yi);
        check = false;
        numberOfPoints=0;
        break;
    case 2 : /* change line thickness to 2 */
        lineDDA(x,y,xi,yi);
        check = false;
        numberOfPoints=0;
        break;
    case 3 : /* change line thickness to 3 */
        
        break;
    default : /* for any case not covered above, leave line thickness unchanged */
        break;
    }
    glEndList ();
}

void accionMenu(int id){
    glNewList (++numberOfLists, GL_COMPILE_AND_EXECUTE);
    switch (id)
    {
    case 1 : /* change line thickness to 1 */
        
        break;
    case 2 : /* change line thickness to 2 */
        
        break;
    case 3 : /* change line thickness to 3 */
        
        break;
    default : /* for any case not covered above, leave line thickness unchanged */
        break;
    }
    glEndList ();
}

void init(void){
	glClearColor(1,1,1,1); //asigna el color  de la ventana(blanco)
	glClear(GL_COLOR_BUFFER_BIT);// establece parametross de proyeccion
	glColor3f(1,0,0);
	glPointSize(3);
	gluOrtho2D(-ancho,ancho,-alto,alto);

	/* Create the menu structure and attach it to the right mouse button. */

    color_menu = glutCreateMenu (colorMenu);
        glutAddMenuEntry ("Rojo", 1);
        glutAddMenuEntry ("Verde", 2);
        glutAddMenuEntry ("Azul", 3);
        glutAddMenuEntry ("Negro", 4);
    fg_menu = glutCreateMenu (figuraMenu);
        glutAddMenuEntry ("Poligono", 1);
        glutAddMenuEntry ("Linea", 2);
        glutAddMenuEntry ("Circulo", 3);
        glutAddMenuEntry ("Parabola", 3);
    fg_accion = glutCreateMenu(accionMenu);
        glutAddMenuEntry ("Mover", 1);
        glutAddMenuEntry ("Escalar", 2);
        glutAddMenuEntry ("Rotar", 3);
    glutCreateMenu (mainMenu);
       glutAddSubMenu ("Color", color_menu);
       glutAddSubMenu ("Figura", fg_menu);
       glutAddSubMenu ("Accion", fg_accion);
       glutAddMenuEntry ("Limpiar ventana", 2);
       glutAddMenuEntry ("Salir", 3);
    glutAttachMenu (GLUT_RIGHT_BUTTON);
}



void ControlMause(int button, int state, int xmouse, int ymouse) {
	cout<<x<<" ; "<<y<<endl;
    cout<<"("<<xmouse<<" ; "<<ymouse<<")"<<endl;
    cout<<"------------"<<endl;
    if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
    	check = true;
        if(xmouse < ancho/2){
            if(ymouse < alto/2){
                x = -2*((ancho/2-1)- xmouse);
                y = 2*((alto/2-1) - ymouse);
            }else{
                x = -2*((ancho/2-1) - xmouse);
                y = -2*(ymouse - (alto/2-1));
            }
        }else{
            if(ymouse < alto/2){
                x = 2*(xmouse- (ancho/2-1));
                y = 2*(alto/2 - ymouse);
            }else{
                x = 2*(xmouse - (ancho/2-1));
                y = -2*(ymouse - (alto/2-1));
            }
        }
    }
    if(numberOfPoints > 1){
		    lineDDA(xf,yf,x,y);
    }
    glutPostRedisplay();
}



void funcion1(void){
	int pos;
	if(check){
        if(numberOfPoints == 0){
		    xi = x; yi = y;
	    }else
		    xf = x; yf = y;
	    numberOfPoints++;
		setPixel(x,y);
        
	}
	//lineDDA(2,1,10,100);
	/*glColor3f(1.0,1.0,0.0);//color del segmento(linea roja)
	lineDDA(2,1,100,200);
	glColor3f(1.0,0.0,1.0);//color del segmento(linea roja)
	lineDDA(1,100,200,2);*/
	//glutMouseFunc(ControlMause);
}

int main(int argc, char const **argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(600,500);
	glutCreateWindow("DIBUJAR#1");
    cout<<"mitas: "<<ancho/2<<" "<<alto/2<<endl;
	init();
	glutDisplayFunc(funcion1); //name_funcion-> funcion a correr
	glutMouseFunc(ControlMause);
	glutMainLoop();
}