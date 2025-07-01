/*
  ==============================================================================

    MainComponent.cpp
    Created: Date
    Author:  Your Name

  ==============================================================================
*/

#include "MainComponent.h"
#include <iostream> // For std::cout

//==============================================================================
MainComponent::MainComponent()
{
    // Set an initial size for the component itself.
    setSize (baseWidth, baseHeight);

    // Initialize White Keys
    for (int i = 0; i < 7; ++i)
    {
        // Default to "C" key in scale for now for visual testing, others not in scale
        bool isInScale = (whiteKeyNotes[i] == "C" || whiteKeyNotes[i] == "E" || whiteKeyNotes[i] == "G");
        whiteKeys.push_back(std::make_unique<PianoKeyComponent>(whiteKeyNotes[i], false, isInScale));
        addAndMakeVisible(*whiteKeys.back());
    }

    // Initialize Black Keys
    // Black keys should be added after white keys so they are drawn on top by default.
    int blackKeyInstanceIndex = 0;
    for (int i = 0; i < 6; ++i) // 6 potential positions in blackKeyNotes array
    {
        if (!blackKeyNotes[i].isEmpty()) // Skip placeholders
        {
            // Default to "F#" key in scale for now
            bool isInScale = (blackKeyNotes[i] == "F#");
            blackKeys.push_back(std::make_unique<PianoKeyComponent>(blackKeyNotes[i], true, isInScale));
            addAndMakeVisible(*blackKeys.back());
            blackKeyInstanceIndex++;
        }
    }

    addAndMakeVisible(titleComponent);
    addAndMakeVisible(verticalFader);

    // Add basic interactions (lambdas for simplicity)
    for (auto& key : whiteKeys)
    {
        key->onClick = [this, name = key->getButtonText()] {
            std::cout << "White key " << name << " clicked." << std::endl;
            // Potentially update some state here, e.g., lastClickedKey = name;
        };
    }

    for (auto& key : blackKeys)
    {
        key->onClick = [this, name = key->getButtonText()] {
            std::cout << "Black key " << name << " clicked." << std::endl;
        };
    }

    verticalFader.onValueChange = [this] {
        std::cout << "Fader value: " << verticalFader.getValue() << std::endl;
    };

    titleComponent.getXlButton().onClick = [this] {
        // Cycle through XL, XXL, XXXL or similar logic
        juce::String currentText = titleComponent.getXlButton().getButtonText();
        if (currentText == "XL") titleComponent.getXlButton().setButtonText("XXL");
        else if (currentText == "XXL") titleComponent.getXlButton().setButtonText("XXXL");
        else titleComponent.getXlButton().setButtonText("XL");
        std::cout << "XL Button clicked. New mode: " << titleComponent.getXlButton().getButtonText() << std::endl;
        // This should trigger a re-layout or change in how keys are displayed/handled if XXL/XXXL were implemented.
        // For now, it just changes the button text.
    };
}

