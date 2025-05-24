# VoxMod
Hello all! This is my first mod I've ever done scripting for so hopefully it's a good one.

Description
This mod takes a folder of soundfiles and makes them available to play via 3D sound or global music in-game dynamically via an in-game dialog.
As of now, there are 5 voices:
-Central Autonomic Service System for Internal Emergencies (C.A.S.S.I.E.) from SCP: Secret Laboratory
-Black Mesa Announcement System (BMAS) from Half-Life
-Hazardous Environment Combat Unit (HECU) from Half-Life
-Hazardous EnVironment(HEV) Suit from Half-Life
-War Operation Plan Response (WOPR/Joshua) from WarGames (1983)

The addition of more voicelines are welcome, but please provide or otherwise acquire word-by-word sound files (preferably .wav) that can be stitched together and has at least 300 words (unless it is particularly funny or useful). The WOPR sounds are an example of handmade sound files with some imperfections. CASSIE is the best example of good voicelines with around 980 separate words by design rather than chopped up from huge clips. As you may be able to tell with specifically the HEV suit, long voicelines do not allow for much flexibility and lead to hard-to-understand naming schemes. I accept suggestions for other features.

Usage
To properly use this mod, please refer to this pastebin[pastebin.com] for all the keywords.

Simply choose a voice, type in the keywords into the box, press check to see if there are any invalid terms, and then press ok to play. Ok will also skip over invalid terms.

Important: if you type multiline (pressing enter at any time, wraparound is okay), make sure to put spaces at the end of the previous line and before the current line. There is no way to read newline characters in BI's system from what I could glean.

The "Emanate from module" checkbox switches between local and global audio. Checked means the sound emanates from the module's placement location.

The textboxs under the checkbox will determine the range, volume, and pitch at which the sound can be heard. A value of 200 equates to about 50m. If not given, defaults to 200. Volume can range from 0 to 5, a 0 is changed automatically to 1. Pitch can range from 0.5 to 2.0, with 1.0 being normal. Changing pitch also changes length of the message. Volume and range are only available for local audio, range is not needed for global audio and each user can adjust audio on their own for global.

Global audio volume is determined by Esc > Configure > Audio > "Scripted UI" slider. This may start very high or very low to start with, so be weary of blown eardrums and/or deafness.

The "Optional" checkbox enables/disables optional additional features for each voice, enabled by default.
At the moment, the only optional setting is for CASSIE. If checked, it will play bell_start, bell_mid, and bell_end at the appropriate locations. These sounds are also available for you if you disable the option, but bell_mid will not be possible manually and will play ONLY the ambience for about a full 3 minutes. bell_mid only works for global audio, I had troubles with it lasting forever with local audio.

Important notes
Any voicelines with different pronunciation typically have numbers appended on the end of them, but they are rare.
Some voicelines are not individual words and are kept in as they are common phrases.

CASSIE has glitch sound effects, in the form of g1, g2, g3, g4, g5, and g6. I like to use this as spaces, commas, or periods.
CASSIE also has the ability to add prefixes and suffixes by adding the keywords "pre", "post", "ed", "ts" , "ing", and more.
CASSIE also has bell effects, in the form of "bell_start" and "bell_end" as well as some longer sounds like "nuke90" and "nukeresume90" which are the nuclear detonation countdowns + music. These mimic SCP:SL's in-game admin menu for CASSIE.

The HECU, HEV, and BMAS all have a "comma" and "period" keyword that acts as dead air for spacing. These are 0.2s and 0.4s respectively.
Many HECU voicelines have underscores(_) after them, meaning the word is stressed/shouted. Almost all regular words have underscored(_) versions.
The HEV voicelines are unfortunately very long and the names are not descriptive enough for the entire phrase, so make sure to test ahead of time.

WOPR has many alternative ways to say some words, to add variety or fill that particular hole in sentences. Original full phrases are also available. The alternatives that have underscores are either variant numbers or are the variants from the final scene where there is an echo present.

Scripting
There are a few functions provided by this mod to enable scripting functionality.
All voicelines can be accessed through "playMusic" and "playSound" by calling them. The naming scheme is "VoxMod_VOICE_WORD", so if you wanted to say "hello" with CASSIE so that everyone in the server can hear, you would do:
playMusic "VoxMod_CASSIE_hello";

For more complex scripting, you have the function VoxMod_fnc_playSoundSequence. This function accepts 9 parameters:
0. input text - the string of words that will be ran in sequence, acts just like the dialog textbox
1. voice category - the string of the voice name, like CASSIE, BMAS, HEV, or HECU
2. local audio - boolean. if true, will play the audio locally from either parameter 3 or parameter 5. If false, ignores parameters 3,4,5.
3. source - the object the sound is played from if parameter 2 is true. this source is overwritten if parameter 5 is given.
4. distance - integer distance the sound can be heard from. BI's scripting claims this measurement is meters, but it seems incorrect. numbers ~200 give ~50m range
5. position - array of x,y,z. if given, overwrites the source from parameter 3.
6. volume - integer multiplier to volume. 0 is mute (which changes to 1 due to uselessness), 1 is normal, 5 is maximum volume boost, as according to BI's playSound3D
7. pitch - floating point multiplier to pitch. 0.5 is lowest pitch, and 2.0 is highest pitch. this changes the length of the sound file, so phrase are automatically shorter
8. optional - boolean. if true, uses the optional feature for the chosen voice. see Usage for details on the effects.

Examples
["hello how are you", "CASSIE", true, myRadioObject, 200] call VoxMod_fnc_playSoundSequence; 
// plays and is hearable ~50m from myRadioObject, identified before function run, also runs optional features by default

["hello how are you", "CASSIE", true, myRadioObject, 200, getPosASL myRadioObject, 5, 1.2, false] call VoxMod_fnc_playSoundSequence; 
// plays and is hearable ~50m from myRadioObject, identified before function run with 5x volume and 1.2x pitch, does not run optional features

["hello how are you", "CASSIE", false] call VoxMod_fnc_playSoundSequence; 
// plays globally normally with optional features

["hello how are you", "CASSIE", false, objNull, 0, [], 1, 1.2, false] call VoxMod_fnc_playSoundSequence; 
// plays globally with a pitch of 1.2 and no optional features

Please be aware that in a multiplayer server, you must instead do
 ["hello how are you", "CASSIE", false, objNull, 0, [], 1, 1.2, false] remoteExec ["VoxMod_fnc_playSoundSequence", 0]; 

You could use these functions to setup triggers to say what you want, when you want it. If anyone creates a mission using some of these, please let me know as I would love to see a video.

Credit
Thanks to Valve, Northwood Studios, and MGM for the voicelines.
Shamefully, I must also thank ChatGPT for my sanity. Getting into the Arma modding scene raw is difficult, especially when the BI forums are down that inform about crucial scripting fixes.
