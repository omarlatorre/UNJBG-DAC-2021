#include <iostream>
#include<GL/freeglut.h>
#include<sstream>
#include <time.h>
#include <stdlib.h>

#define VK_W 0x57
#define VK_S 0x53
#define VK_1 0x31
#define VK_2 0x32
#define o 10

int width = 1200;
int height = 800;
float interval = 1000 / 60;
char sc[100];
int puntuacionmax=10;
float incrementspeed=0.2;

int n=1;
int nn=1;
int a;
int aa;

int scoreLeft = 0;
int scoreRight = 0;
int rebote=0;
int nrebote=2;

int paddleWidth = 10;
int paddleHeight = 100;
int paddleSpeed = 5;

float paddleLeftX = 10;
float paddleLeftY = height / 2 - paddleHeight / 2;
float paddleRightX = width - paddleWidth - 10;
float paddleRightY = height / 2 - paddleHeight / 2;

float ballX[o];
float ballY[o];
float ballDirectionX[o];
float ballDirectionY[o];
float ballSize = 10;
float ballSpeed[o];

void inibolas(void){
	for(int i=0;i<o;i++){
		ballX[i] = width / 2;
		ballY[i] = height / 2;
		ballDirectionX[i] = -1;
		ballDirectionY[i]= 0;
		ballSpeed[i] = 5;
	}
}

void DrawScore(int x, int y, std::string text)
{
	glRasterPos2f(x, y);
	glutBitmapString(GLUT_BITMAP_9_BY_15, (unsigned char*)text.c_str());
}

std::string ToString(int x)
{
	std::stringstream ss;
	ss << x;
	return ss.str();
}

void DrawRect(float x, float y, int width, int height)
{
	
	glBegin(GL_QUADS);
	glVertex2f(x, y);
	glVertex2f(x + width, y);
	glVertex2f(x + width, y + height);
	glVertex2f(x, y + height);
	glEnd();
}

void Draw()
{
	glClearColor(0, 0, 0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	DrawRect(paddleLeftX, paddleLeftY, paddleWidth, paddleHeight);
	DrawRect(paddleRightX, paddleRightY, paddleWidth, paddleHeight);

	if(rebote%nrebote==0){
		n=rebote/nrebote;
		n++;
	}
	for(a=0;a<n;a++){
			DrawRect(ballX[a], ballY[a], ballSize, ballSize);
	}

	DrawScore(width / 2 - 10, height - 50, ToString(scoreLeft) + " : " + ToString(scoreRight));
	DrawScore(width/2 + 500 , height-30 , "Rebotes " + ToString(rebote));

	if (scoreLeft || scoreRight >= puntuacionmax){
		
		if(scoreLeft >= puntuacionmax){
			ballSpeed[a]=0;
			glColor3f(0.7, 0.7, 1.3);
			glRasterPos2i(200,height/2);        
			glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,(unsigned char*)sc );
			sprintf(sc,"1. Jugar de nuevo \n2. Cerrar juego"); 
			glRasterPos2i(width-400, height/2); 
			glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,(unsigned char*)sc );
			sprintf(sc,"Jugador 1 gana");
			
			
		}
		if(scoreRight >= puntuacionmax){
			ballSpeed[a]=0;
			glColor3f(0.7, 0.7, 1.3);
			glRasterPos2i(200,height/2);        
			glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,(unsigned char*)sc );
			sprintf(sc,"Jugador 2 gana"); 
			glRasterPos2i(width-400, height/2); 
			glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,(unsigned char*)sc );
			sprintf(sc,"1. Jugar de nuevo \n2. Cerrar juego");
		}		
		
	}
	
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(612 , 740);
    glVertex2f(611 , 740);
    glVertex2f(611 , 720);
    glVertex2f(612 , 720);
    glEnd();
    
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(612 , 700);
    glVertex2f(611 , 700);
    glVertex2f(611 , 680);
    glVertex2f(612 , 680);
    glEnd();
    
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(612 , 660);
    glVertex2f(611 , 660);
    glVertex2f(611 , 640);
    glVertex2f(612 , 640);
    glEnd();
    
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(612 , 620);
    glVertex2f(611 , 620);
    glVertex2f(611 , 600);
    glVertex2f(612 , 600);
    glEnd();
    
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(612 , 580);
    glVertex2f(611 , 580);
    glVertex2f(611 , 560);
    glVertex2f(612 , 560);
    glEnd();
    
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(612 , 540);
    glVertex2f(611 , 540);
    glVertex2f(611 , 520);
    glVertex2f(612 , 520);
    glEnd();
    
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(612 , 500);
    glVertex2f(611 , 500);
    glVertex2f(611 , 480);
    glVertex2f(612 , 480);
    glEnd();
	
	glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(612 , 460);
    glVertex2f(611 , 460);
    glVertex2f(611 , 440);
    glVertex2f(612 , 440);
    glEnd();
    
	glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(612 , 420);
    glVertex2f(611 , 420);
    glVertex2f(611 , 400);
    glVertex2f(612 , 400);
    glEnd();
    
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(612 , 380);
    glVertex2f(611 , 380);
    glVertex2f(611 , 360);
    glVertex2f(612 , 360);
    glEnd();
	
	glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(612 , 340);
    glVertex2f(611 , 340);
    glVertex2f(611 , 320);
    glVertex2f(612 , 320);
    glEnd();
    
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(612 , 300);
    glVertex2f(611 , 300);
    glVertex2f(611 , 280);
    glVertex2f(612 , 280);
    glEnd();
    
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(612 , 260);
    glVertex2f(611 , 260);
    glVertex2f(611 , 240);
    glVertex2f(612 , 240);
    glEnd();
    
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(612 , 220);
    glVertex2f(611 , 220);
    glVertex2f(611 , 200);
    glVertex2f(612 , 200);
    glEnd();
    
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(612 , 180);
    glVertex2f(611 , 180);
    glVertex2f(611 , 160);
    glVertex2f(612 , 160);
    glEnd();
    
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(612 , 140);
    glVertex2f(611 , 140);
    glVertex2f(611 , 120);
    glVertex2f(612 , 120);
    glEnd();
    
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(612 , 100);
    glVertex2f(611 , 100);
    glVertex2f(611 , 80);
    glVertex2f(612 , 80);
    glEnd();
    
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(612 , 60);
    glVertex2f(611 , 60);
    glVertex2f(611 , 40);
    glVertex2f(612 , 40);
    glEnd();
	
	glutSwapBuffers();
	
}

