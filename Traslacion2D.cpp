#include <GL\glut.h>


void iniciar(){
	//color para limpiar el buffer
	glClearColor(0, 0, 0, 1);
	
	//Color de la linea
	//glColor3f(1.f, 0, 0);
	
	//tamaño del punto o linea
	glLineWidth(3.f);
	
	//camara
	glOrtho(800, 0, 600, 0, -1, 1);
	
	//le decimos q usaremos matrices
	glMatrixMode(GL_MODELVIEW);
	
	//Cargamos
	glLoadIdentity();
}


void dibujar()
{
	//limpiamos pantalla con color de fondo, psdta pinta
	glClear(GL_COLOR_BUFFER_BIT);
		
		
		//PECTORALES
		glPushMatrix();	
		glTranslatef(0.0, 0.45, 0);
		glScalef (2.0f, 2.0f, 1.0f); // Escalar el doble en vertical
		//glRotatef (20.0f, 0.0f, 0.0f, 1.0f); // Rotar 45 grados en el eje y
		glRotated(20,0,0,1);
			glColor3f(0.0f, 0.5f, 0.5f);
			glBegin(GL_POLYGON);
			glVertex2f(0.0,0.0);
			glVertex2f(-0.04,0.02);
			glVertex2f(-0.15,0.02);
			glVertex2f(-0.15,-0.2);
			glVertex2f(0.15,-0.2);
			glVertex2f(0.15,0.02);
			glVertex2f(0.04,0.02);
			glEnd();
			
					
			//--------------------------
			//coordenada ubicación x=0, y=0
			glPointSize(10);
			glBegin(GL_POINTS);
			glColor3f(1.f, 0.f, 0);	
			glVertex2f(0.0, 0.0);		
			glEnd();
		glPopMatrix();
		
		
		
		// Punto Central
		glColor3f(1,0.6,0.6);
		glPushMatrix();
		glTranslatef(0.0f,0.0f,0);
			glPointSize(10);
			glBegin(GL_POINTS);
			glColor3f(1.f, 0.f, 0);	
			glVertex2f(0.0, 0.0);		
			glEnd();
		glPopMatrix();
	
	glFlush();

}
int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	
	//Inicializamos el modo video o display ( le decimos q trabajremos con RGB osea color | Decimos q trabajaremos con un solo buffer )
	glutInitDisplayMode(GLUT_RGB| GLUT_SINGLE);
	
	//Posición de inicio de la ventana
	glutInitWindowPosition (100,100);
	//Tamaño de la ventana
	glutInitWindowSize (600, 700);
	// nombre o título de la ventana
	glutCreateWindow ("taquitos pa llevar");
	
	//Función q llamamos
	iniciar();
	
	glutDisplayFunc(dibujar);
	
	
	// Loop o bucle que hara q nuestra función se ejecute for ever
	glutMainLoop();	
	
}
