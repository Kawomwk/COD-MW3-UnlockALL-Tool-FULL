#include "pch.h"
#include <cstdint>
#include <Windows.h>
void UnlockAll()
{
    uintptr_t module = (uintptr_t)GetModuleHandleA(0);
    uintptr_t cleanup_instr = module + 0x2B07ACD; //FF 50 08 84 C0 0F 84 ? ? ? ? 85 FF 0F 84 - add 5 resolve Jz
    uintptr_t to_swap = module + 0xBEA9610; //48 8D 15 ? ? ? ? 48 89 54 24 ? 8B D3 C4 61 FB 2C C0 - resolve lea 

    unsigned char shell[] = {
        0x48, 0x83, 0xC4, 0x08,               // Add RSP, 8
        0x48, 0xB8, 0x00, 0x00, 0x00, 0x00,   // Mov RAX, 0
        0x00, 0x00, 0x00, 0x00,               // (RAX placeholder)
        0xE9, 0x00, 0x00, 0x00, 0x00,         // Jmp (RAX placeholder)
        0x01                                  // Placeholder for the final byte
    };

    *(__int64*)(shell + 6) = to_swap - 0x87;
    *(int*)(shell + 15) = cleanup_instr - to_swap + 0x83;
    memcpy((void*)(to_swap - 0x96), shell, sizeof(shell));
    *(__int64*)(to_swap + 8) = to_swap - 0x96;
    *(__int64*)to_swap = to_swap;

    MessageBoxA(NULL, "Successfully Inject!", "Discord.gg/A-E", MB_OK | MB_ICONINFORMATION);
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        UnlockAll();
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}