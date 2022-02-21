
#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <gl\gl.h>
#include <gl\glu.h> 
#include <gl\glut.h>

#include <fstream>
#include <stdio.h>
#include "math.h"

using namespace std;

//static GLfloat translate_x = 0.0, translate_y = 0.0, translate_z = 0.0;
static GLfloat angulo_y = 0.0, angulo_x = 0.0;

// -----------------------------------------------------------------------------------------------------------------------------
//							VECTOR
// -----------------------------------------------------------------------------------------------------------------------------

class CVector {

	private:
		
		float nOrm_x,nOrm_y,nOrm_z;  // Estas tres coordenadas forman el vector normal.
		
	public: 
		
		// Constructores:
		// Por defecto con todas las coordenadas a 0, a las que se le indiquen y a las que se
		// le indiquen mas la normal.

		CVector (); 
		CVector (float cx, float cy, float cz);  
		CVector (float cx, float cy, float cz, CVector vNorm);
		
		~CVector();
		
		void set(CVector v); // Da un valor al vector 	
		
		
		float x,y,z;  // coordenadas x,y,z
		

	
		CVector operator +(CVector v2);   // Sobrecarga de los operadores para que sepa cómo actuar.
		CVector operator -(CVector v2);
};

CVector::CVector() {

	x = 0;
	y = 0;
	z = 0;
	
	nOrm_x = 0;
	nOrm_y = 0;
	nOrm_z = 0;
	

}

CVector::CVector(float cx, float cy, float cz) {

	x = cx;
	y = cy;
	z = cz; 

	

	nOrm_x = 0;
	nOrm_y = 0;
	nOrm_z = 0;


}


CVector::CVector(float cx, float cy, float cz, CVector vNorm) {

	x = cx;
	y = cy;
	z = cz; 

	//indice = 0;
	
	nOrm_x = vNorm.x;
	nOrm_y = vNorm.y;
	nOrm_z = vNorm.z;


}

CVector::~CVector() {


}


void CVector::set(CVector v) {

	x = v.x;
	y = v.y;
	z = v.z; 

}


CVector CVector::operator +(CVector v2) {
	
	CVector v;
	
	v.x = x + v2.x;
	v.y = y + v2.y;
    v.z = z + v2.z;

	return v;
}

CVector CVector::operator -(CVector v2) {
	
	CVector v;
	
	v.x = x - v2.x;
	v.y = y - v2.y;
    v.z = z - v2.z;

	return v;
}



// -----------------------------------------------------------------------------------------------------------------------------
//								CAMARA
// -----------------------------------------------------------------------------------------------------------------------------


class CCamera {

	private:
		
		CVector cPos;
		CVector cView;
		CVector cUp;
	
		float cSpeed,rSpeed;
		
	public: 

		CCamera();
		CCamera(CVector camera_pos,CVector camera_view ,CVector camera_up);
		~CCamera();
		void SetPos(CVector camera_pos);  // Indica la posicion de la camara.
		
		// Estas 4 funciones  realizan el movimiento de la camara 
		void Move(float speed);
		void rotate(float speed);
		void rotateUp(float droot);
		void StrafeUp(float droot);    

		CVector getPos();    // Obtiene las coordenadas de posicion de la camara
		CVector getView();   // Obtiene las coordenadas del vector de dirección de la camara
		CVector getUp();     // Obtiene las coordenadas del vector que apunta hacia arriba de la camara
		void Update();  // actualiza glutLookAt(..) Con los parametros de la camara
		void setSpeed(float speed);
};	

CCamera::CCamera(){
	
	cPos.x = 0;
	cPos.y = 0;
	cPos.z = 0;

	cView.x = 0;
	cView.y = 0;
	cView.z = 0;

	cUp.x = 0;
	cUp.y = 0;
	cUp.z = 0;

}

CCamera::CCamera(CVector camera_pos,CVector camera_view ,CVector camera_up){
		
	cPos.x =	camera_pos.x;
	cPos.y =	camera_pos.y;
	cPos.z =	camera_pos.z;

	cView.x =  camera_view.x;
	cView.y =  camera_view.y;
	cView.z =  camera_view.z;

	cUp.x = camera_up.x;
	cUp.y = camera_up.y;
	cUp.z = camera_up.z;
	
	cSpeed = 0.5;
	rSpeed = 0.1;

}

CCamera::~CCamera(){

}

void CCamera::SetPos(CVector camera_pos) {

	cPos.x =	camera_pos.x;
	cPos.y =	camera_pos.y;
	cPos.z =	camera_pos.z;


}

