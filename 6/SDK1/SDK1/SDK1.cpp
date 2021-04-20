#include <windows.h>
#include "resource.h"
#include <stdlib.h>
#include <string.h>

long WINAPI WndProc(HWND hWnd,
	UINT iMessage,
	UINT wParam,
	LONG lParam);					//消息处理函数声明.

BOOL InitWindowsClass(HINSTANCE hInstance);			//初始化窗口类声明
BOOL InitWindows(HINSTANCE hInstance, int nCmdShow);//初始化窗口声明.

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)			//主函数
{
	MSG Message;
	if (!InitWindowsClass(hInstance))		//初始化窗口类.
		return FALSE;
	if (!InitWindows(hInstance, nCmdShow))	//初始化窗口.
		return FALSE;
	while (GetMessage(&Message, 0, 0, 0))
	{
		TranslateMessage(&Message);			//消息循环.
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

HFONT CreateFont(HDC hDC, int nCharHeight, BOOL bItalic)
{
	HFONT hFont;
	hFont = CreateFont(				//定义字体句柄.
		nCharHeight,				//字体高度.
		0,							//由系统根据高宽比选取字体最佳宽度值.
		0,							//文本倾斜度为0,表示水平.
		0,							//字体倾斜度为0.
		400,						//字体粗度.400为正常.
		bItalic,					//是斜体字?,
		0,							//无下划线.
		0,							//无删除线.
		ANSI_CHARSET,				//表示所用的字符集为ANSI_CHARSET.
		OUT_DEFAULT_PRECIS,			//删除精度为缺省值.
		CLIP_DEFAULT_PRECIS,		//裁剪精度为缺省值.
		DEFAULT_QUALITY,			//输出质量为缺省值.
		DEFAULT_PITCH | FF_DONTCARE,	//字间距和字体系列使用缺省值.
		"Arial");					//字体名称.
	if (hFont == NULL) return NULL;
	else return hFont;
}

long WINAPI WndProc(HWND hWnd,
	UINT iMessage,
	UINT wParam,
	LONG lParam)			//消息处理函数.
{
	HDC hdc;
	HPEN hPen;
	HBRUSH hBrush;
	PAINTSTRUCT ps;
	TEXTMETRIC tm;
	HFONT hF;
	SIZE size;
	static RECT clientRect;
	static int judge = 0;
	static double up, l, r, down;
	static char str[] = "我爱学VC++";
	POINT pt;
	GetClientRect(hWnd, &clientRect);
	up = clientRect.top, down = clientRect.bottom, l = clientRect.left, r = clientRect.right;
	switch (iMessage)
	{
	case WM_COMMAND:
		switch (wParam) {
		case IDM_Paintsjx:
			judge = 1;
			InvalidateRect(hWnd, NULL, true);
			break;
		case IDM_Painty:
			judge = 2;
			InvalidateRect(hWnd, NULL, true);
			break;
		case IDM_xianshi:
			judge = 3;
			InvalidateRect(hWnd, NULL, true);
			break;
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		if (judge == 1)
		{
			hPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
			SelectObject(hdc, hPen);
			Ellipse(hdc, r / 2 - 50, down / 2 - 50, r / 2 + 50, down / 2 + 50);
			DeleteObject(hPen);
		}
		else if (judge == 2)
		{
			hPen = CreatePen(PS_SOLID, 3, RGB(255, 255, 0));
			SelectObject(hdc, hPen);
			MoveToEx(hdc, r / 2, down / 3, &pt);
			LineTo(hdc, r / 3, down * 2 / 3);
			LineTo(hdc, r * 2 / 3, down * 2 / 3);
			LineTo(hdc, r / 2, down / 3);
			DeleteObject(hPen);
		}
		else if (judge == 3)
		{
			hF = CreateFont(hdc, 40, 0);			//创建字体.  本地函数
			SelectObject(hdc, hF);			//选入字体.
			GetTextMetrics(hdc, &tm);		//得到包含字体信息的结构体.
			SetTextColor(hdc, RGB(255, 0, 0));
			GetTextExtentPoint32(hdc, str, strlen(str), &size);
			TextOut(hdc, r / 2 - size.cx / 2, down / 2 - 20, str, strlen(str));
			DeleteObject(hF);				//删除字体句柄.
		}

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return(DefWindowProc(hWnd, iMessage, wParam, lParam));
	}
	return 0;
}

BOOL InitWindows(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hWnd = CreateWindow("7_7",				//窗口类名称.
		"菜单显示实例程序",		 //标题栏名称.
		WS_OVERLAPPEDWINDOW,	//窗口样式.有标题栏和最大最小化按钮.
		CW_USEDEFAULT,			//窗口左上角坐标.
		0,
		CW_USEDEFAULT,			//采用缺省的高度和宽度.
		0,
		NULL,					//无父窗口.
		NULL,					//无菜单.
		hInstance,				//当前应用实例句柄.
		NULL);					//指向传递给窗口的参数的指针.不用.
	if (!hWnd)		//创建失败.
		return FALSE;

	ShowWindow(hWnd, nCmdShow);	//显示窗口.
	UpdateWindow(hWnd);			//刷新用户区.
	return TRUE;
}

BOOL InitWindowsClass(HINSTANCE hInstance)
{
	WNDCLASS WndClass;

	WndClass.cbClsExtra = 0;			//无窗口类扩展.
	WndClass.cbWndExtra = 0;			//无窗口实例扩展.
	WndClass.hbrBackground = (HBRUSH)(GetStockObject(WHITE_BRUSH));//背景为白色.
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);	//光标为为箭头.
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	//采用缺省图标.
	WndClass.hInstance = hInstance;			//当前实例.
	WndClass.lpfnWndProc = WndProc;			//消息处理函数.
	WndClass.lpszClassName = "7_7";			//窗口类名称.
	WndClass.lpszMenuName = MAKEINTRESOURCE(MENU3);			/////////////////////////////关联菜单MENU3
	WndClass.style = 0;						//缺省窗口风格.
	return RegisterClass(&WndClass);	//返回窗口注册值.
}


