#include <stdlib.h>
#include <GL\glut.h>
#include <math.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <time.h>
#define ARCHIVO "archivo.csv"

using namespace std;
const GLdouble Pi = 3.1415926536;
string nombre, porciento, porcentaje_E[50], nombre_E[50];
float porcentaje_S[50], Grados[50], P_total=0, red, green, blue, alpha, color[50], color1[50], color2[50], color3[50],ly=0;
int contar_N=0, l=0;

void leyenda();

void lectura_A(){
	ifstream documento(ARCHIVO);
    string fila;
    char separador = ',';
    // leemos el encabezado
    getline(documento, fila);
    // leemos los siguientes filas
    while(getline(documento, fila))
    {
        stringstream stream(fila); // Convertir la cadena a un stream
        // Extraer todos los porcentajes de esa fila
        getline(stream, nombre, separador);
        getline(stream, porciento);
        nombre_E[contar_N]=nombre;
        porcentaje_E[contar_N]=porciento;
        contar_N++;
        cout<<contar_N<<" "<<nombre<<" -> "<<porciento<<endl;
	}

	//comvertir string a float
	for(int i=0;i<contar_N;i++){
		istringstream(porcentaje_E[i])>>porcentaje_S[i];//convierte porcentaje de entrada(string) a porcentaje de salida(float)
		P_total=P_total+porcentaje_S[i]; //sumamos los pocentajes para obtener el total
	}

	//porciento convertir en Grados donde 100%=360°
	for(int i=0;i<contar_N;i++){
		Grados[i]=(porcentaje_S[i]*360)/P_total;
	}
}

void circulo(){
	float  x=0, y=0, r=70, G_final=91, G_inicial=90,x1=20,y1=20;
	srand(time(NULL));
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
	glColor3f (0.1f, 0.1f, 0.1f);
	glVertex2f(20,20);
	for(int j=0;j<contar_N;j++){
		//generamos los Colores aleatorios
		red=float(rand()%10)/10;
		green=float(rand()%10)/10;
		blue=float(rand()%10)/10;
		alpha=float(rand()%10)/10;
		glColor4f(red,green,blue,alpha);
		//Almacenamos los colores generados
		color[j]=red;
		color1[j]=green;
		color2[j]=blue;
		color3[j]=alpha;
		//igualamos a G_final los grados a dibujar
        G_final=G_final+Grados[j];
		for(float i=G_inicial;i<G_final; i++){
			glTranslatef(60,50,0);
			x =x1+ r*cos(i *Pi/180);
			y =y1+ r*sin(i *Pi/180);
			glVertex2f(x,y);
		}
	G_inicial=G_final;//el grado final va ser el nuevo inicio para el siguiente
	}
	glEnd();
	glFlush();
	leyenda();
}

void leyenda(){
	if(l<1){
	for(int j=0 ;j<=contar_N;j++){
		glPushMatrix();
		ly=ly+8;
		//utilizamos los colores almacenados
		red=color[j];
		green=color1[j];
		blue=color2[j];
		alpha=color3[j];
		glTranslatef(-95,90-ly,0);
		glColor4d(red,green,blue,alpha);
		//generamos los nombres en pantalla
		nombre=nombre_E[j];
		const char *str = nombre.c_str();
		glRasterPos2f(0, -5);
		for(const char *c=str; *c != '\0';c++){
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
		}
		glutSwapBuffers();
		glTranslatef(-3,-4,0);
		glutSolidCube(2);
	glPopMatrix();
	}
	ly=0;

	}
}

void init()
{
	glClearColor(1,1,1,1); //colores rgb
    glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-100, 100, -100, 100);

}

int main (int argc, char ** argv)
{	
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition (100, 10);
	glutInitWindowSize (750, 700);
	glutCreateWindow ("REPRESENTACION GRAFICA");

	init ();
	lectura_A();
    glutDisplayFunc(circulo);
	glutMainLoop ();

	return 0;
}

