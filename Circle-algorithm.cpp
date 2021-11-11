#include <stdlib.h> 
#include <stdio.h>
#include <GL\glut.h>

/*  Midpoint Circle Drawing
*/

class circulo 
{ 
	private : 
		GLint x, y; 
	public : 
	/* Constructor predeterminado: inicializa las coordenadas a (0, 0). */ 
	circulo ( ) 
	{ 
		x = 0, y = 0; 
	} 
	void setCoords (GLint xCoordValue, GLint yCoordValue) 
	{ 
		x = xCoordValue; 
		y = yCoordValue; 
	} 
	GLint getx ( ) const 
	{ 
		return x; 
	} 
	GLint gety ( ) const 
	{
		return y; 
	} 
	void incrementx ( )
	{ 
		x++ ; 
	} 
	void decrementy ( )
	{ 
		y--; 
	} 
};


void Pixel (GLint xCoord,GLint yCoord)
{
	glBegin (GL_POINTS);
    	glVertex2i (xCoord,yCoord);
	glEnd ();
}

void circlePlotPoints (GLint xc, GLint yc, circulo circ) 
{
	Pixel (xc + circ.getx ( ), yc + circ.gety() );
	Pixel (xc - circ.getx ( ) , yc + circ.gety()  );
	Pixel (xc + circ.getx ( ), yc - circ.gety() );
	Pixel (xc - circ.getx ( ) , yc - circ.gety() );
	Pixel (xc + circ.gety ( ) , yc + circ.getx() );
	Pixel (xc - circ.gety ( ) , yc + circ.getx() );
	Pixel (xc + circ.gety ( ), yc - circ.getx() );
	Pixel (xc - circ.gety ( ), yc - circ.getx() ) ;
}

 void midcirculo(GLint xc, GLint yc, GLint radius) 
 { 
	 
	circulo circ;
 
	GLint p= 1- radius; // Valor inicial para P1 parámetro de punto medio 
	circ.setCoords (0, radius); // Establecer coordenadas para punto superior del círculo. 
	circlePlotPoints (xc, yc, circ); /* Calcular el siguiente punto y dibujarlo en cada octante. */ 
	while (circ.getx ( ) < circ.gety ( )) 
	{ 
		circ.incrementx ( ); 
		if (p < 0) 
		{
			p += 2 * circ.getx ( ) + 1; 
		}
		else { 
			circ.decrementy ( ); 
			p += 2 * (circ.getx ( ) - circ.gety ( )) + 1; 
		} 
		circlePlotPoints (xc, yc, circ); 
	}
 }
void init(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0,0.0,0.0,1.0);
    glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);
}
void display(void) 
{
	midcirculo(200, 200, 150);
	glFlush();
}

int main (int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition (50, 50);
	glutInitWindowSize (400, 300);
	glutCreateWindow ("An Example OpenGL Program");
	
	init ();
	glutDisplayFunc(display);
	glutMainLoop ();
	return 0;
}


