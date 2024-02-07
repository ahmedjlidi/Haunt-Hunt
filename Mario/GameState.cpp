#include "stdafx.h"
#include "GameState.h"


void GameState::InitLight(GfxSettings& gfx_settings)
{
	this->AmbientLighting.setSize(Vector2f(gfx_settings.ActiveResolution.width,
		gfx_settings.ActiveResolution.height));
	this->AmbientLighting.setFillColor(Color(85, 32, 100, 50));
	
}

void GameState::InitView(GfxSettings& gfx_settings)
{
	this->view.setSize(Vector2f
	(
		floor(gfx_settings.ActiveResolution.width),
		floor(gfx_settings.ActiveResolution.height))
	);

	this->view.setCenter
	(
		gfx_settings.ActiveResolution.width ,
		gfx_settings.ActiveResolution.height 
	);

}

void GameState::InitRenderArea(GfxSettings& gfx_settings)
{
	this->renderTexture.create
	(
		gfx_settings.ActiveResolution.width
	,   gfx_settings.ActiveResolution.height
	);


	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect
	(IntRect
	(
		0,
		0,
		gfx_settings.ActiveResolution.width,
		gfx_settings.ActiveResolution.height
	)
	);
}

void GameState::InitShader()
{
	if (!this->core_shader.loadFromFile("vertex_shader.vert", "fragment_shader.frag"))
	{
		throw"Could not load shader\n";
	}

	
}

void GameState::InitKeybinds()
{
	this->keybinds["Move_left"] = this->supportedkeys->at("A");
	this->keybinds["Move_right"] = this->supportedkeys->at("D");
	this->keybinds["Move_up"] = this->supportedkeys->at("W");
	this->keybinds["Move_down"] = this->supportedkeys->at("S");

	this->keybinds["Start"] = this->supportedkeys->at("Space");
	this->keybinds["Pause"] = this->supportedkeys->at("Escape");
	this->keybinds["Equip_Item1"] = this->supportedkeys->at("Num1");
	this->keybinds["Equip_Item2"] = this->supportedkeys->at("Num2");
	this->keybinds["Equip_Item3"] = this->supportedkeys->at("Num3");
	this->keybinds["Equip_Item4"] = this->supportedkeys->at("Num4");
	this->keybinds["Equip_Item5"] = this->supportedkeys->at("Num5");
	this->keybinds["Equip_Item6"] = this->supportedkeys->at("Num6");
	this->keybinds["Equip_Item7"] = this->supportedkeys->at("Num7");
	this->keybinds["Equip_Item8"] = this->supportedkeys->at("Num8");
	this->keybinds["Use"] = this->supportedkeys->at("E");


	this->keybinds["change_spawn_position"] = this->supportedkeys->at("C");
}

void GameState::InitSounds()
{
	this->audio_system.Init3dSound("lamp_buzz", this->player->getPosition(),
		this->tile_map->LightPositions(), 100.f);
}

void GameState::loadDialogueText()
{
	/*Intro Dialogue*/
	{
		this->dialogues["Intro_dialogue"].push_back
		("My name is John Harris, an Investigator with the Paranomal Investigation Division.\n"
			"I have spent years delving into mysterious cases, and my current assignment\n has led me the this eepy village");

		this->dialogues["Intro_dialogue"].push_back
		("Missing pepole have been reported lately. All evidence has guided me to this isolated house\n");

		this->dialogues["Intro_dialogue"].push_back
		("This is the place. It doesn't look welcoming, but I need to find out what happened to those missing folks.\n");

		this->dialogues["Intro_dialogue"].push_back
		("Door opening sound*\n");

		this->dialogues["Intro_dialogue"].push_back
		("FlashLight sound*\n");

		this->dialogues["Intro_dialogue"].push_back
		("Hello, Anybody here? I have warrant to seach this house.\n");

		this->dialogues["Intro_dialogue"].push_back
		("Door Closing*\n");

		this->dialogues["Intro_dialogue"].push_back
		("What was That!?\n");

		this->dialogues["Intro_dialogue"].push_back
		("I am agent Harris, n Investigator with the Paranomal Investigation Division\n"
			"I have warrant to seach this house, Put down any weapons and follow my instructions ");

		this->dialogues["Intro_dialogue"].push_back
		("No answer*");

		this->dialogues["Intro_dialogue"].push_back
		("A chill runs down my spine. This place... it's suffocating. I'm not comfortable being here; something doesn't feel right.\n"
			"However, I must continue my investigation\n");

	}

	/*Enemy encounter*/
	this->dialogues["enemy_encounter"].push_back("Who is that woman?!!!");

	this->dialogues["enemy_encounter"].push_back("It's too dark i cant see her face");

	this->dialogues["enemy_encounter"].push_back("Mam, I am with the PID \n please step forward so i can see your face");

	/*after_seeing_enemy*/
	{
		this->dialogues["after_seeing_enemy"].push_back("What was that creature?!!!!!");
		this->dialogues["after_seeing_enemy"].push_back("That was not a Human.");
		this->dialogues["after_seeing_enemy"].push_back("This house is not normal. I must find out way out before something bad happen");
	}


	/*realization*/
	{
		this->dialogues["realization"].push_back("No... this can't be real. Those creatures were... people?");
		this->dialogues["realization"].push_back("Aggression, markings... it all makes sense now. What have I stumbled into?");
		this->dialogues["realization"].push_back("Who could have done this?!");
		this->dialogues["realization"].push_back("What is this? a weird looking key\n");
		this->dialogues["realization"].push_back("I need to be cautious, find a way out, and uncover the truth behind this madness.");
		this->dialogues["realization"].push_back("What is that sound?");
		this->dialogues["realization"].push_back("Damn it, the house is collapsing. This is the last door, i can see the exit there\n");
	}

	{
		this->dialogues["boss_meet"].push_back("Do you really think you can run away after you have found my secret\n");
		this->dialogues["boss_meet"].push_back("So you are the one responsible for all of this\nHow dare you sacrifice these innocent lives for your crazy experiments\n");
		this->dialogues["boss_meet"].push_back("HaHa. Mr.Harris, your tiny mind cannot comprehend my goals");
		this->dialogues["boss_meet"].push_back("From the moment i understood the weakness of my flesh, it disgusted me\nI craved the stregth and certainy");
		this->dialogues["boss_meet"].push_back("your kind cling to your flesh as if it will not decay and fail you");
		this->dialogues["boss_meet"].push_back("the curse biomass that you call a temple will with you, and you will beg me to save you");
		this->dialogues["boss_meet"].push_back("Your bullshit and ends here ");
		this->dialogues["boss_meet"].push_back("We'll see about that ");
	}

	{
		this->dialogues["boss_killed"].push_back("You're madness ends here\n");
		this->dialogues["boss_killed"].push_back("No don't leave me here, i can help you. I can give you the power and strength you' ve always wanted \n");
		this->dialogues["boss_killed"].push_back("You and your sins shall all be burried under this house\n");
		this->dialogues["boss_killed"].push_back("Nooo, come back now!!!!\n");
		this->dialogues["boss_killed"].push_back("*Running");
		this->dialogues["boss_killed"].push_back("*Build collapse");

		this->dialogues["boss_killed"].push_back("*police cars");
		this->dialogues["boss_killed"].push_back("Mr Haris! Are you ok?");
		this->dialogues["boss_killed"].push_back("Yeah, well, barely");
		this->dialogues["boss_killed"].push_back("What happened to this house");
		this->dialogues["boss_killed"].push_back("It's long story, let's discuss it tomorrow");
		this->dialogues["boss_killed"].push_back("The End");
	}

	for (auto& e : this->dialogues)
	{
		reverse(e.second.begin(),  e.second.end());
	}

}


