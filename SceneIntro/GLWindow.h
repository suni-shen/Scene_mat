#pragma once

#include "GLContext.h"

class   OpenGLWindow :public GLContext
{
protected:
	int     _width;
	int     _height;
public:

	OpenGLWindow(HINSTANCE hInst = 0)
	{
		//1 注册窗口类
		WNDCLASSEX  wnd;

		memset(&wnd, 0, sizeof(wnd));

		wnd.cbSize = sizeof(wnd);
		wnd.lpfnWndProc = wndProc;
		wnd.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
		wnd.hCursor = LoadCursor(hInst, IDC_ARROW);
		wnd.hIcon = 0;
		wnd.hIconSm = 0;
		wnd.hInstance = 0;
		wnd.lpszClassName =  "Graph" ;
		wnd.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

		RegisterClassEx(&wnd);
	}


	virtual bool    main(int w, int h)
	{
		//2 创建窗口
		HWND hWnd = CreateWindowEx(
			0
			,  "Graph" 
			,  "窗口标题" 
			, WS_OVERLAPPEDWINDOW
			, 10
			, 10
			, w
			, h
			, 0
			, 0
			, 0
			, this);

		//!3    更新显示
		if (hWnd)
		{
			UpdateWindow(hWnd);
			ShowWindow(hWnd, SW_SHOW);
		}

		else
		{
			return  false;
		}

		if (!setup(hWnd, GetDC(hWnd)))
		{
			return  false;
		}



		MSG     msg = { 0 };

		//4 消息循环
		while (WM_QUIT != msg.message)
		{

			if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				RECT    rect;
				GetClientRect(hWnd, &rect);

				_width = rect.right - rect.left;
				_height = rect.bottom - rect.top;

				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				glViewport(0, 0, _width, _height);

				render();

				swapBuffer();
			}
		}
		shutdown();
		return  true;
	}

	virtual void    render()
	{
	}

	/**
	*   消息处理过程
	*/
	virtual LRESULT events(UINT msgId, WPARAM wParam, LPARAM lParam)
	{
		switch (msgId)
		{
		case WM_CLOSE:
		case WM_DESTROY:
		{
			PostQuitMessage(0);
		}
		break;
		default:
			return DefWindowProc(_hWnd, msgId, wParam, lParam);
		}
		return  0;
	}
protected:
	static  LRESULT CALLBACK  wndProc(HWND hWnd, UINT msgId, WPARAM wParam, LPARAM lParam)
	{
		if (msgId == WM_CREATE)
		{
			LPCREATESTRUCT  pData = (LPCREATESTRUCT)lParam;
			OpenGLWindow* pTHis = (OpenGLWindow*)pData->lpCreateParams;
			SetWindowLong(hWnd, GWL_USERDATA, (LONG)pTHis);
			return DefWindowProc(hWnd, msgId, wParam, lParam);
		}
		else
		{
			OpenGLWindow* pTHis = (OpenGLWindow*)GetWindowLong(hWnd, GWL_USERDATA);
			if (pTHis)
			{
				return  pTHis->events(msgId, wParam, lParam);
			}
			else
			{
				return DefWindowProc(hWnd, msgId, wParam, lParam);
			}
		}
	}
};