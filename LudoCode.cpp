#include <windows.h>  // for MS Windows
#include <glut.h>  // GLUT, include glu.h and gl.h
#include <stdlib.h>
#include <math.h>
#include<stdio.h>
#include<time.h>
void drawHomeFinal2();
typedef struct player{
	bool active[4];
	int map[4];	
}Player;

Player p[4];
float h = 0.17f;
float rc[52][2] = {{-0.4, 1.95}, {-0.4, 1.65},  {-0.4, 1.35}, {-0.4, 1.05}, {-0.4, 0.75}, {-0.75, 0.4}, 
{-1.05, 0.4}, {-1.35, 0.4}, {-1.65, 0.4}, {-1.95, 0.4}, {-2.25, 0.4}, {-2.25, 0.0}, {-2.25, -0.4}, {-1.95, -0.4}, 
{-1.65, -0.4}, {-1.35, -0.4}, {-1.05, -0.4}, {-0.75, -0.4}, {-0.4, -0.75}, {-0.4, -1.05},  {-0.4, -1.35}, 
{-0.4, -1.65}, {-0.4, -1.95}, {-0.4, -2.25}, {0.0, -2.25}, {0.4, -2.25}, {0.4, -1.95}, {0.4, -1.65}, {0.4, -1.35}, 
{0.4, -1.05}, {0.4, -0.75}, {0.75, -0.4}, {1.05, -0.4}, {1.35, -0.4}, {1.65, -0.4}, {1.95, -0.4}, {2.25, -0.4}, 
{2.25, 0.0}, {2.25, 0.4}, {1.95, 0.4}, {1.65, 0.4}, {1.35, 0.4}, {1.05, 0.4}, {0.75, 0.4}, {0.4, 0.75}, 
{0.4, 1.05}, {0.4, 1.35}, {0.4, 1.65}, {0.4, 1.95}, {0.4, 2.25}, {0.0, 2.25}, {-0.4, 2.25}};
float home1[5][2] = {{0.0, 1.95}, {0.0, 1.65}, {0.0, 1.35}, {0.0, 1.05}, {0.0, 0.75}};
float home2[5][2] = {{-1.95, 0.0}, {-1.65, 0.0}, {-1.35, 0.0}, {-1.05, 0.0}, {-0.75, 0.0}};
float home3[5][2] = {{0.0, -1.95}, {0.0, -1.65}, {0.0, -1.35}, {0.0, -1.05}, {0.0, -0.75}};
float home4[5][2] = {{1.95, 0.0}, {1.65, 0.0}, {1.35, 0.0}, {1.05, 0.0}, {0.75, 0.0}};
float initPos1[4][2] = {{-1.9, 1.9}, {-1.1, 1.9}, {-1.1, 1.1}, {-1.9, 1.1}};
float initPos2[4][2] = {{-1.9, -1.9}, {-1.1, -1.9}, {-1.1, -1.1}, {-1.9, -1.1}};
float initPos3[4][2] = {{1.9, -1.9}, {1.1, -1.9}, {1.1, -1.1}, {1.9, -1.1}};
float initPos4[4][2] = {{1.9, 1.9}, {1.1, 1.9}, {1.1, 1.1}, {1.9, 1.1}};
int MAP1[52][0];

void display();
char title[] = "Ludo Game";
GLfloat angleCube = 30.0f, anglePyramid = 30.0f, angleCubey = 20.0f;
float x = 2.4f, y = 0.15f;
float base[3] = {0.95f, 0.95f, 0.95f}, side1[3] = {0.6f, 0.196078f, 0.8f} ,side2[3] = {0.196078f, 0.8f, 0.6f}, 
side3[3] = {0.137255f, 0.556863f, 0.419608f}, side4[3] = {0.55f, 0.09f, 0.09f}, lines[3] = {0.0f, 0.0f, 0.0f},
player1[3] = {0.2f, 0.6471f, 0.9216f}, player2[3] = {}, player3[3] = {}, player4[3] = {};
double camera_angle_h = 0;
double camera_angle_v = 0;

int drag_x_origin;
int drag_y_origin;
int dragging = 0;

int dNum, user;
		
void gamePlay();
void gamePlay_user(int sub){
	if(!p[0].active[sub] && (dNum==1 || dNum==6) && MAP1[0][0]== -1){
		p[0].active[sub] = true;
		p[0].map[sub] = 0;
		MAP1[0][0] = 0;
		MAP1[0][1] = sub;
	}
	
	else if(p[0].active[sub]){
		int t = (p[0].map[sub]+dNum)%52;
		if(MAP1[t][0]!=-1){
			MAP1[p[0].map[sub]][0] = -1;
			MAP1[p[0].map[sub]][1] = -1;	
		}
		else{
			p[MAP1[t][0]].map[MAP1[t][1]] = -1;
			p[MAP1[t][0]].active[MAP1[t][1]] = false;
		}
		MAP1[t][0] = 0;
		MAP1[t][1] = sub;
	}	
	glutPostRedisplay();
	
	gamePlay();
}

void gamePlay(){
	int val, maxPlayer, l, j, b, max, k;
	//GLint rand();
	
	for(int i=1;i<4;i++){
//			printf("dfgh");

		scanf("%d", &dNum);
		if(dNum==1||dNum==6&&((!p[i].active[0])||(!p[i].active[1])||(!p[i].active[2])||(!p[i].active[3]))){
			for(int j=0;j<4;j++){
				if(!p[i].active[j]){
					p[i].active[j] = true;
					p[i].map[j] = 13*i;
					MAP1[p[i].map[j]][0] = i;
					MAP1[p[i].map[j]][1] = j;
					//animate(i, j, -1, 13*i);	
					glutPostRedisplay();
					break;
				}
			}
		}
		else{
			//Defensive strategy	
			
			for(k=0;k<4;k++){
				if(p[i].active[k])
					if(MAP1[p[i].map[k]-1][0]!=-1 || MAP1[p[i].map[k]-2][0]!=-1 || MAP1[p[i].map[k]-3][0]!=-1
						|| MAP1[p[i].map[k]-4][0]!=-1 || MAP1[p[i].map[k]-5][0]!=-1 || MAP1[p[i].map[k]-6][0]!=-1){
						MAP1[p[i].map[k]][0] = -1;
						MAP1[p[i].map[k]][1] = -1;	
						int temp = p[i].map[k];
						p[i].map[k] += dNum;
						p[i].map[k] %= 52;
						MAP1[p[i].map[k]][0] = i;
						MAP1[p[i].map[k]][1] = k;
						//animate(i , k, temp, [p[i].map[k]);	
						glutPostRedisplay();
						break;
					}	
			}	
			
			//Aggressive strategy
			if(k==4){
				for(l=0;l<4;l++){
					if(p[i].active[l]){
						int t = (p[i].map[l]+dNum)%52;
						int temp = p[i].map[l];
						if(MAP1[t][0] != -1){
							p[MAP1[t][0]].map[MAP1[t][1]] = -1;
							p[MAP1[t][0]].active[MAP1[t][1]] = false;
						}
						p[i].map[l] += dNum;
						p[i].map[l] %= 52;
						MAP1[p[i].map[l]][0] = i;
						MAP1[p[i].map[l]][1] = l;	
						//animate(i, l, temp, p[i].map[l]);
						glutPostRedisplay();
						break;
					}
				}
			}
			//Fast strategy
			if(l==4){
				max = 0;
				maxPlayer = 0;
				for(int s=0;s<4;s++){	
					if(p[i].active[s]){						//for subplayers of current player
						if(p[i].map[s]<(13*i)){
							val = p[i].map[s] + 51;
						}
						else{
							val = p[i].map[s];
						}
						if(max<val){
							max = val;
							maxPlayer = s;
						}
					}	
				}
				if(max!=0){
					//translate
					p[i].map[maxPlayer] += dNum;
					p[i].map[maxPlayer] %= 52;
					MAP1[p[i].map[maxPlayer]][0] = i;
					MAP1[p[i].map[maxPlayer]][1] = maxPlayer;	
					glutPostRedisplay();
					break;
				}
			}
			//Random strategy
			if(max==0){
				for(int s=0;s<4;s++){	
					if(p[i].active[s]){	
						p[i].map[s] += dNum;
						p[i].map[s] %= 52;					//for subplayers of current player
						MAP1[p[i].map[s]][0] = i;
						MAP1[p[i].map[s]][1] = s;	
						glutPostRedisplay();
						break;
					}	
				}
			}
		}	
	}
//	gamePlay_user(0);
}


