#pragma once

#ifdef OLLAMA_INTERNAL_USE_ONLY
	typedef void(__cdecl* InitNative)(const char*);
	typedef const char* (__cdecl* PromptNative)(const char*);
	typedef void(__cdecl* FreeNative)(void*);
#endif


void InitOllama(const char* path, const char* modelName);
const char* PromptOllama(const char* prompt);
void FreeOllama(const char* response);