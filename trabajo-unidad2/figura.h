
#include "funciones.h"


int MT[9] ={1,0,0,0,1,0,0,0,1};
class figura{
    public:
        int xmin, ymin, xmax, ymax;
        int h,w;
        bool **lienzo;
        figura(){xmax = ymax = h = w = 0; xmin = ymin =600;}
        void llenarLienzo();

};

void figura::llenarLienzo(){
    h = ymax - ymin; w = xmax-xmin;
    for(int i=0; i < h;i++){
        for(int j=0; j < w;j++){
            lienzo[i][j]=0;
        }
    }
}

class poligono:public  figura{

    public:
        int radio,lados; 
        int ox, oy;
        int xt,yt,xs,ys;
        float ang;
        poligono(){lados = ox = oy = radio = 0;}
        void draw();
        void clean();
        void drawRPoligono();
        void drawIPoligono();
        void T_Poligono();
        void R_Poligono();
        void E_Poligono();
        void matrixBuffer();
        void Relleno();
        ~poligono(){}
    
};

poligono *fg;
void poligono::drawRPoligono(){
    cout<<"Numero de lados: ";cin>>lados;
    cout<<"Radio: ";cin>>radio;
    float x1,y1,x2,y2;
    float d_teta = pi2/lados;
    for(int i=0;i<lados; i++){
        x1 = cos(d_teta*i)*radio;
        y1 = sin(d_teta*i)*radio;
        x2 = cos(d_teta * (i + 1)) * radio;
        y2 = sin(d_teta * (i + 1)) * radio;
        drawLine(x1,y1,x2,y2);
        if(x1 < xmin) xmin = x1;
        if(y1 < ymin) ymin = y1;
        if(x1 > xmax) xmax = x1;
        if(y1 > ymax) ymax = y1;
    }
    cout <<"minimos: "<<xmin<<";"<<ymin<<endl;
    cout <<"maximos: "<<xmax<<";"<<ymax<<endl;
    lienzo = new bool*[ymax-ymin+1];

    for (size_t i = 0; i < ymax-ymin+1; i++) {
        lienzo[i] = new bool[xmax-xmin+1];
    }
    matrixBuffer();
}

void poligono::drawIPoligono(){
    ox = px[0]; oy=py[0];
    draw();
    //px.clear(); py.clear();
    cout <<"minimos: "<<xmin<<";"<<ymin<<endl;
    cout <<"maximos: "<<xmax<<";"<<ymax<<endl;
    /*lienzo = new bool*[ymax-ymin+1];
    for (size_t i = 0; i < ymax-ymin+1; i++) {
        lienzo[i] = new bool[xmax-xmin+1];
    }
    matrixBuffer();*/
    cout <<"------- "<<endl;
}


void poligono::matrixBuffer(){
    int i, j;
    for(int t= 0 ; t < vx.size() ; t++){
        i = (vx[t] - xmin);
        j = (vy[t] - ymin);
        //cout<<"("<<i<<";"<<j<<")"<<endl;
        lienzo[j][i] = 1;
    }
    
}


void poligono::T_Poligono(){
    cout<<"--------translacion----------"<<endl;
    int tmpx, tmpy;
    cout<<"*{"<<xt<<";"<<yt<<"}"<<endl;
    MT[2]=xt;MT[5]=yt;
    //vector<int> point(3,1);
    for(int i=0; i<px.size();i++){
       tmpx = MT[0] * px[i] + MT[1] * py[i] + MT[2] * 1;
       tmpy = MT[3] * px[i] + MT[4] * py[i] + MT[5] * 1;
       px[i] = tmpx; py[i] = tmpy;
    }
    clean();
    draw();
}
void poligono::E_Poligono(){
    cout<<"---------escala---------"<<endl;
    //xt = x; yt = y;
    int tmpx, tmpy;
    cout<<"*{"<<xs<<";"<<ys<<"}"<<endl;
    MT[0]=xs;MT[4]=ys;
    //vector<int> point(3,1);
    for(int i=0; i<px.size();i++){
       tmpx = MT[0] * px[i] + MT[1] * py[i] + MT[2] * 1;
       tmpy = MT[3] * px[i] + MT[4] * py[i] + MT[5] * 1;
       px[i] = tmpx; py[i] = tmpy;
    }
    clean();
    draw();
}

void poligono::R_Poligono(){
    cout<<"---------rotacion---------"<<endl;
    //xt = x; yt = y;
    ang = 0.75;
    int tmpx, tmpy;
    cout<<"*{"<<ang<<"}"<<endl;
    //MT[0]=cos(ang);MT[1]=-sin(ang);MT[3]=sin(ang);MT[4]=cos(ang);
    //vector<int> point(3,1);
    for(int i=0; i<px.size();i++){
       tmpx = cos(ang) * px[i] + (-sin(ang)) * py[i] + MT[2] * 1;
       tmpy = sin(ang) * px[i] + cos(ang) * py[i] + MT[5] * 1;
       px[i] = tmpx; py[i] = tmpy;
    }
    clean();
    draw();
}

void poligono::draw(){
    for(int i=0; i<px.size();i++){
        if(i != px.size()-1)
            drawLine(px[i],py[i],px[i+1],py[i+1]);
        else
            drawLine(px[i],py[i],px[0],py[0]);
        if(px[i] < xmin)    xmin = px[i];
        if(px[i] > xmax)    xmax = px[i];
        if(py[i] < ymin)    ymin = py[i];
        if(py[i] > ymax)    ymax = py[i];
    }
    glFlush();
    lienzo = new bool*[ymax-ymin+1];
    for (size_t i = 0; i < ymax-ymin+1; i++) {
        lienzo[i] = new bool[xmax-xmin+1];
    }
    llenarLienzo();
    matrixBuffer();
}
 void poligono::clean(){
    glClearColor(1.0,1.0,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
 }

 void poligono::Relleno(){
    int h=fabs(ymax-ymin+1),w =fabs(xmax-xmin +1);
    bool pintar, cambio;
    for(int i=0; i < h; i++){
        pintar = cambio = false;
        for(int j=0; j < w; j++){
            if(lienzo[i][j] == true)
                cambio = true;
            if(cambio==true && !lienzo[i][j]){
                if(pintar == true)
                    pintar=false;
                else
                    pintar=true;
                cambio = false;
            }
            if(pintar==true)
                setPixel(i+xmin,ymin+j);
        }
    }
 }
