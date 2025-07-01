# PIANO XL

---

**IMPORTANT PLATFORM NOTE**

> **PIANO XL is designed exclusively as a mobile application. The primary and only supported platforms are iPhone and Android devices using Expo Go and React Native. All UI, audio, and interaction specifications are intended for mobile use. There is no web version, and web-specific code or APIs (such as the Web Audio API) should not be used. All implementation must use mobile-native solutions (e.g., expo-av for audio, React Native components for UI).**

## 1. Overview

PIANO XL is a sophisticated music application designed to be a composer's dream tool. At its core, it revolutionizes chord playing by enabling one-touch chord generation—a single press of any key instantly plays a complete chord, eliminating the need for traditional multi-key piano playing. This intuitive approach makes chord progression creation and experimentation remarkably simple and efficient.

### Core Functionality:
1. **One-Touch Chord Generation**
   - Each key press instantly generates a complete chord.
   - No need to press multiple keys simultaneously.
   - Immediate access to complex chord voicings with a single touch.
   - Perfect for quick chord progression building and experimentation.

2. **Diatonic Guidance System**
   - Visual feedback through key highlighting shows which notes belong to the selected scale.
   - Excluded keys become transparent and unplayable, ensuring users stay within the chosen key's harmonic framework.
   - This visual system helps users understand and work within the selected key's diatonic family.

3. **Intelligent Chord Selection**
   - Each playable key offers scrollable chord options that are diatonic to the selected key and mode.
   - Chord selections are automatically filtered to match the current key/mode combination.
   - Users can easily cycle through available chord options directly on the physical key they're pressing.
   - This on-key chord cycling allows for immediate experimentation with different chord types while maintaining the same root note.
   - The system ensures all available chord options are musically appropriate for the current key and mode.

4. **Multiple Operation Modes**
   - XL Mode: Standard 12-chord layout.
   - XXL Mode: 24 chords available (2 per key).
   - XXXL Mode: 36 chords available (3 per key).
   - These modes allow for increased harmonic complexity while maintaining diatonic integrity.

5. **Chord Property Modification**
   - Real-time chord property adjustments for instant sonic exploration.
   - Save and recall chord configurations as "Sets" for quick access to favorite progressions.
   - Import and share custom chord Sets with other users.
   - Access to preset chord Sets (in development) for common progressions and styles.
   - Advanced bass note control for creating slash chords (e.g., C/G, Dm7/A).
   - Chord inversion options for different voicing possibilities.
   - These features allow for sophisticated chord voicing and progression building.

The app's design philosophy focuses on making complex harmonic concepts accessible while providing the tools needed for sophisticated musical composition. By combining one-touch chord generation, visual feedback, intelligent chord filtering, flexible operation modes, and comprehensive chord property modification, PIANO XL helps users create musically coherent progressions with confidence and ease.

---

## 2. List of Buttons/Display

### Piano Keys Area

