 #include "stdafx.h"
#include "MainMenuState.h"


void MainMenuState::InitFonts()
{
	//loading textures and passing them to a sprite object
	this->FontManager["Zelda_font"] = this->Fonts->at("font1");
}


void MainMenuState::InitTextures()
{
	

	this->TextureManager["Backround"] = this->textures->at("texture1");
	this->TextureManager["button"] = this->textures->at("texture3");
	this->TextureManager["LOGO"] = this->textures->at("texture2");
	this->TextureManager["Mouse_Cursor"] = this->textures->at("texture4");

	//assign sprite to textures or text to font 
	this->MouseCursor.setTexture(this->TextureManager["Mouse_Cursor"]);
	this->MouseCursor.setScale(0.6f, 0.6f);
	

	this->BackGround.setTexture(this->TextureManager["Backround"]);
	this->BackroundImageBounds.setSize(Vector2f(this->window->getSize()));
	this->BackroundImageBounds.setTexture(&this->TextureManager["Backround"]);
}


void MainMenuState::InitText()
{
	// Assuming this is inside a function where 'this->title' is an sf::Text object and 'this->window' is your sf::RenderWindow

// Set the font, character size, etc.
	this->title.setFont(this->FontManager["Zelda_font"]);
	this->title.setFillColor(sf::Color::White);
	this->title.setCharacterSize(180);
	this->title.setString("Haunt Hunt");
	this->title.setOutlineColor(Color::Black);
	this->title.setOutlineThickness(2);
	// Calculate the width of the text
	

}//texturesss

void MainMenuState::InitKeybinds()
{

	this->keybinds["Move_left"] = this->supportedkeys->at("A");
	this->keybinds["Move_right"] = this->supportedkeys->at("D");
	this->keybinds["Move_up"] = this->supportedkeys->at("W");
	this->keybinds["Move_down"] = this->supportedkeys->at("S");


	this->keybinds["Start"] = this->supportedkeys->at("Space");

}

void MainMenuState::InitButtons() {
	Vector2f buttonSize = { 300, 100 };
	auto centerX = this->window->getSize().x / static_cast<float>(2) - (buttonSize.x / 2);
	int defaultY = 400;

	centerX = 100.f;

	std::shared_ptr<Font> font = std::make_shared<Font>(this->FontManager["Zelda_font"]);
	Color Idle = Color(255, 255, 255);


	this->buttons["Game_state"] = new Button(centerX, defaultY, buttonSize.x, buttonSize.y, font, "Start Game",
		Idle, Color(172, 172, 172), Color(49, 153, 132), this->TextureManager["button"], 50.f);
	
	this->buttons["Settings"] = new Button(centerX, defaultY + 150, buttonSize.x, buttonSize.y, font, "Settings",
		Idle, Color(172, 172, 172), Color(49, 153, 132), this->TextureManager["button"],  50.f);

	this->buttons["Editor_State"] = new Button(centerX, defaultY + 300, buttonSize.x, buttonSize.y, font, "Tile Editor",
		Idle, Color(172, 172, 172), Color(49, 153, 132), this->TextureManager["button"],  50.f);

	this->buttons["Exit"] = new Button(centerX, defaultY + 450, buttonSize.x, buttonSize.y, font, "Exit Game",
		Idle, Color(172, 172, 172), Color(49, 153, 132), this->TextureManager["button"],  50.f);


	Texture temp;
	
	this->label = new Label(this->gfx_settings->ActiveResolution.width - 300.f, this->gfx_settings->ActiveResolution.height - 150.f,
		300, 100, font, "Dev Version", temp, Color::White, 35.f);
}

