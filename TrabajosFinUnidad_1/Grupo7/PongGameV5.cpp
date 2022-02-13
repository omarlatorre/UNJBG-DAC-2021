#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
//#include <stdlib.h>
//#include <time.h>
#include <stdio.h>

/*
	Juego de ping pong multiplayer usando librerías OpenGL y glut
	Game start: El juego inicia haciendo click izquierdo con el mouse
	Game stop: El juego para si preciona el boton de en medio del mouse
	Game end: precionar tecla c
	
	Keyboard:
		Player 1 : controla la paleta usando las teclas w y a 
		Player 2 : controla la paleta usando las teclas arriba y abajo
		
		tecla r : para reiniciar el juego
		tecla m : para iniciar el movimiento de la segunda pelota
*/

// Variables globales 
static GLint windowSizeX = 800, windowSizeY = 1200;
static GLint orthoSizeX = 600, orthoSizeY = 400;

// Variables del juego
static char score_1[20], score_2[20];
static GLint player1_score = 0, player2_score = 0, score_limit=10;
//static GLint player1_life = 3, pla
//player2_life = 3;  //Para agregarle vida a los jugadores
static GLint paddle_boundary = 350, paddle_height = 100, paddile_velocity = 8.0;
static GLint player1_paddile_y = 0, player2_paddile_y = 0, paddle_x = 595;
//
static GLfloat ball_velocity_x = 0, ball_velocity_y = 0, speed_increment = 0.9;
static GLint ball_pos_x = 0, ball_pos_y = 0, ball_radius = 20;
//
static GLfloat ball2_velocity_x = 0, ball2_velocity_y = 0, speed2_increment = 0.9;
static GLint ball2_pos_x = 0, ball2_pos_y = 0, ball2_radius = 20;
static GLint rebo=0, rebote=1;
//

void init(void) {
    // inicializa el display(monitor) con color negro
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_FLAT);

    //srand(time(NULL));
}

// Dibujar el texto( puntuación ) en la ventana
void drawStrokeText(char*string, int x, int y, int z)
{
    char *c;
    glPushMatrix();
	glTranslatef(x, y+8,z);
	    // glScalef(1.0f,-0.08f,z);
	    for (c=string; *c != '\0'; c++)
	    {
	        glutStrokeCharacter(GLUT_STROKE_ROMAN , *c);
	    }
    glPopMatrix();
}

// Dibujado de las lineas centrales [ espaciado: 20px, ancho: 4px ]
void drawCenterLines() {
	
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(-2 , -410);
    glVertex2f(2 , -410);
    glVertex2f(2 , -390);
    glVertex2f(-2 , -390);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(-2 , -370);
    glVertex2f(2 , -370);
    glVertex2f(2 , -350);
    glVertex2f(-2 , -350);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(-2 , -330);
    glVertex2f(2 , -330);
    glVertex2f(2 , -310);
    glVertex2f(-2 , -310);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(-2 , -290);
    glVertex2f(2 , -290);
    glVertex2f(2 , -270);
    glVertex2f(-2 , -270);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(-2 , -250);
    glVertex2f(2 , -250);
    glVertex2f(2 , -230);
    glVertex2f(-2 , -230);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(-2 , -210);
    glVertex2f(2 , -210);
    glVertex2f(2 , -190);
    glVertex2f(-2 , -190);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(-2 , -170);
    glVertex2f(2 , -170);
    glVertex2f(2 , -150);
    glVertex2f(-2 , -150);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(-2 , -130);
    glVertex2f(2 , -130);
    glVertex2f(2 , -110);
    glVertex2f(-2 , -110);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(-2 , -90);
    glVertex2f(2 , -90);
    glVertex2f(2 , -70);
    glVertex2f(-2 , -70);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(-2 , -50);
    glVertex2f(2 , -50);
    glVertex2f(2 , -30);
    glVertex2f(-2 , -30);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(-2 , -10);
    glVertex2f(2 , -10);
    glVertex2f(2 , 10);
    glVertex2f(-2 , 10);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(-2 , 30);
    glVertex2f(2 , 30);
    glVertex2f(2 , 50);
    glVertex2f(-2 , 50);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(-2 , 70);
    glVertex2f(2 , 70);
    glVertex2f(2 , 90);
    glVertex2f(-2 , 90);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(-2 , 110);
    glVertex2f(2 , 110);
    glVertex2f(2 , 130);
    glVertex2f(-2 , 130);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(-2 , 150);
    glVertex2f(2 , 150);
    glVertex2f(2 , 170);
    glVertex2f(-2 , 170);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(-2 , 190);
    glVertex2f(2 , 190);
    glVertex2f(2 , 210);
    glVertex2f(-2 , 210);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(-2 , 230);
    glVertex2f(2 , 230);
    glVertex2f(2 , 250);
    glVertex2f(-2 , 250);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(-2 , 270);
    glVertex2f(2 , 270);
    glVertex2f(2 , 290);
    glVertex2f(-2 , 290);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(-2 , 310);
    glVertex2f(2 , 310);
    glVertex2f(2 , 330);
    glVertex2f(-2 , 330);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(-2 , 350);
    glVertex2f(2 , 350);
    glVertex2f(2 , 370);
    glVertex2f(-2 , 370);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(-2 , 390);
    glVertex2f(2 , 390);
    glVertex2f(2 , 410);
    glVertex2f(-2 , 410);
    glEnd();
}

