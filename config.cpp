class CfgPatches
{
	class DayZ_WaterWorld_scripts
	{
		requiredAddons[] = {"DZ_Data"};
	};
};
class CfgMods
{
	class DayZ_WaterWorld
	{
		action = "";
		hideName = 0;
		hidePicture = 0;
		name = "WaterWorld";
		credits = "Dolphin";
		author = "Dolphin";
		authorID = "";
		version = "0.1";
		extra = 0;
		type = "servermod";
		dependencies[] = {"Game","World","Mission"};
		class defs
		{
			class missionScriptModule
			{
				value = "";
				files[] = {"dolphin/WaterWorld/Scripts/5_Mission"};
			};
		};
	};
};
