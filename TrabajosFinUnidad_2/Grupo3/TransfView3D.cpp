#include <GL/freeglut.h> 
#define _USE_MATH_DEFINES
#include <math.h>

class Renderer {

public:
  float t;

public:
  Renderer() : t(0.0) {}

public:

  void resize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective (30.0, (float)w/(float)h, 2.0, 20.0);
  }

  void display() {    
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    double rad = M_PI / 180.0f * t;
    
    //Funcion de la libreria 
    
//    gluLookAt(10.0*cos(rad), 5.0 , 10.0*sin(rad), // eye
//    gluLookAt(10.0, 10.0 , 10.0, // eye
//              0.0, 0.0, 0.0, // look at
//              0.0, 1.0, 0.0); // up

	//Mi function lookAt
//
	  myLookAt(10.0*cos(rad), 5.0 , 10.0*sin(rad), // eye
//	  lookAt(10.0, 10.0 , 10.0, // eye
              0.0, 0.0, 0.0, // look at
              0.0, 1.0, 0.0); // up

    //draw cube at origin
    drawCube();

    glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
    glTranslatef(2.5f, 0.0f, 0.0f );
    glScalef(0.5f, 0.5f, 0.5f);

    drawCube(); //draw transformed cube
  }

  void init() {
    glEnable(GL_DEPTH_TEST);
  }
  
private:
	
  void drawCube() {
  	
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f,-1.0f, 1.0f);
    glVertex3f( 1.0f,-1.0f, 1.0f);
    glVertex3f( 1.0f, 1.0f, 1.0f);
    glEnd();
    glColor3f(0.0,1.0,0.0);
    glBegin(GL_POLYGON);
    glVertex3f( 1.0f, 1.0f,-1.0f);
    glVertex3f( 1.0f,-1.0f,-1.0f);
    glVertex3f(-1.0f,-1.0f,-1.0f);
    glVertex3f(-1.0f, 1.0f,-1.0f);
    glEnd();
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_POLYGON);
    glVertex3f( 1.0f, 1.0f, 1.0f);
    glVertex3f( 1.0f,-1.0f, 1.0f);
    glVertex3f( 1.0f,-1.0f,-1.0f);
    glVertex3f( 1.0f, 1.0f,-1.0f);
    glEnd();
    glColor3f(1.0,1.0,0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-1.0f, 1.0f,-1.0f);
    glVertex3f(-1.0f,-1.0f,-1.0f);
    glVertex3f(-1.0f,-1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glEnd();
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_POLYGON);
    glVertex3f( 1.0f, 1.0f,-1.0f);
    glVertex3f(-1.0f, 1.0f,-1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f( 1.0f, 1.0f, 1.0f);
    glEnd();
    glColor3f(0.0,1.0,1.0);
    glBegin(GL_POLYGON);
    glVertex3f( 1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f,-1.0f);
    glVertex3f( 1.0f, -1.0f,-1.0f);  
    glEnd();
  }
  
  void myLookAt(float posix, float posiy, float posiz,
			float centerx, float centery, float centerz,
			float  upx, float  upy, float  upz)
  {
		
		float efe_x = centerx - posix; // Se calcula el vector del "eye"
		float efe_y = centery - posiy;
		float efe_z = centerz - posiz;
		
		float v_normalizado = sqrt(efe_x * efe_x + efe_y * efe_y + efe_z * efe_z); // Se normaliza 
		
		efe_x /= v_normalizado;     // Se encuentra el vector "f"
		efe_y /= v_normalizado;
		efe_z /= v_normalizado;
		
		// Productos Vectoriales , producto cruz
		
		float ele_x = efe_y * upz - efe_z * upy;     // Se calcula el vector "l"
		float ele_y = efe_z * upx - efe_x * upz;
		float ele_z = efe_x * upy - efe_y * upx;
	
		float u_x = ele_y * efe_z - ele_z * efe_y;	 // Se calcula el nuevo vector "u" (up)
		float u_y = ele_z * efe_x - ele_x * efe_z;
		float u_z = ele_x * efe_y - ele_y * efe_x;
		
		// Matrix 
		float mat[16] = {
			ele_x, u_x, -efe_x, 0,
			ele_y, u_y, -efe_y, 0,
			ele_z, u_z, -efe_z, 0,
			0, 0, 0, 1
		};
		
		// Multiplicacion de Matrices
		glMultMatrixf(mat);
		
		glTranslatef(-posix, -posiy, -posiz);
	}
};

static Renderer *renderer;

static void glutResize(int w, int h) 
{
  renderer->resize(w,h);
}

static void glutDisplay() 
{
  renderer->display();
  glutSwapBuffers();
}

static void timer(int v) 
{
  float offset = 1.0f;
  renderer->t += offset;
  glutDisplay();
  glutTimerFunc(unsigned(20), timer, ++v);
}

int main(int argc, char **argv) 
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowPosition(100,100);
  glutInitWindowSize(320, 320);

  glutCreateWindow("Proyecto final");

  glutDisplayFunc(glutDisplay);
  glutReshapeFunc(glutResize);
  
  renderer = new Renderer;
  renderer->init();

  glutTimerFunc(unsigned(20), timer, 0);

  glutMainLoop();
}