#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>
#include <time.h>
#define PI (3.14159265358979323846)
#define PI_DIV_180 (0.017453292519943296)//π/180
#define DegToRad(x)	((x)*PI_DIV_180)//角度转换为弧度
#define N 5

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

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM  wParam,LPARAM lParam)
{
    HPEN hp;
    HBRUSH hbr;
    HDC hdc;				//定义设备环境句柄.
    HFONT hF;				//定义字体句柄.
    PAINTSTRUCT ps;			//定义包含绘图信息的结构体变量
    TEXTMETRIC tm;			//定义包含字体信息的结构体变量.
    char lpsz_1[]="浙江农林大学欢迎您！";	//定义输出的字符串.
    int nCharlen=strlen(lpsz_1);	//定义字符串长度变量.
    static int x1[N], y1[N], x2[N], y2[N];
    int i=0, j=0;
    RECT rect;
    SIZE size;
    LPPOINT lppoint;
    static int cnt[N];
    int r=50;
    int angle=0;
    GetClientRect(hwnd , &rect) ;

    switch(message)
    {
        case WM_CREATE:
            SetTimer(hwnd,1,300,NULL);	//建立计时器,每0.3秒发出WM_TIMER消息.
            srand(time(NULL));
            for(i=0; i<N; i++){
                x1[i] = rand()%600;
                y1[i] = rand()%600+200;
                x2[i] = x1[i]+20;
                y2[i] = y1[i]+50;
            }
        case WM_TIMER:						//处理由计时器发出的消息.
            InvalidateRect(hwnd,NULL,1);	//刷新用户区.
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            KillTimer(hwnd,1);				//删除计时器
            return 0;
        case WM_PAINT:
            hdc = BeginPaint(hwnd,&ps) ;
            hbr = (HBRUSH)CreateSolidBrush(RGB(0,0,0));
            SelectObject(hdc, hbr);
            Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
            DeleteObject(hbr);

            for(i=0; i<N; i++) {
                if (cnt[i] <= 5) {
                    y1[i] -= 50;
                    y2[i] -= 50;
                    cnt[i]++;
                }
            }
            for(i=0; i<N; i++) {
                if(cnt[i] <= 5) {
                    hbr = (HBRUSH)CreateSolidBrush(RGB(rand()%255+1,rand()%255+1,rand()%255+1));
                    SelectObject(hdc, hbr);
                    RoundRect(hdc, x1[i], y1[i], x2[i], y2[i], 50, 30);
                    DeleteObject(hbr);
                }else{
                    hp = (HPEN)CreatePen(PS_DASHDOTDOT, 1, RGB(rand()%255+1,rand()%255+1,rand()%255+1));
                    SelectObject(hdc, hp);
                    for(j=0; j<8; j++) {
                        MoveToEx(hdc, (x1[i] + x2[i]) / 2, (y1[i] + y2[i]) / 2, lppoint);
                        LineTo(hdc, (x1[i] + x2[i]) / 2 + r*sin(DegToRad(angle)), (y1[i] + y2[i]) / 2 - r*cos(DegToRad(angle)));
                        angle+=45;
                    }
                    DeleteObject(hp);
                }
            }


//            DeleteObject(hbr);
            EndPaint(hwnd,&ps) ;
            return 0;

        default:
            return DefWindowProc(hwnd,message,wParam,lParam);
    }
    return 0;
}
