// @ts-check
'use strict';

const vscode = require('vscode');

/**
 * @param {vscode.ExtensionContext} context
 */
function activate(context) {
    console.log('[mujs-debug] extension activated');

    context.subscriptions.push(
        vscode.debug.registerDebugAdapterDescriptorFactory('mujs', {
            /**
             * @param {vscode.DebugSession} session
             * @returns {vscode.DebugAdapterDescriptor}
             */
            createDebugAdapterDescriptor(session) {
                const host = session.configuration.host ?? 'localhost';
                const port = session.configuration.port ?? 4711;

                console.log(`[mujs-debug] DAP will connect to ${host}:${port}`);
                // No probe: let VSCode connect directly. Probe caused a stray connection
                // that closed immediately; the second connection then never sent DAP data.
                return new vscode.DebugAdapterServer(port, host);
            }
        })
    );
}

function deactivate() {}

module.exports = { activate, deactivate };
