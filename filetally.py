import os
from mutagen.oggvorbis import OggVorbis

def get_ogg_duration(file_path):
    """Retrieve the duration of an OGG file"""
    try:
        audio = OggVorbis(file_path)  # Open the OGG file
        return audio.info.length      # Return duration in seconds
    except Exception as e:
        print(f"Error processing {file_path}: {e}")
        return None

def scan_directory_for_ogg_files(directory):
    """Scan the directory and return a dictionary mapping subdirectories to their .ogg files"""
    ogg_files_by_category = {}
    
    for root, _, files in os.walk(directory):
        category = os.path.basename(root)  # Subdirectory name (CASSIE, HECU, etc.)
        
        ogg_files = [os.path.join(root, file) for file in files if file.lower().endswith(".ogg")]
        if ogg_files:
            ogg_files_by_category[category] = ogg_files

    return ogg_files_by_category

def generate_cfgsounds_and_cfgmusic(ogg_files_by_category):
    """Generate CfgSounds and CfgMusic format for OGG files with their durations and sounds array."""
    
    sounds = []  # Sound list for CfgSounds and CfgMusic
    cfg_sounds_classes = ""  # Store sound class definitions separately
    cfg_music_classes = ""  # Store music class definitions separately

    for category, ogg_files in ogg_files_by_category.items():
        for ogg_file in ogg_files:
            sound_name = os.path.splitext(os.path.basename(ogg_file))[0]
            duration = get_ogg_duration(ogg_file)
            if duration is not None:
                class_name = f"VoxMod_{category}_{sound_name}"
                file_path = f"VoxMod\\sounds\\{category}\\{os.path.basename(ogg_file)}"

                # Create class for CfgSounds (no duration field)
                cfg_sounds_classes += f"    class {class_name} {{\n"
                cfg_sounds_classes += f"        name = \"{class_name}\";\n"
                cfg_sounds_classes += f"        sound[] = {{\"{file_path}\", 1, 1}};\n"
                cfg_sounds_classes += f"        titles[] = {{}};\n"
                cfg_sounds_classes += f"    }};\n"

                # Create class for CfgMusic (with duration field)
                cfg_music_classes += f"    class {class_name} {{\n"
                cfg_music_classes += f"        name = \"{class_name}\";\n"
                cfg_music_classes += f"        sound[] = {{\"{file_path}\", 1, 1}};\n"
                cfg_music_classes += f"        duration = {duration};\n"
                cfg_music_classes += f"        titles[] = {{}};\n"
                cfg_music_classes += f"    }};\n"

                # Add sound name to the sounds array for both CfgSounds and CfgMusic
                sounds.append(f"\"{class_name}\"")

    # Ensure sounds[] appears at the top for CfgSounds and CfgMusic
    sounds_array = "    sounds[] = {" + ", ".join(sounds) + "};\n" if sounds else ""
    cfg_sounds = "class CfgSounds {\n" + sounds_array + cfg_sounds_classes + "};\n"

    sounds_array_for_music = "    tracks[] = {" + ", ".join(sounds) + "};\n" if sounds else ""
    cfg_music = "class CfgMusic {\n" + sounds_array_for_music + cfg_music_classes + "};\n"

    # Generate the tracks.hpp content for both CfgSounds and CfgMusic
    tracks_hpp = f"private _tracks = [{', '.join(sounds)}];"

    return cfg_sounds, cfg_music, tracks_hpp

def main():
    target_directory = "C:/Users/Cole/Documents/Arma 3 Projects/VoxMod/sounds/"  # Start in the sounds directory
    cfg_sounds_output_file = "CfgSounds.hpp"  # Output file where CfgSounds will be written
    cfg_music_output_file = "CfgMusic.hpp"    # Output file where CfgMusic will be written
    tracks_output_file = "tracks.hpp"         # Output file for sounds array

    # Scan for all .ogg files in subdirectories
    ogg_files_by_category = scan_directory_for_ogg_files(target_directory)

    # Generate the CfgSounds, CfgMusic configuration and tracks.hpp
    cfg_sounds, cfg_music, tracks_hpp = generate_cfgsounds_and_cfgmusic(ogg_files_by_category)

    # Write the generated CfgSounds to a file
    with open(cfg_sounds_output_file, "w") as f:
        f.write(cfg_sounds)

    # Write the generated CfgMusic to a file
    with open(cfg_music_output_file, "w") as f:
        f.write(cfg_music)

    # Write the generated tracks.hpp to a file
    with open(tracks_output_file, "w") as f:
        f.write(tracks_hpp)

    print(f"CfgSounds file has been generated and saved to {cfg_sounds_output_file}")
    print(f"CfgMusic file has been generated and saved to {cfg_music_output_file}")
    print(f"tracks.hpp file has been generated and saved to {tracks_output_file}")

if __name__ == "__main__":
    main()