void GameState::InitTextures()
{

	this->TextureManager["Mouse_Cursor"] = this->textures->at("texture4");
	this->TextureManager["crosshair"] = this->textures->at("texture10");
	this->TextureManager["texture_sheet"] = this->textures->at("texture5");
	this->TextureManager["hp-bar"] = this->textures->at("texture7");
	this->TextureManager["pop_backround"] = this->textures->at("texture8");
	this->TextureManager["PLAYER_SHEET"] = this->textures->at("texture9");
	this->TextureManager["herb"] = this->textures->at("texture11");
	this->TextureManager["magazine"] = this->textures->at("texture12");
	this->TextureManager["blood_overlay"] = this->textures->at("texture13");

}
void GameState::InitFont()
{
	this->FontManager["Zelda_font"] = this->Fonts->at("font1");
	this->FontManager["Hp_Bar_Text"] = this->Fonts->at("font2");
	this->FontManager["fps_text"] = this->Fonts->at("font2");

}


void GameState::InitMap()
{
	this->tile_map = new TileMap(this->stateDataPtr->gridSize, 100, 100,
		this->TextureManager["texture_sheet"]);

	this->tile_map->LoadMap("Map.slmp");
}




void GameState::InitPlayer()
{
	const float x = this->tile_map->getPlayerSpawnPosition(PLAYERSPAWNPOS::START_ROOM).x;
	const float y = this->tile_map->getPlayerSpawnPosition(PLAYERSPAWNPOS::START_ROOM).y;
	this->player = new Player(x, y, this->TextureManager["PLAYER_SHEET"]);
}

void GameState::InitEnemySpawner()
{
	this->enemySpawner = new EnemySpawner(this->tile_map->getEnemySpawnPosition(), Vector2f(2500.f, 2000.f), 2.f);
}

void GameState::InitHpBar()
{
	this->hp_bar = new playerGui::HpBar(70.f, 40.f
		,this->TextureManager["hp-bar"],
		this->FontManager["Zelda_font"], "HP: ", Color::Green);
}

void GameState::InitPauseMenu()
{
	this->fontt = std::make_shared<Font>(this->FontManager["Zelda_font"]);
	pausemenu = new PauseMenu(*this->window, fontt, this->Gtextures["PLAYER_SHEET"]);



}

void GameState::InitPopUpText()
{
	this->popuptext = make_shared<PopUpText>(this->FontManager["Zelda_font"], 25.f, 4.f);
}

void GameState::InitItemPreview()
{
	this->itempreview = new playerGui::ItemPreview(
		Vector2f(100.f, 70.f),
		Vector2f(20.f, 120.f),
		2,
		Color::White,
		this->player->getCurrentItemTexture(), this->FontManager["Zelda_font"]
	);

}

void GameState::InitDialogueWindow()
{

	shared_ptr<Font>font = make_shared<Font>(this->FontManager["Zelda_font"]);

	//Intro Dialogue
	/*{

		for (auto it = this->dialogues["Intro"].begin(); it != --this->dialogues["Intro"].end();)
		{
			const auto& line = *it;
			this->dialogue_windows["Intro_dialogue"].push(new DialogueWindow(Vector2f(this->gfx_settings->ActiveResolution.width,
				this->gfx_settings->ActiveResolution.height), Vector2f(this->gfx_settings->ActiveResolution.width / 2.f - 100.f
					, 200), 25.f, font, "insert text here", this->TextureManager["pop_backround"],
				Vector2f(this->gfx_settings->ActiveResolution.width, this->gfx_settings->ActiveResolution.height)));

			this->dialogue_windows["Intro_dialogue"].top()->setDialogue(line, *this->window);

			it = this->dialogues["Intro"].erase(it);;
		}


		this->dialogue_windows["Intro_dialogue"].push(new DialogueWindow(Vector2f(this->gfx_settings->ActiveResolution.width,
			this->gfx_settings->ActiveResolution.height), Vector2f(this->gfx_settings->ActiveResolution.width / 2.f - 100.f
				, 200), 25.f, font, "insert text here", this->TextureManager["pop_backround"],
			Vector2f(this->gfx_settings->ActiveResolution.width, this->gfx_settings->ActiveResolution.height)));

		this->dialogue_windows["Intro_dialogue"].top()->setDialogue(this->dialogues["Intro"][this->dialogues.size() - 1], *this->window);
		this->dialogue_windows["Intro_dialogue"].top()->setActive(true);
	}*/

	for (auto& e : this->dialogues)
	{
		const string dialogue_name = e.first;
		for (auto it = this->dialogues[dialogue_name].begin(); it != this->dialogues[dialogue_name].end() - 1;)
		{
			const auto& line = *it;
			this->dialogue_windows[dialogue_name].push(new DialogueWindow(Vector2f(this->gfx_settings->ActiveResolution.width,
				this->gfx_settings->ActiveResolution.height), Vector2f(this->gfx_settings->ActiveResolution.width / 2.f - 100.f
					, 200), 25.f, font, "insert text here", this->TextureManager["pop_backround"],
				Vector2f(this->gfx_settings->ActiveResolution.width, this->gfx_settings->ActiveResolution.height)));

			this->dialogue_windows[dialogue_name].top()->setDialogue(line, *this->window);

			it = this->dialogues[dialogue_name].erase(it);
		}

		this->dialogue_windows[dialogue_name].push(new DialogueWindow(Vector2f(this->gfx_settings->ActiveResolution.width,
			this->gfx_settings->ActiveResolution.height), Vector2f(this->gfx_settings->ActiveResolution.width / 2.f - 100.f
				, 200), 25.f, font, "insert text here", this->TextureManager["pop_backround"],
			Vector2f(this->gfx_settings->ActiveResolution.width, this->gfx_settings->ActiveResolution.height)));

		this->dialogue_windows[dialogue_name].top()->setDialogue(this->dialogues[dialogue_name][this->dialogues[dialogue_name].size() - 1], *this->window);

		if(dialogue_name == "Intro_dialogue")
			this->dialogue_windows[dialogue_name].top()->setActive(true);

	}






}

