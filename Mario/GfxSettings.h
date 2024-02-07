#pragma once
class GfxSettings
{
public:

	VideoMode ActiveResolution;
	bool fullscreen;
	bool vertical_sync;
	unsigned frameratelimit;
	ContextSettings contextsettings;
	vector<VideoMode>videomodes;
	string title;

	GfxSettings();
	

	void LoadFromFile(const string path);
	void SaveToFile(const string path, GfxSettings &gfxsettings);
	

};

