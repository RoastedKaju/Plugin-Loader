#include <Windows.h>
#include <iostream>

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		std::cout << "DLL process attached" << std::endl;
		break;

	case DLL_PROCESS_DETACH:
		std::cout << "DLL process detached" << std::endl;
		break;
	default:
		break;
	}

	return TRUE;
}

/// <summary>
/// Same as the interface in our Loader project
/// </summary>
class IPlugin
{
public:
	virtual void DoSomething() = 0;
	virtual ~IPlugin() = default;
};

class Plugin : public IPlugin
{
public:
	// Just a test function for non-interface call
	void init();

	virtual void DoSomething() override;

};

// Only regular free functions can be exported due to C++'s name mangling
extern "C" __declspec(dllexport) void InitPlugin();

// We should export a factory method so we can return a pointer and keep it alive longer
extern "C" __declspec(dllexport) IPlugin* CreatePluginInstance();

// Due to ABI compatibility we cannot directly use smart pointers in our exported factory.
// Unique pointer cannot be copied, so returning it across DLL boundry is not clean solution
// For shared pointer both DLL and and host has to agree on control block implementation which can vary compiler to compiler
// The best solution is to return raw and wrap the result in a smart pointer in host application


// You can also provide a exposed deleter for the instance you created of plugin
extern "C" __declspec(dllexport) void DestroyPluginInstance(IPlugin* plugin);

