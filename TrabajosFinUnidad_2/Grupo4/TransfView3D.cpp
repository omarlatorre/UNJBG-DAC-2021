#include <iostream>
#include <GL/glut.h>
#include<GL/freeglut.h>
#include <cmath>

using namespace std;

GLfloat vex=0.0,vey=1.0,vez=5.0,vtx=0.0,vty=0.0,vtz=0.0,upx=0.0,upy=1.0,upz=0.0;
GLfloat matriz_R[16];
bool cambio=true,menuuso=false,matriz_v=true,p_vista=true;
int menux=1,menuy=1;
const GLfloat light_ambient[]  = { 0.3, 0.3, 0.3, 1.0 };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 30.0f ,50.0f, 40.0f, 1.0f };

int valor=1;
void tiempo(int param){
	glutPostRedisplay();
	glutTimerFunc(valor,tiempo,0);	
}
void letra(float x, float y,float z, char *string,int a){
    switch(a){
    	case 1:
		glColor3f(0,1,0); break;
		case 2:
		glColor3f(1,1,1); break;
		case 3:
		glColor3f(0.3,1,0.3); break;
		default:	
		glColor3f(0.5,0.5,0.5);
	}
	int len, i;
    glRasterPos2f(x, y);
    len = (int) strlen(string);
    for (i = 0; i < len; i++) {
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[i]);
    }
  }
