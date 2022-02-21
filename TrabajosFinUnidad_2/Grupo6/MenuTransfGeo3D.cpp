#include <stdio.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

double rY = 0;
double rX = 0;
double rZ = 0;

GLfloat X = 0.0f;
GLfloat Y = 0.0f;
GLfloat Z = 0.0f;

GLfloat escala = 1.0f;

int opcion;

void PIRAMIDE ()
{
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	glRotatef(rX, 1.0, 0.0, 0.0);
	glRotatef(rY, 0.0, 1.0, 0.0);
	glRotatef(rZ, 0.0, 0.0, 1.0);
	
	glTranslatef(X, Y, Z);
	glScalef(escala, escala, escala);
	
	glBegin(GL_QUADS);
	glColor3f(1.0,1.0,1.0);
	glVertex3d(-0.2,0,-0.2);
	glVertex3d(-0.2,0,0.2);
	glVertex3d(0.2,0,0.2);
	glVertex3d(0.2,0,-0.2);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0,1,0.6);
	glVertex3d(0,0.2,0);
	glVertex3d(-0.2,0,-0.2);
	glVertex3d(0.2,0,-0.2);
	glEnd();
	
	glBegin(GL_TRIANGLES);
	glColor3f(1,0,0);
	glVertex3d(0,0.2,0);
	glVertex3d(0.2,0,-0.2);
	glVertex3d(0.2,0,0.2);
	glEnd();
	
	glBegin(GL_TRIANGLES);
	glColor3f(0,1,0);
	glVertex3d(0,0.2,0);
	glVertex3d(-0.2,0,0.2);
	glVertex3d(-0.2,0,-0.2);
	glEnd();
	
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.1, 0.9);
	glVertex3d(0,0.2,0);
	glVertex3d(0.2,0,0.2);
	glVertex3d(-0.2,0,0.2);
	glEnd();
	
	glFlush();
	glutSwapBuffers();
}

void CUBO ()
{
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	glRotatef(rX, 1.0, 0.0, 0.0);
	glRotatef(rY, 0.0, 1.0, 0.0);
	glRotatef(rZ, 0.0, 0.0, 1.0);
	
	glTranslatef(X, Y, Z);
	glScalef(escala, escala, escala);
	
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(0.2,-0.2,-0.2);
	glVertex3f(0.2,0.2,-0.2);
	glVertex3f(-0.2,0.2,-0.2);
	glVertex3f(-0.2,-0.2,-0.2);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 0.60);
	glVertex3f(0.2,-0.2,0.2);
	glVertex3f(0.2,0.2,0.2);
	glVertex3f(-0.2,0.2,0.2);
	glVertex3f(-0.2,-0.2,0.2);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.5, 0.0);
	glVertex3f(0.2,-0.2,-0.2);
	glVertex3f(0.2,0.2,-0.2);
	glVertex3f(0.2,0.2,0.2);
	glVertex3f(0.2,-0.2,0.2);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.6, 0.80, 0.51);
	glVertex3f(-0.2,-0.2,0.2);
	glVertex3f(-0.2,0.2,0.2);
	glVertex3f(-0.2,0.2,-0.2);
	glVertex3f(-0.2,-0.2,-0.2);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.1, 0.9);
	glVertex3f(0.2,0.2,0.2);
	glVertex3f(0.2,0.2,-0.2);
	glVertex3f(-0.2,0.2,-0.2);
	glVertex3f(-0.2,0.2,0.2);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.2,-0.2,-0.2);
	glVertex3f(0.2,-0.2,0.2);
	glVertex3f(-0.2,-0.2,0.2);
	glVertex3f(-0.2,-0.2,-0.2);
	glEnd();
	
	glFlush();
	glutSwapBuffers();
}
/*void ejes(int x, int y)
{
	int mouseX=x;
	int mouseY=y;
	
	X = mouseX;
	Y = mouseY;
	glutPostRedisplay();
	
	
}*/
void raton(int boton, int estado, int x , int y)
{	
	if(boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN)
	{
		X+= 0.1;
		Y+= 0.1;
	}if(boton == GLUT_RIGHT_BUTTON && estado == GLUT_DOWN)
	{
		X-= 0.1;
		Y-= 0.1;
	}
	glutPostRedisplay();
}

void teclas (unsigned char key, int x , int y)
{
	switch(key){
		case '+':
			escala += 0.1;
			break;
			
		case '-':
			escala -= 0.1;
			break;
		
		/*case 'c':
			X += 0.50f;
			Y += 0.50f;
			Z += 0.50f;
			break;*/
		//rotación 
		case 'w':
			rX += 5;
			break;
		
		case 's':
			rX -= 5;
			break;
		
		case 'e':
			rY += 5;
			break;
		
		case 'r':
			rY -= 5;
			break;
		
		case 'a':
			rZ += 5;
			break;
		
		case 'd':
			rZ -= 5;
			break;
	}
	glutPostRedisplay();
}

int main (int argc, char* argv[])
{			
	cout<<"--------------------TRANSFORMACIONES GEOMÉTRICA 3D--------------------"<<endl;
	cout<<"  Escoja la figura a graficar: "<<endl;
	cout<<"     1. Cubo"<<endl;
	cout<<"     2. Piramide"<<endl;
	cin>>opcion;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800,800);
	glutInitWindowPosition(0,0);
	
	switch(opcion){
		case 1:
			
			glutCreateWindow("Transformaciones 3D");
			glEnable(GL_DEPTH_TEST);
			glutDisplayFunc(CUBO);
			glutKeyboardFunc(teclas);
			glutMouseFunc(raton);
			glutMainLoop();
			break;
		case 2:
			
			glutCreateWindow("Transformaciones 3D");
			glEnable(GL_DEPTH_TEST);
			glutDisplayFunc(PIRAMIDE);
			glutKeyboardFunc(teclas);
			glutMouseFunc(raton);
			glutMainLoop();
			break;
	}
	
	//glutSpecialFunc(flechasteclado);
	//glutMainLoop();
	return 0;
}
