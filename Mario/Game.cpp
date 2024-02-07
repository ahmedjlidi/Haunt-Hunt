#include "stdafx.h"
#include "Game.h"





void Game::InitGfxSettings()
{
	this->gfx_settings = new GfxSettings();
	this->gfx_settings->LoadFromFile("config/graphics.ini");


}

void Game::InitWindow()
{
	 if (this->gfx_settings->fullscreen)
	 {
		 this->window = new RenderWindow(this->gfx_settings->ActiveResolution
			 , this->gfx_settings->title, Style::Fullscreen ,this->gfx_settings->contextsettings);
	 }
	 else
		 this->window = new RenderWindow(this->gfx_settings->ActiveResolution
		,this->gfx_settings->title, Style::Titlebar | Style::Close, this->gfx_settings->contextsettings);
		 
	
	this->window->setFramerateLimit(this->gfx_settings->frameratelimit);
	this->window->setVerticalSyncEnabled(this->gfx_settings->vertical_sync);
}

void Game::InitVariables()
{
	this->GridSize = 100.f;

}


void Game::InitStateData()
{
	this->statedata.window = this->window;
	this->statedata.supportedkeys = &this->supportedKeys;
	this->statedata.states = &this->states;
	this->statedata.gridSize = this->GridSize;

}

void Game::InitStates()
{
	this->states.push(new MainMenuState(&this->statedata, &this->textures,&this->fonts,
		*this->gfx_settings));
	StatesAssetManager* states_asset_manager = new StatesAssetManager(&this->textures, &this->fonts);
}

void Game::InitKeys()
{
	ifstream file("config/Keybinds.ini");
	
	if (file.is_open())
	{
		string key = "";
		int key_num = 0;
		while(file >> key >> key_num)
		{
			this->supportedKeys[key] = key_num;

			
		}
	}
	else
	{
		throw( "Error opening keybinds.ini:: config/Keybinds.ini \n");
		
	}
	file.close();
}

void Game::InitTextures()
{

	const string modelPath = "resources/models/";
	const string MapPath = "resources/map/";
	const string Interface = "resources/interface/";
	this->texturePath = 
	{
	modelPath + "backround.jpg",modelPath + "arcadia.png"
	,modelPath + "button.png" , modelPath + "mouse_cursor.png", MapPath + "SHEET.png",
	MapPath + "tree.png", Interface + "hp_bar.png",  Interface + "pop.png",
	modelPath +"Sprite_sheet2.png", modelPath + "crosshair.png", modelPath +
		"herb.png",modelPath+ "magazine.png",Interface+"blood.png"
	};

	for (size_t i = 0; i < texturePath.size(); ++i)
	{
		shared_ptr<Texture> texture = make_unique<Texture>();
		if (!texture->loadFromFile(texturePath[i]))
		{
			
			throw("Error loading textures \n");
		}
		this->textures["texture" + std::to_string(i + 1)] = move(*texture);

	}


	const string FontPath = "resources/Fonts/";
	vector<string>FontPaths = { FontPath + "Unutterable-Regular.ttf"
	,FontPath + "Montserrat-Regular.ttf"};

	for (size_t i = 0; i < FontPaths.size(); ++i)
	{
		shared_ptr<Font> font = make_unique<Font>();
		if (!font->loadFromFile(FontPaths[i]))
		{

			throw("Error loading Fonts \n");
		}
		this->fonts["font" + std::to_string(i + 1)] = move(*font);

	}
}




Game::Game()
{
	this->InitGfxSettings();
	this->InitVariables();
	this->InitWindow();
	this->InitTextures();
	this->InitKeys();
	this->InitStateData();
	this->InitStates();
	
	
}

Game::~Game()
{
	delete this->window;

	while (this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}


void Game::updateDt()
{
	this->dt = dtClock.restart().asSeconds();
}

void Game::pollevent()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case Event::Closed:
			this->window->close();
			break;
		}
	}

}





const bool Game::IsRunning()
{
	return this->window->isOpen();
}



void Game::update()
{
	this->updateDt();
	if (!this->states.empty())
	{
		if (this->states.top()->getQuitStatus())
		{
			this->states.top()->EndState();
			delete this->states.top();
			this->states.pop();
		}
		else
			this->states.top()->update(this->dt);
	}
	else if (this->states.empty())
		this->window->close();
}



void Game::render()
{
	//clear window
	this->window->clear(Color::Black);

	//update window
	if (!this->states.empty())
	{
		this->states.top()->render(this->window);
	}
	
	//display  window
	this->window->display();

}

void Game::run()
{
	this->pollevent();
	this->update();
	this->render();
}