// Dibujado de la paleta que usaran los jugadores para pegar la pelota
void drawPaddle(int x, int y) {
    glPushMatrix();
	glTranslatef(x, y, 0);
	
	    glBegin(GL_QUADS);
	    glColor3f(1.0, 1.0, 1.0);
	    int height = paddle_height / 2;
	    glVertex2f(-5 , height);
	    glVertex2f(5 , height);
	    glVertex2f(5 , -height);
	    glVertex2f(-5, -height);
	    glEnd();

    glPopMatrix();
}

// Dibujado de la pelota
void drawBall(int x, int y) {
    glPushMatrix();
	glTranslatef(x, y, 0);
	    
	    glColor3f(1.0, 1.0, 1.0);
	    glutSolidSphere (ball_radius, 20, 16);

    glPopMatrix();
}

// Funciones del main display
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
	
	// función de dibujado de las lineas centrales
    drawCenterLines();

    // dibujado del player1(su paleta) izquierda
    drawPaddle(-paddle_x, player1_paddile_y);
    // dibujado del player2(su paleta) derecha
    drawPaddle(paddle_x, player2_paddile_y);

    // dibujado de la pelota wakamoly boly, variando en cada frame
    drawBall(ball_pos_x, ball_pos_y);
    
    if(rebo >=  rebote ){
    	drawBall(ball2_pos_x, ball2_pos_y);
	}
	
    // dibujado de la puntuación lado izquierdo para el player1
    snprintf (score_1, sizeof(score_1), "%d", player1_score);
    drawStrokeText(score_1, -300, 200, 0);

    // dibujado de la puntuación lado derecho para el player2
    snprintf (score_2, sizeof(score_2), "%d", player2_score);
    drawStrokeText(score_2, 200, 200, 0);

    // intercambia el marco actual con el marco dibujado
    glutSwapBuffers();
    glFlush();
}

void startGame(void) {

    // movimiento de la pelota
    //Variables de movimiento de pelota 1
    ball_pos_x += ball_velocity_x;
    ball_pos_y += ball_velocity_y;
    
    //Variables de movimiento de pelota 2
    ball2_pos_x += ball2_velocity_x;
    ball2_pos_y += ball2_velocity_y;
	
	//Cuando se obtiene 10 puntos
	if (player1_score == score_limit || player2_score == score_limit ){
		ball_pos_x = 0;
		ball_pos_y = 0;
		ball_velocity_x = 0;
		ball_velocity_y = 0;
		
		ball2_pos_x = 0;
		ball2_pos_y = 0;
		ball2_velocity_x = 0;
		ball2_velocity_y = 0;		 
	}
	
    // cuando la pelota golpea la parte de arriba de la ventana o la parte de abajo (top or bottom)
    if (ball_pos_y + ball_radius > orthoSizeY || ball_pos_y - ball_radius < -orthoSizeY)
        ball_velocity_y = -ball_velocity_y;
        
        
        

    // cuando la pelota golpea el muro izquierdo
    if (ball_pos_x - ball_radius - 5 < -paddle_x && ball_pos_x - ball_radius < -paddle_x)
        if (ball_pos_y < player1_paddile_y + paddle_height && ball_pos_y > player1_paddile_y - paddle_height) {
            ball_velocity_x = -ball_velocity_x;
            ball_velocity_x += speed_increment;
            paddile_velocity += speed_increment;
            rebo+=1;
        }


    // cuando la pelota golpea el muro derecho
    if (ball_pos_x + ball_radius + 5 > paddle_x && ball_pos_x + ball_radius < paddle_x)
        if (ball_pos_y < player2_paddile_y + paddle_height && ball_pos_y > player2_paddile_y - paddle_height)
            ball_velocity_x = -ball_velocity_x;

    // puntuación del player1
    if (ball_pos_x + ball_radius > orthoSizeX) {
        player1_score++;
        printf("Player 1 = %d \n", player1_score);
        ball_velocity_x = -ball_velocity_x;
        
    }

    // puntuación del player2
    if (ball_pos_x - ball_radius < -orthoSizeX) {
        player2_score++;
        printf("Player 2 = %d \n", player2_score);
        ball_velocity_x = -ball_velocity_x;
    }

//--------------------------------------------------------------
// movimiento de la pelota 2	
	
    // cuando la pelota golpea la parte de arriba de la ventana o la parte de abajo (top or bottom)
    if (ball2_pos_y + ball2_radius > orthoSizeY || ball2_pos_y - ball2_radius < -orthoSizeY)
        ball2_velocity_y = -ball2_velocity_y;
        
        

    // cuando la pelota golpea el muro izquierdo
    if (ball2_pos_x - ball2_radius - 5 < -paddle_x && ball2_pos_x - ball2_radius < -paddle_x)
        if (ball2_pos_y < player1_paddile_y + paddle_height && ball2_pos_y > player1_paddile_y - paddle_height) {
            ball2_velocity_x = -ball2_velocity_x;
            ball2_velocity_x += speed2_increment;
            //paddile_velocity += speed_increment;
        }


    // cuando la pelota golpea el muro derecho
    if (ball2_pos_x + ball2_radius + 5 > paddle_x && ball2_pos_x + ball2_radius < paddle_x)
        if (ball2_pos_y < player2_paddile_y + paddle_height && ball2_pos_y > player2_paddile_y - paddle_height)
            ball2_velocity_x = -ball2_velocity_x;

    
    if (ball2_pos_x + ball2_radius > orthoSizeX) {
        player1_score++;
        printf("Player 1 = %d \n", player1_score);
        ball2_velocity_x = -ball2_velocity_x;
        
    }

    
    if (ball2_pos_x - ball2_radius < -orthoSizeX) {
        player2_score++;
        printf("Player 2 = %d \n", player2_score);
        ball2_velocity_x = -ball2_velocity_x;
    }
//-----------------------------------------------------------------
    glutPostRedisplay();
}

