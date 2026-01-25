# Summary of Important Changes in Akhenaten Repository for 2025

## Main Development Directions

### Major Architecture Refactoring
- **Transition to Configuration System**
  - Massive migration of logic from C++ to JavaScript configs
  - All buildings and figures are now configured through JS configs
  - Simplified data loading system from archives
  - New scheme for registering enum tokens in JS
  - Unified system for loading structures from configs

- **Refactoring of Building and Figure Classes**
  - Extraction of runtime_data from common building class into specialized classes
  - Migration of planner logic into building classes
  - Simplification of type casting system for buildings and figures
  - Reorganization of figure system with base class extraction

### Enemy and Invasion System
- **New Enemy System**
  - Added enemy figure types (barbarian, hittite, hyksos, kushite, persian, roman, phoenician, nubian, libian, assyrian, seapeople)
  - Battalion system (batalions) instead of legions
  - Improved enemy army formation logic
  - Invasion points system with support for sea and land invasions
  - Enemy properties configuration through configs
  - Enemy strength grid system

- **Combat System**
  - Improved archer logic
  - Distant battle system
  - Debug window for enemy armies
  - City siege event handling

### Localization and Internationalization
- **New Language Support**
  - Added German language support
  - Added Spanish language support
  - Migration of all localizations from C++ to JS configs
  - Improved font system with Unicode support
  - Tools for generating game fonts

- **Localization System Improvements**
  - Loading localizations from .sgx archives
  - Support for external language directories
  - Improved Unicode font rendering

### New Buildings and Functionality
- **New Building Types**
  - Carpenter Guild with carpenter figure
  - Stonemasons Guild with stonemason figure
  - Tower Gatehouse
  - Improved logic for Senet House
  - Restored logic for Carpenter Guild

- **Existing Building Improvements**
  - Irrigation canals system with improved logic
  - Improved logic for Water Lift
  - Garden system with decay logic
  - Improved logic for Temple Complex
  - Mastaba system with static parameters support

### Resource System
- **Resource Depletion System**
  - Implemented depletion system for all quarry types
  - Resource depletion for copper mines
  - Depletion system for gems
  - Save/load resource state (copper, stone, gems grids)

- **Resource Management Improvements**
  - New city_resource_handle class for simplified resource handling
  - Improved resource storage logic in buildings
  - Mission resource configuration through configs

### UI/UX Improvements
- **New Windows and Interfaces**
  - Information window for trade caravans and ships
  - Information window for gatehouse
  - Information window for forts and legions with formation mode buttons
  - Mod manager window
  - Event history window
  - Political overseer window

- **Interface Improvements**
  - Fixed top menu when resizing window
  - Improved scrollbar system
  - Dynamic text support for buttons
  - Improved tooltips for buildings and figures
  - Image centering support in messages
  - Improved mission window

### Rendering System
- **Graphics Improvements**
  - New deferred rendering system with Y-sorting
  - Improved cart rendering
  - Grayscale support for images
  - Cloud system with settings
  - Improved isometric texture rendering
  - Texture caching for performance improvement

### Figure and Animal System
- **New Figure Types**
  - Carpenter figure
  - Stonemason figure
  - Drunkard figure
  - Base class for hyena
  - Improved crocodile logic with citizen pursuit

- **Existing Figure Improvements**
  - Improved logic for ostrich hunter
  - Improved logic for trade ships
  - Standard bearer logic
  - Improved logic for trade caravans

### Mission System
- **New Missions and Improvements**
  - Mission 8 (Selima) with distant battle support
  - Mission 10 (Saqqara)
  - Mission building configuration through configs
  - Mission goals system through configs

### Mod System
- **Mod Support**
  - Ability to download mods from GitHub
  - Save/load active mods
  - Texture loading support from modpacks
  - Improved data loading from .sgx archives
  - Automatic start index detection for images

### Technical Improvements
- **Platform Improvements**
  - Build support for Bazzite Linux
  - Build improvements for macOS (ARM and x86)
  - Build improvements for Android
  - Fixes for Emscripten/WASM
  - System libpng support on macOS

- **Architectural Improvements**
  - New type system (typeid implementation)
  - stable_array class for hash-sorted arrays
  - Improved variants system
  - New events system
  - Improved routing system with amphibian support

- **Game Logic Improvements**
  - Improved population migration system
  - Irrigation system (irrigation value)
  - Improved logic for dentist/physician
  - Weekly building update system

### Empire System
- **Trade and Empire Improvements**
  - Empire system redesign using handles instead of raw numbers
  - Improved trade route logic for long intervals
  - Fixed trader creation in cities
  - Support for creating trade cities under siege

## 🎮 Game Improvements
- Risk system now depends on difficulty and house value
- Improved tutorial system
- Support for multiple temple complexes and monuments (optional)
- New tax collection system (optional)
- Improved labor system

## 🔧 Developer Tools
- Sprite tool for viewing game resources
- Improved debugging tools
- Console commands for creating figures and game management
- Font generation tools
- Debug modes for routing
- Debug rendering for canals, gardens, enemies
