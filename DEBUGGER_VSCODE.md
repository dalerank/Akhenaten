# Debugging embedded JavaScript (mujs) in Visual Studio Code

In Akhenaten, gameplay logic written in **JavaScript** runs inside the embedded **mujs** VM. A **Debug Adapter Protocol (DAP)** server can run alongside the game: **Visual Studio Code** (or **Cursor**) attaches to it, you set breakpoints in `.js` files, and you can inspect locals and the call stack.

This debugger does **not** replace the native C++ debugger (Visual Studio): it only observes **mujs script** execution.

---

## Prerequisites

- A build with debug symbols is optional but useful (**RelWithDebInfo** or **Debug**) for clearer traces; the DAP server itself does not require special CMake flags.
- Script sources on disk: **`--mixed`** is the most convenient way to edit files under `src/scripts/` (or unpacked scripts) and reload the VM without rebuilding the binary.
- A **debugger extension or configuration** that can attach to a **`mujs`** adapter over TCP (see below). After `js_debugger start`, the game prints a hint like: *attach VSCode on localhost:4711 (type: mujs)*.

---

## Starting the debug server from the game

1. Launch Akhenaten and load a scene where JS runs (menu, city, etc.).
2. Open the **in-game console** (same as for other console commands in the project).
3. Run:

```text
js_debugger start
```

The default listen port is **4711**. To use another port:

```text
js_debugger start 9000
```

Useful commands:

| Command | Action |
|--------|--------|
| `js_debugger status` | Show whether the server is running and on which port |
| `js_debugger stop` | Stop the server (if the game was paused in the debugger, execution resumes) |
| `js_debugger verbose on` | Log **every** JS line change (use when breakpoints never hit) |
| `js_debugger verbose off` | Disable the per-line trace |

Until a client (VS Code) connects, the game runs normally. After you connect, when execution stops on a breakpoint, the **thread running mujs blocks** until you continue from the IDE (**Continue**, **Step**, etc.).

---

## Attaching from Visual Studio Code

### 1. Open the right folder

Open the **Akhenaten repository root** in VS Code (or the folder that contains the same `.js` files the game loads with `--mixed`) so file paths match what the engine reports when breaking.

### 2. Attach configuration

Create or edit `.vscode/launch.json`. You need **`"request": "attach"`**, **`localhost`**, the **same port** as in `js_debugger start` (often **4711**), and whatever `type` your DAP client expects (the game log says **type: mujs**).

Template (property names may differ by extension—check its README):

```json
{
  "version": "0.2.0",
  "configurations": [
    {
      "name": "Attach: Akhenaten mujs",
      "type": "mujs",
      "request": "attach",
      "address": "localhost",
      "port": 4711
    }
  ]
}
```

3. Ensure the server is already running (`js_debugger start`).
4. In **Run and Debug**, pick this configuration and press **Start Debugging** (attach).

The same flow works in **Cursor** with `launch.json`.

---

## Breakpoints

- Set breakpoints in **`.js` files`** that actually execute (including those loaded via `import` / disk when using `--mixed`).
- Stops occur on **source line** changes (the hook is tied to `OP_LINE` in mujs). Very dense code without line breaks can make “file line ↔ debugger line” mapping less obvious.
- If a breakpoint never hits:
  - Check that the path the IDE uses matches what the VM sees (absolute paths, same drive and casing on Windows).
  - Turn on **`js_debugger verbose on`** and inspect logs to see whether execution reaches the expected file and line.

---

## Debugger UI

### Variables (Locals / Global)

- **Local** — for mujs **lightweight** functions, parameters and `var` locals come from **stack slots**, not only from the lexical `with`/global environment listing.
- **Global** — the global environment object.

For **objects**, the list includes **own** properties and properties inherited from the **prototype** (values are resolved via `getproperty`; accessors may run when you expand nodes, like in ordinary JS).

### Expressions (Watch / Debug Console)

Evaluation is **limited**: only **simple identifiers** (a single variable name, no dots or calls). Expressions like `obj.prop` or `foo()` may not work—use **Locals** and expand objects instead.

### Call Stack

Frames come from mujs’s internal trace (function name, file, line). Depth and names depend on how scripts are compiled.

### Stepping

- **Continue** — run until the next breakpoint or end of the current stretch of work.
- **Step Over** — stop on the next line in the current function (subject to `js_debugger.cpp` step logic).
- **Step In** — step into a call (as implemented by the adapter).
- **Step Out** — leave the current function.

Exact behavior depends on `tracetop` and `DebugStepMode` in the engine.

---

## Limitations and caveats

- **Hover evaluate** is not supported (`supportsEvaluateForHovers: false` in the `initialize` response).
- After **hot reload** of scripts, VM state changes; restart `js_debugger` and reconnect if things look wrong.
- If the debugger hangs or the connection drops, **`js_debugger stop`** releases the server; if the game thread seems stuck, restarting the game is the most reliable fix.

---

## Implementation reference

- DAP server, commands, and limits: `src/js/js_debugger.cpp`, `src/js/js_debugger.h`
- Console commands: `js_debugger` in `src/js/js.cpp`
- Line hook: JS execution path in `js.cpp` (`g_mujs_debugger.update_state` / `on_line`)

---

## Quick checklist

1. Run the game → `js_debugger start` → optionally `verbose on` to diagnose path/line issues.
2. In VS Code, open the repo, configure **Attach** to `localhost:4711` with type **mujs**.
3. Set a breakpoint in the right `.js` and wait for it to hit.
4. Inspect **Locals** / **Global**; use Watch only for simple names.
5. End the session: **Disconnect** in the IDE and optionally `js_debugger stop` in the game.