void GameState::InitObjectives()
{
	for (auto& e : this->Objectives)
	{
		e.second = false;
	}
}


void GameState::InitGui()
{
	this->InitPauseMenu();
	this->InitHpBar();
	this->InitItemPreview();
	this->InitfpsText(this->FontManager["fps_text"]);
	this->blood_overlay.setTexture(this->TextureManager["blood_overlay"]);
	this->InitMouseCursor(this->TextureManager["Mouse_Cursor"]);
	this->InitDialogueWindow();
	this->InitPopUpText();

}






GameState::GameState(stateData* state_data, map<string, Texture>* textures ,
	map<string, Font>* Fonts, GfxSettings& gfx_settings, AudioSystem& audio_system)
	: State(state_data), StatesAssetManager(textures, Fonts), audio_system(audio_system)
{
	this->InitFont();
	this->InitKeybinds();
	this->InitTextures();
	this->loadDialogueText();
	this->InitView(gfx_settings);
	this->InitRenderArea(gfx_settings);
	this->InitShader();
	this->InitLight(gfx_settings);
	this->InitMap();
	this->InitPlayer();
	this->InitEnemySpawner();
	this->InitGui();
	this->InitSounds();
	this->window->setMouseCursorVisible(false);
	this->ShowMouseCursor(false);
	this->InitObjectives();

	
}

GameState::~GameState()
{
	delete this->pausemenu;
	delete this->player;
	delete this->tile_map;
	delete this->hp_bar;
	delete this->itempreview;
	delete this->enemySpawner;
	for (auto& e : this->popup_windows)
	{
		if (e.second)
		{
			e.second = nullptr;
			delete e.second;
		}
	}
	

	this->audio_system.stopAllSounds();
	this->audio_system.PlayTheme("menu_theme");	
	this->ShowMouseCursor(true);
}

void GameState::GamePlayEvents()
{
	if (!this->player->itemIsInInventory(ITEMS::GLOCK))
	{
		this->player->addItem(ITEMS::GLOCK);
		this->player->addItem(ITEMS::MAGAZINE);
	}
	
	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("Equip_Item2")))
		&&this->getKeyTime() && this->player->itemIsInInventory(ITEMS::GLOCK))
	{	
		this->player->EquipItem(ITEMS::GLOCK);
		this->audio_system.playSound("gun_equip");
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("Equip_Item1")))
		&& this->getKeyTime())
	{
		this->audio_system.playSound("flashlight");
		this->player->EquipItem(ITEMS::FLASHLIGHT);
		/////////////////////////////////////////////////////////////////////////
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("Equip_Item3")))
		&& this->getKeyTime() && this->player->itemIsInInventory(ITEMS::HERB))
	{
		this->player->EquipItem(ITEMS::HERB);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("Equip_Item4")))
		&& this->getKeyTime() && this->player->itemIsInInventory(ITEMS::MAGAZINE))
	{
		this->player->EquipItem(ITEMS::MAGAZINE);
	}

	else if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("Equip_Item5")))
		&& this->getKeyTime() && this->player->itemIsInInventory(ITEMS::KEY))
	{
		this->player->EquipItem(ITEMS::KEY);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("Equip_Item6")))
		&& this->getKeyTime() && this->player->itemIsInInventory(ITEMS::SPECIAL_KEY))
	{
		this->player->EquipItem(ITEMS::SPECIAL_KEY);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("Equip_Item7")))
		&& this->getKeyTime() && this->player->itemIsInInventory(ITEMS::MED_KIT))
	{
		this->player->EquipItem(ITEMS::MED_KIT);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("Equip_Item8")))
		&& this->getKeyTime() && this->player->itemIsInInventory(ITEMS::CRYSTAL))
	{
		this->player->EquipItem(ITEMS::CRYSTAL);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("Use")))
		&& this->getKeyTime())
	{
		if (this->player->CurrentEquippedITemID() == ITEMS::HERB
			&&this->player->getHp() < 250.f && this->player->CurrentItem()->getQuantity() >= 1)
		{
			this->player->CurrentItem()->Use(true);
			this->player->updateHP(50.f);
		}
		else if (this->player->CurrentEquippedITemID() == ITEMS::CRYSTAL
			&& this->player->CurrentItem()->getQuantity() >= 3)
		{
			this->player->addItem(ITEMS::SPECIAL_KEY);
			{
				this->player->CurrentItem()->Use(true);
				this->player->CurrentItem()->Use(true);
				this->player->CurrentItem()->Use(true);
			}
		}
		else if (this->player->CurrentEquippedITemID() == ITEMS::MED_KIT
			&& this->player->CurrentItem()->getQuantity() >= 1)
		{
				this->player->CurrentItem()->Use(true);
				this->player->restorHp();
			
		}
		
	}

	if (this->tile_map->isDamageTile() && this->getKeyTime())
	{
		this->player->updateHP(-1.f);
	}
	
}



