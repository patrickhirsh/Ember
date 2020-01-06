#pragma once

extern Ember::Application* Ember::CreateApplication();

int main(int argc, char* argv[])
{
	auto application = Ember::CreateApplication();
	application->Run();
	delete application;
}