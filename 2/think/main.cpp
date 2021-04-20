#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>
#include <time.h>
#include <algorithm>
#define N 10


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
    static int x[N] , y[N] ;
    static int vx[N] , vy[N] ;
    static int r[N];
    static int uddis[N] ;
    static int lrdis[N] ;
    static int  t[N] ;
    int i, j, k;
    static int c=0;
    static int colorA[N], colorB[N], colorC[N];
    HPEN hp;
    HBRUSH hbr;
    HDC hdc;
    PAINTSTRUCT ps;
    RECT rect;
    int nextx[N] , nexty[N] ;
    int distance[N];
    int min=0;
    int num=0;

    switch(message)
    {
        case WM_CREATE:
            srand(time(NULL)) ;
            for(i=0;i<N;i++){
                x[i] = rand() % 1000 +10 ;
                y[i] = rand() % 1000 +10 ;
                vx[i] = rand() % 50 ;
                vy[i] = rand() % 50 ;
                r[i] = rand() % 50 ;
                t[i] = rand() ;
                if(t[i]%2){
                    vx[i] = -vx[i] ;
                }
                t[i] = rand() ;
                if(t[i]%2){
                    vy[i] = -vy[i] ;
                }
                colorA[i] = rand()%255+1;
                colorB[i] = rand()%255+1;
                colorC[i] = rand()%255+1;
                uddis[i] = 1;
                lrdis[i] = 1;
            }
            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_PAINT:
            hdc = BeginPaint(hwnd,&ps) ;
            GetClientRect(hwnd , &rect) ;
            for(i=0; i<N; i++){
                hp = (HPEN)CreatePen(PS_SOLID, 1, RGB(colorA[i],colorB[i],colorC[i]));
                hbr = (HBRUSH)CreateSolidBrush(RGB(colorA[i], colorB[i], colorC[i]));
                SelectObject(hdc,hp) ;
                SelectObject(hdc,hbr) ;
                Ellipse(hdc,x[i]-r[i],y[i]-r[i],x[i]+r[i],y[i]+r[i]) ;
                DeleteObject(hp);
                DeleteObject(hbr);
            }

            for(i=0; i<N; i++) {
                nextx[i] = x[i] + lrdis[i] * vx[i];
                nexty[i] = y[i] + uddis[i] * vy[i];
                if (nextx[i] < rect.left + r[i]) {
                    nextx[i] = rect.left + r[i];
                    lrdis[i] = -lrdis[i];
                }
                if (nexty[i] < rect.top + r[i]) {
                    nexty[i] = rect.top + r[i];
                    uddis[i] = -uddis[i];
                }
                if (nextx[i] > rect.right - r[i]) {
                    nextx[i] = rect.right - r[i];
                    lrdis[i] = -lrdis[i];
                }
                if (nexty[i] > rect.bottom - r[i]) {
                    nexty[i] = rect.bottom - r[i];
                    uddis[i] = -uddis[i];
                }

                for(j=0; j<N; j++){
                    if(i == j)
                        continue;
                    if(pow((nextx[i]-x[j]),2)+pow(nexty[i]-y[j],2) <= pow(r[i]+r[num],2)){
                        lrdis[i] = -lrdis[i]; lrdis[j] = -lrdis[j];
                        uddis[i] = -uddis[i]; uddis[j] = -uddis[j];
                    }
                }
                /*
                min = distance[0];

                for(k=0; k<N; k++){
                    if(k == i)
                        continue;
                    if(min > distance[k]){
                        min = distance[k];
                        num = k;
                    }
                }
                */


                x[i] = nextx[i];
                y[i] = nexty[i];
            }

            Sleep(100) ;
            InvalidateRect(hwnd,NULL,1) ;
            EndPaint(hwnd,&ps) ;
            return 0;

        default:
            return DefWindowProc(hwnd,message,wParam,lParam);
    }
    return 0;
}