void GameState::UpdatePopupWindowEvents()
{
	static bool create = false;
	
	static Clock *delay = new Clock();
	if (delay)
	{
		if (delay->getElapsedTime().asSeconds() >= 5.f)
		{
			create = false;
			delay = nullptr;
			delete delay;
		}
		else
			create = true;
	}
	///chest opening
	for (auto it = this->tile_map->ChestsPosition().begin(); it != this->tile_map->ChestsPosition().end(); /* no increment here */)
	{
		auto& element = *it;
		if (element != nullptr)
		{
			if (element->contains(this->MosPosView) && Mouse::isButtonPressed(Mouse::Left) && !create)
			{
				if (this->player->CurrentEquippedITemID() == ITEMS::FLASHLIGHT)
				{
					this->popup_windows["open_chest"] = (new PopUpWinodw(Vector2f(400.f, 400.f),
						Vector2f(400.f, 200.f), Color::Blue, this->fontt, "Item Found", "Open",
						this->TextureManager["pop_backround"]));

					this->audio_system.playSound("container_open");

					create = true;
					it = this->tile_map->ChestsPosition().erase(it); // erase the element from the vector
				}
				else
				{
					this->popup_windows["cant_open_chest"] = (new PopUpWinodw(Vector2f(400.f, 400.f),
						Vector2f(400.f, 200.f), Color::Blue, this->fontt, "It's too dark i cant see the lock", "Close", this->TextureManager["pop_backround"]));
					create = true;
					++it;
				}
			}
			else
			{
				++it;
			}
		}
		else
		{
			++it;
		}
	}

	static int door_index;
	for (auto it = this->tile_map->DoorPositions().begin(); it != this->tile_map->DoorPositions().end();)
	{
			auto& element = *it;
			if (element.second.bounds.contains(this->MosPosView) && Mouse::isButtonPressed(Mouse::Left) && !create)
			{
				if (this->player->CurrentEquippedITemID() == ITEMS::FLASHLIGHT)
				{
					if (element.second.type == DoorType::LOCKED)
					{
						if (this->player->itemIsInInventory(ITEMS::KEY)
							&& this->player->getItemInInventory(ITEMS::KEY)->getQuantity() > 0)
						{
							this->popup_windows["Door_unlocked"] = (new PopUpWinodw(Vector2f(400.f, 400.f),
								Vector2f(400.f, 200.f), Color::Blue, this->fontt, "Key Found", "Unlock",
								this->TextureManager["pop_backround"]));
							door_index = element.first;

						}
						else
						{
							this->audio_system.playSound("locked_door");
							this->popup_windows["Locked_Door"] = (new PopUpWinodw(Vector2f(400.f, 400.f),
								Vector2f(400.f, 200.f), Color::Blue, this->fontt, "This Door requires a key", "Close",
								this->TextureManager["pop_backround"]));
							door_index = element.first;
						}
					}
					else if(element.second.type == DoorType::NORMAL)
					{
						this->popup_windows["Door"] = (new PopUpWinodw(Vector2f(400.f, 400.f),
							Vector2f(400.f, 200.f), Color::Blue, this->fontt, "Use Door", "Open",
							this->TextureManager["pop_backround"]));
						door_index = element.first;
					}
					else if (element.second.type == DoorType::ENEMY_DEPEND)
					{
						if (this->enemySpawner->CurrentEnemies()->size() <= 0
							&& this->Objectives["read_letter"])
						{
							this->popup_windows["Door"] = (new PopUpWinodw(Vector2f(400.f, 400.f),
								Vector2f(400.f, 200.f), Color::Blue, this->fontt, "Use Door", "Open",
								this->TextureManager["pop_backround"]));
							door_index = element.first;
						}
						else
						{
							this->popup_windows["cant_open_door_>0_enemies"] = (new PopUpWinodw(Vector2f(400.f, 400.f),
								Vector2f(400.f, 200.f), Color::Blue, this->fontt, "All enemies must be cleared\n and secret key is required", "Close",
								this->TextureManager["pop_backround"]));
							door_index = element.first;
						}
						
					}
					else if (element.second.type == DoorType::SPECIAL)
					{
						if (this->player->itemIsInInventory(ITEMS::SPECIAL_KEY)
							&& this->player->getItemInInventory(ITEMS::SPECIAL_KEY)->getQuantity() > 0)
						{
							this->popup_windows["special_door_unlock"] = (new PopUpWinodw(Vector2f(400.f, 400.f),
								Vector2f(400.f, 200.f), Color::Blue, this->fontt, "Special Key Found", "Unlock",
								this->TextureManager["pop_backround"]));
							door_index = element.first;

						}
						else
						{
							this->audio_system.playSound("locked_door");
							this->popup_windows["Locked_special_Door"] = (new PopUpWinodw(Vector2f(400.f, 400.f),
								Vector2f(400.f, 200.f), Color::Blue, this->fontt, "This Door requires a Special key", "Close",
								this->TextureManager["pop_backround"]));
							door_index = element.first;
						}
					}
					create = true;
					++it;
				}
				else
				{
					this->popup_windows["cant_open_door"] = (new PopUpWinodw(Vector2f(400.f, 400.f),
						Vector2f(400.f, 200.f), Color::Blue, this->fontt, "It's too dark, I can't open this door", "Close", this->TextureManager["pop_backround"]));
					create = true;
					++it;
				}
			}
			else
			{
				++it;
			}
	}

	for (auto it = this->tile_map->key_containersPosition().begin(); it != this->tile_map->key_containersPosition().end(); /* no increment here */)
	{
		auto& element = *it;
		if (element != nullptr)
		{
			if (element->contains(this->MosPosView) && Mouse::isButtonPressed(Mouse::Left) && !create)
			{
				if (this->player->CurrentEquippedITemID() == ITEMS::FLASHLIGHT)
				{
					this->popup_windows["open_key"] = (new PopUpWinodw(Vector2f(400.f, 400.f),
						Vector2f(400.f, 200.f), Color::Blue, this->fontt, "locked container found", "pick-lock",
						this->TextureManager["pop_backround"]));
					create = true;
					it = this->tile_map->key_containersPosition().erase(it);
				}
				else
				{
					this->popup_windows["cant_open_key"] = (new PopUpWinodw(Vector2f(400.f, 400.f),
						Vector2f(400.f, 200.f), Color::Blue, this->fontt, 
						"It's too dark i can't see the lock", "Close",
						this->TextureManager["pop_backround"]));
					create = true;
					++it;
				}
			}
			else
			{
				++it;
			}
		}
		else
		{
			++it;
		}
	}

	for (auto it = this->tile_map->LettersPosition().begin(); it != this->tile_map->LettersPosition().end(); ++it)
	{
		auto& element = *it;
		if (element != nullptr)
		{
			if (element->contains(this->MosPosView) && Mouse::isButtonPressed(Mouse::Left) && !create)
			{
				if (this->player->CurrentEquippedITemID() == ITEMS::FLASHLIGHT)
				{

					this->popup_windows["open_letter"] = (new PopUpWinodw(Vector2f(400.f, 400.f),
						Vector2f(400.f, 200.f), Color::Blue, this->fontt, "Letter found ", "Read",
						this->TextureManager["pop_backround"], nullptr, true));
					create = true;
				}
				else
				{
					this->popup_windows["cant_read_letter"] = (new PopUpWinodw(Vector2f(400.f, 400.f),
						Vector2f(400.f, 200.f), Color::Blue, this->fontt,
						"It's too dark i can't read this letter", "Close",
						this->TextureManager["pop_backround"]));
					create = true;
				}

			}
		}
	}

	if (!this->popup_windows.empty())
	{
		auto& lastElement = --this->popup_windows.end();
		lastElement->second->update(State::Mouse_pos(*this->window));

		static bool lootwindow = false;

		//Door events
		
		 if (lastElement->first == "Door")
		{
			if (lastElement->second->buttonIsPressed("Default") && this->getKeyTime())
			{
				if (door_index % 2 == 0)
				{
					this->player->ChangepawnPosition(this->tile_map->getPlayerSpawnPosition(door_index + 2));

					this->player->setRoom(this->player->CurrentRoom() + 1);
				}
				else
				{
					this->player->ChangepawnPosition(this->tile_map->getPlayerSpawnPosition(door_index));
					this->player->setRoom(this->player->CurrentRoom() - 1);
				}

				lastElement->second->closeWindow();
				create = false;
				this->popup_windows.erase(lastElement);

			}
		}
		else if (lastElement->first == "cant_open_door" || lastElement->first == "Locked_Door"
			|| lastElement->first == "Locked_special_Door" || lastElement->first == "cant_open_door_>0_enemies")
		{
			if (lastElement->second->buttonIsPressed("Default") && this->getKeyTime())
			{
				create = false;
				lastElement->second->closeWindow();
				this->popup_windows.erase(lastElement);

			}
		}
		else if (lastElement->first == "Door_unlocked" ||lastElement->first == "special_door_unlock")
		{
			if (lastElement->second->buttonIsPressed("Default") && this->getKeyTime())
			{
				this->tile_map->setDoorType(door_index, DoorType::NORMAL);
				if(lastElement->first == "Door_unlocked")
					this->player->getItemInInventory(ITEMS::KEY)->Use(true);
				else
					this->player->getItemInInventory(ITEMS::SPECIAL_KEY)->Use(true);
				this->audio_system.playSound("door_unlock");
				create = false;
				lastElement->second->closeWindow();
				this->popup_windows.erase(lastElement);
			}
		}


		 //Container Events
		else if (lastElement->first == "open_chest" || lastElement->first == "open_key")
		{
			
			if (lastElement->second->buttonIsPressed("Default") && !lootwindow && this->getKeyTime())
			{
				 int propability = this->RandIntBetween(1, 8);;
				if (lastElement->first == "open_chest")
				{
					if (this->player->CurrentRoom() == ROOM5)
					{
						this->popup_windows["upgrade_kit"] = (new PopUpWinodw(Vector2f(400.f, 400.f),
							Vector2f(400.f, 200.f), Color::Blue, this->fontt, "Gun upgrade kit",
							"Use", this->TextureManager["pop_backround"],
							&this->player->getItemTexture(ITEMS::UPGRADE_KIT)));
					}
					
					else

						if (propability == 1 || propability == 2)
					{
						this->popup_windows["Med_kit"] = (new PopUpWinodw(Vector2f(400.f, 400.f),
							Vector2f(400.f, 200.f), Color::Blue, this->fontt, "Med kit",
							"Take", this->TextureManager["pop_backround"],
							&this->player->getItemTexture(ITEMS::MED_KIT)));
					}
						else if (propability == 3 || propability == 4 || propability == 5 )
					{


						this->popup_windows["magazine"] = (new PopUpWinodw(Vector2f(400.f, 400.f),
							Vector2f(400.f, 200.f), Color::Blue, this->fontt, "Magazine", "Take",
							this->TextureManager["pop_backround"], &this->player->getItemTexture(ITEMS::MAGAZINE)));

					}
						else if (propability == 6 || propability == 7 || propability == 8)
					{
						this->popup_windows["herb"] = (new PopUpWinodw(Vector2f(400.f, 400.f),
							Vector2f(400.f, 200.f), Color::Blue, this->fontt, "Herb", "Take",
							this->TextureManager["pop_backround"], &this->player->getItemTexture(ITEMS::HERB)));
					}

				}
				else
				{
					this->audio_system.playSound("lock_pick");
					this->popup_windows["key"] = (new PopUpWinodw(Vector2f(400.f, 400.f),
					Vector2f(400.f, 200.f), Color::Blue, this->fontt, "Key Found", "Take",
					this->TextureManager["pop_backround"], &this->player->getItemTexture(ITEMS::KEY)));
					 
				}

				lastElement->second->closeWindow();
				this->popup_windows.erase(lastElement);
				lootwindow = true;
			}
		}

		//Loot events
		else if (lastElement->first == "cant_open_chest" || lastElement->first == "cant_open_key")
		{
			if (lastElement->second->buttonIsPressed("Default") && this->getKeyTime())
			{
				create = false;
				lastElement->second->closeWindow();
				this->popup_windows.erase(lastElement);
				
			}
		}
		
		else if (lastElement->first == "herb" || lastElement->first == "magazine" || lastElement->first == "key"
			|| lastElement->first == "special_key" || lastElement->first == "Med_kit" || lastElement->first == "upgrade_kit")
		{
			if (lastElement->second->buttonIsPressed("Default") && this->getKeyTime())
			{
				create = false;
				lootwindow = false;
				if(lastElement->first == "herb")
					this->player->addItem(ITEMS::HERB);
				else if(lastElement->first == "magazine")
					this->player->addItem(ITEMS::MAGAZINE);
				else if (lastElement->first == "key")
					this->player->addItem(ITEMS::KEY);
				else if(lastElement->first == "special_key")
					this->player->addItem(ITEMS::SPECIAL_KEY);
				else if(lastElement->first == "Med_kit")
					this->player->addItem(ITEMS::MED_KIT);
				else if (lastElement->first == "upgrade_kit")
				{
					this->player->getItemInInventory(ITEMS::GLOCK)->setDamage(75.f);
					this->audio_system.playSound("upgrade");
				}


				lastElement->second->closeWindow();
				this->popup_windows.erase(lastElement);	
			}
		}	

		else if (lastElement->first == "open_letter")
		{
			 if (lastElement->second->buttonIsPressed("Default") && !lootwindow && this->getKeyTime())
			 {

				 string letter_text;
				 switch (this->player->CurrentRoom())
				 {
				 case ROOM1:
					 letter_text = "They're Close now.Should you break the silence,\n they'll awaken, hungry for fear.\n They hear everything";
					 break;
				 case ROOM4:
					 letter_text = "Name: Elena Radulescu\nAge : 32\nOccupation : Village Seamstress\nAddress : Strada Pacii 13, Comuna Magurele, Romania\n"
						 "\n\nName: Andrei Dumitru\nAge : 28\nOccupation : Village Carpenter\nAddress : Strada Libertatii 7, Comuna Campina, Romania\n";
					 break;
				 case ROOM5:
					 letter_text = "Subject Report - Experiment Log #342:\n\n\n"
						 "Observations:\n\n"
						 "1-Initial exposure to Elixarum Obscura resulted in\ndisorientation and increased sensitivity to light\n\n"
						 "2-Over the course of three weeks, the subject exhibited\nheightened aggression and enhanced physical strength.\n\n"
						 "3-Strange markings appeared on the subject's skin\nresembling ancient symbols\n";
					 break;
				 }



				 this->popup_windows["read_letter"] = (new PopUpWinodw(Vector2f(400.f, 400.f),
					 Vector2f(400.f, 200.f), Color::Blue, this->fontt, letter_text,
					 "Close", this->TextureManager["pop_backround"], nullptr, true));
				 this->popup_windows["read_letter"]->ReadMode(*this->window);
				 lastElement->second->closeWindow();
				 this->popup_windows.erase(lastElement);
				 lootwindow = true;
			 }
		}
		else if (lastElement->first == "read_letter" || "cant_read_letter" )
		{
			 if (lastElement->second->buttonIsPressed("Default") && this->getKeyTime())
			 {
				 if (lastElement->first == "read_letter")
				 {
					 if (this->player->CurrentRoom() == ROOMS::ROOM5)
					 {
						 CurrentDialogue = &this->dialogue_windows["realization"];
						 this->DialogueNum = DIALOGUE::REALAIZE;
					 }
				 }
				 create = false;
				 lootwindow = false;
				 lastElement->second->closeWindow();
				 this->popup_windows.erase(lastElement);
				
			 }
		}
	}
}