void animate(int play_num, int sub_num, int initial, int final){
	
}

void drawLines(){
	
	float div = 0.6f;
	glLoadIdentity();                 // Reset the model-view matrix
   	glTranslatef(0.0f, 0.0f, -7.0f);  // Move right and into the screen
   	glRotatef(angleCube, 1.0f, 0.0f, 0.0f);
   	glRotatef(angleCubey, 0.0f, 1.0f, 0.0f);
   	glRotated(camera_angle_v, 1.0, 0.0, 0.0);
	glRotated(camera_angle_h, 0.0, 1.0, 0.0);
	
	glColor3f(0.0, 0.0, 0.0);
	for(int i =0;i<5;i++){
		glBegin(GL_POINTS);
		glVertex3f(home3[i][0], h, home3[i][1]);
		
		glVertex3f(home4[i][0], h, home4[i][1]);
		glEnd();
	}
   	glLineWidth(2.5); 
	glColor3f(lines[0], lines[1], lines[2]);
	
	glBegin(GL_LINES);
	float y=0.16f;
	glVertex3f( -div, y, -x);
	glVertex3f( -div, y, x);
	glVertex3f( -div+0.4f, y, -x);
	glVertex3f( -div+0.4f, y, -div);
	glVertex3f( -div+0.8f, y, -x);
	glVertex3f( -div+0.8f, y, -div);
	
	glVertex3f( div, y, x);
	glVertex3f( div, y, -x);
	glVertex3f( div-0.4f, y, x);
	glVertex3f( div-0.4f, y, div);
	glVertex3f( div-0.8f, y, x);
	glVertex3f( div-0.8f, y, div);
	
	glVertex3f( -div, y, x);
	glVertex3f( -div, y, div);
	
	glVertex3f( x, y, -div);
	glVertex3f( div, y, -div);
	
	glVertex3f( div, y, -x);
	glVertex3f( div, y, -div);

	glVertex3f( -x, y, div);
	glVertex3f( -div, y, div);
	
	glVertex3f( -x, y, -div);
	glVertex3f( x, y, -div);
	glVertex3f( -x, y, -div+0.4f);
	glVertex3f( -div, y, -div+0.4f);
	glVertex3f( -x, y, -div+0.8f);
	glVertex3f( -div, y, -div+0.8f);
	
	glVertex3f( x, y, div);
	glVertex3f( -x, y, div);
	glVertex3f( x, y, div-0.4f);
	glVertex3f( div, y, div-0.4f);
	glVertex3f( x, y, div-0.8f);
	glVertex3f( div, y, div-0.8f);
	
	glEnd();
	
	glBegin(GL_LINES);
	for(int i=0;i<6;i++){
		glVertex3f(div, y, x);
		glVertex3f(div-1.2f, y, x);
		x-=0.3f;
	}
	for(int i=0;i<6;i++){
		glVertex3f(-x, y, div);
		glVertex3f(-x, y, div-1.2f);
		x+=0.3f;
	}
	for(int i=0;i<6;i++){
		glVertex3f(x, y, div);
		glVertex3f(x, y, div-1.2f);
		x-=0.3f;
	}
	for(int i=0;i<6;i++){
		glVertex3f(div, y, -x);
		glVertex3f(div-1.2f, y, -x);
		x+=0.3f;
	}
	glEnd();
	glFlush();	
}

