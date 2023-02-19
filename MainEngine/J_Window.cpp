#include "J_Window.h"
#include "J_ImageManager.h"
#include "J_Input.h"
#include <J_GameEngineTime.h>
#include <J_SoundManager.h>

J_Window* J_Window::instance_ = new J_Window();
bool isWindowOn = true;
LRESULT CALLBACK WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);

J_Window::J_Window()
    : hInstance_(NULL),
    hWnd_(NULL),
    windowClassName_(""), 
    windowTitle_(""), 
    windowSize_(float4::ZERO), 
    windowPos_(float4::ZERO)
{
}

J_Window::~J_Window()
{
    if (nullptr != hWnd_)
    {
        DestroyWindow(hWnd_);
        hWnd_ = nullptr;
    }
}

void J_Window::CreateMainWindowClass(HINSTANCE _hInstance, const std::string& _windowClassName)
{
    if (NULL == _hInstance)
    {
        J_GameEngineDebug::AssertFalse();
        return;
    }

    if (true == _windowClassName.empty())
    {
        J_GameEngineDebug::AssertFalse();
        return;
    }

    hInstance_ = _hInstance;
    windowClassName_ = _windowClassName;

    //WNDCLASSEXW: �Ʒ��� ����üŸ�� ���� ����� typedef.
    //typedef struct tagWNDCLASSEXW {
    //    UINT        cbSize;
    //    /* Win 3.x */
    //    UINT        style;            �������� ����.
    //    WNDPROC     lpfnWndProc;      ������ ���� �޽����� ó���� �Լ� �̸�.    
    //    int         cbClsExtra;       ���� ����. ���� ���� ����.
    //    int         cbWndExtra;       ���� ����. ���� ���� ����.
    //    HINSTANCE   hInstance;        ������ Ŭ������ ����ϴ� ���α׷�(�ν��Ͻ�)�� �ڵ�.  
    //    HICON       hIcon;            ������ ������
    //    HCURSOR     hCursor;          �����쿡�� �� Ŀ�� ����.
    //    HBRUSH      hbrBackground;    ������ ����� ĥ�� Ư�� ���� �귯�� ������Ʈ ����. +1: ���, +2:ȸ��
    //    LPCWSTR     lpszMenuName;     ���α׷��� �� �޴� ����. ������� �����Ŷ�� NULL
    //    LPCWSTR     lpszClassName;    ������ Ŭ������ �̸�. MyRegisterClass()�� ���� OS�� ��ϵ� Ŭ�����̸��� �ٸ��� ������� �ʴ´�.
    //    /* Win 4.0 */
    //    HICON       hIconSm;          �����찡 �ּ�ȭ�Ǹ� ����� ������.
    //} WNDCLASSEXW, * PWNDCLASSEXW, NEAR* NPWNDCLASSEXW, FAR* LPWNDCLASSEXW;

    WNDCLASSEXA wcex{};
    wcex.cbSize = sizeof(WNDCLASSEXA);
    wcex.style = CS_HREDRAW | CS_VREDRAW;   //���� | ���� ȭ��ũ�� ���� �ɼ�
    wcex.lpfnWndProc = WndProc;             //DispatchMessage()�� ���� MSG������ ���� �������� �Ǵ� �Լ�. 
    wcex.cbClsExtra = 0;                    //??
    wcex.cbWndExtra = 0;                    //??
    wcex.hInstance = hInstance_;            //������ �ν��Ͻ��� �ڵ�.

    wcex.hIcon = nullptr;                   //�� �����찡 ����� �⺻ ������ �ڵ�.
    wcex.hCursor = nullptr;                 //�� �����찡 ����� Ŀ�� �ڵ�.
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);    //������ �⺻ ��� ��.

    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = windowClassName_.c_str();  //������ Ŭ���� �̸�.
    wcex.hIconSm = nullptr;                 //�� �����찡 �ּ�ȭ�Ǿ��� �� ����� ������ �ڵ�.

    RegisterClassExA(&wcex);    //������ ������ �ɼ��� �����츦 �׸��ڴٰ� OS���� ����ϴ� �Լ�. �����ϸ� 0�� ��ȯ.
}

void J_Window::CreateMainWindow(const std::string& _windowTitle, const float4& _windowPos, const float4& _windowSize)
{
    if (NULL == hInstance_)
    {
        J_GameEngineDebug::AssertFalse();
        return;
    }

    if (true == _windowTitle.empty())
    {
        J_GameEngineDebug::AssertFalse();
        return;
    }

    windowTitle_ = _windowTitle;

    hWnd_ = CreateWindowA(
        windowClassName_.c_str(),       //������ Ŭ���� �̸�.
        windowTitle_.c_str(),           //������ ����.
        WS_OVERLAPPEDWINDOW,            //������ ����: �⺻ ������.
        _windowPos.IntX(),              //������ ��ġ�� x��ǥ. CW_USEDEFAULT: ������.
        _windowPos.IntY(),              //������ ��ġ�� y��ǥ.
        _windowSize.IntX(),             //������ ���α���:
        _windowSize.IntY(),             //������ ���α���.
        nullptr,                        //�θ� �����찡 �ִٸ� ���� �ִ´�.
        nullptr,                        //�޴� �ڵ��� ���� �ִٸ� ���� �ִ´�.
        hInstance_,                     //�����츦 ���� ��ü�� �ν��Ͻ��� �ڵ��� �ִ´�.
        nullptr                         //???
    );


    if (NULL == hWnd_)
    {
        J_GameEngineDebug::AssertFalse();
        return;
    }

    ShowWindow(hWnd_, SW_SHOW);
    UpdateWindow(hWnd_);
    SetWindowPosAndSize(_windowPos, _windowSize);

    HDC windowHDC = ::GetDC(hWnd_);
    if (nullptr == windowHDC)
    {
        J_GameEngineDebug::AssertFalse();
        return;
    }

    J_ImageManager::GetInstance().InitializeWindow(windowHDC);
    //���α׷��� ����Ǹ� �ڵ����� ������� ��� �ڵ���� �����ϹǷ� ReleaseDC()������ ���� �ʾƵ� �ȴ�.
}