void GameState::EndState()
{

	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("Pause"))) &&
		this->getKeyTime())
	{
		if (!this->pause)
		{
			this->PauseState();
		}
		else
		{
			this->UnPauseState();
			
		}
	}

	if (this->player->getHp() <= 0)
	{
		this->audio_system.stopAllSounds();
		this->states->pop();
		this->states->push(new EndGameState(this->stateDataPtr, this->textures, this->Fonts, *this->gfx_settings
			, this->audio_system));
	}
	else if (this->dialogue_windows["boss_killed"].empty())
	{
		State::EndState();
	}
}

void GameState::UpdateKeys(const float& dt)
{
	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("Move_left"))))
	{
		this->player->move(- 1, 0.f, dt);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("Move_right"))))
	{

		this->player->move(1, 0.f, dt);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("Move_up"))))
	{
		this->player->move(0.0, -1.f, dt);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("Move_down"))))
	{
		this->player->move(0.f, 1.f, dt);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("Move_down"))))
	{
		this->player->move(0.f, 1.f, dt);
	}

}

void GameState::updateView()
{

	this->view.setCenter
	(
		floor(this->player->getPosition().x + 50.f +
			(static_cast<float>(State::Mouse_pos(*this->window).x)
			- static_cast<float>(this->gfx_settings->ActiveResolution.width/2))/10.f),

		floor(this->player->getPosition().y + 60.f +
			(static_cast<float>(State::Mouse_pos(*this->window).y)
			- static_cast<float>(this->gfx_settings->ActiveResolution.height/2))/10.f)
	);


	if (this->view.getCenter().x - this->view.getSize().x / 2.f < 0.f)
	{
		this->view.setCenter(0.f + this->view.getSize().x / 2.f, this->view.getCenter().y);
	}
	else if (this->view.getCenter().x + this->view.getSize().x / 2.f > 10000)
	{
		this->view.setCenter(10000 -  this->view.getSize().x / 2.f, this->view.getCenter().y);
	}

	if (this->view.getCenter().y - this->view.getSize().y / 2.f < 0.f)
	{
		this->view.setCenter(this->view.getCenter().x, 0.f + this->view.getSize().y /2.f );
	}
	else if (this->view.getCenter().y + this->view.getSize().y / 2.f > 10000)
	{
		this->view.setCenter(this->view.getCenter().x , 10000 -  this->view.getSize().y / 2.f);
	}


	this->viewGridPosition.x = static_cast<int>(this->view.getCenter().x) / this->stateDataPtr->gridSize;
	this->viewGridPosition.y = static_cast<int>(this->view.getCenter().y) / this->stateDataPtr->gridSize;
	

	this->AmbientLighting.setPosition(this->view.getCenter().x - 
		this->AmbientLighting.getSize().x / 2.f , this->view.getCenter().y -
		this->AmbientLighting.getSize().y / 2.f);

	
}