void drawCubes(){
	float y1 = y+0.01;
	glLoadIdentity();                 // Reset the model-view matrix
   	glTranslatef(0.0f, 0.0f, -7.0f);  // Move right and into the screen
   	glRotatef(angleCube, 1.0f, 0.0f, 0.0f);
   	glRotatef(angleCubey, 0.0f, 1.0f, 0.0f);
   	glRotated(camera_angle_v, 1.0, 0.0, 0.0);
	glRotated(camera_angle_h, 0.0, 1.0, 0.0);
	
	glBegin(GL_QUADS);
	//side1
	glColor3f(side1[0], side1[1], side1[2]);
	glVertex3f(-1.6f, y1, x-0.8f);
	glVertex3f(-1.6f, y1, x-0.2f);
	glVertex3f(-2.2f, y1, x-0.2f);
	glVertex3f(-2.2f, y1, x-0.8f);
	
	glVertex3f(-1.4f, y1, x-0.2f);
	glVertex3f(-1.4f, y1, x-0.8f);
	glVertex3f(-0.8f, y1, x-0.8f);
	glVertex3f(-0.8f, y1, x-0.2f);
	
	glVertex3f(-2.2f, y1, x-1.0f);
	glVertex3f(-2.2f, y1, x-1.6f);
	glVertex3f(-1.6f, y1, x-1.6f);
	glVertex3f(-1.6f, y1, x-1.0f);
	
	glVertex3f(-1.4f, y1, x-1.0f);
	glVertex3f(-1.4f, y1, x-1.6f);
	glVertex3f(-0.8f, y1, x-1.6f);
	glVertex3f(-0.8f, y1, x-1.0f);
	//side2
	glColor3f(side2[0], side2[1], side2[2]);
	glVertex3f(1.4f, y1, x-0.2f);
	glVertex3f(1.4f, y1, x-0.8f);
	glVertex3f(0.8f, y1, x-0.8f);
	glVertex3f(0.8f, y1, x-0.2f);
	
	glVertex3f(2.2f, y1, x-0.2f);
	glVertex3f(2.2f, y1, x-0.8f);
	glVertex3f(1.6f, y1, x-0.8f);
	glVertex3f(1.6f, y1, x-0.2f);
	
	glVertex3f(2.2f, y1, x-1.0f);
	glVertex3f(2.2f, y1, x-1.6f);
	glVertex3f(1.6f, y1, x-1.6f);
	glVertex3f(1.6f, y1, x-1.0f);
	
	glVertex3f(1.4f, y1, x-1.0f);
	glVertex3f(1.4f, y1, x-1.6f);
	glVertex3f(0.8f, y1, x-1.6f);
	glVertex3f(0.8f, y1, x-1.0f);
	//side4
	glColor3f(side4[0], side4[1], side4[2]);
	glVertex3f(-1.6f, y1, -x+0.8f);
	glVertex3f(-1.6f, y1, -x+0.2f);
	glVertex3f(-2.2f, y1, -x+0.2f);
	glVertex3f(-2.2f, y1, -x+0.8f);
	
	glVertex3f(-1.4f, y1, -x+0.2f);
	glVertex3f(-1.4f, y1, -x+0.8f);
	glVertex3f(-0.8f, y1, -x+0.8f);
	glVertex3f(-0.8f, y1, -x+0.2f);
	
	glVertex3f(-2.2f, y1, -x+1.0f);
	glVertex3f(-2.2f, y1, -x+1.6f);
	glVertex3f(-1.6f, y1, -x+1.6f);
	glVertex3f(-1.6f, y1, -x+1.0f);
	
	glVertex3f(-1.4f, y1, -x+1.0f);
	glVertex3f(-1.4f, y1, -x+1.6f);
	glVertex3f(-0.8f, y1, -x+1.6f);
	glVertex3f(-0.8f, y1, -x+1.0f);
	
	//side3
	glColor3f(side3[0], side3[1], side3[2]);
	glVertex3f(1.4f, y1, -x+0.2f);
	glVertex3f(1.4f, y1, -x+0.8f);
	glVertex3f(0.8f, y1, -x+0.8f);
	glVertex3f(0.8f, y1, -x+0.2f);
	
	glVertex3f(2.2f, y1, -x+0.2f);
	glVertex3f(2.2f, y1, -x+0.8f);
	glVertex3f(1.6f, y1, -x+0.8f);
	glVertex3f(1.6f, y1, -x+0.2f);
	
	glVertex3f(2.2f, y1, -x+1.0f);
	glVertex3f(2.2f, y1, -x+1.6f);
	glVertex3f(1.6f, y1, -x+1.6f);
	glVertex3f(1.6f, y1, -x+1.0f);
	
	glVertex3f(1.4f, y1, -x+1.0f);
	glVertex3f(1.4f, y1, -x+1.6f);
	glVertex3f(0.8f, y1, -x+1.6f);
	glVertex3f(0.8f, y1, -x+1.0f);
	
	glEnd();
	glFlush();
}
void drawHomeFinal(){
	float y1 = y+0.05f, y2 = y1+0.25f;
	int i=0, k=0;
	glLoadIdentity();                 // Reset the model-view matrix
	glTranslatef(0.0f, 0.0f, -7.0f);  // Move right and into the screen
	glRotatef(angleCube, 1.0f, 0.0f, 0.0f);
	glRotatef(angleCubey, 0.0f, 1.0f, 0.0f);
	glRotated(camera_angle_v, 1.0, 0.0, 0.0);
	glRotated(camera_angle_h, 0.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	
	glBegin(GL_QUADS);
	
	glVertex3f(-0.2, y1, 0.6);
	glVertex3f(-0.2, y1+0.2, 0.6);
	glVertex3f(-0.2, y1+0.2, 0.2);
	glVertex3f(-0.2, y1, 0.2);
	
	glVertex3f(0.2, y1, 0.6);
	glVertex3f(0.2, y1+0.2, 0.6);
	glVertex3f(0.2, y1+0.2, 0.2);
	glVertex3f(0.2, y1, 0.2);
	
	glVertex3f(-0.2, y1+0.2, 0.6);
	glVertex3f(0.0, y1+0.3, 0.6);
	glVertex3f(0.0, y1+0.3, 0.2);
	glVertex3f(-0.2, y1+0.2, 0.2);
	
	glVertex3f(0.2, y1+0.2, 0.6);
	glVertex3f(0.0, y1+0.3, 0.6);
	glVertex3f(0.0, y1+0.3, 0.2);
	glVertex3f(0.2, y1+0.2, 0.2);
	
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(-0.2, y1, -0.6);
	glVertex3f(-0.2, y1+0.2, -0.6);
	glVertex3f(-0.2, y1+0.2, -0.2);
	glVertex3f(-0.2, y1, -0.2);
	
	glVertex3f(0.2, y1, -0.6);
	glVertex3f(0.2, y1+0.2, -0.6);
	glVertex3f(0.2, y1+0.2, -0.2);
	glVertex3f(0.2, y1, -0.2);
	
	glVertex3f(-0.2, y1+0.2, -0.6);
	glVertex3f(0.0, y1+0.3, -0.6);
	glVertex3f(0.0, y1+0.3, -0.2);
	glVertex3f(-0.2, y1+0.2, -0.2);
	
	glVertex3f(0.2, y1+0.2, -0.6);
	glVertex3f(0.0, y1+0.3, -0.6);
	glVertex3f(0.0, y1+0.3, -0.2);
	glVertex3f(0.2, y1+0.2, -0.2);
	
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.6, y1, -0.2);
	glVertex3f(0.6, y1+0.2, -0.2);
	glVertex3f(0.2, y1+0.2, -0.2);
	glVertex3f(0.2, y1, -0.2);
	
	glVertex3f(0.6, y1, 0.2);
	glVertex3f(0.6, y1+0.2, 0.2);
	glVertex3f(0.2, y1+0.2, 0.2);
	glVertex3f(0.2, y1, 0.2);
	
	glVertex3f(0.6, y1+0.2, -0.2);
	glVertex3f(0.6, y1+0.3, 0.0);
	glVertex3f(0.2, y1+0.3, 0.0);
	glVertex3f(0.2, y1+0.2, -0.2);
	
	glVertex3f(0.6, y1+0.2, 0.2);
	glVertex3f(0.6, y1+0.3, 0.0);
	glVertex3f(0.2, y1+0.3, 0.0);
	glVertex3f(0.2, y1+0.2, 0.2);
	
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-0.6, y1, -0.2);
	glVertex3f(-0.6, y1+0.2, -0.2);
	glVertex3f(-0.2, y1+0.2, -0.2);
	glVertex3f(-0.2, y1, -0.2);
	
	glVertex3f(-0.6, y1, 0.2);
	glVertex3f(-0.6, y1+0.2, 0.2);
	glVertex3f(-0.2, y1+0.2, 0.2);
	glVertex3f(-0.2, y1, 0.2);
	
	glVertex3f(-0.6, y1+0.2, -0.2);
	glVertex3f(-0.6, y1+0.3, 0.0);
	glVertex3f(-0.2, y1+0.3, 0.0);
	glVertex3f(-0.2, y1+0.2, -0.2);
	
	glVertex3f(-0.6, y1+0.2, 0.2);
	glVertex3f(-0.6, y1+0.3, 0.0);
	glVertex3f(-0.2, y1+0.3, 0.0);
	glVertex3f(-0.2, y1+0.2, 0.2);
