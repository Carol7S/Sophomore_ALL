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
    hFont=CreateFont(				//����������.
            nCharHeight,				//����߶�.
            0,							//��ϵͳ���ݸ߿��ѡȡ������ѿ��ֵ.
            0,							//�ı���б��Ϊ0,��ʾˮƽ.
            0,							//������б��Ϊ0.
            400,						//����ֶ�.400Ϊ����.
            bItalic,					//��б����?,
            0,							//���»���.
            0,							//��ɾ����.
            ANSI_CHARSET,				//��ʾ���õ��ַ���ΪANSI_CHARSET.
            OUT_DEFAULT_PRECIS,			//ɾ������Ϊȱʡֵ.
            CLIP_DEFAULT_PRECIS,		//�ü�����Ϊȱʡֵ.
            DEFAULT_QUALITY,			//�������Ϊȱʡֵ.
            DEFAULT_PITCH|FF_DONTCARE,	//�ּ�������ϵ��ʹ��ȱʡֵ.
            "Arial");					//��������.
    if(hFont == NULL) return NULL;
    else return hFont;
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInst,LPSTR lpszCmdLine,int nCmdShow)
{
    HWND hwnd;
    MSG Msg;
    WNDCLASS wndclass ;
    char lpszClassName[] = "����";
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
    HDC hDC;				//�����豸�������.
    HBRUSH hBr;
    HPEN hPen;
    PAINTSTRUCT ps;			//���������ͼ��Ϣ�Ľṹ�����
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
            InvalidateRect(hWnd,NULL,1);	//ˢ���û�����
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

        case WM_PAINT:							//�����ͼ��Ϣ.

            if(flag == 1)//����
            {
                y1 -= 50;
                y2 -= 50;
                if(rect.top >= y1){
                    y1 += 100;
                    y2 += 100;
                }
//                flag = 0;
            }
            else if(flag == 2)//����
            {
                y1 += 50;
                y2 += 50;
                if(rect.bottom <= y2){
                    y1 -= 100;
                    y2 -= 100;
                }

//                flag = 0;
            }
            else if(flag == 3)//����
            {
                x1 -= 50;
                x2 -= 50;
                if(rect.left >= x1){
                    x1 += 100;
                    x2 += 100;
                }
//                flag = 0;
            }
            else if(flag == 4)//����
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
