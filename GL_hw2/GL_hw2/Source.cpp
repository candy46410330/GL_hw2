/**********************************************************************************************************/
//姓名:楊方寧
//學號 : 605415032
//E - mail : candy46410330@yahoo.com.tw
//作業環境 : Win10 64bit
//編譯器 : Visual Studio 2013

//備註：
//	1.所有相關程式碼在hw2_605415032\GL_hw2資料夾下。
//  2.demo_605415032.mp4為程式實際執行狀況影片
/**********************************************************************************************************
 指定作業功能 :
   1.Robot 2D 形狀&關節點 :
	   1個身體上有1顆頭2隻手2隻腳, 身體可以左右移動, 頭上有1個關節點可以上下移動, 手腳分別各有2個關節點可以轉動

   2.手動 mode :
	   (1)操控方式為按滑鼠移動的位移做為機器人判斷要動左右方向及上下方向及旋轉角度
	   滑鼠位移(+, +)身體往右平移, 機器人頭往上移動, 操控右手向上.操控右腳往後
	   滑鼠位移(+, -)身體往右平移, 機器人頭往上移動, 操控右手向下.操控右腳往前
	   滑鼠位移(-, +)身體往左平移, 機器人頭往下移動, 操控左手向上.操控左腳往後
	   滑鼠位移(-, -)身體往左平移, 機器人頭往下移動, 操控左手向下.操控左腳往前
	   (2)軀幹角度受限於設計的自由度, 上限90度, 下限 - 60度, 不同關節旋轉的角度不同
	   平移的距離也有受限, 超過會移動到初始設定值
	   (3)有讓機器人有一點雙腳跳起來的感覺

	3.自動 mode:
       (1)一隻能揮手舉手和有腳張開(有一點跳起來的感覺像啦啦隊一樣)的機器人
 /**********************************************************************************************************
   額外bonus操作功能 :
       (1)一開始的畫面為自動mode, 會保持自動, 但是還可以同時手動操控想操控的地方, 不影響自動
	   (2)老師說畫出圈圈眼睛的話可以加分, 所以我畫了圓頭和2個眼睛
	   (3)exe畫面有顯示滑鼠位移量及確認滑鼠Click和Move的觸發
	   (4)在demo_605415032.mp4的影片為實際操作影片
 **********************************************************************************************************/

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <math.h>
#include<glut.h>
#define PI 3.1415926

Fl_Window *Interface;
const int n = 20; //circle
const GLfloat R = 10.0f;
const GLfloat Pi = 3.1415926536f;
static GLfloat move = 0.0;

int old_rot_x = 0;  //剛按下滑鼠時的視窗座標
int old_rot_y = 0;
int rot_x = 0;      //拖曳後的相對座標，用這決定要旋轉幾度
int rot_y = 0;
int record_x = 0;   //紀錄上一次旋轉的角度
int record_y = 0;

float value1 = 0;
float value2 = 0;
int key = 0;
float distance = 0;

