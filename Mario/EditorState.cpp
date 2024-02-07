#include "stdafx.h"
#include "EditorState.h"



void EditorState::InitView(GfxSettings& gfx_settings)
{
	this->view.setSize(Vector2f
	(
		gfx_settings.ActiveResolution.width,
		gfx_settings.ActiveResolution.height)
	);

	this->view.setCenter
	(
		gfx_settings.ActiveResolution.width / 2.f,
		gfx_settings.ActiveResolution.height / 2.f
	);


}

void EditorState::InitVariables()
{
	this->Collision = false;
	this->type = TileTypes::DEFAULT;
	this->CameraSpeed = 800.f;
	this->hasReachedTheEndOfTheMap = true;
}

void EditorState::InitTextures()
{
	//inisialize all textures using derived class statesAssetmanager

	this->TextureManager["texture_sheet"] = this->textures->at("texture5");
	//this->TextureManager["test"] = this->textures->at("texture6");
	this->FontManager["Mouse_Text"] = this->Fonts->at("font2");
}

void EditorState::InitTextureRect()
{
	//give a default value for texture rect which will choose the first texture in the texturesheet
	this->TextureRect = IntRect(0, 0,
		static_cast<int>(this->stateDataPtr->gridSize),
		static_cast<int>(this->stateDataPtr->gridSize));

}

void EditorState::InitGui()
{
	//inisialize visual things in the editor state. if they require parameters 
	//they will be insialized directly in the constructor
	//here selector rec is being inisialized
	this->selector.setSize(Vector2f(this->stateDataPtr->gridSize, this->stateDataPtr->gridSize));
	this->selector.setFillColor(Color::Transparent);
	this->selector.setOutlineThickness(1);
	this->selector.setOutlineColor(Color::Green);
}

void EditorState::InitText()
{
	stringstream iss;
	iss << State::Mouse_pos(*this->window).x << "\n";
	iss << State::Mouse_pos(*this->window).y << "\n";

	this->info.setFont(this->FontManager["Mouse_Text"]);
	this->info.setCharacterSize(14);
	this->info.setFillColor(Color::White);
	this->info.setString(iss.str());
}







void EditorState::InitKeybinds()
{
	//inisialize all keybinds needed and give them names

	//Pause Menu
	this->keybinds["Pause"] = this->supportedkeys->at("Escape");

	//Tile Editing
	this->keybinds["cycle_texture"] = this->supportedkeys->at("Space");
	this->keybinds["toggle_showPreview"] = this->supportedkeys->at("Tab");
	this->keybinds["toggle_showTexture_selector"] = this->supportedkeys->at("LShift");
	this->keybinds["toggle_Enable_Collision"] = this->supportedkeys->at("C");
	this->keybinds["toggle_Cycle_Type"] = this->supportedkeys->at("T");
	this->keybinds["Delete_Map"] = this->supportedkeys->at("X");
	this->keybinds["Lock_tile"] = this->supportedkeys->at("L");
	this->keybinds["change_door_type"] = this->supportedkeys->at("LControl");


	//camera view Keybinds
	this->keybinds["Move_View_Left"] = this->supportedkeys->at("D");
	this->keybinds["Move_View_Right"] = this->supportedkeys->at("A");
	this->keybinds["Move_View_Up"] = this->supportedkeys->at("W");
	this->keybinds["Move_View_Down"] = this->supportedkeys->at("S");
	this->keybinds["Reset_Camera_View"] = this->supportedkeys->at("R");
}



