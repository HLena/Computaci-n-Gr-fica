#include <fstream>
#include <GL/glut.h>
#include <math.h>
using namespace std;
//graficando Turtle
//g++ grafica3.cpp -o g1 -lglut -lGLU -lGL^C

float  calx, caly;
void reshape(int width, int height){
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0,(GLfloat)height/(GLfloat)width, 1.0, 128.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0,1.0,3.0,0.0,0.0,0.0,0.0,1.0,0.0);
}

void keyboard(unsigned char key, int x, int y){
    switch (key) {
        case 'h':
            printf("help\n\n");
            printf("c - Toggle culling\n");
            printf("q/escape - Quit\n\n");
            break;
        case 'c':
            if (glIsEnabled(GL_CULL_FACE))
                glDisable(GL_CULL_FACE);
            else
                glEnable(GL_CULL_FACE);
            break;
        case '1':
            glRotatef(1.0,1.,0.,0.);
            break;
        case '2':
            glRotatef(1.0,0.,1.,0.);
            break;
        case 'q':
        case 27:
            exit(0);
            break;
    }
    glutPostRedisplay();
}
void write_pixel(float x, float y){
    glBegin(GL_POINTS);
        glVertex2f(x ,y);
    glEnd();
}
void puntos(float x, float y){
    glColor3f(1.0,0.0,0.0);
    write_pixel(x,y);
    write_pixel(x,-y);
    //write_pixel(-x,y);
    //write_pixel(-x,-y);
    write_pixel(y,x);
    write_pixel(y,-x);
    //write_pixel(-y,x);
    //write_pixel(-y,-x);
}
void line(float x, float y){
    glBegin(GL_LINES);
        glVertex2f(x,y);
        glVertex2f(-x,-y);
    glEnd();
}
void circulo(float radio, int px, int py){
    glColor3f(1.0,1.0,1.0);
    for(double i=0.0;i<10.0;i+=0.001){
        calx = radio * cos(i) + px;
        caly = radio * sin(i) + py;
        write_pixel(calx, caly);
    }
}
void drawTurtle(float radio, float x, float y){
    float d_teta;
    for(double i=0.0;i<5.0;i+=0.5){
        calx = radio * cos(i)+x ;
        caly = radio * sin(i)+y;
        puntos(calx, caly);
    }

}

void display(void){
    glClearColor(0.0,0.0,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);
    glColor3f(0.0,0.0,1.0);
    line(0.0,1.0);
    line(1.0,0.0);
    //puntos(0.5,1.0);
    //circulo();
    drawTurtle(0.5,0.0,0.0);
    drawTurtle(0.4,0.0,0.0);
    drawTurtle(0.3,0.0,0.0);
    drawTurtle(0.2,0.0,0.0);

    drawTurtle(0.1, 0.5, 0.5);
    glFlush();
    //glutWireTorus(0.25,0.75,28,28);
    //glColor3f(0.0,0.0,1.0);
    //glutWireCube(.60);
    glutSwapBuffers();
}


int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(400,200);
    glutCreateWindow("Practica 2");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape); 
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