void display(){
	glPushMatrix();
	//glClearColor(1.0, 1.0, 1.0, 1.0);  //(留著!!!)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glutSolidSphere(0.2, 30, 30); //點點另一種方法 
		/*int i;
		glBegin(GL_POLYGON);  //另一種三角型的方法 怪怪的
		for (i = 0; i<n; ++i)
			glColor3f(1.0, 1.0, 1.0);
			glVertex2f(R*cos(2 * Pi / n*i) + 3, R*sin(2 * Pi / n*i) + 3);
		glEnd();
		glFlush();*/
		glColor3f(1.0, 0.0, 0.0);
		glVertex2f(0.1, 0.1);
		glEnd();

		glPushMatrix();
		glTranslatef(distance, 0.3, 0); // rrot_x  +(float)rrecord_x
		glBegin(GL_QUADS);//身體
		glColor3f(1.0, 0.0, 0.0);
		glVertex2f(-0.3, -0.5);
		glVertex2f(-0.2, 0.2);
		glVertex2f(0.2, 0.2);
		glVertex2f(0.3, -0.5);
		glEnd();
//////////////////////////////////////////////////////////
		glPushMatrix();
		GLint circle_points = 100, i = 0; //利用很多邊形成圓

		glPushMatrix();
		glTranslatef(0.0, 0.32 + distance / 6, 0); //頭2
		glBegin(GL_TRIANGLE_FAN);
		for (int i = 0; i < circle_points; i++){
			double angle = 2 * PI*i / circle_points;
			glVertex3d(0.2*cos(angle), 0.2*sin(angle), 0);
			glColor3f(0.5, 0.5, 0.5);
		}
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0, 0.32+distance/6, 0); //頭2
		glBegin(GL_TRIANGLE_FAN);
		for (int i = 0; i < circle_points; i++){
			double angle = 2 * PI*i / circle_points;
			glVertex3d(0.2*cos(angle), 0.2*sin(angle), 0);
			glColor3f(0.5, 0.5, 0.5);
		}
		glEnd();
		glPopMatrix();

		glTranslatef(0.1, 0.42 + distance / 6, 0);    //右眼1
		glBegin(GL_TRIANGLE_FAN);   
		for (int i = 0; i < circle_points; i++){
			double angle = 2 * PI*i / circle_points;
			glVertex3d(0.05*cos(angle), 0.05*sin(angle), 0); 
			glColor3f(0.0, 0.0, 0.0);
		}
		glEnd();
		glPopMatrix();
		
		glPushMatrix();
		glTranslatef(0.1, 0.42 + distance / 6, 0); //右眼2(疊上去)
		glBegin(GL_TRIANGLE_FAN);
		for (int i = 0; i < circle_points; i++){
			double angle = 2 * PI*i / circle_points;
			glVertex3d(0.05*cos(angle), 0.05*sin(angle), 0); 
			glColor3f(0.0, 0.0, 0.0);
		}
		glEnd();
		glPopMatrix();
		
		glPushMatrix();
		glTranslatef(-0.1, 0.42 + distance / 6, 0); //左眼
		glBegin(GL_TRIANGLE_FAN);
		for (int i = 0; i < circle_points; i++){
			double angle = 2 * PI*i / circle_points;
			glVertex3d(0.05*cos(angle), 0.05*sin(angle), 0);
			glColor3f(0.0, 0.0, 0.0);
		}
		glEnd();
		glPopMatrix();
		
		glPushMatrix();
		glTranslatef(0, 0.35 + distance / 6, 0); //鼻子 三角形
		glBegin(GL_TRIANGLE_FAN);
		for (int i = 0; i < 3; i++){
			double angle = 2 * PI*i / 3;
			glVertex3d(0.05*sin(angle), 0.05*cos(angle), 0);
			glColor3f(1.0, 1.0, 1.0);
		}
		glEnd();
		glPopMatrix();
		
		glPushMatrix();
		glTranslatef(0, distance / 6, 0);
		glBegin(GL_QUADS);//嘴巴
		glColor3f(1.0, 1.0, 0.0);//黃
		glVertex2f(0.16, 0.27);
		glVertex2f(0.1, 0.23);
		glVertex2f(-0.1, 0.23);
		glVertex2f(-0.16, 0.27);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0, distance / 6, 0);
		glBegin(GL_QUADS);//嘴巴
		glColor3f(1.0, 1.0, 1.0);//黃
		glVertex2f(0.01, 0.18);
		glVertex2f(0.01, 0.16);
		glVertex2f(-0.01, 0.16);
		glVertex2f(-0.01, 0.18);
		glEnd();
		glPopMatrix();
////////////////////////////////////////////
		glPushMatrix();
			glTranslatef(0.15, 0.15, 0);
			glRotatef(-value2, 0, 0, 1); //現在是面向Z軸
			glBegin(GL_QUADS);//右手1
			glColor3f(0.0, 1.0, 0.0);
			glVertex2f(0.2, 0.2);
			glVertex2f(0.2, 0);
			glVertex2f(0, 0);
			glVertex2f(0, 0.2);
			//glEnd();   //有點不懂為何不用加 加了會飛走 = =

			glPushMatrix();
			glRotatef(0, 0, 0, 1); 
			glBegin(GL_QUADS);//右手點點1
			glColor3f(1.0, 1.0, 1.0);
			glVertex2f(0.02, 0.0);
			glVertex2f(0.02, 0.02);
			glVertex2f(0.0, 0.02);
			glVertex2f(0.0, 0.0);
			glEnd();
				
			glPushMatrix();
			glTranslatef(0.15, 0.15, 0);
			glRotatef(-(value2)/2, 0, 0, 1); 
			glBegin(GL_QUADS);//右手2
			glColor3f(0.0, 0.0, 1.0);
			glVertex2f(0.3, 0.0);
			glVertex2f(0.3, 0.2);
			glVertex2f(0.0, 0.2);
			glVertex2f(0.0, 0.0);
			glEnd();
				
			glPushMatrix();
			glTranslatef(0.15, 0.15, 0);
			glRotatef(0, 0, 0, 1); 
			glBegin(GL_QUADS);//右手點點2
			glColor3f(1.0, 1.0, 1.0);
			glVertex2f(-0.15, -0.13);
			glVertex2f(-0.15, -0.15);
			glVertex2f(-0.13, -0.15);
			glVertex2f(-0.13, -0.13);
			glEnd();
			
			glPopMatrix();
			glPopMatrix();
			glPopMatrix(); //回到身體
