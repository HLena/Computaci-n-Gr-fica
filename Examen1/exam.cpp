#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <cmath>

using namespace std;


void init(){
 glOrtho(-10, 10, -10, 10, -10, 10);
}


void write_pixel(int x_, int y_){
    float x,y;
    x = (float)x_;
    y = (float)y_;
    glVertex2f(x, y);          
    
}
void CirclePoints(int x, int y){
   write_pixel(x,y);
   write_pixel(x,-y);
   write_pixel(-x,y);
   write_pixel(-x,-y);
   write_pixel(y,x);
   write_pixel(y,-x);
   write_pixel(-y,x);
   write_pixel(-y,-x);
}

void circle(void){

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0, 0);
    glPointSize(3);
    glBegin(GL_POINTS);
    int x,y, radio = 5; 
    float d;
    x = 0; y = radio;
    d = (float)5/4 - radio;
    CirclePoints(x,y); /*marcando pixel*/
    while(y > x){ /* se cicla hasta llegar al extremo de la línea */
        if(d < 0){ //E
            d = d + 2 * x + 3;
            x++;
        }else{ // SE
            d = d + 2 * (x - y) + 5;
            x++; y--;
        }
        CirclePoints(x,y);   
    }
    glEnd();
    glFlush();



}
void ParabolaPoints(int x, int y){
    write_pixel(x,y);
    write_pixel(x,-y);
}
//Parabola con el metodo de punto medio
void Parabola(void){
    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(3);
    glBegin(GL_POINTS);
    int x,y,p, p2, p4,d;
    x = 0; y = 0; p=3;
    glColor3f(1, 0, 0);
    write_pixel(p,y); // dibujando el punto p
    p2 = 2 * p; p4 = p2 * 2;
    d = 1 - p;
     glColor3f(0, 0, 0);
    while( y < p && x <= 100){
        ParabolaPoints(x,y);
        if( d >= 0){
                x++;
                d = d - p2;
        }
        y++;
        d = d + 2 * y + 1;
    }
    if(d == 1) d = 1 - p4;
    else d = 1 - p2;
    
    while(x<=100){
        ParabolaPoints(x,y);
        if(d <= 0){
            y++;
            d = d + 4*y;
        }
        x++;
        d = d - p4;
    }
    glEnd();
    glFlush();
}

/*void Line3d(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0, 0);
    glPointSize(3);
    int xmax, xmin, ymin, ymax, x, y, z;
    xmin=0 ; ymin=0;
    xmax=3; ymax=3;
    glVertex3f (0.0, 0.0, 1.0);
    glBegin (GL_LINES);
        for (x = xmin; x <= xmax; x++)
        {
            for (y = ymin; y <= ymax; y++)
            {
                z = sin (sqrt ((x*x) + (y*y)));
                glVertex3f ((float)x, (float)y, (float)z);
            }
        }
    glEnd ();
}*/

int main(int argc, char **argv)
{
 glutInit(&argc, argv);
 glutInitWindowPosition(50, 50);
 glutInitWindowSize(500, 500);
 glutCreateWindow("Graficos");
 init();
 glutDisplayFunc(circle);
 //glutDisplayFunc(Parabola);
 glutMainLoop();

 return 0;
}

