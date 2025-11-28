//
//  ViewController.swift
//  akhenaten
//
//  Created by Prof. Dr. Luigi on 27.11.25.
//

import Cocoa
import Foundation
import AppKit

class ViewController: NSViewController {
    
    @IBOutlet weak var startButton: NSButton!
    @IBOutlet weak var updatesButton: NSButton!
    @IBOutlet weak var visitButton: NSButton!
    @IBOutlet weak var installButton: NSButton!
    @IBOutlet weak var installInfo: NSTextField!
    
    
    let scriptPath = Bundle.main.path(forResource: "/innoextract/innoextract", ofType: "command")!

    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
    }

    override var representedObject: Any? {
        didSet {
        // Update the view, if already loaded.
        }
    }

    @IBAction func startGame(_ sender: Any) {
        // Pfad zum Resource-Ordner
        guard let resourceURL = Bundle.main.resourceURL else {
            print("❌ resourceURL fehlt")
            return
        }

        // Pfad zu Contents/Resources/game
        let gameURL = resourceURL.appendingPathComponent("game")

        // Pfad zu launch.sh
        let scriptURL = gameURL.appendingPathComponent("launch.sh")

        // Prüfen ob vorhanden
        let fm = FileManager.default
        if !fm.fileExists(atPath: scriptURL.path) {
            print("❌ launch.sh nicht gefunden: \(scriptURL.path)")
            return
        }

        // Prüfen ob ausführbar
        if !fm.isExecutableFile(atPath: scriptURL.path) {
            print("⚠️ launch.sh ist nicht ausführbar — versuche chmod einzusetzen")
            do {
                try fm.setAttributes([.posixPermissions: 0o755], ofItemAtPath: scriptURL.path)
            } catch {
                print("❌ launch.sh ist nicht ausführbar und konnte nicht gepatcht werden")
                return
            }
        }

        // Prozess starten
        let task = Process()
        task.executableURL = scriptURL
        task.currentDirectoryURL = gameURL   // wichtig für relative Pfade in launch.sh
        task.arguments = []                  // falls du Argumente brauchst

        do {
            try task.run()
            print("▶️ launch.sh gestartet")
        } catch {
            print("❌ Fehler beim Starten: \(error)")
        }
    }
    
    @IBAction func openProjectPage(_ sender: Any) {
        guard let url = URL(string: "https://github.com/dalerank/Akhenaten") else {
            print("❌ Ungültige URL")
            return
        }

        // Öffnet den Standardbrowser (Safari, Chrome, usw.)
        NSWorkspace.shared.open(url)
    }

    @IBAction func install_gog(_ sender: Any) {
        requestGOGInstaller()
        

        
    }
    
    /// MARK: EXE auswählen
    private func requestGOGInstaller() {
        let dialog = NSOpenPanel()
        dialog.title = NSLocalizedString("SelectInstallerTitle", comment: "")
        dialog.message = NSLocalizedString("SelectInstallerMessage", comment: "")
        dialog.allowedFileTypes = ["exe"]
        dialog.allowsMultipleSelection = false
        dialog.canChooseDirectories = false
        
        dialog.begin { response in
            guard response == .OK, let url = dialog.url else { return }
            
            // Validierung sicherstellen
            guard FileManager.default.fileExists(atPath: url.path) else {
                self.showError(NSLocalizedString("InstallerNotFound", comment: ""))
                return
            }
            
            // Speichern
            UserDefaults.standard.set(url.path, forKey: "GOGInstaller")
            
            self.installInfo.isHidden = false
            self.startButton.isEnabled = false
            self.updatesButton.isEnabled = false
            self.visitButton.isEnabled = false
            self.installButton.isEnabled = false
            
            self.syncShellExec(path: self.scriptPath, args: ["gog_install"])
            
            self.installInfo.isHidden = true
            self.startButton.isEnabled = true
            self.updatesButton.isEnabled = true
            self.visitButton.isEnabled = true
            self.installButton.isEnabled = true
        }
        

    }

    /// MARK: Error Alert
    private func showError(_ message: String) {
        let alert = NSAlert()
        alert.messageText = NSLocalizedString("This is no valid GOG Installer.", comment: "")
        alert.informativeText = message
        alert.alertStyle = .critical
        alert.runModal()
    }
    
    func syncShellExec(path: String, args: [String] = []) {
        if let mainWindow = NSApplication.shared.windows.first {
            mainWindow.makeFirstResponder(nil)
        }
        let process            = Process()
        process.launchPath     = "/bin/bash"
        process.arguments      = [path] + args
        let outputPipe         = Pipe()
        process.standardOutput = outputPipe
        process.launch() // Start process
        process.waitUntilExit() // Wait for process to terminate.
    }
}

