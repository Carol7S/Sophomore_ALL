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

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM  wParam,LPARAM lParam)
{
    HDC hdc;				//�����豸�������.
    HFONT hF;				//����������.
    PAINTSTRUCT ps;			//���������ͼ��Ϣ�Ľṹ�����
    TEXTMETRIC tm;			//�������������Ϣ�Ľṹ�����.
    char lpsz_1[]="�㽭ũ�ִ�ѧ��ӭ����";	//����������ַ���.
    int nCharlen=strlen(lpsz_1);	//�����ַ������ȱ���.
    static int X=0, flag=1;
    int Y=0,i;
    RECT rect;
    SIZE size;
    GetClientRect(hwnd , &rect) ;

    switch(message)
    {
        case WM_CREATE:
            SetTimer(hwnd,1,50,NULL);	//������ʱ��,ÿ0.3�뷢��WM_TIMER��Ϣ.
        case WM_TIMER:						//�����ɼ�ʱ����������Ϣ.
            InvalidateRect(hwnd,NULL,1);	//ˢ���û���.
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            KillTimer(hwnd,1);				//ɾ����ʱ��
            return 0;
        case WM_PAINT:
            hdc = BeginPaint(hwnd,&ps) ;
            hF = CreateFont(hdc,40,0);			//��������.  ���غ���
            SetTextColor(hdc, RGB(255, 0, 0));
            SelectObject(hdc,hF);			//ѡ������.
            GetTextMetrics(hdc,&tm);		//�õ�����������Ϣ�Ľṹ��.
            GetTextExtentPoint32(hdc, lpsz_1, nCharlen, &size);
            Y=tm.tmExternalLeading+10;			//��������ַ���Y����.
            TextOut(hdc, X, Y, lpsz_1, nCharlen);
            if(rect.right <= X+size.cx){
                flag = 0;
            }else if(rect.left >= X){
                flag = 1;
            }
            if(flag == 1){
                X += 5;
            } else{
                X -= 5;
            }
            DeleteObject(hF);				//ɾ��������.
            EndPaint(hwnd,&ps) ;
            return 0;

        default:
            return DefWindowProc(hwnd,message,wParam,lParam);
    }
    return 0;
}