glEnd();
	glBegin(GL_POLYGON);
	//p1
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(-0.2, y1, 0.2);
	glVertex3f(-0.2, y1+0.2, 0.2);
	glVertex3f(0.0, y1+0.3, 0.2);
	glVertex3f(0.2, y1+0.2, 0.2);
	glVertex3f(0.2, y1, 0.2);
	glEnd();
	//p2
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(-0.2, y1, -0.2);
	glVertex3f(-0.2, y1+0.2, -0.2);
	glVertex3f(-0.2, y1+0.3, 0.0);
	glVertex3f(-0.2, y1+0.2, 0.2);
	glVertex3f(-0.2, y1, 0.2);
glEnd();
	//p3
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(-0.2, y1, -0.2);
	glVertex3f(-0.2, y1+0.2, -0.2);
	glVertex3f(0.0, y1+0.3, -0.2);
	glVertex3f(0.2, y1+0.2, -0.2);
	glVertex3f(0.2, y1, -0.2);
	glEnd();
	//p4
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(0.2, y1, -0.2);
	glVertex3f(0.2, y1+0.2, -0.2);
	glVertex3f(0.2, y1+0.3, 0.0);
	glVertex3f(0.2, y1+0.2, 0.2);
	glVertex3f(0.2, y1, 0.2);
	glEnd();
	drawHomeFinal2();
}

void drawHomeFinal2(){
	glLoadIdentity();                 // Reset the model-view matrix
   	glTranslatef(0.0f, 0.0f, -7.0f);  // Move right and into the screen
   	glRotatef(angleCube, 1.0f, 0.0f, 0.0f);
   	glRotatef(angleCubey, 0.0f, 1.0f, 0.0f);
   	glRotated(camera_angle_v, 1.0, 0.0, 0.0);
	glRotated(camera_angle_h, 0.0, 1.0, 0.0);
	float y1 = y+0.01;
	glBegin(GL_QUADS);
	glColor3f(side1[0], side1[1], side1[2]);
	glVertex3f(-0.2f, y1, 0.6);
	glVertex3f(-0.6f, y1, 0.6f);
	glVertex3f(-0.6f, y1+0.2, 0.6f);
	glVertex3f(-0.2f, y1+0.2, 0.6f);
	
	glVertex3f(0.2f, y1, 0.6);
	glVertex3f(0.6f, y1, 0.6f);
	glVertex3f(0.6f, y1+0.2, 0.6f);
	glVertex3f(0.2f, y1+0.2, 0.6f);
	
	glVertex3f(-0.2f, y1+0.2, 0.6);
	glVertex3f(-0.6f, y1+0.2, 0.6f);
	glVertex3f(-0.6f, y1+0.3, 0.6f);
	glVertex3f(0.0f, y1+0.3, 0.6f);
	
	glVertex3f(0.2f, y1+0.2, 0.6);
	glVertex3f(0.6f, y1+0.2, 0.6f);
	glVertex3f(0.6f, y1+0.3, 0.6f);
	glVertex3f(0.0f, y1+0.3, 0.6f);

	glColor3f(side2[0], side2[1], side2[2]);
	glVertex3f(0.6f, y1, -0.2);
	glVertex3f(0.6f, y1, -0.6f);
	glVertex3f(0.6f, y1+0.2, -0.6f);
	glVertex3f(0.6f, y1+0.2, -0.2f);
	
	glVertex3f(0.6f, y1, 0.2);
	glVertex3f(0.6f, y1, 0.6f);
	glVertex3f(0.6f, y1+0.2, 0.6f);
	glVertex3f(0.6f, y1+0.2, 0.2f);
	
	glVertex3f(0.6f, y1+0.2, -0.2);
	glVertex3f(0.6f, y1+0.2, -0.6f);
	glVertex3f(0.6f, y1+0.3, -0.6f);
	glVertex3f(0.6f, y1+0.3, 0.0f);
	
	glVertex3f(0.6f, y1+0.2, 0.2);
	glVertex3f(0.6f, y1+0.2, 0.6f);
	glVertex3f(0.6f, y1+0.3, 0.6f);
	glVertex3f(0.6f, y1+0.3, 0.0f);

	glColor3f(side3[0], side3[1], side3[2]);
	glVertex3f(-0.2f, y1, -0.6);
	glVertex3f(-0.6f, y1, -0.6f);
	glVertex3f(-0.6f, y1+0.2, -0.6f);
	glVertex3f(-0.2f, y1+0.2, -0.6f);
	
	glVertex3f(0.2f, y1, -0.6);
	glVertex3f(0.6f, y1, -0.6f);
	glVertex3f(0.6f, y1+0.2, -0.6f);
	glVertex3f(0.2f, y1+0.2, -0.6f);
	
	glVertex3f(-0.2f, y1+0.2, -0.6);
	glVertex3f(-0.6f, y1+0.2, -0.6f);
	glVertex3f(-0.6f, y1+0.3, -0.6f);
	glVertex3f(0.0f, y1+0.3, -0.6f);
	
	glVertex3f(0.2f, y1+0.2, -0.6);
	glVertex3f(0.6f, y1+0.2, -0.6f);
	glVertex3f(0.6f, y1+0.3, -0.6f);
	glVertex3f(0.0f, y1+0.3, -0.6f);
	
	glColor3f(side4[0], side4[1], side4[2]);
	glVertex3f(-0.6f, y1, -0.2);
	glVertex3f(-0.6f, y1, -0.6f);
	glVertex3f(-0.6f, y1+0.2, -0.6f);
	glVertex3f(-0.6f, y1+0.2, -0.2f);
	
	glVertex3f(-0.6f, y1, 0.2);
	glVertex3f(-0.6f, y1, 0.6f);
	glVertex3f(-0.6f, y1+0.2, 0.6f);
	glVertex3f(-0.6f, y1+0.2, 0.2f);
	
	glVertex3f(-0.6f, y1+0.2, -0.2);
	glVertex3f(-0.6f, y1+0.2, -0.6f);
	glVertex3f(-0.6f, y1+0.3, -0.6f);
	glVertex3f(-0.6f, y1+0.3, 0.0f);
	
	glVertex3f(-0.6f, y1+0.2, 0.2);
	glVertex3f(-0.6f, y1+0.2, 0.6f);
	glVertex3f(-0.6f, y1+0.3, 0.6f);
	glVertex3f(-0.6f, y1+0.3, 0.0f);

	glEnd();
	
	glBegin(GL_TRIANGLES);
	glColor3f(side1[0], side1[1], side1[2]);
	glVertex3f(-0.7f, y1+0.3, 0.7);
	glVertex3f(0.7f, y1+0.3, 0.7);
	glVertex3f(0.0f, y1+0.6, 0.0);

	glColor3f(side2[0], side2[1], side2[2]);
	glVertex3f(0.7f, y1+0.3, -0.7);
	glVertex3f(0.7f, y1+0.3, 0.7);
	glVertex3f(0.0f, y1+0.6, 0.0);

	glColor3f(side3[0], side3[1], side3[2]);
	glVertex3f(-0.7f, y1+0.3, -0.7);
	glVertex3f(0.7f, y1+0.3, -0.7);
	glVertex3f(0.0f, y1+0.6, 0.0);

	glColor3f(side4[0], side4[1], side4[2]);
	glVertex3f(-0.7f, y1+0.3, -0.7);
	glVertex3f(-0.7f, y1+0.3, 0.7);
	glVertex3f(0.0f, y1+0.6, 0.0);
	glEnd();
}

