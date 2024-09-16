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

        // F¸ge den Button zur Hauptkomponente hinzu
        addAndMakeVisible(button);

        // Setze die Grˆﬂe des Fensters
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
        // Schlieﬂe die Anwendung
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
        // Schlieﬂe das Hauptfenster
        mainWindow = nullptr;
    }

private:
    std::unique_ptr<MainWindow> mainWindow;
};

// Erstelle die JUCE-Anwendung
START_JUCE_APPLICATION(SimpleJuceApp)
