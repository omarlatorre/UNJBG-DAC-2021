#include <iostream>
#include <GL/glut.h>
#include <windows.h>
#include <GL/freeglut.h>
#include <string>
#include <time.h>  

#define P_altura 2.0
#define P_ancho 0.3
#define P_long 0.3
#define B_altura 0.3
#define B_ancho 14.3
#define B_long 0.3
#define mov 0.01
#define borde 3
#define epsilon 1.01
#define r_ball 0.2
#define R 10
#define BM 4
#define maxscore 10

using namespace std;

int escena=0; //0=inicio 1=pvp 2=pvc
bool select=true;
bool d_select=false;
int CPU_mov=0;
int CPU_mov2=0;
const GLfloat light_ambient[]  = { 0.3, 0.3, 0.3, 1.0 };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 30.0f ,50.0f, 40.0f, 1.0f };
double rotate_y=0.2;
int valor=1;
float p1_pos=0;
float p2_pos=0;
float lastp1_pos=0,lastp2_pos=0;
int p1_score=0;
int p2_score=0;
int choques=0;
int balls_now=0;
int auxdelay;
bool kdelay=true;
float Rplayer1=0.61,Gplayer1=0.80,Bplayer1=0.86;
float Rplayer2=0.61,Gplayer2=0.80,Bplayer2=0.86;
float Rborde1=0.33,Gborde1=0.23,Bborde1=0.64;
float Rborde2=0.33,Gborde2=0.23,Bborde2=0.64;

void tiempo(int param){
	glutPostRedisplay();
	glutTimerFunc(valor,tiempo,0);	
}
void letra(float x, float y, char *string,int a,bool b){
    if(b)
	glColor3f(1,1,1);
	else
	glColor3f(0.5,0.5,0.5);
	int len, i;
    glRasterPos2f(x, y);
    len = (int) strlen(string);
    for (i = 0; i < len; i++) {
    	switch(a){
    	case 1:
    	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[i]); break;
    	case 2:
    	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string[i]); break;	
    	default:
    	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, string[i]);
    	}
    }
  }
void printN(float x, float y, int num){
    int len=1, i;
    char T;
    //glPushMatrix();
	//glTranslatef(x, y, 0);
    glRasterPos2f(x, y);
	int a=num;
  		if (a>0){
  			for (len = 0; a > 0; len++) {
        	a = a / 10;
    		}
    	for (int j = 0; j < len; j++) {
        	a = num % (10);
        	num=num/10;
        	switch(a){
			    case 9: T='9';
			    break;
			    case 8: T='8';
			    break;
			    case 7: T='7';
			    break;
			    case 6: T='6';
			    break;
			    case 5: T='5';
			    break;
			    case 4: T='4';
			    break;
			    case 3: T='3';
			    break;
			    case 2: T='2';
			    break;
			    case 1: T='1';
			    break;
			    default: T='0';
			}
			//glScalef(2,2,1);
			//glutStrokeCharacter(GLUT_STROKE_ROMAN, T);
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, T);
			//glTranslatef(-x, -y, 0);
			x=x-0.10;
			//glTranslatef(x, y, 0);
			//glTranslatef(-x, -y, 0);
			glRasterPos2f(x, y);
    		}  
		}
		else{
			//glScalef(2,2,1);
		//glutStrokeCharacter(GLUT_STROKE_ROMAN, '0');
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0');
		}
		//glTranslatef(-x, -y, 0);
	//glPopMatrix();	
	
  }  