MainComponent::~MainComponent()
{
    // Smart pointers handle deletion of PianoKeyComponent objects
    // LookAndFeel for titleComponent.xlButton is cleaned up in TitleComponent destructor
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    // For debugging, draw a border around the contentBounds and pianoArea
    // g.setColour (juce::Colours::red);
    // g.drawRect (contentBounds, 2);
    // if (getWidth() > 0 && getHeight() > 0) { // only if resized has run
    //    float scaleFactor = contentBounds.getWidth() / baseWidth;
    //    float pianoContainerOrigX = -134.0f;
    //    float pianoContainerOrigY = 78.0f;
    //    juce::Point<float> pianoAreaTopLeft(contentBounds.getX() + (pianoContainerOrigX * scaleFactor),
    //                                        contentBounds.getY() + (pianoContainerOrigY * scaleFactor));
    //    g.setColour(juce::Colours::blue);
    //    // Approximate piano area bounds for debug
    //    g.drawRect(pianoAreaTopLeft.x, pianoAreaTopLeft.y, 800 * scaleFactor, 200 * scaleFactor);
    // }
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // We need to calculate the bounds for our content area, respecting aspect ratio and constraints.

    float currentWidthPx = getWidth();
    float currentHeightPx = getHeight();

    float targetWidthForCurrentHeight = currentHeightPx * aspectRatio;
    float targetHeightForCurrentWidth = currentWidthPx / aspectRatio;

    float newContentWidth = 0;
    float newContentHeight = 0;

    // Determine the dominant dimension for scaling
    if (currentWidthPx / currentHeightPx > aspectRatio)
    {
        newContentHeight = currentHeightPx;
        newContentWidth = newContentHeight * aspectRatio;
    }
    else
    {
        newContentWidth = currentWidthPx;
        newContentHeight = newContentWidth / aspectRatio;
    }

    // Apply min/max constraints
    if (newContentWidth < minWidth)
    {
        newContentWidth = minWidth;
        newContentHeight = minWidth / aspectRatio;
    }
    // Ensure minHeight is also respected if it's proportionally larger than what minWidth implies
    if (newContentHeight < minHeight && minHeight > 0)
    {
        newContentHeight = minHeight;
        newContentWidth = newContentHeight * aspectRatio;
    }

    if (newContentHeight > maxHeight)
    {
        newContentHeight = maxHeight;
        newContentWidth = newContentHeight * aspectRatio;
    }
    // Ensure maxWidth is also respected
    if (newContentWidth > maxWidth && maxWidth > 0)
    {
        newContentWidth = maxWidth;
        newContentHeight = newContentWidth / aspectRatio;
    }

    int contentX = (currentWidthPx - newContentWidth) / 2;
    int contentY = (currentHeightPx - newContentHeight) / 2;
    contentBounds.setBounds(contentX, contentY, static_cast<int>(newContentWidth), static_cast<int>(newContentHeight));

    float scaleFactor = contentBounds.getWidth() / baseWidth;

    // Piano Container Offset (from PianoXL.tsx: transform: [{ translateX: -134 }, { translateY: 78 }])
    float pianoContainerOrigX = -134.0f;
    float pianoContainerOrigY = 78.0f;
    juce::Point<float> pianoAreaTopLeft(contentBounds.getX() + (pianoContainerOrigX * scaleFactor),
                                        contentBounds.getY() + (pianoContainerOrigY * scaleFactor));

    // --- White Keys Layout ---
    // styles.whiteKey: width: 72, height: 129, marginHorizontal: 13.5
    // styles.whiteKeysRow: paddingHorizontal: 20, transform: [{ translateY: 10 }]
    float whiteKeyOrigWidth = 72.0f;
    float whiteKeyOrigHeight = 129.0f;
    float whiteKeyOrigMarginH = 13.5f;
    float whiteKeysRowPaddingH = 20.0f; // This padding is for the row container
    float whiteKeysRowTranslateY = 10.0f; // This translation is for the row container

    float scaledKeyWidth = whiteKeyOrigWidth * scaleFactor;
    float scaledKeyHeight = whiteKeyOrigHeight * scaleFactor;
    float scaledMarginH = whiteKeyOrigMarginH * scaleFactor;

    // The first key's left edge starts after the row's padding and its own left margin.
    float currentWhiteKeyX = pianoAreaTopLeft.getX() + (whiteKeysRowPaddingH * scaleFactor);
    float whiteKeysY = pianoAreaTopLeft.getY() + (whiteKeysRowTranslateY * scaleFactor);

    for (size_t i = 0; i < whiteKeys.size(); ++i)
    {
        whiteKeys[i]->setBounds(static_cast<int>(currentWhiteKeyX + scaledMarginH),
                                static_cast<int>(whiteKeysY),
                                static_cast<int>(scaledKeyWidth),
                                static_cast<int>(scaledKeyHeight));
        // Advance X by key width + both margins (left and right)
        currentWhiteKeyX += scaledKeyWidth + (scaledMarginH * 2.0f);
    }

    // --- Black Keys Layout ---
    // styles.blackKey: width: 72, height: 129, marginHorizontal: 13.5
    // styles.blackKeyPlaceholder: width: 99 (this seems to be key_width + 2*margin)
    // styles.blackKeysRow: position: 'absolute', top: -128, left: -3 (relative to pianoContainer)

    float blackKeyOrigWidth = 72.0f;
    float blackKeyOrigHeight = 129.0f;
    float blackKeyOrigMarginH = 13.5f; // Margin for actual black keys
    float blackKeyPlaceholderOrigWidth = 99.0f; // This is (72 + 2*13.5)

    float blackKeysRowOrigTop = -128.0f;
    float blackKeysRowOrigLeft = -3.0f; // Fine-tuning adjustment for the row

    float scaledBlackKeyWidth = blackKeyOrigWidth * scaleFactor;
    float scaledBlackKeyHeight = blackKeyOrigHeight * scaleFactor;
    float scaledBlackKeyMarginH = blackKeyOrigMarginH * scaleFactor;
    float scaledBlackKeyPlaceholderWidth = blackKeyPlaceholderOrigWidth * scaleFactor;

    // The black keys row also seems to respect an initial padding similar to white keys row for alignment.
    // The `left: -3` is an additional offset.
    float blackKeysCurrentX = pianoAreaTopLeft.getX() + (whiteKeysRowPaddingH * scaleFactor) + (blackKeysRowOrigLeft * scaleFactor);
    float blackKeysY = pianoAreaTopLeft.getY() + (whiteKeysRowTranslateY * scaleFactor) + (blackKeysRowOrigTop * scaleFactor);

    int blackKeyInstanceIdx = 0; // To index into the actual blackKeys vector
    for (const auto& noteName : blackKeyNotes) // Iterate through the definition array
    {
        if (!noteName.isEmpty()) // It's an actual key
        {
            if (blackKeyInstanceIdx < blackKeys.size())
            {
                // Black key is placed with its margin
                blackKeys[blackKeyInstanceIdx]->setBounds(static_cast<int>(blackKeysCurrentX + scaledBlackKeyMarginH),
                                                         static_cast<int>(blackKeysY),
                                                         static_cast<int>(scaledBlackKeyWidth),
                                                         static_cast<int>(scaledBlackKeyHeight));
                // Advance X by key width + both margins
                blackKeysCurrentX += scaledBlackKeyWidth + (scaledBlackKeyMarginH * 2.0f);
                blackKeyInstanceIdx++;
            }
        }
        else // It's a placeholder
        {
            // Advance X by the placeholder width. Placeholder width already includes effective margins.
            blackKeysCurrentX += scaledBlackKeyPlaceholderWidth;
        }
    }

    // --- Title Component Layout ---
    float titleOrigX = -211.0f; // Relative to pianoAreaTopLeft
    float titleOrigY = -50.0f;
    float titleScaledX = titleOrigX * scaleFactor;
    float titleScaledY = titleOrigY * scaleFactor;
    float unrotatedTitleWidth = titleComponent.getOriginalUnrotatedWidth() * scaleFactor;
    float unrotatedTitleHeight = titleComponent.getOriginalUnrotatedHeight() * scaleFactor;

    float finalTitleBoxTopLeftX = pianoAreaTopLeft.getX() + titleScaledX;
    float finalTitleBoxTopLeftY = pianoAreaTopLeft.getY() + titleScaledY;

    // After -90deg rotation, component's original width becomes height, and height becomes width.
    float rotatedTitleBoundingBoxWidth = unrotatedTitleHeight;
    float rotatedTitleBoundingBoxHeight = unrotatedTitleWidth;

    // Calculate the center of the final rotated bounding box
    float finalTitleBoxCenterX = finalTitleBoxTopLeftX + rotatedTitleBoundingBoxWidth / 2.0f;
    float finalTitleBoxCenterY = finalTitleBoxTopLeftY + rotatedTitleBoundingBoxHeight / 2.0f;

    // Position the unrotated component so its center aligns with the target center
    titleComponent.setBounds(static_cast<int>(finalTitleBoxCenterX - unrotatedTitleWidth / 2.0f),
                             static_cast<int>(finalTitleBoxCenterY - unrotatedTitleHeight / 2.0f),
                             static_cast<int>(unrotatedTitleWidth),
                             static_cast<int>(unrotatedTitleHeight));

    titleComponent.setTransform(juce::AffineTransform::rotation(-juce::MathConstants<float>::halfPi,
                                                                  unrotatedTitleWidth / 2.0f, // Rotate around its local center X
                                                                  unrotatedTitleHeight / 2.0f // Rotate around its local center Y
                                                                  ));

    // --- Vertical Fader Layout ---
    // faderWrapper: right: -112, top: 13 (relative to A# black key's parent container/row)
    // height: 92.65, width: 30 (wrapper). Fader is 20px wide.
    // The `blackKeysRow` has `top: -128`, `left: -3`.
    // The fader's `top: 13` is relative to this blackKeysRow's Y.
    // The fader's `right: -112` is relative to the blackKeysRow's right edge.
    // The blackKeysRow's content width is the sum of its children widths.
    // `blackKeysCurrentX` at the end of the loop is the right edge of the black keys content area,
    // relative to `pianoAreaTopLeft.getX() + (whiteKeysRowPaddingH * scaleFactor) + (blackKeysRowOrigLeft * scaleFactor)`.
    // So, actual right edge of black keys content area:
    float blackKeyContentAreaStartX = pianoAreaTopLeft.getX() + (whiteKeysRowPaddingH * scaleFactor) + (blackKeysRowOrigLeft * scaleFactor);
    float blackKeyContentAreaRightAbsolute = blackKeysCurrentX; // This already includes the start X and all key/placeholder widths

    float faderOrigHeight = 92.65f;
    float faderOrigWidth = 20.0f; // The actual slider width
    float faderWrapperOrigWidth = 30.0f;
    // float faderWrapperOrigRight = -112.0f; (CSS right property)
    // float faderWrapperOrigTop = 13.0f;

    float faderScaledHeight = faderOrigHeight * scaleFactor;
    float faderScaledWidth = faderOrigWidth * scaleFactor;
    float faderWrapperScaledWidth = faderWrapperOrigWidth * scaleFactor;
    float faderWrapperScaledRightOffset = -112.0f * scaleFactor;
    float faderWrapperScaledTopOffset = 13.0f * scaleFactor;

    // The fader wrapper's right edge is `blackKeyContentAreaRightAbsolute + faderWrapperScaledRightOffset`.
    // The fader wrapper's left edge is then `... - faderWrapperScaledWidth`.
    float faderWrapperLeft = blackKeyContentAreaRightAbsolute + faderWrapperScaledRightOffset - faderWrapperScaledWidth;

    // The fader (20px) is centered within its wrapper (30px).
    float faderActualLeft = faderWrapperLeft + (faderWrapperScaledWidth - faderScaledWidth) / 2.0f;
    float faderActualTop = blackKeysY + faderWrapperScaledTopOffset; // blackKeysY is already the Y for the black key row items

    verticalFader.setBounds(static_cast<int>(faderActualLeft),
                            static_cast<int>(faderActualTop),
                            static_cast<int>(faderScaledWidth),
                            static_cast<int>(faderScaledHeight));
}
