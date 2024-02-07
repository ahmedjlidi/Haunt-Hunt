#include "stdafx.h"
#include "GfxSettings.h"

GfxSettings::GfxSettings()
{
	this->videomodes = VideoMode::getFullscreenModes();
	this->title = "Haunt Hunt";
	this->ActiveResolution = VideoMode::getDesktopMode();
	this->frameratelimit = 120;
	this->vertical_sync = false;
	this->contextsettings.antialiasingLevel = 0;
	this->fullscreen = false;

}

void GfxSettings::LoadFromFile(const string path)
{
	ifstream file(path);
	if (file.is_open())
	{
		getline(file, this->title);
		file >> this->ActiveResolution.width >> ActiveResolution.height;
		file >> this->fullscreen;
		file >> this->frameratelimit;
		file >> this->vertical_sync;
		file >> this->contextsettings.antialiasingLevel;

	}
	else
		cout << "Error loading config file\n";

	file.close();
}

void GfxSettings::SaveToFile(const string path, GfxSettings& gfxsettings)
{
	ofstream outfile(path);
	if (outfile.is_open())
	{
		outfile << gfxsettings.title << "\n";
		outfile << gfxsettings.ActiveResolution.width<<" "<<gfxsettings.ActiveResolution.height<<"\n";
		outfile << gfxsettings.fullscreen << "\n";
		outfile << gfxsettings.frameratelimit << "\n";
		outfile << gfxsettings.vertical_sync << "\n";
		outfile << gfxsettings.contextsettings.antialiasingLevel << "\n";
	}
	else
	{
		cerr << "Error opening file for saving settings.\n";
	}
	outfile.close();
}


