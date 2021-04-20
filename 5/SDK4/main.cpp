#include <windows.h>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <time.h>
#include <cstdio>
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
    static int i;
    static int flag=0;
    WORD x, y;
    static int circle_x, circle_y;
    static int nCount;
    int r = 40;
    static POINT lp_arr[100];
    int dist=0;
    RECT rect;
    GetClientRect(hWnd , &rect) ;
    x = LOWORD(lParam);
    y = HIWORD(lParam);


    for(int j=0;j<100;j++)		//生成正弦曲线的点坐标.
    {
        lp_arr[j].x=(long)(rect.left+j*20);
        lp_arr[j].y=(long)(rect.bottom-j*20);
    }


    switch(message)
    {
        case WM_CREATE:
            srand(time(NULL));
            SetTimer(hWnd,1,500,NULL);
            break;

        case WM_TIMER:						//处理由计时器发出的消息.
            i++;
            InvalidateRect(hWnd,NULL,1);	//刷新用户区.
            break;

        case WM_LBUTTONDOWN:
            dist = pow((x-lp_arr[i].x),2) + pow((y-lp_arr[i].y),2);
            if(dist < r*r){
                if(flag == 2){
                    flag = 0;
                }
                else
                    flag++;
                InvalidateRect(hWnd,NULL,1);
            }

            break;

        case WM_MOUSEMOVE:

            break;

        case WM_PAINT:							//处理绘图消息.
            hDC = BeginPaint(hWnd,&ps);
            if(flag == 0){
                hPen = CreatePen(PS_SOLID, 1, RGB(255,0,0));
                hBr = CreateSolidBrush(RGB(255,0,0));
                SelectObject(hDC, hPen);
                SelectObject(hDC, hBr);
                circle_x = lp_arr[i].x;
                circle_y = lp_arr[i].y;
                Ellipse(hDC, circle_x-r, circle_y-r, circle_x+r, circle_y+r);
                DeleteObject(hPen);
                DeleteObject(hBr);
            }
            else if(flag == 1){
                hPen = CreatePen(PS_SOLID, 1, RGB(0,0,255));
                hBr = CreateSolidBrush(RGB(0,0,255));
                SelectObject(hDC, hPen);
                SelectObject(hDC, hBr);
                circle_x = lp_arr[i].x;
                circle_y = lp_arr[i].y;
                Ellipse(hDC, circle_x-r, circle_y-r, circle_x+r, circle_y+r);

                DeleteObject(hPen);
                DeleteObject(hBr);
            }
            else if(flag == 2){
                hPen = CreatePen(PS_SOLID, 1, RGB(0,255,0));
                hBr = CreateSolidBrush(RGB(0,255,0));
                SelectObject(hDC, hPen);
                SelectObject(hDC, hBr);
                circle_x = lp_arr[i].x;
                circle_y = lp_arr[i].y;
                Ellipse(hDC, circle_x-r, circle_y-r, circle_x+r, circle_y+r);

                DeleteObject(hPen);
                DeleteObject(hBr);
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
