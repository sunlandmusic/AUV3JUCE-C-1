# PIANO XL - JUCE Implementation Specifications

## Development Request
Create a JUCE/C++ AUv3 plugin UI that implements the PIANO XL interface, adapting the mobile app specifications for a plugin context. The implementation requires two main files:
- PluginEditor.h
- PluginEditor.cpp

The UI should maintain the exact dimensions, colors, and layout specified below, adapted for landscape orientation.

## Core UI Elements Specifications

### 1. Piano Keys Layout
- **Total Keys**: 12 keys (7 white, 5 black)
- **Key Dimensions**:
  - Width: 72px
  - Height: 130px
  - Border Radius: 15px
  - Border Width: 2px (when in scale)
  - Border Color: #FF9500 (when in scale)

#### White Keys (C, D, E, F, G, A, B)
- Background Color: #4A4A4A
- Text Color: #FFFFFF
- Position: Bottom aligned in piano space
- Border: 2px solid #FF9500

#### Black Keys (C#, D#, F#, G#, A#)
- Background Color: #000000
- Border Color: #4A4A4A
- Text Color: #FFFFFF
- Position: Top aligned in piano space

### 2. Text Display on Keys
- Position: 20px from bottom of key
- Horizontal Alignment: Centered
- Font Properties:
  - Dynamic Font Sizing:
    - 1-5 characters: 28px
    - 6-7 characters: 24px
    - 8-9 characters: 20px
    - 10+ characters: 16px
  - Font Weight: 400
  - Color: #FFFFFF

### 3. Control Buttons

#### XL Button
- Position: Left side of interface
- Dimensions:
  - Width: 78px
  - Height: 47px
  - Border Radius: 15px
- Border:
  - Width: 1px
  - Color: rgba(255, 255, 255, 0.15)
- Background: rgba(0, 0, 0, 0.5)
- Text Properties:
  - Font Size: 18.4px
  - Color: #FFFFFF
  - Font Weight: 400
  - Text: "XL"

#### Plus/Minus Buttons
- Position: Right side of interface
- Height: 4x standard height
- Style matching XL button

### 4. Global UI Properties
- Background Color: Black (#000000)
- Interface Orientation: Landscape
- Component Spacing: Maintain proportional spacing between elements

## Implementation Notes
1. All dimensions should be scaled proportionally based on the plugin window size
2. Maintain exact color values as specified
3. Ensure proper JUCE component hierarchy
4. Implement proper event handling for all interactive elements
5. Use JUCE's graphics context for custom drawing where needed
6. Ensure proper text rendering and scaling
7. Maintain responsive layout that adapts to plugin window size changes 