void drawHomeLines(){
	glLoadIdentity();                 // Reset the model-view matrix
   	glTranslatef(0.0f, 0.0f, -7.0f);  // Move right and into the screen
   	glRotatef(angleCube, 1.0f, 0.0f, 0.0f);
   	glRotatef(angleCubey, 0.0f, 1.0f, 0.0f);
   	glRotated(camera_angle_v, 1.0, 0.0, 0.0);
	glRotated(camera_angle_h, 0.0, 1.0, 0.0);
	float y1 = y+0.01;
	
	//Yellow path
	glBegin(GL_QUADS);
	glColor3f(side1[0], side1[1], side1[2]);
	glVertex3f(-0.2f, y1, x-0.3f);
	glVertex3f(-0.2f, y1, x-0.6f);
	glVertex3f(-0.6f, y1, x-0.6f);
	glVertex3f(-0.6f, y1, x-0.3f);
	
	glVertex3f(0.2f, y1, x-0.3f);
	glVertex3f(0.2f, y1, x-1.8f);
	glVertex3f(-0.2f, y1, x-1.8f);
	glVertex3f(-0.2f, y1, x-0.3f);
	
	glEnd();
	glFlush();
	
	//Pink path
	glBegin(GL_QUADS);
	glColor3f(side3[0], side3[1], side3[2]);
	glVertex3f(0.2f, y1, -x+0.3f);
	glVertex3f(0.2f, y1, -x+0.6f);
	glVertex3f(0.6f, y1, -x+0.6f);
	glVertex3f(0.6f, y1, -x+0.3f);
	
	glVertex3f(0.2f, y1, -x+0.3f);
	glVertex3f(0.2f, y1, -x+1.8f);
	glVertex3f(-0.2f, y1, -x+1.8f);
	glVertex3f(-0.2f, y1, -x+0.3f);
	
	glVertex3f(0.2f, y1, -x+1.5f);
	
	glVertex3f(-0.2f, y1, -x+1.5f);
	glEnd();
	glFlush();
	
	//Orange path
	glBegin(GL_QUADS);
	glColor3f(side4[0], side4[1], side4[2]);
	glVertex3f(-x+0.6f, y1, -0.2);
	glVertex3f(-x+0.6f, y1, -0.6);
	glVertex3f(-x+0.3f, y1, -0.6);
	glVertex3f(-x+0.3f, y1, -0.2);
	
	
	glVertex3f(-x+0.3f, y1, 0.2);
	glVertex3f(-x+0.3f, y1, -0.2);
	
	glVertex3f(-x+1.8f, y1, -0.2);
	glVertex3f(-x+1.8f, y1, 0.2);
	
	glEnd();
	glFlush();
	
	
	//blue path
	glBegin(GL_QUADS);
	glColor3f(side2[0], side2[1], side2[2]);
	glVertex3f(x-0.6f, y1, 0.2);
	glVertex3f(x-0.6f, y1, 0.6);
	glVertex3f(x-0.3f, y1, 0.6);
	glVertex3f(x-0.3f, y1, 0.2);
	
	glVertex3f(x-0.3f, y1, 0.2);
	glVertex3f(x-0.3f, y1, -0.2);
	glVertex3f(x-1.8f, y1, -0.2);
	glVertex3f(x-1.8f, y1, 0.2);
	
	glEnd();
	glFlush();
	
}

void drawSafeZones(){
	float y1 = y+0.01;
	glLoadIdentity();                 // Reset the model-view matrix
	glTranslatef(0.0f, 0.0f, -7.0f);  // Move right and into the screen
	glRotatef(angleCube, 1.0f, 0.0f, 0.0f);
	glRotatef(angleCubey, 0.0f, 1.0f, 0.0f);	
	glRotated(camera_angle_v, 1.0, 0.0, 0.0);
	glRotated(camera_angle_h, 0.0, 1.0, 0.0);
	
//	glPolygonMode(GL_TRIANGLES, GL_LINE);
	glBegin(GL_TRIANGLES);
	//
	glVertex3f(x-1.87f, y1, x-0.81);	
	glVertex3f(x-2.13f, y1, x-0.81);
	glVertex3f(x-2.0f, y1, x-0.64);

	glVertex3f(x-2.0f, y1, x-0.86);
	glVertex3f(x-1.87f, y1, x-0.69);	
	glVertex3f(x-2.13f, y1, x-0.69);
	//
	glVertex3f(-x+1.87f, y1, -x+0.81);	
	glVertex3f(-x+2.13f, y1, -x+0.81);
	glVertex3f(-x+2.0f, y1, -x+0.64);

	glVertex3f(-x+2.0f, y1, -x+0.86);
	glVertex3f(-x+1.87f, y1, -x+0.69);	
	glVertex3f(-x+2.13f, y1, -x+0.69);
	//
	glVertex3f(x-0.81, y1, -x+1.87f);	
	glVertex3f(x-0.81, y1, -x+2.13f);
	glVertex3f(x-0.64, y1, -x+2.0f);

	glVertex3f(x-0.86, y1, -x+2.0f);
	glVertex3f(x-0.69, y1, -x+1.87f);	
	glVertex3f(x-0.69, y1, -x+2.13f);
	//
	glVertex3f(-x+0.81, y1, x-1.87f);	
	glVertex3f(-x+0.81, y1, x-2.13f);
	glVertex3f(-x+0.64, y1, x-2.0f);

	glVertex3f(-x+0.86, y1, x-2.0f);
	glVertex3f(-x+0.69, y1, x-1.87f);	
	glVertex3f(-x+0.69, y1, x-2.13f);
	glEnd();
	glFlush();	
}

