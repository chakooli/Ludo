#include <windows.h>  // for MS Windows
#include <glut.h>  // GLUT, include glu.h and gl.h
#include <stdlib.h>
#include <math.h>
#include<stdio.h>
#include<time.h>
#include<glaux.h>

typedef struct player{
	bool active[4], home[4], final_home[4];
	int map[4];	
}Player;
Player p[4];

const int font=(int)GLUT_BITMAP_TIMES_ROMAN_24, font1=(int)GLUT_BITMAP_HELVETICA_18;

char title[] = "Ludo Game";
char string[4][10] = {"Your Turn", "Player 2", "Player 3", "Player 4"};
char rules1[] = {"Press 1-4 to select your token"};
char rules2[] = {"Press 5 for computer's turn"}; 

GLfloat angleCube = 30.0f, anglePyramid = 30.0f, angleCubey = 20.0f;

int MAP1[52][2], winning = -1;
int base[2][3] = {{238, 232, 170}, {189, 183, 107}};
int side[4][3] = {{153, 50, 204}, {255, 0, 0}, {0, 128, 128}, {255, 140, 0}};
int lines[3] = {0.0, 0.0, 0.0};
int playerColor[4][3] = {{186, 85, 211}, {255, 127, 80}, {32, 178, 170}, {255, 215, 0}};
int playerColorDark[4][3] = {{75, 0, 130}, {139, 0, 0}, {47, 79, 79}, {255, 69, 0}};
int drag_x_origin, drag_y_origin, dragging = 0;
int dNum, i=0;

double camera_angle_h = 0;
double camera_angle_v = 0;

float h = 0.17f, x = 2.4f, y = 0.15f;
float rc[73][2] = {{-0.4, 1.95}, {-0.4, 1.65},  {-0.4, 1.35}, {-0.4, 1.05}, {-0.4, 0.75}, {-0.75, 0.4}, 
{-1.05, 0.4}, {-1.35, 0.4}, {-1.65, 0.4}, {-1.95, 0.4}, {-2.25, 0.4}, {-2.25, 0.0}, {-2.25, -0.4}, {-1.95, -0.4}, 
{-1.65, -0.4}, {-1.35, -0.4}, {-1.05, -0.4}, {-0.75, -0.4}, {-0.4, -0.75}, {-0.4, -1.05},  {-0.4, -1.35}, 
{-0.4, -1.65}, {-0.4, -1.95}, {-0.4, -2.25}, {0.0, -2.25}, {0.4, -2.25}, {0.4, -1.95}, {0.4, -1.65}, {0.4, -1.35}, 
{0.4, -1.05}, {0.4, -0.75}, {0.75, -0.4}, {1.05, -0.4}, {1.35, -0.4}, {1.65, -0.4}, {1.95, -0.4}, {2.25, -0.4}, 
{2.25, 0.0}, {2.25, 0.4}, {1.95, 0.4}, {1.65, 0.4}, {1.35, 0.4}, {1.05, 0.4}, {0.75, 0.4}, {0.4, 0.75}, 
{0.4, 1.05}, {0.4, 1.35}, {0.4, 1.65}, {0.4, 1.95}, {0.4, 2.25}, {0.0, 2.25}, {-0.4, 2.25},
{0.0, 1.95}, {0.0, 1.65}, {0.0, 1.35}, {0.0, 1.05}, {0.0, 0.75},		//for home
{-1.95, 0.0}, {-1.65, 0.0}, {-1.35, 0.0}, {-1.05, 0.0}, {-0.75, 0.0},
{0.0, -1.95}, {0.0, -1.65}, {0.0, -1.35}, {0.0, -1.05}, {0.0, -0.75},
{1.95, 0.0}, {1.65, 0.0}, {1.35, 0.0}, {1.05, 0.0}, {0.75, 0.0}, {0.0, 0.0}};//for home
float home1[5][2] = {{0.0, 1.95}, {0.0, 1.65}, {0.0, 1.35}, {0.0, 1.05}, {0.0, 0.75}};
float home2[5][2] = {{-1.95, 0.0}, {-1.65, 0.0}, {-1.35, 0.0}, {-1.05, 0.0}, {-0.75, 0.0}};
float home3[5][2] = {{0.0, -1.95}, {0.0, -1.65}, {0.0, -1.35}, {0.0, -1.05}, {0.0, -0.75}};
float home4[5][2] = {{1.95, 0.0}, {1.65, 0.0}, {1.35, 0.0}, {1.05, 0.0}, {0.75, 0.0}};
float initPos1[4][2] = {{-1.9, 1.9}, {-1.1, 1.9}, {-1.1, 1.1}, {-1.9, 1.1}};
float initPos2[4][2] = {{-1.9, -1.9}, {-1.1, -1.9}, {-1.1, -1.1}, {-1.9, -1.1}};
float initPos3[4][2] = {{1.9, -1.9}, {1.1, -1.9}, {1.1, -1.1}, {1.9, -1.1}};
float initPos4[4][2] = {{1.9, 1.9}, {1.1, 1.9}, {1.1, 1.1}, {1.9, 1.1}};

void display();
void drawHomeFinal2();
void view1();
void gamePlay();
int wrpInit(int x, int i);
void winner();
void gamePlay_user(int sub);
void drawLines();
void drawCubes();
void drawHomeFinal();
void drawHomeFinal2();
void drawHomeLines();
void drawSafeZones();
void drawPlayers();
void drawBase();
void mouse_click(int, int,  int, int);
void keyPressed (unsigned char key, int x, int y);
void showLudo();
void showInfo(int i, float x, float y, float z, void *font,const char *string);
void textDisplay();
void renderBitmapString(float x, float y, float z, void *font,const char *string);
void renderBitmapStringForPlayers(int x, void *font);
void mouse_move(int, int);
void reshape(GLsizei, GLsizei);
void initGL();
int wrpInit(int x, int i){
	if(x<(13*i)){
		return (x + 51)-(13*i);		
	}
	else{
		return x-(13*i);
	}
}

void winner(){
	for(int f=0;f<4;f++){
		if(p[f].final_home[0] && p[f].final_home[1] && p[f].final_home[2] && p[f].final_home[3]){
			if(f==0){
				winning = 0;
				break;
			}
			else{
				winning = f;
				break;
			}
			
		}
	}
}
void gamePlay_user(int sub){
	
	int temp = wrpInit(p[0].map[sub], 0);
	
	if(p[0].active[sub] && p[0].home[sub]){
		if(p[0].map[sub]+dNum == (52 + (5*(i+1)))){
			p[0].map[sub] = 72;
			p[0].final_home[sub] = true;
			
		}
		else if(p[i].map[sub] > 51 && (p[i].map[sub]+dNum)<=(51+5*(i+1))){
		
			p[i].map[sub] += dNum;
			p[i].home[sub] = true;		
			
		}
	}
	else if(p[0].active[sub] && !p[0].home[sub] && temp==50 && dNum==6){
		MAP1[p[0].map[sub]][0] = -1;
		MAP1[p[0].map[sub]][1] = -1;	
		p[0].map[sub] = 72;
		p[i].final_home[sub] = true;
	
	}	
	
	else if(p[i].active[sub] && !p[i].home[sub] && temp+dNum>50 && temp+dNum<56){
		MAP1[p[i].map[sub]][0] = -1;
		MAP1[p[i].map[sub]][1] = -1;	
		int rem = (temp+dNum)%50;
		
		p[i].map[sub] = 51  + rem;	
		p[i].home[sub] = true;		
		
	}
	
	else if(!p[0].active[sub] && (dNum==1 || dNum==6) && MAP1[0][0]== -1){
		p[0].active[sub] = true;
		p[0].map[sub] = 0;
		MAP1[0][0] = 0;
		MAP1[0][1] = sub;
	}
	
	else if(p[0].active[sub]){
		int t = (p[0].map[sub]+dNum)%52;
		if(MAP1[t][0]==-1){
			MAP1[p[0].map[sub]][0] = -1;
			MAP1[p[0].map[sub]][1] = -1;	
			MAP1[t][0] = 0;
			MAP1[t][1] = sub;
			p[0].map[sub] = t;
		}
		else if(t!=0 && t!=8 && t!=13 && t!=21 && t!=26 && t!=34 && t!=39 && t!=47){
			MAP1[p[0].map[sub]][0] = -1;
			MAP1[p[0].map[sub]][1] = -1;	
			p[MAP1[t][0]].map[MAP1[t][1]] = -1;
			p[MAP1[t][0]].active[MAP1[t][1]] = false;
			MAP1[t][0] = 0;
			MAP1[t][1] = sub;
			p[0].map[sub] = t;
		}
	
	}	
	
	i++;
	srand (time(NULL));
	dNum = rand()%6 + 1;
	
	winner();
	glutPostRedisplay();
	
	//gamePlay();
}

