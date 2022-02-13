#include <stdlib.h>
#include <GL\glut.h>
#include <math.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <time.h>
#define doc "data.csv"

using namespace std;
int a=0;
string nombre, numero, Nomb[100];
float Number[100], Pi = 3.1416, grados[100], contador=0, color1[100], color2[100], color3[100];

void inscripcion();
void leer(){
	ifstream documento(doc);
    string fila;
    char delimitador = ',';
    // leemos el encabezado
    getline(documento, fila);
    // leemos los siguientes filas
    while(getline(documento, fila))
    {
        stringstream stream(fila);
        getline(stream, nombre, delimitador);
        getline(stream, numero, delimitador);
        Nomb[a]=nombre;
        istringstream(numero)>>Number[a];
        grados[a]=Number[a]*360/100;
        a++;
        cout<<a<<" "<<nombre<<" -> "<<numero<<endl;
	}
}

void pizza(){
	float  x=0, y=0, radio=40, Fin=1, Inicio=0,posx=-20,posy=0;
	srand(time(NULL));
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
	glColor3f (0,0,0);
	glVertex2f(-20,0);
	for(int j=0;j<a;j++){
		color1[j]=float(rand()%10)/10;
		color2[j]=float(rand()%10)/10;
		color3[j]=float(rand()%10)/10;
		glColor3f(color1[j],color2[j],color3[j]);
        Fin=Fin+grados[j];
		for(float i=Inicio;i<Fin; i++){
			glTranslatef(60,50,0);
			x=radio*cos(i *Pi/180)+posx;
			y=radio*sin(i *Pi/180)+posy;
			glVertex2f(x,y);
		}
	Inicio=Fin;
	}
	glEnd();
	glFlush();
	inscripcion();
}

void inscripcion(){
	for(int j=0 ;j<=a;j++)
	{
		glPushMatrix();
		contador=contador+10;
		glTranslatef(30,90-contador,0);
		glColor3d(color1[j],color2[j],color3[j]);
		nombre=Nomb[j];
		const char *str = nombre.c_str();
		glRasterPos2f(0, -10);
		for(const char *c=str; *c != '\0';c++){
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c);
		}
		glutSwapBuffers();
		glPopMatrix();
	}
	contador=0;
}

int main (int argc, char ** argv)
{	
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition (200, 50);
	glutInitWindowSize (500, 500);
	glutCreateWindow ("Circulo pizza");
	glClearColor(0,0,0,0); //colores rgb
    glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-100, 100, -100, 100);
	leer();
    glutDisplayFunc(pizza);
	glutMainLoop();
	return 0;
}
