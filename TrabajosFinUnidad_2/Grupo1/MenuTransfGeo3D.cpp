#include <stdio.h>
#include <iostream>
#include <stdarg.h>
#include <math.h>
#define GL_GLEXT_PROTOTYPES
#ifdef _APPLE_
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;
void cubo();
void transformacionesGeometricas();
void Piramide_base_Cuadrada();
void traslacion();
void menu();

double rotate_y=0; 
double rotate_x=0;
double transleate_x = 0;
double translate_y = 0;
double escalate = 0.2; 

void cubo(){

  //  Borrar pantalla y Z-buffer
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  // Resetear transformaciones
  glLoadIdentity();        
  // Traslacion de objeto
  glTranslatef( transleate_x, translate_y, 0 );     
  // glRotatef( 180, 0.0, 1.0, 0.0 );    // No incluido

  // Rotar cuando el usuario cambie “rotate_x” y “rotate_y”
  glRotatef( rotate_x, 1.0, 0.0, 0.0 );
  glRotatef( rotate_y, 0.0, 1.0, 0.0 );

  // Escalamiento de objeto
  glScalef( escalate, escalate, escalate );     


	//CREANDO CUBO
  //LADO FRONTAL: lado multicolor
  glBegin(GL_POLYGON);
 
  glColor3f( 1.0, 0.0, 0.0 );     glVertex3f(  0.5, -0.5, -0.5 );      // P1 es rojo
  glColor3f( 0.0, 1.0, 0.0 );     glVertex3f(  0.5,  0.5, -0.5 );      // P2 es verde
  glColor3f( 0.0, 0.0, 1.0 );     glVertex3f( -0.5,  0.5, -0.5 );      // P3 es azul
  glColor3f( 1.0, 0.0, 1.0 );     glVertex3f( -0.5, -0.5, -0.5 );      // P4 es morado
 
  glEnd();

  // LADO TRASERO: lado blanco
  glBegin(GL_POLYGON);
  glColor3f(   1.0,  1.0, 1.0 );
  glVertex3f(  0.5, -0.5, 0.5 );
  glVertex3f(  0.5,  0.5, 0.5 );
  glVertex3f( -0.5,  0.5, 0.5 );
  glVertex3f( -0.5, -0.5, 0.5 );
  glEnd();
 
  // LADO DERECHO: lado morado
  glBegin(GL_POLYGON);
  glColor3f(  1.0,  0.0,  1.0 );
  glVertex3f( 0.5, -0.5, -0.5 );
  glVertex3f( 0.5,  0.5, -0.5 );
  glVertex3f( 0.5,  0.5,  0.5 );
  glVertex3f( 0.5, -0.5,  0.5 );
  glEnd();
 
  // LADO IZQUIERDO: lado verde
  glBegin(GL_POLYGON);
  glColor3f(   0.0,  1.0,  0.0 );
  glVertex3f( -0.5, -0.5,  0.5 );
  glVertex3f( -0.5,  0.5,  0.5 );
  glVertex3f( -0.5,  0.5, -0.5 );
  glVertex3f( -0.5, -0.5, -0.5 );
  glEnd();
 
  // LADO SUPERIOR: lado azul
  glBegin(GL_POLYGON);
  glColor3f(   0.0,  0.0,  1.0 );
  glVertex3f(  0.5,  0.5,  0.5 );
  glVertex3f(  0.5,  0.5, -0.5 );
  glVertex3f( -0.5,  0.5, -0.5 );
  glVertex3f( -0.5,  0.5,  0.5 );
  glEnd();
 
  // LADO INFERIOR: lado rojo
  glBegin(GL_POLYGON);
  glColor3f(   1.0,  0.0,  0.0 );
  glVertex3f(  0.5, -0.5, -0.5 );
  glVertex3f(  0.5, -0.5,  0.5 );
  glVertex3f( -0.5, -0.5,  0.5 );
  glVertex3f( -0.5, -0.5, -0.5 );
  glEnd();
 
  glFlush();
  //Estamos utilizando dos buffer y promueve el contenido del bufer
  glutSwapBuffers();
}