void drawPlayers(){
	float y1 = y+0.02f, y2 = y1+0.25f;
	glLoadIdentity();                 // Reset the model-view matrix
   glTranslatef(0.0f, 0.0f, -7.0f);  // Move right and into the screen
   glRotatef(angleCube, 1.0f, 0.0f, 0.0f);
   glRotatef(angleCubey, 0.0f, 1.0f, 0.0f);

   	glRotated(camera_angle_v, 1.0, 0.0, 0.0);
	glRotated(camera_angle_h, 0.0, 1.0, 0.0);
	
	//yellow
	glColor3f(player1[0], player1[1], player1[2]);
	for(int i=0;i<4;i++){
		for(int k = 0;k<4;k++){
			if(!p[i].active[k]){
		//		printf("%d  %d\n", i, k);
				if(i==0){
					glBegin(GL_QUADS);
					glVertex3f(initPos1[k][0]-0.125, y1, initPos1[k][1]+0.125);
					glVertex3f(initPos1[k][0]-0.125, y1, initPos1[k][1]-0.125);	
					glVertex3f(initPos1[k][0]+0.125, y1, initPos1[k][1]-0.125);
					glVertex3f(initPos1[k][0]+0.125, y1, initPos1[k][1]+0.125);
				
					//upperface
					glVertex3f(initPos1[k][0]-0.05, y2, initPos1[k][1]+0.05);
					glVertex3f(initPos1[k][0]-0.05, y2, initPos1[k][1]-0.05);	
					glVertex3f(initPos1[k][0]+0.05, y2, initPos1[k][1]-0.05);
					glVertex3f(initPos1[k][0]+0.05, y2, initPos1[k][1]+0.05);
					
					//right
					glVertex3f(initPos1[k][0]-0.125, y1, initPos1[k][1]+0.125);
					glVertex3f(initPos1[k][0]-0.125, y1, initPos1[k][1]-0.125);	
					glVertex3f(initPos1[k][0]-0.05, y2, initPos1[k][1]-0.05);	
					glVertex3f(initPos1[k][0]-0.05, y2, initPos1[k][1]+0.05);
					
					//front
					glVertex3f(initPos1[k][0]-0.125, y1, initPos1[k][1]+0.125);
					glVertex3f(initPos1[k][0]-0.05, y2, initPos1[k][1]+0.05);
					glVertex3f(initPos1[k][0]+0.05, y2, initPos1[k][1]+0.05);
					glVertex3f(initPos1[k][0]+0.125, y1, initPos1[k][1]+0.125);
				
					//left
					glVertex3f(initPos1[k][0]+0.125, y1, initPos1[k][1]+0.125);
					glVertex3f(initPos1[k][0]+0.125, y1, initPos1[k][1]-0.125);
					glVertex3f(initPos1[k][0]+0.05, y2, initPos1[k][1]-0.05);
					glVertex3f(initPos1[k][0]+0.05, y2, initPos1[k][1]+0.05);	
				
					//back
					glVertex3f(initPos1[k][0]-0.125, y1, initPos1[k][1]-0.125);	
					glVertex3f(initPos1[k][0]+0.125, y1, initPos1[k][1]-0.125);
					glVertex3f(initPos1[k][0]+0.05, y2, initPos1[k][1]-0.05);
					glVertex3f(initPos1[k][0]-0.05, y2, initPos1[k][1]-0.05);
					glEnd();
				}
				if(i==1){
					glBegin(GL_QUADS);
					glVertex3f(initPos2[k][0]-0.125, y1, initPos2[k][1]+0.125);
					glVertex3f(initPos2[k][0]-0.125, y1, initPos2[k][1]-0.125);	
					glVertex3f(initPos2[k][0]+0.125, y1, initPos2[k][1]-0.125);
					glVertex3f(initPos2[k][0]+0.125, y1, initPos2[k][1]+0.125);
				
					//upperface
					glVertex3f(initPos2[k][0]-0.05, y2, initPos2[k][1]+0.05);
					glVertex3f(initPos2[k][0]-0.05, y2, initPos2[k][1]-0.05);	
					glVertex3f(initPos2[k][0]+0.05, y2, initPos2[k][1]-0.05);
					glVertex3f(initPos2[k][0]+0.05, y2, initPos2[k][1]+0.05);
					
					//right
					glVertex3f(initPos2[k][0]-0.125, y1, initPos2[k][1]+0.125);
					glVertex3f(initPos2[k][0]-0.125, y1, initPos2[k][1]-0.125);	
					glVertex3f(initPos2[k][0]-0.05, y2, initPos2[k][1]-0.05);	
					glVertex3f(initPos2[k][0]-0.05, y2, initPos2[k][1]+0.05);
					
					//front
					glVertex3f(initPos2[k][0]-0.125, y1, initPos2[k][1]+0.125);
					glVertex3f(initPos2[k][0]-0.05, y2, initPos2[k][1]+0.05);
					glVertex3f(initPos2[k][0]+0.05, y2, initPos2[k][1]+0.05);
					glVertex3f(initPos2[k][0]+0.125, y1, initPos2[k][1]+0.125);
				
					//left
					glVertex3f(initPos2[k][0]+0.125, y1, initPos2[k][1]+0.125);
					glVertex3f(initPos2[k][0]+0.125, y1, initPos2[k][1]-0.125);
					glVertex3f(initPos2[k][0]+0.05, y2, initPos2[k][1]-0.05);
					glVertex3f(initPos2[k][0]+0.05, y2, initPos2[k][1]+0.05);	
				
					//back
					glVertex3f(initPos2[k][0]-0.125, y1, initPos2[k][1]-0.125);	
					glVertex3f(initPos2[k][0]+0.125, y1, initPos2[k][1]-0.125);
					glVertex3f(initPos2[k][0]+0.05, y2, initPos2[k][1]-0.05);
					glVertex3f(initPos2[k][0]-0.05, y2, initPos2[k][1]-0.05);
					glEnd();
				}
				if(i==2){
					glBegin(GL_QUADS);
					glVertex3f(initPos3[k][0]-0.125, y1, initPos3[k][1]+0.125);
					glVertex3f(initPos3[k][0]-0.125, y1, initPos3[k][1]-0.125);	
					glVertex3f(initPos3[k][0]+0.125, y1, initPos3[k][1]-0.125);
					glVertex3f(initPos3[k][0]+0.125, y1, initPos3[k][1]+0.125);
				
					//upperface
					glVertex3f(initPos3[k][0]-0.05, y2, initPos3[k][1]+0.05);
					glVertex3f(initPos3[k][0]-0.05, y2, initPos3[k][1]-0.05);	
					glVertex3f(initPos3[k][0]+0.05, y2, initPos3[k][1]-0.05);
					glVertex3f(initPos3[k][0]+0.05, y2, initPos3[k][1]+0.05);
					
					//right
					glVertex3f(initPos3[k][0]-0.125, y1, initPos3[k][1]+0.125);
					glVertex3f(initPos3[k][0]-0.125, y1, initPos3[k][1]-0.125);	
					glVertex3f(initPos3[k][0]-0.05, y2, initPos3[k][1]-0.05);	
					glVertex3f(initPos3[k][0]-0.05, y2, initPos3[k][1]+0.05);
					
					//front
					glVertex3f(initPos3[k][0]-0.125, y1, initPos3[k][1]+0.125);
					glVertex3f(initPos3[k][0]-0.05, y2, initPos3[k][1]+0.05);
					glVertex3f(initPos3[k][0]+0.05, y2, initPos3[k][1]+0.05);
					glVertex3f(initPos3[k][0]+0.125, y1, initPos3[k][1]+0.125);
				
					//left
					glVertex3f(initPos3[k][0]+0.125, y1, initPos3[k][1]+0.125);
					glVertex3f(initPos3[k][0]+0.125, y1, initPos3[k][1]-0.125);
					glVertex3f(initPos3[k][0]+0.05, y2, initPos3[k][1]-0.05);
					glVertex3f(initPos3[k][0]+0.05, y2, initPos3[k][1]+0.05);	
				
					//back
					glVertex3f(initPos3[k][0]-0.125, y1, initPos3[k][1]-0.125);	
					glVertex3f(initPos3[k][0]+0.125, y1, initPos3[k][1]-0.125);
					glVertex3f(initPos3[k][0]+0.05, y2, initPos3[k][1]-0.05);
					glVertex3f(initPos3[k][0]-0.05, y2, initPos3[k][1]-0.05);
					glEnd();
				}
				if(i==3){
					glBegin(GL_QUADS);
					glVertex3f(initPos4[k][0]-0.125, y1, initPos4[k][1]+0.125);
					glVertex3f(initPos4[k][0]-0.125, y1, initPos4[k][1]-0.125);	
					glVertex3f(initPos4[k][0]+0.125, y1, initPos4[k][1]-0.125);
					glVertex3f(initPos4[k][0]+0.125, y1, initPos4[k][1]+0.125);
				
					//upperface
					glVertex3f(initPos4[k][0]-0.05, y2, initPos4[k][1]+0.05);
					glVertex3f(initPos4[k][0]-0.05, y2, initPos4[k][1]-0.05);	
					glVertex3f(initPos4[k][0]+0.05, y2, initPos4[k][1]-0.05);
					glVertex3f(initPos4[k][0]+0.05, y2, initPos4[k][1]+0.05);
					
					//right
					glVertex3f(initPos4[k][0]-0.125, y1, initPos4[k][1]+0.125);
					glVertex3f(initPos4[k][0]-0.125, y1, initPos4[k][1]-0.125);	
					glVertex3f(initPos4[k][0]-0.05, y2, initPos4[k][1]-0.05);	
					glVertex3f(initPos4[k][0]-0.05, y2, initPos4[k][1]+0.05);
					
					//front
					glVertex3f(initPos4[k][0]-0.125, y1, initPos4[k][1]+0.125);
					glVertex3f(initPos4[k][0]-0.05, y2, initPos4[k][1]+0.05);
					glVertex3f(initPos4[k][0]+0.05, y2, initPos4[k][1]+0.05);
					glVertex3f(initPos4[k][0]+0.125, y1, initPos4[k][1]+0.125);
				
					//left
					glVertex3f(initPos4[k][0]+0.125, y1, initPos4[k][1]+0.125);
					glVertex3f(initPos4[k][0]+0.125, y1, initPos4[k][1]-0.125);
					glVertex3f(initPos4[k][0]+0.05, y2, initPos4[k][1]-0.05);
					glVertex3f(initPos4[k][0]+0.05, y2, initPos4[k][1]+0.05);	
				
					//back
					glVertex3f(initPos4[k][0]-0.125, y1, initPos4[k][1]-0.125);	
					glVertex3f(initPos4[k][0]+0.125, y1, initPos4[k][1]-0.125);
					glVertex3f(initPos4[k][0]+0.05, y2, initPos4[k][1]-0.05);
					glVertex3f(initPos4[k][0]-0.05, y2, initPos4[k][1]-0.05);
					glEnd();
				}
			}
			else{
				glBegin(GL_QUADS);
				glVertex3f(rc[p[i].map[k]][0]-0.125, y1, rc[p[i].map[k]][1]+0.125);
				glVertex3f(rc[p[i].map[k]][0]-0.125, y1, rc[p[i].map[k]][1]-0.125);	
				glVertex3f(rc[p[i].map[k]][0]+0.125, y1, rc[p[i].map[k]][1]-0.125);
				glVertex3f(rc[p[i].map[k]][0]+0.125, y1, rc[p[i].map[k]][1]+0.125);
			
				//upperface
				glVertex3f(rc[p[i].map[k]][0]-0.05, y2, rc[p[i].map[k]][1]+0.05);
				glVertex3f(rc[p[i].map[k]][0]-0.05, y2, rc[p[i].map[k]][1]-0.05);	
				glVertex3f(rc[p[i].map[k]][0]+0.05, y2, rc[p[i].map[k]][1]-0.05);
				glVertex3f(rc[p[i].map[k]][0]+0.05, y2, rc[p[i].map[k]][1]+0.05);
				
				//right
				glVertex3f(rc[p[i].map[k]][0]-0.125, y1, rc[p[i].map[k]][1]+0.125);
				glVertex3f(rc[p[i].map[k]][0]-0.125, y1, rc[p[i].map[k]][1]-0.125);	
				glVertex3f(rc[p[i].map[k]][0]-0.05, y2, rc[p[i].map[k]][1]-0.05);	
				glVertex3f(rc[p[i].map[k]][0]-0.05, y2, rc[p[i].map[k]][1]+0.05);
				
				//front
				glVertex3f(rc[p[i].map[k]][0]-0.125, y1, rc[p[i].map[k]][1]+0.125);
				glVertex3f(rc[p[i].map[k]][0]-0.05, y2, rc[p[i].map[k]][1]+0.05);
				glVertex3f(rc[p[i].map[k]][0]+0.05, y2, rc[p[i].map[k]][1]+0.05);
				glVertex3f(rc[p[i].map[k]][0]+0.125, y1, rc[p[i].map[k]][1]+0.125);
			
				//left
				glVertex3f(rc[p[i].map[k]][0]+0.125, y1, rc[p[i].map[k]][1]+0.125);
				glVertex3f(rc[p[i].map[k]][0]+0.125, y1, rc[p[i].map[k]][1]-0.125);
				glVertex3f(rc[p[i].map[k]][0]+0.05, y2, rc[p[i].map[k]][1]-0.05);
				glVertex3f(rc[p[i].map[k]][0]+0.05, y2, rc[p[i].map[k]][1]+0.05);	
			
				//back
				glVertex3f(rc[p[i].map[k]][0]-0.125, y1, rc[p[i].map[k]][1]-0.125);	
				glVertex3f(rc[p[i].map[k]][0]+0.125, y1, rc[p[i].map[k]][1]-0.125);
				glVertex3f(rc[p[i].map[k]][0]+0.05, y2, rc[p[i].map[k]][1]-0.05);
				glVertex3f(rc[p[i].map[k]][0]-0.05, y2, rc[p[i].map[k]][1]-0.05);
				glEnd();
			}
		}
		
	}
	
  
	for(int i=0;i<4;i++){
    	for(int k=0;k<4;k++){
    		if(!p[i].active[k]){
    			if(i==0){
    				glPushMatrix();
				    glTranslated(initPos1[k][0], y2+0.01, initPos1[k][1]);
				    glutSolidSphere(0.1,50,50);    
				    glPopMatrix();
    				
    			}
    			if(i==1){
    				glPushMatrix();
				    glTranslated(initPos2[k][0], y2+0.01, initPos2[k][1]);
				    glutSolidSphere(0.1,50,50);    
				    glPopMatrix();
    			}
    			if(i==2){
    				glPushMatrix();
				    glTranslated(initPos3[k][0], y2+0.01, initPos3[k][1]);
				    glutSolidSphere(0.1,50,50);    
				    glPopMatrix();
    			}
    			else if(i==3){
    				glPushMatrix();
				    glTranslated(initPos4[k][0], y2+0.01, initPos4[k][1]);
				    glutSolidSphere(0.1,50,50);    
				    glPopMatrix();
    			}
    		}
    		else{
	    		glPushMatrix();
			    glTranslated(rc[p[i].map[k]][0], y2+0.01, rc[p[i].map[k]][1]);
			    glutSolidSphere(0.1,50,50);    
			    glPopMatrix();
			}
    	}
    }
  			
}