void gamePlay(){
	int val, maxPlayer, l, j, b, max=0, k, whichMove=0;
	GLint rand();
	 srand (time(NULL));
		
		if((dNum==1||dNum==6)&&(MAP1[13*i][0]== -1)&&((!p[i].active[0])||(!p[i].active[1])||(!p[i].active[2])||(!p[i].active[3]))){
			
			for(int j=0;j<4;j++){
				if(!p[i].active[j]){
					p[i].active[j] = true;
					p[i].map[j] = 13*i;
					MAP1[p[i].map[j]][0] = i;
					MAP1[p[i].map[j]][1] = j;
					
					break;
				}
			}
		}
		else{
			if((p[i].active[0])||(p[i].active[1])||(p[i].active[2])||(p[i].active[3])){
				
				//going home
				if(whichMove==0){
					for(k=0;k<4;k++){
						int temp = wrpInit(p[i].map[k], i);
						if(p[i].active[k] && p[i].home[k]){
							if(p[i].map[k]+dNum == (52 + (5*(i+1)))){
								p[i].map[k] = 72;
								whichMove = 1;
								p[i].final_home[k] = true;
								
								break;
							}
						}
						else if(p[i].active[k] && !p[i].home[k] && temp==50 && dNum==6){
							MAP1[p[i].map[k]][0] = -1;
							MAP1[p[i].map[k]][1] = -1;	
							p[i].map[k] = 72;
							whichMove = 1;
							p[i].final_home[k] = true;
							
							break;
						}	
					}
				}
				if(whichMove==0){
					for(k=0;k<4;k++){
						if(p[i].active[k]&&!p[i].final_home[k]){
							int temp = wrpInit(p[i].map[k], i);
							
							if(p[i].map[k] > 51 && (p[i].map[k]+dNum)<=(51+5*(i+1))){
								
								p[i].map[k] += dNum;
								p[i].home[k] = true;		
								whichMove = 2;
							
								break;
							}
							else if(p[i].active[k] && !p[i].home[k] && temp+dNum>50 && temp+dNum<56){
								MAP1[p[i].map[k]][0] = -1;
								MAP1[p[i].map[k]][1] = -1;	
								int rem = (temp+dNum)%50;
								p[i].map[k] = 51 + (5*i) + rem + 1;	
								whichMove = 2;
								p[i].home[k] = true;		
								
								break;
							}
						}
					}	
				}
				
				//defensive
				if(whichMove==0){
					for(k=0;k<4;k++){					
						if(p[i].active[k] && !p[i].home[k]){
							if((MAP1[p[i].map[k]-1][0]!=-1 && MAP1[p[i].map[k]-1][0]!=i )
								|| (MAP1[p[i].map[k]-2][0]!=-1 && MAP1[p[i].map[k]-2][0]!=i) 
								|| (MAP1[p[i].map[k]-3][0]!=-1 && MAP1[p[i].map[k]-3][0]!=i)
								|| (MAP1[p[i].map[k]-4][0]!=-1 && MAP1[p[i].map[k]-4][0]!=i)
								|| (MAP1[p[i].map[k]-5][0]!=-1 && MAP1[p[i].map[k]-5][0]!=i) 
								|| (MAP1[p[i].map[k]-6][0]!=-1 && MAP1[p[i].map[k]-6][0]!=i)){							
								if(MAP1[(p[i].map[k]+dNum)%52][0]== -1){
									MAP1[p[i].map[k]][0] = -1;
									MAP1[p[i].map[k]][1] = -1;	
									p[i].map[k] += dNum;
									p[i].map[k] %= 52;
									MAP1[p[i].map[k]][0] = i;
									MAP1[p[i].map[k]][1] = k;
									
									whichMove = 3;
									break;	
								}
							}
						}
					}	
				}
				l = 0;
				//Aggressive strategy
				if(whichMove==0){
					for(l=0;l<4;l++){
						if(p[i].active[l] && !p[i].home[l]){
							
							int t = (p[i].map[l]+dNum)%52;
							if(MAP1[t][0] != -1&&MAP1[t][0]!=i&&t!=0 && t!=8 && t!=13 && t!=21 && t!=26 && t!=34 && t!=39 && t!=47){
								MAP1[p[i].map[l]][0] = -1;
								MAP1[p[i].map[l]][1] = -1;
								
								p[MAP1[t][0]].map[MAP1[t][1]] = -1;
								p[MAP1[t][0]].active[MAP1[t][1]] = false;
								p[i].map[l] += dNum;
								p[i].map[l] %= 52;
								MAP1[p[i].map[l]][0] = i;
								MAP1[p[i].map[l]][1] = l;	
								whichMove = 4;
								break;
							}
							
						}
					}
				}
				//Fast strategy
				
				if(whichMove==0){				//for subplayers of current player
					max = -1;
					maxPlayer = 0;
					for(int s=0;s<4;s++){	
						if(p[i].active[s]&& !p[i].home[s]){
							
								
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
					if(max!=-1){
						//translate
						MAP1[p[i].map[maxPlayer]][0] = -1;
						MAP1[p[i].map[maxPlayer]][1] = -1;	
						p[i].map[maxPlayer] += dNum;
						p[i].map[maxPlayer] %= 52;
						MAP1[p[i].map[maxPlayer]][0] = i;
						MAP1[p[i].map[maxPlayer]][1] = maxPlayer;	
						
						whichMove = 5;
					}
				}
				//Random strategy
				if(whichMove==0){
											//for subplayers of current player
					for(int s=0;s<4;s++){	
						if(p[i].active[s]&& !p[i].home[s]){	
							MAP1[p[i].map[s]][0] = -1;
							MAP1[p[i].map[s]][1] = -1;	
							p[i].map[s] += dNum;
							p[i].map[s] %= 52;					//for subplayers of current player
							MAP1[p[i].map[s]][0] = i;
							MAP1[p[i].map[s]][1] = s;	
						
							whichMove = 6;
							break;
						}	
					}
				}
			}
		}
		dNum = rand()%6 + 1;
		winner();
		glutPostRedisplay();
	
		i = (i+1)%4;
	
}	

void view1(){
	glLoadIdentity();                 // Reset the model-view matrix
	glTranslatef(23.0f, 6.0f, -35.0f);  // Move right and into the screen
	int x1 = 1.0f;
	glRotatef(80.0f, 1.0f, 0.0f, 0.0f);
      // Top face (y = 1.0f)
    
	  // Define vertices in counter-clockwise (CCW) order with normal pointing out
	glPointSize(5.0);
	glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads		
	
	glColor3f(base[0][0], base[0][1], base[0][2]);     // Green
	glVertex3f( x1, x1, -x1);
	glColor3ub(192, 192, 192);
	glVertex3f(-x1, x1, -x1);
	glVertex3f(-x1, x1,  x1);
	glVertex3f( x1, x1,  x1);
	glEnd();  
	glFlush();	
	
	glBegin(GL_POINTS);
	glColor3ub(0, 0, 0);
	
	if(dNum == 1){ 		
		glVertex3f( 0.0, x1+0.1, 0.0);
	}
	
	else if(dNum == 2){
		glVertex3f( -0.4, x1+0.1, 0.0);
		glVertex3f( 0.4, x1+0.1, 0.0);
	}
	
	else if(dNum == 3){
		glVertex3f( -0.6, x1+0.1, 0.0);
		glVertex3f( 0.0, x1+0.1, 0.0);
		glVertex3f( 0.6, x1+0.1, 0.0);
	}
	
	else if(dNum == 4){
		glVertex3f( -0.5, x1+0.1, -0.5);
		glVertex3f( 0.5, x1+0.1, -0.5);
		glVertex3f( -0.5, x1+0.1, 0.5);
		glVertex3f( 0.5, x1+0.1, 0.5);
	}
 	 
	else if(dNum == 5){
		glVertex3f( -0.5, x1+0.1, -0.5);
		glVertex3f( 0.5, x1+0.1, -0.5);
		glVertex3f( 0.0, x1+0.1, 0.0);
		glVertex3f( -0.5, x1+0.1, 0.5);
		glVertex3f( 0.5, x1+0.1, 0.5);
	}
	
	else if(dNum == 6){
		glVertex3f( -0.4, x1+0.1, -0.4);
		glVertex3f( 0.4, x1+0.1, -0.4);
		glVertex3f( -0.4, x1+0.1, 0.0);
		glVertex3f( 0.4, x1+0.1, 0.0);
		glVertex3f( -0.4, x1+0.1, 0.4);
		glVertex3f( 0.4, x1+0.1, 0.4);
	}
	
	 glEnd();
	 glFlush();
 	  // Bottom face (y = -1.0f)
    glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads		
	
	  glColor3ub(160, 160, 160);     // Green
	  glVertex3f( x1, -x1,  -x1);
      glColor3f(base[0][0], base[0][1], base[0][2]);     // Green
	  glVertex3f(-x1, -x1,  -x1);
      glVertex3f(-x1, -x1, x1);
      glVertex3f( x1, -x1, x1);
 
      // Front face  (z = 1.0f)
      glColor3f(base[0][0], base[0][1], base[0][2]);     // Green
      glVertex3f(x1,  x1, x1);
      glColor3ub(160, 160, 160);    
      glVertex3f(-x1,  x1, x1);
      glVertex3f(-x1, -x1, x1);
      glVertex3f( x1, -x1, x1);
 
      // Back face (z = -1.0f)
      glColor3f(base[0][0], base[0][1], base[0][2]);     // Green
      glVertex3f( x1, -x1, -x1);
      glColor3ub(192, 192, 192);    
      glVertex3f(-x1, -x1, -x1);
      glVertex3f(-x1,  x1, -x1);
      glVertex3f( x1,  x1, -x1);
 
      // Left face (x = -1.0f)
      glColor3f(base[0][0], base[0][1], base[0][2]);     // Green
      glVertex3f(-x1,  x1,  x1);
      glColor3ub(160, 160, 160);    
      glVertex3f(-x1,  x1, -x1);
      glVertex3f(-x1, -x1, -x1);
      glVertex3f(-x1, -x1,  x1);
 
      // Right face (x = 1.0f)
      glColor3f(base[0][0], base[0][1], base[0][2]);     // Green
      glVertex3f(x1,  x1, -x1);
      glVertex3f(x1,  x1,  x1);
      glVertex3f(x1, -x1,  x1);
      glVertex3f(x1, -x1, -x1);
  glEnd();  // End of drawing color-cube*/
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
	
	//glBindTexture(GL_TEXTURE_2D, textures.textureID);
	
	glBegin(GL_QUADS);
	//side1
	glColor3ub(side[0][0], side[0][1], side[0][2]);
	
	//glTexCoord2f(0.0, 1.0);
	glVertex3f(-1.6f, y1, x-0.8f);
	
	//glTexCoord2f(1.0, 1.0);
	glVertex3f(-1.6f, y1, x-0.2f);
	
	//glTexCoord2f(1.0, 0.0);
	glVertex3f(-2.2f, y1, x-0.2f);
	
	//glTexCoord2f(0.0, 0.0);
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
	glColor3ub(side[3][0], side[3][1], side[3][2]);
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
	//side[3]
	glColor3ub(side[1][0], side[1][1], side[1][2]);
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
	
	//side[2]
	glColor3ub(side[2][0], side[2][1], side[2][2]);
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
	glColor3ub(0.0, 0.0, 0.0);
	
	glBegin(GL_QUADS);
	
	glVertex3f(-0.2, y1, 0.6);
	glVertex3f(-0.2, y1+0.25, 0.6);
	glVertex3f(-0.2, y1+0.25, 0.2);
	glVertex3f(-0.2, y1, 0.2);
	
	glVertex3f(0.2, y1, 0.6);
	glVertex3f(0.2, y1+0.25, 0.6);
	glVertex3f(0.2, y1+0.25, 0.2);
	glVertex3f(0.2, y1, 0.2);
	
	glVertex3f(-0.2, y1+0.25, 0.6);
	glVertex3f(0.0, y1+0.35, 0.6);
	glVertex3f(0.0, y1+0.35, 0.2);
	glVertex3f(-0.2, y1+0.25, 0.2);
	
	glVertex3f(0.2, y1+0.25, 0.6);
	glVertex3f(0.0, y1+0.35, 0.6);
	glVertex3f(0.0, y1+0.35, 0.2);
	glVertex3f(0.2, y1+0.25, 0.2);
	
	glColor3ub(0.0, 0.0, 1.0);
	glVertex3f(-0.2, y1, -0.6);
	glVertex3f(-0.2, y1+0.25, -0.6);
	glVertex3f(-0.2, y1+0.25, -0.2);
	glVertex3f(-0.2, y1, -0.2);
	
	glVertex3f(0.2, y1, -0.6);
	glVertex3f(0.2, y1+0.25, -0.6);
	glVertex3f(0.2, y1+0.25, -0.2);
	glVertex3f(0.2, y1, -0.2);
	
	glVertex3f(-0.2, y1+0.25, -0.6);
	glVertex3f(0.0, y1+0.35, -0.6);
	glVertex3f(0.0, y1+0.35, -0.2);
	glVertex3f(-0.2, y1+0.25, -0.2);
	
	glVertex3f(0.2, y1+0.25, -0.6);
	glVertex3f(0.0, y1+0.35, -0.6);
	glVertex3f(0.0, y1+0.35, -0.2);
	glVertex3f(0.2, y1+0.25, -0.2);
	
	glColor3ub(0.0, 1.0, 0.0);
	glVertex3f(0.6, y1, -0.2);
	glVertex3f(0.6, y1+0.25, -0.2);
	glVertex3f(0.2, y1+0.25, -0.2);
	glVertex3f(0.2, y1, -0.2);
	
	glVertex3f(0.6, y1, 0.2);
	glVertex3f(0.6, y1+0.25, 0.2);
	glVertex3f(0.2, y1+0.25, 0.2);
	glVertex3f(0.2, y1, 0.2);
	
	glVertex3f(0.6, y1+0.25, -0.2);
	glVertex3f(0.6, y1+0.35, 0.0);
	glVertex3f(0.2, y1+0.35, 0.0);
	glVertex3f(0.2, y1+0.25, -0.2);
	
	glVertex3f(0.6, y1+0.25, 0.2);
	glVertex3f(0.6, y1+0.35, 0.0);
	glVertex3f(0.2, y1+0.35, 0.0);
	glVertex3f(0.2, y1+0.25, 0.2);
	
	glColor3ub(1.0, 0.0, 0.0);
	glVertex3f(-0.6, y1, -0.2);
	glVertex3f(-0.6, y1+0.25, -0.2);
	glVertex3f(-0.2, y1+0.25, -0.2);
	glVertex3f(-0.2, y1, -0.2);
	
	glVertex3f(-0.6, y1, 0.2);
	glVertex3f(-0.6, y1+0.25, 0.2);
	glVertex3f(-0.2, y1+0.25, 0.2);
	glVertex3f(-0.2, y1, 0.2);
	
	glVertex3f(-0.6, y1+0.25, -0.2);
	glVertex3f(-0.6, y1+0.35, 0.0);
	glVertex3f(-0.2, y1+0.35, 0.0);
	glVertex3f(-0.2, y1+0.25, -0.2);
	
	glVertex3f(-0.6, y1+0.25, 0.2);
	glVertex3f(-0.6, y1+0.35, 0.0);
	glVertex3f(-0.2, y1+0.35, 0.0);
	glVertex3f(-0.2, y1+0.25, 0.2);
glEnd();
	glBegin(GL_POLYGON);
	//p1
	glColor3ub(0.0, 0.0, 0.0);
	glVertex3f(-0.2, y1, 0.2);
	glVertex3f(-0.2, y1+0.25, 0.2);
	glVertex3f(0.0, y1+0.35, 0.2);
	glVertex3f(0.2, y1+0.25, 0.2);
	glVertex3f(0.2, y1, 0.2);
	glEnd();
	//p2
	glBegin(GL_POLYGON);
	glColor3ub(0.0, 0.0, 1.0);
	glVertex3f(-0.2, y1, -0.2);
	glVertex3f(-0.2, y1+0.25, -0.2);
	glVertex3f(-0.2, y1+0.35, 0.0);
	glVertex3f(-0.2, y1+0.25, 0.2);
	glVertex3f(-0.2, y1, 0.2);
glEnd();
	//p3
	glColor3ub(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(-0.2, y1, -0.2);
	glVertex3f(-0.2, y1+0.25, -0.2);
	glVertex3f(0.0, y1+0.35, -0.2);
	glVertex3f(0.2, y1+0.255, -0.2);
	glVertex3f(0.2, y1, -0.2);
	glEnd();
	//p4
	glColor3ub(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(0.2, y1, -0.2);
	glVertex3f(0.2, y1+0.25, -0.2);
	glVertex3f(0.2, y1+0.35, 0.0);
	glVertex3f(0.2, y1+0.25, 0.2);
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
	glColor3ub(side[0][0], side[0][1], side[0][2]);
	glVertex3f(-0.2f, y1, 0.6);
	glVertex3f(-0.6f, y1, 0.6f);
	glVertex3f(-0.6f, y1+0.25, 0.6f);
	glVertex3f(-0.2f, y1+0.25, 0.6f);
	
	glVertex3f(0.2f, y1, 0.6);
	glVertex3f(0.6f, y1, 0.6f);
	glVertex3f(0.6f, y1+0.25, 0.6f);
	glVertex3f(0.2f, y1+0.25, 0.6f);
	
	glVertex3f(-0.2f, y1+0.25, 0.6);
	glVertex3f(-0.6f, y1+0.25, 0.6f);
	glVertex3f(-0.6f, y1+0.35, 0.6f);
	glVertex3f(0.0f, y1+0.35, 0.6f);
	
	glVertex3f(0.2f, y1+0.25, 0.6);
	glVertex3f(0.6f, y1+0.25, 0.6f);
	glVertex3f(0.6f, y1+0.35, 0.6f);
	glVertex3f(0.0f, y1+0.35, 0.6f);

	glColor3ub(side[3][0], side[3][1], side[3][2]);
	glVertex3f(0.6f, y1, -0.2);
	glVertex3f(0.6f, y1, -0.6f);
	glVertex3f(0.6f, y1+0.25, -0.6f);
	glVertex3f(0.6f, y1+0.25, -0.2f);
	
	glVertex3f(0.6f, y1, 0.2);
	glVertex3f(0.6f, y1, 0.6f);
	glVertex3f(0.6f, y1+0.25, 0.6f);
	glVertex3f(0.6f, y1+0.25, 0.2f);
	
	glVertex3f(0.6f, y1+0.25, -0.2);
	glVertex3f(0.6f, y1+0.25, -0.6f);
	glVertex3f(0.6f, y1+0.35, -0.6f);
	glVertex3f(0.6f, y1+0.35, 0.0f);
	
	glVertex3f(0.6f, y1+0.25, 0.2);
	glVertex3f(0.6f, y1+0.25, 0.6f);
	glVertex3f(0.6f, y1+0.35, 0.6f);
	glVertex3f(0.6f, y1+0.35, 0.0f);

	glColor3ub(side[2][0], side[2][1], side[2][2]);
	glVertex3f(-0.2f, y1, -0.6);
	glVertex3f(-0.6f, y1, -0.6f);
	glVertex3f(-0.6f, y1+0.25, -0.6f);
	glVertex3f(-0.2f, y1+0.25, -0.6f);
	
	glVertex3f(0.2f, y1, -0.6);
	glVertex3f(0.6f, y1, -0.6f);
	glVertex3f(0.6f, y1+0.25, -0.6f);
	glVertex3f(0.2f, y1+0.25, -0.6f);
	
	glVertex3f(-0.2f, y1+0.25, -0.6);
	glVertex3f(-0.6f, y1+0.25, -0.6f);
	glVertex3f(-0.6f, y1+0.35, -0.6f);
	glVertex3f(0.0f, y1+0.35, -0.6f);
	
	glVertex3f(0.2f, y1+0.25, -0.6);
	glVertex3f(0.6f, y1+0.25, -0.6f);
	glVertex3f(0.6f, y1+0.35, -0.6f);
	glVertex3f(0.0f, y1+0.35, -0.6f);
	
	glColor3ub(side[1][0], side[1][1], side[1][2]);
	glVertex3f(-0.6f, y1, -0.2);
	glVertex3f(-0.6f, y1, -0.6f);
	glVertex3f(-0.6f, y1+0.25, -0.6f);
	glVertex3f(-0.6f, y1+0.25, -0.2f);
	
	glVertex3f(-0.6f, y1, 0.2);
	glVertex3f(-0.6f, y1, 0.6f);
	glVertex3f(-0.6f, y1+0.25, 0.6f);
	glVertex3f(-0.6f, y1+0.25, 0.2f);
	
	glVertex3f(-0.6f, y1+0.25, -0.2);
	glVertex3f(-0.6f, y1+0.25, -0.6f);
	glVertex3f(-0.6f, y1+0.35, -0.6f);
	glVertex3f(-0.6f, y1+0.35, 0.0f);
	
	glVertex3f(-0.6f, y1+0.25, 0.2);
	glVertex3f(-0.6f, y1+0.25, 0.6f);
	glVertex3f(-0.6f, y1+0.35, 0.6f);
	glVertex3f(-0.6f, y1+0.35, 0.0f);

	glEnd();
	
	glBegin(GL_TRIANGLES);
	glColor3ub(side[0][0], side[0][1], side[0][2]);
	glVertex3f(-0.7f, y1+0.35, 0.7);
	glVertex3f(0.7f, y1+0.35, 0.7);
	glColor3ub(playerColorDark[0][0], playerColorDark[0][1], playerColorDark[0][2]);
	glVertex3f(0.0f, y1+0.65, 0.0);

	glColor3ub(side[3][0], side[3][1], side[3][2]);
	glVertex3f(0.7f, y1+0.35, -0.7);
	glVertex3f(0.7f, y1+0.35, 0.7);
	glColor3ub(playerColorDark[3][0], playerColorDark[3][1], playerColorDark[3][2]);
	glVertex3f(0.0f, y1+0.65, 0.0);

	glColor3ub(side[2][0], side[2][1], side[2][2]);
	glVertex3f(-0.7f, y1+0.35, -0.7);
	glVertex3f(0.7f, y1+0.35, -0.7);
	glColor3ub(playerColorDark[2][0], playerColorDark[2][1], playerColorDark[2][2]);
	glVertex3f(0.0f, y1+0.65, 0.0);

	glColor3ub(side[1][0], side[1][1], side[1][2]);
	glVertex3f(-0.7f, y1+0.35, -0.7);
	glVertex3f(-0.7f, y1+0.35, 0.7);
	glColor3ub(playerColorDark[1][0], playerColorDark[1][1], playerColorDark[1][2]);
	glVertex3f(0.0f, y1+0.65, 0.0);
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
	glColor3ub(side[0][0], side[0][1], side[0][2]);
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
	glColor3ub(side[2][0], side[2][1], side[2][2]);
	glVertex3f(0.2f, y1, -x+0.3f);
	glVertex3f(0.2f, y1, -x+0.6f);
	glVertex3f(0.6f, y1, -x+0.6f);
	glVertex3f(0.6f, y1, -x+0.3f);
	
	glVertex3f(0.2f, y1, -x+0.3f);
	glVertex3f(0.2f, y1, -x+1.8f);
	glVertex3f(-0.2f, y1, -x+1.8f);
	glVertex3f(-0.2f, y1, -x+0.3f);
	
	//glVertex3f(0.2f, y1, -x+1.5f);
	
	//glVertex3f(-0.2f, y1, -x+1.5f);
	glEnd();
	glFlush();
	
	//Orange path
	glBegin(GL_QUADS);
	glColor3ub(side[1][0], side[1][1], side[1][2]);
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
	glColor3ub(side[3][0], side[3][1], side[3][2]);
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
	glColor3ub(153, 0, 76);
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
	
	for(int i=0;i<4;i++){
		
		
		for(int k = 0;k<4;k++){
			
			if(!p[i].active[k]){
		//		printf("%d  %d\n", i, k);
				if(i==0){
					glBegin(GL_QUADS);
					glColor3ub(playerColor[i][0], playerColor[i][1], playerColor[i][2]);
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
					glColor3ub(playerColorDark[i][0], playerColorDark[i][1], playerColorDark[i][2]);
					glVertex3f(initPos1[k][0]-0.125, y1, initPos1[k][1]+0.125);
					glVertex3f(initPos1[k][0]-0.125, y1, initPos1[k][1]-0.125);	
					glColor3ub(playerColor[i][0], playerColor[i][1], playerColor[i][2]);
					
					glVertex3f(initPos1[k][0]-0.05, y2, initPos1[k][1]-0.05);	
					glVertex3f(initPos1[k][0]-0.05, y2, initPos1[k][1]+0.05);
					
					
					//front
					glColor3ub(playerColorDark[i][0], playerColorDark[i][1], playerColorDark[i][2]);
					glVertex3f(initPos1[k][0]-0.125, y1, initPos1[k][1]+0.125);
					glColor3ub(playerColor[i][0], playerColor[i][1], playerColor[i][2]);
					glVertex3f(initPos1[k][0]-0.05, y2, initPos1[k][1]+0.05);
					glVertex3f(initPos1[k][0]+0.05, y2, initPos1[k][1]+0.05);
					glColor3ub(playerColorDark[i][0], playerColorDark[i][1], playerColorDark[i][2]);
					glVertex3f(initPos1[k][0]+0.125, y1, initPos1[k][1]+0.125);
					
					
					//left
					glVertex3f(initPos1[k][0]+0.125, y1, initPos1[k][1]+0.125);
					glVertex3f(initPos1[k][0]+0.125, y1, initPos1[k][1]-0.125);
					
					glColor3ub(playerColor[i][0], playerColor[i][1], playerColor[i][2]);
					glVertex3f(initPos1[k][0]+0.05, y2, initPos1[k][1]-0.05);
					glVertex3f(initPos1[k][0]+0.05, y2, initPos1[k][1]+0.05);	
				
					//back
					glColor3ub(playerColorDark[i][0], playerColorDark[i][1], playerColorDark[i][2]);
					glVertex3f(initPos1[k][0]-0.125, y1, initPos1[k][1]-0.125);	
					glVertex3f(initPos1[k][0]+0.125, y1, initPos1[k][1]-0.125);
					glColor3ub(playerColor[i][0], playerColor[i][1], playerColor[i][2]);
					glVertex3f(initPos1[k][0]+0.05, y2, initPos1[k][1]-0.05);
					glVertex3f(initPos1[k][0]-0.05, y2, initPos1[k][1]-0.05);
					glEnd();
				}
				if(i==1){
					glBegin(GL_QUADS);
					glColor3ub(playerColor[i][0], playerColor[i][1], playerColor[i][2]);
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
					glColor3ub(playerColorDark[i][0], playerColorDark[i][1], playerColorDark[i][2]);
					glVertex3f(initPos2[k][0]-0.125, y1, initPos2[k][1]+0.125);
					glVertex3f(initPos2[k][0]-0.125, y1, initPos2[k][1]-0.125);
					glColor3ub(playerColor[i][0], playerColor[i][1], playerColor[i][2]);	
					glVertex3f(initPos2[k][0]-0.05, y2, initPos2[k][1]-0.05);	
					glVertex3f(initPos2[k][0]-0.05, y2, initPos2[k][1]+0.05);
					
					//front
					glColor3ub(playerColorDark[i][0], playerColorDark[i][1], playerColorDark[i][2]);
					glVertex3f(initPos2[k][0]-0.125, y1, initPos2[k][1]+0.125);
					glColor3ub(playerColor[i][0], playerColor[i][1], playerColor[i][2]);
					glVertex3f(initPos2[k][0]-0.05, y2, initPos2[k][1]+0.05);
					glVertex3f(initPos2[k][0]+0.05, y2, initPos2[k][1]+0.05);
					glColor3ub(playerColorDark[i][0], playerColorDark[i][1], playerColorDark[i][2]);
					glVertex3f(initPos2[k][0]+0.125, y1, initPos2[k][1]+0.125);
				
					//left
					glVertex3f(initPos2[k][0]+0.125, y1, initPos2[k][1]+0.125);
					glVertex3f(initPos2[k][0]+0.125, y1, initPos2[k][1]-0.125);
					glColor3ub(playerColor[i][0], playerColor[i][1], playerColor[i][2]);
					glVertex3f(initPos2[k][0]+0.05, y2, initPos2[k][1]-0.05);
					glVertex3f(initPos2[k][0]+0.05, y2, initPos2[k][1]+0.05);	
				
					//back
					glColor3ub(playerColorDark[i][0], playerColorDark[i][1], playerColorDark[i][2]);
					glVertex3f(initPos2[k][0]-0.125, y1, initPos2[k][1]-0.125);	
					glVertex3f(initPos2[k][0]+0.125, y1, initPos2[k][1]-0.125);
					glColor3ub(playerColor[i][0], playerColor[i][1], playerColor[i][2]);
					glVertex3f(initPos2[k][0]+0.05, y2, initPos2[k][1]-0.05);
					glVertex3f(initPos2[k][0]-0.05, y2, initPos2[k][1]-0.05);
					glEnd();
				}
				if(i==2){
					glBegin(GL_QUADS);
					glColor3ub(playerColorDark[i][0], playerColorDark[i][1], playerColorDark[i][2]);
					glVertex3f(initPos3[k][0]-0.125, y1, initPos3[k][1]+0.125);
					glVertex3f(initPos3[k][0]-0.125, y1, initPos3[k][1]-0.125);	
					glVertex3f(initPos3[k][0]+0.125, y1, initPos3[k][1]-0.125);
					glVertex3f(initPos3[k][0]+0.125, y1, initPos3[k][1]+0.125);
					
					glColor3ub(playerColor[i][0], playerColor[i][1], playerColor[i][2]);
					//upperface
					glVertex3f(initPos3[k][0]-0.05, y2, initPos3[k][1]+0.05);
					glVertex3f(initPos3[k][0]-0.05, y2, initPos3[k][1]-0.05);	
					glVertex3f(initPos3[k][0]+0.05, y2, initPos3[k][1]-0.05);
					glVertex3f(initPos3[k][0]+0.05, y2, initPos3[k][1]+0.05);
					
					//right
					glColor3ub(playerColorDark[i][0], playerColorDark[i][1], playerColorDark[i][2]);
					glVertex3f(initPos3[k][0]-0.125, y1, initPos3[k][1]+0.125);
					glVertex3f(initPos3[k][0]-0.125, y1, initPos3[k][1]-0.125);
					glColor3ub(playerColor[i][0], playerColor[i][1], playerColor[i][2]);	
					glVertex3f(initPos3[k][0]-0.05, y2, initPos3[k][1]-0.05);	
					glVertex3f(initPos3[k][0]-0.05, y2, initPos3[k][1]+0.05);
					
					//front
					glColor3ub(playerColorDark[i][0], playerColorDark[i][1], playerColorDark[i][2]);
					glVertex3f(initPos3[k][0]-0.125, y1, initPos3[k][1]+0.125);
					glColor3ub(playerColor[i][0], playerColor[i][1], playerColor[i][2]);
					glVertex3f(initPos3[k][0]-0.05, y2, initPos3[k][1]+0.05);
					glVertex3f(initPos3[k][0]+0.05, y2, initPos3[k][1]+0.05);
					glColor3ub(playerColorDark[i][0], playerColorDark[i][1], playerColorDark[i][2]);
					glVertex3f(initPos3[k][0]+0.125, y1, initPos3[k][1]+0.125);
				
					//left
					glVertex3f(initPos3[k][0]+0.125, y1, initPos3[k][1]+0.125);
					glVertex3f(initPos3[k][0]+0.125, y1, initPos3[k][1]-0.125);
					glColor3ub(playerColor[i][0], playerColor[i][1], playerColor[i][2]);
					glVertex3f(initPos3[k][0]+0.05, y2, initPos3[k][1]-0.05);
					glVertex3f(initPos3[k][0]+0.05, y2, initPos3[k][1]+0.05);	
				
					//back
					glColor3ub(playerColorDark[i][0], playerColorDark[i][1], playerColorDark[i][2]);
					glVertex3f(initPos3[k][0]-0.125, y1, initPos3[k][1]-0.125);	
					glVertex3f(initPos3[k][0]+0.125, y1, initPos3[k][1]-0.125);
					glColor3ub(playerColor[i][0], playerColor[i][1], playerColor[i][2]);
					glVertex3f(initPos3[k][0]+0.05, y2, initPos3[k][1]-0.05);
					glVertex3f(initPos3[k][0]-0.05, y2, initPos3[k][1]-0.05);
					glEnd();
				}
				if(i==3){
					glBegin(GL_QUADS);
					glColor3ub(playerColorDark[i][0], playerColorDark[i][1], playerColorDark[i][2]);
					glVertex3f(initPos4[k][0]-0.125, y1, initPos4[k][1]+0.125);
					glVertex3f(initPos4[k][0]-0.125, y1, initPos4[k][1]-0.125);	
					glVertex3f(initPos4[k][0]+0.125, y1, initPos4[k][1]-0.125);
					glVertex3f(initPos4[k][0]+0.125, y1, initPos4[k][1]+0.125);
				glColor3ub(playerColor[i][0], playerColor[i][1], playerColor[i][2]);
					//upperface
					glVertex3f(initPos4[k][0]-0.05, y2, initPos4[k][1]+0.05);
					glVertex3f(initPos4[k][0]-0.05, y2, initPos4[k][1]-0.05);	
					glVertex3f(initPos4[k][0]+0.05, y2, initPos4[k][1]-0.05);
					glVertex3f(initPos4[k][0]+0.05, y2, initPos4[k][1]+0.05);
					
					//right
					glColor3ub(playerColorDark[i][0], playerColorDark[i][1], playerColorDark[i][2]);
					glVertex3f(initPos4[k][0]-0.125, y1, initPos4[k][1]+0.125);
					glVertex3f(initPos4[k][0]-0.125, y1, initPos4[k][1]-0.125);
					glColor3ub(playerColor[i][0], playerColor[i][1], playerColor[i][2]);	
					glVertex3f(initPos4[k][0]-0.05, y2, initPos4[k][1]-0.05);	
					glVertex3f(initPos4[k][0]-0.05, y2, initPos4[k][1]+0.05);
					
					//front
					glColor3ub(playerColorDark[i][0], playerColorDark[i][1], playerColorDark[i][2]);
					glVertex3f(initPos4[k][0]-0.125, y1, initPos4[k][1]+0.125);
					glColor3ub(playerColor[i][0], playerColor[i][1], playerColor[i][2]);
					glVertex3f(initPos4[k][0]-0.05, y2, initPos4[k][1]+0.05);
					glVertex3f(initPos4[k][0]+0.05, y2, initPos4[k][1]+0.05);
					glColor3ub(playerColorDark[i][0], playerColorDark[i][1], playerColorDark[i][2]);
					glVertex3f(initPos4[k][0]+0.125, y1, initPos4[k][1]+0.125);
				
					//left
					glColor3ub(playerColorDark[i][0], playerColorDark[i][1], playerColorDark[i][2]);
					glVertex3f(initPos4[k][0]+0.125, y1, initPos4[k][1]+0.125);
					glVertex3f(initPos4[k][0]+0.125, y1, initPos4[k][1]-0.125);
					glColor3ub(playerColor[i][0], playerColor[i][1], playerColor[i][2]);
					glVertex3f(initPos4[k][0]+0.05, y2, initPos4[k][1]-0.05);
					glVertex3f(initPos4[k][0]+0.05, y2, initPos4[k][1]+0.05);	
				
					//back
					glColor3ub(playerColorDark[i][0], playerColorDark[i][1], playerColorDark[i][2]);
					glVertex3f(initPos4[k][0]-0.125, y1, initPos4[k][1]-0.125);	
					glVertex3f(initPos4[k][0]+0.125, y1, initPos4[k][1]-0.125);
					glColor3ub(playerColor[i][0], playerColor[i][1], playerColor[i][2]);
					glVertex3f(initPos4[k][0]+0.05, y2, initPos4[k][1]-0.05);
					glVertex3f(initPos4[k][0]-0.05, y2, initPos4[k][1]-0.05);
					glEnd();
				}
			}
			else{
				glBegin(GL_QUADS);
				glColor3ub(playerColorDark[i][0], playerColorDark[i][1], playerColorDark[i][2]);
				glVertex3f(rc[p[i].map[k]][0]-0.125, y1, rc[p[i].map[k]][1]+0.125);
				glVertex3f(rc[p[i].map[k]][0]-0.125, y1, rc[p[i].map[k]][1]-0.125);	
				glVertex3f(rc[p[i].map[k]][0]+0.125, y1, rc[p[i].map[k]][1]-0.125);
				glVertex3f(rc[p[i].map[k]][0]+0.125, y1, rc[p[i].map[k]][1]+0.125);
			glColor3ub(playerColor[i][0], playerColor[i][1], playerColor[i][2]);
				//upperface
				glVertex3f(rc[p[i].map[k]][0]-0.05, y2, rc[p[i].map[k]][1]+0.05);
				glVertex3f(rc[p[i].map[k]][0]-0.05, y2, rc[p[i].map[k]][1]-0.05);	
				glVertex3f(rc[p[i].map[k]][0]+0.05, y2, rc[p[i].map[k]][1]-0.05);
				glVertex3f(rc[p[i].map[k]][0]+0.05, y2, rc[p[i].map[k]][1]+0.05);
				
				//right
				glColor3ub(playerColorDark[i][0], playerColorDark[i][1], playerColorDark[i][2]);
				glVertex3f(rc[p[i].map[k]][0]-0.125, y1, rc[p[i].map[k]][1]+0.125);
				glVertex3f(rc[p[i].map[k]][0]-0.125, y1, rc[p[i].map[k]][1]-0.125);	
				glColor3ub(playerColor[i][0], playerColor[i][1], playerColor[i][2]);
				glVertex3f(rc[p[i].map[k]][0]-0.05, y2, rc[p[i].map[k]][1]-0.05);	
				glVertex3f(rc[p[i].map[k]][0]-0.05, y2, rc[p[i].map[k]][1]+0.05);
				
				//front
				glColor3ub(playerColorDark[i][0], playerColorDark[i][1], playerColorDark[i][2]);
				glVertex3f(rc[p[i].map[k]][0]-0.125, y1, rc[p[i].map[k]][1]+0.125);
				glColor3ub(playerColor[i][0], playerColor[i][1], playerColor[i][2]);
				glVertex3f(rc[p[i].map[k]][0]-0.05, y2, rc[p[i].map[k]][1]+0.05);
				glVertex3f(rc[p[i].map[k]][0]+0.05, y2, rc[p[i].map[k]][1]+0.05);
				glColor3ub(playerColorDark[i][0], playerColorDark[i][1], playerColorDark[i][2]);
				glVertex3f(rc[p[i].map[k]][0]+0.125, y1, rc[p[i].map[k]][1]+0.125);
			
				//left
				glColor3ub(playerColorDark[i][0], playerColorDark[i][1], playerColorDark[i][2]);
				glVertex3f(rc[p[i].map[k]][0]+0.125, y1, rc[p[i].map[k]][1]+0.125);
				glVertex3f(rc[p[i].map[k]][0]+0.125, y1, rc[p[i].map[k]][1]-0.125);
				glColor3ub(playerColor[i][0], playerColor[i][1], playerColor[i][2]);
				glVertex3f(rc[p[i].map[k]][0]+0.05, y2, rc[p[i].map[k]][1]-0.05);
				glVertex3f(rc[p[i].map[k]][0]+0.05, y2, rc[p[i].map[k]][1]+0.05);	
			
				//back
				glColor3ub(playerColorDark[i][0], playerColorDark[i][1], playerColorDark[i][2]);
				glVertex3f(rc[p[i].map[k]][0]-0.125, y1, rc[p[i].map[k]][1]-0.125);	
				glVertex3f(rc[p[i].map[k]][0]+0.125, y1, rc[p[i].map[k]][1]-0.125);
				glColor3ub(playerColor[i][0], playerColor[i][1], playerColor[i][2]);
				glVertex3f(rc[p[i].map[k]][0]+0.05, y2, rc[p[i].map[k]][1]-0.05);
				glVertex3f(rc[p[i].map[k]][0]-0.05, y2, rc[p[i].map[k]][1]-0.05);
				glEnd();
			}
		}
		
	}
	
  
	for(int i=0;i<4;i++){
		glColor3ub(playerColor[i][0], playerColor[i][1], playerColor[i][2]);
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
//glMatrixMode(GL_MODELVIEW); 	
glLoadIdentity();                 // Reset the model-view matrix
   glTranslatef(0.0f, 0.0f, -7.0f);  // Move right and into the screen
   
   	 glRotatef(angleCube, 1.0f, 0.0f, 0.0f);
   glRotatef(angleCubey, 0.0f, 1.0f, 0.0f);

   	glRotated(camera_angle_v, 1.0, 0.0, 0.0);
	glRotated(camera_angle_h, 0.0, 1.0, 0.0);
		
   glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
      // Top face (y = 1.0f)
      // Define vertices in counter-clockwise (CCW) order with normal pointing out
      glColor3ub(base[0][0], base[0][1], base[0][2]);     // Green
      
      glVertex3f( x, y, -x);
      glVertex3f(-x, y, -x);
      glVertex3f(-x, y,  x);
      glVertex3f( x, y,  x);
 
      // Bottom face (y = -1.0f)
      glColor3ub(base[1][0], base[1][1], base[1][2]);     // Green
      glVertex3f( x, -y,  -x);
      glVertex3f(-x, -y,  -x);
      glVertex3f(-x, -y, x);
      glVertex3f( x, -y, x);
  
      // Front face  (z = 1.0f)
      
      glVertex3f(x,  y, x);
      glVertex3f(-x,  y, x);
      glVertex3f(-x, -y, x);
      glVertex3f( x, -y, x);
 
      // Back face (z = -1.0f)
      
      glVertex3f( x, -y, -x);
      glVertex3f(-x, -y, -x);
      glVertex3f(-x,  y, -x);
      glVertex3f( x,  y, -x);
 
      // Left face (x = -1.0f)
      
      glVertex3f(-x,  y,  x);
      glVertex3f(-x,  y, -x);
      glVertex3f(-x, -y, -x);
      glVertex3f(-x, -y,  x);
 
      // Right face (x = 1.0f)
      
      glVertex3f(x,  y, -x);
      glVertex3f(x,  y,  x);
      glVertex3f(x, -y,  x);
      glVertex3f(x, -y, -x);
   glEnd();  // End of drawing color-cube 	
   glFlush();
   
}

void display(){
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
   	glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
	drawBase();
	drawHomeLines();
	drawLines();
	drawCubes();
	drawPlayers();
	drawSafeZones();
	drawHomeFinal();
	view1();
	textDisplay();
	showLudo();
	glutSwapBuffers();  
}

void mouse_click(int button, int state, int x, int y){
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

void keyPressed (unsigned char key, int x, int y){ 
	 switch(key)
	{
		case '1': 
				if(i==0){
					gamePlay_user(0); 
				}
				break;
		case '2': 
				if(i==0){
					gamePlay_user(1); 
				}
				break;
		case '3': if(i==0){
					gamePlay_user(2); 
				}	
				break;
		case '4': if(i==0){
				gamePlay_user(3); 
				}
				break;
		case '5': if(i==1 || i==2 || i==3){
					gamePlay();
				}
				break;
		default: ;//exit(1); 
		break;
	};
}

void showLudo(){
	glLoadIdentity();                 // Reset the model-view matrix
   	glTranslatef(1.5f, 0.0f, -7.0f);  // 
	glLineWidth(9);
	glColor3ub(51,255,153);
	float s = 0.0, inY = 1.8;

	glBegin(GL_LINES);
	  glVertex3f(-1.8,0.8+inY, s);
	  glVertex3f(-1.8,0.4+inY, s);
	  glVertex3f(-1.8,0.4+inY, s); //L
	  glVertex3f(-1.6,0.4+inY, s);
	  glEnd();
      glFlush();

      glBegin(GL_LINES);
	  glVertex3f(-1.5,0.4+inY, s);
	  glVertex3f(-1.5,0.7+inY, s);
	  glVertex3f(-1.5,0.4+inY, s);  //U
	  glVertex3f(-1.3,0.4+inY, s);
	  glVertex3f(-1.3,0.4+inY, s);
	  glVertex3f(-1.3,0.7+inY, s);
	  glEnd();
      glFlush();

      glBegin(GL_LINES);
	  glVertex3f(-1.1,0.38+inY, s);
	  glVertex3f(-1.1,0.83+inY, s);
	  glVertex3f(-1.125,0.815+inY, s);  //D
	  glVertex3f(-0.95,0.6+inY, s);
	  glVertex3f(-0.95,0.6+inY, s);
	  glVertex3f(-1.125,0.4+inY, s);
	  glEnd();
	  glFlush();

	  glBegin(GL_LINES);
	  glVertex3f(-0.93,0.38+inY, s);
	  glVertex3f(-0.7,0.7+inY, s);
	  glVertex3f(-0.7,0.7+inY, s);   //O
	  glVertex3f(-0.6,0.38+inY, s);
	  glVertex3f(-0.93,0.38+inY, s);
	  glVertex3f(-0.6,0.38+inY, s);
	  glEnd();
	  glFlush();
}
void showInfo(int i, float x, float y, float z, void *font,const char *string){
	const char *c;
	
    glColor3ub(playerColor[i][0], playerColor[i][1], playerColor[i][2]);
    glRasterPos3f(x, y, z);
    for (c=string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void textDisplay(){
		
		if(winning==0){
			renderBitmapString( -43.0,  -5.0,  -5.0, (void *)font, "You won!");
		}
		else if(winning==1||winning==2||winning==3){
			renderBitmapString( -43.0,  -5.0,  -5.0, (void *)font, "You lost.");
		}
		renderBitmapString(-10.0, 0.0, -5.0,(void *)font,string[i]);
		renderBitmapString(-45.0, 0.0, -5.0,(void *)font,rules1);
		renderBitmapString(-44.5, 2.0, -5.0,(void *)font,rules2);
	
		showInfo(0, -65.0, -30.0, -5.0,(void *)font1,"You");
		showInfo(1, -71.0, -40.0, -5.0,(void *)font1,"Player 2");
		showInfo(2, -77.0, -50.0, -5.0,(void *)font1,"Player 3");
		showInfo(3, -83.0, -60.0, -5.0,(void *)font1,"Player 4");
	
		glPushAttrib( GL_LIGHTING_BIT );  // << here
		glDisable( GL_LIGHTING );
		renderBitmapStringForPlayers(0,(void *)font);
		renderBitmapStringForPlayers(1,(void *)font);
		renderBitmapStringForPlayers(2,(void *)font);
		renderBitmapStringForPlayers(3,(void *)font);
		glPopAttrib();		
		
}
void renderBitmapString(float x, float y, float z, void *font,const char *string){
    const char *c;
    glColor3ub(255, 255, 255);
    glRasterPos3f(x, y, z);
    for (c=string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}  
void renderBitmapStringForPlayers(int k, void *font){
    const char *c ;
    const char string[4][2] = {"1", "2", "3", "4"};
    float y1 = y+0.02f, y2 = y1+0.25f;
    glLoadIdentity();                 // Reset the model-view matrix
   	glTranslatef(0.0f, 0.0f, -7.0f);  // Move right and into the screen
   	glRotatef(angleCube, 1.0f, 0.0f, 0.0f);
   	glRotatef(angleCubey, 0.0f, 1.0f, 0.0f);
   	glRotated(camera_angle_v, 1.0, 0.0, 0.0);
	glRotated(camera_angle_h, 0.0, 1.0, 0.0);
    glColor3ub(255, 255, 255);
    if(!p[0].active[k]){
    	glRasterPos3f(initPos1[k][0]+0.1, y2+0.02, initPos1[k][1]+0.1);
    }
    else{
    	glRasterPos3f(rc[p[0].map[k]][0], y2+0.18, rc[p[0].map[k]][1]);
    }
    for (c=string[k]; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}  
void mouse_move(int x, int y){
    if(dragging) {
        camera_angle_v += (y - drag_y_origin)*0.3;
        camera_angle_h += (x - drag_x_origin)*0.3;
        drag_x_origin = x;
        drag_y_origin = y;
    }
    glutPostRedisplay();
}
void reshape(GLsizei width, GLsizei height){  
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
void initGL(){
	//LoadTGAFile(&textures, painting2);
	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	//glEnable(GL_TEXTURE_2D);
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClearDepth(1.0f);                   // Set background depth to farthest
   glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
   glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
   glShadeModel(GL_SMOOTH);   // Enable smooth shading
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}

int main(int argc, char** argv){
	GLint rand();
	 srand (time(NULL));
	dNum = rand()%6 + 1;
	printf("Dice %d\n", dNum);
	
	for(int i =0;i<4;i++){
		for(int j=0;j<4;j++){
			p[i].active[j] = false;
			p[i].home[j] = false;
			p[i].final_home[j] = false;
			p[i].map[j] = -1;
		}
	}
	for(int i=0;i<52;i++){
		for(int j = 0;j<2;j++){
			MAP1[i][j] = -1;
		}
	}
	glutInit(&argc, argv);            
	glutInitDisplayMode(GLUT_DOUBLE); 
	glutInitWindowSize(1400, 1100);   
	glutInitWindowPosition(50, 50); 
	glutCreateWindow(title);        
	glutDisplayFunc(display);       
	glutReshapeFunc(reshape);       
	
	glutMouseFunc(mouse_click);
	glutMotionFunc(mouse_move);
	glutKeyboardFunc(keyPressed);
	initGL();   
	
	glutMainLoop();
	return 0;
}