void J_Window::SetWindowPosAndSize(const float4& _windowPos, const float4& _windowSize)
{
    windowPos_ = _windowPos;
    windowSize_ = _windowSize;
    RECT windowRect = { 0, 0, windowSize_.IntX(), windowSize_.IntY() };
    AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, false);
    SetWindowPos(
        hWnd_,
        HWND_TOP,
        windowPos_.IntX(),
        windowPos_.IntY(),
        windowRect.right - windowRect.left, //windowSize_.IntX(), 
        windowRect.bottom - windowRect.top, //windowSize_.IntY(),
        0
    );
}

void J_Window::Update(void(*UpdateFunctions)())
{
    //MSG: �Ʒ� tagMSG ����üŸ�� ���� ������ typedef. ����ڰ� �Է��� ������ �����Ѵ�.
    //    typedef struct tagMSG {
    //        HWND        hwnd;         //�����츦 �׸� �� �ʿ��� ������ ������ �ִ� �ڵ�.
    //        UINT        message;      //����ڰ� �Է��� ����.
    //        WPARAM      wParam;       //�������� �Է� ����.
    //        LPARAM      lParam;       //�������� �Է� ����. WPARAM�� ���� ���������� �𸣰ڴ�.
    //        DWORD       time;         //�Է� �ð�.
    //        POINT       pt;           //�Է��� �������� ���콺 �����Ͱ� �ִ� ��ġ.
    //#ifdef _MAC
    //        DWORD       lPrivate;     
    //#endif
    //    } MSG, * PMSG, NEAR* NPMSG, FAR* LPMSG;

    //GetMessageW(): �Է��� �������� �ٸ� �Է³������ ù��° �Ű������� msg�� ���ؼ� �����ϰ�,
    //���� ����϶��� false�� ��ȯ�ؼ� ������ ������ �����츦 �ݴ´�.
    //�Է��� ������ ������ �ʵ� ������ ��� ����Ǿ�� �ϹǷ� ���⼭�� ������� �ʴ´�. 

    MSG msg;

    while (isWindowOn)
    {
        if (nullptr == UpdateFunctions) //������Ʈ �Լ������Ͱ� ������ �ȵǾ��ִٸ� ����.
        {
            assert(false && "nullptr == UpdateFunctions");
            return;
        }
        else
        {
            UpdateFunctions();
            //�Լ������͵� ����ó�� ���� '�Լ�'�̹Ƿ� �ݵ�� ()�� ������� �Ѵ�.
            //J_GameEngineTime::GetInstance().UpdateDeltaTime();
            //J_Input::GetInstance().Update();
            //J_SoundManager::GetInstance().UpdateSound();
        }

        if (0 != PeekMessage(   //PeekMessage(): ��� �Է�üũ�� �ϴٰ� �Է��� ������ 0�� �ƴ� �ٸ� ���� ��ȯ�ϰ� msg�� �Է��� �ڼ��� ������ �����Ѵ�.
            &msg,               //���� �Է��� ��ü���� ���� ����.
            //nullptr,            //������ �ڵ�. nullptr�� �־��ָ� ��� �������� �޼����� �� ó���Ѵ�.
            this->hWnd_,
            0,                  //���� �ּ�??
            0,                  //���� �ִ�??
            PM_REMOVE           //�����Ǵ� �޽��� ó�� ��� ����.
            //PM_REMOVE: �����Ǵ� �޽��� ����. PM_NOREMOVE: �����Ǵ� �޽����� ������� ó����. 
            //PM_NOYIELD: ??
        ))       
        {
            if (!TranslateAccelerator(msg.hwnd, nullptr, &msg))
            {
                TranslateMessage(&msg); //������� �Է� ������ ����, ��ȯ�ؼ� OS�� ������ �� �ִ� ���·� �����.
                DispatchMessage(&msg);  //WndProc()�� �޽����� ������.
            }
        }
    }
}

void J_Window::TurnOff()
{
    isWindowOn = false;
}

LRESULT CALLBACK WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
    switch (_message)
    {
    case WM_PAINT:
    {
        //WM_PAINT �޽����� �������� BeginPaint()�Լ��� ������ �ٸ� �����쿡 ������ ��ȿ������ �׸��� ����
        //���� �Լ��� WM_PAINT �޽����� ������ ���ͼ� ����� PeekMessage()�Լ��� 0�� ��ȯ���� �ʴ´�.
        //�׷��� WM_PAINT�޽����� ó���� �Ŷ�� �ݵ�� BeginPaint()�Լ��� ����ؾ� �Ѵ�. 
        //�ƴϸ� �ƿ� WM_PAINT �޽��� ��ü�� ���� ���� ���� DefWindowProc() �Լ��� �Ѱܾ� �Ѵ�.
        //GetDC()�Լ��� WM_PAINT �޽����� ó�������� ���ϹǷ� �ǹ� ����. �ݵ�� BeginPaint()���� �Ѵ�.

        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(_hWnd, &ps);
        EndPaint(_hWnd, &ps);
        break;
    }
    case WM_DESTROY:
    {
        isWindowOn = false;
        break;
    }
    default:
        return DefWindowProc(_hWnd, _message, _wParam, _lParam);
    }
    return 0;
}