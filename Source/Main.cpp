/*
  ==============================================================================

    Main.cpp
    Created: Date
    Author:  Your Name

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
class PianoXLApplication  : public juce::JUCEApplication
{
public:
    //==============================================================================
    PianoXLApplication() {}

    const juce::String getApplicationName() override       { return ProjectInfo::projectName; }
    const juce::String getApplicationVersion() override      { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override             { return true; }

    //==============================================================================
    void initialise (const juce::String& commandLine) override
    {
        // This method is where you should put your application's initialisation code
        mainWindow.reset (new MainWindow (getApplicationName()));
    }

    void shutdown() override
    {
        // Add your application's shutdown code here..
        mainWindow = nullptr; // (deletes our window)
    }

    //==============================================================================
    void systemRequestedQuit() override
    {
        // This is called when the OS tells us to quit.
        quit();
    }

    void anotherInstanceStarted (const juce::String& commandLine) override
    {
        // When another instance of the app is launched while this one is running,
        // this method is called, and the commandLine parameter tells you what
        // the other instance's command-line arguments were.
    }

    //==============================================================================
    /*
        This class implements the desktop window that contains an instance of
        our MainComponent class.
    */
    class MainWindow    : public juce::DocumentWindow
    {
    public:
        MainWindow (juce::String name)
            : DocumentWindow (name,
                              juce::Desktop::getInstance().getDefaultLookAndFeel()
                                                          .findColour (juce::ResizableWindow::backgroundColourId),
                              DocumentWindow::allButtons)
        {
            setUsingNativeTitleBar (true);
            mainComponent = new MainComponent();
            setContentOwned (mainComponent, true);

           #if JUCE_IOS || JUCE_ANDROID
            setFullScreen (true);
           #else
            // Set initial size to 844x390 for desktop
            setResizable (true, true); // User can resize
            centreWithSize (844, 390);
            // MainComponent will enforce aspect ratio and min/max dimensions
           #endif

            setVisible (true);

            // Enforce landscape orientation (conceptual for desktop, more direct on mobile)
            // For desktop, this is more about the content's design.
            // Actual window orientation lock is an OS-level feature not directly controlled by JUCE for desktop.
            // We will ensure our MainComponent's content adheres to landscape proportions.
        }

        void closeButtonPressed() override
        {
            // This is called when the user tries to close this window. Here, we'll just
            // ask the app to quit when this happens, but you can change this to do
            // whatever you need.
            JUCEApplication::getInstance()->systemRequestedQuit();
        }

    private:
        MainComponent* mainComponent; // Keep a raw pointer

        //==============================================================================
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };

private:
    std::unique_ptr<MainWindow> mainWindow;
};

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (PianoXLApplication)
