#include <Windows.h>
#include "Graphics.h"

Graphics* graphics;

//Funkcja zajmuj¹ca sie wiadomoœciami z okna (ruchy myszy, klikanie klawiszy, zamkniêcie okna itd.)
LRESULT CALLBACK WindowProc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam)
{
	if (uMsg == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd,
						 uMsg,
						 wParam,
						 lParam);
}

//G³ówna fukncja
int WINAPI wWinMain(HINSTANCE hInstance,
					HINSTANCE prevInstance,
					LPWSTR cmd,
					int nCmdShow)
{
	//Tworzenie okna
	WNDCLASSEX windowclass;
	ZeroMemory(&windowclass, sizeof(WNDCLASSEX));
	windowclass.cbSize = sizeof(WNDCLASSEX);
	windowclass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowclass.hInstance = hInstance;
	windowclass.lpfnWndProc = WindowProc;
	windowclass.lpszClassName = L"MainWindow";
	windowclass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&windowclass);

	RECT rect = { 0, 0, 800, 800 }; //Wymiary okna
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);

	//Tworzenie identyfikatora obiektu okna
	HWND windowhandle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MainWindow", L"MyGame", WS_OVERLAPPEDWINDOW, 100, 100, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, 0);

	//Jeœli dojdzie do b³êdu, zakoñcz program
	if (!windowhandle) return -1;

	//Tworzenie obiektu graphics, koñczenie programu w wypadku b³edu
	graphics = new Graphics();

	if (!graphics->Init(windowhandle))
	{
		delete graphics;
		return -1;
	}

	//Wyœwlietlanie okna
	ShowWindow(windowhandle, nCmdShow);

	//G³ówna pêtla
	MSG message;
	while (GetMessage(&message, NULL, 0, 0))
	{
		DispatchMessage(&message);
	}

	return 0;
}