void RandomDirection(int e)
{
	int num1, num2;
    srand(time(NULL));
    num1 =  + rand() % (2 - 0);
    num2 =  + rand() % (2 - 0);
   
	if(num1 % 2 == 0)
		ballDirectionX[e] = -1;
	else
		ballDirectionX[e] = 1;
		
	if(num2 % 2 == 0)
		ballDirectionY[e] = -1;
	else
		ballDirectionY[e] = 1;
}

void ResetScore()
{
	scoreRight=0;
	scoreLeft=0;
}

void ResetGame(int e)
{
	ballX[e] = width/2;
	ballY[e] = height/2;
	ballSpeed[e]=5;
	rebote=0;
	RandomDirection(e);
}


void Keyboard(int e)
{
	if (GetAsyncKeyState(VK_UP))
		paddleRightY += paddleSpeed;
	else if (GetAsyncKeyState(VK_DOWN))
		paddleRightY -= paddleSpeed;
	if (GetAsyncKeyState(VK_W))
		paddleLeftY += paddleSpeed;
	else if (GetAsyncKeyState(VK_S))
		paddleLeftY -= paddleSpeed;
	if (GetAsyncKeyState(VK_1)){
		ResetScore();
		ResetGame(e);
	}
	else if (GetAsyncKeyState(VK_2)){
		exit(0);
	}
}


void UpdateBall(int e)
{
	ballX[e] += ballDirectionX[e] * ballSpeed[e];
	ballY[e] += ballDirectionY[e] * ballSpeed[e];
	if (ballX[e] < 0)
	{
		scoreRight++;
		ResetGame(e);
	}

	if (ballX[e] > width)
	{
		scoreLeft++;
		ResetGame(e);
	}

	if (ballX[e] < paddleLeftX + paddleWidth && ballX[e] > paddleLeftX - ballSize && ballY[e] < paddleLeftY + paddleHeight
		&& ballY[e] > paddleLeftY - ballSize)
	{
		ballDirectionX[e] *= -1;
		float offset = (ballY[e] - paddleLeftY) / paddleHeight - 0.5;
		ballDirectionY[e] = offset;
		ballSpeed[e]=ballSpeed[e]+incrementspeed;
		rebote++;
		
	}

	if (ballX[e] > paddleRightX - ballSize && ballX[e] < paddleRightX + paddleWidth && ballY[e] < paddleRightY + paddleHeight
		&& ballY[e] > paddleRightY - ballSize)
	{
		ballDirectionX[e] *= -1;
		float offset = (ballY[e] - paddleRightY) / paddleHeight - 0.5;
		ballDirectionY[e] = offset;
		ballSpeed[e]=ballSpeed[e]+incrementspeed;
		rebote++;
	}

	if (ballY[e] < 0)
	{
		ballDirectionY[e] *= -1;

	}

	if (ballY[e] > height - ballSize)
	{
		ballDirectionY[e] *= -1;

	}
}

void Update(int value)
{
	Keyboard(0);
	if(rebote%nrebote==0){
		nn=rebote/nrebote;
		nn++;
	}	
	for(aa=0;aa<nn;aa++){
			UpdateBall(aa);
	}
	glutTimerFunc(interval, Update, 0);
	glutPostRedisplay();
}

void Init()
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, 0, height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char** argv)
{
	inibolas();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(200, 100);
	glutCreateWindow("Elaboracion Ping Pong");

	glutDisplayFunc(Draw);
	glutTimerFunc(interval, Update, 0);
	Init();

	glutMainLoop();

	return 0;
}