int menu_color(int x,int y){
	if(menuuso){
		if(menux==x&&menuy==y)
			return 3;
		else
			return 4;
	}
	else{
		if(menux==x&&menuy==y)
			return 2;
		else
			return 1;
	}
}
void L_menu(int xm, int ym, float m,float X,float Y,bool T){
	char num1 [17];
glPushMatrix();
	glTranslatef(X,Y,-1);
	glScalef(0.0006,0.0006,1);
	sprintf(num1, "%f", m);
	if(T)
	letra(-0.85,-0.5,0,num1,menu_color(xm,ym));
	else
	letra(-0.85,-0.5,0,num1,1);
glPopMatrix();
}
void ControlRaton( int button, int state, int x, int y ){
    if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
        cambio=!cambio;
    }
    if (button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN){
        matriz_v=!matriz_v;
    }
}
void ControlTeclado(unsigned char key,int x,int y ){  
    if(key=='e')
    	p_vista=!p_vista;
	
	if(menuuso){
	    switch(key){  
	        case 'a':  
	            if(menux==1&&menuy==1)
				vex=vex-0.1;  
				if(menux==2&&menuy==1)
				vey=vey-0.1;  
				if(menux==3&&menuy==1)
				vez=vez-0.1;  
				if(menux==1&&menuy==2)
				vtx=vtx-0.1;  
				if(menux==2&&menuy==2)
				vty=vty-0.1;  
				if(menux==3&&menuy==2)
				vtz=vtz-0.1; 
				if(menux==1&&menuy==3)
				upx=upx-0.1;  
				if(menux==2&&menuy==3)
				upy=upy-0.1;  
				if(menux==3&&menuy==3)
				upz=upz-0.1; 
	            break;  
	        case 'd':  
	            if(menux==1&&menuy==1)
				vex=vex+0.1;  
				if(menux==2&&menuy==1)
				vey=vey+0.1;  
				if(menux==3&&menuy==1)
				vez=vez+0.1;  
				if(menux==1&&menuy==2)
				vtx=vtx+0.1;  
				if(menux==2&&menuy==2)
				vty=vty+0.1;  
				if(menux==3&&menuy==2)
				vtz=vtz+0.1; 
				if(menux==1&&menuy==3)
				upx=upx+0.1;  
				if(menux==2&&menuy==3)
				upy=upy+0.1;  
				if(menux==3&&menuy==3)
				upz=upz+0.1; 
	            break;  
	        case ' ':
			 	menuuso=!menuuso;
				break;       
	    } 	
	}
	else{
		switch(key){  
	        case 'a':
				if(menux==1)
				menux=3;
				else  
	            menux=menux-1; 
	            break;  
	        case 'd':  
	        	menux=(menux%3)+1;
	            break;  
	        case 'w':  
	            if(menuy==1)
				menuy=3;
				else  
	            menuy=menuy-1; 
	            break;    
	        case 's':  
	            menuy=(menuy%3)+1;
	            break; 
	        case ' ':
			 	menuuso=!menuuso;
				break;  
	    } 	
	}
} 
struct Vector
{
    GLfloat x,y,z;
    Vector()
    {
        x=y=z=0;
    }
    Vector(GLfloat x2, GLfloat y2, GLfloat z2)
    {
        x=x2;
        y=y2;
        z=z2;
    }
};
void mod(Vector &vector)
{
    GLfloat div=sqrt(vector.x*vector.x+vector.y*vector.y+vector.z*vector.z);
    vector.x=vector.x/div;
    vector.y=vector.y/div;
    vector.z=vector.z/div;
}
Vector vectorial(Vector a, Vector b)
{
    return Vector(a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x);
}
void LookAt(GLfloat veX, GLfloat veY, GLfloat veZ, GLfloat vtX, 
GLfloat vtY, GLfloat vtZ, GLfloat upX, GLfloat upY, GLfloat upZ)
{
    memset(matriz_R, 0, sizeof(matriz_R));
    matriz_R[15] = 1;
    Vector f(vtX - veX, vtY - veY, vtZ - veZ);
    mod(f);
    Vector up(upX, upY, upZ);
    Vector l = vectorial(f, up);
    mod(l);
    up = vectorial(l, f);
    matriz_R[0] = l.x;
    matriz_R[4] = l.y;
    matriz_R[8] = l.z;
    matriz_R[1] = up.x;
    matriz_R[5] = up.y;
    matriz_R[9] = up.z;
    matriz_R[2] = -f.x;
    matriz_R[6] = -f.y;
    matriz_R[10] = -f.z;
    glLoadMatrixf(matriz_R);
    glTranslated(-veX, -veY, -veZ);
}
void menu(){
	int color_c=1;
	char num [17];
glPushMatrix();
	if(cambio){
		glTranslatef(-0.04,0.5,-1);
		glScalef(0.0006,0.0006,1);
		letra(0,1,0,"LookAt",2);
	}
	else{
		glTranslatef(-0.065,0.5,-1);
		glScalef(0.0006,0.0006,1);
		letra(0,1,0,"gluLookAt",2);
	}
glPopMatrix();
glPushMatrix();
	glTranslatef(0,0.555,-1.1);
	glScalef(0.3,0.1,0.000001);
	glColor4f(0,0,0,1);
	glutSolidCube(1);
glPopMatrix();	
glPushMatrix();
	glTranslatef(-0.85,-0.3,-1);
	glScalef(0.0006,0.0006,1);
	letra(0,0,0,"X",4);
glPopMatrix();
glPushMatrix();
	glTranslatef(-0.7,-0.3,-1);
	glScalef(0.0006,0.0006,1);
	letra(0,0,0,"Y",4);
glPopMatrix();
glPushMatrix();
	glTranslatef(-0.55,-0.3,-1);
	glScalef(0.0006,0.0006,1);
	letra(0,0,0,"Z",4);
glPopMatrix();
glPushMatrix();
	glTranslatef(-0.97,-0.35,-1);
	glScalef(0.0006,0.0006,1);
	letra(0,0,0,"Ve",4);
glPopMatrix();
glPushMatrix();
	glTranslatef(-0.97,-0.4,-1);
	glScalef(0.0006,0.0006,1);
	letra(0,0,0,"Vt",4);
glPopMatrix();
glPushMatrix();
	glTranslatef(-0.97,-0.45,-1);
	glScalef(0.0006,0.0006,1);
	letra(0,0,0,"Up",4);
glPopMatrix();
L_menu(1,1, vex,-0.90,-0.35,true);
L_menu(2,1, vey,-0.75,-0.35,true);
L_menu(3,1, vez,-0.60,-0.35,true);
L_menu(1,2,vtx,-0.90,-0.4,true);
L_menu(2,2,vty,-0.75,-0.4,true);
L_menu(3,2,vtz,-0.60,-0.4,true);
L_menu(1,3,upx,-0.90,-0.45,true);
L_menu(2,3,upy,-0.75,-0.45,true);
L_menu(3,3,upz,-0.60,-0.45,true);
glPushMatrix();
	glTranslatef(-0.8,-0.41,-1.1);
	glScalef(0.6,0.25,0.000001);
	glColor4f(0,0,0,1);
	glutSolidCube(1);
glPopMatrix();
	if(matriz_v){
		glPushMatrix();
		glTranslatef(0.52,0,-1);
		glScalef(0.0006,0.0006,1);
		letra(0,0,0,"Matriz de Traslacion T",2);
		glPopMatrix();
		L_menu(1,1,1,0.4,-0.05,false);
	    L_menu(1,1,0,0.55,-0.05,false);
	    L_menu(1,1,0,0.7,-0.05,false);
	    L_menu(1,1,-vex,0.85,-0.05,false);
	    L_menu(1,1,0,0.4,-0.1,false);
	    L_menu(1,1,1,0.55,-0.1,false);
	    L_menu(1,1,0,0.7,-0.1,false);
	    L_menu(1,1,-vey,0.85,-0.1,false);
	    L_menu(1,1,0,0.4,-0.15,false);
	    L_menu(1,1,0,0.55,-0.15,false);
	    L_menu(1,1,1,0.7,-0.15,false);
	    L_menu(1,1,-vez,0.85,-0.15,false);
	    L_menu(1,1,0,0.4,-0.2,false);
	    L_menu(1,1,0,0.55,-0.2,false);
	    L_menu(1,1,0,0.7,-0.2,false);
	    L_menu(1,1,1,0.85,-0.2,false);
		glPushMatrix();
		glTranslatef(0.54,-0.25,-1);
		glScalef(0.0006,0.0006,1);
		letra(0,0,0,"Matriz de Rotacion R",2);
		glPopMatrix();   
	    L_menu(1,1,matriz_R[0],0.4,-0.3,false);
	    L_menu(1,1,matriz_R[4],0.55,-0.3,false);
	    L_menu(1,1,matriz_R[8],0.7,-0.3,false);
	    L_menu(1,1,0,0.85,-0.3,false);
	    L_menu(1,1,matriz_R[1],0.4,-0.35,false);
	    L_menu(1,1,matriz_R[5],0.55,-0.35,false);
	    L_menu(1,1,matriz_R[9],0.7,-0.35,false);
	    L_menu(1,1,0,0.85,-0.35,false);
	    L_menu(1,1,-matriz_R[2],0.4,-0.4,false);
	    L_menu(1,1,-matriz_R[6],0.55,-0.4,false);
	    L_menu(1,1,-matriz_R[10],0.7,-0.4,false);
	    L_menu(1,1,0,0.85,-0.4,false);
	    L_menu(1,1,0,0.4,-0.45,false);
	    L_menu(1,1,0,0.55,-0.45,false);
	    L_menu(1,1,0,0.7,-0.45,false);
	    L_menu(1,1,1,0.85,-0.45,false);
	    glPushMatrix();
		glTranslatef(0.75,-0.24,-1.1);
		glScalef(0.7,0.58,0.000001);
		glColor4f(0,0,0,1);
		glutSolidCube(1);
		glPopMatrix();
	}
}
void dibujar(){
	glPushMatrix();
	glTranslatef(-0.3,0,-1);
	glScalef(1,1.2,1);
	glColor4f(0.1506,0.3506,0.3506,0.5);
	glutSolidTeapot(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.4,-0.03,2);
	glScalef(1,1,1);
	glColor4f(0.1882,0.2784,0.3843,0.5);
	glutSolidIcosahedron();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0,-1,0);
	glScalef(10,0.2,10);
	glColor4f(0.9412,0.3294,0.3294,0.5);
	glutSolidCube(1);
	glPopMatrix();
}
void display(void)
{
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glClearColor(0.5,0.5,0.5,0.0);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	
	menu();
	if(cambio){
		LookAt (vex, vey, vez, vtx, vty, vtz, upx, upy, upz);
		if(p_vista){
			glPushMatrix();
			glTranslatef(vtx,vty,vtz);
			glScalef(1,1,1);
			glColor4f(0,1,0,1);
			glutSolidSphere(0.3,50,50);
			glPopMatrix();
		}		
	}
	else{
		gluLookAt (vex, vey, vez, vtx, vty, vtz, upx, upy, upz);
		if(p_vista){
			glPushMatrix();
			glTranslatef(vtx,vty,vtz);
			glScalef(1,1,1);
			glColor4f(1,0,0,1);
			glutSolidSphere(0.3,50,50);
			glPopMatrix();
		}
	}
	dibujar();
	glFlush();
	glutSwapBuffers();  
	glutMouseFunc(ControlRaton);
	glutKeyboardFunc(ControlTeclado);  
}
void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);  
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 100.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}
int main(int argc, char ** argv)
{	
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
glutInitWindowPosition(0,0);
glutInitWindowSize(1280,720);
glutCreateWindow("Proyecto");
glutDisplayFunc(display);
glutReshapeFunc(reshape); 
glutTimerFunc(valor,tiempo,0);	
glutMainLoop();
return 0;
}
