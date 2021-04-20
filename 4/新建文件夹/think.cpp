#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>
#include <time.h>
#define Pi 3.1415926
#define M 5
#define N 10

typedef struct MyRect{
    double x1, x2;
    double y1, y2;
    bool state = TRUE;
    int color;
}MyRect;

typedef struct MyBan{
    double x1, x2;
    double y1, y2;
    int color;
};

typedef struct MyCircle{
    int x, y;
    int vx, vy;
    int r;
    int t;
    int color;
    int uddis;
    int lrdis;
    int nextx, nexty;
};

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
    wndclass.hbrBackground =(HBRUSH) GetStockObject(GRAY_BRUSH);
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
    static int i=0, j=0;
    static int flag=0;
    static MyRect rect_arr[M*N];
    static MyBan ban;
    static MyCircle circle;
    static int change_ban;
    static int change_circle;
    RECT rect;
    GetClientRect(hWnd , &rect) ;

    switch(message)
    {
        case WM_CREATE:
            SetTimer(hWnd,1,1000,NULL);	//建立计时器,每0.3秒发出WM_TIMER消息.
            srand(time(NULL));

            //初始化砖块
            rect_arr[0].x1 = rect.left;
            rect_arr[0].x2 = rect_arr[0].x1 + 120;
            rect_arr[0].y1 = rect.top;
            rect_arr[0].y2 = rect_arr[0].y1 + 60;
            rect_arr[0].color = RGB(236, 24, 255);
            for(i=1; i<M*N; i++){
                rect_arr[i].x1 = rect_arr[i-1].x1 + 140;
                rect_arr[i].x2 = rect_arr[i].x1 + 130;
                if(i%10 == 0 && i != 0) {
                    rect_arr[i].y1 = rect_arr[i-1].y1 + 80;
                    rect_arr[i].y2 = rect_arr[i].y1 + 60;
                    rect_arr[i].x1 = rect.left;
                    rect_arr[i].x2 = rect_arr[0].x1 + 120;
                }else{
                    rect_arr[i].y1 = rect_arr[i-1].y1;
                    rect_arr[i].y2 = rect_arr[i-1].y2;
                }
            }
            //设定颜色
            for(i=0; i<M*N; i++){
                switch (i%10) {
                    case 0:
                        rect_arr[i].color = RGB(236, 24, 255);
                        break;
                    case 1:
                        rect_arr[i].color = RGB(0, 0, 255);
                        break;
                    case 2:
                        rect_arr[i].color = RGB(24, 207, 255);
                        break;
                    case 3:
                        rect_arr[i].color = RGB(24, 255, 255);
                        break;
                    case 4:
                        rect_arr[i].color = RGB(24, 255, 134);
                        break;
                    case 5:
                        rect_arr[i].color = RGB(139, 255, 24);
                        break;
                    case 6:
                        rect_arr[i].color = RGB(220, 255, 24);
                        break;
                    case 7:
                        rect_arr[i].color = RGB(255, 137, 24);
                        break;
                    case 8:
                        rect_arr[i].color = RGB(255, 0, 0);
                        break;
                    case 9:
                        rect_arr[i].color = RGB(255, 24, 201);
                        break;
                }
            }


            //初始化底部的板子
            ban.x1 = (rect.left+rect.right)/2.2;
            ban.y1 = rect.bottom - 30;
            ban.x2 = (rect.left+rect.right)/1.8;
            ban.y2 = rect.bottom;
            ban.color = RGB(0, 0, 255);


            //初始化球
            circle.x = (rect.left+rect.right)/1.7;
            circle.y = (rect.top+rect.bottom)/1.7;
            circle.r = 50;
            circle.color = RGB(0,255,0);
            circle.vx = 30;
            circle.vy = 40;
            circle.t = rand();
            circle.uddis = 1;
            circle.lrdis = 1;
            if(circle.t%2){
                circle.vx = -circle.vx ;
            }
            circle.t = rand() ;
            if(circle.t%2){
                circle.vy = -circle.vy ;
            }
            break;

        case WM_TIMER:						//处理由计时器发出的消息.
            InvalidateRect(hWnd,NULL,1);	//刷新用户区.
            change_circle = 1;
            break;

        case WM_KEYUP:
            InvalidateRect(hWnd,NULL,1);	//刷新用户区。'
            change_ban = 1;
            break;

        case WM_CHAR:
            if(wParam == 'a'){
                flag = 1;
            }else if(wParam == 'd'){
                flag = 2;
            }
            break;

        case WM_KEYDOWN:
            if(wParam == VK_LEFT){
                flag = 1;
            }else if(wParam == VK_RIGHT){
                flag = 2;
            }
            break;

        case WM_PAINT:							//处理绘图消息.
            hDC=BeginPaint(hWnd,&ps);
            //绘制砖块
            for(i=0; i<M*N; i++) {
                hPen = CreatePen(PS_SOLID, 1, rect_arr[i].color);
                SelectObject(hDC, hPen);
                hBr = CreateSolidBrush(rect_arr[i].color);
                SelectObject(hDC, hBr);
                Rectangle(hDC, rect_arr[i].x1, rect_arr[i].y1, rect_arr[i].x2, rect_arr[i].y2);
                DeleteObject(hPen);
                DeleteObject(hBr);
            }

            if(flag == 1)//向左
            {
                if(ban.x1 <= rect.left){
                    ban.x1 += 50;
                    ban.x2 += 50;
                }
                ban.x1 -= 50;
                ban.x2 -= 50;
                flag = 0;
            }
            else if(flag == 2)//向右
            {
                if(ban.x2 >= rect.right){
                    ban.x1 -= 50;
                    ban.x2 -= 50;
                }
                ban.x1 += 50;
                ban.x2 += 50;
                flag = 0;
            }


            //绘制板子

            hPen = CreatePen(PS_SOLID, 1, ban.color);
            SelectObject(hDC, hPen);
            hBr = CreateSolidBrush(ban.color);
            SelectObject(hDC, hBr);
            Rectangle(hDC, ban.x1, ban.y1, ban.x2, ban.y2);
            DeleteObject(hPen);
            DeleteObject(hBr);
            change_ban = 0;



            //绘制球
            if(change_circle) {
                hPen = CreatePen(PS_SOLID, 1, circle.color);
                SelectObject(hDC, hPen);
                hBr = CreateSolidBrush(circle.color);
                SelectObject(hDC, hBr);
                Ellipse(hDC, circle.x - circle.r, circle.y - circle.r, circle.x + circle.r, circle.y + circle.r);
                circle.nextx = circle.x + circle.lrdis * circle.vx;
                circle.nexty = circle.y + circle.uddis * circle.vy;
                if (circle.nextx < rect.left + circle.r) {
                    circle.nextx = rect.left + circle.r;
                    circle.lrdis = -circle.lrdis;
                }
                if (circle.nexty < rect.top + circle.r) {
                    circle.nexty = rect.top + circle.r;
                    circle.uddis = -circle.uddis;
                }
                if (circle.nextx > rect.right - circle.r) {
                    circle.nextx = rect.right - circle.r;
                    circle.lrdis = -circle.lrdis;
                }
                if (circle.nexty > rect.bottom - circle.r) {
                    circle.nexty = rect.bottom - circle.r;
                    circle.uddis = -circle.uddis;
                }
                circle.x = circle.nextx;
                circle.y = circle.nexty;
                DeleteObject(hPen);
                DeleteObject(hBr);
                change_circle = 0;
            }else{
                hPen = CreatePen(PS_SOLID, 1, circle.color);
                SelectObject(hDC, hPen);
                hBr = CreateSolidBrush(circle.color);
                SelectObject(hDC, hBr);
                Ellipse(hDC, circle.x - circle.r, circle.y - circle.r, circle.x + circle.r, circle.y + circle.r);
                DeleteObject(hPen);
                DeleteObject(hBr);
            }
            EndPaint(hWnd,&ps);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            KillTimer(hWnd,1);				//删除计时器W
            return 0;
        default:
            return DefWindowProc(hWnd,message,wParam,lParam);
    }
    return 0;
}
