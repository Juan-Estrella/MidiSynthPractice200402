#pragma once

#include <Arduino.h>

void MyNoteOn(byte channel, byte note, byte velocity);
void MyNoteOff(byte channel, byte note, byte velocity);
void InitializeAudio();