// refrescar la pantalla(display
void reshape(int w, int h) {
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-orthoSizeX, orthoSizeX, -orthoSizeY, orthoSizeY, -100, 100);
    //glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
}

// click del mouse
void mouse(int button, int state, int x, int y) {
    switch (button) {
        // click izquierdo
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN)
            ball_velocity_x = (rand() % 5) -  (rand() % 3);
            ball_velocity_y = (rand() % 5) -  (rand() % 3);

            // sige llamando a la devolución de llamada para mover la pelota y verificar las condiciones de los límites
            glutIdleFunc(startGame);
            break;
        // click central resetea la pelota, paleta de players y puntuaciones
        case GLUT_MIDDLE_BUTTON:
            // resetea la pelota, paleta de players y puntuaciones
            ball_pos_x = ball_pos_y = 0;
            player1_paddile_y = player2_paddile_y = 0;
            player1_score = player2_score = 0;
            if (state == GLUT_DOWN)
                // remueve la llamada de regreso para parar el juego
                glutIdleFunc(NULL);
            break;
        default:
        	break;
    }
}

void keyboard (unsigned char key, int x, int y) {
    switch (key) {
        // mover player 1 paddile up
        case 'w':
            if (player1_paddile_y < paddle_boundary)
                player1_paddile_y += paddile_velocity;
            glutPostRedisplay();
            break;
        // mover player 1 paddile down
        case 's':
            if (player1_paddile_y > -paddle_boundary)
                player1_paddile_y -= paddile_velocity;
            glutPostRedisplay();
            break;

        // Iniciar pelota dos
        case 'm':
        	ball2_velocity_x = (rand() % 5) -  (rand() % 3);
            ball2_velocity_y = (rand() % 5) -  (rand() % 3);
        	break;
        // Reset game
		case 'r':
			ball_pos_x = ball_pos_y = 0;
            ball2_pos_x = ball2_pos_y = 0;
            player1_paddile_y = 0;
			player2_paddile_y = 0;
            player1_score = 0;
			player2_score = 0;
			rebo = 0;
            
            glutIdleFunc(NULL);        	
        	break;
        // exit on esc
        case 'c':
            exit(0);
            break;
        default:
            break;
    }
}

void special_keyboard(int tecla, int x, int y){
	if (tecla == GLUT_KEY_UP){
		if (player2_paddile_y < paddle_boundary)
                player2_paddile_y += paddile_velocity;
            glutPostRedisplay();
	}
	
	if (tecla == GLUT_KEY_DOWN){
		if (player2_paddile_y > -paddle_boundary)
                player2_paddile_y -= paddile_velocity;
            glutPostRedisplay();
    }
}


/*
* Solicita modo de visualización de doble búfer.
* Registra las funciones de devolución de llamada de entrada del mouse
*/
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (1200, 800);
    glutInitWindowPosition (10, 10);
    glutCreateWindow (argv[0]);
    init ();

    // llamada a las funciones para rendering, reshape
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    // llamada a funcion del click del mouse y teclado
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special_keyboard);
    glutMainLoop();
    return 0;
}