void GameState::updateMouseCursor()
{
	State::updateMouseCursor();
	if (this->player->CurrentEquippedITemID() == ITEMS::GLOCK)
	{
		this->setMouseCursorTexture(this->TextureManager["crosshair"]);
		this->MouseCursor.setPosition(this->MouseCursor.getPosition().x - 10.f, this->MouseCursor.getPosition().y - 40.f);
	}
	else
	{
		this->setMouseCursorTexture(this->TextureManager["Mouse_Cursor"]);
	}
}


void GameState::updatePlayerState()
{
	

}

//update audios that are not related to any event
void GameState::updateAudioEvents()
{
	if (this->player->getHp() <= 50.f || this->time_left - this->timer.getElapsedTime().asSeconds() <= 0.f)
	{
		this->audio_system.playSound("low_hp_sound");	
	}
	else
	{
		this->audio_system.stopSound("low_hp_sound");
	}



	if (this->player->getState() == PlayerState::SHOOTING)
	{
		if(this->player->CurrentItem()->getDamage()> 35.f)
			this->audio_system.playSound("upgraded_gun", true);

		else
			this->audio_system.playSound("gun_shot", true);
		
	}
	else if (this->player->getState() == PlayerState::RELOADING)
	{

		this->audio_system.playSound("reload");

	}

	if (abs(this->player->getVelocity().x) > 5.f || abs(this->player->getVelocity().y) > 5.f)
	{
		this->audio_system.playSound("footsteps");
	}
	else
		this->audio_system.stopSound("footsteps");


	if (CurrentDialogue)
	{
		if (CurrentDialogue->top())
		{
			if (CurrentDialogue->top()->Active())
			{
				this->audio_system.StopTheme("normal_theme");
				this->audio_system.Stop3dSound("light_buzz");
			}
		}
	}
	else
		this->audio_system.play3dSound("lamp_buzz", this->player->getPosition(), this->tile_map->LightPositions());


	if (this->DialogueNum == DIALOGUE::INTRO)
	{
		if (this->dialogueIndex == 2)
		{
			this->audio_system.playSoundOnce("door_open");
		}
		else if (this->dialogueIndex == 3)
		{
			this->audio_system.playSoundOnce("flashlight");
		}
		else if (this->dialogueIndex == 5)
		{
			this->audio_system.playSoundOnce("door_closing");
		}
	}
	else if (this->DialogueNum == DIALOGUE::REALAIZE)
	{
		
		if (this->dialogueIndex == 4)
		{
			this->audio_system.playSoundOnce("quake");
			
		}
	}
	else if (this->DialogueNum == DIALOGUE::KILLED_BOSS)
	{
		if (this->dialogueIndex == 4)
		{
			this->audio_system.playSound("running");
		}
		else if (this->dialogueIndex == 5)
		{
			this->audio_system.playSound("collapse");

		}
		else if (this->dialogueIndex == 6)
		{
			this->audio_system.playSound("police");

		}

	}
}




