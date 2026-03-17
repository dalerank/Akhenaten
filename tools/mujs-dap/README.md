# MuJS Debugger for VSCode

Debugs JavaScript running inside Akhenaten's embedded MuJS engine.

## Install (from source, no vsix)

Since VSCode 1.72, copying a folder into `.vscode\extensions` is not enough — the extension must be registered via the command palette.

**1.** In VSCode: `Ctrl+Shift+P` → **Developer: Install Extension from Location...**

**2.** Choose the folder: `C:\work\Akhenaten\tools\mujs-dap` (or your repo path to this extension).

**3.** Reload the window when prompted, or `Ctrl+Shift+P` → **Developer: Reload Window**.

**4.** Check: `Ctrl+Shift+X` → search **mujs** → "MuJS Debugger" should appear. You can edit files in `tools\mujs-dap` and Reload Window to pick up changes.

## Usage

1. Start Akhenaten
2. Open the in-game console and type: `js_debugger start`
3. In VSCode, open `C:\work\Akhenaten`
4. Set a breakpoint in any `.js` file under `src/scripts/`
5. Press **F5** → select **"Attach to Akhenaten JS"**

## Commands (in-game console)

| Command | Description |
|---------|-------------|
| `js_debugger start` | Start DAP server on port 4711 |
| `js_debugger start 9229` | Start on custom port |
| `js_debugger stop` | Stop server, resume if paused |
| `js_debugger status` | Show current state |
| `js_debugger verbose` | Log every JS line (for diagnosis) |
| `js_debugger verbose off` | Stop verbose logging |

## Uninstall

Extensions → find "MuJS Debugger" → Uninstall. If you installed from location, the folder `tools\mujs-dap` is left as-is; only the registration is removed.