void drawBase(){
	glLoadIdentity();                 // Reset the model-view matrix
   glTranslatef(0.0f, 0.0f, -7.0f);  // Move right and into the screen
   glRotatef(angleCube, 1.0f, 0.0f, 0.0f);
   glRotatef(angleCubey, 0.0f, 1.0f, 0.0f);

   	glRotated(camera_angle_v, 1.0, 0.0, 0.0);
	glRotated(camera_angle_h, 0.0, 1.0, 0.0);
	
   glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
      // Top face (y = 1.0f)
      // Define vertices in counter-clockwise (CCW) order with normal pointing out
      glColor3f(base[0], base[1], base[2]);     // Green
      glVertex3f( x, y, -x);
      glVertex3f(-x, y, -x);
      glVertex3f(-x, y,  x);
      glVertex3f( x, y,  x);
 
      // Bottom face (y = -1.0f)
      glColor3f(1.0f, 0.45f, 0.0f);     // Orange
      glVertex3f( x, -y,  -x);
      glVertex3f(-x, -y,  -x);
      glVertex3f(-x, -y, x);
      glVertex3f( x, -y, x);
 
      // Front face  (z = 1.0f)
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f(x,  y, x);
      glVertex3f(-x,  y, x);
      glVertex3f(-x, -y, x);
      glVertex3f( x, -y, x);
 
      // Back face (z = -1.0f)
      glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
      glVertex3f( x, -y, -x);
      glVertex3f(-x, -y, -x);
      glVertex3f(-x,  y, -x);
      glVertex3f( x,  y, -x);
 
      // Left face (x = -1.0f)
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(-x,  y,  x);
      glVertex3f(-x,  y, -x);
      glVertex3f(-x, -y, -x);
      glVertex3f(-x, -y,  x);
 
      // Right face (x = 1.0f)
      glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
      glVertex3f(x,  y, -x);
      glVertex3f(x,  y,  x);
      glVertex3f(x, -y,  x);
      glVertex3f(x, -y, -x);
   glEnd();  // End of drawing color-cube 	
}

