#include "includes.h"

#include "defines.h"

#include "functions.h"


ATOM CreateWindowAtom(LPCTSTR lpszAtomName, HINSTANCE hInstance, WNDPROC wndProc);

LRESULT CALLBACK wndProc(HWND, UINT, WPARAM, LPARAM);


int 
WINAPI
WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
) {

	ATOM atom = CreateWindowAtom(WINDOW_ATOM_NAME, hInstance, wndProc);

	if (INVALID_ATOM == atom) {
		return 1;
	}

	HWND hWnd = CreateWindowEx(0L, WINDOW_ATOM_NAME,
		TEXT("Minecraft LogTracker [ver.0.0.1]"),
		WS_OVERLAPPEDWINDOW, 50, 50, 300, 300,
		NULL, NULL, hInstance, NULL);

	if(IsWindow(hWnd)) {
		ShowWindow(hWnd, nCmdShow);
		UpdateWindow(hWnd);
		
		BOOL bRes;
		MSG msg;
		while (true) {
			bRes = GetMessage(&msg, NULL, 0U, 0U);
			if (bRes <= 0) break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	UnregisterClass(MAKEINTATOM(atom), hInstance);

	return 0;
}


ATOM CreateWindowAtom(LPCTSTR lpszAtomName, HINSTANCE hInstance, WNDPROC lpfnWndProc) {
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(wcex);
	wcex.cbClsExtra = 0L;
	wcex.cbWndExtra = 0L;

	wcex.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hInstance = hInstance;

	wcex.lpfnWndProc = lpfnWndProc;
	wcex.lpszClassName = lpszAtomName;
	wcex.lpszMenuName = NULL;

	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;

	return RegisterClassEx(&wcex);
}





LRESULT CALLBACK wndProc(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp) {
	switch (uMsg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, uMsg, wp, lp);
}