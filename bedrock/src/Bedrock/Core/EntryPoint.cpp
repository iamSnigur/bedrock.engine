#include "Application.h"

int main()
{
	Bedrock::Application* app = new Bedrock::Application{};
	app->Boot();
	app->Run();
	delete app;

	return 0;
}
