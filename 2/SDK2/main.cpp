#include <windows.h>
#include <cmath>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);   //窗口函数
//--------------------------以下是入口代码-------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
    WNDCLASSEX wcex;
    HWND hWnd;
    MSG msg;
    char szWindowClass[] = "窗口实例";   //窗口类名
    char szTitle[] = "My Windows";   //窗口标题名

//------------------------以下初始化窗口类---------------------------------
    wcex.cbSize = sizeof(WNDCLASSEX); //窗口类的大小
    wcex.style = CS_HREDRAW | CS_VREDRAW;   //窗口类型
    wcex.lpfnWndProc = WndProc;     //窗口处理函数
    wcex.cbClsExtra = 0;            //窗口类无扩展
    wcex.cbWndExtra = 0;            //窗口实例无扩展
    wcex.hInstance = hInstance;     //当前实例句柄
    wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION); //窗口的图标为默认图标
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);                //窗口采用箭头光标
    wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //窗口背景为白色
    wcex.lpszMenuName = NULL;   //窗口中无菜单
    wcex.lpszClassName = szWindowClass; //窗口的类名为"窗口实例"
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION); //窗口的小图标为默认图标

//---------------------以下进行窗口类的注册-------------------------------------
    if(!RegisterClassEx(&wcex)){    //注册失败则发出警告
        MessageBox(NULL, "窗口类注册失败!", "窗口注册", NULL);
        return 1;
    }