//update world and surroundings (collision, enemies...)
void GameState::updateWorld(const float &dt)
{

	if (this->tile_map)
	{
		bool chase = false;
		this->tile_map->update();
		this->tile_map->CheckCollision(*this->player,this->MosPosView,dt);
		for (auto it = this->enemySpawner->CurrentEnemies()->begin(); it != this->enemySpawner->CurrentEnemies()->end(); ++it)
		{
			auto& activenemy = *it;
			
			if (this->popup_windows.empty())
			{
				activenemy->update(dt, *this->player);

				if(activenemy->getType() != ENEMYTYPE::BOSS)
					this->tile_map->CheckCollision(*activenemy, this->MosPosView, dt);
				if (activenemy->getState() != ENEMYSTATES::PATROL)
				{
					chase = true;
				}
				
				if (activenemy->getGlobalbounds().contains(this->MosPosView)
					&& this->player->getState() == PlayerState::SHOOTING && this->getKeyTime()
					&& this->player->CurrentItem()->getMagazineSize() > 0)
				{
					
					activenemy->deductHp(this->player->CurrentItem()->getDamage());
					activenemy->setState(ENEMYSTATES::BEING_HIT);
					

					
				}
				if (activenemy->getState() == ENEMYSTATES::ATTACK)
				{
					static Clock delay;
					if (delay.getElapsedTime().asSeconds() >= 0.75f)
					{
						this->audio_system.playSound("hit");
						this->player->updateHP(-activenemy->getDamage());
						delay.restart();
					}
				}
					

				if (activenemy->getType() == ENEMYTYPE::BOSS)
				{
					if (!this->Objectives["boss"])
						this->Objectives["boss"] = true;
					if (activenemy->getState() == ENEMYSTATES::ENEMY_DIE)
					{
						this->Objectives["boss_killed"] = true;
						this->audio_system.StopTheme("boss_theme");
					}
					else
						this->Objectives["boss_killed"] = false;

				}
				 if (activenemy->getState() == ENEMYSTATES::ENEMY_DIE)
				 {
				    this->player->addItem(ITEMS::CRYSTAL);
					this->popuptext->addText(*this->window, "Crystal found");
					

					it = this->enemySpawner->CurrentEnemies()->erase(it);
					--it;
				 }
				 
			}
		}
		if (!this->Objectives["boss"])
		{
			if (chase)
			{
				this->audio_system.PlayTheme("chase_theme");
			}
			else
				this->audio_system.PlayTheme("normal_theme");
		}
		else if(!this->Objectives["boss_killed"])
		{
			this->audio_system.StopTheme("chase_theme");
			this->audio_system.StopTheme("normal_theme");

			this->audio_system.PlayTheme("boss_theme");
		}
	}
}


void GameState::updateEnemySpawn(const float& dt)
{
	this->enemySpawner->updateEnemiesSpawn(*this->player);
}

void GameState::updateDialogueWindow(const float &dt)
{
	if (!this->dialogue_windows["Intro_dialogue"].empty())
	{
		CurrentDialogue = &this->dialogue_windows["Intro_dialogue"];
		this->DialogueNum = DIALOGUE::INTRO;
	}

	else if (this->enemySpawner->CurrentEnemies()->size() == 1 &&
		this->player->CurrentRoom() == ROOMS::ROOM2 && !this->dialogue_windows["enemy_encounter"].empty())
	{
		CurrentDialogue = &this->dialogue_windows["enemy_encounter"];
		CurrentDialogue->top()->setActive(true);
		this->DialogueNum = DIALOGUE::ENEMY_ENCOUNTER;
		
	}
	else if (this->player->CurrentRoom() == ROOMS::ROOM3 && !this->dialogue_windows["after_seeing_enemy"].empty())
	{
		CurrentDialogue = &this->dialogue_windows["after_seeing_enemy"];
		CurrentDialogue->top()->setActive(true);
		this->DialogueNum = DIALOGUE::AFTER_SEEING_ENEMY;

	}
	else if (this->player->CurrentRoom() == ROOMS::ROOM6 && !this->dialogue_windows["boss_meet"].empty())
	{
		CurrentDialogue = &this->dialogue_windows["boss_meet"];
		CurrentDialogue->top()->setActive(true);
		this->DialogueNum = DIALOGUE::AFTER_SEEING_ENEMY;

	}
	else if (this->Objectives["boss_killed"] && !this->dialogue_windows["boss_killed"].empty())
	{
		CurrentDialogue = &this->dialogue_windows["boss_killed"];
		CurrentDialogue->top()->setActive(true);
		this->DialogueNum = DIALOGUE::KILLED_BOSS;
	}

	if (CurrentDialogue && !CurrentDialogue->empty())
	{
		CurrentDialogue->top()->update(*this->window, State::Mouse_pos(*this->window), dt);

		if (CurrentDialogue->top()->isskip())
		{
			while (!CurrentDialogue->empty())
			{
				delete CurrentDialogue->top();
				CurrentDialogue->pop();
				this->dialogueIndex = 0;
			}
			CurrentDialogue = nullptr;
		}
		else if (!CurrentDialogue->top()->Active())
		{
			delete CurrentDialogue->top();
			CurrentDialogue->pop();
			++dialogueIndex;

			if (!CurrentDialogue->empty())
			{
				CurrentDialogue->top()->setActive(true);
			}
			else
			{
				CurrentDialogue = nullptr;
				this->dialogueIndex = 0;
			}
		}
	}

	if (this->dialogue_windows["Intro_dialogue"].empty()
		&&!this->popuptext->isActive() && this->popuptext && !this->Objectives["Investigate"])
	{
		this->Objectives["Investigate"] = true;
		this->popuptext->addText(*this->window, "Investigate Missing pepole", new short(35), 150.f);
	}
	else if (this->dialogue_windows["after_seeing_enemy"].empty()
		&& !this->popuptext->isActive() && this->popuptext && !this->Objectives["find_way_out"])
	{
		this->Objectives["find_way_out"] = true;
		this->popuptext->addText(*this->window, "Find a way out of the house", new short(35), 150.f);
	}
	else if (this->dialogue_windows["realization"].empty())
	{
		this->Objectives["read_letter"] = true;
		
		double timeDifference = time_left - timer.getElapsedTime().asSeconds();
		std::string timeDifferenceString = std::to_string(timeDifference);
		size_t decimalPoint = timeDifferenceString.find('.');

		if (decimalPoint != string::npos)
		{
			timeDifferenceString = timeDifferenceString.substr(0, decimalPoint + 2);
		}

		this->popuptext->addText(*this->window, timeDifferenceString, new short(35), 150.f);
	}
	
	if (!this->Objectives["read_letter"])
	{
		this->timer.restart();
	}
}

