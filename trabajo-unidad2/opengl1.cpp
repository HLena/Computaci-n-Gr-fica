#include <GL/glut.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
//g++ turtle.cpp -o g1 -lglut -lGLU -lGL^C compilacion

class figura{
    public:
        int xmin, ymin, xmax, ymax;
        bool **lienzo;
        figura(){}

};

class poligono:public  figura{

    public:
        int tipo, radio,n_lados; 
        int ox, oy;
        poligono(int n,int t){n_lados = n; tipo = t; ox = oy = radio = 0;}
        poligono(){}
        ~poligono(){}
    
};



int ancho=600, alto=500;
bool check = false;
int x,y,xf,yf,xi,yi;
int fg_menu,color_menu,fg_accion,numberOfLists=0, numberOfPoints=0;
vector<int> points;

//---------------------------FUNCIONES------------------------------------

//funcion dibuja punto
void setPixel(int x_, int y_){  
    //glBegin(GL_POINTS);
    glVertex2i(x_, y_); //Set pixel coordinates 
    //glEnd();
    //glFlush(); //Render pixel
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


void draw_line(int x1, int y1, int x2, int y2){
  int v_x = x2 - x1;
  int v_y = y2 - y1;

  int octante;

  int * la;

  if(v_x > 0 && v_y > 0){
    if(v_x > v_y)
      octante = 0;
    else
      octante = 1;
  }
  else if(v_x < 0 && v_y > 0){
    if(fabs(v_x) > fabs(v_y))
      octante = 3;
    else
      octante = 2;
  }
  else if(v_x < 0 && v_y < 0){
    if(fabs(v_x) > fabs(v_y))
      octante = 4;
    else
      octante = 5;
  }
  else if(v_x > 0 && v_y < 0){
    if(fabs(v_x) > fabs(v_y))
      octante = 7;
    else
      octante = 6;
  }

  cout<< "octante: "<<octante<<endl;
  cout<<x2<<" "<<y2<<endl;

  int tx = -x1;
  int ty = -y1;

  x1 = 0;
  y1 = 0;

  x2 += tx;
  y2 += ty;


  int temp;
  switch (octante) {

    case 1: temp = x2;
      x2 = y2;
      y2 = temp;
      break;
    case 2: temp = x2;
      x2 = y2;
      y2 = -temp;
      break;

    case 3:
      x2 = -x2;
      break;

    case 4:
      x2 = -x2;
      y2 = -y2;
      break;

    case 5: temp = x2;
      x2 = -y2;
      y2 = -temp;
      break;

    case 6: temp = x2;
      x2 = -y2;
      y2 = temp;
      break;

    case 7:
      y2 = -y2;
      break;


  }

  cout<<x2<<" "<<y2<<endl;

  int dx, dy, incE, incNE, d, x, y;

  dx = x2 - x1;
  dy = y2 - y1;
  d = 2 * dy - dx;
  incE = 2 * dy;
  incNE = 2 * (dy - dx);
  x = x1;
  y = y1;




  glBegin(GL_POINTS);

  // setPixel(0, 0);
  // setPixel(50, 50);
  // setPixel(-50, -50);
  // setPixel(50, -50);
  // setPixel(-50, 50);

  // setPixel(x, y);


  while (x < x2) {
    if(d <= 0){
      d = d + incE;
      x = x + 1;
    }
    else{
      d = d + incNE;
      x = x + 1;
      y = y + 1;
    }

    switch (octante) {
      case 0: setPixel(x - tx, y - ty);
        break;
      case 1: setPixel(y - tx, x - ty);
        break;
      case 2: setPixel(-y - tx, x - ty);
        break;
      case 3: setPixel(-x - tx, y - ty);
        break;
      case 4: setPixel(-x - tx, -y - ty);
        break;
      case 5: setPixel(-y - tx, -x - ty);
        break;
      case 6: setPixel(y - tx, -x - ty);
        break;
      case 7: setPixel(x - tx, -y - ty);
        break;
    }

  }

  glEnd();
  glFlush();
}

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

void figuraMenu(int id){
    int nlados;
    poligono *fg;
    glNewList (++numberOfLists, GL_COMPILE_AND_EXECUTE);
    switch (id){
        case 1 : /* change line thickness to 1 */
            cout<<"Numero de lados: ";cin>>nlados;
            fg = new poligono(nlados,1);
            fg->ox = xi; fg->oy = yi;
            fg->radio = sqrt(pow(xf-xi,2) +pow(yf-yi,2));
            ///cout<<"radio es: "<<fg->radio<<endl;
            check = false;
            numberOfPoints=0;
            break;
        case 2 : /* change line thickness to 2 */
            lineDDA(x,y,xi,yi);
            check = false;
            numberOfPoints=0;
            break;
        case 3 : /* change line thickness to 3 */
            lineDDA(x,y,xi,yi);
            check = false;
            numberOfPoints=0;
            break;
        case 4: /* change line thickness to 3 */
            break;
        case 5 : /* change line thickness to 3 */
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

void tipoPoligo(int id){
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
        glutAddMenuEntry ("P.regular", 1);
        glutAddMenuEntry ("P.irregular", 2);
        glutAddMenuEntry ("Linea", 3);
        glutAddMenuEntry ("Circulo", 4);
        glutAddMenuEntry ("Parabola", 5);
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
            //lineDDA(xf,yf,x,y);
        draw_line(xf,yf,x,y);
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

int main(int argc, char  **argv){
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