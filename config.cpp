// config.cpp

class CfgPatches {
    class VoxMod {
        units[] = {"VoxMod_ZeusModule"};
        requiredAddons[] = {"A3_Modules_F", "CBA_Main"};
    };
};

class CfgFunctions {
    class VoxMod {
        tag = "VoxMod";
        class Functions {
            file = "VoxMod\functions";
            class module{};
            class openConfigMenu{};
            class loadDropdownMenu{};
            class processText{};
            class playSoundSequence{};
        };
    };
};

class CfgVehicles {
    class Module_F;
    class VoxMod_ZeusModule: Module_F {
        scope = 2;
        scopeCurator = 2;
        displayName = "VoxMod";
        category = "Audio";
        function = "VoxMod_fnc_module";

        curatorInfoType = "VoxMod_ConfigMenu";
        isGlobal = 1;
        isTriggerActivated = 0;
        curatorCanAttach = 0;

        icon = "VoxMod\ui\icon_voxmod.paa";
        picture = "VoxMod\ui\icon_voxmod.paa";     
    };
};

#define GUI_GRID_W (1 / 40)
#define GUI_GRID_H (1 / 25)
#define GUI_GRID_X (safezoneX + (safezoneW - 1) / 2)
#define GUI_GRID_Y (safezoneY + (safezoneH - 1) / 2)

class RscFrame;
class RscText;
class RscStructuredText;
class RscCheckbox;
class RscCombo;
class RscEdit;
class RscButton;

class VoxMod_ConfigMenu {
        idd = 618795;
        movingEnable = 1;
	enableSimulation = 1;
	fadeIn=0.2;
	fadeOut=0.2;
	duration = 10e10;
	name = "VoxMod_ConfigMenu";
        class Controls {

            class Frame: RscText {
                idc = -1;
                x = 0 * GUI_GRID_W + GUI_GRID_X;
                y = 0 * GUI_GRID_H + GUI_GRID_Y;
                w = 40 * GUI_GRID_W;
                h = 25 * GUI_GRID_H;
                colorBackground[] = {0,0,0,0.6};
	        };

            class Title: RscStructuredText {
                idc = 1000;
                text = "Enter VOX Below:";
                x = 1 * GUI_GRID_W + GUI_GRID_X;
                y = 1 * GUI_GRID_H + GUI_GRID_Y;
                w = 25 * GUI_GRID_W;
                h = 2.5 * GUI_GRID_H;
                colorBackground[] = {0,0,0,0.8};
            };

            class InputText: RscEdit {
                idc = 1001;
                style = 16;
		        text = "";
                lineSpacing = 1;
                sizeEx = 0.05;
                autocomplete = "general";
                x = 0 * GUI_GRID_W + GUI_GRID_X;
                y = 4 * GUI_GRID_H + GUI_GRID_Y;
                w = 40 * GUI_GRID_W;
                h = 17 * GUI_GRID_H;
                colorBackground[] = {0,0,0,0.8};
            };
            
            class Info: RscStructuredText {
                idc = 1002;
                text = "Emanate from module?";
                x = 0 * GUI_GRID_W + GUI_GRID_X;
                y = 21 * GUI_GRID_H + GUI_GRID_Y;
                w = 9 * GUI_GRID_W;
                h = 1 * GUI_GRID_H;
                colorBackground[] = {0,0,0,0.8};
            };

            class DistNum: RscEdit {
                idc = 1003;
		        text = "";
                x = 8 * GUI_GRID_W + GUI_GRID_X;
                y = 22 * GUI_GRID_H + GUI_GRID_Y;
                w = 3 * GUI_GRID_W;
                h = 1 * GUI_GRID_H;
                colorBackground[] = {0,0,0,0.8};
            };

            class Info2: RscStructuredText {
                idc = 1004;
                text = "Distance (EMANATE):";
                x = 0 * GUI_GRID_W + GUI_GRID_X;
                y = 22 * GUI_GRID_H + GUI_GRID_Y;
                w = 8 * GUI_GRID_W;
                h = 1 * GUI_GRID_H;
                colorBackground[] = {0,0,0,0.8};
            };

