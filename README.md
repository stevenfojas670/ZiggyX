# ZiggyX

**ZiggyX** is a Windows-only game engine written in C++20, built as a learning project. It pairs the engine
architecture of [Hazel](https://github.com/TheCherno/Hazel) with the higher-level game systems of
*Game Coding Complete, 4th Edition*.

- **Windowing:** SDL3
- **Rendering:** custom with DirectX 11
- **Physics:** custom
- **Logging:** custom
- **Platform:** Windows only

## Building

**Requirements:** Windows 10/11, Visual Studio 2022 (with the *Desktop development with C++* workload and the
Windows 10 SDK).

1. Clone the repository (with submodules, as dependencies are added in later milestones):
   ```sh
   git clone --recursive https://github.com/stevenfojas670/ZiggyX.git
   ```
   If you already cloned without `--recursive`:
   ```sh
   git submodule update --init --recursive
   ```
2. Open `ZiggyX.slnx` in Visual Studio 2022.
3. Select the **Debug | x64** configuration and build (Ctrl+Shift+B), then run (F5).
