
# Quick CPU Patch

A lightweight DLL that removes trial and license restrictions from Quick CPU.

## What It Does

- Bypasses license verification checks
- Removes trial limitations
- Exe stays untouched — patches applied in-memory at runtime

## How It Works

The DLL masquerades as `stlib.dll` and sits alongside `QuickCpu.exe`. On launch it:

1. Forwards all `stlib.dll` API calls to the real system DLL
2. Verifies the host EXE via hash before applying patches
3. Patches 25 memory offsets to force registered state

## Installation

1. Drop stlib.dll (compiled from this source) in the install folder
2. Run `QuickCpu.exe` — that's it

## Notes

- Built for **Quick CPU x64** only. Other builds may not work.
- AV may flag the DLL — false positives are common with in-memory patching tools.
- For educational purposes only.

## Disclaimer

This project is for **educational and research purposes only**. Use at your own risk. The author is not responsible for any misuse or damage.

---

Cracked by **github.com/ofkits1**
