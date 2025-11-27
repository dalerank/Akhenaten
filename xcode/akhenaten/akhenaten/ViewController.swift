//
//  ViewController.swift
//  akhenaten
//
//  Created by Prof. Dr. Luigi on 27.11.25.
//

import Cocoa

class ViewController: NSViewController {

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

}

