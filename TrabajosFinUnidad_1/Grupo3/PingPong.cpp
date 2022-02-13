#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <math.h>

using namespace std;

// Tama�ano de la pantalla
int winSize = 500;
// Barras
int barPixelWidth = 25, barPixelHeight = 200;
float barHeight, barWidth, halfBarHeight, halfBarWidth;
float barSpeed = 20;
int moveLeftBar, moveRightBar;
float barXPos = .9;
// Bola
int ballEdgePixelSize = 20;
float ballEdgeSize, halfBallEdgeSize;
int R = 5;
int countR = 0;
int numBall = 0;
bool outBall = false;
float startBallSpeed = 2, ballSpeedQuotient = 1.1;
// Juego
double currentTime, lastTime, delay;
float replaceDelay = 1, winReplaceDelay = 2;
float digitHeight = 65, digitWidth = 40;
int maxGoal = 10;
int score1 = 0, score2 = 0;
bool playerWin = false;
float defaultZ = -2;

// Menu de navegaci�n
const int nav1Length = 2;
int nav1Pos = 0;

// Declaraci�n de funciones
void nav();
void dafaultInit();

// Tipo de dato Vector
class Vector{
	public:
		float x, y;
		
		void zero()
		{
			x = 0;
			y = 0;
		}
		
		void random()
		{
			x = 1;
			y = 1;
			
			srand((int) time(0));
			if(rand() % 2 == 0){
				x = -1;
			}
			if(rand() % 2 == 0){
				y = -1;
			}
		}
		
		void cpvec(Vector v){
			x = v.x;
			y = v.y;
		}
};

//Vector ballPosition, ballDirection, previousBallPosition;
Vector leftBarPosition, rightBarPosition;

class Ball{
	public:
		float ballSpeed, realBallMove;
		bool ballOut;
		Vector ballPosition, ballDirection, previousBallPosition;
};

Ball balls[0];

// Convierte los pixeles en unidades cuando se redimensiona la pantalla
float pixelToUnit(float pixel)
{
	return pixel / winSize;
}