//////////////////////////////////
		glPushMatrix();
		//glRotatef(-value1 , 0, 0, 1);
		glTranslatef(-0.1, -0.45, 0);
		glRotatef(-value1, 0, 0, 1); 
		glBegin(GL_QUADS);//左腳1
		glColor3f(0.0, 1.0, 0.0);
		glVertex2f(-0.1, -0.35);
		glVertex2f(-0.1, -0.0);
		glVertex2f(-0.0, -0.0);
		glVertex2f(-0.0, -0.35);
		//glEnd();

		glPushMatrix();
		//glRotatef(0, 0, 0, 1); 
		glBegin(GL_QUADS);//左腳點點1
		glColor3f(1.0, 1.0, 1.0);
		glVertex2f(-0.02, -0.02);
		glVertex2f(-0.02, 0.0);
		glVertex2f(0.0, 0.0);
		glVertex2f(0.0, -0.02);
		//glEnd();
		//glPopMatrix();

		glPushMatrix();
		//glTranslatef(0.1, -0.1, 0);
		glRotatef(-(value1) / 2, 0, 0, 1); 
		glBegin(GL_QUADS);//左腳2
		glColor3f(0.0, 0.0, 1.0);
		glVertex2f(-0.35, -0.25);
		glVertex2f(-0.35, -0.4);
		glVertex2f(-0.05, -0.4);
		glVertex2f(-0.05, -0.25);
		glEnd();

		glPushMatrix();
		glTranslatef(-0.1, -0.45, 0);
		//glRotatef(0, 0, 0, 1); 
		glBegin(GL_QUADS);//左腳點點2
		glColor3f(1.0, 1.0, 1.0);
		glVertex2f(0.03, 0.2);
		glVertex2f(0.03, 0.18);
		glVertex2f(0.05, 0.18);
		glVertex2f(0.05, 0.2);
		glEnd();
		glPopMatrix();
		glPopMatrix();
		//glPopMatrix();
/////////////////////////////////////////
		glPushMatrix();
		glTranslatef(0.2, -0.45, 0);
		glRotatef(value2, 0, 0, 1); 
		glBegin(GL_QUADS);//右腳1
		glColor3f(0.0, 1.0, 0.0);
		glVertex2f(-0.1, -0.35);
		glVertex2f(-0.1, -0.0);
		glVertex2f(-0.0, -0.0);
		glVertex2f(-0.0, -0.35);
		//glEnd();

		glPushMatrix();
		//glRotatef(0, 0, 0, 1); 
		glBegin(GL_QUADS);//右腳點點1
		glColor3f(1.0, 1.0, 1.0);
		glVertex2f(-0.02, -0.02);
		glVertex2f(-0.02, 0.0);
		glVertex2f(0.0, 0.0);
		glVertex2f(0.0, -0.02);
		//glEnd();
		//glPopMatrix();

		glPushMatrix();
		glRotatef((value2)/2, 0, 0, 1);
		glTranslatef(0.2 + distance, -0.1, 0);
		glBegin(GL_QUADS);//右腳2
		glColor3f(0.0, 0.0, 1.0);
		glVertex2f(0.25, -0.25);
		glVertex2f(0.25, -0.4);
		glVertex2f(-0.05, -0.4);
		glVertex2f(-0.05, -0.25);
		glEnd();

		glPushMatrix();
		glTranslatef(0.2, -0.45, 0);
		glRotatef(0, 0, 0, 1); 
		glBegin(GL_QUADS);//右腳點點2
		glColor3f(1.0, 1.0, 1.0);
		glVertex2f(-0.23, 0.2);
		glVertex2f(-0.23, 0.18);
		glVertex2f(-0.25, 0.18);
		glVertex2f(-0.25, 0.2);
		glEnd();
		glPopMatrix();
		glPopMatrix();
		//glPopMatrix();
		//glPopMatrix();
		//glPopMatrix();
