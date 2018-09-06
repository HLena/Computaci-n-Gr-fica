#include <GL/glut.h>
#include <math.h>  
#include <iostream>
using namespace std;

//jgutierrezca@unsa.edu.pe


float pi2 = 6.28318530718;
int h = 600; //altura
int w = 600; //ancho
 
void write_pixel(int x_, int y_){
   
    float x,y;
    x = x_/(float) w/2; /*Normalizamos las coordenadas para poder graficar*/  
    y = y_/(float) h/2; /*con respecto a las dimensiones de la ventana*/
    //cout <<x<<";"<<y<<endl;
    glVertex2f(x, y);          
    
}

/*Trazando una linea con el metodo de punto medio*/
void Midpoint_Algorithm(void){  /*---(2)---*/
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f (1.0, 0.0, 0.0); // color Rojo
    int x1,y1,x2,y2;    
    x1 = 0; y1 = 0; //  p1(x1,y1) 
    x2=800; y2=50;  //  p2(x2,y2)
    int dx,dy,incE, incNE, d, x, y;    
    dx = x2 - x1;
    dy = y2 - y1;
    d = 2* dy - dx;
    incE = 2 * dy;
    incNE = 2 * ( dy - dx );
    x = x1; y = y1; //punto inicial
    glBegin(GL_POINTS);
    while(x < x2){ /* se cicla hasta llegar al extremo de la línea */
        write_pixel(x,y); /*marcando pixel*/
        if(d <= 0){
            d = d + incE;
            x = x + 1;
        }else{
            d = d + incNE;
            x =  x + 1;
            y = y + 1;
        }
        
    }
    glEnd();
    glFlush();
}


/*Graficando  poligonos dado determinado numero de lados y un radio*/
void DrawPolygon(void){  /*---(1)---*/
    glClear(GL_COLOR_BUFFER_BIT); 
    glBegin(GL_POLYGON);
    glColor3f (1.0, 0.0, 0.0); 
    float lado,radio,ang;
    lado=7; radio=1.0;
    ang = pi2 / lado;
    float px,py;
    for(int i=0;i<lado;i++){
        px = cos(ang*i) * radio; 
        py = sin(ang*i) * radio;
        //cout<<px<<";"<<py<<endl;
        glVertex3f(px, py, 0.0f);
    }
    glEnd();
    glFlush();
}



int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(w, h);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Polígonos");
    glutDisplayFunc(DrawPolygon);  /*---(1)---*/
    glutDisplayFunc(Midpoint_Algorithm); /*---(2)---*/
    glutMainLoop();
    return 0;
}