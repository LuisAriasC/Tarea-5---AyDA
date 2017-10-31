#include <GLUT/glut.h>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <math.h>


std::vector<float> x;
std::vector<float> y;

GLdouble width = 400;
GLdouble height = 300;

float r = 1.0,g = 1.0,b = 1.0;

using namespace std;

void plot(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(4.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-width, width, -height, height);
}

void circlePoints(int x, int y){
    plot(x,y-100);
    plot(y,x-100);
    plot(-x,y-100);
    //plot(y,-x); //
    //plot(x,-y); //
    plot(-y,x-100);
    //plot(-x,-y); //
    //plot(-y,-x); //
}

void circle(void)
{
    int x = 0, y = 0;
    GLdouble radius =  height - 10;
    x = 0 ; y = radius;
    double p = 5.0 / 4.0 - radius;
    //plot(x,y);
    while (y > x) {
        if (p < 0) {
            x++;
            p += 2.0 * x + 3.0;
        }
        else{
            x++;
            y--;
            p += 2.0 * (x - y) + 5.0;
        }
        circlePoints(x, y);
        
    }
}



void lineBres(int x0, int y0, int x1, int y1){

    int x, y, dx, dy, xend, p, incE, incNE;
    dx = abs(x1-x0);
    dy = abs(y1 - y0);
    p = 2 * dy - dx;
    incE = 2 * dy;
    incNE = 2 * (dy - dx);
    
    if (x0 > x1) {
        x = x1;
        y = y1;
        xend = x0;
    }
    else{
        x = x0;
        y = y0;
        xend = x1;
    }
    
    while (x <= xend) {
        plot(x, y);
        x = x + 1;
        
        if (p < 0) {
            p = p + incE;
        }
        else{
            y = y + 1;
            p = p + incNE;
        }
    }
    
}

void DDA_Line(float x0, float y0, float x1, float y1){
    float x, y, xs, ys;
    int dx, dy, steps;
    
    dx = x1 - x0;
    dy = y1 - y0;
    
    x = x0;
    y = y0;
    
    if (abs(dx) > abs(dy)) {
        steps = abs(dx);
    }
    else steps = abs(dy);
    
    
    if (steps == 0) {
        plot(x, y);
    }
    
    
    xs = dx / (float)steps;
    ys = dy / (float)steps;
    
    for (int i = 0; i <= steps; i++) {
        plot(x, y);
        x = x + xs;
        y = y + ys;
    }
}

void print_Poligon(int lados)
{
    //float x[lados];
    //float y[lados];
    GLdouble radius =  height - 10;

    float angle = 0;
    float angle_increment = 360 / lados;
    
    for (int i = 0; i < lados; i++) {
        
        float angle_rad = angle * (M_PI/180);
        x.push_back(radius * cos(angle_rad));
        y.push_back(radius * sin(angle_rad));
        //x[i] = radius * cos(angle_rad);
        //y[i] = radius * sin(angle_rad);
        angle = angle + angle_increment;
    }
    
    for (int i = 0; i < lados; i++) {
        if (i<=lados-2) {
            DDA_Line(x[i], y[i], x[i+1], y[i+1]);
        }
        if (i == lados-1) {
            DDA_Line(x[i], y[i], x[0], y[0]);
        }

    }
}

void print_cube(){
    
    pair<float, float> p;
    vector<pair<float, float> > c1;
    vector<pair<float, float> > c2;
    float lado = 130.00;
    
    
    float x0_c1 = -100.00;
    float y0_c1 = 20.00;
    p.first = x0_c1;
    p.second = y0_c1;
    c1.push_back(p);
    p.first = x0_c1 + lado;
    p.second = y0_c1;
    c1.push_back(p);
    p.first = x0_c1 + lado;
    p.second = y0_c1 - lado;
    c1.push_back(p);
    p.first = x0_c1;
    p.second = c1[0].second - lado;
    c1.push_back(p);
    
    float angle = 50.00;
    float angle_rad = angle * (M_PI/180);
    float x0_c2 = x0_c1 + (120.00 * cos(angle_rad));
    float y0_c2 = y0_c1 + (120.00 * cos(angle_rad));
    p.first = x0_c2;
    p.second = y0_c2;
    c2.push_back(p);
    p.first = x0_c2 + lado;
    p.second = y0_c2;
    c2.push_back(p);
    p.first = x0_c2 + lado;
    p.second = y0_c2 - lado;
    c2.push_back(p);
    p.first = x0_c2;
    p.second = y0_c2 - lado;
    c2.push_back(p);
    
    for (int i = 0; i < 4; i++) {
        
        if (i<=2) {
            DDA_Line(c1[i].first, c1[i].second, c1[i+1].first, c1[i+1].second);
            DDA_Line(c2[i].first, c2[i].second, c2[i+1].first, c2[i+1].second);
        }
        if (i == 3) {
            DDA_Line(c1[i].first, c1[i].second, c1[0].first, c1[0].second);
            DDA_Line(c2[i].first, c2[i].second, c2[0].first, c2[0].second);
        }
        
        DDA_Line(c1[i].first, c1[i].second, c2[i].first, c2[i].second);
    }

}

void otherDisplay(void)
{
    bool op = true;
    while (op) {
        glClear (GL_COLOR_BUFFER_BIT);
        glColor3f (1.0, 1.0, 1.0);
        glPointSize(1.0);
        
        int opci;
        cout << "Opcion" << endl;
        cout << "\t1)Polígono de n lados\t2)Arco\t3)Figuras 3D\t4)Salir" << endl;
        cout << "\n\tOpción: "; cin >> opci;
            
        switch (opci) {
            case 1:
                int lados;
                do{
                    cout << "Deme la cantidad de lados(Mayor o igual a 3): ";
                    cin >> lados;
                } while(lados < 3);
                print_Poligon(lados);
                //glFlush ();
                break;
                
            case 2:
                circle();
                //glFlush ();
                break;
                
            case 3:
                int opcio;
                cout << endl << "Seleccione " << endl;
                cout << "\t1)Cubo\t2)Prisma rectangular\t3)Prisma triangular\t4)Cono" << endl;
                cout << "\tOpción: "; cin >> opcio;
                switch (opcio) {
                    case 1:
                        print_cube();
                        break;
                        
                    default:
                        cout << endl << "OPCIÓN NO VÁLIDA" << endl << endl;
                        break;
                }
                break;
                    
            default:
                cout << "Saliendo" << endl;
                op = false;
                break;
            }
            
            glFlush ();
            
            x.clear();
            y.clear();
        }
    //glFlush();
}

int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Randomly generated points");
    glClearColor(1,1,1,0);
    glClear(GL_COLOR_BUFFER_BIT);
    glutDisplayFunc(otherDisplay);
    init();
    //glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
