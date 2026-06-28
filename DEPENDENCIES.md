# Dependencies

ZiggyX uses [Hazel](https://github.com/TheCherno/Hazel) for **architecture**, not for its dependency list.
Confirmed against Hazel's `vendor/` (Box2D, GLFW, Glad, ImGuizmo, entt, filewatch, glm, imgui, mono,
msdf-atlas-gen, spdlog, stb_image, yaml-cpp), the **only** external dependency the two share is **Dear ImGui**.
Everything else is either provided by the Windows SDK or written from scratch. Note also that the public Hazel is a
**2D** engine with no model importer — ZiggyX's 3D model-loading need is a deliberate divergence.

## Management strategy: Git submodules + vendored

No package manager. Dependencies are managed by hand:

- **Submodules** — libraries with their own repos (Dear ImGui, sol2, Lua) live as Git submodules under `ThirdParty/`,
  pinned to a specific commit. Upgrading is deliberate: check out a new tag inside the submodule, then commit the moved pointer.
- **Vendored** — small single-header libraries (nlohmann/json, stb_image) are copied into `ThirdParty/` and committed directly.

Conventions:

- All third-party code lives under `ThirdParty/`.
- Submodules are tracked in `.gitmodules`.
- The `.vcxproj` adds the relevant include paths; compiled submodules (Lua, and later a model importer) are built from source.
- **CI checks out with `submodules: recursive`** so the runner has every dependency.

## Built-in (Windows SDK — no external dependency)

| Dependency | Purpose | Enters at |
|---|---|---|
| Win32 (`User32` / `Gdi32` / `Shell32`) | window creation | already linked |
| Direct3D 11 (`d3d11.lib`, `dxgi.lib`, `d3dcompiler.lib`) | rendering | M1 |
| DirectXMath (`<DirectXMath.h>`) | math — replaces Hazel's glm | M1 |
| WIC (Windows Imaging Component) | image decode — alternative to stb_image | M5 (optional) |

## Custom (written from scratch — no dependency)

Logger (M0) · Physics (M3) · Process Manager + Actor/Component (M4) · Resource cache (M5) · Game AI (M7).
*(These replace Hazel's spdlog, Box2D, and entt respectively.)*

## External (submodule / vendored)

| Dependency | How | Purpose | Enters at |
|---|---|---|---|
| **Dear ImGui** (+ `imgui_impl_win32`, `imgui_impl_dx11`) | submodule | debug / editor UI | M2–M3 |
| **nlohmann/json** | vendored header | actor defs, level/map data, config | M4–M5 |
| **stb_image** | vendored header | texture decode (or use built-in WIC) | M5 |
| **Lua 5.4** | submodule, built from source | scripting VM | M6 |
| **sol2** | submodule (header-only) | C++ ↔ Lua binding | M6 |
| **Assimp _or_ a glTF loader** | deferred decision | 3D model + animation import | **M5** |

### Deferred M5 decision — 3D model loading

3D was chosen for ZiggyX, which (unlike 2D Hazel) requires getting mesh and animation data out of model files:

- **Assimp** — 40+ formats, but a heavy CMake build with its own sub-dependencies. The one painful compiled dependency.
- **Lightweight loader** — a single-format, vendored-header loader (e.g. `cgltf` / `tinygltf`, glTF only).

Neither is needed before M5, so this decision does not influence the near-term setup and is made at that milestone.

## Timeline

Dependencies are added in the milestone where they are first needed, not up front:
**ImGui** at M2–M3 · **nlohmann/json** + **stb_image** at M4–M5 · a model loader at M5 · **Lua** + **sol2** at M6.
