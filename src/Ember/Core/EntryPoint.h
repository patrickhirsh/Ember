#pragma once

extern Ember::Application* Ember::CreateApplication();

int main(int argc, char* argv[])
{
	auto app = Ember::CreateApplication();
	app->Run();
	delete app;
}