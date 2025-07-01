/*
  ==============================================================================

    MainComponent.h
    Created: Date
    Author:  Your Name

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PianoKeyComponent.h"
#include "TitleComponent.h"
#include "VerticalFaderComponent.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    //==============================================================================
    // Your private member variables go here...

    // Define base dimensions and aspect ratio
    const float baseWidth = 844.0f;
    const float baseHeight = 390.0f;
    const float aspectRatio = baseWidth / baseHeight;

    // Define min/max constraints for the content area
    const int minWidth = 844;
    const int minHeight = static_cast<int>(minWidth / aspectRatio); // approx 390
    const int maxWidth = static_cast<int>(390.0f * aspectRatio); // approx 844 if height is capped
    const int maxHeight = 390;

    juce::Rectangle<int> contentBounds;

    // Test Piano Key
    // PianoKeyComponent testKey; // Will be replaced by arrays of keys

    // Other UI Elements
    TitleComponent titleComponent;
    VerticalFaderComponent verticalFader;

    // Piano Keys
    std::vector<std::unique_ptr<PianoKeyComponent>> whiteKeys;
    std::vector<std::unique_ptr<PianoKeyComponent>> blackKeys;

    // Key names (using "Db" for "C#" etc. for easier processing if needed, but display can be "#")
    const juce::String whiteKeyNotes[7] = {"C", "D", "E", "F", "G", "A", "B"};
    // Using nullptrs for spacing in black key array based on PianoXL.tsx structure
    const juce::String blackKeyNotes[6] = {"C#", "D#", "", "F#", "G#", "A#"}; // "" for placeholder

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