void color_player(){//Rplayer=0.61,Gplayer=0.80,Bplayer=0.86;
	if(Rplayer1<0.61)
		Rplayer1=Rplayer1+0.001;
	if(Rplayer1>0.61)
		Rplayer1=Rplayer1-0.001;
	if(Gplayer1<0.80)
		Gplayer1=Gplayer1+0.001;
	if(Gplayer1>0.80)
		Gplayer1=Gplayer1-0.001;
	if(Bplayer1<0.86)
		Bplayer1=Bplayer1+0.001;
	if(Bplayer1>0.86)
		Bplayer1=Bplayer1-0.001;

	if(Rplayer2<0.61)
		Rplayer2=Rplayer2+0.001;
	if(Rplayer2>0.61)
		Rplayer2=Rplayer2-0.001;
	if(Gplayer2<0.80)
		Gplayer2=Gplayer2+0.001;
	if(Gplayer2>0.80)
		Gplayer2=Gplayer2-0.001;
	if(Bplayer2<0.86)
		Bplayer2=Bplayer2+0.001;
	if(Bplayer2>0.86)
		Bplayer2=Bplayer2-0.001;
}
void modi_color_player(float a, float b, float c, int d){
	switch(d){
	case 1:
	Rplayer1=a;
	Gplayer1=b;
	Bplayer1=c;
	break;
	default:
	Rplayer2=a;
	Gplayer2=b;
	Bplayer2=c;	
	}
}
void color_borde(){//0.33f, 0.57f, 0.66f
	if(Rborde1<0.33f)
		Rborde1=Rborde1+0.001;
	if(Rborde1>0.33f)
		Rborde1=Rborde1-0.001;
	if(Gborde1<0.23f)
		Gborde1=Gborde1+0.001;
	if(Gborde1>0.23f)
		Gborde1=Gborde1-0.001;
	if(Bborde1<0.64f)
		Bborde1=Bborde1+0.001;
	if(Bborde1>0.64f)
		Bborde1=Bborde1-0.001;

	if(Rborde2<0.33f)
		Rborde2=Rborde2+0.001;
	if(Rborde2>0.33f)
		Rborde2=Rborde2-0.001;
	if(Gborde2<0.23f)
		Gborde2=Gborde2+0.001;
	if(Gborde2>0.23f)
		Gborde2=Gborde2-0.001;
	if(Bborde2<0.64f)
		Bborde2=Bborde2+0.001;
	if(Bborde2>0.64f)
		Bborde2=Bborde2-0.001;
}
void modi_color_borde(float a, float b, float c, int d){
	switch(d){
	case 1:
	Rborde1=a;
	Gborde1=b;
	Bborde1=c;
	break;
	default:
	Rborde2=a;
	Gborde2=b;
	Bborde2=c;	
	}
}
void calc_color_medio(int a){
	if(a<=5){
		a=a+a-1;
	}	
	else{
		switch (a){
			case 6:
				a=8;break;
			case 7:
				a=6;break;
			case 8:
				a=4;break;
			default:
				a=2;
		}
	}
	if(a<=choques%R)
	glColor3f(0.80f, 0.80f, 0.80f);
	else
	glColor3f(0.40f, 0.40f, 0.40f);
}
void controlupdate(){
	if(p1_pos<=borde){
		if(	(GetAsyncKeyState(0x57)!=0 && (escena==1||escena==2)) || (CPU_mov2==1 && escena==0))
		p1_pos=p1_pos+mov;
	}
	else{
		if((GetAsyncKeyState(0x53)!=0 && (escena==1||escena==2)) || (CPU_mov2==-1 && escena==0))
		p1_pos=p1_pos-mov;
	}
	if(p1_pos>=-borde){
		if((GetAsyncKeyState(0x53)!=0 && (escena==1||escena==2)) || (CPU_mov2==-1 && escena==0))
		p1_pos=p1_pos-mov;
	}
	else{
		if((GetAsyncKeyState(0x57)!=0 && (escena==1||escena==2)) || (CPU_mov2==1 && escena==0))
		p1_pos=p1_pos+mov;
	}
	if(p2_pos<=borde){
		if((GetAsyncKeyState(0x26)!=0 && escena==1) || (CPU_mov==1 && (escena==2||escena==0)))
		p2_pos=p2_pos+mov;
	}
	else{
		if((GetAsyncKeyState(0x28)!=0 && escena==1) || (CPU_mov==-1 && (escena==2||escena==0)))
		p2_pos=p2_pos-mov;
	}
	if(p2_pos>=-borde){
		if((GetAsyncKeyState(0x28)!=0 && escena==1) || (CPU_mov==-1 && (escena==2||escena==0)))
		p2_pos=p2_pos-mov;
	}
	else{
		if((GetAsyncKeyState(0x26)!=0 && escena==1) || (CPU_mov==1 && (escena==2||escena==0)))
		p2_pos=p2_pos+mov;
	}
	//cout<<"p2="<<p2_pos<<endl;
}
int playerdirec(int a){
	if(a==1){
		if(lastp1_pos>p1_pos)
			return -1;
		else if(lastp1_pos==p1_pos)
			return 0;
		else
			return 1;		
	}
	else{
		if(lastp2_pos>p2_pos)
			return -1;
		else if(lastp2_pos==p2_pos)
			return 0;
		else
			return 1;
	}
}
void scoreupdate_rayas(float a){
	glTranslatef(a,borde+(P_altura/2)+(B_altura/2)-0.03,P_long);
	glPushMatrix();
	glScalef(P_ancho/2,P_altura/3-0.2,0.1);
	glColor3f(0.80f, 0.80f, 0.80f);
	glutSolidCube(1);
	glPopMatrix();
	glTranslatef(-a,-borde-(P_altura/2)-(B_altura/2)+0.03,-P_long);	
}
void scoreupdate(){
	float a=-6;
	glColor3f(1,1,1);
	//printN(-0,0,p1_score);
	printN(-3.7,3.5,p1_score);
	printN(3.7,3.5,p2_score);
	for(int i=0;i<p1_score;i++){
		scoreupdate_rayas(a);
		a=a+0.3;
	}
	a=6;
	for(int i=0;i<p2_score;i++){
		scoreupdate_rayas(a);
		a=a-0.3;
	}
}
bool game(){
	if(p1_score>=maxscore||p2_score>=maxscore)
	return false;
	else
	return true;
}
class bola{
public:
	float vel_ball,ball_x,ball_y,ball_x2,ball_y2,ball_ax,ball_ay;
	bool newball;
	bool perdidaball;
	bool ballviva;
	bool chocadoend;
	float Ax,By;
	int D;