void CCamera::Move(float dir) {

	CVector vDir;

	vDir = cView - cPos;
	
	cPos.x  = cPos.x  + vDir.x * (dir * cSpeed);
	cPos.z  = cPos.z  + vDir.z * (dir * cSpeed);
	cView.x = cView.x + vDir.x * (dir * cSpeed);
	cView.z = cView.z + vDir.z * (dir * cSpeed);

}

void CCamera::rotate(float droot) {

	CVector vDir = cView - cPos;
	
	cView.z = (float)(cPos.z + sin(rSpeed*droot )*vDir.x + cos(rSpeed*droot )*vDir.z);   
	cView.x = (float)(cPos.x + cos(rSpeed*droot )*vDir.x - sin(rSpeed*droot )*vDir.z);

}

void CCamera::rotateUp(float droot) {
	
	cView.y = cView.y + rSpeed*3*droot;



}

void CCamera::StrafeUp(float droot) {
	
	cPos.y = cPos.y + cSpeed*3*droot;
	cView.y = cPos.y;

}

CVector CCamera::getPos() {
	
	CVector v;

		v.x = cPos.x;
		v.y = cPos.y;
		v.z = cPos.z;

	return v;
}

CVector CCamera::getView(){
	
	CVector v;

		v.x = cView.x;
		v.y = cView.y;
		v.z = cView.z;

	return v;
}


CVector CCamera::getUp(){
	
	CVector v;
		
		v.x = cUp.x;
		v.y = cUp.y;
		v.z = cUp.z;

	return v;
}

void lookAtView(float eyex, float eyey, float eyez,    float centerx, float centery, float centerz,    float  upx, float  upy, float  upz)
  {
		// centerx es el punto donde la camara apunta
		// esta parte hace referencia al vector f o matris f del doc
		
		float vfnx = centerx - eyex; // Se calcula el vector del "eye"
		float vfny = centery - eyey; 
		float vfnz = centerz - eyez;
		
		// normalizar el vector posición  , para tener un vector ortogonal
		float len = sqrt(vfnx * vfnx + vfny * vfny + vfnz * vfnz); // Se normaliza 
		
		vfnx = vfnx / len;     // Se encuentra el vector "f"
		vfny = vfny / len;
		vfnz = vfnz / len;
		
		// Productos Vectoriales , producto cruz
		
		float vlx = vfny * upz - vfnz * upy;     // se calcula el vector "l"
		float vly = vfnz * upx - vfnx * upz;
		float vlz = vfnx * upy - vfny * upx;
	
		float vux = vly * vfnz - vlz * vfny;	 // Se calcula el nuevo vector "u" (up)
		float vuy = vlz * vfnx - vlx * vfnz;
		float vuz = vlx * vfny - vly * vfnx;
		
		// Matrix 
		float mat[16] = {
			vlx, vux, -vfnx, 0,
			vly, vuy, -vfny, 0,
			vlz, vuz, -vfnz, 0,
			0, 0, 0, 1
		};
		
		// Aplica la matriz y la traslada a eyepoint
		glMultMatrixf(mat);		// multiplica la matriz mat * la matriz MODELVIEW
		
		glTranslatef(-eyex, -eyey, -eyez);	// invierte la viste natural de la camara
	}
	

void CCamera::Update() {
	
	glLoadIdentity();
	
	lookAtView(cPos.x,cPos.y,cPos.z,cView.x,cView.y,cView.z,cUp.x,cUp.y,cUp.z);
	//gluLookAt(cPos.x,cPos.y,cPos.z,cView.x,cView.y,cView.z,cUp.x,cUp.y,cUp.z);
	
	glRotatef(angulo_y,0.0,0.1,0.0);
	glRotatef(angulo_x,1.0,0.0,0.0);
	//glTranslatef(translate_x,translate_y,translate_z);

}

void CCamera::setSpeed(float speed) {

	cSpeed = speed;
}



// -----------------------------------------------------------------------------------------------------------------------------
//								MAIN MAIN MAIN MAIN
// -----------------------------------------------------------------------------------------------------------------------------

// CLASE CAMARA 
// Utilizamos la funcion del paquete glu gluLookAt(...);
// Tiene como parametros de iniciación 3 parametros tipo CVector, una clase que definimos nosotros
// y que solo da las coordenadas de un punto en el espacio, así como la normal de dicho punto.
// Cada parametro es: CVector 1 -> Posicion de la camara, CVector 2 -> Hacia donde mira la camara,
// CVector 3 -> Indica donde está el "arriba" para la camara.


CCamera camara(CVector(0, 2,10),CVector(0,2,0),CVector(0.0,1.0,0.0)); 

float rotar = 0;

