![Ollama](https://img.shields.io/badge/Ollama-%23000000?logo=Ollama)
![C++](https://img.shields.io/badge/C%2B%2B-%2300599C?logo=C%2B%2B)
![C#](https://img.shields.io/badge/C%23-%23512BD4?logo=.NET)
![License](https://img.shields.io/github/license/HardCodeDev777/OllamaPlusPlus?color=%2305991d)
![Last commit](https://img.shields.io/github/last-commit/HardCodeDev777/OllamaPlusPlus?color=%2305991d)
![Tag](https://img.shields.io/github/v/tag/HardCodeDev777/OllamaPlusPlus)
![Top lang](https://img.shields.io/github/languages/top/HardCodeDev777/OllamaPlusPlus)


# 🦙 OllamaPlusPlus

Listed in [Ollama Community Projects](https://github.com/ollama/ollama#community-projects)

&nbsp;

## 👀 Introduction

Most of the time, C++ libraries are written to be used in C#.  
But have you ever seen a **C#-written library for C++** — that even talks to LLM models via [Ollama](https://ollama.com)?

If not — congratulations! You've just found one.

**OllamaPlusPlus** is a lightweight, very simple way to use Ollama from C++, powered by C# and a native bridge.

---

## 🚀 Overview

**OllamaPlusPlus** is a lightweight and incredibly simple library for using [Ollama](https://ollama.com) from C++.  
The low-level communication with Ollama is implemented in C#, while the native bridge is written in C++.

This means you can talk to LLM models from C++ using just a few lines of code:

```cpp
#include "OllamaPlusPlus.h"

InitOllama("OllamaNET.dll", "deepseek-r1:7b");

auto response = PromptOllama("When was GitHub created?");

std::cout << response;

FreeOllama(response);
```

> [!NOTE]  
> The base logic for communicating with Ollama is written in C#, taking into account the needs of a C++ interface. The C++ part acts as a native bridge. If you ever want to modify the internals — either on the C# or C++ side — you'll only need basic knowledge of both. In total, the entire library is just around 120 lines of code across both languages.

It works with any model downloaded via the [Ollama CLI](https://ollama.com/library).

---

## 🚀 Quick start

> **Requirement:** [Download and install Ollama](https://ollama.com) first.

1. Download the latest `.zip` archive from the **Releases** page  
2. Extract it in your C++ project  
3. Open Demo.cpp to see example of usage

---

## 📋 API

OllamaPlusPlus is a very simple C++ library, so it contains only three methods to communicate with Ollama. Here you see what you can do with this library:

- [Initialize Ollama](#initialize-ollama)
- [Send prompt to Ollama](#prompt-ollama)
- [Free memory from Ollama's response](#free-ollama)

### Initialize Ollama

To initialize Ollama and load OllamaNET.dll library, use the `InitOllama()` method:

```cpp
InitOllama("OllamaNET.dll", "deepseek-r1:7b");
```

This method has signature:

```cpp
void InitOllama(const char* path, const char* modelName);
```

#### Parameters:
- `path` – Path to the `OllamaNET.dll`
- `modelName` – Name of the model you want to use

> [!NOTE]  
> If `OllamaNET.dll` is in the same folder as your `.cpp` file, you can just write `"OllamaNET.dll"`. Otherwise, specify the full path like: `"C:\Users\YourName\Desktop\OllamaNET.dll"`

### Prompt Ollama
To send a prompt to the model and receive a response, use the `PromptOllama()` method.

```cpp
auto response = PromptOllama("When was GitHub created?");
```

This method has signature:

```cpp
const char* PromptOllama(const char* prompt);
```

#### Parameters:
- `prompt` – The prompt to send to the model

**It returns the LLM response.**

### Free Ollama
To free the allocated memory and unload the library, use the `FreeOllama()` method.

```cpp
FreeOllama(response);
```

This method has signature:

```cpp
void FreeOllama(const char* response);
```

#### Parameters:
- `response` – The response returned by `PromptOllama()`

---

## 📄 License

This project is licensed under the **MIT License**.  
See LICENSE for full terms.

---

## 👨‍💻 Author

**HardCodeDev**  
- [GitHub](https://github.com/HardCodeDev777)  
- [Itch.io](https://hardcodedev.itch.io/)

---

> 💬 Got feedback, found a bug, or want to contribute? Open an issue or fork the repo on GitHub!
