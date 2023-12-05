#include "PhysicsApplication.h"

int main(int argv, char* argc[])
{
	PhysicsApplication application;

	Debugger::print = true;

	application.InitializeWindow(1366, 728);

	application.Render();

	return -1;
}