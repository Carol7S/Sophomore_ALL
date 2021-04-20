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
    static int i=0;
    static int flag=0;

    static WORD x, y;
    char str_x[20], str_y[20];
    char lpsz_1[50]="你在{ ";
    char lpsz_2[]=" }坐标点击了鼠标左键";
    char lpsz_3[]=" }坐标点击了鼠标右键";
    char lpsz_4[]=" }坐标双击了鼠标左键";
    static char pos[20] = "";
    static int left_flag=0;
    static int right_flag=0;
    static int left_db_flag=0;
    RECT rect;
    GetClientRect(hWnd , &rect) ;
    static int X, Y;
    x=LOWORD(lParam);
    y=HIWORD(lParam);
    switch(message)
    {
        case WM_CREATE:
            X=(rect.left+rect.right)/2;
            Y=(rect.top+rect.bottom)/2;
            break;

        case WM_MOUSEMOVE:
            sprintf(pos, "%d,%d", x, y);
            InvalidateRect(hWnd,NULL,1);
            break;

        case WM_LBUTTONDOWN:
            DWORD st;
            DWORD et;
            MSG msg;
            st = GetTickCount();
            while(1)
            {
                if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
                {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);}
                if(WM_LBUTTONDBLCLK == msg.message)
                {
                    return DefWindowProc(hWnd,message,wParam,lParam);
                }
                et = GetTickCount();
                if(et - st > 200)
                    break;
            }

            right_flag=0;
            left_db_flag=0;
            left_flag = 1;
            InvalidateRect(hWnd,NULL,1);
            break;

        case WM_RBUTTONDOWN:
            left_flag=0;
            left_db_flag=0;
            right_flag = 1;
            InvalidateRect(hWnd,NULL,1);
            break;

        case WM_LBUTTONDBLCLK:
            left_flag=0;
            right_flag=0;
            left_db_flag = 1;
            InvalidateRect(hWnd,NULL,1);
            break;

//        case WM_LBUTTONUP:
//            InvalidateRect(hWnd,NULL,1);

        case WM_PAINT:							//处理绘图消息.
            hDC = BeginPaint(hWnd,&ps);
            if(left_db_flag == 1){
                strcat(pos,lpsz_4);
                strcat(lpsz_1, pos);
                TextOut(hDC,X,Y,lpsz_1,strlen(lpsz_1));

            }
            else if(left_flag == 1){
                strcat(pos,lpsz_2);
                strcat(lpsz_1, pos);
                TextOut(hDC,X,Y,lpsz_1,strlen(lpsz_1));

            }
            else if(right_flag == 1){
                strcat(pos,lpsz_3);
                strcat(lpsz_1, pos);
                TextOut(hDC,X,Y,lpsz_1,strlen(lpsz_1));

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
