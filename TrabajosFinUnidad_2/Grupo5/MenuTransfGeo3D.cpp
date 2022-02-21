#include <stdio.h>
#include <iostream>
#include <GL/glut.h>

#define VK_2 0x32
#define VK_4 0x34
#define VK_6 0x36
#define VK_8 0x38
#define VK_9 0x39

using namespace std;

int tecla;

float coordrotacion[2];
float coordtraslacion[2];
float coordescalacion[2];
float interval = 1000 / 60;

void inicoordenadas(){
	for(int i=0; i<=2; i++){
		coordrotacion[i]=0;
		coordtraslacion[i]=0;
		coordescalacion[i]=0;
	}
}

void escala(){
	for(int i=0; i<=2; i++){
	coordescalacion[i]=0.2;	
	}
}

void drawcubo(){
	
	  glBegin(GL_POLYGON);
		glColor3f(1,1,0);
		glVertex3f(  0.5, -0.5, -0.5 );
		glVertex3f(  0.5,  0.5, -0.5 );  
		glVertex3f( -0.5,  0.5, -0.5 );  
		glVertex3f( -0.5, -0.5, -0.5 ); 
		glEnd();
	
	  glBegin(GL_POLYGON);
	  glColor3f(   1.0,  1.0, 1.0 );//blanco
	  glVertex3f(  0.5, -0.5, 0.5 );
	  glVertex3f(  0.5,  0.5, 0.5 );
	  glVertex3f( -0.5,  0.5, 0.5 );
	  glVertex3f( -0.5, -0.5, 0.5 );
	  glEnd();
	 
	  glBegin(GL_POLYGON);
	  glColor3f(  1.0,  0.0,  1.0 );//morado
	  glVertex3f( 0.5, -0.5, -0.5 );
	  glVertex3f( 0.5,  0.5, -0.5 );
	  glVertex3f( 0.5,  0.5,  0.5 );
	  glVertex3f( 0.5, -0.5,  0.5 );
	  glEnd();
	 
	  glBegin(GL_POLYGON);
	  glColor3f(   0.0,  1.0,  0.0 );
	  glVertex3f( -0.5, -0.5,  0.5 );
	  glVertex3f( -0.5,  0.5,  0.5 );
	  glVertex3f( -0.5,  0.5, -0.5 );
	  glVertex3f( -0.5, -0.5, -0.5 );
	  glEnd();
	 
	  glBegin(GL_POLYGON);
	  glColor3f(   0.0,  0.0,  1.0 );//azul
	  glVertex3f(  0.5,  0.5,  0.5 );
	  glVertex3f(  0.5,  0.5, -0.5 );
	  glVertex3f( -0.5,  0.5, -0.5 );
	  glVertex3f( -0.5,  0.5,  0.5 );
	  glEnd();

	  glBegin(GL_POLYGON);
	  glColor3f(   1.0,  0.0,  0.0 );// rojo
	  glVertex3f(  0.5, -0.5, -0.5 );
	  glVertex3f(  0.5, -0.5,  0.5 );
	  glVertex3f( -0.5, -0.5,  0.5 );
	  glVertex3f( -0.5, -0.5, -0.5 );
	  glEnd();	
}

void drawpiramide(){
	
	glBegin(GL_QUADS);
		glColor3f(1,0,0);//rojo
		glVertex3d(-2,0,-2);
		
		glColor3f(1,1,0);//amarillo
		glVertex3d(-2,0,2);
		
		glColor3f(0,0,1);//azul
		glVertex3d(2,0,2);
		
		glColor3f(0,1,0);//verde
		glVertex3d(2,0,-2);
		glEnd();
		
		glBegin(GL_TRIANGLES);
		glColor3f(1,1,1);//blanco
		glVertex3d(0,2,0);
		glVertex3d(-2,0,-2);
		glVertex3d(2,0,-2);
		glEnd();
		
		glBegin(GL_TRIANGLES);
		glColor3f(1,1,1);//blanco
		glVertex3d(0,2,0);
		glColor3f(1,0,0);//rojo
		glVertex3d(2,0,-2);
		glVertex3d(2,0,2);
		glEnd();

		glBegin(GL_TRIANGLES);
		glColor3f(0,1,0);//verde
		glVertex3d(0,2,0);
		glVertex3d(-2,0,2);
		glVertex3d(-2,0,-2);
		glEnd();
		
		glBegin(GL_TRIANGLES);
		glColor3f(1,1,1);//blanco
		glVertex3d(0,2,0);
		glColor3f(0,0,1);
		glVertex3d(2,0,2);
		glVertex3d(-2,0,2);
		glEnd();
}

void transformacion(){

		//ESCALAMIENTO
		glScalef( coordescalacion[0], coordescalacion[1], coordescalacion[2] ); 
		
		//TRASLACION
		glTranslatef( coordtraslacion[0], coordtraslacion[1], 0 );     
		
		//ROTACION
		glRotatef(coordrotacion[0], 1.0, 0.0, 0.0);
		glRotatef(coordrotacion[1], 0.0, 1.0, 0.0);
		glRotatef(coordrotacion[2], 0.0, 0.0, 1.0);
		
}
void display(){

  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
	transformacion();
	if(tecla == 2){
	 	drawcubo();
	}
	if(tecla == 1){
		drawpiramide();
	}

  glFlush();
  glutSwapBuffers();
}

void tecladotransformacion( unsigned char tecla, int x, int y)
{
	switch(tecla)
	{
		case'x':coordrotacion[0] += 1;//derecha
				break; 
		case's':coordrotacion[1] += 1;//izquierda
				break;
		case'z':coordrotacion[2] += 0.01;//arriba
				break;
				
		case'-': coordescalacion[0] -= 0.02;
				 coordescalacion[1] -= 0.02;
				 coordescalacion[2] -= 0.02;
				break;
		case'+': coordescalacion[0] += 0.02;
			     coordescalacion[1] += 0.02;
				 coordescalacion[2] += 0.02;	
				break;		
	}
  glutPostRedisplay();
}

void keyboard(){

	if (GetAsyncKeyState(VK_2)){
	coordtraslacion[1] -= 0.1;
		}
	else if (GetAsyncKeyState(VK_8)){
	coordtraslacion[1] += 0.1;
		}
	if (GetAsyncKeyState(VK_4)){
	coordtraslacion[0] -= 0.1;
		}
	else if (GetAsyncKeyState(VK_6)){
	coordtraslacion[0] += 0.1;
		}	
	if (GetAsyncKeyState(VK_9)){
			exit(0);
		}
}


void Update(int value)
{
	keyboard();
	glutTimerFunc(interval, Update, 0);
	glutPostRedisplay();
}

int main(int argc, char* argv[]){

		glutInit(&argc,argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
		escala();
		
		cout<<"\n\t----ACTIVIDAD 01----\n";	
		cout<<"\tDibujar cubos y piramides\n";	
		cout<<"\n\t 1. Figura de piramide \n";
		cout<<"\n\t 2. Figura de cubo \n";
		
		cout<<"\n\tElige la figura geometrica : ";
		cin>>tecla;
		
		glutCreateWindow("FIGURA ELEGIDA");
		glEnable(GL_DEPTH_TEST);
		glutDisplayFunc(display);
		glutTimerFunc(interval, Update, 0);
		glutKeyboardFunc(tecladotransformacion);
		
		glutMainLoop();
		return 0;		
}