            class Info3: RscStructuredText {
                idc = 1005;
                text = "Volume (EMANATE):";
                x = 0 * GUI_GRID_W + GUI_GRID_X;
                y = 23 * GUI_GRID_H + GUI_GRID_Y;
                w = 8 * GUI_GRID_W;
                h = 1 * GUI_GRID_H;
                colorBackground[] = {0,0,0,0.8};
            };

            class VolNum: RscEdit {
                idc = 1006;
		        text = "";
                x = 8 * GUI_GRID_W + GUI_GRID_X;
                y = 23 * GUI_GRID_H + GUI_GRID_Y;
                w = 3 * GUI_GRID_W;
                h = 1 * GUI_GRID_H;
                colorBackground[] = {0,0,0,0.8};
            };

            class Info4: RscStructuredText {
                idc = 1007;
                text = "Pitch:";
                x = 0 * GUI_GRID_W + GUI_GRID_X;
                y = 24 * GUI_GRID_H + GUI_GRID_Y;
                w = 8 * GUI_GRID_W;
                h = 1 * GUI_GRID_H;
                colorBackground[] = {0,0,0,0.8};
            };

            class PitchNum: RscEdit {
                idc = 1008;
		        text = "";
                x = 8 * GUI_GRID_W + GUI_GRID_X;
                y = 24 * GUI_GRID_H + GUI_GRID_Y;
                w = 3 * GUI_GRID_W;
                h = 1 * GUI_GRID_H;
                colorBackground[] = {0,0,0,0.8};
            };

            class Info5: RscStructuredText {
                idc = 1009;
                text = "Optional setting:";
                x = 11 * GUI_GRID_W + GUI_GRID_X;
                y = 21 * GUI_GRID_H + GUI_GRID_Y;
                w = 8 * GUI_GRID_W;
                h = 1 * GUI_GRID_H;
                colorBackground[] = {0,0,0,0.8};
            };

            class CheckButton: RscButton {
                idc = 1600;
                text = "Check";
                x = 25 * GUI_GRID_W + GUI_GRID_X;
                y = 22 * GUI_GRID_H + GUI_GRID_Y;
                w = 3 * GUI_GRID_W;
                h = 2 * GUI_GRID_H;
                colorBackground[] = {0,0,0,0.8};
		        action = "[] call VoxMod_fnc_processText";
            };

            class OkButton: RscButton {
                idc = 1601;
                text = "Ok";
                x = 30 * GUI_GRID_W + GUI_GRID_X;
                y = 22 * GUI_GRID_H + GUI_GRID_Y;
                w = 3 * GUI_GRID_W;
                h = 2 * GUI_GRID_H;
                colorBackground[] = {0,0,0,0.8};
                action = "[ctrlText (findDisplay 618795 displayCtrl 1001), lbText [2100, lbCurSel (findDisplay 618795 displayCtrl 2100)], cbChecked (findDisplay 618795 displayCtrl 1603), VoxMod_Module, parseNumber (ctrlText (findDisplay 618795 displayCtrl 1003)), getPosASL VoxMod_Module, parseNumber (ctrlText (findDisplay 618795 displayCtrl 1006)), parseNumber (ctrlText (findDisplay 618795 displayCtrl 1008)), cbChecked (findDisplay 618795 displayCtrl 1604)] remoteExec [""VoxMod_fnc_playSoundSequence"", 0]";

            };

            class CloseButton: RscButton {
                idc = 1602;
                text = "Close";
                x = 35 * GUI_GRID_W + GUI_GRID_X;
                y = 22 * GUI_GRID_H + GUI_GRID_Y;
                w = 3 * GUI_GRID_W;
                h = 2 * GUI_GRID_H;
                colorBackground[] = {0,0,0,0.8};
		        action = "closeDialog 0; deleteVehicle VoxMod_Module";
            };

