#include "stdafx.h"
#include "SettingsState.h"

void SettingsState::InitTextures()
{
	this->TextureManager["Mouse_Cursor"] = this->textures->at("texture4");
	

}

void SettingsState::InitVariables()
{
	this->videomodes = VideoMode::getFullscreenModes();
}

void SettingsState::InitButton(RenderWindow& window, shared_ptr<Font> font, Texture& texture)
{
	Vector2f buttonSize = { 300, 100 };
	const float PosX = 75.f;
	const int defaultY = 75;

	font = make_shared<Font>();
	Color Idle = Color(255, 255, 255);


	vector<string>modes;
	for (auto& i : videomodes)
	{
		modes.push_back(to_string(i.width) + " x " + to_string(i.height));
	}

	


	this->labels["Resolution"] = new Label(75, defaultY, 300, 100, this->font, "Resolution", this->texture, Color::White, 50.f);
	this->dropdownlists["Resolution"] = new DropDownList(window, this->font,
		this->texture, modes.data(), modes.size(), 0, defaultY , 50.f);

	this->fpslist = {to_string(this->gfxsettings.frameratelimit),"30","60","120","144", "165","240", "365", "Unlimited"};

	this->labels["FrameRate"] = new Label(75, defaultY + 100.f, 300, 100, this->font, "FrameRate", this->texture, Color::White, 50.f);
	this->dropdownlists["FrameRate"] = new DropDownList(window, this->font,
		this->texture, this->fpslist.data(), this->fpslist.size(), 0, defaultY + 100.f,  50.f);

	this->isFullscreen = { "off", "on"};

	this->labels["FullScreen"] = new Label(75, defaultY + 200.f, 300, 100, this->font, "FullScreen", this->texture, Color::White, 50.f);
	this->dropdownlists["FullScreen"] = new DropDownList(window, this->font,
		this->texture, this->isFullscreen.data(), this->isFullscreen.size(), 0, defaultY + 200.f, 50.f);

	this->verticalSync = { "off", "on" };
	this->labels["Vertical-Sync"] = new Label(75, defaultY + 300.f, 300, 100, this->font, "Vertical-Sync", this->texture, Color::White, 50.f);
	this->dropdownlists["Vertical-Sync"] = new DropDownList(window, this->font,
		this->texture, this->isFullscreen.data(), this->isFullscreen.size(), 0, defaultY + 300.f, 50.f);


	this->buttons["Quit"] = new Button(window.getSize().x - 300.f , window.getSize().y - 200.f, buttonSize.x, buttonSize.y, this->font, "Back",
		Idle, Color(172, 172, 172), Color(49, 153, 132), this->texture, 50.f);

	this->buttons["Apply"] = new Button(window.getSize().x - 550.f, window.getSize().y - 200.f, buttonSize.x, buttonSize.y, this->font, "Apply",
		Idle, Color(172, 172, 172), Color(49, 153, 132), this->texture, 50.f,false);

	
	

	

}

void SettingsState::InitBackround(RenderWindow& window, Texture &texture)
{
	this->Backround.setSize(Vector2f(this->window->getSize()));
	//this->Backround.setFillColor(Color(169, 91, 73));
	this->Backround.setTexture(&texture);
}





void SettingsState::InitKeybinds()
{
	this->keybinds["Exit_Settings"] = this->supportedkeys->at("Escape");
}




SettingsState::SettingsState(stateData* state_data
	, shared_ptr<Font>font, Texture& texture, map<string, Texture>* textures, map<string, Font>* Fonts, GfxSettings& gfx_settings) :
	State(state_data),
	StatesAssetManager(textures,Fonts), font(font), texture(texture), gfxsettings(gfx_settings)
	
{
	this->InitVariables();
	this->InitKeybinds();
	this->InitBackround(*window, this->texture);
	this->InitButton(*window, this->font, this->texture);
	this->InitTextures();
	this->ShowMouseCursor(true);

}

SettingsState::~SettingsState()
{
	
}

void SettingsState::UpdateKeys(const float& dt)
{
	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("Exit_Settings"))))
	{
		this->EndState();
	}

	if (this->buttons["Quit"]->IsPressed())
	{
		this->EndState();
	}

	else if (this->buttons["Apply"]->IsPressed())
	{
		stringstream iss;
		if (this->fpslist[this->dropdownlists["FrameRate"]->getId()] != "Unlimited")
		{
			iss << this->fpslist[this->dropdownlists["FrameRate"]->getId()];
			this->gfxsettings.frameratelimit = stoi(iss.str());
		}
		else
			this->gfxsettings.frameratelimit = 5000.f;
		if (this->verticalSync[this->dropdownlists["Vertical-Sync"]->getId()] == "off")
		{
			this->gfxsettings.vertical_sync = false;
		}
		else
		{
			this->gfxsettings.vertical_sync = true;
		}


		this->gfxsettings.ActiveResolution = this->videomodes[this->dropdownlists["Resolution"]->getId()];
		

		if (this->isFullscreen[this->dropdownlists["FullScreen"]->getId()] == "off")
		{
			this->gfxsettings.fullscreen = false;
			this->window->create(this->gfxsettings.ActiveResolution,
				this->gfxsettings.title, Style::Titlebar | Style::Close,this->gfxsettings.contextsettings);
			this->window->setFramerateLimit(this->gfxsettings.frameratelimit);
		}
		else
		{
			this->gfxsettings.fullscreen = true;
			this->window->create(this->gfxsettings.ActiveResolution,
				this->gfxsettings.title, Style::Fullscreen, this->gfxsettings.contextsettings);
			this->window->setFramerateLimit(this->gfxsettings.frameratelimit);
			
		}

		this->window->setFramerateLimit(static_cast<unsigned>(this->gfxsettings.frameratelimit));
		this->ShowMouseCursor(true);

		this->gfxsettings.SaveToFile("config/graphics.ini", this->gfxsettings);
	}

}

void SettingsState::updateButtons(const float &dt)
{
	for (const auto& e : this->buttons)
	{
		e.second->update(State::Mouse_pos(*this->window));
	}
	for (const auto& e : this->dropdownlists)
	{
		e.second->update(State::Mouse_pos(*this->window), dt);
	}
	
}

void SettingsState::update(const float &dt)
{
	this->SetFullScreen();
	this->updateButtons(dt);
	this->UpdateKeys(dt);
	this->updateKeytime(dt);
	this->calcFps(dt);
}

void SettingsState::render(RenderWindow* target)
{
	target->draw(this->Backround);

	for (const auto& e : this->buttons)
	{
		e.second->render(target);
	}
	for (const auto& e : this->dropdownlists)
	{
		e.second->render(target);
	}
	for (const auto& e : this->labels)
	{
		e.second->render(target);
	}

	
		
}
