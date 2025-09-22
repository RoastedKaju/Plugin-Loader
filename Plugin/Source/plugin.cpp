#include "plugin.hpp"

void Plugin::init()
{
	std::cout << "Plugin initialized" << std::endl;
}

void Plugin::DoSomething()
{
	std::cout << "Using Interface you did something with a DLL type" << std::endl;
}

void InitPlugin()
{
	Plugin pluginInstance;
	pluginInstance.init();
}

IPlugin* CreatePluginInstance()
{
	return new Plugin();
}

void DestroyPluginInstance(IPlugin* plugin)
{
	std::cout << "Destroying Instance of Plugin" << std::endl;
	delete plugin;
}
