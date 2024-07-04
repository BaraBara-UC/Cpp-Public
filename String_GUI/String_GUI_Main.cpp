/*
STRING_GUIは2024年7月4日（木）、薔薇薔薇UCに作られました。
開始時間：14:30
完成時間：15:00(当日)
*/

#include <windows.h>

LRESULT CALLBACK windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        
        SetTextColor(hdc, RGB(255, 255,255));
        SetBkMode(hdc, TRANSPARENT);

        RECT clientRect;
        GetClientRect(hwnd, &clientRect);

        HFONT hFont = CreateFontW(48, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
            DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
            VARIABLE_PITCH, L"Segoe UI Emoji");
        HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);

        const wchar_t * text = L"みんなさん、こんにちは😄";

        SIZE textSize;
        GetTextExtentPoint32W(hdc, text, lstrlenW(text), &textSize);
        int x = (clientRect.right - textSize.cx) / 2;
        int y = (clientRect.bottom - textSize.cy) / 2;

        TextOutW(hdc, x, y, text, lstrlenW(text));

        SelectObject(hdc, hOldFont);

        EndPaint(hwnd, &ps);
    }
                 return 0;
    case WM_ERASEBKGND:
        {
            RECT rect;
            GetClientRect(hwnd, &rect);
            HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
            FillRect((HDC)wParam, &rect, hBrush);
            DeleteObject(hBrush);
        }
        return 1;


    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    WNDCLASSW wc = { };

    wc.lpfnWndProc = windowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClassW(&wc);

    HWND hwnd = CreateWindowExW(
        0,
        CLASS_NAME,
        L"薔薇薔薇のウィンドウのコード",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    MSG msg = { };

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
