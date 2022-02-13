#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <GL/glut.h>
using namespace std;

int pntX1, pntY1, vertices, opcion=0;
vector<int> pntX;
vector<int> pntY;
int transX, transY, pfX, pfY, ang; 

void dibujarP()
{
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	for(int i = 0; i < vertices; i++)
	{
		glVertex2i(pntX[i], pntY[i]);
	}
	glEnd();
}

void traslacion(int x, int y)
{
	glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 0.0);
	for(int i = 0; i < vertices; i++)
	{
		glVertex2i(pntX[i] + x, pntY[i] + y);
	}
	glEnd();
}

void escalado(int x, int y, int pf1, int pf2)
{
	glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 0.0);
	for(int i = 0; i < vertices; i++)
	{
		glVertex2i(pntX[i]*x+pf1*(1- x), pntY[i]*y+pf2*(1- y));
	}
	glEnd();
}

void rotacion(int x, int y,int angulo)
{   //el valor del angulo debe estar en radianes entonces lo multiplicamos por 3.14/180
	glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 0.0);
	for(int i = 0; i < vertices; i++)
	{
		glVertex2i(x+(pntX[i]-x)*cos(angulo*3.14/180)-(pntY[i]-y)*sin(angulo*3.14/180), 
		           y+(pntX[i]-x)*sin(angulo*3.14/180)+(pntY[i]-y)*cos(angulo*3.14/180));
	}
	glEnd();
}

void iniciador (void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(4.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-50.0, 300.0, -50.0, 300.0);
}

void Display(void)
{
	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f (0.0, 0.0, 0.0);
	
	if(opcion==1)
	{
		dibujarP();
		traslacion(transX, transY);
	}
	else if(opcion==2)
	{
		dibujarP();
		escalado(transX, transY, pfX, pfY);
	}
	else if(opcion==3)
	{
		dibujarP();
		rotacion(transX, transY, ang);
	}
	
	glFlush ();
}

int main(int argc, char ** argv)
{	cout <<"Selecciona una opcion:\n\n"<<endl;
	cout << "1. Translacion" << endl;
	cout << "2. Escalado" << endl;
	cout << "3. Rotacion" << endl;
	cout << "4. Exit" << endl;
	cin >> opcion;
	
	if(opcion==4)
	{
		return 0;
	}
	
	cout <<"\n\nPara dibujar el poligono:\n" << endl;
	
	cout << "Ingrese numero de vertices: "; cin >> vertices;

	for (int i = 0; i < vertices; i++)
	{
		cout << "Ingrese la coordenada del vertice  " << i + 1 << " : "; cin >> pntX1 >> pntY1;
		pntX.push_back(pntX1);
		pntY.push_back(pntY1);
	}
	
	if(opcion==1)
	{
		cout << "Ingrese el factor de traslación para X e Y: "; cin >> transX >> transY;
	}
	else if(opcion==2)
	{
		cout << "Ingrese el factor de escala para X e Y: "; cin >> transX >> transY;
		cout << "Ingrese coordenada de punto fijo: "; cin >> pfX >> pfY;
	}
	else if(opcion==3)
	{
		cout << "Ingrese coordenada de punto pivote: "; cin >> transX >> transY;
		cout << "Ingrese angulo de rotacion: "; cin >> ang;
	}
	
	
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (600, 600);
	glutInitWindowPosition (100, 150);
	glutCreateWindow ("Transformaciones básicas");
	glutDisplayFunc(Display);
	iniciador ();
	glutMainLoop();

}
