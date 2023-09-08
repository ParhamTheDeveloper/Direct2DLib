/*
	Include	the sample header file without changing the source code
*/
#include "General.h"

int main()
{
	GameApplication* application = new GameApplication(L"D2DLib Game Sample", 800, 600);

	application->Run();
	
	delete application;
	return 0;
}