// Source code for the OllamaNET.dll

#nullable disable

using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.AI;
using Microsoft.Extensions.Hosting;
using System.Threading.Tasks;

namespace OllamaNET;

public static class Program
{
    private static IChatClient _chatClient;
    private static List<ChatMessage> _chatHistory = new();

    [UnmanagedCallersOnly(EntryPoint = "InitOllama")]
    public static void InitOllama(IntPtr modelNamePtr)
    {
        var builder = Host.CreateApplicationBuilder();

        var modelName = Marshal.PtrToStringAnsi(modelNamePtr)!;
        builder.Services.AddChatClient(new OllamaChatClient(new Uri("http://localhost:11434"), modelName));

        var app = builder.Build();

        _chatClient = app.Services.GetRequiredService<IChatClient>();
    }


    [UnmanagedCallersOnly(EntryPoint = "PromptOllama")]
    public static IntPtr PromptOllama(IntPtr promptPtr)
    {
        try
        {
            var prompt = Marshal.PtrToStringAnsi(promptPtr)!;

            _chatHistory.Add(new(ChatRole.User, prompt));

            var result = StreamOllamaResponse().GetAwaiter().GetResult();

            _chatHistory.Add(new(ChatRole.Assistant, result));

            return Marshal.StringToHGlobalAnsi(result);
        }
        catch(Exception ex){
            return Marshal.StringToHGlobalAnsi($"Error: {ex}");
        }
    }

    private static async Task<string> StreamOllamaResponse()
    {
        var chatResponse = "";
        await foreach (var item in _chatClient.GetStreamingResponseAsync(_chatHistory)) chatResponse += item.Text;

        return chatResponse;
    }

    [UnmanagedCallersOnly(EntryPoint = "FreeOllama")]
    public static void FreeOllama(IntPtr ptr) => Marshal.FreeHGlobal(ptr);
        
}
