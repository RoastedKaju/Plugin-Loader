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

}
