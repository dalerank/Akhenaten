import Cocoa
import Foundation
import AppKit
import CoreText
import CryptoKit

extension Substring {
    func intValue(forKey key: String) -> Int? {
        let prefix = key + "="
        if self.hasPrefix(prefix) {
            return Int(self.dropFirst(prefix.count))
        }
        return nil
    }
}

class ViewController: NSViewController {
    
    @IBOutlet weak var startButton: NSButton!
    @IBOutlet weak var updatesButton: NSButton!
    @IBOutlet weak var visitButton: NSButton!
    @IBOutlet weak var installButton: NSButton!
    
    @IBOutlet weak var linkLabel: NSTextField!
    
    @IBOutlet weak var install_soundpatch_button: NSButton!
    @IBOutlet weak var already_installed: NSTextField!
    
    @IBOutlet weak var settings_tab: NSTabViewItem!
    
    @IBOutlet weak var language_selector: NSPopUpButton!
    
    @IBOutlet weak var window_mode: NSButton!
    
    @IBOutlet weak var screen_scaling: NSPopUpButton!
    @IBOutlet weak var cursor_scaling: NSPopUpButton!
    @IBOutlet weak var window_width: NSTextField!
    @IBOutlet weak var window_height: NSTextField!
    
    @IBOutlet weak var game_font: NSPopUpButton!
    
    
    var configWindowMode: Int = 1
    var configWindowWidth: Int = 800
    var configWindowHeight: Int = 600
    var configDisplayScale: Int = 100
    var configCursorScale: Int = 100
    var overlayView: NSView?
    
    let scriptPath = Bundle.main.path(forResource: "/innoextract/innoextract", ofType: "command")!
    
    override func viewDidAppear() {
        super.viewDidAppear()
        
        // Nichts fokussieren
        self.view.window?.makeFirstResponder(nil)
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        isGOGinstalled()
        
        let urlString = "https://www.gog.com/de/game/pharaoh_cleopatra"
        let displayText = NSLocalizedString("Buy on GOG", comment: "")
        
        let attributed = NSMutableAttributedString(string: displayText)
        attributed.addAttribute(.link, value: urlString, range: NSRange(location: 0, length: displayText.count))
        
        linkLabel.allowsEditingTextAttributes = true
        linkLabel.isSelectable = true
        linkLabel.attributedStringValue = attributed
        
        // Spracheinträge erstellen
        language_selector.removeAllItems()
        
        language_selector.addItem(withTitle: NSLocalizedString("Install Sound Files", comment: ""))
        language_selector.item(at: 0)?.tag = 0
        
        language_selector.addItem(
            withTitle: "🇩🇪 " + NSLocalizedString("German", comment: "")
        )
        language_selector.item(at: 1)?.tag = 1
        
        language_selector.addItem(
            withTitle: "🇫🇷 " + NSLocalizedString("French", comment: "")
        )
        language_selector.item(at: 2)?.tag = 2
        
        language_selector.addItem(
            withTitle: "🇪🇸 " + NSLocalizedString("Spanish", comment: "")
        )
        language_selector.item(at: 3)?.tag = 3
        
        language_selector.addItem(
            withTitle: "🇵🇱 " + NSLocalizedString("Polish", comment: "")
        )
        language_selector.item(at: 4)?.tag = 4
        
        language_selector.addItem(
            withTitle: "🇮🇹 " + NSLocalizedString("Italian", comment: "")
        )
        language_selector.item(at: 5)?.tag = 5
        
        language_selector.addItem(
            withTitle: "🇷🇺 " + NSLocalizedString("Russian", comment: "")
        )
        language_selector.item(at: 6)?.tag = 6
        
        language_selector.addItem(
            withTitle: "🇺🇸 " + NSLocalizedString("English", comment: "")
        )
        language_selector.item(at: 7)?.tag = 7
        
        language_selector.addItem(
            withTitle: "🇹🇭 " + NSLocalizedString("Thai (Missions only)", comment: "")
        )
        language_selector.item(at: 8)?.tag = 8
        
        updateInstallButtonState()
        
        // ZUERST PopUps befüllen
        screen_scaling.removeAllItems()
        for value in stride(from: 100, through: 200, by: 10) {
            let title = "\(value)%"
            screen_scaling.addItem(withTitle: title)
            screen_scaling.item(withTitle: title)?.tag = value
        }
        
        cursor_scaling.removeAllItems()
        for value in stride(from: 100, through: 200, by: 10) {
            let title = "\(value)%"
            cursor_scaling.addItem(withTitle: title)
            cursor_scaling.item(withTitle: title)?.tag = value
        }
        
        // DANN Config laden und anwenden
        loadConfig()
        applyConfigToUI()
        
        registerCustomFonts()
        setupGameFontPopup()
        
        updateInstalledSoundpatchLabel()
        
        let enabled = (configWindowMode == 1)
        
        window_width.isEnabled  = enabled
        window_height.isEnabled = enabled
        
        window_width.focusRingType = .none
        window_height.focusRingType = .none
        
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
        dialog.allowedFileTypes = ["exe"]
        dialog.allowsMultipleSelection = false
        dialog.canChooseDirectories = false
        
        dialog.begin { [weak self] response in
            guard response == .OK, let url = dialog.url else { return }
            UserDefaults.standard.set(url.path, forKey: "GOGInstaller")
            
            // Overlay im Main Thread anzeigen
            DispatchQueue.main.async {
                self?.showOverlay()
            }
            
            // Hintergrundtask starten
            DispatchQueue.global(qos: .userInitiated).async {
                // syncShellExec muss den Main Thread blockieren **nur für UI-Freigaben** vermeiden
                self?.syncShellExec(path: self?.scriptPath ?? "", args: ["gog_install"])
                
                // Overlay wieder ausblenden im Main Thread
                DispatchQueue.main.async {
                    self?.hideOverlay()
                    self?.isGOGinstalled()
                }
            }
        }
    }
    
