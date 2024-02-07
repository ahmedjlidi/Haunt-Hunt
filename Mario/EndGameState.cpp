#include "stdafx.h"
#include "EndGameState.h"


void EndGameState::InitTextures()
{

	this->TextureManager["button"] = this->textures->at("texture2");
	
}

void EndGameState::InitSounds()
{
	this->audio_system.InitSound("dead", "resources/audio/dead.wav", 60);


}

void EndGameState::InitFont()
{
	this->FontManager["font"] = this->Fonts->at("font1");
}

void EndGameState::InitKeybinds()
{

}

void EndGameState::InitText()
{
	this->texts["dead"] = new Text();
	this->texts["dead"]->setFont(this->FontManager["font"]);
	this->texts["dead"]->setCharacterSize(80.f);
	this->texts["dead"]->setOutlineThickness(2.f);
	this->texts["dead"]->setOutlineColor(Color::Black);
	this->texts["dead"]->setFillColor(Color(180, 24, 24));
	this->texts["dead"]->setString("You Died");
	this->texts["dead"]->setPosition
	(
		static_cast<float>(this->gfx_settings->ActiveResolution.width / 2.f) - (this->texts["dead"]->getGlobalBounds().width / 2.f),
		static_cast<float>(this->gfx_settings->ActiveResolution.height / 2.f) - (this->texts["dead"]->getGlobalBounds().height / 2.f + 400.f )
	);

}

void EndGameState::InitButtons()
{

	Vector2f buttonSize = { 300.f, 100.f };

	shared_ptr<Font> font = make_shared<Font>(this->FontManager["font"]);

	this->buttons["Quit"] = new Button(
		(this->gfx_settings->ActiveResolution.width / 2.f) - buttonSize.x / 2.f,
		this->gfx_settings->ActiveResolution.height - (buttonSize.y + 150.f), buttonSize.x, buttonSize.y, font, "Quit", Color(255, 255, 255)
		, Color(172, 172, 172), Color(49, 153, 132), this->TextureManager["button"], 50.f);

	this->buttons["restart"] = new Button(
		(this->gfx_settings->ActiveResolution.width / 2.f) - buttonSize.x / 2.f,
		this->gfx_settings->ActiveResolution.height - (buttonSize.y + 300.f), buttonSize.x, buttonSize.y, font, "Restart", Color(255, 255, 255)
		, Color(172, 172, 172), Color(49, 153, 132), this->TextureManager["button"], 50.f);
}




EndGameState::EndGameState(stateData* state_data,
	map<string, Texture>* textures, map<string, Font>* Fonts,
	GfxSettings& gfx_settings, AudioSystem& audio_system)
	: State(state_data), StatesAssetManager(textures, Fonts), audio_system(audio_system)
{
	
	this->InitSounds();
	this->InitTextures();
	this->InitKeybinds();
	this->InitFont();
	this->InitText();
	this->InitButtons();

	this->ShowMouseCursor(true);

	this->audio_system.playSound("dead");

}

EndGameState::~EndGameState()
{
	for (auto& e : this->texts)
		delete e.second;

	
}

void EndGameState::UpdateKeys(const float& dt)
{
	if (this->buttons["Quit"]->IsPressed())
	{
		this->states->pop();
		State::EndState();
	}
	else if (this->buttons["restart"]->IsPressed())
	{
		this->states->pop();
		this->states->push(new GameState(this->stateDataPtr, this->textures, this->Fonts, *this->gfx_settings
			, this->audio_system));
	}
}

void EndGameState::update(const float& dt)
{
	for (auto& e : this->buttons)
	{
		e.second->update(State::Mouse_pos(*this->window));
	}
	this->UpdateKeys(dt);
}

void EndGameState::render(RenderWindow* target)
{
	for (auto& e : this->buttons)
	{
		e.second->render(target);
	}
	target->draw(*this->texts["dead"]);
}
