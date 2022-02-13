//Las bibliotecas a utilizar
#include<GL/glut.h>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<iostream>

using namespace std;

int ancho = 800, alto =600;
float tx = 1, ty = 0 ;
float tam = 0;
float Sx = 0.9999, Sy = 0.9999;
int opct = 0,opcta = 0,opcts = 0,opctd = 0,opctw = 0;
int opcr = 0, opcr1 = 0, opcr2 = 0;
int opcs = 0, opcs1 = 0, opcs2 = 0;
float angulo = -0.05;

//Figura poligonal mariposa
float MatrixP[107][3] = {
	{143,69,1}, {124,138,1}, {163,182,1}, {186,272,1}, {267,267,1}, {208,347,1}, {248,435,1}, {338,458,1}, {389,360,1},
	{402,374,1},{414,360,1}, {466,459,1}, {555,435,1}, {595,347,1}, {538,267,1}, {619,272,1}, {641,182,1}, {680,138,1},
	{661,69,1}, {557,89,1},  {425,190,1}, {427,176,1}, {421,170,1}, {407,169,1}, {437,120,1}, {423,108,1}, {406,169,1},
	{393,170,1},{380,108,1}, {360,120,1}, {392,170,1}, {382,169,1}, {376,176,1}, {374,190,1}, {248,89,1},  {143,69,1},
	{146,130,1},{163,182,1}, {248,89,1},  {124,138,1}, {163,182,1}, {220,176,1}, {267,267,1}, {186,272,1}, {248,89,1},
	{374,190,1},{220,176,1}, {267,267,1}, {374,190,1}, {389,360,1}, {248,435,1}, {267,267,1}, {386,322,1}, {208,347,1},
	{255,386,1},{386,322,1}, {208,347,1}, {289,415,1}, {248,435,1}, {255,386,1}, {338,458,1}, {289,415,1}, {386,322,1},
	{389,360,1},{402,349,1}, {402,258,1}, {386,306,1}, {374,190,1}, {391,213,1}, {411,213,1}, {402,258,1}, {391,213,1},
	{411,213,1},{425,190,1}, {414,360,1}, {402,349,1}, {414,360,1}, {416,306,1}, {402,258,1}, {402,349,1}, {414,360,1},
	{517,415,1},{555,435,1}, {466,459,1}, {595,347,1}, {538,267,1}, {555,435,1}, {517,415,1}, {418,322,1}, {550,389,1},
	{595,347,1},{418,322,1}, {538,267,1}, {425,190,1}, {583,176,1}, {538,267,1}, {619,272,1}, {583,176,1}, {641,182,1},
	{583,176,1},{557,89,1},  {641,182,1}, {657,130,1}, {680,138,1}, {661,69,1},  {657,130,1}, {557,89,1}
};


void pintaPixel(double Cx1, double Cy1, double Cx2, double Cy2, int R, int G, int B) {
	glBegin(GL_LINES); //dibuja la linea en cada vertice que enviamos
	glPointSize(1);
	glColor3f(1.0f, 0.5f, 0.0f);
	glVertex2d(Cx1, Cy1);
	glVertex2d(Cx2, Cy2);
	glEnd();
	glFlush();
}
void dibujaPlano(float Mimatriz[107][3]) {

	for (int i = 0; i < 107-1; i++)
	{
		pintaPixel(Mimatriz[i][0], Mimatriz[i][1], Mimatriz[i + 1][0], Mimatriz[i + 1][1],
			0, 2, 8);
	}
}