    func isGOGinstalled() {
        let fileURL = FileManager.default
            .homeDirectoryForCurrentUser
            .appendingPathComponent("Library/Application Support/akhenaten/eventmsg.txt")
        
        if FileManager.default.fileExists(atPath: fileURL.path) {
            startButton.isEnabled = true
            language_selector.isEnabled = true
            window_mode.isEnabled = true
            screen_scaling.isEnabled = true
            cursor_scaling.isEnabled = true
            window_width.isEnabled = true
            window_height.isEnabled = true
        } else {
            startButton.isEnabled = false
            language_selector.isEnabled = false
            window_mode.isEnabled = false
            screen_scaling.isEnabled = false
            cursor_scaling.isEnabled = false
            window_width.isEnabled = false
            window_height.isEnabled = false
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
    
    /// MARK: Sound Patch
    @IBAction func install_soundpatch(_ sender: Any) {
        guard let selectedTag = language_selector.selectedItem?.tag else {
            showError("No language selected.")
            return
        }
        
        switch selectedTag {
            
        case 1:
            installLanguagePack(
                urlString: "https://www.sl-soft.de/extern/software/akhenaten/pharaoh_german.7z",
                archiveName: "pharaoh_german.7z"
            )
            
        case 2:
            installLanguagePack(
                urlString: "https://www.sl-soft.de/extern/software/akhenaten/pharaoh_french.7z",
                archiveName: "pharaoh_french.7z"
            )
            
        case 3:
            installLanguagePack(
                urlString: "https://www.sl-soft.de/extern/software/akhenaten/pharaoh_spanish.7z",
                archiveName: "pharaoh_spanish.7z"
            )
            
        case 4:
            installLanguagePack(
                urlString: "https://www.sl-soft.de/extern/software/akhenaten/pharaoh_polish.7z",
                archiveName: "pharaoh_polish.7z"
            )
            
        case 5:
            installLanguagePack(
                urlString: "https://www.sl-soft.de/extern/software/akhenaten/pharaoh_italian.7z",
                archiveName: "pharaoh_italian.7z"
            )
            
        case 6:
            installLanguagePack(
                urlString: "https://www.sl-soft.de/extern/software/akhenaten/pharaoh_russian.7z",
                archiveName: "pharaoh_russian.7z"
            )
        
        case 7:
            installLanguagePack(
                urlString: "https://www.sl-soft.de/extern/software/akhenaten/pharaoh_english.7z",
                archiveName: "pharaoh_english.7z"
            )
            
        case 8:
            installLanguagePack(
                urlString: "https://www.sl-soft.de/extern/software/akhenaten/pharaoh_thai.7z",
                archiveName: "pharaoh_thai.7z"
            )
            
        default:
            showError("Invalid language selection.")
        }
    }
    
    @IBAction func languageChanged(_ sender: Any) {
        updateInstallButtonState()
    }
    
    private func installLanguagePack(urlString: String, archiveName: String) {
        DispatchQueue.main.async { [weak self] in
            self?.showOverlay()
        }
        
        DispatchQueue.global(qos: .userInitiated).async {
            guard let url = URL(string: urlString) else {
                DispatchQueue.main.async { [weak self] in
                    self?.hideOverlay()
                    self?.showError("Invalid URL")
                }
                return
            }
            
            let fm = FileManager.default
            let supportPath = fm.homeDirectoryForCurrentUser
                .appendingPathComponent("Library/Application Support/akhenaten")
            let tempArchive = supportPath.appendingPathComponent(archiveName)
            
            try? fm.createDirectory(at: supportPath, withIntermediateDirectories: true)
            
            // 1) Download
            let curlResult = self.runTask(
                "/usr/bin/curl",
                arguments: ["-L", "-o", tempArchive.path, url.absoluteString]
            )
            
            if curlResult != 0 {
                DispatchQueue.main.async { [weak self] in
                    self?.hideOverlay()
                    self?.showError("Download failed")
                }
                return
            }
            
            // 2) 7z Pfad
            guard let bundle7z = Bundle.main.path(forResource: "bin/7z", ofType: nil) else {
                DispatchQueue.main.async { [weak self] in
                    self?.hideOverlay()
                    self?.showError("7z not found in bundle")
                }
                return
            }
            
            chmod(bundle7z, mode_t(0o755))
            
            // 3) Entpacken
            let unzipResult = self.runTask(
                bundle7z,
                arguments: ["x", tempArchive.path, "-y", "-o\(supportPath.path)"]
            )
            
            if unzipResult != 0 {
                DispatchQueue.main.async { [weak self] in
                    self?.hideOverlay()
                    self?.showError("Unpacking failed")
                }
                return
            }
            
            try? fm.removeItem(at: tempArchive)
            
            DispatchQueue.main.async { [weak self] in
                self?.hideOverlay()
                self?.updateInstalledSoundpatchLabel()
            }
        }
    }
    
    func updateInstallButtonState() {
        let selectedTag = language_selector.selectedItem?.tag ?? 0
        
        if selectedTag == 0 {
            install_soundpatch_button.isEnabled = false
        } else {
            install_soundpatch_button.isEnabled = true
        }
    }
    
    /// MARK: Settings
    @IBAction func window_mode(_ sender: Any) {
        let enabled = (window_mode.state == .on)
        configWindowMode = (window_mode.state == .on) ? 1 : 0
        window_width.isEnabled  = enabled
        window_height.isEnabled = enabled
        saveConfig()
    }
    
    @IBAction func window_width_changed(_ sender: Any) {
        if let val = Int(window_width.stringValue) {
            configWindowWidth = val
            saveConfig()
        }
    }
    
    
    @IBAction func window_height_changed(_ sender: Any) {
        if let val = Int(window_height.stringValue) {
            configWindowHeight = val
            saveConfig()
        }
    }
    
    @IBAction func screen_scaling(_ sender: Any) {
        configDisplayScale = screen_scaling.selectedItem?.tag ?? 100
        saveConfig()
    }
    
    @IBAction func cursor_scaling(_ sender: Any) {
        configCursorScale = cursor_scaling.selectedItem?.tag ?? 100
        saveConfig()
    }
    
    struct AkhenatenConfig {
        var window_mode: Int = 1
        var display_scale_percentage: Int = 100
        var cursor_scale_percentage: Int = 100
    }
    
    /// MARK: Config
    func configURL() -> URL {
        let home = FileManager.default.homeDirectoryForCurrentUser
        return home
            .appendingPathComponent(".config/akhenaten/akhenaten.cfg")
    }
    
    func loadConfig() {
        let configURL = FileManager.default
            .homeDirectoryForCurrentUser
            .appendingPathComponent(".config/akhenaten/akhenaten.cfg")
        
        guard let content = try? String(contentsOf: configURL) else {
            print("⚠️ Keine Config gefunden – Standardwerte bleiben aktiv.")
            return
        }
        
        for line in content.split(separator: "\n") {
            if let val = line.intValue(forKey: "window_mode") {
                configWindowMode = val
            }
            if let val = line.intValue(forKey: "window_width") {
                configWindowWidth = val
            }
            if let val = line.intValue(forKey: "window_height") {
                configWindowHeight = val
            }
            if let val = line.intValue(forKey: "display_scale_percentage") {
                configDisplayScale = val
            }
            if let val = line.intValue(forKey: "cursor_scale_percentage") {
                configCursorScale = val
            }
        }
    }
    
    func saveConfig() {
        let configURL = FileManager.default
            .homeDirectoryForCurrentUser
            .appendingPathComponent(".config/akhenaten/akhenaten.cfg")
        
        guard var lines = try? String(contentsOf: configURL)
            .split(separator: "\n")
            .map(String.init) else
        {
            print("❌ Config konnte nicht gelesen werden")
            return
        }
        
        func replace(_ key: String, _ value: Int) {
            let full = "\(key)=\(value)"
            if let index = lines.firstIndex(where: { $0.hasPrefix(key + "=") }) {
                lines[index] = full
            } else {
                lines.append(full)   // Falls der Key früher nicht existierte
            }
        }
        
        replace("window_mode", configWindowMode)
        replace("window_width", configWindowWidth)
        replace("window_height", configWindowHeight)
        replace("display_scale_percentage", configDisplayScale)
        replace("cursor_scale_percentage", configCursorScale)
        
        let newContent = lines.joined(separator: "\n")
        
        do {
            try newContent.write(to: configURL, atomically: true, encoding: .utf8)
        } catch {
            print("❌ Fehler beim Schreiben der Config: \(error)")
        }
    }
    
    func applyConfigToUI() {
        window_mode.state = configWindowMode == 1 ? .on : .off
        window_width.stringValue = "\(configWindowWidth)"
        window_height.stringValue = "\(configWindowHeight)"
        
        // Screen scaling
        if screen_scaling.indexOfItem(withTag: configDisplayScale) != -1 {
            screen_scaling.selectItem(withTag: configDisplayScale)
        } else {
            screen_scaling.selectItem(withTag: 100)
        }
        
        // Cursor scaling
        if cursor_scaling.indexOfItem(withTag: configCursorScale) != -1 {
            cursor_scaling.selectItem(withTag: configCursorScale)
        } else {
            cursor_scaling.selectItem(withTag: 100)
        }
    }
    
    /// MARK: Buy Pharaoh
    @IBAction func buy_pharaoh(_ sender: Any) {
        if let url = URL(string: "https://www.gog.com/de/game/pharaoh_cleopatra") {
            NSWorkspace.shared.open(url)
        }
    }
    
    /// MARK: Overlay
    func showOverlay() {
        guard overlayView == nil, let window = self.view.window else { return }
        
        let overlay = NSView(frame: window.contentView!.bounds)
        overlay.wantsLayer = true
        overlay.layer?.backgroundColor = NSColor.black.withAlphaComponent(0.8).cgColor
        
        // Spinner hinzufügen
        let spinner = NSProgressIndicator()
        spinner.style = .spinning
        spinner.controlSize = .regular
        spinner.startAnimation(nil)
        spinner.translatesAutoresizingMaskIntoConstraints = false
        overlay.addSubview(spinner)
        
        NSLayoutConstraint.activate([
            spinner.centerXAnchor.constraint(equalTo: overlay.centerXAnchor),
            spinner.centerYAnchor.constraint(equalTo: overlay.centerYAnchor)
        ])
        
        window.contentView?.addSubview(overlay)
        overlay.autoresizingMask = [.width, .height]
        overlayView = overlay
    }
    
    func hideOverlay() {
        overlayView?.removeFromSuperview()
        overlayView = nil
    }

    func registerCustomFonts() {
        // Alle TTFs im Subfolder "fonts" holen
        let urls = Bundle.main.urls(forResourcesWithExtension: "ttf",
                                    subdirectory: "fonts") ?? []

        for url in urls {
            CTFontManagerRegisterFontsForURL(url as CFURL, .process, nil)
        }
    }

    func setupGameFontPopup() {
        game_font.removeAllItems()
        let fontNames = ["STIX Two Text Regular", "STIX Two Text Medium", "STIX Two Text Bold"]

        for name in fontNames {
            game_font.addItem(withTitle: name)
            if let item = game_font.lastItem,
               let font = NSFont(name: name, size: 17) {
                let attr = NSAttributedString(string: name,
                                              attributes: [.font: font])
                item.attributedTitle = attr
            }
        }
    }
    
    func updateInstalledSoundpatchLabel() {
        let fm = FileManager.default
        let home = fm.homeDirectoryForCurrentUser
        let fileURL = home
            .appendingPathComponent("Library/Application Support/akhenaten/AUDIO/Voice/Mission/200_mission_classic.mp3")

        // SHA1 -> Flaggen-Emoji
        let hashToFlag: [String: String] = [
            "7f97701612bd31d436047d58ffb396971a849aa7": "🇺🇸",
            "76fb6ac52aec51fb270a0e596095e01bcc0351c8": "🇷🇺",
            "a04b6a370f20fac7161c272a7134a2fdebcaf474": "🇩🇪",
            "819e4fe1f7ff84eec60db93dac11bce72658f61a": "🇫🇷",
            "371c0ca3d78d8efa8bd6db00523d862a593b1872": "🇵🇱",
            "c9798ccdcf3a44fc35de7802e28758b9ea50843c": "🇮🇹",
            "c92e5c2e48c40909a721993f1e1cfeee1ca683f9": "🇹🇭",
            "4bbae939a12a71ec8d87dc62a47d3c8e1ea883c3": "🇪🇸"
        ]

        guard let data = try? Data(contentsOf: fileURL) else {
            already_installed.stringValue = ""
            return
        }

        let digest = Insecure.SHA1.hash( data: data)
        let hex = digest.map { String(format: "%02x", $0) }.joined()

        if let flag = hashToFlag[hex] {
            already_installed.stringValue = flag
        } else {
            already_installed.stringValue = ""
        }
    }

    @IBAction func quitApp(_ sender: Any) {
        NSApp.terminate(nil)
    }
    
    @discardableResult
    private func runTask(_ launchPath: String, arguments: [String]) -> Int32 {
        let task = Process()
        task.launchPath = launchPath
        task.arguments = arguments
        
        let pipe = Pipe()
        task.standardOutput = pipe
        task.standardError  = pipe
        
        do {
            try task.run()
            task.waitUntilExit()
            return task.terminationStatus
        } catch {
            return -1
        }
    }
    
    func syncShellExec(path: String, args: [String] = []) {
        // **Kein makeFirstResponder im Hintergrund**
        let process = Process()
        process.launchPath = "/bin/bash"
        process.arguments = [path] + args
        let pipe = Pipe()
        process.standardOutput = pipe
        process.standardError  = pipe
        
        do {
            try process.run()
            process.waitUntilExit()
        } catch {
            print("❌ Fehler beim Ausführen von \(path): \(error)")
        }
    }
}
