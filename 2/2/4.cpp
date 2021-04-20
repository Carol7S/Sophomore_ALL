#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>
#include <time.h>
#define Pi 3.1415926


LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

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

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM  wParam,LPARAM lParam)
{
    static int x , y ;
    static int vx = 3 , vy = 4 ;
    static int r = 5 ;
    static int uddis = 1 ;
    static int lrdis = 1 ;
    static int  t ;

    HPEN hp;
    HBRUSH hbr;
    HDC hdc;
    PAINTSTRUCT ps;
    RECT rect;
    int nextx , nexty ;
    GetClientRect(hwnd , &rect) ;

    switch(message)
    {
        case WM_CREATE:
            srand(time(NULL)) ;
            x = rand() % 1000 +10 ;
            y = rand() % 1000 +10 ;
            vx = rand() % 50 ;
            vy = rand() % 50 ;
            r = rand() % 50 ;
            t = rand() ;
            if(t%2){
                vx = -vx ;
            }
            t = rand() ;
            if(t%2){
                vy = -vy ;
            }
            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_PAINT:
            hdc = BeginPaint(hwnd,&ps) ;
            hp = (HPEN)CreatePen(PS_SOLID, 1, RGB(255,0,0));
            hbr = (HBRUSH)CreateHatchBrush(HS_BDIAGONAL, RGB(255, 0, 0));
            SelectObject(hdc,hp) ;
            SelectObject(hdc,hbr) ;

            Ellipse(hdc,x-r,y-r,x+r,y+r) ;

            nextx = x + lrdis * vx ;
            nexty = y + uddis * vy ;
            if(nextx < rect.left+r){
                nextx = rect.left + r ;
                lrdis = -lrdis ;
            }
            if(nexty < rect.top+r){
                nexty = rect.top + r ;
                uddis = -uddis ;
            }
            if(nextx > rect.right - r){
                nextx = rect.right - r ;
                lrdis = -lrdis ;
            }
            if(nexty > rect.bottom - r){
                nexty = rect.bottom - r ;
                uddis = -uddis ;
            }
            x = nextx ;
            y = nexty ;

            Sleep(100) ;
            InvalidateRect(hwnd,NULL,1) ;
            EndPaint(hwnd,&ps) ;
            return 0;

        default:
            return DefWindowProc(hwnd,message,wParam,lParam);
    }
    return 0;
}
