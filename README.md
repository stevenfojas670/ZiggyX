# ZiggyX

[![CI](https://github.com/stevenfojas670/ZiggyX/actions/workflows/ci.yml/badge.svg)](https://github.com/stevenfojas670/ZiggyX/actions/workflows/ci.yml)

**ZiggyX** is a Windows-only game engine written in C++20, built as a learning project. It pairs the engine
architecture of [Hazel](https://github.com/TheCherno/Hazel) with the higher-level game systems of
*Game Coding Complete, 4th Edition*.

- **Windowing:** Win32 API
- **Rendering:** DirectX 11
- **Physics:** custom
- **Logging:** custom
- **Platform:** Windows only

> ⚠️ This project recently moved **away from OpenGL/GLEW/GLFW**. Rendering is now DirectX 11 and windowing is Win32 —
> no GLFW/GLEW setup is required.

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

## Repository layout

```
ZiggyX/
├── ZiggyX/
│   ├── src/                     # Engine + entry-point source
│   │   └── ZiggyX/
│   │       ├── Core/            # Platform-independent core (Base, Log, Application, ...)
│   │       └── Events/          # Event system
│   ├── ZiggyX.vcxproj           # MSBuild project
│   └── ZiggyX.vcxproj.filters
├── ThirdParty/                  # Dependencies (submodules / vendored) — added per milestone
├── ZiggyX.slnx                  # Solution
├── ROADMAP.md                   # Milestones M0–M7 and dates
└── DEPENDENCIES.md              # Dependency strategy
```

## Status & roadmap

ZiggyX is in early development. The plan runs from **M0 (Foundations & CI/CD)** through **M7 (Game AI)** — see
[`ROADMAP.md`](ROADMAP.md) for the full milestone breakdown and target dates, and [`DEPENDENCIES.md`](DEPENDENCIES.md)
for how third-party libraries are managed.

## Contributing

Issues are organized by milestone. Use the issue templates (bug / feature / task) when filing, and the
pull-request template when opening a PR. CI builds every push and PR against `main` and `dev`.