void Piramide_base_Cuadrada(){

  //  Borrar pantalla y Z-buffer
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  // Resetear transformaciones
  glLoadIdentity();
  // Otras transformaciones
  glTranslatef( transleate_x, translate_y, 0 );     
  // glRotatef( 180, 0.0, 1.0, 0.0 );    // No incluido

  // Rotar cuando el usuario cambie “rotate_x” y “rotate_y”
  glRotatef( rotate_x, 1.0, 0.0, 0.0 );
  glRotatef( rotate_y, 0.0, 1.0, 0.0 );

  // Otras transformaciones
  glScalef( escalate, escalate, escalate );          // No incluido

	glBegin( GL_TRIANGLES );
glColor3f( 1.0f, 0.0f, 0.0f ); glVertex3f( 0.0f, 1.f, 0.0f );
glColor3f( 0.0f, 1.0f, 0.0f ); glVertex3f( -1.0f, -1.0f, 1.0f );
glColor3f( 0.0f, 0.0f, 1.0f ); glVertex3f( 1.0f, -1.0f, 1.0f);

glColor3f( 1.0f, 0.0f, 0.0f ); glVertex3f( 0.0f, 1.0f, 0.0f);
glColor3f( 0.0f, 1.0f, 0.0f ); glVertex3f( -1.0f, -1.0f, 1.0f);
glColor3f( 0.0f, 0.0f, 1.0f ); glVertex3f( 0.0f, -1.0f, -1.0f);

glColor3f( 1.0f, 0.0f, 0.0f ); glVertex3f( 0.0f, 1.0f, 0.0f);
glColor3f( 0.0f, 1.0f, 0.0f ); glVertex3f( 0.0f, -1.0f, -1.0f);
glColor3f( 0.0f, 0.0f, 1.0f ); glVertex3f( 1.0f, -1.0f, 1.0f);

glColor3f( 1.0f, 0.0f, 0.0f ); glVertex3f( -1.0f, -1.0f, 1.0f);
glColor3f( 0.0f, 1.0f, 0.0f ); glVertex3f( 0.0f, -1.0f, -1.0f);
glColor3f( 0.0f, 0.0f, 1.0f ); glVertex3f( 1.0f, -1.0f, 1.0f);
glEnd();
  glFlush();
  glutSwapBuffers();
}
void transformacionesGeometricas( unsigned char tecla, int x, int y )
{

	switch(tecla)
	{
		case'x':rotate_y += 5;//derecha
				break; 
				
		case's':rotate_y -= 5;//izquierda
				break;
		case'z':rotate_x += 5;//arriba
				break;
		case'+':escalate += 0.2;//aumentar
				break; 		
		case'-':escalate -= 0.2; //disminuir
				break;
	//	case'x':rotate_x -= 5;//abajo
			//	break;			
	}
  //  Solicitar actualización de visualización
  glutPostRedisplay();
}
/*void traslacion(int btn, int state, int x, int y)
{ 
	if((state==GLUT_DOWN) && (btn==GLUT_LEFT_BUTTON))
	{
			translate_y = translate_y + 0.2;
			transleate_x=transleate_x + 0.2;

	}
  glutPostRedisplay();
 }*/

void specialKeys1( int key, int x, int y ) {
 
  //  Flecha derecha: aumentar rotación 5 grados
  int mod_key = glutGetModifiers();
  // Comprobraciones para translacion
  
   if (key == GLUT_KEY_RIGHT)
	 transleate_x += 0.2;
	
   if (key == GLUT_KEY_LEFT)	
   	 transleate_x -= 0.2;
 
   if (key == GLUT_KEY_UP )	
   	 translate_y += 0.2;

   if (key == GLUT_KEY_DOWN)	
     translate_y -= 0.2;
  glutPostRedisplay();
}

void menu()
{
	system("cls");
	bool repite=true;
	int a;
	system("color 70");
	cout<<"\n\t\t\t ------------------------------\n";	
	cout<<"\n\t\t\t\tMENU PRINCIPAL\n";	
	cout<<"\n\t\t\t ------------------------------\n";	
	cout<<"\n\t\t1. Dibujar Cubos \n";
	cout<<"\n\t\t2. Dibujar Piramides \n";
	cout<<"\n\t\t3. Salir\n";
	cout<<"\n\t\tIngrese su eleccion: ";
	cin>>a;
	system("cls");
	switch(a)
	{
		case 1:
			cout<<"\n\t\t\t ------------------------------\n";	
			cout<<"\n\t\t\t\tDIBUJANDO CUBOS\n";	
			cout<<"\n\t\t\t ------------------------------\n";
			glutCreateWindow("CUBO");
			  //  Habilitar la prueba de profundidad de Z-buffer
			glEnable(GL_DEPTH_TEST);
  			glutDisplayFunc(cubo);
  			glutSpecialFunc(specialKeys1);
  			/*glutMouseFunc(traslacion);*/
  			glutKeyboardFunc(transformacionesGeometricas);
			glutMainLoop();
			break;
		case 2:
			cout<<"\n\t\t\t ------------------------------\n";	
			cout<<"\n\t\t\t\tDIBUJANDO PIRAMIDE\n";	
			cout<<"\n\t\t\t ------------------------------\n";
			glutCreateWindow("PIRAMIDE_BASE_CUADRADA");
			  //  Habilitar la prueba de profundidad de Z-buffer
  			glEnable(GL_DEPTH_TEST);
  			glutDisplayFunc(Piramide_base_Cuadrada);
  			glutKeyboardFunc(transformacionesGeometricas);
 			
			glutSpecialFunc(specialKeys1);
  			glutMainLoop();
			break;
		case 3:
			repite=false;
			break;	
	}	
}

int main(int argc, char* argv[]){
 
  //  Inicializar los parámetros GLUT y de usuario proceso
  glutInit(&argc,argv);

  //  Solicitar ventana con color real y doble buffer con Z-buffer 
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
 	
  // Crear ventana
/*  glutCreateWindow("Cubito mano");

  //  Habilitar la prueba de profundidad de Z-buffer
  glEnable(GL_DEPTH_TEST);

  // Funciones de retrollamada
  glutDisplayFunc(display);
  glutSpecialFunc(specialKeys);

  //  Pasar el control de eventos a GLUT
  glutMainLoop();*/
 	glutInitWindowSize(800,600);
	glutInitWindowPosition(50,50);
  //  Regresar al sistema operativo
  menu();
  return 0;
}