//---------------------以下创建窗口--------------------------------------------
    hWnd = CreateWindow(
            szWindowClass,      //窗口类名
            szTitle,            //窗口实例的标题名
            WS_OVERLAPPEDWINDOW,    //窗口的风格
            CW_USEDEFAULT,CW_USEDEFAULT,      //窗口左上角坐标为默认值
            CW_USEDEFAULT, CW_USEDEFAULT,   //窗口的高和宽为默认值
            NULL,                    //此窗口无父窗口
            NULL,                   //此窗口无主菜单
            hInstance,          //创建此窗口应用程序的当前句柄
            NULL                        //不使用该值
    );

    if(!hWnd){      //如果创建窗口失败则发出警告
        MessageBox(NULL, "创建窗口失败!", "创建窗口", NULL);
        return 1;
    }
    ShowWindow(hWnd, nCmdShow);     //显示窗口
    UpdateWindow(hWnd);             //绘制用户区
    while(GetMessage(&msg, NULL, 0, 0)){ //消息循环
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return(int) msg.wParam;     //程序终止时将信息返回系统
}
//-------------------以下是窗口函数的代码--------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
    PAINTSTRUCT ps;
    HDC hdc;
    HPEN hP;
    HBRUSH hBr;
    LPPOINT lpPoint;
    POINT pt;
    RECT rect;
    static long i = 0;
    static long j = 0;
    static long k = 0;
    static long l = 0;
    switch(message){
        case WM_DESTROY:
            PostQuitMessage(0);     //调用PostQuiteMessage发出WM_QUIT消息
            return 0;
        case WM_PAINT:
            GetClientRect(hWnd, &rect);
            hdc = BeginPaint(hWnd, &ps);
            hP = (HPEN)CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
            SelectObject(hdc, hP);
            Rectangle(hdc, (rect.left+rect.right)/8, (rect.top+rect.bottom)/8,
                    (rect.right+rect.left)/1.2, (rect.bottom+rect.top)/1.7);
            MoveToEx(hdc, (rect.right+rect.left)/2.1, (rect.bottom+rect.top)/8, lpPoint);
            LineTo(hdc, (rect.right+rect.left)/2.1, (rect.bottom+rect.top)/1.7);
            //0
//            Rectangle(hdc, (rect.left+rect.right)/7, (rect.top+rect.bottom)/6,
//            (rect.right+rect.left)/4, (rect.bottom+rect.top)/1.8);
//            Rectangle(hdc, (rect.left+rect.right)/3.1, (rect.top+rect.bottom)/6,
//                      (rect.right+rect.left)/2.3, (rect.bottom+rect.top)/1.8);
//            Rectangle(hdc, (rect.left+rect.right)/2, (rect.top+rect.bottom)/6,
//                      (rect.right+rect.left)/1.6, (rect.bottom+rect.top)/1.8);
//            Rectangle(hdc, (rect.left+rect.right)/1.5, (rect.top+rect.bottom)/6,
//                      (rect.right+rect.left)/1.25, (rect.bottom+rect.top)/1.8);
            //1
//            MoveToEx(hdc, (rect.left+rect.right)/5, (rect.top+rect.bottom)/6, lpPoint);
//            LineTo(hdc, (rect.left+rect.right)/5, (rect.top+rect.bottom)/1.8);

//            MoveToEx(hdc, (rect.left+rect.right)/2.5, (rect.top+rect.bottom)/6, lpPoint);
//            LineTo(hdc, (rect.left+rect.right)/2.5, (rect.top+rect.bottom)/1.8);

//            MoveToEx(hdc, (rect.left+rect.right)/1.8, (rect.top+rect.bottom)/6, lpPoint);
//            LineTo(hdc, (rect.left+rect.right)/1.8, (rect.top+rect.bottom)/1.8);

//            MoveToEx(hdc, (rect.left+rect.right)/1.3, (rect.top+rect.bottom)/6, lpPoint);
//            LineTo(hdc, (rect.left+rect.right)/1.3, (rect.top+rect.bottom)/1.8);
//            //2
//            MoveToEx(hdc, (rect.left+rect.right)/6, (rect.top+rect.bottom)/6, lpPoint);
//            LineTo(hdc, (rect.left+rect.right)/4, (rect.top+rect.bottom)/6);
//            LineTo(hdc, (rect.left+rect.right)/4, (rect.top+rect.bottom)/3);
//            LineTo(hdc, (rect.left+rect.right)/6, (rect.top+rect.bottom)/3);
//            LineTo(hdc, (rect.left+rect.right)/6, (rect.top+rect.bottom)/2);
//            LineTo(hdc, (rect.left+rect.right)/4, (rect.top+rect.bottom)/2);

//            MoveToEx(hdc, (rect.left+rect.right)/3, (rect.top+rect.bottom)/6, lpPoint);
//            LineTo(hdc, (rect.left+rect.right)/2.3, (rect.top+rect.bottom)/6);
//            LineTo(hdc, (rect.left+rect.right)/2.3, (rect.top+rect.bottom)/3);
//            LineTo(hdc, (rect.left+rect.right)/3, (rect.top+rect.bottom)/3);
//            LineTo(hdc, (rect.left+rect.right)/3, (rect.top+rect.bottom)/2);
//            LineTo(hdc, (rect.left+rect.right)/2.3, (rect.top+rect.bottom)/2);

//            MoveToEx(hdc, (rect.left+rect.right)/1.9, (rect.top+rect.bottom)/6, lpPoint);
//            LineTo(hdc, (rect.left+rect.right)/1.6, (rect.top+rect.bottom)/6);
//            LineTo(hdc, (rect.left+rect.right)/1.6, (rect.top+rect.bottom)/3);
//            LineTo(hdc, (rect.left+rect.right)/1.9, (rect.top+rect.bottom)/3);
//            LineTo(hdc, (rect.left+rect.right)/1.9, (rect.top+rect.bottom)/2);
//            LineTo(hdc, (rect.left+rect.right)/1.6, (rect.top+rect.bottom)/2);
//
//            MoveToEx(hdc, (rect.left+rect.right)/1.5, (rect.top+rect.bottom)/6, lpPoint);
//            LineTo(hdc, (rect.left+rect.right)/1.3, (rect.top+rect.bottom)/6);
//            LineTo(hdc, (rect.left+rect.right)/1.3, (rect.top+rect.bottom)/3);
//            LineTo(hdc, (rect.left+rect.right)/1.5, (rect.top+rect.bottom)/3);
//            LineTo(hdc, (rect.left+rect.right)/1.5, (rect.top+rect.bottom)/2);
//            LineTo(hdc, (rect.left+rect.right)/1.3, (rect.top+rect.bottom)/2);
            //3
//            MoveToEx(hdc, (rect.left+rect.right)/6, (rect.top+rect.bottom)/6, lpPoint);
//            LineTo(hdc, (rect.left+rect.right)/4, (rect.top+rect.bottom)/6);
//            LineTo(hdc, (rect.left+rect.right)/4, (rect.top+rect.bottom)/3);
//            LineTo(hdc, (rect.left+rect.right)/6, (rect.top+rect.bottom)/3);
//            MoveToEx(hdc, (rect.left+rect.right)/4, (rect.top+rect.bottom)/3, lpPoint);
//            LineTo(hdc, (rect.left+rect.right)/4, (rect.top+rect.bottom)/2);
//            LineTo(hdc, (rect.left+rect.right)/6, (rect.top+rect.bottom)/2);
//
//            MoveToEx(hdc, (rect.left+rect.right)/3, (rect.top+rect.bottom)/6, lpPoint);
//            LineTo(hdc, (rect.left+rect.right)/2.3, (rect.top+rect.bottom)/6);
//            LineTo(hdc, (rect.left+rect.right)/2.3, (rect.top+rect.bottom)/3);
//            LineTo(hdc, (rect.left+rect.right)/3, (rect.top+rect.bottom)/3);
//            MoveToEx(hdc, (rect.left+rect.right)/2.3, (rect.top+rect.bottom)/3, lpPoint);
//            LineTo(hdc, (rect.left+rect.right)/2.3, (rect.top+rect.bottom)/2);
//            LineTo(hdc, (rect.left+rect.right)/3, (rect.top+rect.bottom)/2);
//
//            MoveToEx(hdc, (rect.left+rect.right)/1.9, (rect.top+rect.bottom)/6, lpPoint);
//            LineTo(hdc, (rect.left+rect.right)/1.6, (rect.top+rect.bottom)/6);
//            LineTo(hdc, (rect.left+rect.right)/1.6, (rect.top+rect.bottom)/3);
//            LineTo(hdc, (rect.left+rect.right)/1.9, (rect.top+rect.bottom)/3);
//            MoveToEx(hdc, (rect.left+rect.right)/1.6, (rect.top+rect.bottom)/3, lpPoint);
//            LineTo(hdc, (rect.left+rect.right)/1.6, (rect.top+rect.bottom)/2);
//            LineTo(hdc, (rect.left+rect.right)/1.9, (rect.top+rect.bottom)/2);
//
//            MoveToEx(hdc, (rect.left+rect.right)/1.5, (rect.top+rect.bottom)/6, lpPoint);
//            LineTo(hdc, (rect.left+rect.right)/1.3, (rect.top+rect.bottom)/6);
//            LineTo(hdc, (rect.left+rect.right)/1.3, (rect.top+rect.bottom)/3);
//            LineTo(hdc, (rect.left+rect.right)/1.5, (rect.top+rect.bottom)/3);
//            MoveToEx(hdc, (rect.left+rect.right)/1.3, (rect.top+rect.bottom)/3, lpPoint);
//            LineTo(hdc, (rect.left+rect.right)/1.3, (rect.top+rect.bottom)/2);
//            LineTo(hdc, (rect.left+rect.right)/1.5, (rect.top+rect.bottom)/2);
//            //4
//            MoveToEx(hdc, (rect.left+rect.right)/6, (rect.top+rect.bottom)/6, lpPoint);
//            LineTo(hdc, (rect.left+rect.right)/6, (rect.top+rect.bottom)/3);
//            LineTo(hdc, (rect.left+rect.right)/4, (rect.top+rect.bottom)/3);
//            MoveToEx(hdc, (rect.left+rect.right)/4.5, (rect.top+rect.bottom)/6, lpPoint);
//            LineTo(hdc, (rect.left+rect.right)/4.5, (rect.top+rect.bottom)/2);
//
//            MoveToEx(hdc, (rect.left+rect.right)/3, (rect.top+rect.bottom)/6, lpPoint);
//            LineTo(hdc, (rect.left+rect.right)/3, (rect.top+rect.bottom)/3);
//            LineTo(hdc, (rect.left+rect.right)/2.3, (rect.top+rect.bottom)/3);
//            MoveToEx(hdc, (rect.left+rect.right)/2.5, (rect.top+rect.bottom)/6, lpPoint);
//            LineTo(hdc, (rect.left+rect.right)/2.5, (rect.top+rect.bottom)/2);
//
//            MoveToEx(hdc, (rect.left+rect.right)/1.9, (rect.top+rect.bottom)/6, lpPoint);
//            LineTo(hdc, (rect.left+rect.right)/1.9, (rect.top+rect.bottom)/3);
//            LineTo(hdc, (rect.left+rect.right)/1.6, (rect.top+rect.bottom)/3);
//            MoveToEx(hdc, (rect.left+rect.right)/1.7, (rect.top+rect.bottom)/6, lpPoint);
//            LineTo(hdc, (rect.left+rect.right)/1.7, (rect.top+rect.bottom)/2);
//
//            MoveToEx(hdc, (rect.left+rect.right)/1.5, (rect.top+rect.bottom)/6, lpPoint);
//            LineTo(hdc, (rect.left+rect.right)/1.5, (rect.top+rect.bottom)/3);
//            LineTo(hdc, (rect.left+rect.right)/1.3, (rect.top+rect.bottom)/3);
//            MoveToEx(hdc, (rect.left+rect.right)/1.4, (rect.top+rect.bottom)/6, lpPoint);
//            LineTo(hdc, (rect.left+rect.right)/1.4, (rect.top+rect.bottom)/2);
//            5
//            MoveToEx(hdc, (rect.left+rect.right)/6, (rect.top+rect.bottom)/6, lpPoint);
//            LineTo(hdc, (rect.left+rect.right)/4, (rect.top+rect.bottom)/6);
//            MoveToEx(hdc, (rect.left+rect.right)/6, (rect.top+rect.bottom)/6, lpPoint);
//            LineTo(hdc, (rect.left+rect.right)/6, (rect.top+rect.bottom)/3);
//            LineTo(hdc, (rect.left+rect.right)/4, (rect.top+rect.bottom)/3);
//            LineTo(hdc, (rect.left+rect.right)/4, (rect.top+rect.bottom)/2);
//            LineTo(hdc, (rect.left+rect.right)/6, (rect.top+rect.bottom)/2);

//            MoveToEx(hdc, (rect.left+rect.right)/3, (rect.top+rect.bottom)/6, lpPoint);
//            LineTo(hdc, (rect.left+rect.right)/2.3, (rect.top+rect.bottom)/6);
//            MoveToEx(hdc, (rect.left+rect.right)/3, (rect.top+rect.bottom)/6, lpPoint);
//            LineTo(hdc, (rect.left+rect.right)/3, (rect.top+rect.bottom)/3);
//            LineTo(hdc, (rect.left+rect.right)/2.3, (rect.top+rect.bottom)/3);
//            LineTo(hdc, (rect.left+rect.right)/2.3, (rect.top+rect.bottom)/2);
//            LineTo(hdc, (rect.left+rect.right)/3, (rect.top+rect.bottom)/2);
//
//            MoveToEx(hdc, (rect.left+rect.right)/1.9, (rect.top+rect.bottom)/6, lpPoint);
//            LineTo(hdc, (rect.left+rect.right)/1.6, (rect.top+rect.bottom)/6);
//            MoveToEx(hdc, (rect.left+rect.right)/1.9, (rect.top+rect.bottom)/6, lpPoint);
//            LineTo(hdc, (rect.left+rect.right)/1.9, (rect.top+rect.bottom)/3);
//            LineTo(hdc, (rect.left+rect.right)/1.6, (rect.top+rect.bottom)/3);
//            LineTo(hdc, (rect.left+rect.right)/1.6, (rect.top+rect.bottom)/2);
//            LineTo(hdc, (rect.left+rect.right)/1.9, (rect.top+rect.bottom)/2);
//
//            MoveToEx(hdc, (rect.left+rect.right)/1.5, (rect.top+rect.bottom)/6, lpPoint);
//            LineTo(hdc, (rect.left+rect.right)/1.3, (rect.top+rect.bottom)/6);
//            MoveToEx(hdc, (rect.left+rect.right)/1.5, (rect.top+rect.bottom)/6, lpPoint);
//            LineTo(hdc, (rect.left+rect.right)/1.5, (rect.top+rect.bottom)/3);
//            LineTo(hdc, (rect.left+rect.right)/1.3, (rect.top+rect.bottom)/3);
//            LineTo(hdc, (rect.left+rect.right)/1.3, (rect.top+rect.bottom)/2);
//            LineTo(hdc, (rect.left+rect.right)/1.5, (rect.top+rect.bottom)/2);
//          6
//            MoveToEx(hdc, (rect.left+rect.right)/6, (rect.top+rect.bottom)/6, lpPoint);
//            LineTo(hdc, (rect.left+rect.right)/6, (rect.top+rect.bottom)/2);
//            LineTo(hdc, (rect.left+rect.right)/4, (rect.top+rect.bottom)/2);
//            LineTo(hdc, (rect.left+rect.right)/4, (rect.top+rect.bottom)/3);
//            LineTo(hdc, (rect.left+rect.right)/6, (rect.top+rect.bottom)/3);
//
//            MoveToEx(hdc, (rect.left+rect.right)/3, (rect.top+rect.bottom)/6, lpPoint);
//            LineTo(hdc, (rect.left+rect.right)/3, (rect.top+rect.bottom)/2);
//            LineTo(hdc, (rect.left+rect.right)/2.3, (rect.top+rect.bottom)/2);
//            LineTo(hdc, (rect.left+rect.right)/2.3, (rect.top+rect.bottom)/3);
//            LineTo(hdc, (rect.left+rect.right)/3, (rect.top+rect.bottom)/3);
//
//            MoveToEx(hdc, (rect.left+rect.right)/1.9, (rect.top+rect.bottom)/6, lpPoint);
//            LineTo(hdc, (rect.left+rect.right)/1.9, (rect.top+rect.bottom)/2);
//            LineTo(hdc, (rect.left+rect.right)/1.6, (rect.top+rect.bottom)/2);
//            LineTo(hdc, (rect.left+rect.right)/1.6, (rect.top+rect.bottom)/3);
//            LineTo(hdc, (rect.left+rect.right)/1.9, (rect.top+rect.bottom)/3);

//            MoveToEx(hdc, (rect.left+rect.right)/1.5, (rect.top+rect.bottom)/6, lpPoint);
//            LineTo(hdc, (rect.left+rect.right)/1.5, (rect.top+rect.bottom)/2);
//            LineTo(hdc, (rect.left+rect.right)/1.3, (rect.top+rect.bottom)/2);
//            LineTo(hdc, (rect.left+rect.right)/1.3, (rect.top+rect.bottom)/3);
//            LineTo(hdc, (rect.left+rect.right)/1.5, (rect.top+rect.bottom)/3);
            //7
//            MoveToEx(hdc, (rect.left+rect.right)/3, (rect.top+rect.bottom)/6, lpPoint);
//            LineTo(hdc, (rect.left+rect.right)/2.3, (rect.top+rect.bottom)/6);
//            LineTo(hdc, (rect.left+rect.right)/2.3, (rect.top+rect.bottom)/2);
//
//            MoveToEx(hdc, (rect.left+rect.right)/1.5, (rect.top+rect.bottom)/6, lpPoint);
//            LineTo(hdc, (rect.left+rect.right)/1.3, (rect.top+rect.bottom)/6);
//            LineTo(hdc, (rect.left+rect.right)/1.3, (rect.top+rect.bottom)/2);
                //8
//            Rectangle(hdc, (rect.left+rect.right)/3, (rect.top+rect.bottom)/6,
//                      (rect.left+rect.right)/2.3, (rect.top+rect.bottom)/2);
//            MoveToEx(hdc, (rect.left+rect.right)/3, (rect.top+rect.bottom)/3, lpPoint);
//            LineTo(hdc, (rect.left+rect.right)/2.3, (rect.top+rect.bottom)/3);
//
//            Rectangle(hdc, (rect.left+rect.right)/1.5, (rect.top+rect.bottom)/6,
//                      (rect.left+rect.right)/1.3, (rect.top+rect.bottom)/2);
//            MoveToEx(hdc, (rect.left+rect.right)/1.5, (rect.top+rect.bottom)/3, lpPoint);
//            LineTo(hdc, (rect.left+rect.right)/1.3, (rect.top+rect.bottom)/3);
//            //9
//            MoveToEx(hdc, (rect.left+rect.right)/3, (rect.top+rect.bottom)/6, lpPoint);
//            LineTo(hdc, (rect.left+rect.right)/2.3, (rect.top+rect.bottom)/6);
//            LineTo(hdc, (rect.left+rect.right)/2.3, (rect.top+rect.bottom)/3);
//            LineTo(hdc, (rect.left+rect.right)/3, (rect.top+rect.bottom)/3);
//            LineTo(hdc, (rect.left+rect.right)/3, (rect.top+rect.bottom)/6);
//            MoveToEx(hdc, (rect.left+rect.right)/2.3, (rect.top+rect.bottom)/3, lpPoint);
//            LineTo(hdc, (rect.left+rect.right)/2.3, (rect.top+rect.bottom)/2);
//            LineTo(hdc, (rect.left+rect.right)/3, (rect.top+rect.bottom)/2);
//
//            MoveToEx(hdc, (rect.left+rect.right)/1.5, (rect.top+rect.bottom)/6, lpPoint);
//            LineTo(hdc, (rect.left+rect.right)/1.3, (rect.top+rect.bottom)/6);
//            LineTo(hdc, (rect.left+rect.right)/1.3, (rect.top+rect.bottom)/3);
//            LineTo(hdc, (rect.left+rect.right)/1.5, (rect.top+rect.bottom)/3);
//            LineTo(hdc, (rect.left+rect.right)/1.5, (rect.top+rect.bottom)/6);
//            MoveToEx(hdc, (rect.left+rect.right)/1.3, (rect.top+rect.bottom)/3, lpPoint);
//            LineTo(hdc, (rect.left+rect.right)/1.3, (rect.top+rect.bottom)/2);
//            LineTo(hdc, (rect.left+rect.right)/1.5, (rect.top+rect.bottom)/2);
            if(l==0){
                Rectangle(hdc, (rect.left+rect.right)/1.5, (rect.top+rect.bottom)/6,
                          (rect.right+rect.left)/1.25, (rect.bottom+rect.top)/1.8);
            }else if(l==1){
                MoveToEx(hdc, (rect.left+rect.right)/1.3, (rect.top+rect.bottom)/6, lpPoint);
                LineTo(hdc, (rect.left+rect.right)/1.3, (rect.top+rect.bottom)/1.8);
            }else if(l==2){
                MoveToEx(hdc, (rect.left+rect.right)/1.5, (rect.top+rect.bottom)/6, lpPoint);
                LineTo(hdc, (rect.left+rect.right)/1.3, (rect.top+rect.bottom)/6);
                LineTo(hdc, (rect.left+rect.right)/1.3, (rect.top+rect.bottom)/3);
                LineTo(hdc, (rect.left+rect.right)/1.5, (rect.top+rect.bottom)/3);
                LineTo(hdc, (rect.left+rect.right)/1.5, (rect.top+rect.bottom)/2);
                LineTo(hdc, (rect.left+rect.right)/1.3, (rect.top+rect.bottom)/2);
            }else if(l==3){
                MoveToEx(hdc, (rect.left+rect.right)/1.5, (rect.top+rect.bottom)/6, lpPoint);
                LineTo(hdc, (rect.left+rect.right)/1.3, (rect.top+rect.bottom)/6);
                LineTo(hdc, (rect.left+rect.right)/1.3, (rect.top+rect.bottom)/3);
                LineTo(hdc, (rect.left+rect.right)/1.5, (rect.top+rect.bottom)/3);
                MoveToEx(hdc, (rect.left+rect.right)/1.3, (rect.top+rect.bottom)/3, lpPoint);
                LineTo(hdc, (rect.left+rect.right)/1.3, (rect.top+rect.bottom)/2);
                LineTo(hdc, (rect.left+rect.right)/1.5, (rect.top+rect.bottom)/2);
            }else if(l==4){
                MoveToEx(hdc, (rect.left+rect.right)/1.5, (rect.top+rect.bottom)/6, lpPoint);
                LineTo(hdc, (rect.left+rect.right)/1.5, (rect.top+rect.bottom)/3);
                LineTo(hdc, (rect.left+rect.right)/1.3, (rect.top+rect.bottom)/3);
                MoveToEx(hdc, (rect.left+rect.right)/1.4, (rect.top+rect.bottom)/6, lpPoint);
                LineTo(hdc, (rect.left+rect.right)/1.4, (rect.top+rect.bottom)/2);
            }else if(l==5){
                MoveToEx(hdc, (rect.left+rect.right)/1.5, (rect.top+rect.bottom)/6, lpPoint);
                LineTo(hdc, (rect.left+rect.right)/1.3, (rect.top+rect.bottom)/6);
                MoveToEx(hdc, (rect.left+rect.right)/1.5, (rect.top+rect.bottom)/6, lpPoint);
                LineTo(hdc, (rect.left+rect.right)/1.5, (rect.top+rect.bottom)/3);
                LineTo(hdc, (rect.left+rect.right)/1.3, (rect.top+rect.bottom)/3);
                LineTo(hdc, (rect.left+rect.right)/1.3, (rect.top+rect.bottom)/2);
                LineTo(hdc, (rect.left+rect.right)/1.5, (rect.top+rect.bottom)/2);
            }else if(l==6){
                MoveToEx(hdc, (rect.left+rect.right)/1.5, (rect.top+rect.bottom)/6, lpPoint);
                LineTo(hdc, (rect.left+rect.right)/1.5, (rect.top+rect.bottom)/2);
                LineTo(hdc, (rect.left+rect.right)/1.3, (rect.top+rect.bottom)/2);
                LineTo(hdc, (rect.left+rect.right)/1.3, (rect.top+rect.bottom)/3);
                LineTo(hdc, (rect.left+rect.right)/1.5, (rect.top+rect.bottom)/3);
            }else if(l==7){
                MoveToEx(hdc, (rect.left+rect.right)/1.5, (rect.top+rect.bottom)/6, lpPoint);
                LineTo(hdc, (rect.left+rect.right)/1.3, (rect.top+rect.bottom)/6);
                LineTo(hdc, (rect.left+rect.right)/1.3, (rect.top+rect.bottom)/2);
            }else if(l==8){
                Rectangle(hdc, (rect.left+rect.right)/1.5, (rect.top+rect.bottom)/6,
                          (rect.left+rect.right)/1.3, (rect.top+rect.bottom)/2);
                MoveToEx(hdc, (rect.left+rect.right)/1.5, (rect.top+rect.bottom)/3, lpPoint);
                LineTo(hdc, (rect.left+rect.right)/1.3, (rect.top+rect.bottom)/3);
            }else if(l==9){
                MoveToEx(hdc, (rect.left+rect.right)/1.5, (rect.top+rect.bottom)/6, lpPoint);
                LineTo(hdc, (rect.left+rect.right)/1.3, (rect.top+rect.bottom)/6);
                LineTo(hdc, (rect.left+rect.right)/1.3, (rect.top+rect.bottom)/3);
                LineTo(hdc, (rect.left+rect.right)/1.5, (rect.top+rect.bottom)/3);
                LineTo(hdc, (rect.left+rect.right)/1.5, (rect.top+rect.bottom)/6);
                MoveToEx(hdc, (rect.left+rect.right)/1.3, (rect.top+rect.bottom)/3, lpPoint);
                LineTo(hdc, (rect.left+rect.right)/1.3, (rect.top+rect.bottom)/2);
                LineTo(hdc, (rect.left+rect.right)/1.5, (rect.top+rect.bottom)/2);
            }else{}

            //十位
            if(k==0){
                Rectangle(hdc, (rect.left+rect.right)/2, (rect.top+rect.bottom)/6,
                          (rect.right+rect.left)/1.6, (rect.bottom+rect.top)/1.8);
            }else if(k==1){
                MoveToEx(hdc, (rect.left+rect.right)/1.8, (rect.top+rect.bottom)/6, lpPoint);
                LineTo(hdc, (rect.left+rect.right)/1.8, (rect.top+rect.bottom)/1.8);
            }else if(k==2){
                MoveToEx(hdc, (rect.left+rect.right)/1.9, (rect.top+rect.bottom)/6, lpPoint);
                LineTo(hdc, (rect.left+rect.right)/1.6, (rect.top+rect.bottom)/6);
                LineTo(hdc, (rect.left+rect.right)/1.6, (rect.top+rect.bottom)/3);
                LineTo(hdc, (rect.left+rect.right)/1.9, (rect.top+rect.bottom)/3);
                LineTo(hdc, (rect.left+rect.right)/1.9, (rect.top+rect.bottom)/2);
                LineTo(hdc, (rect.left+rect.right)/1.6, (rect.top+rect.bottom)/2);
            }else if(k==3){
                MoveToEx(hdc, (rect.left+rect.right)/1.9, (rect.top+rect.bottom)/6, lpPoint);
                LineTo(hdc, (rect.left+rect.right)/1.6, (rect.top+rect.bottom)/6);
                LineTo(hdc, (rect.left+rect.right)/1.6, (rect.top+rect.bottom)/3);
                LineTo(hdc, (rect.left+rect.right)/1.9, (rect.top+rect.bottom)/3);
                MoveToEx(hdc, (rect.left+rect.right)/1.6, (rect.top+rect.bottom)/3, lpPoint);
                LineTo(hdc, (rect.left+rect.right)/1.6, (rect.top+rect.bottom)/2);
                LineTo(hdc, (rect.left+rect.right)/1.9, (rect.top+rect.bottom)/2);
            }else if(k==4){
                MoveToEx(hdc, (rect.left+rect.right)/1.9, (rect.top+rect.bottom)/6, lpPoint);
                LineTo(hdc, (rect.left+rect.right)/1.9, (rect.top+rect.bottom)/3);
                LineTo(hdc, (rect.left+rect.right)/1.6, (rect.top+rect.bottom)/3);
                MoveToEx(hdc, (rect.left+rect.right)/1.7, (rect.top+rect.bottom)/6, lpPoint);
                LineTo(hdc, (rect.left+rect.right)/1.7, (rect.top+rect.bottom)/2);
            }else if(k==5){
                MoveToEx(hdc, (rect.left+rect.right)/1.9, (rect.top+rect.bottom)/6, lpPoint);
                LineTo(hdc, (rect.left+rect.right)/1.6, (rect.top+rect.bottom)/6);
                MoveToEx(hdc, (rect.left+rect.right)/1.9, (rect.top+rect.bottom)/6, lpPoint);
                LineTo(hdc, (rect.left+rect.right)/1.9, (rect.top+rect.bottom)/3);
                LineTo(hdc, (rect.left+rect.right)/1.6, (rect.top+rect.bottom)/3);
                LineTo(hdc, (rect.left+rect.right)/1.6, (rect.top+rect.bottom)/2);
                LineTo(hdc, (rect.left+rect.right)/1.9, (rect.top+rect.bottom)/2);
            }else if(k==6){
                MoveToEx(hdc, (rect.left+rect.right)/1.9, (rect.top+rect.bottom)/6, lpPoint);
                LineTo(hdc, (rect.left+rect.right)/1.9, (rect.top+rect.bottom)/2);
                LineTo(hdc, (rect.left+rect.right)/1.6, (rect.top+rect.bottom)/2);
                LineTo(hdc, (rect.left+rect.right)/1.6, (rect.top+rect.bottom)/3);
                LineTo(hdc, (rect.left+rect.right)/1.9, (rect.top+rect.bottom)/3);
            }else {}

            //百位
            if(j==0){
                Rectangle(hdc, (rect.left+rect.right)/3.1, (rect.top+rect.bottom)/6,
                          (rect.right+rect.left)/2.3, (rect.bottom+rect.top)/1.8);
            }else if(j==1){
                MoveToEx(hdc, (rect.left+rect.right)/2.5, (rect.top+rect.bottom)/6, lpPoint);
                LineTo(hdc, (rect.left+rect.right)/2.5, (rect.top+rect.bottom)/1.8);
            }else if(j==2){
                MoveToEx(hdc, (rect.left+rect.right)/3, (rect.top+rect.bottom)/6, lpPoint);
                LineTo(hdc, (rect.left+rect.right)/2.3, (rect.top+rect.bottom)/6);
                LineTo(hdc, (rect.left+rect.right)/2.3, (rect.top+rect.bottom)/3);
                LineTo(hdc, (rect.left+rect.right)/3, (rect.top+rect.bottom)/3);
                LineTo(hdc, (rect.left+rect.right)/3, (rect.top+rect.bottom)/2);
                LineTo(hdc, (rect.left+rect.right)/2.3, (rect.top+rect.bottom)/2);
            }else if(j==3){
                MoveToEx(hdc, (rect.left+rect.right)/3, (rect.top+rect.bottom)/6, lpPoint);
                LineTo(hdc, (rect.left+rect.right)/2.3, (rect.top+rect.bottom)/6);
                LineTo(hdc, (rect.left+rect.right)/2.3, (rect.top+rect.bottom)/3);
                LineTo(hdc, (rect.left+rect.right)/3, (rect.top+rect.bottom)/3);
                MoveToEx(hdc, (rect.left+rect.right)/2.3, (rect.top+rect.bottom)/3, lpPoint);
                LineTo(hdc, (rect.left+rect.right)/2.3, (rect.top+rect.bottom)/2);
                LineTo(hdc, (rect.left+rect.right)/3, (rect.top+rect.bottom)/2);
            }else if(j==4){
                MoveToEx(hdc, (rect.left+rect.right)/3, (rect.top+rect.bottom)/6, lpPoint);
                LineTo(hdc, (rect.left+rect.right)/3, (rect.top+rect.bottom)/3);
                LineTo(hdc, (rect.left+rect.right)/2.3, (rect.top+rect.bottom)/3);
                MoveToEx(hdc, (rect.left+rect.right)/2.5, (rect.top+rect.bottom)/6, lpPoint);
                LineTo(hdc, (rect.left+rect.right)/2.5, (rect.top+rect.bottom)/2);
            }else if(j==5){
                MoveToEx(hdc, (rect.left+rect.right)/3, (rect.top+rect.bottom)/6, lpPoint);
                LineTo(hdc, (rect.left+rect.right)/2.3, (rect.top+rect.bottom)/6);
                MoveToEx(hdc, (rect.left+rect.right)/3, (rect.top+rect.bottom)/6, lpPoint);
                LineTo(hdc, (rect.left+rect.right)/3, (rect.top+rect.bottom)/3);
                LineTo(hdc, (rect.left+rect.right)/2.3, (rect.top+rect.bottom)/3);
                LineTo(hdc, (rect.left+rect.right)/2.3, (rect.top+rect.bottom)/2);
                LineTo(hdc, (rect.left+rect.right)/3, (rect.top+rect.bottom)/2);
            }else if(j==6){
                MoveToEx(hdc, (rect.left+rect.right)/3, (rect.top+rect.bottom)/6, lpPoint);
                LineTo(hdc, (rect.left+rect.right)/3, (rect.top+rect.bottom)/2);
                LineTo(hdc, (rect.left+rect.right)/2.3, (rect.top+rect.bottom)/2);
                LineTo(hdc, (rect.left+rect.right)/2.3, (rect.top+rect.bottom)/3);
                LineTo(hdc, (rect.left+rect.right)/3, (rect.top+rect.bottom)/3);
            }else if(j==7){
                MoveToEx(hdc, (rect.left+rect.right)/3, (rect.top+rect.bottom)/6, lpPoint);
                LineTo(hdc, (rect.left+rect.right)/2.3, (rect.top+rect.bottom)/6);
                LineTo(hdc, (rect.left+rect.right)/2.3, (rect.top+rect.bottom)/2);
            }else if(j==8){
                Rectangle(hdc, (rect.left+rect.right)/3, (rect.top+rect.bottom)/6,
                          (rect.left+rect.right)/2.3, (rect.top+rect.bottom)/2);
                MoveToEx(hdc, (rect.left+rect.right)/3, (rect.top+rect.bottom)/3, lpPoint);
                LineTo(hdc, (rect.left+rect.right)/2.3, (rect.top+rect.bottom)/3);
            }else if(j==9){
                MoveToEx(hdc, (rect.left+rect.right)/3, (rect.top+rect.bottom)/6, lpPoint);
                LineTo(hdc, (rect.left+rect.right)/2.3, (rect.top+rect.bottom)/6);
                LineTo(hdc, (rect.left+rect.right)/2.3, (rect.top+rect.bottom)/3);
                LineTo(hdc, (rect.left+rect.right)/3, (rect.top+rect.bottom)/3);
                LineTo(hdc, (rect.left+rect.right)/3, (rect.top+rect.bottom)/6);
                MoveToEx(hdc, (rect.left+rect.right)/2.3, (rect.top+rect.bottom)/3, lpPoint);
                LineTo(hdc, (rect.left+rect.right)/2.3, (rect.top+rect.bottom)/2);
                LineTo(hdc, (rect.left+rect.right)/3, (rect.top+rect.bottom)/2);
            }else{}

            //千位
            if(i==0){
                Rectangle(hdc, (rect.left+rect.right)/7, (rect.top+rect.bottom)/6,
                          (rect.right+rect.left)/4, (rect.bottom+rect.top)/1.8);
            }else if(i==1){
                MoveToEx(hdc, (rect.left+rect.right)/5, (rect.top+rect.bottom)/6, lpPoint);
                LineTo(hdc, (rect.left+rect.right)/5, (rect.top+rect.bottom)/1.8);
            }else if(i==2){
                MoveToEx(hdc, (rect.left+rect.right)/6, (rect.top+rect.bottom)/6, lpPoint);
                LineTo(hdc, (rect.left+rect.right)/4, (rect.top+rect.bottom)/6);
                LineTo(hdc, (rect.left+rect.right)/4, (rect.top+rect.bottom)/3);
                LineTo(hdc, (rect.left+rect.right)/6, (rect.top+rect.bottom)/3);
                LineTo(hdc, (rect.left+rect.right)/6, (rect.top+rect.bottom)/2);
                LineTo(hdc, (rect.left+rect.right)/4, (rect.top+rect.bottom)/2);
            }else if(i==3){
                MoveToEx(hdc, (rect.left+rect.right)/6, (rect.top+rect.bottom)/6, lpPoint);
                LineTo(hdc, (rect.left+rect.right)/4, (rect.top+rect.bottom)/6);
                LineTo(hdc, (rect.left+rect.right)/4, (rect.top+rect.bottom)/3);
                LineTo(hdc, (rect.left+rect.right)/6, (rect.top+rect.bottom)/3);
                MoveToEx(hdc, (rect.left+rect.right)/4, (rect.top+rect.bottom)/3, lpPoint);
                LineTo(hdc, (rect.left+rect.right)/4, (rect.top+rect.bottom)/2);
                LineTo(hdc, (rect.left+rect.right)/6, (rect.top+rect.bottom)/2);
            }else if(i==4){
                MoveToEx(hdc, (rect.left+rect.right)/6, (rect.top+rect.bottom)/6, lpPoint);
                LineTo(hdc, (rect.left+rect.right)/6, (rect.top+rect.bottom)/3);
                LineTo(hdc, (rect.left+rect.right)/4, (rect.top+rect.bottom)/3);
                MoveToEx(hdc, (rect.left+rect.right)/4.5, (rect.top+rect.bottom)/6, lpPoint);
                LineTo(hdc, (rect.left+rect.right)/4.5, (rect.top+rect.bottom)/2);
            }else if(i==5){
                MoveToEx(hdc, (rect.left+rect.right)/6, (rect.top+rect.bottom)/6, lpPoint);
                LineTo(hdc, (rect.left+rect.right)/4, (rect.top+rect.bottom)/6);
                MoveToEx(hdc, (rect.left+rect.right)/6, (rect.top+rect.bottom)/6, lpPoint);
                LineTo(hdc, (rect.left+rect.right)/6, (rect.top+rect.bottom)/3);
                LineTo(hdc, (rect.left+rect.right)/4, (rect.top+rect.bottom)/3);
                LineTo(hdc, (rect.left+rect.right)/4, (rect.top+rect.bottom)/2);
                LineTo(hdc, (rect.left+rect.right)/6, (rect.top+rect.bottom)/2);
            }else if(i==6){
                MoveToEx(hdc, (rect.left+rect.right)/6, (rect.top+rect.bottom)/6, lpPoint);
                LineTo(hdc, (rect.left+rect.right)/6, (rect.top+rect.bottom)/2);
                LineTo(hdc, (rect.left+rect.right)/4, (rect.top+rect.bottom)/2);
                LineTo(hdc, (rect.left+rect.right)/4, (rect.top+rect.bottom)/3);
                LineTo(hdc, (rect.left+rect.right)/6, (rect.top+rect.bottom)/3);
            }else {}

            ++l;
            if(l==9){
                l=0;
                k++;
                if(k==6){
                    k=0;
                    j++;
                    if(j==9){
                        j=0;
                        i++;
                    }
                }
            }
            DeleteObject(hP);
            EndPaint(hWnd, &ps);
            Sleep(100);
            if (i < 7)
                InvalidateRect(hWnd, NULL, 1);
            return 0;
        default:                    //默认时采用系统消息默认处理函数
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
}