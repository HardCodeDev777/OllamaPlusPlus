#define OLLAMA_INTERNAL_USE_ONLY

#include "OllamaPlusPlus.h"
#include <windows.h>
#include <iostream>

InitNative Init;
PromptNative Prompt;
FreeNative Free;
HMODULE hLib;

void InitOllama(const char* path, const char* modelName) {
	try {
		hLib = LoadLibraryA(path);
		if (!hLib) {
			std::cerr << "[Ollama][Error] Failed to load OllamaNET.dll from: " << path << std::endl;
			return;
		}
		Init = (InitNative)GetProcAddress(hLib, "InitOllama");
		Prompt = (PromptNative)GetProcAddress(hLib, "PromptOllama");
		Free = (FreeNative)GetProcAddress(hLib, "FreeOllama");
		if (!Init || !Prompt || !Free) {
			std::cerr << "[Ollama][Error] Failed to locate exported functions in DLL." << std::endl;
			FreeLibrary(hLib);
			return;
		}
		Init(modelName);
	}
	catch (std::exception& ex) {
		std::cerr << "[Ollama][Exception] Initialization failed:  " << ex.what() << std::endl;
	}
}

const char* PromptOllama(const char* prompt) {
	try {
		const char* response = Prompt(prompt);
		if (response == nullptr)
		{
			std::cerr << "[Ollama][Error] Received null response from Ollama." << std::endl;
			return nullptr;
		}
		return response;
	}
	catch (std::exception& ex) {
		std::cerr << "[Ollama][Exception] Prompting failed: " << ex.what() << std::endl;
	}
}

void FreeOllama(const char* response) {
	try {
		Free((void*)response);
		if (hLib) 
		{ 
			FreeLibrary(hLib); 
			hLib = nullptr;
			Init = nullptr;
			Prompt = nullptr;
			Free = nullptr;
		}
	}
	catch (std::exception& ex) {
		std::cerr << "[Ollama][Exception] Cleanup failed: " << ex.what() << std::endl;
	}
}