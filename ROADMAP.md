# ZiggyX Roadmap

ZiggyX is a **Windows-only** game engine written in C++20, built for learning. It draws on two references:

- **[Hazel](https://github.com/TheCherno/Hazel)** — the low-level engine architecture (Core/Base macros, Events,
  Window abstraction, Input, Renderer, Layer/LayerStack, Application, EntryPoint).
- **Game Coding Complete, 4th Edition** (McShaffry & Graham) — the higher-level game systems (Process Manager,
  Actor/Component model, a Resource cache, Lua scripting, and Game AI).

Rendering is **DirectX 11**, windowing is **Win32**, physics is **custom**. See [`DEPENDENCIES.md`](DEPENDENCIES.md)
for the full dependency strategy.

> **Estimates** assume ~8–12 hrs/week and include a **1.5× realism multiplier** (first-time engine work overruns).
> The later a milestone sits, the wider its real-world error bar.

## Milestones

| Milestone | Scope | Target | Reference |
|---|---|---|---|
| M0 | Foundations & CI/CD | **2026-07-09** | — |
| M1 | Core MVP ⭐ | **2026-08-09** | Hazel |
| M2 | Application & Layers | **2026-08-30** | Hazel |
| M3 | Physics MVP | **2026-09-20** | — |
| M4 | Process Manager & Actor/Component | **2026-10-22** | GCC 4e |
| M5 | Resource Storage & Cache | **2026-12-03** | GCC 4e |
| M6 | Lua Scripting (sol2) | **2027-01-14** | GCC 4e |
| M7 | Game AI | **2027-02-25** | GCC 4e |

**MVP (M1) ≈ early August 2026 · near-term physics (M3) ≈ late September 2026 · full scope (M7) ≈ late February 2027.**

---

### M0 — Foundations & CI/CD · target 2026-07-09
Repo hygiene plus the macro/logging bedrock every later phase depends on.

- `.github/` scaffolding: auto-labeller, PR template, issue templates, MSBuild CI workflow.
- `ROADMAP.md`, a refreshed `README.md`, and `DEPENDENCIES.md`.
- `Core/Base.h` upgrade to Hazel-style primitives: `Scope`/`Ref` + `CreateScope`/`CreateRef`, `BIT(x)`,
  `ZIGGY_BIND_EVENT_FN(fn)`, `ZIGGY_DEBUGBREAK()`, `ZIGGY_CORE_ASSERT`/`ZIGGY_ASSERT`.
- Custom logging system (`Core/Log.{h,cpp}`): core + client loggers, `ZIGGY_CORE_*`/`ZIGGY_*` macros, colored console output.

### M1 — Core MVP ⭐ · target 2026-08-09
A running window, a DirectX-painted shape, a working event system, and input echoed to the console.

- **Events:** bitmask `EventCategory` flags, the template `EventDispatcher`, and concrete `KeyEvent`/`MouseEvent`/`WindowEvent`.
- **Window:** `Core/Window.h` + `Platform/Windows/WindowsWindow` — owns the `HWND`, moves `WndProc` out of `main.cpp`,
  and translates Win32 messages into ZiggyX events via `SetEventCallback`.
- **Input:** `Core/Input.h` static polling backed by Win32, plus `KeyCodes.h`/`MouseCodes.h`.
- **DirectX 11 renderer:** device + swap chain + render-target view, screen clear, and one colored triangle/quad
  through a minimal vertex + pixel shader.
- **Acceptance:** the window runs, a shape is painted by DirectX, and key/mouse input flows through the event system to the console.

### M2 — Application & Layer Architecture · target 2026-08-30
Adopt Hazel's layered application model so menus/UI/game logic become composable layers.

- `Timestep`, `Layer` (`OnAttach`/`OnDetach`/`OnUpdate`/`OnEvent`), and `LayerStack` (layers vs. overlays, reverse-order propagation).
- `Application` (owns Window + LayerStack, runs the main loop, dispatches events) + `EntryPoint.h` with a `CreateApplication()` factory.
- An example `SandboxLayer`. *Stretch:* a simple debug/UI or menu layer.

### M3 — Physics MVP · target 2026-09-20
Input → event system → physics subscribes → console logs simulated movement (no rendering).

- A `PhysicsLayer`/`PhysicsSystem` that receives input events.
- An object with position/velocity advanced each `Timestep`; key input changes velocity.
- **Acceptance:** movement keys log the object's changing position to the console.

### M4 — Process Manager & Actor/Component · target 2026-10-22
The Game Coding Complete backbone; Resources, Scripting, and AI all build on it.

- **Process Manager:** cooperative `Process`/`ProcessManager` (running/paused/succeeded/failed, child chaining) driven from the main loop.
- **Actor/Component model:** an `Actor` as an id + a bag of `ActorComponent`s (Transform/Render/Physics), created from data via an `ActorFactory`.
- Integrate both with the event system (actor lifecycle events, component messages).

### M5 — Resource Storage & Cache · target 2026-12-03
Game Coding Complete's `ResCache` pattern for textures, animation data, and map/level data.

- `IResourceFile` (folder source first), `Resource`/`ResHandle`, and `IResourceLoader` per type.
- Loaders for texture data (→ DirectX), animation data, and map/level data.
- An LRU `ResCache` with a memory budget; the renderer and actors pull assets through the cache.
- **Deferred decision:** 3D model loading via Assimp vs. a lightweight glTF loader (see `DEPENDENCIES.md`).

### M6 — Lua Scripting (sol2) · target 2027-01-14
A scripting layer over the standard Lua VM using **sol2**.

- Embed Lua + sol2; a `ScriptManager`/`LuaStateManager` owning the VM and running scripts (loaded via the resource cache).
- Expose logging, the event system, actor creation, and component access to Lua.
- Script-driven actors so content lives in data, not C++ recompiles.

### M7 — Game AI · target 2027-02-25
Decision-making built on the Process Manager, Actors, and (optionally) Lua.

- A reusable state-machine + decision-tree core, each behavior running as a `Process`.
- A* pathfinding over grid/map data from M5.
- AI actors that subscribe to events and can be authored in Lua; console/visual feedback of decisions.

### Post-MVP / stretch (no date)
Render the physics object with DirectX, networking, a full scene serializer, an in-engine editor/UI, and audio.

---

## Design note — `EventManager` (pub/sub) vs. Hazel layer propagation

Hazel has no event bus: the window fires a callback into `Application::OnEvent`, which walks the `LayerStack` in
reverse; a layer sets `event.Handled` to stop propagation. ZiggyX already scaffolds an `EventManager.h`, and the
physics goal describes systems that *"subscribe to input."* Two viable shapes, to decide at M3:

- **(A) Hazel-style:** `PhysicsLayer::OnEvent` receives events through the layer stack. Less code, matches the reference.
- **(B) Lightweight pub/sub bus:** flesh out `EventManager` so systems `Subscribe(EventType, handler)`. Matches the
  "subscribe" mental model and the existing stub, at the cost of a parallel dispatch path.

Recommendation: build M1/M2 on the Hazel callback path; introduce subscription at M3 only if (A) feels constraining.