void animateFun(){
		
}

void display() {
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
   glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
 
   drawBase();
   drawHomeLines();
   drawLines();
   drawCubes();
   drawPlayers();
   drawSafeZones();
   drawHomeFinal();
   animateFun();
   //gamePlay();
   glutSwapBuffers();  
}

void mouse_click(int button, int state, int x, int y) {
    if(button == GLUT_LEFT_BUTTON) {
 		if(state == GLUT_DOWN) {
            dragging = 1;
            drag_x_origin = x;
            drag_y_origin = y;
        }
        else
            dragging = 0;
    }
    glutPostRedisplay();
}

void mouse_move(int x, int y) {
    if(dragging) {
        camera_angle_v += (y - drag_y_origin)*0.3;
        camera_angle_h += (x - drag_x_origin)*0.3;
        drag_x_origin = x;
        drag_y_origin = y;
    }
    glutPostRedisplay();
}
void reshape(GLsizei width, GLsizei height) {  
 	if (height == 0) height = 1;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;
 
   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);
 
   // Set the aspect ratio of the clipping volume to match the viewport
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();             // Reset
   // Enable perspective projection with fovy, aspect, zNear and zFar
   gluPerspective(45.0f, aspect, 0.1f, 100.0f);
   
}

/* Initialize OpenGL Graphics */
void initGL() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClearDepth(1.0f);                   // Set background depth to farthest
   glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
   glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
   glShadeModel(GL_SMOOTH);   // Enable smooth shading
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}

int main(int argc, char** argv) {
	//dNum = rand()%6 + 1;
	scanf("%d", &dNum);
	scanf("%d", &user);
		
	for(int i =0;i<4;i++){
		for(int j=0;j<4;j++){
			p[i].active[j] = false;
			p[i].map[j] = -1;
		}
	}
	for(int i=0;i<52;i++){
		for(int j = 0;j<2;j++){
			MAP1[i][j] = -1;
		}
	}
	glutInit(&argc, argv);            // Initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
	glutInitWindowSize(1400, 1100);   // Set the window's initial width & height
	glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
	glutCreateWindow(title);          // Create window with the given title
	glutDisplayFunc(display);       // Register callback handler for window re-paint event
	glutReshapeFunc(reshape);       // Register callback handler for window re-size event
	
	// here are the two new functions
	glutMouseFunc(mouse_click);
	glutMotionFunc(mouse_move);
	initGL();        
	gamePlay_user(user);                 // Enter the infinite event-processing loop
	
	glutMainLoop();
	return 0;
}
