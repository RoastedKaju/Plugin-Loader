#include "loader.hpp"

#include <Windows.h>
#include <filesystem>
#include <iostream>

void Loader::LoadPlugin(const std::string& filePath)
{
	// Convert relative path to absolute
	std::filesystem::path relPath = filePath;
	std::filesystem::path absPath = std::filesystem::absolute(relPath);

	std::cout << "Full path is : " << absPath << std::endl;

	// Does file exist
	if (!std::filesystem::exists(absPath))
	{
		std::cerr << "File does not exist" << std::endl;
		return;
	}

	// Load library
	HMODULE module = LoadLibraryA(absPath.string().c_str());
	if (!module)
	{
		std::cerr << "Failed to load module" << std::endl;
		return;
	}

	// First try to run the normal test function
	typedef void(*InitPluginFunc)();

	InitPluginFunc initFunc = (InitPluginFunc)GetProcAddress(module, "InitPlugin");

	if (initFunc)
	{
		initFunc();
	}
	else
	{
		std::cout << "Failed to find a function called [InitPlugin] make sure the name and signature match" << std::endl;
	}

	// Now run the factory function that uses our interface
	typedef IPlugin* (*CreatePluginInstanceFunc)();

	CreatePluginInstanceFunc PluginInstanceCreaterFunc = (CreatePluginInstanceFunc)GetProcAddress(module, "CreatePluginInstance");
	if (PluginInstanceCreaterFunc)
	{
		IPlugin* instance = PluginInstanceCreaterFunc();
		instance->DoSomething();

		// For unique pointer
		std::unique_ptr<IPlugin> instanceUnique(PluginInstanceCreaterFunc()); // Safe caller owns this
		// For shared pointer (custom deleter provided)
		std::shared_ptr<IPlugin> instanceShared(PluginInstanceCreaterFunc(), [](IPlugin* plugin) { delete plugin; });
		// For shared pointer (deleter comes from DLL as well)
		typedef void(*DestroyPluginFunc)(IPlugin*);
		DestroyPluginFunc destroyPluginFunc = (DestroyPluginFunc)GetProcAddress(module, "DestroyPluginInstance");
		if (destroyPluginFunc)
		{
			std::shared_ptr<IPlugin> instanceShared2(PluginInstanceCreaterFunc(), destroyPluginFunc);

		}
		else
		{
			std::cout << "Failed to find a function called [DestroyPluginInstance]" << std::endl;
		}
	}
	else
	{
		std::cout << "Failed to find a function called [CreatePluginInstance]" << std::endl;
	}
}
