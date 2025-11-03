# MW3 UnlockAll

Contains a Windows DLL that manipulates the memory addresses of a specific process to enable the ‘Unlock All’ function in Modern Warfare III. This can be used to unlock all items in MW3.

## Features

- Unlocks all content or features in the targeted application.
- Demonstrates memory manipulation and DLL injection techniques.

## Compilation and Usage

- Download the project to your computer.

- Open the Project with Visual Studio.

- Compile DLL

- Make sure the Windows SDK is installed.

- Inject the DLL:

  - Use a DLL injector tool to load the compiled DLL into the target application's process.

- Observe Behaviour:
  - After a successful injection, all content in the application should be unlocked.

## How It Works

The DLL leverages Windows API functions to:

1. Obtain the module base address of the target application.
2. Modify specific memory locations with prepared assembly instructions.
3. Replace in-memory instructions to achieve the "Unlock All" behavior.

### Example

```cpp
void UnlockAll()
{
    uintptr_t module = (uintptr_t)GetModuleHandleA(0);
    uintptr_t cleanup_instr = module + 0x2B07ACD;
    uintptr_t to_swap = module + 0xBEA9610;
    ...
    MessageBoxA(NULL, "Successfully Inject!", "Message", MB_OK | MB_ICONINFORMATION);
}
```

## 🔧 Technical Details

### Important Functions

- **`UnlockAll`**: Executes memory modifications.
  - Fetches base address of the application.
  - Injects a custom shellcode to unlock features.
- **`DllMain`**: Entry point for the DLL, executed on process attachment.

### Assembly Code

The injected assembly (`shell`) modifies key memory areas to alter program behavior. Key components:

- Adjusts stack pointer (`Add RSP, 8`).
- Moves specific addresses into registers for further operations.

```asm
0x48, 0x83, 0xC4, 0x08, // Add RSP, 8
0x48, 0xB8, ...         // Mov RAX, (dynamic address)
0xE9, ...               // Jmp (dynamic address)
```

## Contribution

This repository is open for contributions! To Contribute:

1. Fork the repository.
2. Leave a star on the repository.

## ⚠️ Disclaimer & Legal Notice

This project is intended for **educational purposes only**:

- Do not use this code to target applications without authorization.
- Misuse of this code may lead to legal consequences.
- The author takes no responsibility for damages caused by improper usage of this software.

## License

This project is licensed under the [MIT License](LICENSE). By using this code, you agree to the terms of this license.