// Con esta funcion dibujamos un curioso cubo gigante a base de lineas
// que crearán un efecto de entorno 3d y nos servirá de referencia mientras nos movemos.

void Draw3dCubeSpace() {  
							
	int max_lines = 100;
	int i = -max_lines ;
	
	glBegin(GL_LINES);
		
		for (i=-max_lines ; i < max_lines ;i++) {
			
			// suelo 

			glColor3f(1,0,0);
				glVertex3f(-max_lines ,0,i);
				glVertex3f(max_lines ,0,i);
	
			glColor3f(0,1,0);
				glVertex3f(i,0,max_lines );
				glVertex3f(i,0,-max_lines );

			// techo

			glColor3f(1,0,0);
				glVertex3f(-max_lines ,max_lines,i);
				glVertex3f(max_lines ,max_lines,i);
	
			glColor3f(0,1,0);
				glVertex3f(i,0,max_lines );
				glVertex3f(i,0,-max_lines );

			//paredes
	
			glColor3f(0,0,1);
				glVertex3f(i,0,-max_lines );
				glVertex3f(i,max_lines ,-max_lines );
				
				glVertex3f(-max_lines,0,i);
				glVertex3f(-max_lines,max_lines,i);
			
				glVertex3f(+max_lines,0,i);
				glVertex3f(+max_lines,max_lines,i);
			glColor3f(1,0,1);
				glVertex3f(i,0,max_lines );
				glVertex3f(i,max_lines ,max_lines );
	
				i = i+4;  // Contra mas sumes mas grandes serán los cuadrados.
		}
		
	glEnd();
	
	glColor3f(0,0.5,0);

}

// Dibuja un pequeño cubo en el centro que nos servirá como referencia. Girará y será un ejemplo
// de utilización de la pila de matrices.

void Draw3dCube() {
	
	CVector v;
	CVector vNorm1(-1, 1, 1);
	CVector vNorm2(-1, -1, 1);
	CVector vNorm3(1, -1, 1);

	glColor3f(0.0f,1.0f,0.0f);


 glBegin(GL_QUADS);
      // front
      glNormal3f(1, 0, 0); 
      glColor3f(1, 0,0 );
      glVertex3f(-1, 1, 1);
      glVertex3f(-1, -1, 1);
      glVertex3f(1, -1, 1);
      glVertex3f(1, 1, 1);

      // back
      glNormal3f(0, 0, -1);
      glColor3f(0, 1, 0);
      glVertex3f(-1, 1, -1);
      glVertex3f(1, 1, -1);
      glVertex3f(1, -1, -1);
      glVertex3f(-1, -1, -1);

      // top
      glNormal3f(0, 1, 0);
      glColor3f(0, 0, 1);
      glVertex3f(-1, 1, -1);
      glVertex3f(-1, 1, 1);
      glVertex3f(1, 1, 1);
      glVertex3f(1, 1, -1);

      // bottom
      glNormal3f(0, -1, 0);
      glColor3f(1, 1, 0);
      glVertex3f(-1, -1, -1);
      glVertex3f(1, -1, -1);
      glVertex3f(1, -1, 1);
      glVertex3f(-1, -1, 1);

      // left
      glNormal3f(-1, 0, 0);
      glColor3f(0, 1, 1);
      glVertex3f(-1, 1, -1);
      glVertex3f(-1, -1, -1);
      glVertex3f(-1, -1, 1);
      glVertex3f(-1, 1, 1);

      // right
      glNormal3f(1, 0, 0);
      glColor3f(1, 0, 1);
      glVertex3f(1, 1, 1);
      glVertex3f(1, -1, 1);
      glVertex3f(1, -1, -1);
      glVertex3f(1, 1, -1);
   glEnd();
	

}

void initopengl() {
	
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);	
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	glClearColor(0.0f,0.0f,0.0f,0.0f);
	
	
	glFrontFace(GL_CCW);

}



static void render(void) {
	

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	rotar++;
	
	//Comenzamos el juego de la pila de matrices. 
	// glPushMatrix() hace que una nueva matriz se coloque en el primer puesto de la pila, 
	// todo lo que hagamos dentro de esta matriz no se reflejará en la matriz inferior.  

	glPushMatrix();        
		camara.Update();  // Actualiza la posicion de la camara a partir de los valores del objecto camara.
		Draw3dCubeSpace();  // dibuja el cubo.
		
		glPushMatrix();        // Nueva Matriz lo que hace aquí no se refleja en la de arriba pero si en las de abajo.
			glTranslatef(0,2,0);   // sube 2 posiciones todo lo que se dibuje a partir de ahora
			glScalef(2,2,2);    // escala  
			glRotatef(rotar,1,0,0); // Rota todo con el valor indicado por rotar, como se va actualizando girará sin final.
									// sobre el eje indicado (a 1). En este caso es el eje Y (x = 0,y = 1, z = 0);
			Draw3dCube();   
		glPopMatrix();

	glPopMatrix();
	


	glutSwapBuffers();  // intercambia los buffers para la animación
	glFlush();          // ejecuta todas las funciones gl que no se han hecho aun.

		
}