void GameState::updateGui(const float& dt)
{
	this->updateDialogueWindow(dt);
	this->popuptext->update();
	
}


void GameState::updateGameplay(const float& dt)
{
	auto DialogueemptyCheck = [](const stack<DialogueWindow*>* dialogue_window_stack) -> bool
	{
			return !dialogue_window_stack || dialogue_window_stack->empty();
	};

	if (DialogueemptyCheck(CurrentDialogue))
	{
		this->ShowMouseCursor(false);
		this->GamePlayEvents();
		this->UpdatePopupWindowEvents();
		this->updatePlayerState();
		if (this->popup_windows.empty())
		{
			auto hasOpenedChest = [this](Vector2f& mousePosView)
				{
					for (auto& element : this->tile_map->ChestsPosition())
					{
						if (element != nullptr && element->contains(mousePosView) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
							return true;
						}
					}
					return false;
				};
			this->player->update(dt, this->player->getPosition(), this->MosPosView, hasOpenedChest(this->MosPosView));
			this->updateAudioEvents();
			this->updateEnemySpawn(dt);
		}
		this->itempreview->update(this->player->getCurrentItemTexture(), this->player->CurrentitemIsInInventory());
		this->updateWorld(dt);

	}
	else
	{
		this->updateAudioEvents();
		this->audio_system.PauseTheme("chase_theme");
		this->player->stopVelocity(StopVelocity::STOP_VELOCITY);
		this->ShowMouseCursor(true);
		this->updateWorld(dt);
	}
}

void GameState::update(const float& dt)
{
	this->SetFullScreen();
	
	if (!this->pause)
	{
		
		this->updateMouseCursor();
		this->calcFps(dt);
		this->UpdateKeys(dt);
		this->updateKeytime(dt);
		this->UpdateMosePos(&this->view);
		this->updateView();

		this->updateGameplay(dt);
		this->updateGui(dt);
		
		this->EndState();
	
	}
	else
	{
		this->audio_system.PauseTheme("normal_theme");
		this->audio_system.PauseTheme("chase_theme");
		this->ShowMouseCursor(true);
		this->updateKeytime(dt);
		this->pausemenu->update(State::Mouse_pos(*this->window));
		if (this->pausemenu->Quit() && this->getKeyTime())
			this->window->close();
		else if (this->pausemenu->GetResumeStatus() && this->getKeyTime())
		{
			this->UnPauseState();
		}
		else if (this->pausemenu->GoToMenu() && this->getKeyTime())
		{
			State::EndState();
		}
	}
}

void GameState::renderPopUpWindow(RenderTarget& target)
{
	if (!this->popup_windows.empty())
	{
		auto& lastElement = --this->popup_windows.end();
		lastElement->second->render(target);
	}
}

void GameState::renderActors(RenderTexture& renderTexture)
{
	auto hasOpenedChest = [this](Vector2f& mousePosView)
	{
		for (auto& element : this->tile_map->ChestsPosition())
		{
			if (element != nullptr && element->contains(mousePosView) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				return true;
			}
		}
		return false;
	};
	this->player->render(&this->renderTexture, &this->core_shader, this->player->getCenter(), hasOpenedChest(this->MosPosView), false);
	for (auto it = this->enemySpawner->CurrentEnemies()->begin(); it != this->enemySpawner->CurrentEnemies()->end();)
	{
		auto& element = *it;
		element->render(this->renderTexture, &this->core_shader, this->player->getCenter(), false);
		++it;
	}
}

void GameState::RenderGui(RenderTarget& target)
{
	this->player->renderHPBar(target);
	this->hp_bar->render(target,this->player->getHp());

	this->popuptext->render(target);
	if (this->player->CurrentEquippedITemID() != ITEMS::FLASHLIGHT)
	{
		if (this->player->CurrentEquippedITemID() == ITEMS::HERB
			|| this->player->CurrentEquippedITemID() == ITEMS::KEY
			|| this->player->CurrentEquippedITemID() == ITEMS::SPECIAL_KEY
			||this->player->CurrentEquippedITemID() == ITEMS::CRYSTAL
			|| this->player->CurrentEquippedITemID() == ITEMS::MED_KIT)
		{
			const string quantity = to_string(this->player->CurrentItem()->getQuantity());
			this->itempreview->render(target, &quantity);
		}
		else if(this->player->CurrentEquippedITemID() == ITEMS::GLOCK )
		{
			const string quantity = 
			to_string(this->player->getItemInInventory(ITEMS::MAGAZINE)->getQuantity())+" / "
			+to_string(this->player->CurrentItem()->getMagazineSize());
			this->itempreview->render(target, &quantity);
		}
		else if (this->player->CurrentEquippedITemID() == ITEMS::MAGAZINE)
		{
			const string quantity = "Bullets: " + to_string(this->player->CurrentItem()->getQuantity());
			this->itempreview->render(target, &quantity);
		}

	}
	else
		this->itempreview->render(target);
	this->renderFpsText(target);

	if (!this->popup_windows.empty())
	{
		auto& lastElement = --this->popup_windows.end();
		lastElement->second->render(target);
	}
	this->renderMouseCursor(&target);

	if (this->player->getHp() <= 50.f)
	{
		target.draw(this->blood_overlay);
	}

	for (const auto& e : this->dialogue_windows)
	{
		if (!e.second.empty())
		{
			if(e.second.top()->Active() && e.second.top())
			e.second.top()->render(target);
		}
	}
	
}


void GameState::render(RenderWindow* target)
{
	if (target == NULL)
		target = this->window;
	
	this->renderTexture.clear();
	this->renderTexture.setView(this->view);

	if (this->tile_map)
	{
		this->tile_map->render(this->renderTexture, &this->viewGridPosition, false,
			&this->core_shader, this->player->getCenter());

		this->renderActors(this->renderTexture);
		
		this->tile_map->renderOverlappingTiles(this->renderTexture, &this->core_shader, this->player->getCenter());
	}
		

	//final render;
	this->renderTexture.draw(this->AmbientLighting);
	this->renderTexture.display();
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	
	target->draw(this->renderSprite);
	
	
	this->RenderGui(*target);

	if (this->pause)
	{
		this->ShowMouseCursor(true);
		this->renderTexture.setView(this->window->getDefaultView());
		this->pausemenu->render(target);
	}
	
}