void MainMenuState::InitAudio()
{

	this->audioSystem = new AudioSystem();

	this->audioSystem->InitSound("low_hp_sound", "resources/audio/low_hp.wav", 45);
	this->audioSystem->InitSound("lamp_buzz", "resources/audio/lamp_buzz.wav", 100);
	this->audioSystem->InitSound("gun_shot", "resources/audio/gun_shot.wav", 80);
	this->audioSystem->InitSound("gun_equip", "resources/audio/gun_equip.wav", 80);
	this->audioSystem->InitSound("reload", "resources/audio/reload.wav", 80);
	this->audioSystem->InitSound("flashlight", "resources/audio/flashlight.wav", 80);
	this->audioSystem->InitSound("hit", "resources/audio/hit.wav", 80);
	this->audioSystem->InitSound("door_unlock", "resources/audio/door_unlock.wav", 80);
	this->audioSystem->InitSound("door_open", "resources/audio/door_open.wav", 80);
	this->audioSystem->InitSound("locked_door", "resources/audio/locked_door.wav", 80);
	this->audioSystem->InitSound("container_open", "resources/audio/cintainer_open.wav", 80);
	this->audioSystem->InitSound("footsteps", "resources/audio/footsteps.wav", 80);
	this->audioSystem->InitSound("door_closing", "resources/audio/door_closing.wav", 80);
	this->audioSystem->InitSound("lock_pick", "resources/audio/lockpick.wav", 80);
	this->audioSystem->InitSound("upgraded_gun", "resources/audio/upgraded_gun.wav", 80);
	this->audioSystem->InitSound("upgrade", "resources/audio/upgrade.wav", 80);
	this->audioSystem->InitSound("quake", "resources/audio/quake.wav", 80);
	this->audioSystem->InitSound("collapse", "resources/audio/build_collapse.wav", 80);
	this->audioSystem->InitSound("running", "resources/audio/running.wav", 80);
	this->audioSystem->InitSound("police", "resources/audio/police.wav", 80);

	this->audioSystem->InitTheme("normal_theme", "resources/audio/norma_theme.wav", 60);
	this->audioSystem->InitTheme("chase_theme", "resources/audio/chase_theme.wav", 40);
	this->audioSystem->InitTheme("boss_theme", "resources/audio/boss_theme.wav", 40);

	

	this->audioSystem->InitTheme("menu_theme", "resources/audio/menu_soundtrack.wav", 50);
	

	//lamp_buzz.wav

}




MainMenuState::MainMenuState(stateData* state_data, map<string, Texture>*textures, map<string, Font>* Fonts, GfxSettings& gfx_settings)
	: State(state_data), StatesAssetManager(textures,Fonts), gfxsettings(gfx_settings)
{

	this->InitText();
	this->InitTextures();
	this->InitKeybinds();
	this->InitFonts();
	this->InitButtons();
	this->InitAudio();
	
	this->Logo.setPosition(50, this->window->getSize().y - this->Logo.getGlobalBounds().height - 50);
	
	const float textWidth = this->title.getGlobalBounds().width;

	this->title.setOrigin(this->title.getGlobalBounds().width / 2.f, this->title.getGlobalBounds().height / 2.f);

		// Calculate the x-coordinate to position the text in the center of the window
	const float centerX = static_cast<float>(this->window->getSize().x) / 2.f;
		
		// Set the position of the text centered horizontally and vertically
	this->title.setPosition(this->title.getGlobalBounds().width- 200.f , this->title.getGlobalBounds().height);
	this->splashscreen = new SplashScreen(this->TextureManager["LOGO"], *this->window, this->gfxsettings.frameratelimit);
	this->window->setMouseCursorVisible(true);
	
	/*this->audioSystem->PlayTheme("menu_theme");*/
}

MainMenuState::~MainMenuState()
{
	for (const auto& e : this->buttons)
	{
		delete e.second;
	}
	

}

//ShowMouseCursor

void MainMenuState::EndState()
{
	if (this->buttons["Exit"]->IsPressed())
	{

		this->quit = true;
	}
}


void MainMenuState::UpdateKeys(const float& dt)
{
	this->audioSystem->PlayTheme("menu_theme");
	for (auto& e : this->buttons)
	{
		e.second->update(State::Mouse_pos(*this->window));
	}

	this->EndState();

	if (this->buttons["Game_state"]->IsPressed())
	{
		this->audioSystem->StopTheme("menu_theme");
		this->states->push(new GameState(this->stateDataPtr, this->textures, this->Fonts, this->gfxsettings
		, *this->audioSystem));
	}

	std::shared_ptr<Font> font = std::make_shared<Font>(this->FontManager["Zelda_font"]);
	if (this->buttons["Editor_State"]->IsPressed())
	{
		this->audioSystem->StopTheme("menu_theme");
		this->states->push(new EditorState(this->stateDataPtr, font, this->TextureManager["Backround"]
		,this->textures, this->Fonts, this->gfxsettings, *this->audioSystem));
	}

	
	if (this->buttons["Settings"]->IsPressed())
	{
		this->states->push(new SettingsState(this->stateDataPtr, font, this->TextureManager["Backround"]
			, this->textures, this->Fonts, this->gfxsettings));
	}
}





void MainMenuState::update(const float& dt)
{
	this->SetFullScreen();
	if (this->splashscreen->Quit())

	{
		this->UpdateKeys(dt);
		this->UpdateMosePos();
	}
	else
		this->splashscreen->update(dt);

}

void MainMenuState::render(RenderWindow* target)
{
	
		if (target == NULL)
			target = this->window;
		if (this->splashscreen->Quit())
		{

			target->draw(this->BackroundImageBounds);

			target->draw(this->title);
			this->label->render(target);
			

			for (const auto& e : this->buttons)
			{
				e.second->render(this->window);
			}

		}
		else
			this->splashscreen->render(*target);
}

	