EditorState::EditorState(stateData* state_data, shared_ptr<Font> font, Texture& texure, 
	map<string, Texture>* textures, map<string, Font>* Fonts, GfxSettings& gfx_settings, AudioSystem& audio_system)
	: State(state_data), StatesAssetManager(textures, Fonts), font(font), texture(texture), audio_system(audio_system)
{
	//constructor all default values are being inislaized init == inisialize
	this->InitView(gfx_settings);
	this->InitVariables();
	this->InitKeybinds();//initkeybinds
	this->InitTextures();//initextures
	this->InitText();
	this->InitTextureRect();//initexturerect
	

	this->pausemenu = new PauseMenu(*this->window, this->font, this->texture);//add a pause menu
	this->pausemenu->AddButton(*this->window, this->font, this->texture,
		300.f, 100.f,300.f, 50.f, "Save", "Save");
	this->pausemenu->AddButton(*this->window, this->font, this->texture,
		300.f, 100.f, 450.f, 50.f, "Load", "Load");

	this->ShowMouseCursor(true);//showmouse cursor
	
	//add new tilemap
	this->tile_map = new TileMap(state_data->gridSize, 100, 100, this->TextureManager["texture_sheet"]);

	//positions for the preview screen
	{
		float PosX = this->window->getSize().x - 250;
		float PosY = 0;

		float width = 250;
		float height = 450;

		//add new texturepreview window
		this->texture_preview = new TexturePreview(*this->window, this->TextureManager["texture_sheet"]
			, this->TextureRect, this->stateDataPtr->gridSize, PosX
			, PosY, width, height);
		this->InitGui();

		//add new button called show texture
		
		this->font = make_shared<Font>(this->FontManager["Mouse_Text"]);

		this->buttons["Show_texture"] = new Button(PosX + 50, PosY  + height / 1.5f, 150.f, 100.f, this->font, "Texture Picker",
			Color(255, 255, 255), Color(172, 172, 172), Color(49, 153, 132), this->TextureManager["button"]
			, 25.f);
	}

	this->texture_selector = new TextureSelector(this->tile_map->getTextureSheet(),
		Color(50, 50, 50, 100),this->stateDataPtr->gridSize, 2300.f, 1700.f , 20.f, 20.f);


	
	
	
}

EditorState::~EditorState()
{
	//destructor to deallocate all uneeded memory
	delete this->pausemenu;
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
	delete this->tile_map;

	delete this->texture_selector;

	this->ShowMouseCursor(true);

	this->audio_system.PlayTheme("menu_theme");
}

void EditorState::ChooseTexture(float Maxheight, float Maxwidth)
{
	//choose texture button logic where it decides which texture to choose
	//require to give it max height and width of the texturesheet
	//cycle through textures by either pressing cycle texture key or pressing the button
	if ((Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("cycle_texture"))) && this->getKeyTime())
		 && this->getKeyTime() && !this->HideTexturePreview)
	{
		if (this->TextureRect.width < Maxwidth)
		{
			this->TextureRect.left += this->stateDataPtr->gridSize;
			this->TextureRect.width += this->stateDataPtr->gridSize;
		}
		else if (this->TextureRect.height < Maxheight)
		{
			this->TextureRect.left = 0;
			this->TextureRect.width = this->stateDataPtr->gridSize;
			this->TextureRect.top += this->stateDataPtr->gridSize;
			this->TextureRect.height += this->stateDataPtr->gridSize;
		}
		else
		{
			this->TextureRect = IntRect(0, 0,
				static_cast<int>(this->stateDataPtr->gridSize),
				static_cast<int>(this->stateDataPtr->gridSize));
				
		}
	}


	
}

bool EditorState::AllowEditing()
{
	return (!texture_preview->GetPreviewScreenPos().getGlobalBounds().contains(State::Mouse_pos(*this->window))
		|| this->HideTexturePreview);
}

void EditorState::SaveTileMap()
{
	
}

