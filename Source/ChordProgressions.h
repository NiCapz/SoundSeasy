/*
  ==============================================================================
    ChordProgressions.h
    Created: 26 Jun 2025 10:43:47pm
    Author:  Karl Diedrichsen
  ==============================================================================
*/

#pragma once
#include <list>
#include <string>

struct ChordType
{
    std::array<int, 3> noteOffsets;
};

struct Chord
{
    int degree;
    ChordType type;
};

struct ChordTree
{
    Chord chord;
    std::list<ChordTree> nextChords;

    ChordTree(int degree, ChordType chordType) : chord({degree, chordType}), nextChords({}) {}
    ChordTree(Chord chord, std::list<ChordTree> nextChords) : chord(chord), nextChords(nextChords) {}
};

const ChordType MAJOR {{0, 4, 7}};
const ChordType MINOR {{0, 3, 7}};
const ChordType DIMINISHED {{0, 3, 6}};

const ChordTree majorProgressions {{1, MAJOR}, {{{6, MINOR}, {{{4, MAJOR}, {{5, MAJOR},
                                                                            {3, MINOR},
                                                                            {2, MAJOR}}},
                                                              {{2, MAJOR}, {{5, MAJOR},
                                                                            {3, MAJOR},
                                                                            {3, MINOR},
                                                                            {4, MINOR}}},
                                                              {{3, MINOR}, {{4, MAJOR},
                                                                            {2, MINOR},
                                                                            {5, MAJOR}}},
                                                              {{5, MAJOR}, {{4, MAJOR},
                                                                            {2, MINOR},
                                                                            {5, MAJOR},
                                                                            {4, MINOR}}}}},
                                                {{4, MAJOR}, {{{6, MINOR}, {{5, MAJOR},
                                                                            {3, MINOR},
                                                                            {7, MAJOR}}},
                                                              {{2, MINOR}, {{5, MAJOR},
                                                                            {6, MINOR},
                                                                            {7, MAJOR}}},
                                                              {{3, MINOR}, {{5, MAJOR},
                                                                            {2, MINOR},
                                                                            {4, MINOR},
                                                                            {7, MAJOR}}},
                                                              {{5, MAJOR}, {{2, MINOR},
                                                                            {6, MAJOR},
                                                                            {7, MAJOR}}}}},
                                                {{5, MAJOR}, {{{6, MINOR}, {{4, MAJOR},
                                                                            {3, MINOR},
                                                                            {5, MAJOR},
                                                                            {2, MAJOR}}},
                                                              {{3, MINOR}, {{2, MAJOR},
                                                                            {4, MAJOR},
                                                                            {5, MAJOR},
                                                                            {2, MINOR}}},
                                                              {{4, MAJOR}, {{6, MINOR},
                                                                            {2, MINOR},
                                                                            {3, MAJOR},
                                                                            {3, MINOR},
                                                                            {4, MINOR}}},
                                                              {{2, MINOR}, {{6, MINOR},
                                                                            {4, MAJOR},
                                                                            {3, MAJOR},
                                                                            {3, MINOR},
                                                                            {7, MAJOR}}}}},
                                                {{2, MINOR}, {{{6, MINOR}, {{5, MAJOR},
                                                                            {3, MINOR},
                                                                            {4, MINOR},
                                                                            {7, MAJOR}}},
                                                              {{3, MINOR}, {{4, MAJOR},
                                                                            {4, MINOR},
                                                                            {5, MAJOR},
                                                                            {7, MAJOR}}},
                                                              {{4, MINOR}, {{5, MAJOR},
                                                                            {3, MINOR},
                                                                            {4, MINOR},
                                                                            {7, MAJOR}}},
                                                              {{5, MAJOR}, {{4, MINOR},
                                                                            {4, MAJOR},
                                                                            {6, MINOR},
                                                                            {7, MAJOR}}}}}}};

inline std::string noteNumberToName(int noteNumber)
{
    static const std::string names[] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "Bb", "B"};
    return names[noteNumber % 12];
}

inline std::string chordName(int baseNote, Chord chord)
{
    static const int scaleIndex[] = {0, 2, 4, 5, 7, 9, 11};

    std::string name = noteNumberToName(baseNote + scaleIndex[chord.degree - 1]);

    if(chord.type.noteOffsets == MAJOR.noteOffsets)
        name.append(" major");
    else if(chord.type.noteOffsets == MINOR.noteOffsets)
        name.append(" minor");
    else if(chord.type.noteOffsets == DIMINISHED.noteOffsets)
        name.append(" diminished");

    return name;
}

inline std::array<int, 3> chordToNotes(int baseNote, Chord chord)
{
    static const int scaleIndex[] = {0, 2, 4, 5, 7, 9, 11};
    
    std::array<int, 3> notes{0};
    
    for(int note = 0; note < 3; note++)
        notes[note] = baseNote + scaleIndex[chord.degree - 1] + chord.type.noteOffsets[note];
    
    return notes;
}
