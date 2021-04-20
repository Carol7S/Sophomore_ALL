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
    char cUP[]="您按下了UP键";
    char cCTRL[]="您按下了CTRL键";
    char cNum[] = "0123456789";
    static int i=0;
    static int flag=-1;
    static bool nCtrlRKeyDown = FALSE;
    static bool nCtrlKeyDown = FALSE;
    static bool nShiftBKeyDown = FALSE;
    static bool nShiftKeyDown = FALSE;
    RECT rect;
    static int out = 1;
    GetClientRect(hWnd , &rect) ;

    switch(message)
    {
        case WM_CREATE:
            srand(time(NULL));
            SetTimer(hWnd,1,2000,NULL);	//建立计时器,每2秒发出WM_TIMER消息.


        case WM_KEYUP:
            InvalidateRect(hWnd,NULL,1);	//刷新用户区。
            break;

        case WM_TIMER:						//处理由计时器发出的消息.
            i = rand()%10;
            InvalidateRect(hWnd,NULL,1);	//刷新用户区.
            break;

        case WM_CHAR:
            if(wParam=='1')
            {
                flag = 1;
            }
            else if(wParam=='2')	//当按下b键时
            {
                flag = 2;
            }
            else if(wParam=='3')	//当按下c键时
            {
                flag = 3;
            }
            if(wParam=='4')
            {
                flag = 4;
            }
            else if(wParam=='5')	//当按下b键时
            {
                flag = 5;
            }
            else if(wParam=='6')	//当按下c键时
            {
                flag = 6;
            }
            if(wParam=='7')
            {
                flag = 7;
            }
            else if(wParam=='8')	//当按下b键时
            {
                flag = 8;
            }
            else if(wParam=='9')	//当按下c键时
            {
                flag = 9;
            }
            else if(wParam=='0')	//当按下c键时
            {
                flag = 0;
            }
            break;

        case WM_KEYDOWN:
            break;

        case WM_PAINT:							//处理绘图消息.
            hDC=BeginPaint(hWnd,&ps);
            SetTextColor(hDC,RGB(0,255,0));
            TextOut(hDC, (rect.left+rect.right)/2, (rect.top+rect.bottom)/2, &cNum[i], 1);
            out = 1;
            //输出信息。
            if(flag == 1 && out == 1){
                if(flag == i)
                    SetTextColor(hDC,RGB(0,0,255));
                else
                    SetTextColor(hDC,RGB(255,0,0));

                TextOut(hDC, (rect.left+rect.right)/2, (rect.top+rect.bottom)/2, &cNum[i], 1);
                flag = -1;
                out = 0;
            }
            else if(flag == 2 && out == 1){
                if(flag == i)
                    SetTextColor(hDC,RGB(0,0,255));
                else
                    SetTextColor(hDC,RGB(255,0,0));

                TextOut(hDC, (rect.left+rect.right)/2, (rect.top+rect.bottom)/2, &cNum[i], 1);
                flag = -1;
                out = 0;

            }

            else if(flag == 3 && out == 1){
                if(flag == i)
                    SetTextColor(hDC,RGB(0,0,255));
                else
                    SetTextColor(hDC,RGB(255,0,0));

                TextOut(hDC, (rect.left+rect.right)/2, (rect.top+rect.bottom)/2, &cNum[i], 1);
                flag = -1;
                out = 0;

            }
            else if(flag == 4 && out == 1){
                if(flag == i)
                    SetTextColor(hDC,RGB(0,0,255));
                else
                    SetTextColor(hDC,RGB(255,0,0));

                TextOut(hDC, (rect.left+rect.right)/2, (rect.top+rect.bottom)/2, &cNum[i], 1);
                flag = -1;
                out = 0;

            }
            else if(flag == 5 && out == 1){
                if(flag == i)
                    SetTextColor(hDC,RGB(0,0,255));
                else
                    SetTextColor(hDC,RGB(255,0,0));

                TextOut(hDC, (rect.left+rect.right)/2, (rect.top+rect.bottom)/2, &cNum[i], 1);
                flag = -1;
                out = 0;

            }
            else if(flag == 6 && out == 1){
                if(flag == i)
                    SetTextColor(hDC,RGB(0,0,255));
                else
                    SetTextColor(hDC,RGB(255,0,0));

                TextOut(hDC, (rect.left+rect.right)/2, (rect.top+rect.bottom)/2, &cNum[i], 1);
                flag = -1;
                out = 0;

            }
            else if(flag == 7 && out == 1){
                if(flag == i)
                    SetTextColor(hDC,RGB(0,0,255));
                else
                    SetTextColor(hDC,RGB(255,0,0));

                TextOut(hDC, (rect.left+rect.right)/2, (rect.top+rect.bottom)/2, &cNum[i], 1);
                flag = -1;
                out = 0;

            }
            else if(flag == 8 && out == 1){
                if(flag == i)
                    SetTextColor(hDC,RGB(0,0,255));
                else
                    SetTextColor(hDC,RGB(255,0,0));

                TextOut(hDC, (rect.left+rect.right)/2, (rect.top+rect.bottom)/2, &cNum[i], 1);
                flag = -1;
                out = 0;

            }
            else if(flag == 9 && out == 1){
                if(flag == i)
                    SetTextColor(hDC,RGB(0,0,255));
                else
                    SetTextColor(hDC,RGB(255,0,0));

                TextOut(hDC, (rect.left+rect.right)/2, (rect.top+rect.bottom)/2, &cNum[i], 1);
                flag = -1;
                out = 0;

            }
            else if(flag == 0 && out == 1){
                if(flag == i)
                    SetTextColor(hDC,RGB(0,0,255));
                else
                    SetTextColor(hDC,RGB(255,0,0));

                TextOut(hDC, (rect.left+rect.right)/2, (rect.top+rect.bottom)/2, &cNum[i], 1);
                flag = -1;
                out = 0;

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