//////////////////////////////////
		glPushMatrix();  
			glTranslatef(-0.15, 0.15, 0);
			glRotatef(value1, 0, 0, 1); 
			glBegin(GL_QUADS);//左手1
			glColor3f(0.0, 1.0, 0.0);
			glVertex2f(-0.2, 0.2);
			glVertex2f(-0.2, 0);
			glVertex2f(0, 0);
			glVertex2f(0, 0.2);
			glEnd();
			
			glPushMatrix();
			glRotatef(0, 0, 0, 1); 
			glBegin(GL_QUADS);//左手點點1
			glColor3f(1.0, 1.0, 1.0);
			glVertex2f(-0.02, 0.02);
			glVertex2f(-0.02, -0.0);
			glVertex2f(-0.0, -0.0);
			glVertex2f(-0.0, 0.02);
			glEnd();
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-0.15, 0.15, 0);
				glRotatef((value1)/2, 0, 0, 1); 
				glBegin(GL_QUADS);//左手2
				glColor3f(0.0, 0.0, 1.0);
				glVertex2f(-0.3, 0.2);
				glVertex2f(-0.3, 0);
				glVertex2f(0, 0);
				glVertex2f(0, 0.2);
				glEnd();
				
				glPushMatrix();
				glTranslatef(-0.15, 0.15, 0);
				glRotatef(0, 0, 0, 1); 
				glBegin(GL_QUADS);//左手點點2
				glColor3f(1.0, 1.0, 1.0);
				glVertex2f(0.13, -0.15);
				glVertex2f(0.13, -0.13);
				glVertex2f(0.15, -0.13);
				glVertex2f(0.15, -0.15);
				glEnd();
				glPopMatrix();

			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	//////////////////自動部分////////////////////////////
	//value1 = value1>45 ? value1 -= 10 : value1 += 0.05; //可以替代下面的整段了...= =
	for (int count3 = 0; count3 < 2; count3++){
		for (int count1 = 0; count1 < 2; count1++){
			value1 += 0.05;
			value2 += 0.05;
			distance += 0.0001;
			glFlush();
			if (value1>=90){
				//value1 = 90;     //怪怪的沒變????
				for (int count2 = 0; count2 < 10; count2++)
					value1 -= 5;
					//Sleep(100);
			}
			if (value2 >= 90){
				for (int count2 = 0; count2 < 10; count2++)
					value2 -= 5;
			}
			if (distance >= 0.3){
				for (int count2 = 0; count2 < 40; count2++)
					distance -= 0.01;
			}
		}
		/*for (int count2 = 0; count2 < 2; count2++){    //怪怪的沒變????
			value1 -= 1;
			glFlush();
		}
		glFlush();*/
	}
	glFlush();
	glutSwapBuffers();
}
//////////////////手動部分////////////////////////////
void mouseMove( int x, int y){//(後做)滑鼠按住並移動的狀態下，所經過的視窗座標 
	printf("Move\n");
	rot_x = x - old_rot_x;
	rot_y = y - old_rot_y;

	if (rot_x >= 0){
		if (rot_y >= 0)
			if (value2 > 90)
				value2 = 90;
			else
				value2 += 10;
		else if (rot_y<0)
			if (value2 < -60)
				value2 = -60;
			else
				value2 -= 10;
	}
	else if (rot_x<0){
		if (rot_y >= 0){
			if (value1 > 90)
				value1 = 90;
			else
				value1 += 10;
		}
		else if (rot_y < 0){
			if (value1 < -60)
				value1 = -60;
			else
				value1 -= 10;
		}
	}
	//key = 1;
	if (rot_x >= 0)
		distance += 0.02;
	else if (rot_x<0)
		distance -= 0.02;

	Sleep(10);
	glutPostRedisplay();
}
void mouseClick(int button, int state, int x, int y){//(先做)指定一個自定函式接收滑鼠按下和放開時的訊息，按住和沒按住的過程並沒有動作 
//button:按左鍵時值為0，按右鍵值為2(中間按鍵大概是1) 
//state:按下時值為0，放開時值為1 
//x,y是按下和放開時的視窗座標 
	printf("此時視窗內的滑鼠位移座標是(%d,%d)\n", rot_x, -rot_y);
	printf("Click\n");
	if (state){
		record_x += x - old_rot_x;
		record_y += y - old_rot_y;
		//rot_x = 0;   //沒有歸零會有不理想的結果
		//rot_y = 0;
	}else{
		old_rot_x = x;
		old_rot_y = y;
	}
	if (state == GLUT_DOWN){
		if (button == GLUT_LEFT_BUTTON){ //&& state == GLUT_DOWN
			//key = 1;
			if (rot_x >= 0){
				if (rot_y >= 0)
					value2 -= 10;
				else if (rot_y<0)
					value2 += 10;
			}else if(rot_x<0){
				if (rot_y >= 0)
					value1 += 10;
				else if (rot_y<0)
					value1 -= 10;
			}
			key = 1;
			if (rot_x>=0)
				distance += 0.02;
			else if (rot_x<0)
				distance -= 0.02;
		}
		if (button == GLUT_RIGHT_BUTTON){
			key = 2;
		}
		if (button == GLUT_MIDDLE_BUTTON){
			key = 2;
			for (int counter1 = 0; counter1 < 30; counter1++){
				distance += 0.02;
			}
			for (int counter2 = 0; counter2 < 30; counter2++){
				distance -= 0.02;
			}
		}
		key = 0;
	}
}
int main(int argc, char**argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Robot");
	glutMouseFunc(mouseClick); //指定一個自定函式接收滑鼠按下和放開時的訊息，按住和沒按住的過程並沒有動作 
	glutMotionFunc(mouseMove); //滑鼠按住並移動的狀態下，所經過的視窗座標
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutMainLoop();
}
//counter += 1.1;
//if (counter > 200)
//counter = 0.0;