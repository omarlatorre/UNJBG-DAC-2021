#include <GL/glut.h>

int tijera, profundidad;
int ventana[2];

void IniciarGLUT() {
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(600,600);
   glutInitWindowPosition(100,100);
   glutCreateWindow("Practica III,9 de OpenGL");

   glDepthFunc(GL_LEQUAL);
   glDepthRange(-1,1);
}

void PintarEscena() {
   glMatrixMode(GL_MODELVIEW);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();

   if (tijera) glEnable(GL_SCISSOR_TEST);
   if (profundidad) glEnable(GL_DEPTH_TEST);
   glScissor(100,100,ventana[0]-200,ventana[1]-200);

   float i;
   glBegin(GL_QUADS);
      for (i=-10; i<9; i++) {
         glColor3f((i+10)/20,0,0);
         glVertex3i(i,i,-i);
         glVertex3i(i+2,i,-i);
         glVertex3i(i+2,i+2,-i);
         glVertex3i(i,i+2,-i);
      }
   glEnd();

   glDisable(GL_DEPTH_TEST);
   glDisable(GL_SCISSOR_TEST);
   
   glutSwapBuffers();
}

void ReProyectar(int w, int h) {
   GLfloat formato;

   ventana[0] = w;
   ventana[1] = h;

   if(h == 0) h = 1;
   
   glViewport(0, 0, w, h);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   formato = (GLfloat)w / (GLfloat)h;
   if (w <= h) glOrtho (-10.0f, 10.0f, -10.0f / formato, 10.0f / formato, -10.0f, 10.0f);
   else glOrtho (-10.0f * formato, 10.0f * formato, -10.0f, 10.0f, -10.0f, 10.0f);
}

void Teclado(unsigned char key, int x, int y) {
   switch (key) {
      case 'z': profundidad = !profundidad; break;
      case 't': tijera = !tijera; break;
   }
}

int main(int argc, char **argv) {
   glutInit(&argc,argv); //Solo necesario en Linux
   IniciarGLUT();
 
   glutReshapeFunc(ReProyectar);
   glutDisplayFunc(PintarEscena);
   glutIdleFunc(PintarEscena);
   glutKeyboardFunc(Teclado);
 
   glutMainLoop();
   return 0;
}

