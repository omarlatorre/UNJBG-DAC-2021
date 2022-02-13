#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#define NOMBRE_ARCHIVO "lenguajes.csv"

using namespace std;

string lenguaje;
string porcentaje,aux, porcentajeS[50],lenguajeS[50];
float  porcentajeF[50];
float angulo[50],sum=0,sum2=0,r1,r2,r3,q=0, posletra;
int contador=0;char * my;

void renderBitmapString(float x, float y, void *font,const char *string)
{
    const char *c;
    glRasterPos2f(x, y);
    for (c=string; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15,*c);
    }
} 

void init()
{
    glClearColor(1,1,1,1);
    gluOrtho2D(-100,100,-100,100);
}


void Circle()
{
    float theta, x = 0, y = 0, r = 70, ax, ay, sumG=1,Gan=0, grado; 
		
    
    
    glClear(GL_COLOR_BUFFER_BIT);	
    glBegin(GL_POLYGON);
    glVertex2f(0, 0);
    
    for(int j=0; j<contador; j++){
    	grado=angulo[j];
    	sumG=sumG+grado;
    	
    	r1=(float)(1+rand()%10)/10;
    	r2=(float)(1+rand()%10)/10;
    	r3=(float)(1+rand()%10)/10;
    	
	        glColor3f(r1,r2,r3);
		for(float i = Gan; i<sumG; i++)
	    {
	            theta = i * 3.1416 / 180;
	            ax=x+r*cos(theta);
	            ay=y+r*sin(theta);
	            glVertex2f(ax,ay);
		}
	    Gan=sumG;
	}
    glEnd();
    glFlush();
    
    for(int j=0; j<contador; j++){
    	grado=angulo[j];
    	sumG=sumG+grado;
		posletra=(sumG+Gan)/2;
	        
	        theta = posletra * 3.1416 / 180;
	        ax=x+73*cos(theta);
	        ay=y+73*sin(theta);
	        lenguaje=lenguajeS[j];
 			const char *str = lenguaje.c_str();

    			glColor3d(0.0, 0.0, 0.0);
				renderBitmapString(ax,ay,(void *)GLUT_BITMAP_9_BY_15,str);
    			glutSwapBuffers();
    			
	    Gan=sumG;
}
}

void csv(){
    ifstream archivo(NOMBRE_ARCHIVO);
    string linea;
    char delimitador = ';';
    // Leemos la primer línea para descartarla, pues es el encabezado
    getline(archivo, linea);
    // Leemos todas las líneas
    while (getline(archivo, linea)){
        stringstream stream(linea); // Convertir la cadena a un stream
        // Extraer todos los valores de esa fila
        getline(stream, lenguaje, delimitador);
        getline(stream, porcentaje, delimitador);
        lenguajeS[contador]=lenguaje;
        cout<<lenguaje<<endl;
    
        cout<<endl;
        porcentajeS[contador]=porcentaje;
        contador++;
	}
}


void ingresar_arreglo() 
{  
    for (int i=0;i<15;i++)
	{
    	aux=porcentajeS[i];
        porcentajeF[i] = stof(aux);
    	sum=sum+porcentajeF[i];
	}
}

void form()
{
    for (int i=0;i<contador;i++)
	{
        angulo[i]=(porcentajeF[i]*360)/sum;
    }
}


int main (int argc, char ** argv){
	csv();
	ingresar_arreglo();
    form();
    glutInit(&argc,argv);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(800,800);
    glutCreateWindow("Gráfica circular");
    init();
    
    glutDisplayFunc(Circle);
    
    glutMainLoop();

    return 0;
}
