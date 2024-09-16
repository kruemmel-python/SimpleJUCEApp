# SimpleJUCEApp

Ein einfaches JUCE-basiertes GUI-Projekt, das einen Button anzeigt, der beim Klicken eine Nachricht ausgibt. Dieses Projekt verwendet **JUCE** und wird mithilfe von **CMake** und **vcpkg** verwaltet.

## Voraussetzungen

- **Visual Studio 2022** oder neuer
- **CMake** (Version 3.15 oder neuer)
- **vcpkg** als Paketmanager

## Installation

### 1. vcpkg installieren

Zuerst musst du **vcpkg** installieren, wenn du es noch nicht hast. Verwende die folgenden Befehle, um vcpkg auf deinem System zu installieren:

```bash
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat  # Für Windows
```

### 2. JUCE über vcpkg installieren

Verwende **vcpkg**, um **JUCE** zu installieren:

```bash
vcpkg install juce
```

Stelle sicher, dass die **vcpkg**-Integration für Visual Studio eingerichtet ist:

```bash
vcpkg integrate install
```

### 3. Umgebungsvariable für vcpkg setzen

Setze die **VCPKG_ROOT**-Umgebungsvariable, um sicherzustellen, dass CMake die richtige Toolchain-Datei verwenden kann:

```bash
set VCPKG_ROOT=C:\Pfad\zu\vcpkg
```

### 4. CMake-Konfiguration

Erstelle einen neuen Ordner `build` im Projektverzeichnis:

```bash
mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=%VCPKG_ROOT%/scripts/buildsystems/vcpkg.cmake ..
```

### 5. Visual Studio-Projekt öffnen

Sobald die CMake-Konfiguration abgeschlossen ist, kannst du das generierte **Visual Studio**-Projekt öffnen:

```bash
cmake --open .
```

### 6. Subsystem auf "Windowed" umstellen

Damit das Projekt als GUI-Anwendung ausgeführt wird, musst du das **Subsystem** auf **Windowed** umstellen:

1. Rechtsklick auf das Projekt **SimpleJUCEApp** im **Projektmappen-Explorer** in Visual Studio.
2. Wähle **Eigenschaften**.
3. Gehe zu **Linker -> System** und stelle das **Subsystem** auf **Windows (/SUBSYSTEM:WINDOWS)**.

### 7. Projekt erstellen und ausführen

Baue das Projekt:

```bash
cmake --build .
```

Starte das Projekt direkt in Visual Studio, indem du **F5** drückst oder im Menü **Debug -> Start Debugging** auswählst.

## Projektdateien

### CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.15)

# Setze den Projektnamen und die Version
project(SimpleJUCEApp VERSION 1.0.0)

if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    # Setzt das Toolchain-File von Vcpkg, das für die Verwaltung von Abhängigkeiten erforderlich ist.
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()

# JUCE verwenden
find_package(JUCE CONFIG REQUIRED)

# Füge die Hauptanwendung hinzu
add_executable(SimpleJUCEApp Main.cpp)

# Binde JUCE-Bibliotheken ein
target_link_libraries(SimpleJUCEApp PRIVATE juce::juce_gui_basics juce::juce_core)
```

### main.cpp

```cpp
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_core/juce_core.h>

class MainComponent : public juce::Component
{
public:
    MainComponent()
    {
        // Erstelle einen Button
        button.setButtonText("Klicke mich!");
        button.onClick = [this] { buttonClicked(); };

        // Füge den Button zur Hauptkomponente hinzu
        addAndMakeVisible(button);

        // Setze die Größe des Fensters
        setSize(400, 300);
    }

    // Methode, die aufgerufen wird, wenn der Button geklickt wird
    void buttonClicked()
    {
        juce::AlertWindow::showMessageBoxAsync(juce::AlertWindow::InfoIcon,
            "Button Klick",
            "Du hast den Button geklickt!");
    }

    void resized() override
    {
        // Positioniere den Button in der Mitte des Fensters
        button.setBounds(150, 100, 100, 40);
    }

private:
    juce::TextButton button;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};

class MainWindow : public juce::DocumentWindow
{
public:
    MainWindow() : DocumentWindow("JUCE App",
        juce::Colours::lightgrey,
        DocumentWindow::allButtons)
    {
        setUsingNativeTitleBar(true);
        setContentOwned(new MainComponent(), true);

        centreWithSize(400, 300);
        setVisible(true);
    }

    void closeButtonPressed() override
    {
        // Schließe die Anwendung
        juce::JUCEApplication::getInstance()->systemRequestedQuit();
    }
};

class SimpleJuceApp : public juce::JUCEApplication
{
public:
    const juce::String getApplicationName() override { return "Einfache JUCE-App"; }
    const juce::String getApplicationVersion() override { return "1.0"; }

    void initialise(const juce::String&) override
    {
        // Starte das Hauptfenster
        mainWindow.reset(new MainWindow());
    }

    void shutdown() override
    {
        // Schließe das Hauptfenster
        mainWindow = nullptr;
    }

private:
    std::unique_ptr<MainWindow> mainWindow;
};

// Erstelle die JUCE-Anwendung
START_JUCE_APPLICATION(SimpleJuceApp)
```