	float nuevoX,nuevoY,nuevoX2,nuevoY2,aux_Ax,aux_By,aux_D,aux_vel;
	bool sacarLast;
	float pruebaY;
	bola(){
	refresh();	
	}
	void refresh(){
		vel_ball=0.01;
		ball_x=0;
		ball_y=0;
		ball_x2=0;
		ball_y2=0;
		ball_ax=0;
		ball_ay=0;
		nuevoX=0;
		nuevoY=0;
		sacarLast=true;
		chocadoend=false;
		newball=true;
		perdidaball=false;
		ballviva=false;
		srand (time(NULL));
		Ax = rand() % 41 - 20;  
		By = 30;  	
		if (Ax==0)
		Ax=1;
		if (By==0)
		By=1;
		D = rand() % 2;
		if(D==0)
		D=-1;
		newball=false;
	}
	bool direccion(bool d){
		float aux_x=ball_x;
		float aux_x2=aux_x+vel_ball*D;
		if(aux_x<aux_x2){
			if(d)
				return true;
			else
				return false;
		}
		else{
			if(d)
				return false;
			else
				return true;
		}
	}
	bool chocaH(bool a){
		if(ball_y>=borde+P_altura/2-r_ball){
			if(a)
			modi_color_borde(0.94,0.94,0.96,1); 
			return true;}
		else if(ball_y<=-(borde+P_altura/2-r_ball)) {
			if(a)
			modi_color_borde(0.94,0.94,0.96,2); 
			return true;}
		else
			return false;
	}
	bool chocaV(bool a){
		if( ball_x<=-7+P_ancho/2+r_ball && perdidaball==false){
			//cout<<"p1M="<<p1_pos+P_altura/2<<" p1m="<<p1_pos-(P_altura/2)<<" X="<<ball_x<<endl;
			if( ball_y<=p1_pos+P_altura/2 && ball_y>=p1_pos-(P_altura/2) ){
			if(a)
			modi_color_player(0.94,0.94,0.96,1);
			return true;}
			else{
				perdidaball=true;
				return false;
			}	
		}
		else if(ball_x>=7-P_ancho/2-r_ball && perdidaball==false){
			if( ball_y<=p2_pos+P_altura/2 && ball_y>=p2_pos-P_altura/2 ){
			if(a)
			modi_color_player(0.94,0.94,0.96,2);
			return true;}
			else{
				perdidaball=true;
				return false;
			}	
		}
		else
			return false;
	}
	int chocaPH(){
			if( ball_x<=-7+P_ancho/2+r_ball&&ball_x>=-7-P_ancho/2-r_ball&&chocadoend==false){
				//cout<<"p1M="<<p1_pos+P_altura/2<<" p1m="<<p1_pos-(P_altura/2)<<" X="<<ball_x<<endl;
				if( ball_y<=p1_pos+P_altura/2 && ball_y>=p1_pos-(P_altura/2) ){
					if(ball_y<=p1_pos){
						return -1;
						//chocadoend=true;
					}
					else{
						return 1;
						//chocadoend=true;
					}
				}
				else
					return 0;
			}
			else if(ball_x<=7+P_ancho/2+r_ball&&ball_x>=7-P_ancho/2-r_ball&&chocadoend==false){
				if( ball_y<=p2_pos+P_altura/2 && ball_y>=p2_pos-(P_altura/2 )){
					if(ball_y<=p2_pos){
						return -2;
						//chocadoend=true;
					}
					else{
						return 2;
						//chocadoend=true;
					}
				}
				else
					return 0;
			}
			else
				return 0;	
	}
	bool muere(){
		if(( ball_x>=9 || (ball_x<=-9) ) || ballviva==false){
			//ballviva=false;
			return true;
		}
		else
			return false;
	}
	void calcmovi(){
		ball_ay=ball_y2;
		ball_ax=ball_x2;
		ball_x2=ball_x2+vel_ball*D;
		ball_y2=(-(ball_x2*Ax))/By;
		ball_y=ball_y+(ball_y2-ball_ay);
		ball_x=ball_x+(ball_x2-ball_ax);
	}
	void ballmovi(bool T){
		//cout<<" X="<<ball_x<<" X2="<<ball_x2<<endl;
		//cout<<" p1="<<p1_score<<" p2="<<p2_score<<endl;
		//cout<<" vel="<<vel_ball<<endl;
		if(ballviva==true){
			if(T)
				drawball();
			if(sacarLast){
			sacarLast=false;
			nuevoX=ball_x;
			nuevoY=ball_y;
			nuevoX2=ball_x2;
			nuevoY2=ball_y2;
			aux_Ax=Ax;
			aux_By=By;
			aux_D=D;
			aux_vel=vel_ball;
			vel_ball=0.7;
			if (direccion(true)){
				while(ball_x<=-(-7+P_ancho/2+r_ball)){
					ballmovi(false);
				}
			}	
			else{
				while(ball_x>=(-7+P_ancho/2+r_ball)){
					ballmovi(false);
				}
			}
			pruebaY=ball_y;
			ball_x=nuevoX;
			ball_y=nuevoY;
			ball_x2=nuevoX2;
			ball_y2=nuevoY2;
			Ax=aux_Ax;
			By=aux_By;
			D=aux_D;
			vel_ball=aux_vel;
			sacarLast=false;
			}
		if(chocaV(false)==false&&chocaH(false)==false&&muere()==false&&chocaPH()==0){
			calcmovi();
		//ball_x=(-C-(ball_y*By))/Ax;
		}
		else{
			if(chocaH(T)){
				if(T)
				Beep(100,25);
				ball_x2=0;
				ball_y2=0;
				Ax=Ax*-1;
				calcmovi();
			}
			else if(chocaV(T)){
				//MessageBeep(0);
				//PlaySound(TEXT("SystemExit"), NULL, SND_ALIAS | SND_ASYNC);
				//PlaySound(TEXT("SystemStart"), NULL, SND_ALIAS | SND_ASYNC | SND_NODEFAULT);
				if(T)
				Beep(523,45);
				ball_x2=0;
				ball_y2=0;
				By=By*-1;
				D=D*-1;
				
				if(T)
				sacarLast=true;
				
				calcmovi();
				vel_ball=vel_ball*epsilon;
				choques++;
			}
			else if(chocaPH()!=0){
				Beep(523,45);
				switch(chocaPH()){
					case 1:
						if(playerdirec(1)==1){
							ball_x2=0;
							ball_y2=0;
							Ax=0.7;
							By=0.4;
							calcmovi();
						}
						else{
							ball_x2=0;
							ball_y2=0;
							Ax=Ax*-1;
							calcmovi();
						}
					break;
					case -1:
						if(playerdirec(1)==-1){
							ball_x2=0;
							ball_y2=0;
							Ax=-0.7;
							By=0.4;
							calcmovi();
						}
						else{
							ball_x2=0;
							ball_y2=0;
							Ax=Ax*-1;
							calcmovi();
						}
					break;
					case 2:
						if(playerdirec(2)==1){
							ball_x2=0;
							ball_y2=0;
							Ax=-0.7;
							By=0.4;
							calcmovi();
						}
						else{
							ball_x2=0;
							ball_y2=0;
							Ax=Ax*-1;
							calcmovi();
						}
					break;
					default:
						if(playerdirec(2)==-1){
							ball_x2=0;
							ball_y2=0;
							Ax=0.7;
							By=0.4;
							calcmovi();
						}
						else{
							ball_x2=0;
							ball_y2=0;
							Ax=Ax*-1;
							calcmovi();
						}
				}
				chocadoend=true;
			}
			else{
				if (ballviva==true){
					if(ball_x>6)
					p1_score=p1_score+1;
					else
					p2_score=p2_score+1;
					balls_now--;
					MessageBeep(0x00000000L);
				}
				else{}
				ballviva=false;
			}
		}
	}
	}
	void drawball(){
	glTranslatef(ball_x,ball_y,0);
	glColor3f(0.81,0.84,0.88);
	glPushMatrix();
	glutSolidSphere(r_ball,50,50);
	glPopMatrix();
	glTranslatef(-ball_x,-ball_y,0);
	/*
	glTranslatef(ball_x,pruebaY,0);
	glColor3f(0,1,0);
	glPushMatrix();
	glutSolidSphere(r_ball,50,3);
	glPopMatrix();
	glTranslatef(-ball_x,-pruebaY,0);*/
	
	}
};
bola bolas[BM];
int Num_ball_direct(bool a){//a=true numero de bolas a la derecha
	int N=0;
	for(int i=0;i<BM;i++){	
		if(bolas[i].ballviva==true){
			if(bolas[i].direccion(a))
			N++;
		}
	}
	return N;
}
void CPU_mov_cambio(bool a,float b){
	if(a){
			if(p2_pos<b-0.04)
				CPU_mov=1;
			else if(p2_pos>b+0.02)
				CPU_mov=-1;
			else
				CPU_mov=0;
		}
	else{
			if(p1_pos<b-0.04)
				CPU_mov2=1;
			else if(p1_pos>b+0.02)
				CPU_mov2=-1;
			else
				CPU_mov2=0;
		}
}
void updateCPU(bool a){ //a=true cpu derecha 1, a=false cpu izquierda 2
	float max_ball_pos;
	if(Num_ball_direct(a)==0){
		CPU_mov_cambio(a,0);
	}
	else if(Num_ball_direct(a)==1){
		for(int i=0;i<BM;i++){	
			if(bolas[i].direccion(a)&&bolas[i].ballviva==true){
				CPU_mov_cambio(a,bolas[i].pruebaY);
			}
		}
	}
	else{
		for(int i=0;i<BM;i++){	
			if(bolas[i].direccion(a)&&bolas[i].ballviva==true){
				if(a){
					if(bolas[i].ball_x>=max_ball_pos)
						max_ball_pos=bolas[i].ball_x;		
				}
				else{
					if(bolas[i].ball_x<=max_ball_pos)
						max_ball_pos=bolas[i].ball_x;
				}
			}
		}
		for(int i=0;i<BM;i++){	
			if(bolas[i].ball_x==max_ball_pos&&bolas[i].ballviva==true){
				CPU_mov_cambio(a,bolas[i].pruebaY-0.8);
			}
		}
	}
}
void reiniciar(){
	p1_pos=0;
	p2_pos=0;
	p1_score=0;
	p2_score=0;
	choques=0;
	balls_now=0;
	lastp1_pos=0;
	lastp2_pos=0;
	auxdelay;
	kdelay=true;
	for(int i=0;i<BM;i++){	
		bolas[i].refresh();
		//bolas[i].ballviva=true;
	}
}
void ballupdate(){
	//cout<<" ball_now="<<balls_now<<endl;
	int i=0;
	bool j=true;
	if(kdelay==false){
		if (auxdelay==choques) //para que solo se cumpla una vez la condicion para generar bola si los choques son R;
			kdelay=true;
	}
	if(balls_now==0){
		bolas[0].refresh();
		bolas[0].ballviva=true;
		balls_now=1;
		choques=0;
	}
	else{
		if(balls_now<=BM && choques%R==0 && choques!=0 && kdelay==true && escena!=0){
			i=0;
			j=true;
			for(i=0;i<BM&&j==true;i++){
				if(bolas[i].ballviva==true){
				}	
				else{
					bolas[i].refresh();
					bolas[i].ballviva=true;
					balls_now++;	
					j=false;
					kdelay=false;
					auxdelay=choques+1;
				}
			}	
		}
		else{}
	}
	for(int i=0;i<BM;i++){
		if(bolas[i].ballviva==true)
		bolas[i].ballmovi(true);
	}
}
void display(void)
{
if(GetAsyncKeyState(0x57)==0 && GetAsyncKeyState(0x26)==0 && GetAsyncKeyState(0x53)==0 && GetAsyncKeyState(0x28)==0 && GetAsyncKeyState(0x1B)==0)
	d_select=false;  
	
	glEnable(GL_LIGHT0);

    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

	glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
glDepthFunc(GL_LEQUAL);
glEnable(GL_DEPTH_TEST);
glClearColor(0.02,0.17,0.26,0.0);
glClearDepth(1.0);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glViewport(-60,-340,1400,1400);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(60.0,1.0,1.0,100.0);
glMatrixMode(GL_MODELVIEW);
glTranslatef(0.0,0.0,-16.0);
	if(escena==0){
	glPushMatrix();
	glTranslatef(0,1,-6);
	glRotatef( -45, 1,0, 0 );
	glRotatef( GetTickCount ()/40, 0,0, 1 );
	}	
// Dibujamos P1
glTranslatef(-7,p1_pos,0);
glPushMatrix();
glScalef(P_ancho,P_altura,P_long);
color_player();
glColor3f(Rplayer1, Gplayer1, Bplayer1);
glutSolidCube(1);
glPopMatrix();
glTranslatef(+7,-p1_pos,0);
// Dibujamos P2
glTranslatef(+7,p2_pos,0);
glPushMatrix();
glScalef(P_ancho,P_altura,P_long);
glColor3f(Rplayer2, Gplayer2, Bplayer2);
glutSolidCube(1);
glPopMatrix();
glTranslatef(-7,-p2_pos,0);
// Dibujamos bordes
glTranslatef(0,borde+(P_altura/2)+(B_altura/2),0);
glPushMatrix();
glScalef(B_ancho,B_altura,B_long);
color_borde();
glColor3f(Rborde1, Gborde1, Bborde1);
glutSolidCube(1);
glPopMatrix();
glTranslatef(0,-(borde+(P_altura/2)+(B_altura/2)),0);
glTranslatef(0,-(borde+(P_altura/2)+(B_altura/2)),0);
glPushMatrix();
glScalef(B_ancho,B_altura,B_long);
glColor3f(Rborde2, Gborde2, Bborde2);
glutSolidCube(1);
glPopMatrix();
glTranslatef(0,+(borde+(P_altura/2)+(B_altura/2)),0);
//Dibujamos medio
for(int i=0;i<9;i++){
glTranslatef(0,i-4,-B_long);
glPushMatrix();
glScalef(P_ancho,P_altura/3,P_long);
calc_color_medio(i+1);
glutSolidCube(1);
glPopMatrix();
glTranslatef(0,-(i-4),B_long);
}
//Bola
//glTranslatef(bola1.ball_x2,bola1.ball_y2,0);
if(escena!=0)
scoreupdate();

if(game()){
//cout<<Num_ball_direct(true)<<endl;
if(escena==0||escena==2)
	updateCPU(true);
if(escena==0)
	updateCPU(false);
controlupdate();
//cout<<playerdirec(2)<<endl;
ballupdate();
lastp1_pos=p1_pos;
lastp2_pos=p2_pos;
if(escena==0){
	glRotatef( -GetTickCount ()/40, 0,0, 1 );
	glRotatef( 45, 1,0, 0 );
	glTranslatef(0,-1,6);
	glPopMatrix();
	}
}

else{
	glTranslatef(0,0,P_long+0.3);
	glPushMatrix();
	glScalef(P_altura*4,P_altura,0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(0.05f, 0.0f, 0.00f,1);
	glutSolidCube(1);
	glPopMatrix();
	glTranslatef(0,0,-0.1);
	glBegin(GL_QUADS);
	glColor4f(0.5f,0.5f,0.5f,0.5f);
	glVertex3f(-10,10,0);
	glVertex3f(-10,-10,0);
	glVertex3f(10,-10,0);
	glVertex3f(10,10,0);
	glEnd();
	glTranslatef(0,0,0.1);
	glTranslatef(0,0,0.3);
	if(p1_score>=maxscore)
	letra(-1.3,0.1,"Jugador 1 es el Ganador",1,true);
	else
	letra(-1.3,0.1,"Jugador 2 es el Ganador",1,true);	
letra(-0.8,-0.4,"Reiniciar (Enter)",2,true);
glTranslatef(0,0,-0.3);
glTranslatef(0,0,-(P_long+0.3));
	if(GetAsyncKeyState(0x0D)!=0)
	reiniciar();
//cout<<GetAsyncKeyState(0x0D)<<endl;
}

if(escena==0){ ///menu inicial
	//glRotatef( rotate_y, 0.0, 1.0, 0.0 );
	glTranslatef(0,-2,P_long+0.3);
	glPushMatrix();
	glScalef(P_altura*4,P_altura,0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(0.05f, 0.0f, 0.00f,0.6);
	glutSolidCube(1);
	glPopMatrix();
	
	if(select)
		glTranslatef(-1.6,0.16,0);
	else
		glTranslatef(-1.6,-0.37,0);
	glPushMatrix();
	glRotatef( GetTickCount ()/50, 1,0, 0 );
	//glPushMatrix();
	glRotatef(45, 0,1, 0 );
	glScalef(0.2,0.2,0.2);
	glColor3f(Rplayer2, Gplayer2, Bplayer2);
	glutSolidCube(1);
	glRotatef(45, 0,1, 0 );
	//glPopMatrix();
	glRotatef( -GetTickCount ()/50, 1,0, 0);
	glPopMatrix();
	if(select)
		glTranslatef(+1.6,-0.16,0);
	else
		glTranslatef(+1.6,+0.37,0);
	
	glTranslatef(0,0,0.3);
	letra(-1.3,0.1,"Jugador contra Jugador",1,select);
	letra(-1.3,-0.4,"Jugador contra CPU",1,!select);
	glTranslatef(0,0,-0.3);
	glTranslatef(0,2,-(P_long+0.3));
	if( (GetAsyncKeyState(0x57)!=0 || GetAsyncKeyState(0x26)!=0) && d_select==false ){
		select=!select;
		d_select=true;
	}
	else{
		if((GetAsyncKeyState(0x53)!=0 || GetAsyncKeyState(0x28)!=0) && d_select==false){
		select=!select;
		d_select=true;}
	}
	if(GetAsyncKeyState(0x0D)!=0){
	reiniciar();
	if(select)
		escena=1;
	else
		escena=2;	
	}
}
if(GetAsyncKeyState(0x1B)!=0 && d_select==false){
	if(escena==0)
		exit(EXIT_SUCCESS);
	else{
		escena=0;
		select=true;
		reiniciar();
	}
	d_select=true;
}
glFlush();
glTranslatef(0.0,0.0,16.0);
}

int main(int argc, char ** argv)
{
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
glutInitWindowPosition(120,20);
glutInitWindowSize(1280,720);
glutCreateWindow("OpenPongL");
glEnable(GL_DEPTH_TEST);
if(game())
glutDisplayFunc(display);

glutTimerFunc(valor,tiempo,0);	
glutMainLoop();
return 0;
}
