#include <GL/glut.h>

//static winWidth = 500, winHeight = 500;

void init(void){
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

void wire(void){
	
	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 1.0);
	
	gluLookAt(2.0 , 2.0 , 2.0 , 0.0 , 0.0 , 0.0 , 0.0 , 0.0 , 1.0);
	
	glPushMatrix();
		glTranslatef (1.0 , 1.0 , 0.0) ;
		glutSolidSphere (0.75 , 8 , 6) ;
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef (1.0 , -0.5 , 0.5 ) ;
		glutWireCone (0.7 , 2.0 , 7 , 6) ;
	glPopMatrix ();
	
	
	GLUquadricObj * cylinder ; 
	
	glPushMatrix();
		glTranslatef(0.0 , 1.2 , 0.8);
		cylinder = gluNewQuadric();
		gluQuadricDrawStyle (cylinder , GLU_LINE);
		gluCylinder(cylinder , 0.6 , 0.6 , 1.5 , 6 , 4 );
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(1.0 , 2.9 , 0.8);
		glutSolidTorus(0.2,0.4,10,10);
	glPopMatrix();
	
	
	glFlush ();
}


void Reshape(GLint newWidth, GLint newHeight)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0 , 0 , newWidth, newHeight) ;
	glMatrixMode (GL_PROJECTION);
	glOrtho(-2.0 , 2.0 , -2.0 , 2.0 , 0.0 , 8.0) ;
	glMatrixMode(GL_MODELVIEW);
	
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (800, 800);
    glutInitWindowPosition (10, 10);
    //glutCreateWindow (argv[0]);
	glutCreateWindow("Superficies Cuádricas con modelo alámbrico") ;
	init();
	glutDisplayFunc(wire) ;
	glutReshapeFunc(Reshape) ;
	glutMainLoop();
	//return 0;
}