            class CheckBox: RscCheckbox {
                idc = 1603;
                x = 9 * GUI_GRID_W + GUI_GRID_X;
                y = 21 * GUI_GRID_H + GUI_GRID_Y;
                w = 1 * GUI_GRID_W;
                h = 1 * GUI_GRID_H;
                colorBackground[] = {0,0,0,0.8};
                checked = 0;
                textureChecked = "A3\Ui_f\data\GUI\RscCommon\RscCheckBox\CheckBox_checked_ca.paa";
                textureUnchecked = "A3\Ui_f\data\GUI\RscCommon\RscCheckBox\CheckBox_unchecked_ca.paa";
                textureFocusedChecked = "A3\Ui_f\data\GUI\RscCommon\RscCheckBox\CheckBox_checked_ca.paa";
                textureFocusedUnchecked = "A3\Ui_f\data\GUI\RscCommon\RscCheckBox\CheckBox_unchecked_ca.paa";
                textureHoverChecked = "A3\Ui_f\data\GUI\RscCommon\RscCheckBox\CheckBox_checked_ca.paa";
                textureHoverUnchecked = "A3\Ui_f\data\GUI\RscCommon\RscCheckBox\CheckBox_unchecked_ca.paa";
                texturePressedChecked = "A3\Ui_f\data\GUI\RscCommon\RscCheckBox\CheckBox_checked_ca.paa";
                texturePressedUnchecked = "A3\Ui_f\data\GUI\RscCommon\RscCheckBox\CheckBox_unchecked_ca.paa";
                soundEnter[] = {"", 0.1, 1};
                soundPush[] = {"", 0.1, 1};
                soundClick[] = {"", 0.1, 1};
                soundEscape[] = {"", 0.1, 1};
            };

            class CheckBox2: RscCheckbox {
                idc = 1604;
                x = 19 * GUI_GRID_W + GUI_GRID_X;
                y = 21 * GUI_GRID_H + GUI_GRID_Y;
                w = 1 * GUI_GRID_W;
                h = 1 * GUI_GRID_H;
                colorBackground[] = {0,0,0,0.8};
                checked = 1;
                textureChecked = "A3\Ui_f\data\GUI\RscCommon\RscCheckBox\CheckBox_checked_ca.paa";
                textureUnchecked = "A3\Ui_f\data\GUI\RscCommon\RscCheckBox\CheckBox_unchecked_ca.paa";
                textureFocusedChecked = "A3\Ui_f\data\GUI\RscCommon\RscCheckBox\CheckBox_checked_ca.paa";
                textureFocusedUnchecked = "A3\Ui_f\data\GUI\RscCommon\RscCheckBox\CheckBox_unchecked_ca.paa";
                textureHoverChecked = "A3\Ui_f\data\GUI\RscCommon\RscCheckBox\CheckBox_checked_ca.paa";
                textureHoverUnchecked = "A3\Ui_f\data\GUI\RscCommon\RscCheckBox\CheckBox_unchecked_ca.paa";
                texturePressedChecked = "A3\Ui_f\data\GUI\RscCommon\RscCheckBox\CheckBox_checked_ca.paa";
                texturePressedUnchecked = "A3\Ui_f\data\GUI\RscCommon\RscCheckBox\CheckBox_unchecked_ca.paa";
                soundEnter[] = {"", 0.1, 1};
                soundPush[] = {"", 0.1, 1};
                soundClick[] = {"", 0.1, 1};
                soundEscape[] = {"", 0.1, 1};
            };

            class DropdownMenu: RscCombo {
                idc = 2100;
                x = 28.5 * GUI_GRID_W + GUI_GRID_X;
                y = 1 * GUI_GRID_H + GUI_GRID_Y;
                w = 9.5 * GUI_GRID_W;
                h = 1 * GUI_GRID_H;
                colorBackground[] = {0,0,0,0.8};
		        onLoad = "_this call VoxMod_fnc_loadDropdownMenu";
            };
       };
 };

#include "CfgMusic.hpp"
#include "CfgSounds.hpp"