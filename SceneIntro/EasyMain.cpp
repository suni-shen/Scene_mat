
#include <windows.h>
#include <tchar.h>

#include "GLWindow.h"


class   EasyWindow :public OpenGLWindow
{
public:
	EasyWindow(HINSTANCE hInst = 0) :OpenGLWindow(hInst)
	{

	}

	virtual void    render()
	{
		//! 指定以下的操作针对投影矩阵
		glMatrixMode(GL_PROJECTION);
		//! 将投影举证清空成单位矩阵
		glLoadIdentity();
		glOrtho(0, _width, _height, 0, -100, 100);

		glColor3f(1, 1, 1);
		glBegin(GL_TRIANGLES);

		glVertex3f(_width * 0.5f, 0, 0);
		glVertex3f(_width, _height, 0);
		glVertex3f(0, _height, 0);

		glEnd();
	}
};

int __stdcall WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd
)
{

	EasyWindow    instance(hInstance);
	instance.main(800, 600);


	return  0;
}