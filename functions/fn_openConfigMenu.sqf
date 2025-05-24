// fn_processText.sqf
// This function will process the entered text when the Check button is pressed

#include "..\tracks.hpp"

// Category acquisition
private _dropdown = findDisplay 618795 displayCtrl 2100;
private _selectedIndex = lbCurSel _dropdown;
private _selectedCategory = _dropdown lbText _selectedIndex;

// Input text
private _textbox = findDisplay 618795 displayCtrl 1001;
private _inputText = ctrlText _textbox;
private _words = _inputText splitString " ";

// Validity reporter
private _ctrl = findDisplay 618795 displayCtrl 1000;
private _processedText = "Invalid terms: ";

private _validSoundsLower = _tracks apply { toLower _x };

{
    private _word = _x;
    private _formattedWord = format["VoxMod_%1_%2", _selectedCategory, _word];
    private _wordLower = toLower _formattedWord;

    if (!(_wordLower in _validSoundsLower)) then {
        _processedText = _processedText + _x + " "; // Mark as invalid
    };
} forEach _words;

// Report the invalid words
_ctrl ctrlSetText _processedText;
