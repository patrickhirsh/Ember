#pragma once

extern Ember::ApplicationToken Ember::CreateApplication();

int main(int argc, char* argv[])
{
	auto applicationToken = Ember::CreateApplication();
	applicationToken._application->Run(
		applicationToken._options,
		applicationToken._applicationTick,
		applicationToken._applicationOnEvent);
	delete applicationToken._application;
}