// La funcion idle es la que se ejecuta de forma continua para glut. Se suele utilizar para actualizar
// datos y cosas así. En este caso  solo llama a la funcion render. 

static void idle(void) {  

	render();
}

// Tipica funcion para el control de la piramide de visualización. 

void reshape(int w, int h) {


		if (h == 0) {
			h = 1;
	}

		glViewport(0,0,(GLsizei)w,(GLsizei)h);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();	
		
			gluPerspective(45.0f,((GLsizei)w/(GLsizei)h), 0.1, 1000.0);
			
		glMatrixMode (GL_MODELVIEW);
		glLoadIdentity ();
		

}

// Lee el teclado de teclado. 

void  specialfunc(int key, int x, int y) {
	
	switch(key) {
		case GLUT_KEY_UP : 
			camara.Move(1);  // MOVE hace que se mueva la camara en la dirección indicada por su segundo parametro (hacia donde mira)
							 // el valor 1 (positivo) indica que es para el frente, - 1 (negativo) indica para atrás.
			render();
			break;
		case GLUT_KEY_DOWN :
			camara.Move(-1);
			render();
			break;
		case GLUT_KEY_PAGE_UP:
			camara.rotateUp(1); // RotateUp es equivalente a move pero para mirar arriba o abajo, negativo hacia abajo y positivo hacia arriba
			render();
			break;
		case GLUT_KEY_PAGE_DOWN:
			camara.rotateUp(-1); 
			render();
			break;
		case GLUT_KEY_LEFT:
			camara.rotate(-1); // Rotate es equivalente a move pero con la rotación, negativo a la izquierda y positivo a la derecha
			render();
			break;
		case GLUT_KEY_RIGHT: 
			camara.rotate(1);
			render();
			break;
		case GLUT_KEY_F1: 
			render();
			break;
		case GLUT_KEY_F2:
			camara.StrafeUp(1);  // Para ir hacia arriba (positivo) o hacia abajo (negativo)
			render();
			break;
		case GLUT_KEY_F3:
			camara.StrafeUp(-1);
			render();
			break;
		default :
			cout << endl << "nada" <<endl ;
	 }
	
}
void keyboard (unsigned char key, int x, int y) {
    switch (key) {
        // rotar en x en sentido  horario
        case 'w':
        	camara.rotateUp(1); // RotateUp es equivalente a move pero para mirar arriba o abajo, negativo hacia abajo y positivo hacia arriba
			render();
            break;
        // rotar en x en sentido contrario
        case 's':
            camara.rotateUp(-1); 
			render();
            break;
        // rotar en y en sentido horario
        case 'a':
        	//camara.rotate(-1); // Rotate es equivalente a move pero con la rotación, negativo a la izquierda y positivo a la derecha
			//render();
			
			angulo_y = angulo_y + 1.0;
            glutPostRedisplay();
            break;
        // rotar en y en sentido contrario
        case 'd':
            //camara.rotate(1);
			//render();
			
			angulo_y = angulo_y - 1.0;
            glutPostRedisplay();
            break;
            
		case 'q':			
			angulo_x = angulo_x + 1.0;
            glutPostRedisplay();
            break;
        // rotar en y en sentido contrario
        case 'e':
			angulo_x = angulo_x - 1.0;
            glutPostRedisplay();
            break;   
			     	
        // exit on esc
        case 'm':
            exit(0);
            break;
        default:
            break;
    }
}





int main(int argc, char* argv[])
{

	// Estas funciones inician glut. Indicamos que es doble buffer,
	// el tamaño, la posicion inicial y el nombre de la ventana. 

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE );
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Tutorial 0 - Espacio de trabajo 3D");

	glutShowWindow();
	
	initopengl();
	
	// Estas funciones son las que se repiten continuamente y serán las que se encarguen
	// de tomar datos, visualizar...

	glutSpecialFunc(specialfunc);  
	glutKeyboardFunc(keyboard);	     
	glutDisplayFunc(render);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	
	glutMainLoop();  // que no pare el circo, bucle infinito hasta que se termine la aplicación 
					 // que llama a las funciones anteriores.



	return 0;
}
