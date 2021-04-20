#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;
#define maxn 1000

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND hwnd;
	MSG Msg;
	WNDCLASS wndclass;
	char lpszClassName[] = "窗口";
	char lpszTitle[] = "My_Window";

	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = lpszClassName;

	if (!RegisterClass(&wndclass))
	{
		MessageBeep(0);
		return FALSE;
	}
	hwnd = CreateWindow
	(
		lpszClassName,
		lpszTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	return Msg.wParam;
}

HFONT createfont(int h) {
	HFONT hFont;
	hFont = CreateFont(             //创建自定义字体
		h,            //字体的高度
		0,        //由系统根据高宽比选取字体最佳宽度值
		0,            //文本的倾斜度为0，表示水平
		0,            //字体的倾斜度为0
		FW_HEAVY,        //字体的粗度，FW_HEAVY为最粗
		0,            //非斜体字
		0,            //无下划线
		0,            //无删除线
		ANSI_CHARSET,    //表示所用的字符集为ANSI_CHARSET
		OUT_DEFAULT_PRECIS,        //输出精度为缺省精度
		CLIP_DEFAULT_PRECIS,        //剪裁精度为缺省精度
		DEFAULT_QUALITY,        //输出质量为缺省值
		DEFAULT_PITCH | FF_DONTCARE,//字间距和字体系列使用缺省值
		"粗体字");         //字体名称
	if (hFont == NULL) return NULL;
	else return hFont;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	WORD x, y;
	HDC hDC;
	HCURSOR hCursor;
	HFONT hF;
	PAINTSTRUCT ps;
	TEXTMETRIC tm;
	RECT rect;
	SIZE size;
	static bool lbu = false;
	static POINTS point[maxn];
	static int count;

	switch (message)
	{
	case WM_LBUTTONDOWN:
		lbu = true;
		count = 0;
		InvalidateRect(hWnd, NULL, true);
		break;
	case WM_LBUTTONUP:
		lbu = false;
		InvalidateRect(hWnd, NULL, false);
		break;
	case WM_MOUSEMOVE:
		if (lbu == true && count < 1000)
		{
			x = LOWORD(lParam);
			y = HIWORD(lParam);
			point[count].x = x;
			point[count++].y = y;
			hDC = GetDC(hWnd);
			SetPixel(hDC, x, y, 0L);
			ReleaseDC(hWnd, hDC);
		}
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		for (int i = 0; i < count - 1; i++)
		{
			MoveToEx(hDC, point[0].x, point[0].y, NULL);
			LineTo(hDC, point[i].x, point[i].y);
		}

		EndPaint(hWnd, &ps);
		return 0;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

}