
//g++ turtle.cpp -o g1 -lglut -lGLU -lGL^C compilacion
#include "figura.h"

//------------------VARIABLES VENTANA -------------------
int ancho=600, alto=500;


//-------------------------------------------------------------------------------
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
        px.clear(); py.clear();
        break;
    case 3 : /* exit the program */
        exit (0);
        break;
    default : /* in case none of the above occur */
        break;
    }
}


void figuraMenu(int id){  /*Tipo de figura a dibujar*/
    //int nlados,r;
    glNewList (++numberOfLists, GL_COMPILE_AND_EXECUTE);
    switch (id){
        case 1 : /* Para poligono regular */
            fg = new poligono();
            fg->drawRPoligono();
            break;
        case 2 : /* poligono irregular */
            //fg = new poligono();
            break;
        case 3 : /* linea */
            fg = new poligono();
            break;
    }
    glEndList ();
}

void accionMenu(int id){
    int pxt,pyt;
    glNewList (++numberOfLists, GL_COMPILE_AND_EXECUTE);
    switch (id)
    {
    case 1 : /* trasladar imagen */
        cout<<"P.traslacion"<<endl;
        cout <<"x:";cin>>fg->xt; 
        cout <<"y:";cin>>fg->yt; 
        fg->T_Poligono();
        ///glFlush();
        break;
    case 2 : /* escalar imagen */
        cout<<"Valores de escala"<<endl;
        cout <<"x:";cin>>fg->xs; 
        cout <<"y:";cin>>fg->ys; 
        fg->E_Poligono();
        break;
    case 3 : /* Rotacion */
        cout<<"Rotacion Imagen"<<endl;
        //cout <<"angulo:";cin>>fg->ang; 
        fg->R_Poligono();
        break;
    default : /* for any case not covered above, leave line thickness unchanged */
        break;
    }
    glEndList ();
}

void colorMenu (int id){
    glNewList (++numberOfLists, GL_COMPILE_AND_EXECUTE);
    switch (id)
    {
    case 1 : /* change color to red */
        //glColor3d (1.0, 0.0, 0.0);
        fg->Relleno();
        break;
    case 2 : /* change color to green */
        glColor3d (0.0, 1.0, 0.0);
        break;
    case 3 : /* change color to blue */
        glColor3d (0.0, 0.0, 1.0);
        break;
    default : /* for any case not covered above, leave color unchanged */
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
        glutAddMenuEntry ("P.regular", 1);
        glutAddMenuEntry ("Circulo", 2);
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
    if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
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
        px.push_back(x);    py.push_back(y);
        cout<<"{"<<x<<";"<<y<<"}"<<endl;
        glBegin(GL_POINTS);
        setPixel(x,y);
        glEnd();
        glFlush();
    }
    glutPostRedisplay();
}

void ControlKeyboard(unsigned char key, int x, int y) {
    switch (key)
    {
    case 'q': /*PAra poligono irregular*/
        cout<<"px"<<px.size()<<endl;
        fg = new poligono();
        fg->drawIPoligono();
        break;
    case 'a':
        exit(0);
        break;
    }
    glutPostRedisplay();
   
}



void display(void){
	/*int pos;
    cout<<check<<endl;
	if(check){
        if(x < fg->xmin) fg->xmin = x;
        if(y < fg->ymin) fg->ymin = y;
        if(x > fg->xmax) fg->xmax = x;
        if(y > fg->ymax) fg->ymax = y;
        if(numberOfPoints == 0){
            cout<<"x,y"<<x<<";"<<y<<endl;
		    fg->ox = x; fg->oy = y;
	    }else{
		    xf = x; yf = y;
        }
        numberOfPoints++;
        setPixel(x,y);
    }*/
}

int main(int argc, char  **argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(600,500);
	glutCreateWindow("DIBUJAR#1");
    //cout<<"mitas: "<<ancho/2<<" "<<alto/2<<endl;
	init();
	glutDisplayFunc(display); //name_funcion-> funcion a correr
	glutMouseFunc(ControlMause);
    glutKeyboardFunc(ControlKeyboard);
	glutMainLoop();
}