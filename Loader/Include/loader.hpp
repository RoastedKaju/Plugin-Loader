#pragma once

#include <string>
#include <memory>

/// <summary>
/// This interface should be known in both DLL and Loader
/// This is how we would interact with the pointer we get from DLL
/// </summary>
class IPlugin
{
public:
	virtual void DoSomething() = 0;
	virtual ~IPlugin() = default;
};

class Loader
{
public:
	static void LoadPlugin(const std::string& filePath);
};