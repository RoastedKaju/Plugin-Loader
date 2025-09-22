#include "plugin.hpp"

void Plugin::init()
{
	std::cout << "Plugin initialized" << std::endl;
}

void InitPlugin()
{
	Plugin pluginInstance;
	pluginInstance.init();
}
