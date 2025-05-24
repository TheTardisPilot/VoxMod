// fn_playSoundSequence.sqf
// This function will play each valid track in the input text sequentially

params [
    ["_inputText", "", [""]],                // Input text (textbox input in dialog)
    ["_selectedCategory", "", [""]],         // Voice (dropdown menu in dialog)
    ["_isChecked", false, [false]],          // Play local? boolean, default false, determined by checkbox in dialog
    ["_object", objNull, [objNull]],         // Default to objNull
    ["_soundDistance", 200, [200]],          // Distance default 200 (Distance: textbox in dialog)
    ["_position", [0,0,0], [[0,0,0]]],       // Default to obj position, overwrites object if supplied
    ["_volume", 1, [1]],                     // Volume default 1 (volume in textbox)
    ["_pitch", 1.0, [1.0]],                  // Pitch default 1.0 (pitch in textbox)
    ["_optional", true, [true]]              // Optional default enabled
];

if (!isNull _object && {_position isEqualTo [0,0,0]}) then {
    _position = getPosASL _object;
};
if (_soundDistance <= 0) then {
    _soundDistance = 200;
};
if (_volume <= 0) then {
    _volume = 1;
};
if (_pitch <= 0) then { 
    _pitch = 1.0;
};

#include "..\tracks.hpp"

private _words = _inputText splitString " ";
private _validTracksToPlay = [];
private _validTracksLower = _tracks apply { toLower _x };

// Iterate over each word and check if it's a valid track
{
    private _word = _x;
    private _formattedWord = format["VoxMod_%1_%2", _selectedCategory, _word];
    private _wordLower = toLower _formattedWord;

    if (_wordLower in _validTracksLower) then {
        // If valid, add it to the list
        _validTracksToPlay pushBack _formattedWord;
    };
} forEach _words;

if (_isChecked) then { // Checked, play local
    
    [_validTracksToPlay, _object, _position, _soundDistance, _volume, _pitch, _selectedCategory, _optional] spawn {
        if(_this select 7) then { // Optional, makes it more like actual thing
            if((_this select 6) == "CASSIE") then {
                playSound3D [(getArray(configFile >> "CfgMusic" >> "VoxMod_CASSIE_bell_start" >> "sound")) select 0, (_this select 1), false, (_this select 2), (_this select 4), 1, (_this select 3), 0, true];
                sleep 2.5;
            };

        };
        
        // Play each valid sound sequentially
        {
            private _soundArray = getArray (configFile >> "CfgMusic" >> _x >> "sound"); // Each voiceline has same path in CfgMusic and CfgSounds
            private _configPath = if (count _soundArray > 0) then { _soundArray select 0 } else { "" };
            
            if (_configPath != "") then {
                playSound3D [_configPath, (_this select 1), false, (_this select 2), (_this select 4), (_this select 5), (_this select 3), 0, true];
            } else {
                diag_log format ["VoxMod_ERROR: No valid sound path for %1", _x];
            };

            private _duration = [_x, "duration", 1] call CBA_fnc_getMusicData;

            _duration = (_duration / (_this select 5));

            sleep _duration; // Sleep between tracks according to pitch

            

        } forEach (_this select 0);
        
        if(_this select 7) then {
            if((_this select 6) == "CASSIE") then {
                playSound3D [(getArray(configFile >> "CfgMusic" >> "VoxMod_CASSIE_bell_end" >> "sound")) select 0, (_this select 1), false, (_this select 2), (_this select 4), 1, (_this select 3), 0, true];
            };

        };

    };
} else { // Unchecked, play global
    [_validTracksToPlay, _selectedCategory, _optional, _pitch] spawn {
        private _id = -1;
        if(_this select 2) then { // Optional, makes it more like actual thing
            if((_this select 1) == "CASSIE") then {
                playSoundUI ["VoxMod_CASSIE_bell_start", 1, 1];
                _id = playSoundUI ["VoxMod_CASSIE_bell_mid", 1, 1];
                sleep 2.5;
            };

        };
        
        // Play each valid track sequentially
        {
            playSoundUI [_x, 1, _this select 3];

            private _duration = [_x, "duration", 1] call CBA_fnc_getMusicData;

	    if((_this select 1) == "AlterraPDA") then {
                _duration = _duration * 1.1;
            };

            _duration = _duration / (_this select 3);

            sleep _duration;
        } forEach (_this select 0);
        
        if(_this select 2) then {
            if((_this select 1) == "CASSIE") then {
                playSoundUI ["VoxMod_CASSIE_bell_end", 1, 1];
                stopSound _id;
            };

        };

    };
};