// funcion de redimension
static void resize(int width, int height)
{
	const float ar = (float) width / (float) height;
	
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Estado inicial de la bola
void placeBall(Ball * ball)
{
	ball->ballPosition.zero();
	ball->ballDirection.random();
}

// Verifica si la pelota colisiona con la pantalla
void checkScreenCollision(Ball * ball)
{
	if(ball->ballPosition.y - halfBallEdgeSize <= -1 || ball->ballPosition.y + halfBallEdgeSize >= 1)
	{
		ball->ballDirection.y *= -1;
		
		if(ball->ballPosition.y < 0)
		{
			ball->ballPosition.y = -1 + halfBallEdgeSize;
		}
		else
		{
			ball->ballPosition.y = 1 - halfBallEdgeSize;
		}
	}
}

// Calcula la distancia en la que debera moverse la bola (Pit�goras)
float ballMoveDistance(Ball * ball)
{
	float xSquare = ball->ballDirection.x * ball->ballSpeed, ySquare = ball->ballDirection.y * ball->ballSpeed;
	
	xSquare *= xSquare;
	ySquare *= ySquare;
	
	return sqrt(xSquare + ySquare);
}

// Funci�n que crea una nueva bola e inicializan sus valores
void newBall()
{
	Ball iball;
	balls[numBall] = iball;
			
	balls[numBall].ballSpeed = startBallSpeed;
	balls[numBall].ballSpeed *= (1 / (float) winSize);
			
	placeBall(&balls[numBall]);
			
	balls[numBall].realBallMove = ballMoveDistance(&balls[numBall]);
			
	numBall++;
}

// Devuelve el valor absoluto de un n�mero
float absolute(float value)
{
	return sqrt(value * value);
}

// Calculamos la nueva direcci�n direcci�n de la bola al chocar
void computeNewBallDirection(float barPosY, Ball * ball)
{
	float ballToCenterDistance, yDirection;
	double alpha, alpha1, alpha2, alpha1tan;
	
	ballToCenterDistance = absolute(ball->ballPosition.y - barPosY);
	
	alpha = (ballToCenterDistance * 89) / halfBarHeight;
	alpha1tan = absolute(ball->ballDirection.y / ball->ballDirection.x);
	alpha1 = atan(alpha1tan) * 180 / 3.1416; //Convertimos radianos en grados
	alpha2 = alpha - alpha1;
	
	yDirection = tan(alpha2 * 3.1415 / 180) * absolute(ball->ballDirection.x);
	yDirection = 1 - absolute(yDirection);
	yDirection *= -1;
	
	if((ball->ballDirection.y < 0 && yDirection > 0) || (ball->ballDirection.y == 0 && ball->ballPosition.y < barPosY))
	{
		yDirection *= -1;
	}
	
	if(yDirection > 1)
	{
		yDirection = 1;
	}
	else if (yDirection < -1)
	{
		yDirection = -1;
	}
	
	ball->ballDirection.y = yDirection;
}

// Verifica que la bola choco con alguna de las barras de los jugadores
void checkBarCollision(Ball * ball)
{
	float upperCorner, downCorner;
	
	upperCorner = ball->ballPosition.y + halfBallEdgeSize;
	downCorner = ball->ballPosition.y - halfBallEdgeSize;
	
	float leftBarUpperCorner, leftBarDownCorner, rightBarUpperCorner, rightBarDownCorner;
	
	leftBarUpperCorner = leftBarPosition.y + halfBarHeight;
	leftBarDownCorner = leftBarPosition.y - halfBarHeight;
	
	rightBarUpperCorner = rightBarPosition.y + halfBarHeight;
	rightBarDownCorner = rightBarPosition.y - halfBarHeight;
	
	float leftBallEdge, rightBallEdge, leftBarEdge, rightBarEdge;
	
	leftBallEdge = ball->ballPosition.x - halfBallEdgeSize;
	rightBallEdge = ball->ballPosition.x + halfBallEdgeSize;
	
	leftBarEdge = leftBarPosition.x + halfBarWidth;
	rightBarEdge = rightBarPosition.x - halfBarWidth;
	
	bool collision = false;
	
	if(ball->ballPosition.x < 0)
	{
		if((ball->previousBallPosition.x - halfBallEdgeSize >= leftBarEdge) && (leftBallEdge <= leftBarEdge) && (upperCorner >= leftBarDownCorner) && (downCorner <= leftBarUpperCorner))
		{
			collision = true;
			ball->ballPosition.x = leftBarPosition.x + halfBarWidth + halfBallEdgeSize;
			computeNewBallDirection(leftBarPosition.y, ball);
		}
	}
	else
	{
		if((ball->previousBallPosition.x - halfBallEdgeSize <= rightBarEdge) && (rightBallEdge >= rightBarEdge) && (upperCorner >= rightBarDownCorner) && (downCorner <= rightBarUpperCorner))
		{
			collision = true;
			ball->ballPosition.x = rightBarPosition.x - halfBarWidth - halfBallEdgeSize;
			computeNewBallDirection(rightBarPosition.y, ball);
		}
	}
	
	// Si existe colision redirecciono la bola
	if(collision)
	{
		ball->ballDirection.x *= -1;
		ball->realBallMove *= ballSpeedQuotient;
		float currentBallMove = ballMoveDistance(ball);
		float moveQuotient = currentBallMove / ball->realBallMove;
		ball->ballSpeed /= moveQuotient;
		countR++;
		
		if(countR == R)
		{
			newBall();
			countR = 0;
		}
	}
}

// Verificar si la bola salio de la pantalla por el lado de los jugadores
void checkBallExit(Ball * ball)
{
	if(ball->ballPosition.x - halfBallEdgeSize > 1 || ball->ballPosition.x + halfBallEdgeSize < -1)
	{
		ball->ballOut = true;
		
		if(ball->ballPosition.x < 0)
		{
			score2++;
		}
		else
		{
			score1++;
		}
	}
}

// Sombrear cuadrado de score
void packBlack(float posX, float posY, float w1, float w2, float w3, float w4, float h1, float h2, float h3, float h4)
{
	glPushMatrix();
		glTranslated(posX, posY, defaultZ);
		glBegin(GL_QUADS);
			glColor3f(0, 0, 0);
			glVertex2f(-digitWidth + w1, -digitHeight + h1);
			glVertex2f(digitWidth + w2, -digitHeight + h2);
			glVertex2f(digitWidth + w3, digitHeight + h3);
			glVertex2f(-digitWidth + w4, digitHeight + h4);
		glEnd();
	glPopMatrix();
}

// Pintar de blanco el cuadrado de score
void packDigit(float posX, float posY, int n)
{	
	glPushMatrix();
		glTranslated(posX, posY, defaultZ);
		glBegin(GL_QUADS);
			glColor3f(1, 1, 1);
			glVertex2f(-digitWidth, -digitHeight);
			glVertex2f(digitWidth, -digitHeight);
			glVertex2f(digitWidth, digitHeight);
			glVertex2f(-digitWidth, digitHeight);
		glEnd();
	glPopMatrix();
	
	float border = digitWidth / 2;
	
	switch(n)
	{
		case 0:
			packBlack(posX, posY, border, -border, -border, border, border, border, -border, -border);
			break;
		case 1:
			packBlack(posX, posY, 0, -border, -border, 0, 0, 0, 0, 0);
			break;
		case 2:
			packBlack(posX, posY, border, 0, 0, border, border, border, -border * 3.75, -border * 3.75);
			packBlack(posX, posY, 0, -border, -border, 0, border * 3.75, border * 3.75, -border, -border);
			break;
		case 3:
			packBlack(posX, posY, 0, -border, -border, 0, border, border, -border * 3.75, -border * 3.75);
			packBlack(posX, posY, 0, -border, -border, 0, border * 3.75, border * 3.75, -border, -border);
			break;
		case 4:
			packBlack(posX, posY, border, -border, -border, border, border * 3.75, border * 3.75, 0, 0);
			packBlack(posX, posY, 0, -border, -border, 0, 0, 0, -border * 3.75, -border * 3.75);
			break;
		case 5:
			packBlack(posX, posY, border, 0, 0, border, border * 3.75, border * 3.75, -border, -border);
			packBlack(posX, posY, 0, -border, -border, 0, border, border, -border * 3.75, -border * 3.75);
			break;
		case 6:
			packBlack(posX, posY, border, 0, 0, border, border * 3.75, border * 3.75, -border, -border);
			packBlack(posX, posY, border, -border, -border, border, border, border, -border * 3.75, -border * 3.75);
			break;
		case 7:
			packBlack(posX, posY, 0, -border, -border, 0, 0, 0, -border, -border);
			break;
		case 8:
			packBlack(posX, posY, border, -border, -border, border, border * 3.75, border * 3.75, -border, -border);
			packBlack(posX, posY, border, -border, -border, border, border, border, -border * 3.75, -border * 3.75);
			break;
		case 9:
			packBlack(posX, posY, border, -border, -border, border, border * 3.75, border * 3.75, -border, -border);
			packBlack(posX, posY, 0, -border, -border, 0, border, border, -border * 3.75, -border * 3.75);
			break;
	}
}

// Escena del juego
void game()
{
	currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	
	if((rightBarPosition.y + halfBarHeight > 1 && moveRightBar == 1) || (rightBarPosition.y - halfBarHeight < -1 && moveRightBar == -1))
	{
		moveRightBar = 0;
	}
	
	if((leftBarPosition.y + halfBarHeight > 1 && moveLeftBar == 1) || (leftBarPosition.y - halfBarHeight < -1 && moveLeftBar == -1))
	{
		moveLeftBar = 0;
	}
	
	rightBarPosition.y += barSpeed * moveRightBar;
	leftBarPosition.y += barSpeed * moveLeftBar;
	
	for(int i = 0; i < numBall; i++)
	{
		if(!balls[i].ballOut)
		{
		
			checkScreenCollision(&balls[i]);
			checkBarCollision(&balls[i]);
				
			balls[i].previousBallPosition.cpvec(balls[i].ballPosition);
			
			balls[i].ballPosition.x += balls[i].ballSpeed * balls[i].ballDirection.x;
			balls[i].ballPosition.y += balls[i].ballSpeed * balls[i].ballDirection.y;
				
			checkBallExit(&balls[i]);
		}
		else
		{
			outBall = true;
			delay = currentTime + replaceDelay;
		}
	}
	
	if(outBall)
	{
		countR = 0;
		numBall = 0;
		
		if(score1 == maxGoal || score2 == maxGoal)
		{
			playerWin = true;
		}
		
		if(currentTime >= delay)
		{
			if(playerWin)
			{
				glutDisplayFunc(nav);
			}
			
			newBall();
			outBall = false;
		}
	}
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3d(0, 0, 1);
	
	float posX = .5, posY = .7;
	
	if(score1 == 10)
	{
		packDigit(-posX, posY, 1);
		packDigit(-posX + digitWidth * 3, posY, 0);
		packDigit(posX, posY, score2);
	}
	else if(score2 == 10)
	{
		packDigit(posX, posY, 1);
		packDigit(posX + digitWidth * 3, posY, 0);
		packDigit(-posX, posY, score1);
	}
	else
	{
		packDigit(-posX, posY, score1);
		packDigit(posX, posY, score2);
	}
	
	// Dibujar las bolas
	for(int i = 0; i < numBall; i++)
	{
		glPushMatrix();
			glTranslated(balls[i].ballPosition.x, balls[i].ballPosition.y, defaultZ);
			glBegin(GL_QUADS);
				glColor3f(1, 1, 1);
				glVertex2f(-halfBallEdgeSize, -halfBallEdgeSize);
				glVertex2f(halfBallEdgeSize, -halfBallEdgeSize);
				glVertex2f(halfBallEdgeSize, halfBallEdgeSize);
				glVertex2f(-halfBallEdgeSize, halfBallEdgeSize);
			glEnd();
		glPopMatrix();
	}
	
	// Dibujar barra del jugador 1
	glPushMatrix();
		glTranslated(leftBarPosition.x, leftBarPosition.y, defaultZ);
		glBegin(GL_QUADS);
			glColor3f(1, 1, 1);
			glVertex2f(-halfBarWidth, -halfBarHeight);
			glVertex2f(halfBarWidth, -halfBarHeight);
			glVertex2f(halfBarWidth, halfBarHeight);
			glVertex2f(-halfBarWidth, halfBarHeight);
		glEnd();
	glPopMatrix();
	
	// Dibujar barra del jugador 2
	glPushMatrix();
		glTranslated(rightBarPosition.x, rightBarPosition.y, defaultZ);
		glBegin(GL_QUADS);
			glColor3f(1, 1, 1);
			glVertex2f(-halfBarWidth, -halfBarHeight);
			glVertex2f(halfBarWidth, -halfBarHeight);
			glVertex2f(halfBarWidth, halfBarHeight);
			glVertex2f(-halfBarWidth, halfBarHeight);
		glEnd();
	glPopMatrix();
	
	float w = pixelToUnit(2);
	float h = pixelToUnit(10);
	
	// Dibujar linea central
	for(int n = 0; n < 1 / (2 * h); n++)
	{
		glPushMatrix();
			glTranslated(0, 1 - n * 4 * h, defaultZ);
			glBegin(GL_QUADS);
				glColor3f(1, 1, 1);
				glVertex2f(-w, -h);
				glVertex2f(w, -h);
				glVertex2f(w, h);
				glVertex2f(-w, h);
			glEnd();
		glPopMatrix();
	}
	
	glutSwapBuffers();
}

// Marca la ventana actual que necesita volver a mostrarse
static void idle()
{
	glutPostRedisplay();
}

// Evento que se desata al hundir una tecla
static void keyDown(unsigned char key, int x, int y)
{
	if(key == 'p')
	{
		moveRightBar = 1;
	}
	
	if(key == 'l')
	{
		moveRightBar = -1;
	}
	
	if(key == 'w')
	{
		moveLeftBar = 1;
	}
	
	if(key == 's')
	{
		moveLeftBar = -1;
	}
}

// Evento que se desata al soltar una tecla
static void keyUp(unsigned char key, int x, int y)
{
	if(key == 'p' || key == 'l')
	{
		moveRightBar = 0;
	}
	
	if(key == 's' || key == 'w')
	{
		moveLeftBar = 0;
	}
}

// Configuraci�n inicial del juego
void dafaultInit()
{
	countR = 0;
	numBall = 0;
	barSpeed = 20;
	digitHeight = 65;
	digitWidth = 40;
	score1 = 0;
	score2 = 0;
	playerWin = false;

	ballEdgeSize = pixelToUnit(ballEdgePixelSize);
	halfBallEdgeSize = ballEdgeSize / 2;
	
	barWidth = pixelToUnit(barPixelWidth);
	halfBarWidth = barWidth / 2;
	barHeight = pixelToUnit(barPixelHeight);
	halfBarHeight = barHeight / 2;
	
	leftBarPosition.zero();
	rightBarPosition.zero();
	leftBarPosition.x = -barXPos;
	rightBarPosition.x = barXPos;
	barSpeed *= (1 / (float) winSize);

	newBall();
	
	digitWidth = pixelToUnit((int) digitWidth);
	digitHeight = pixelToUnit((int) digitHeight);
}

// Sombrear partes para formar la letra
void packBlackWord(float x, float y, float w, float h, float w1, float h1, float w2, float h2, float w3, float h3, float w4, float h4, bool selected)
{
	glPushMatrix();
		glTranslated(x, y, defaultZ);
		glBegin(GL_QUADS);
			
			if(selected)
			{
				glColor3f(1, 1, 1);
			}
			else
			{
				glColor3f(0, 0, 0);
			}
				
			glVertex2f(-(w / 2) + w1, -(h / 2) + h1);
			glVertex2f((w / 2) + w2, -(h / 2) + h2);
			glVertex2f((w / 2) + w3, (h / 2) + h3);
			glVertex2f(-(w / 2) + w4, (h / 2) + h4);
		glEnd();
	glPopMatrix();
}

// Pinta letra por letra
void printWord(string word, float xWordInit, float yWordInit, float wordWidth, float wordHeigth, float gapWord, bool selected)
{
	float border = wordWidth / 4;
			
	if(selected)
	{
		glPushMatrix();
			glTranslated(xWordInit, yWordInit, defaultZ);
			glBegin(GL_QUADS);
				glColor3f(1, 1, 1);
				
				float width = (((wordWidth * (word.length())) + (gapWord * (word.length() - 1))) / 2);
				float heigth = wordHeigth / 2;
			
				glVertex2f(-width - border * 3, -heigth - border * 4);
				glVertex2f(width + border * 3, -heigth - border * 4);
				glVertex2f(width + border * 3, heigth - border);
				glVertex2f(-width - border * 3, heigth - border);
			glEnd();
		glPopMatrix();
	}
	
	xWordInit -= (((wordWidth * (word.length() - 1)) + (gapWord * (word.length() - 1))) / 2);
	yWordInit -= wordHeigth / 2;
	
	for(int i = 0; i < word.length(); i++)
	{
		glPushMatrix();
			glTranslated(xWordInit, yWordInit, defaultZ);
			glBegin(GL_QUADS);
			
				if(selected)
				{
					glColor3f(0, 0, 0);
				
					glVertex2f(-(wordWidth / 2), -(wordHeigth / 2));
					glVertex2f((wordWidth / 2), -(wordHeigth / 2));
					glVertex2f((wordWidth / 2), (wordHeigth / 2));
					glVertex2f(-(wordWidth / 2), (wordHeigth / 2));
				}
				else
				{
					glColor3f(1, 1, 1);
				
					glVertex2f(-(wordWidth / 2), -(wordHeigth / 2));
					glVertex2f((wordWidth / 2), -(wordHeigth / 2));
					glVertex2f((wordWidth / 2), (wordHeigth / 2));
					glVertex2f(-(wordWidth / 2), (wordHeigth / 2));
				}
			glEnd();
		glPopMatrix();
		
		switch(word[i])
		{
			case 'P':
				packBlackWord(xWordInit, yWordInit, wordWidth, wordHeigth, border, border * 3, -border, border * 3, -border, -border, border, -border, selected);
				packBlackWord(xWordInit, yWordInit, wordWidth, wordHeigth, border, 0, 0, 0, 0, -border * 3, border, -border * 3, selected);
				break;
			case 'O':
				packBlackWord(xWordInit, yWordInit, wordWidth, wordHeigth, border, border, -border, border, -border, -border, border, -border, selected);
				break;
			case 'N':
				packBlackWord(xWordInit, yWordInit, wordWidth, wordHeigth, border, 0, -border, 0, -border, -border, +border, -border, selected);
				break;
			case 'G':
				packBlackWord(xWordInit, yWordInit, wordWidth, wordHeigth, border, border * 3, 0, border * 3, 0, -border, border, -border, selected);
				packBlackWord(xWordInit, yWordInit, wordWidth, wordHeigth, border, border, -border, border, -border, -border * 3, border, -border * 3, selected);
				packBlackWord(xWordInit, yWordInit, wordWidth, wordHeigth, border, border * 2, -border * 2, border * 2, -border * 2, -border * 2, border, -border * 2, selected);
				break;
			case 'U':
				packBlackWord(xWordInit, yWordInit, wordWidth, wordHeigth, border, border, -border, border, -border, 0, border, 0, selected);
				break;
			case 'E':
				packBlackWord(xWordInit, yWordInit, wordWidth, wordHeigth, border, border * 3, 0, border * 3, 0, -border, border, -border, selected);
				packBlackWord(xWordInit, yWordInit, wordWidth, wordHeigth, border * 3, border * 2, 0, border * 2, 0, -border * 2, border * 3, -border * 2, selected);
				packBlackWord(xWordInit, yWordInit, wordWidth, wordHeigth, border, border, 0, border, 0, -border * 3, border, -border * 3, selected);
				break;
			case 'V':
				packBlackWord(xWordInit, yWordInit, wordWidth, wordHeigth, border, border, -border, border, -border, 0, border, 0, selected);
				packBlackWord(xWordInit, yWordInit, wordWidth, wordHeigth, 0, 0, -border * 3, 0, -border * 3, -border * 4, 0, -border * 4, selected);
				packBlackWord(xWordInit, yWordInit, wordWidth, wordHeigth, border * 3, 0, 0, 0, 0, -border * 4, border * 3, -border * 4, selected);
				break;
			case ' ':
				packBlackWord(xWordInit, yWordInit, wordWidth, wordHeigth, 0, 0, 0, 0, 0, 0, 0, 0, selected);
				break;
			case 'J':
				packBlackWord(xWordInit, yWordInit, wordWidth, wordHeigth, border, border, -border, border, -border, 0, border, 0, selected);
				packBlackWord(xWordInit, yWordInit, wordWidth, wordHeigth, 0, border * 2, -border * 3, border * 2, -border * 3, 0, 0, 0, selected);
				break;
			case 'S':
				packBlackWord(xWordInit, yWordInit, wordWidth, wordHeigth, border, border * 3, 0, border * 3, 0, -border, border, -border, selected);
				packBlackWord(xWordInit, yWordInit, wordWidth, wordHeigth, 0, border, -border, border, -border, -border * 3, 0, -border * 3, selected);
				break;
			case 'A':
				packBlackWord(xWordInit, yWordInit, wordWidth, wordHeigth, border, border * 3, -border, border * 3, -border, -border, border, -border, selected);
				packBlackWord(xWordInit, yWordInit, wordWidth, wordHeigth, border, 0, -border, 0, -border, -border * 3, border, -border * 3, selected);
				break;
			case 'L':
				packBlackWord(xWordInit, yWordInit, wordWidth, wordHeigth, border, border, 0, border, 0, 0, border, 0, selected);
				break;
			case 'I':
				packBlackWord(xWordInit, yWordInit, wordWidth, wordHeigth, 0, border, -border * 2.5, border, -border * 2.5, -border, 0, -border, selected);
				packBlackWord(xWordInit, yWordInit, wordWidth, wordHeigth, border * 2.5, border, 0, border, 0, -border, border * 2.5, -border, selected);
				break;
			case 'R':
				packBlackWord(xWordInit, yWordInit, wordWidth, wordHeigth, border, border * 3, -border, border * 3, -border, -border, border, -border, selected);
				packBlackWord(xWordInit, yWordInit, wordWidth, wordHeigth, border * 3, border * 2, 0, border * 2, 0, -border * 2, border * 3, -border * 2, selected);
				packBlackWord(xWordInit, yWordInit, wordWidth, wordHeigth, border, 0, -border, 0, -border, -border * 3, border, -border * 3, selected);
				break;
		}
		
		xWordInit += wordWidth + gapWord;
	}
}

// Imprimir Menu
void printNav1()
{
	string nav1[] = {"NUEVO JUEGO", "SALIR"};
	float tile = pixelToUnit(6);
	float yMenu = pixelToUnit(-100);
	
	for(int i = 0; i < nav1Length; i++)
	{
		bool selected = false;
		
		if(i == nav1Pos) selected = true;
		
		printWord(nav1[i], 0, yMenu, tile * 4, tile * 5, tile, selected);
		
		yMenu -= tile * 15;
	}
}

// Verificar que item se selecciona en Menu
void enterScene()
{
	switch(nav1Pos)
	{
		case 0:
			glutDisplayFunc(game);
	
			// Inicializa las variables del juego
			dafaultInit();
	
			// Escuchador de eventos
			glutKeyboardFunc(keyDown);
			glutKeyboardUpFunc(keyUp);
			
			glutIdleFunc(idle);
			break;
			
		case 1:
			exit(0);
	}
}

// Evento de presionar el boton en Menu
static void arrowDown(unsigned char key, int x, int y)
{
	if(key == 'w')
	{
		if(nav1Pos > 0) nav1Pos--;
	}
	
	if(key == 's')
	{
		if(nav1Pos + 1 < nav1Length) nav1Pos++;
	}
	
	if(key == 13)
	{
		enterScene();
	}
}

// Escena de menu
void nav()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3d(0, 0, 1);
	
	// Dibujar "PONG"
	float pongTile = pixelToUnit(30);
	float pongWidth = pongTile * 4;
	float pongHeigth = pongTile * 5;
	float gapPong = pongTile;
	float xPongInit = 0;
	float yPongInit = pixelToUnit(250);
	printWord("PONG", xPongInit, yPongInit, pongWidth, pongHeigth, gapPong, false);
	
	printNav1();
	
	glutSwapBuffers();
	
	// Escuchador de eventos
	glutKeyboardFunc(arrowDown);
	glutIdleFunc(idle);
}

int main (int argc, char *argv[])
{	
	glutInit(&argc, argv);
	glutInitWindowPosition(300, 300);
	glutInitWindowSize(winSize, winSize);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("PONG");
	
	glutReshapeFunc(resize);
	glutDisplayFunc(nav);
	
	glutMainLoop();
	
	return EXIT_SUCCESS;
}
