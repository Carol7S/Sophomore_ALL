#include <windows.h>
//#include <tchar.h>

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
    HPEN hPenOld;
    LPPOINT lpPoint;
    POINT pt;
    RECT rect;
    switch(message){
        case WM_DESTROY:
            PostQuitMessage(0);     //调用PostQuiteMessage发出WM_QUIT消息
            break;
        case WM_PAINT:
            GetClientRect(hWnd, &rect);
            hdc = BeginPaint(hWnd, &ps);
            hP = (HPEN)CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
            hPenOld = (HPEN)SelectObject(hdc, hP);
            Ellipse(hdc, rect.left, rect.top, rect.right, rect.bottom);
            hP = (HPEN)CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
            hPenOld = (HPEN)SelectObject(hdc, hP);
            MoveToEx(hdc, (rect.left+rect.right)/2, rect.top, lpPoint);
            LineTo(hdc, rect.right, rect.bottom);
            LineTo(hdc, rect.left, rect.bottom);
            LineTo(hdc, (rect.left+rect.right)/2, rect.top);
            SelectObject(hdc, hPenOld);
            DeleteObject(hP);
            EndPaint(hWnd, &ps);
            break;
        default:                    //默认时采用系统消息默认处理函数
            return DefWindowProc(hWnd, message, wParam, lParam);
            break;
    }
    return 0;
}