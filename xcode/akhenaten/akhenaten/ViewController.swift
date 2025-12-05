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
    
    @IBOutlet weak var linkLabel: NSTextField!
    
    
    let scriptPath = Bundle.main.path(forResource: "/innoextract/innoextract", ofType: "command")!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        let fileURL = FileManager.default
            .homeDirectoryForCurrentUser
            .appendingPathComponent("Library/Application Support/akhenaten/eventmsg.txt")
        
        if FileManager.default.fileExists(atPath: fileURL.path) {
            startButton.isEnabled = true
        } else {
            startButton.isEnabled = false
        }
        
        let urlString = "https://www.gog.com/de/game/pharaoh_cleopatra"
        let displayText = NSLocalizedString("Buy on GOG", comment: "")
        
        let attributed = NSMutableAttributedString(string: displayText)
        attributed.addAttribute(.link, value: urlString, range: NSRange(location: 0, length: displayText.count))
        
        linkLabel.allowsEditingTextAttributes = true
        linkLabel.isSelectable = true
        linkLabel.attributedStringValue = attributed
        
        self.preferredContentSize = NSMakeSize(self.view.frame.size.width, self.view.frame.size.height)
    }
    
    class ClickableLinkLabel: NSTextField {
        
        private var trackingArea: NSTrackingArea?
        private var url: URL?
        
        override func updateTrackingAreas() {
            super.updateTrackingAreas()
            
            if let trackingArea = trackingArea {
                self.removeTrackingArea(trackingArea)
            }
            
            let area = NSTrackingArea(rect: self.bounds,
                                      options: [.mouseEnteredAndExited, .activeAlways],
                                      owner: self,
                                      userInfo: nil)
            self.addTrackingArea(area)
            self.trackingArea = area
        }
        
        override func mouseEntered(with event: NSEvent) {
            NSCursor.pointingHand.push()
            underline(true)
        }
        
        override func mouseExited(with event: NSEvent) {
            NSCursor.pop()
            underline(false)
        }
        
        override func mouseDown(with event: NSEvent) {
            if let url {
                NSWorkspace.shared.open(url)
            }
        }
        
        func setLink(text: String, url: String) {
            self.isEditable = false
            self.isSelectable = false
            self.allowsEditingTextAttributes = true
            self.drawsBackground = false
            self.isBordered = false
            
            let attr = NSMutableAttributedString(string: text)
            attr.addAttribute(.foregroundColor, value: NSColor.systemBlue, range: NSRange(location: 0, length: text.count))
            attr.addAttribute(.underlineStyle, value: NSUnderlineStyle.single.rawValue, range: NSRange(location: 0, length: text.count))
            self.attributedStringValue = attr
            self.url = URL(string: url)
        }
        
        private func underline(_ active: Bool) {
            guard let attr = self.attributedStringValue.mutableCopy() as? NSMutableAttributedString else { return }
            let style: Int = active ? NSUnderlineStyle.single.rawValue : NSUnderlineStyle.single.rawValue
            attr.addAttribute(.underlineStyle, value: style, range: NSRange(location: 0, length: attr.length))
            self.attributedStringValue = attr
        }
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
    
    @IBAction func buy_pharaoh(_ sender: Any) {
        if let url = URL(string: "https://www.gog.com/de/game/pharaoh_cleopatra") {
            NSWorkspace.shared.open(url)
        }
    }
    
    @IBAction func quitApp(_ sender: Any) {
        NSApp.terminate(nil)
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

