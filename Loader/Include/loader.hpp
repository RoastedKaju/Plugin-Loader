#pragma once

#include <string>
#include <memory>

class Loader
{
public:
	static void LoadPlugin(const std::string& filePath);
};