1. **Piano Keys (12 total)**
   - 7 White Keys (C, D, E, F, G, A, B)
   - 5 Black Keys (C#, D#, F#, G#, A#)
   - Dimensions:
     - Width: 72px
     - Height: 130px
     - Border Radius: 15px
     - Border Width: 2px (when in scale)
     - Border Color: #FF9500 (when in scale)
   - Colors:
     - White Keys: #4A4A4A
     - Black Keys: #000000 with #4A4A4A border
   - Text Properties:
     - Base Font Size: 28px for chord names
     - Dynamic scaling based on chord name length:
       - 1-5 characters: 28px (maximum size)
       - 6-7 characters: 24px
       - 8-9 characters: 20px
       - 10+ characters: 16px (minimum size)
     - Color: #FFFFFF
     - Font Weight: 400
     - Text alignment: Centered
     - Padding: 20px from bottom of key

### Text Positioning on Piano Keys

The chord name or note label is always displayed at the bottom of each piano key. This is achieved by absolutely positioning the text 20px above the bottom edge of the key (`bottom: 20`), and centering it horizontally (`width: 100%`, `textAlign: center`). The key's content container uses `justifyContent: flex-end` and `paddingBottom: 20` to ensure the text remains at the bottom, regardless of key size or screen dimensions.

**Example Implementation:**

```tsx
<View style={[styles.keyContent, styles.xlKeyContent]}>
  <Text style={[
    styles.chordNameText,
    styles.xlChordText,
    isWhite ? styles.whiteKeyText : styles.blackKeyText,
  ]}>
    {chordNames[0]}
  </Text>
</View>
```

```ts
const styles = StyleSheet.create({
  keyContent: {
    width: '100%',
    height: '100%',
    justifyContent: 'center',
    alignItems: 'center',
  },
  xlKeyContent: {
    justifyContent: 'flex-end',
    paddingBottom: 20,
  },
  chordNameText: {
    textAlign: 'center',
    fontSize: 18.4,
    fontWeight: '400',
    paddingHorizontal: 2,
  },
  xlChordText: {
    position: 'absolute',
    bottom: 20,
    width: '100%',
  },
  whiteKeyText: {
    color: '#FFFFFF',
  },
  blackKeyText: {
    color: '#FFFFFF',
  },
});
```

This ensures the text is always visually anchored to the bottom of the key, providing a consistent and clear UI across all devices.

### PIANO Label and XL Mode Button

- The text **"PIANO"** is displayed prominently at the top (or side, in vertical layout) of the interface, serving as a title for the piano area.
- Next to the "PIANO" label is the **"XL" button**. This button displays the current mode ("XL", "XXL", or "XXXL") and allows the user to toggle between these modes by pressing it.
- In some layouts, "PIANO XL" may be displayed vertically on the left side of the screen for stylistic effect.

**Example Implementation:**

```tsx
<View style={styles.titleContainer}>
  <Text style={styles.titleText}>PIANO</Text>
  <Pressable style={styles.xlButton} onPress={handleSizePress}>
    <Text style={styles.xlButtonText}>{sizeText}</Text>
  </Pressable>
</View>
```

- `titleText` style: white, font size 20.4, font weight 300, centered.
- `xlButton` style: 78x47px, border radius 15px, background rgba(0,0,0,0.5), border 1px rgba(255,255,255,0.15).
- `xlButtonText` style: white, font size 18.4, font weight 400.

This ensures that the "PIANO" label and the "XL" mode button are always clearly visible and functionally distinct in the UI.

2. **XL Mode Button**
   - Dimensions:
     - Width: 78px
     - Height: 47px
     - Border Radius: 15px
     - Border Width: 1px
     - Border Color: rgba(255, 255, 255, 0.15)
   - Background: rgba(0, 0, 0, 0.5)
   - Text Properties:
     - Font Size: 18.4px
     - Color: #FFFFFF
     - Font Weight: 400

### Settings Panel Area

1. **Skin Button**
   - Dimensions:
     - Width: 38.7px
     - Height: 38.7px
     - Border Radius: 19.35px
   - Background: rgba(255, 255, 255, 0.2)
   - Icon: ImageIcon (24.2px)
   - Background Skin:
     - Covers the entire application screen
     - Positioned behind all UI elements
     - Semi-transparent dark overlay (rgba(0, 0, 0, 0.5)) applied to the entire background
     - Ensures UI elements remain visible against any background image
     - Maintains consistent contrast for all interactive elements

2. **A/B Memory Buttons**
   - Dimensions:
     - Width: 32px
     - Height: 50px
     - Border Radius: 8px
   - Background: rgba(0, 0, 0, 0.5)
   - Border: 1px rgba(255, 255, 255, 0.15)
   - Text Properties:
     - Font Size: 20px
     - Color: #FFFFFF
     - Font Weight: bold

3. **BASS Button**
   - Dimensions:
     - Width: 64px
     - Height: 64px
     - Border Radius: 15px
   - Background: rgba(0, 0, 0, 0.5)
   - Icon: Bass clef symbol (𝄢) or text showing current offset (e.g., "+1", "-2", "OFF")
   - Position: Top bar, after the A/B buttons and before the Sound Window
   - Visual Feedback:
     - Highlighted when active/selected
     - Shows current bass offset value or bass clef symbol when not selected

4. **Sound Window**
   - Dimensions:
     - Width: 132px
     - Height: 50px
     - Border Radius: 15px
   - Background: rgba(0, 0, 0, 0.5)
   - Border: 1px rgba(255, 255, 255, 0.15)
   - Text Properties:
     - Font Size: 16px
     - Color: #FFFFFF
     - Font Weight: 500
   - Available Sounds:
     - Balafon
     - Piano
     - Rhodes
     - Steel Drum
     - Pluck
     - Pad

5. **Settings Item: KEY**
   - Dimensions:
     - Width: 58px
     - Height: 67px
     - Border Radius: 15px
   - Background: rgba(0, 0, 0, 0.5)
   - Label Properties:
     - Font Size: 13.8px
     - Color: rgba(255, 255, 255, 0.6)
     - Font Weight: 400
   - Value Properties:
     - Font Size: 18.4px
     - Color: #FFFFFF
     - Font Weight: 400

6. **Settings Item: MODE**
   - Dimensions:
     - Width: 102px
     - Height: 67px
     - Border Radius: 15px
   - Background: rgba(0, 0, 0, 0.5)
   - Label Properties:
     - Font Size: 13.8px
     - Color: rgba(255, 255, 255, 0.6)
     - Font Weight: 400
   - Value Properties:
     - Font Size: 18.4px
     - Color: #FFFFFF
     - Font Weight: 400
   - Default: **FREE**
   - Available Modes and Display Names:
     - FREE: "FREE" (no alternate name)
     - MAJOR: "MAJOR" / "IONIAN"
     - MINOR: "MINOR" / "AEOLIAN"
     - MIXOLYDIAN: "MIXO" / "LYDIAN"
     - PHRYGIAN: "PHRYG" / "IAN"
     - DORIAN: "DORIAN" (no alternate name)
     - LOCRIAN: "LOCRIAN" (no alternate name)
   - Display Format:
     - Main name in larger text
     - Alternate name (if available) in smaller text below
     - Both names centered in the button
   - Functions:
     - Press: Select mode for adjustment
     - Long press: Switch to FREE mode while preserving existing chord selections

7. **Settings Item: OCT**
   - Dimensions:
     - Width: 58px
     - Height: 67px
     - Border Radius: 15px
   - Background: rgba(0, 0, 0, 0.5)
   - Label Properties:
     - Font Size: 13.8px
     - Color: rgba(255, 255, 255, 0.6)
     - Font Weight: 400
   - Value Properties:
     - Font Size: 18.4px
     - Color: #FFFFFF
     - Font Weight: 400
   - Functions:
     - Press: Select octave for adjustment
     - Range: -2 to +1
     - Default: 0

8. **Settings Item: INV**
   - Dimensions:
     - Width: 58px
     - Height: 67px
     - Border Radius: 15px
   - Background: rgba(0, 0, 0, 0.5)
   - Label Properties:
     - Font Size: 13.8px
     - Color: rgba(255, 255, 255, 0.6)
     - Font Weight: 400
   - Value Properties:
     - Font Size: 18.4px
     - Color: #FFFFFF
     - Font Weight: 400

9. **Chord Display**
   - Dimensions:
     - Width: 102px
     - Height: 67px
     - Border Radius: 15px
   - Background: rgba(0, 0, 0, 0.5)
   - Label Properties:
     - Font Size: 13.8px
     - Color: rgba(255, 255, 255, 0.6)
     - Font Weight: 400
   - Value Properties:
     - Font Size: Dynamic (28px to 16px based on length)
     - Color: #FFFFFF
     - Font Weight: 400

10. **Plus/Minus Buttons**
   - Dimensions:
     - Width: 42px
     - Height: 42px
     - Border Radius: 15px
   - Background: rgba(0, 0, 0, 0.5)
   - Border: 1px rgba(255, 255, 255, 0.15)
   - Icon Properties:
     - Plus/Minus symbol
     - Color: #FFFFFF
     - Size: 24px
   - Functions:
     - Plus: Increase selected value or cycle through chord types
     - Minus: Decrease selected value or cycle through chord types
   - Behavior:
     - When no settings selected: Cycles through chord types of last played key
     - When a setting is selected: Adjusts the selected setting's value
   - Visual Feedback:
     - Highlighted when active
     - Maintains consistent contrast against background

---

## 3. List of Button/Display Functions

### Piano Keys Area

1. **Piano Keys**
   - Primary Functions:
     - Play chords and bass notes
     - Display chord names
     - Select chords based on Music Mode
     - Support multiple chord types per key in XXL/XXXL modes
   - Touch Behaviors:
     - Press: Play chord and bass
     - Release: Stop sound
     - In XXL/XXXL modes: Vertical position determines which chord to play
   - Chord Type Selection:
     - After pressing a key, use Plus/Minus buttons to cycle through available chord types
     - Only works when no Settings are selected
     - Affects the last played key's chord type
     - Maintains diatonic compatibility with current key/mode

2. **XL Mode Button**
   - Functions:
     - Toggle between XL (12 chords), XXL (24 chords), and XXXL (36 chords) modes
     - Updates key display and functionality accordingly

### Settings Panel Area

1. **Skin Button**
   - Functions:
     - Press: Change app skin/theme
     - Long press: Reset to default skin
     - Controls full-screen background image with overlay

2. **A/B Memory Buttons**
   - Functions:
     - Press: Load saved configuration
     - Long press: Save current configuration
     - Visual feedback when slot is occupied

3. **BASS Button**
   - Functions:
     - Press: Selects/deselects the BASS offset mode for the last played chord
     - When selected, pressing Plus/Minus cycles through the following values:  
       **BASS CLEF (default/root), +1, +2, +3, +4, +5, -6, -5, -4, -3, -2, -1, OFF**
     - The chord name and display update to show the slash chord (e.g., C/C#, C/D, etc.) as the offset changes
     - When BASS is deselected, the altered bass chord remains for that chord/key until BASS is pressed again for that key
     - When BASS is deselected, the button text/icon returns to the bass clef symbol (𝄢)
     - When BASS is deselected, it does not alter any other piano key or chord

4. **Sound Window**
   - Functions:
     - Press: Cycle through available instruments
     - Display current instrument name
     - Visual feedback when selected

5. **Settings Item: KEY**
   - Functions:
     - Press: Select key for adjustment
     - Long press: Toggle between sharp/flat notation
     - In major/minor modes: Long press switches to relative key

6. **Settings Item: MODE**
   - Functions:
     - Press: Select mode for adjustment
     - Long press: Switch to FREE mode while preserving existing chord selections

7. **Settings Item: OCT**
   - Functions:
     - Press: Select octave for adjustment
     - Range: -2 to +1
     - Default: 0

8. **Settings Item: INV**
   - Functions:
     - Press: Select inversion for adjustment
     - Range: -3 to +3
     - Default: 0

9. **Chord Display**
   - Functions:
     - Shows current chord name
     - Dynamic font sizing based on chord name length
     - Updates in real-time as chord changes

10. **Plus/Minus Buttons**
   - Functions:
     - Plus: Increase selected value or cycle through chord types
     - Minus: Decrease selected value or cycle through chord types
   - Behavior:
     - When no settings selected: Cycles through chord types of last played key
     - When a setting is selected: Adjusts the selected setting's value

---

## 4. Button Positioning & Layout

### Reference Screen Size
- Width: 1664px
- Height: 768px

#### Exact Pixel Values and Responsive Percentages

| Button         | X(px) | Y(px) | Width(px) | Height(px) | X(%) | Y(%) | Width(%) | Height(%) | Notes |
|----------------|-------|-------|-----------|------------|------|------|----------|-----------|-------|
| Eye            | 32    | 32    | 64        | 64         | 1.9  | 4.2  | 3.8      | 8.3       | Circle, icon centered |
| Skin           | 128   | 32    | 64        | 64         | 7.7  | 4.2  | 3.8      | 8.3       | Circle, icon centered |
| A              | 224   | 32    | 64        | 64         | 13.5 | 4.2  | 3.8      | 8.3       | Square, text centered |
| B              | 304   | 32    | 64        | 64         | 18.3 | 4.2  | 3.8      | 8.3       | Square, text centered |
| BASS           | 384   | 32    | 64        | 64         | 23.1 | 4.2  | 3.8      | 8.3       | Bass clef or offset |
| Sound Window   | 480   | 32    | 240       | 64         | 28.8 | 4.2  | 14.4     | 8.3       | Rounded rect, text centered |
| KEY            | 800   | 32    | 64        | 64         | 48.1 | 4.2  | 3.8      | 8.3       | Label above value |
| MODE           | 880   | 32    | 120       | 64         | 52.9 | 4.2  | 7.2      | 8.3       | Label above value |
| OCT            | 1020  | 32    | 64        | 64         | 61.3 | 4.2  | 3.8      | 8.3       | Label above value |
| INV            | 1100  | 32    | 64        | 64         | 66.1 | 4.2  | 3.8      | 8.3       | Label above value |
| CHORD          | 1180  | 32    | 120       | 64         | 70.9 | 4.2  | 7.2      | 8.3       | Label above value |
| PIANO XL Mode  | 32    | 160   | 64        | 240        | 1.9  | 20.8 | 3.8      | 31.3      | Vertical, text rotated |
| Plus           | 1560  | 240   | 64        | 64         | 93.8 | 31.3 | 3.8      | 8.3       | Centered vertically |
| Minus          | 1560  | 440   | 64        | 64         | 93.8 | 57.3 | 3.8      | 8.3       | Centered vertically |

#### Piano Keys (Bottom Row)

| Key | X(px) | Y(px) | Width(px) | Height(px) | X(%) | Y(%) | Width(%) | Height(%) |
|-----|-------|-------|-----------|------------|------|------|----------|-----------|
| C   | 160   | 480   | 120       | 240        | 9.6  | 62.5 | 7.2      | 31.3      |
| D   | 300   | 480   | 120       | 240        | 18.0 | 62.5 | 7.2      | 31.3      |
| E   | 440   | 480   | 120       | 240        | 26.4 | 62.5 | 7.2      | 31.3      |
| F   | 580   | 480   | 120       | 240        | 34.8 | 62.5 | 7.2      | 31.3      |
| G   | 720   | 480   | 120       | 240        | 43.3 | 62.5 | 7.2      | 31.3      |
| A   | 860   | 480   | 120       | 240        | 51.7 | 62.5 | 7.2      | 31.3      |
| B   | 1000  | 480   | 120       | 240        | 60.1 | 62.5 | 7.2      | 31.3      |

#### Black Keys (Top Row)

| Key  | X(px) | Y(px) | Width(px) | Height(px) | X(%) | Y(%) | Width(%) | Height(%) |
|------|-------|-------|-----------|------------|------|------|----------|-----------|
| C#   | 240   | 320   | 100       | 180        | 14.4 | 41.7 | 6.0      | 23.4      |
| D#   | 380   | 320   | 100       | 180        | 22.8 | 41.7 | 6.0      | 23.4      |
| F#   | 660   | 320   | 100       | 180        | 39.7 | 41.7 | 6.0      | 23.4      |
| G#m  | 800   | 320   | 100       | 180        | 48.1 | 41.7 | 6.0      | 23.4      |
| A#   | 940   | 320   | 100       | 180        | 56.5 | 41.7 | 6.0      | 23.4      |

---

## 5. MORE POINTS

- **Framework:** React Native + Expo, TypeScript
- **Default background color:** #000000 (black)
- **Skin/Background image:** Covers entire app, with overlay for contrast
- **Button layout:** Matches screenshot and above description
- **Button and key alignment:** Even, centered, and responsive
- **All interactive elements:** Have clear visual feedback (highlight, border, or color change)
- **All text:** Centered, with dynamic font sizing for chord names
- **All icons:** White, sized for clarity and touchability
- **All settings and controls:** Accessible from the top bar or left edge
- **Plus/Minus buttons:** Always visible on the right edge, vertically stacked
- **All UI elements:** Maintain high contrast and legibility regardless of background

---

## 6. SPECIAL FUNCTIONS and RELEVANT CODE

### 1. Chord Filtering by Key/Mode

**Explanation:**  
In all modes except FREE, only chords that are diatonically appropriate to the selected key and mode are available for each key.

**Code:**
```typescript
// utils/chord-utils.ts
export const getScaleNotes = (key: NoteName, mode: MusicMode): NoteName[] => {
  if (mode === 'free') return noteNames;
  // ...modeIntervals logic...
  return modeIntervals[mode].map(interval => {
    const noteIndex = (keyIndex + interval) % 12;
    return noteNames[noteIndex];
  });
};

export const isChordTypeDiatonic = (root: NoteName, type: ChordType, mode: MusicMode, currentKey: NoteName): boolean => {
  if (mode === 'free') return true;
  const scaleNotes = getScaleNotes(currentKey, mode);
  const rootIndex = scaleNotes.indexOf(root);
  if (rootIndex === -1) return false;
  const qualities = CGLS_MODE_QUALITIES[mode];
  const allowedTypes = qualities[rootIndex] || [];
  return allowedTypes.includes(type);
};
```

---

### 2. More Chords per Key in FREE Mode

**Explanation:**  
- In FREE mode, every key (all 12 notes) is available, and every chord type (`ALL_CHORD_TYPES`) can be selected for each key.
- In other modes, only the scale notes are available, and each note only offers the chord types that are diatonic to its scale degree.

**Code:**
```typescript
// components/PianoXL.tsx
const ALL_CHORD_TYPES: ChordType[] = [/* ...full list... */];

const getAvailableChordTypes = (note: NoteName): ChordType[] => {
  if (mode === 'free') {
    return ALL_CHORD_TYPES;
  }
  if (!scaleNotes.includes(note)) return [];
  // ...return diatonic chord types for this note...
};
```

---

### 3. How KEY and MODE Control Highlighting/Transparency of Piano Keys

**Explanation:**  
- When the KEY or MODE changes, the app recalculates which notes are in the scale.
- Only keys in the scale are highlighted (with a colored border or background); others are rendered transparent or unplayable.

**Code:**
```typescript
// components/PianoXL.tsx (simplified)
useEffect(() => {
  if (selectedKey && mode) {
    setScaleNotes(getScaleNotes(selectedKey, mode));
  }
}, [selectedKey, mode]);

// In the PianoKey render function:
const isInScale = mode === 'free' ? true : scaleNotes.includes(note as NoteName);

return (
  <Pressable
    style={[
      styles.pianoKey,
      isWhite ? styles.whiteKey : styles.blackKey,
      isInScale && styles.keyInScale, // highlighted
      !isInScale && styles.keyTransparent // transparent/unplayable
    ]}
    disabled={!isInScale}
    // ...
  >
    {/* ... */}
  </Pressable>
);
```

---

### 4. Bass Note Logic: C-E vs. F-B

**Explanation:**  
- For root notes C through E, the bass note is played one octave below the root.
- For F through B, the bass note is played two octaves below the root (an extra octave lower).

**Code:**
```typescript
// components/PianoXL.tsx
const notes = ['C', 'C#', 'D', 'D#', 'E', 'F', 'F#', 'G', 'G#', 'A', 'A#', 'B'];
const rootIndex = notes.indexOf(note);

if (rootIndex !== -1) {
  let bassNote;
  if (!bassOffset || bassOffset === 'BASS') {
    // Default: play root note one octave lower
    // For notes F through B (indices 5-11), shift another octave down
    const extraOctaveShift = rootIndex >= 5 ? -12 : 0;
    bassNote = chord.notes[0] - 12 + extraOctaveShift;
  }
  // ...other bass offset logic...
  if (bassNote !== undefined) {
    playBassNote(bassNote);
  }
}
```

---

### 5. BASS Button and Bass Offset Logic

**Explanation:**  
- The BASS button allows the user to set a custom bass note (slash chord) for each chord.
- The available offsets are: BASS CLEF (root), +1, +2, +3, +4, +5, -6, -5, -4, -3, -2, -1, OFF.
- When a bass offset is set, the chord name updates (e.g., C/C#, C/D).
- The altered bass setting is stored per chord and persists until changed.
- When BASS is deselected, the button returns to the clef symbol and does not affect other keys.

**Code:**
```typescript
// Bass offset sequence
const BASS_SEQUENCE = ['BASS', '+1', '+2', '+3', '+4', '+5', '-6', '-5', '-4', '-3', '-2', '-1', 'OFF'];

// In DockPianoXL or similar:
const [currentBassOffset, setCurrentBassOffset] = useState<string>('BASS');
const [chordBassOffsets, setChordBassOffsets] = useState<Record<string, string>>({});

const handlePlus = () => {
  if (selectedControl === 'bass' && currentChord?.name) {
    const currentIndex = BASS_SEQUENCE.indexOf(currentBassOffset);
    const nextIndex = (currentIndex + 1) % BASS_SEQUENCE.length;
    const newOffset = BASS_SEQUENCE[nextIndex];
    setCurrentBassOffset(newOffset);
    setChordBassOffsets(prev => ({
      ...prev,
      [currentChord.name]: newOffset
    }));
  }
  // ...other plus logic...
};

const handleBassPress = () => {
  setSelectedControl(selectedControl === 'bass' ? null : 'bass');
  // When deselected, the altered bass stays for that chord
};

// When displaying the chord name:
const getChordNameWithBass = (chord: Chord, bassOffset: string) => {
  if (!bassOffset || bassOffset === 'BASS' || bassOffset === 'OFF') return chord.name;
  // Calculate the bass note name based on offset and root
  // e.g., C +1 => C/C#
  // ...logic as in previous code...
  return `${chord.name}/${bassNote}`;
};
```

**Behavior Summary:**
- The BASS root note always plays with each chord by default.
- Pressing the BASS button allows more bass options for each chord separately.
- When BASS is de-selected, the text changes back to the bass clef symbol.
- When BASS is de-selected, it does not alter any other piano key.

---

### 6. ON KEY Chord Scrolling

**Explanation:**
- When a user presses a piano key, that key's note is stored as the `lastPressedNote`.
- If the user then presses the Plus or Minus button (and no settings are selected), the app cycles through the available chord types for that note.
- The available chord types depend on the current mode:
  - In **FREE** mode: all chord types are available for every key.
  - In other modes: only diatonically-appropriate chord types are available for each scale degree.
- The chord name and sound update immediately as the user scrolls.

**Code:**
```typescript
// components/PianoXL.tsx (inside handleKeyPress)
const handleKeyPress = (note: string, buttonIndex?: number) => {
  // ...other logic...
  setLastPressedNote(note as NoteName);
  // ...play chord logic...
};

// Cycling Through Chord Types with Plus/Minus
useImperativeHandle(ref, () => ({
  adjustLastChordType: (direction: 'up' | 'down', buttonIndex?: number) => {
    if (!lastPressedNote) return;
    const availableTypes = mode === 'free'
      ? ALL_CHORD_TYPES
      : getAvailableChordTypes(lastPressedNote);
    if (mode !== 'free' && !scaleNotes.includes(lastPressedNote)) return;
    if (availableTypes.length === 0) return;
    setChordTypeIndices(prev => {
      const noteIndices = prev[lastPressedNote];
      if (sizeText !== 'XL' && buttonIndex !== undefined) {
        // Handle split buttons (XXL/XXXL)
        let currentButtonIndices: { [key: number]: number };
        if (typeof noteIndices === 'object') {
          currentButtonIndices = noteIndices;
        } else {
          currentButtonIndices = {};
          if (typeof noteIndices === 'number') {
            const buttonCount = sizeText === 'XXL' ? 2 : 3;
            for (let i = 0; i < buttonCount; i++) {
              currentButtonIndices[i] = noteIndices;
            }
          }
        }
        const currentIndex = currentButtonIndices[buttonIndex] || 0;
        const newIndex = direction === 'up'
          ? (currentIndex + 1) % availableTypes.length
          : (currentIndex - 1 + availableTypes.length) % availableTypes.length;
        return {
          ...prev,
          [lastPressedNote]: {
            ...currentButtonIndices,
            [buttonIndex]: newIndex
          }
        };
      }
      // Handle single button (XL)
      const currentIndex = typeof noteIndices === 'number' ? noteIndices : 0;
      const newIndex = direction === 'up'
        ? (currentIndex + 1) % availableTypes.length
        : (currentIndex - 1 + availableTypes.length) % availableTypes.length;
      return {
        ...prev,
        [lastPressedNote]: newIndex
      };
    });
  },
  // ...other imperative methods...
}));

// Plus/Minus Button Triggers
// app/Dock-PianoXL.tsx or similar
const handlePlus = () => {
  if (!selectedControl && pianoXLRef.current) {
    pianoXLRef.current.adjustLastChordType('up', lastPressedButtonIndex);
    return;
  }
  // ...other plus logic...
};

const handleMinus = () => {
  if (!selectedControl && pianoXLRef.current) {
    pianoXLRef.current.adjustLastChordType('down', lastPressedButtonIndex);
    return;
  }
  // ...other minus logic...
};
```

**Summary of Flow**
1. User presses a key → `lastPressedNote` is set.
2. User presses Plus/Minus → `adjustLastChordType` cycles the chord type for `lastPressedNote`.
3. The chord name and sound update instantly. 

### 7. Comprehensive Chord Type Mapping

**Explanation:**
- Each degree in each mode has a specific set of available chord types that are musically appropriate.
- This mapping ensures that when users scroll through chord options on a key, they only see harmonically valid choices for the current key and mode.
- In FREE mode, all chord types are available for every key.

**Code:**
```typescript
// utils/musicLogic.ts

// Define the complete set of chord types available for each degree in each mode
const MODE_DIATONIC_CHORD_TYPES: Record<MusicMode, Record<number, ChordType[]>> = {
  'major': {
    1: ['maj', 'maj7', 'maj9', 'maj6', 'maj7#11', 'maj13'], // I
    2: ['min', 'min7', 'min9', 'min6', 'min11'], // ii
    3: ['min', 'min7', 'min9', 'min6', 'min11'], // iii
    4: ['maj', 'maj7', 'maj9', 'maj6', 'maj7#11'], // IV
    5: ['maj', 'maj7', 'maj9', 'maj13', '7', '9', '13'], // V
    6: ['min', 'min7', 'min9', 'min6', 'min11'], // vi
    7: ['dim', 'dim7', 'm7b5'] // vii°
  },
  'minor': {
    1: ['min', 'min7', 'min9', 'min6', 'min11'], // i
    2: ['dim', 'dim7', 'm7b5'], // ii°
    3: ['maj', 'maj7', 'maj9', 'maj6', 'maj7#11'], // III
    4: ['min', 'min7', 'min9', 'min6', 'min11'], // iv
    5: ['min', 'min7', 'min9', 'min6', 'min11', '7', '9', '13'], // v
    6: ['maj', 'maj7', 'maj9', 'maj6', 'maj7#11'], // VI
    7: ['maj', 'maj7', 'maj9', 'maj6', 'maj7#11'] // VII
  },
  'dorian': {
    1: ['min', 'min7', 'min9', 'min6', 'min11'], // i
    2: ['min', 'min7', 'min9', 'min6', 'min11'], // ii
    3: ['maj', 'maj7', 'maj9', 'maj6', 'maj7#11'], // III
    4: ['maj', 'maj7', 'maj9', 'maj6', 'maj7#11'], // IV
    5: ['min', 'min7', 'min9', 'min6', 'min11', '7', '9', '13'], // v
    6: ['dim', 'dim7', 'm7b5'], // vi°
    7: ['maj', 'maj7', 'maj9', 'maj6', 'maj7#11'] // VII
  },
  'phrygian': {
    1: ['min', 'min7', 'min9', 'min6', 'min11'], // i
    2: ['maj', 'maj7', 'maj9', 'maj6', 'maj7#11'], // II
    3: ['dim', 'dim7', 'm7b5'], // iii°
    4: ['min', 'min7', 'min9', 'min6', 'min11'], // iv
    5: ['min', 'min7', 'min9', 'min6', 'min11', '7', '9', '13'], // v
    6: ['maj', 'maj7', 'maj9', 'maj6', 'maj7#11'], // VI
    7: ['min', 'min7', 'min9', 'min6', 'min11'] // vii
  },
  'mixolydian': {
    1: ['maj', 'maj7', 'maj9', 'maj6', 'maj7#11', '7', '9', '13'], // I
    2: ['min', 'min7', 'min9', 'min6', 'min11'], // ii
    3: ['dim', 'dim7', 'm7b5'], // iii°
    4: ['maj', 'maj7', 'maj9', 'maj6', 'maj7#11'], // IV
    5: ['min', 'min7', 'min9', 'min6', 'min11'], // v
    6: ['min', 'min7', 'min9', 'min6', 'min11'], // vi
    7: ['maj', 'maj7', 'maj9', 'maj6', 'maj7#11'] // VII
  },
  'locrian': {
    1: ['dim', 'dim7', 'm7b5'], // i°
    2: ['maj', 'maj7', 'maj9', 'maj6', 'maj7#11'], // II
    3: ['min', 'min7', 'min9', 'min6', 'min11'], // iii
    4: ['min', 'min7', 'min9', 'min6', 'min11'], // iv
    5: ['maj', 'maj7', 'maj9', 'maj6', 'maj7#11'], // V
    6: ['maj', 'maj7', 'maj9', 'maj6', 'maj7#11'], // VI
    7: ['min', 'min7', 'min9', 'min6', 'min11'] // vii
  }
};

// Helper function to get available chord types for a specific degree in a mode
export const getDiatonicChordTypesForDegree = (
  mode: MusicMode,
  degree: number
): ChordType[] => {
  return MODE_DIATONIC_CHORD_TYPES[mode][degree] || [];
};

// Helper function to get available chord types for a note in a key/mode
export const getAvailableChordTypesForNote = (
  note: NoteName,
  key: NoteName,
  mode: MusicMode
): ChordType[] => {
  if (mode === 'free') return ALL_CHORD_TYPES;
  
  const scaleNotes = getScaleNotes(key, mode);
  const degree = scaleNotes.indexOf(note) + 1; // Convert to 1-based index
  
  if (degree === -1) return []; // Note not in scale
  
  return getDiatonicChordTypesForDegree(mode, degree);
};
```

**Key Features:**
1. **Comprehensive Chord Types**: Each degree in each mode has a curated list of appropriate chord types that are commonly used in that context.

2. **Music Theory Accuracy**: The chord types follow standard music theory practices for each mode:
   - Major mode: Standard major scale harmony
   - Minor mode: Natural minor scale harmony
   - Dorian: Characteristic minor mode with major IV
   - Phrygian: Characteristic minor mode with b2
   - Mixolydian: Characteristic major mode with b7
   - Locrian: Characteristic diminished mode

3. **Common Extensions**: Each chord type includes common extensions and variations:
   - Major chords: maj, maj7, maj9, maj6, maj7#11, maj13
   - Minor chords: min, min7, min9, min6, min11
   - Dominant chords: 7, 9, 13
   - Diminished chords: dim, dim7, m7b5

4. **Flexible Implementation**: The helper functions make it easy to:
   - Get chord types for a specific degree in a mode
   - Get chord types for a specific note in a key/mode
   - Handle the special case of FREE mode

This implementation ensures that when users scroll through chord options on a key, they'll only see musically appropriate choices for the current key and mode, while still maintaining the flexibility to use any chord type in FREE mode. 

## 9. Audio Implementation: Sample-Based Audio (Mobile Only)

The audio system uses pre-recorded audio samples (MP3 files) for high-quality sound playback. This is implemented using the Expo Audio API (expo-av) and is optimized for mobile devices.

```typescript
// utils/audioEngine.ts
import { Audio } from 'expo-av';

// Available sound types and their corresponding MP3 files
const AVAILABLE_SOUNDS = {
  BALAFON: require('../assets/sounds/balafon.mp3'),
  PIANO: require('../assets/sounds/piano.mp3'),
  RHODES: require('../assets/sounds/rhodes.mp3'),
  STEEL_DRUM: require('../assets/sounds/steel_drum.mp3'),
  PLUCK: require('../assets/sounds/pluck.mp3'),
  PAD: require('../assets/sounds/pad.mp3'),
};

class SoundManager {
  private sounds: { [key: string]: Audio.Sound } = {};
  private currentInstrument: string = 'PIANO';

  // Load all sound samples
  async loadSounds() {
    for (const [name, source] of Object.entries(AVAILABLE_SOUNDS)) {
      const { sound } = await Audio.Sound.createAsync(source);
      this.sounds[name] = sound;
    }
  }

  // Play a chord with the current instrument
  async playChord(notes: number[]) {
    const sound = this.sounds[this.currentInstrument];
    if (sound) {
      await sound.setPositionAsync(0);
      await sound.playAsync();
    }
  }

  // Play a bass note
  async playBass(note: number) {
    const sound = this.sounds[this.currentInstrument];
    if (sound) {
      await sound.setPositionAsync(0);
      await sound.playAsync();
    }
  }

  // Stop all currently playing sounds
  async stopAll() {
    for (const sound of Object.values(this.sounds)) {
      await sound.stopAsync();
    }
  }

  // Change the current instrument
  setInstrument(instrument: string) {
    if (AVAILABLE_SOUNDS[instrument]) {
      this.currentInstrument = instrument;
    }
  }
}

export const soundManager = new SoundManager();
```

Key Features:
- Uses high-quality pre-recorded audio samples
- Supports multiple instruments (Balafon, Piano, Rhodes, Steel Drum, Pluck, Pad)
- Efficient sound management with the Expo Audio API
- Easy to add new instrument samples
- Low latency playback
- Memory-efficient sound loading

Note: The current implementation uses the sample-based system for its high-quality sound and realistic instrument timbres. The synthesizer implementation is provided as an alternative option that could be used if different sound characteristics are desired. 