#ifndef __Draw_sharp
#define __Draw_sharp
#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Window.H>

#include <glut.h>
#include <gl/gl.h>

class Draw_sharp : public Fl_Gl_Window{


	static void Timer_CB(void *userdata) {
		Draw_sharp *pb = (Draw_sharp*)userdata;
		pb->redraw();
		Fl::repeat_timeout(1.0 / 24.0, Timer_CB, userdata);
	}

public:
	void draw();
	Draw_sharp(int x, int y, int w, int h, const char *l = 0);
	int draw_number; //mode模式
	//int draw_open;
	int frame;
	int valid = 0;
	int rot1 = 0;
	int rot2 = 0;
	int old_rot_x = 0;   //剛按下滑鼠時的視窗座標
	int old_rot_y = 0;

	int rot_x = 0;      //拖曳後的相對座標，用這決定要旋轉幾度
	int rot_y = 0;

	int record_x = 0;      //紀錄上一次旋轉的角度
	int record_y = 0;
};
#endif
