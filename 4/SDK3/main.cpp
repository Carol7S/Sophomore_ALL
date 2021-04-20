#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>
#include <time.h>
#define Pi 3.1415926


LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

HFONT CreateFont(HDC hdc,int nCharHeight,BOOL bItalic)
{
    HFONT hFont;
    hFont=CreateFont(				//定义字体句柄.
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
            DEFAULT_PITCH|FF_DONTCARE,	//字间距和字体系列使用缺省值.
            "Arial");					//字体名称.
    if(hFont == NULL) return NULL;
    else return hFont;
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInst,LPSTR lpszCmdLine,int nCmdShow)
{
    HWND hwnd;
    MSG Msg;
    WNDCLASS wndclass ;
    char lpszClassName[] = "窗口";
    char lpszTitle[]= "My_Windows";

    wndclass.style = 0;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL,IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL,IDC_ARROW);
    wndclass.hbrBackground =(HBRUSH) GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = lpszClassName;

    if(!RegisterClass(&wndclass))
    {
        MessageBeep(0) ;
        return FALSE ;
    }
    hwnd=CreateWindow(
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
            NULL);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while(GetMessage(&Msg,NULL,0,0))
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM  wParam,LPARAM lParam)
{
    HDC hDC;				//定义设备环境句柄.
    HBRUSH hBr;
    HPEN hPen;
    PAINTSTRUCT ps;			//定义包含绘图信息的结构体变量
    static int i=0;
    static int flag=0;
//    static bool nCtrlRKeyDown = FALSE;
//    static bool nCtrlKeyDown = FALSE;
//    static bool nShiftBKeyDown = FALSE;
//    static bool nShiftKeyDown = FALSE;
static double x1, x2, y1, y2;
RECT rect;
GetClientRect(hWnd , &rect) ;

    switch(message)
    {
        case WM_CREATE:
            x1 = (rect.left+rect.right)/2.4;
            x2 = (rect.left+rect.right)/1.9;
            y1 = (rect.top+rect.bottom)/3;
            y2 = (rect.top+rect.bottom)/1.8;
            break;
        case WM_KEYUP:
            InvalidateRect(hWnd,NULL,1);	//刷新用户区。
            break;

        case WM_CHAR:
            if(wParam == 'w'){
                flag = 1;
            }else if(wParam == 's'){
                flag = 2;
            }else if(wParam == 'a'){
                flag = 3;
            }else if(wParam == 'd'){
                flag = 4;
            }
            break;

        case WM_KEYDOWN:
            if(wParam == VK_UP){
                flag = 1;
            }else if(wParam == VK_DOWN){
                flag = 2;
            }else if(wParam == VK_LEFT){
                flag = 3;
            }else if(wParam == VK_RIGHT){
                flag = 4;
            }
            break;

        case WM_PAINT:							//处理绘图消息.

            if(flag == 1)//向上
            {
                y1 -= 50;
                y2 -= 50;
                if(rect.top >= y1){
                    y1 += 100;
                    y2 += 100;
                }
//                flag = 0;
            }
            else if(flag == 2)//向下
            {
                y1 += 50;
                y2 += 50;
                if(rect.bottom <= y2){
                    y1 -= 100;
                    y2 -= 100;
                }

//                flag = 0;
            }
            else if(flag == 3)//向左
            {
                x1 -= 50;
                x2 -= 50;
                if(rect.left >= x1){
                    x1 += 100;
                    x2 += 100;
                }
//                flag = 0;
            }
            else if(flag == 4)//向右
            {
                x1 += 50;
                x2 += 50;
                if(rect.right <= x2){
                    x1 -= 100;
                    x2 -= 100;
                }
//                flag = 0;
            }
            hDC=BeginPaint(hWnd,&ps);
            hPen = CreatePen(PS_SOLID, 1, RGB(255,0,0));
            SelectObject(hDC, hPen);
            hBr = CreateSolidBrush(RGB(255,0,0));
            SelectObject(hDC, hBr);
            Ellipse(hDC, x1, y1, x2, y2);
            DeleteObject(hPen);
            DeleteObject(hBr);
//            flag = 0;
            EndPaint(hWnd,&ps);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        default:
            return DefWindowProc(hWnd,message,wParam,lParam);
    }
    return 0;
}
