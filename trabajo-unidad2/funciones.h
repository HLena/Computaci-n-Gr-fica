

#include <GL/glut.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <GL/glut.h>
#include <vector>
using namespace std;


vector<int> vx, vy;
vector<int> px, py;
void drawLine(int, int , int, int);
float pi2 = 6.28318530718;



int x,y,xf,yf,xi,yi;
int fg_menu,color_menu,fg_accion,numberOfLists=0, numberOfPoints=0 , numberOfFigures = 0;


void setPixel(int x_, int y_){	
    glVertex2i(x_, y_); 
    vx.push_back(x_);    vy.push_back(y_);
}


void drawLine(int x1, int y1, int x2, int y2){
  int v_x = x2 - x1;
  int v_y = y2 - y1;

  int octante = -1;

  int * la;

  if(v_x >= 0 && v_y >= 0){
    if(v_x > v_y)
      octante = 0;
    else
      octante = 1;
  }
  else if(v_x <= 0 && v_y >= 0){
    if(fabs(v_x) > fabs(v_y))
      octante = 3;
    else
      octante = 2;
  }
  else if(v_x <= 0 && v_y <= 0){
    if(fabs(v_x) > fabs(v_y))
      octante = 4;
    else
      octante = 5;
  }
  else if(v_x >= 0 && v_y <= 0){
    if(fabs(v_x) > fabs(v_y))
      octante = 7;
    else
      octante = 6;
  }
  if(octante == -1)
    cout<<"Error reconociendo octante"<<endl;

  // cout<< "octante: "<<octante<<endl;
  // cout<<x2<<" "<<y2<<endl;

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

  // cout<<x2<<" "<<y2<<endl;

  int dx, dy, incE, incNE, d, x, y;

  dx = x2 - x1;
  dy = y2 - y1;
  d = 2 * dy - dx;
  incE = 2 * dy;
  incNE = 2 * (dy - dx);
  x = x1;
  y = y1;




  glBegin(GL_POINTS);



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

