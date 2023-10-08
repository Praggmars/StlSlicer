#include "application.h"

int Main()
{
	Application app;
	try 
	{
		app.Init(L"STL slicer", 1000, 500);
		app.Run();
	}
	catch (const std::exception& ex)
	{
		OutputDebugStringA(ex.what());
		MessageBoxA(nullptr, ex.what(), "Error", MB_OK);
	}

	return 0;
}

int WINAPI WinMain(HINSTANCE __in hInstance, HINSTANCE __in_opt hPrevInstance, LPSTR szCmdLine, int nCmdShow)
{
	return Main();
}

int main(int argc, char* argv[])
{
	return Main();
}