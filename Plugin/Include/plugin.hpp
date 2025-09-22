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

class Plugin
{
public:
	void init();
};

// Only regular free functions can be exported due to C++'s name mangling
extern "C" __declspec(dllexport) void InitPlugin();

// We should export a factory method so we can return a pointer and keep it alive longer
