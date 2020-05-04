# MidiSynthPractice200402
First attempt at a talking midi synthesizer.

# The Program:
       -Uses MIDI Controller plugged into Teensy 3.6  to trigger notes.
       -Alternatively, the letter 'a' on the qwerty keyboard can trigger a note by sending a MIDI 'Note On' message for debugging.
       -And the letter 's' sends MIDI 'Note Off'.
       -Program was written on Microsoft Visual Studio Code, with PlatformIO extension.
       -All controls can be selected via qwerty input and modified with a potentiometer.
       -4 simultaneous oscillators per note, each with separate waveforms(9), LFOs, envelopes, filters, and settings.
       -9 LFO shapes selectable, each with adjustable slope, depth, speed, and height.
       -USB MIDI note allocation to voice number method.
       -LFO functionality is defined in LfoUpdate.cpp file in the src folder.
       -Most other functions are defined in 'Martone.cpp' file in the src folder.
       -'GuiTool.cpp' contains the code exported from the Teensy Audio Library. (See link below).
       -(Currently I only have 1 note enabled (A440), bc I'm working on modulation and vocal formants, (i.e. LFOs and Filters) not melody.)
#      The Circuit:
       -USB Midi controller plugged into USB host port jack on on Teensy 3.6
       -Teensy Audio Shield plugged on top of Teensy.
       -10k pot connected to 'A1' on Teensy. (I'm using a thumbwheel that I soldered onto the Audio Shield. See Teensy Audio Workshop below.)
       -The pot modifies different parameters (attack, volume, filter, etc.), depending on which parameter is selected via qwerty input.
#     References:
       -  https://forum.pjrc.com/threads/41862-MIDI-notes-to-trigger-Audio-Board-synth?highlight=polyphony 'Seenthysizer' Polyphony example
       -  https://www.youtube.com/watch?v=evVRCL9-TWs  'Create a Bluetooth App and control the Arduino.'
       -  http://www.martyncurrey.com/arduino-hm-10-and-app-inventor-2-adding-a-slider/ Adding a Slider to MIT App Inventor. 
       -  https://www.youtube.com/watch?v=zphkBTkOIyQ Notes and Volts Part 8 LFO
       -  https://www.youtube.com/watch?v=IoADj8dvTQc Notes and Volts Part 3 Keyboard
       -  https://github.com/k2rek/martone-prototype/blob/master/Final%20Prototype/main/main.ino  Martone V1 code. Kyle Tworek
       -  https://www.pjrc.com/store/audio_tutorial_kit.html Teensy Audio Workshop
       -  https://www.pjrc.com/teensy/gui/ Teensy Audio Library
  #   Author(s):
       Juan Estrella
