#include "Draw_sharp.h"
Draw_sharp::Draw_sharp(int x, int y, int w, int h, const char *l) :
Fl_Gl_Window(x, y, w, h, l)
{
	mode(FL_RGB | FL_ALPHA | FL_DOUBLE | FL_STENCIL);
	Fl::add_timeout(1.0 / 24.0, Timer_CB, (void*)this);
	frame = 0;
}

void Draw_sharp::draw() {
	// the valid() property may be used to avoid reinitializing your GL transformation for each redraw:
	if (!valid) {
		valid = 1;
		glLoadIdentity();
		glViewport(0, 0, w(), h());
		glClearColor(1.0, 1.0, 1.0, 1.0);
	}
	if (draw_number == 1){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glPushMatrix();
		//glutWireCube(0.3);
		glBegin(GL_POINTS); //點點出不來凸
		glColor3f(1.0, 0.0, 0.0);
		glVertex2f(0.1, 0.1);
		glEnd();

		glBegin(GL_QUADS);//身體
		glColor3f(1.0, 0.0, 0.0);
		glVertex2f(-0.2, -0.2);
		glVertex2f(-0.2, 0.2);
		glVertex2f(0.2, 0.2);
		glVertex2f(0.2, -0.2);
		glEnd();

		glPushMatrix();
		glTranslatef(0.15, 0.15, 0);//Y軸向上移動0.1 X軸也向右移動0.1
		glRotatef(-rot1, 0, 0, 1); //現在是面向Z軸
		//glutWireCube(0.1);
		glBegin(GL_QUADS);//右手1
		glColor3f(0.0, 1.0, 0.0);
		glVertex2f(0.2, 0.2);// 0.4
		glVertex2f(0.2, 0);
		glVertex2f(0, 0);//0.2
		glVertex2f(0, 0.2);
		glEnd();

		glPushMatrix();
		glTranslatef(0.15, 0.15, 0);//Y軸向上移動0.1 X軸也左移動0.1
		glRotatef(rot2, 0, 0, 1); //現在是面向Z軸
		//glutWireCube(0.1);
		glBegin(GL_QUADS);//右手2
		glColor3f(0.0, 0.0, 1.0);
		glVertex2f(0.2, 0.2);// 0.4
		glVertex2f(0.2, 0);
		glVertex2f(0, 0);//0.2
		glVertex2f(0, 0.2);
		glEnd();
		glPopMatrix();
		glPopMatrix();

		glPushMatrix();  //回到身體
		glTranslatef(-0.15, 0.15, 0);//Y軸向上移動0.1 X軸也向右移動0.1
		glRotatef(-rot_x, 0, 0, 1); //現在是面向Z軸
		//glutWireCube(0.1);
		glBegin(GL_QUADS);//左手1
		glColor3f(0.0, 1.0, 0.0);
		glVertex2f(-0.2, 0.2);// 0.4
		glVertex2f(-0.2, 0);
		glVertex2f(0, 0);//0.2
		glVertex2f(0, 0.2);
		glEnd();

		glPushMatrix();
		glTranslatef(-0.15, 0.15, 0);//Y軸向上移動0.1 X軸也左移動0.1
		glRotatef(-rot_x, 0, 0, 1); //現在是面向Z軸
		//glutWireCube(0.1);
		glBegin(GL_QUADS);//左手2
		glColor3f(0.0, 0.0, 1.0);
		glVertex2f(-0.2, 0.2);// 0.4
		glVertex2f(-0.2, 0);
		glVertex2f(0, 0);//0.2
		glVertex2f(0, 0.2);
		glEnd();
		glPopMatrix();
		glPopMatrix();

		glPopMatrix();
	}
	++frame;
}

/*
glTranslatef(0.0, 0.1f, 0.0);
glColor3f(0.0, 255.0, 0.0);
glBegin(GL_QUAD_STRIP);
glVertex3f(0.9, -0.45, 1.3);
glVertex3f(-0.9, -0.45, 1.3);
glVertex3f(0.9, -0.1, 1.7);
glVertex3f(-0.9, -0.1, 1.7);
glVertex3f(0.9, 0.45, 1.3);
glVertex3f(-0.9, 0.45, 1.3);
glVertex3f(0.9, 0.45, -1.3);
glVertex3f(-0.9, 0.45, -1.3);
glVertex3f(0.9, -0.1, -1.7);
glVertex3f(-0.9, -0.1, -1.7);
glVertex3f(0.9, -0.45, -1.3);
glVertex3f(-0.9, -0.45, -1.3);
glVertex3f(0.9, -0.45, 1.3);
glVertex3f(-0.9, -0.45, 1.3);
glEnd();
*/