void Traslacion(float Mimatriz[107][3]){
	float MatTras[3][3] = { 
	{ 1,0,tx },
	 { 0,1,ty },
	 {0,0,1} };
	 
	if(opcta ==1 && opctw == 1){
		tx = -0.75;ty = -0.75;
	} else { if(opcta == 1 && opcts==1){
		tx = -0.75;ty = 0.75;
	} else { if(opctd ==1 && opctw == 1){
		tx = 0.75;ty = -0.75;
	} else { if(opctd == 1 && opcts==1){
		tx = 0.75;ty = 0.75;
	} else { 
		if (opcta == 1){tx = -1;ty = 0;}
		if (opctd == 1){tx = 1;ty = 0;}
		if (opctw == 1){tx = 0;ty = -1;}
		if (opcts == 1){tx = 0;ty = 1;}
	}
	}}}
	
	float punto1 = Mimatriz[65][0];
	float punto2 = Mimatriz[65][1];

	for (int i = 0; i < 107; i++)
		{
			Mimatriz[i][0] = ((Mimatriz[i][0] * MatTras[0][0]) + (Mimatriz[i][1] * MatTras[0][1]) + MatTras[0][2]);
			Mimatriz[i][1] = ((Mimatriz[i][0] * MatTras[1][0]) + (Mimatriz[i][1] * MatTras[1][1]) + MatTras[1][2]);	
		}
	dibujaPlano(Mimatriz);
}
void Escalacion(float Mimatriz[107][3], int a){
	
	float Xc = Mimatriz[65][0];
	float Yc = Mimatriz[65][1];
	
	float MatEsc[3][3] = { 
	{Sx,0,Xc * (1 - Sx)},
	{0,Sy,Yc*(1-Sy)},
	{0,0,1} };
	if(a == 1){
		Sx = 1.0013;
		Sy = 1.0013;	
	}
	if(a == 0){
		Sx = 0.995;
		Sy = 0.995;
	} 
	for (int i = 0; i < 107; i++)
		{
			Mimatriz[i][0] = ((Mimatriz[i][0] * MatEsc[0][0]) + (Mimatriz[i][1] * MatEsc[0][1]) + MatEsc[0][2]);
			Mimatriz[i][1] = ((Mimatriz[i][0] * MatEsc[1][0]) + (Mimatriz[i][1] * MatEsc[1][1]) + MatEsc[1][2]);	
		}
	dibujaPlano(Mimatriz);
}
void Rotacion(float Mimatriz[107][3],int a){
	
	float Xc = Mimatriz[65][0];
	float Yc = Mimatriz[65][1];
	if(a==1) angulo=-0.05;
	if(a==2) angulo=0.05;
	
	float MatRot[3][3] = { 
	{cos(angulo), -sin(angulo),-Xc*(cos(angulo))+ Yc * sin(angulo) + Xc},
	{sin(angulo), cos(angulo),-Yc*(cos(angulo)) - Xc*(sin(angulo)) + Yc},
	{0 , 0 , 1}};

	for (int i = 0; i < 107; i++)
		{
			Mimatriz[i][0] = ((Mimatriz[i][0] * MatRot[0][0]) + (Mimatriz[i][1] * MatRot[0][1]) + MatRot[0][2]);
			Mimatriz[i][1] = ((Mimatriz[i][0] * MatRot[1][0]) + (Mimatriz[i][1] * MatRot[1][1]) + MatRot[1][2]);	
		}
	dibujaPlano(Mimatriz);
}

void teclado(unsigned char tecla, int x, int y) { //enviamos como parametro la letra que deseemos 
	switch (tecla)
	{
		case 'a':
			if (opcta == 0){
				opct = 1;
				opcta = 1; opctd = 0;
			}else{
				opcta = opct = 0;
			}
			glutPostRedisplay();
			break;
		case 'd':
			if (opctd == 0){
				opct = 1;
				opctd = 1; opcta = 0;
			}else{
				opctd = opct = 0;
			}
			glutPostRedisplay();
			break;
		case 'w':
			if (opctw == 0){
				opct = 1;
				opctw = 1; opcts = 0;
			}else{
				opctw = opct = 0;
			}
			glutPostRedisplay();
			break;
		case 's':
			if (opcts == 0){
				opct = 1;
				opcts = 1; opctw = 0;
			}else{
				opcts = opct = 0;
			}
			glutPostRedisplay();
			break;
		case 'q':
				opcs2 = 0;
			if (opcs1 == 0){
				opcs1 = 1;
				opcs = 0;
			}else{
				opcs1 = opcs = 0;
			}
			glutPostRedisplay();
			break;
		case 'e':
				opcs1 = 0;
			if (opcs2 == 0){
				opcs2 = 1;
				opcs = 1;
			}else{
				opcs2 = opcs = 0;
			}
			glutPostRedisplay();
			break;
		case 'r':
				opcr2 = 0;
			if (opcr1 == 0){
				opcr1 = 1;
				opcr = 1;
			}else{
				opcr1 =	opcr  = 0;
			}
			glutPostRedisplay();
			break;
		case 'f':
				opcr1 = 0;
			if (opcr2 == 0){
				opcr2 = 1;
				opcr = 2;
			}else{
				opcr2 =	opcr = 0;
			}
			glutPostRedisplay();
			break;
		}
	}

void display() {
	
	glClear(GL_COLOR_BUFFER_BIT); //limpia la pantalla
	if (opcr + opcs + opct == 0) {
		dibujaPlano(MatrixP);
	}
	if (opct  == 1) {
		Traslacion(MatrixP);
	}
	if (opcs  == 1 || opcs1 == 1) {
		Escalacion(MatrixP, opcs);
	}
	if (opcr1 == 1 || opcr2 == 1 ) {
		Rotacion(MatrixP,opcr);
	}
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
	
}
int main(int arg, char* argv[]) {
	//INICIALIZAR LA LIBRERIA OPENGL CON SUS PAARAMETROS
	glutInit(&arg, argv);
	//CONFIGURAR EL MODO DE PANTALLA, ENVIANDO 2 PARAMETROS LOS COLORES Y LOS BUFFER A UTILIZAR
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	//CONFIGURAMOS EL ANCHO Y ALTO DE LA VENTANA
	glutInitWindowSize(ancho, alto);
	//CONFIGURAMOS LA POSICION DE LA VENTANA
	glutInitWindowPosition(75, 50);
	//CREAR VENTANA Y TITULO
	glutCreateWindow("TRANSFORMADAS GEOMETRICAS 2D");
	glClearColor(0,0,0,1);
	gluOrtho2D(0, ancho, alto, 0);
	//llamamos la funcion dps
	glutDisplayFunc(display);
	//funcion para hacer uso del teclado
	glutKeyboardFunc(teclado);
	//FUNCION QUE REPETIR EL CICLO	
	glutMainLoop();
	//return 0;
}