void EditorState::UpdateKeys(const float& dt)
{
	//this function should ve been called update input since it updates all the input related to
	//editor state (not previewscreen)
	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("Pause"))) &&
		this->getKeyTime())
	{
		//if pause key is pressed check if paused is true or false, if true then false and vice versa
		if (!this->pause)
		{
			this->PauseState();
		}
		else
		{
			this->UnPauseState();

		}
	}
	//update the choosetexture since texturerect will change based or user input
	//(if he changed texture)
	this->ChooseTexture(100,200);

	//if mouse left is pressed and mouse cooldown is over and mouse is not overlapping preview screen
	//or preview screen is hidden, then add a tile
	if (Mouse::isButtonPressed(Mouse::Left)
	&& (this->AllowEditing()) &&
		!this->texture_selector->TextureSelectorIsActive() &&
		this->getKeyTime() && !this->SpriteSelectorIsActive)
	{
		if (this->lockTile)
		{
			if (this->tile_map->empty(this->MousePosGrid.x, this->MousePosGrid.y, 0))
			{
				this->tile_map->addTile(this->MousePosGrid.x, this->MousePosGrid.y, 0,
					this->TextureRect, this->Collision, this->type);
			}
			if (this->type == TileTypes::PlayerSpawn)
			{
				this->tile_map->addSpawnPosition(Vector2f(static_cast<float>(this->MousePosGrid.x) * gridSize
					, static_cast<float>(this->MousePosGrid.y) * gridSize));
			}
		}
		else
			this->tile_map->addTile(this->MousePosGrid.x, this->MousePosGrid.y, 0,
				this->TextureRect, this->Collision, this->type);

		if (this->type == TileTypes::DOOR)
		{
			this->tile_map->addDoor(Vector2f(static_cast<float>(this->MousePosGrid.x) * gridSize
				, static_cast<float>(this->MousePosGrid.y) * gridSize), this->doorType);
		}
	}

	//with right mouse and cooldown is over, remove a tile
	else if (Mouse::isButtonPressed(Mouse::Right) && this->getKeyTime()
		&& !this->texture_selector->TextureSelectorIsActive() && !this->SpriteSelectorIsActive)
	{
		this->tile_map->removeTile(this->MousePosGrid.x, this->MousePosGrid.y, 0);

		if (this->lockTile)
		{
			if (this->type == TileTypes::PlayerSpawn)
			{
				this->tile_map->deleteSpawnPosition(Vector2f(static_cast<float>(this->MousePosGrid.x) * gridSize
					, static_cast<float>(this->MousePosGrid.y) * gridSize));
			}
			else if (this->type == TileTypes::DOOR)
			{
				this->tile_map->DeleteDoor(Vector2f(static_cast<float>(this->MousePosGrid.x) * gridSize
					, static_cast<float>(this->MousePosGrid.y) * gridSize));
			}

		}
	}


	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds["toggle_Enable_Collision"]))
		&& this->getKeyTime())
	{
		if (this->Collision)
			this->Collision = false;
		else
			this->Collision = true;

	}
	else if(Keyboard::isKeyPressed(Keyboard::Key(this->keybinds["toggle_Cycle_Type"]))
		&&this->getKeyTime())
	{
		if (this->type > 8)
		{
			this->type = 0;
		}
		else
			++this->type;
	}

	else if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds["Delete_Map"]) )
		&& this->getKeyTime() && !this->SpriteSelectorIsActive)
	{
		this->tile_map->DeleteMap();
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds["Lock_tile"]))
		&& this->getKeyTime() && !this->SpriteSelectorIsActive)
	{
		if (this->lockTile)
			this->lockTile = false;
		else
			this->lockTile = true;

	}
	else if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds["change_door_type"]))
		&& this->getKeyTime() && !this->SpriteSelectorIsActive)
	{
		if (this->doorType > DoorType::ENEMY_DEPEND)
		{
			this->doorType = DoorType::NORMAL;
		}
		else
			++this->doorType;
	}



	//Camera View
	
	 

	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds["Move_View_Left"])))
	{
		this->view.move(this->CameraSpeed * dt, 0);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds["Move_View_Right"])))
	{
		this->view.move(-this->CameraSpeed * dt, 0);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds["Move_View_Up"])))
	{
		if (this->MosPosView.y > 0)
		{
			this->view.move(0.f, -this->CameraSpeed * dt);
			this->hasReachedTheEndOfTheMap = false;
		}
		else
			this->hasReachedTheEndOfTheMap = true;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds["Move_View_Down"])))
	{
		this->view.move(0.f, this->CameraSpeed * dt);
	}

	else if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds["Reset_Camera_View"])))
	{
		this->view.setCenter(this->window->getSize().x / 2.f, this->window->getSize().y / 2.f);
	}

}

void EditorState::updatePreviewScreen()
{
	//update preview screen by passing texture rect and giving its texture to the preview tile
	this->texture_preview->update(this->TextureRect);
	//if toggle preview is pressed and keyboard presses are allowed, update the visibilty

	this->texture_preview->updateVisibilty(this->keybinds["toggle_showPreview"],
		this->AllowKeyboardPress(this->keybinds["toggle_showPreview"]), this->HideTexturePreview);
}

void EditorState::EndState()
{

}


void EditorState::updateGUI()
{
	//update the selector position, make it snappy by multiplying it with grid size
	
	this->selector.setPosition(this->MousePosGrid.x * this->stateDataPtr->gridSize
			,this->MousePosGrid.y * this->stateDataPtr->gridSize);
	
	
	this->texture_selector->update(State::Mouse_pos(*this->window), this->TextureRect, this->AllowMouse("left"));
	
	if (!this->HideTexturePreview)
	{
		this->texture_selector->show(this->buttons["Show_texture"]->IsPressed() && this->getKeyTime());
	}
	
	
}

