#include <windows.h>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <time.h>
#include <cstdio>
#define Pi 3.1415926


LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInst,LPSTR lpszCmdLine,int nCmdShow)
{
    HWND hwnd;
    MSG Msg;
    WNDCLASS wndclass ;
    char lpszClassName[] = "窗口";
    char lpszTitle[]= "My_Windows";

    wndclass.style = CS_DBLCLKS;
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
    LPPOINT lpPoint;
    static int i=0;
    static int flag=0;
    int j;
    static int r = 20;
    WORD x, y;
    static int X, Y;
    static int nCount;
    RECT rect;
    GetClientRect(hWnd , &rect) ;
    x = LOWORD(lParam);
    y = HIWORD(lParam);

    switch(message)
    {
        case WM_CREATE:
            hDC = BeginPaint(hWnd,&ps);

            EndPaint(hWnd,&ps);
            break;

        case WM_LBUTTONDOWN:

            InvalidateRect(hWnd,NULL,FALSE);
            break;

        case WM_MOUSEMOVE:
            X = x; Y = y;
            break;

        case WM_PAINT:							//处理绘图消息.
            hDC = BeginPaint(hWnd,&ps);
            MoveToEx(hDC, rect.left + 100, rect.top + 50, lpPoint);
            LineTo(hDC, rect.right - 70, rect.top + 50);
            LineTo(hDC, rect.right - 70, rect.bottom-20);
            LineTo(hDC, rect.left + 100, rect.bottom-20);
            for(j=1; j<=13; j++) {
                MoveToEx(hDC, rect.left + 100, rect.top + 50*j, lpPoint);
                LineTo(hDC, rect.right - 70, rect.top + 50*j);
            }
            for(j=2; j<=26; j++) {
                MoveToEx(hDC, rect.left + 50*j, rect.top + 50, lpPoint);
                LineTo(hDC, rect.left + 50*j, rect.bottom - 20);
            }

            if(flag==1){
                hBr = CreateSolidBrush(RGB(0,0,0));
                SelectObject(hDC, hBr);
                Ellipse(hDC, X-r, Y-r, X+r, Y+r);
                DeleteObject(hBr);
                flag=0;
            }
            else{
                hBr = CreateSolidBrush(RGB(255,255,255));
                SelectObject(hDC, hBr);
                Ellipse(hDC, X-r, Y-r, X+r, Y+r);
                DeleteObject(hBr);
                flag=1;
            }

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