void EditorState::updateTextPosition()
{
	this->info.setPosition(this->MosPosView.x + 15, this->MosPosView.y - 20);
	stringstream iss;
	iss <<"X: "<< this->MosPosView.x << "\n";
	iss <<"Y: "<< this->MosPosView.y << "\n";
	iss << "Grid X: " << this->MousePosGrid.x << "\n";
	iss << "Grid Y: " << this->MousePosGrid.x << "\n";
	iss << "Collision: " << this->Collision << "\n";
	switch (this->type)
	{
	case TileTypes::DEFAULT:
		iss << "Type: " << "Default" << "\n";
		break;
	case TileTypes::DAMAGING:
		iss << "Type: " << "Slow" << "\n";
		break;
	case TileTypes::OverLap:
		iss << "Type: " << "OverLap" << "\n";
		break;
	case TileTypes::Chest:
		iss << "Type: " << "Chest" << "\n";
		break;
	case TileTypes::PlayerSpawn:
		iss << "Type: " << "PlayerSpawn" << "\n";
		break;
	case TileTypes::ENEMYSPAWN:
		iss << "Type: " << "EnemySpawn" << "\n";
		break;
	case TileTypes::DOOR:
		iss << "Type: " << "Door" << "\n";
		iss << "Door Type: ";
		switch (this->doorType)
		{
		case 0:
			iss << "Normal door\n";
			break;
		case 1:
			iss << "Locked door\n";
			break;
		case 2:
			iss << "Special door\n";
			break;
		case 3:
			iss << "Cyrstal required\n";
			break;
		}
		break;
	case TileTypes::LIGHT:
		iss << "Type: " << "Light" << "\n";
		break;

	case TileTypes::KEY_CONTAINER:
		iss << "Type: " << "key Container" << "\n";
		break;
	case TileTypes::LETTER:
		iss << "Type: " << "Leter" << "\n";
		break;
	}
	
	iss << "Lock tile: " << this->lockTile << "\n";

	this->info.setString(iss.str());
}

void EditorState::update(const float& dt)
{
	//if pause menu is not click on update editor state
	this->SetFullScreen();
	if (!this->pause)
	{
		this->UpdateKeys(dt);
		this->updateKeytime(dt);
		this->UpdateMosePos(&this->view);
		this->EndState();
		this->updateGUI();
		this->updatePreviewScreen();
		this->updateTextPosition();
		for (auto& e : this->buttons)
		{
			e.second->update(State::Mouse_pos(*this->window));
		}

		
		
		
	}
	else
	{
		//update pause menyu stuff (mouse cursor, mouse cooldown, button preseed..)
		this->updateKeytime(dt);
		this->updateMouseCursor();
		this->pausemenu->update(State::Mouse_pos(*this->window));
		if (this->pausemenu->Quit() && this->getKeyTime())
			this->window->close();
		else if (this->pausemenu->GetResumeStatus() && this->getKeyTime())
		{
			this->UnPauseState();
		}
		else if (this->pausemenu->GoToMenu() && this->getKeyTime())
		{
			this->ShowMouseCursor(false);
			State::EndState();
			
		}
		if (this->pausemenu->GetButton("Save")->IsPressed() && this->getKeyTime())
		{
			this->tile_map->saveMap("Map.slmp");
			
		}
		if (this->pausemenu->GetButton("Load")->IsPressed() && this->getKeyTime())
		{
			this->tile_map->LoadMap("Map.slmp");
		}

		
	}
		
}

void EditorState::render(RenderWindow* target)
{
	//if target is null assign it to window
	if (target == NULL)
		target = this->window;

	else
	{
		target->setView(this->view);
		this->tile_map->render(*target,nullptr, true);
		this->tile_map->renderOverlappingTiles(*target);

		for (const auto &e : this->CustomSprites)
		{
			target->draw(*e);
		}

		if (!this->pause)
		{
			

			target->setView(this->window->getDefaultView());
			this->texture_preview->render(*target, this->SpriteSelectorIsActive);
			this->texture_selector->renderTextureSelectorWindow(*target);
			
			if (!texture_preview->GetPreviewScreenPos().getGlobalBounds().contains(State::Mouse_pos(*this->window))
				|| this->HideTexturePreview)
			{
				if (!this->texture_selector->TextureSelectorIsActive())
				{
					target->setView(this->view);
					target->draw(this->selector);
					target->draw(this->info);

				}
				else
					this->texture_selector->renderSelector(*target);

			}

			target->setView(this->window->getDefaultView());



			if (!this->HideTexturePreview)
			{
				for (const auto& e : this->buttons)
				{
					e.second->render(this->window);
				}
			}


		}
		else
		{
			target->setView(this->window->getDefaultView());
			this->pausemenu->render(target);
			this->renderMouseCursor(target);
		}
	}
}
