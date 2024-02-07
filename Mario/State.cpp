#include "stdafx.h"
#include "State.h"


State::State(stateData* state_data)
{
	this->stateDataPtr = state_data;
	this->states = state_data->states;
	this->window = state_data->window;
	this->quit = false;
	this->supportedkeys = state_data->supportedkeys;
	this->pause = false;
	this->keytime = 0.f;
	this->keytimeMax = 11.f;
	this->gridSize = state_data->gridSize;

	this->gfx_settings = new GfxSettings();
	
}

State::~State()
{
	delete this->gfx_settings;
	

}

const bool& State::getQuitStatus()
{
	return this->quit;
}

bool State::getKeyTime()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}
	return false;
}


void State::PauseState()
{
	this->pause = true;
}

void State::UnPauseState()
{
	this->pause = false;
}

void State::SetFullScreen()
{
	if (Keyboard::isKeyPressed(Keyboard::F))
	{
		this->window->create(this->gfx_settings->ActiveResolution, this->gfx_settings->title, Style::Fullscreen);
		this->window->setFramerateLimit(this->gfx_settings->frameratelimit);
		this->ShowMouseCursor(false);

	}
}

bool State::AllowMouse(const string mouseButton)
{
	if (mouseButton == "right")
	{
		static bool wasPressed = false;
		static bool isClicked = false;
		static int MousePress = 0;

		if (Mouse::isButtonPressed(Mouse::Right))
		{
			if (!wasPressed)
			{
				isClicked = true;
				MousePress++;

				wasPressed = true;
			}
			else
			{
				isClicked = false;
			}
		}
		else
		{
			wasPressed = false;
			isClicked = false;
		}

		return isClicked && MousePress > 1;
	}
	else if (mouseButton ==  "left")
	{
		static bool wasPressed = false;
		static bool isClicked = false;
		static int MousePress = 0;

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (!wasPressed)
			{
				isClicked = true;
				MousePress++;

				wasPressed = true;
			}
			else
			{
				isClicked = false;
			}
		}
		else
		{
			wasPressed = false;
			isClicked = false;
		}

		return isClicked && MousePress > 0;
	}
	else
	{
		return false;
	}

}

bool State::AllowKeyboardPress(unsigned key)
{
	static bool wasPressed = false;
	static bool isClicked = false;
	static int MousePress = 0;

	if (Keyboard::isKeyPressed(Keyboard::Key(key)))
	{
		if (!wasPressed)
		{
			isClicked = true;
			MousePress++;

			wasPressed = true;
		}
		else
		{
			isClicked = false;
		}
	}
	else
	{
		wasPressed = false;
		isClicked = false;
	}

	return isClicked && MousePress > 0;
}



Vector2f State::Mouse_pos(const RenderWindow& window)
{
	return static_cast<Vector2f>(Mouse::getPosition(window));

}

void State::InitKeybinds()
{
}

void State::InitfpsText(Font& font)
{
	this->fpsText.setFont(font);
	this->fpsText.setCharacterSize(35.f);
	this->fpsText.setFillColor(Color::White);
	this->fpsText.setOutlineThickness(2.f);
	this->fpsText.setOutlineColor(Color::Black);

	
}

void State::InitMouseCursor(Texture& texture)
{
	this->MouseCursor.setTexture(texture);
	this->MouseCursor.setScale(0.2f, 0.2f);
}

const Vector2f State::GetMouseCursorPos() const
{
	return this->MouseCursor.getPosition();
}



void State::renderMouseCursor(RenderTarget* target)
{
	target->draw(this->MouseCursor);
}

void State::updateMouseCursor()
{
	this->MouseCursor.setPosition(this->Mouse_pos(*this->window).x
		- this->MouseCursor.getGlobalBounds().width + 125.f/ 2.f, this->Mouse_pos(*this->window).y
		- this->MouseCursor.getGlobalBounds().height + 140.f / 2.f);
}

void State::ShowMouseCursor(bool show)
{
	if (show)
		this->window->setMouseCursorVisible(true);
	else
		this->window->setMouseCursorVisible(false);
}

void State::setMouseCursorTexture(const Texture& texture)
{
	this->MouseCursor.setTexture(texture);
}


const int State::RandIntBetween(const int x, const int y)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<float> dis(x, y);
	return dis(gen);
}

void State::updateKeytime(const float &dt)
{
	if (this->keytime < this->keytimeMax)
		this->keytime += 100.f * dt;

}

void State::calcFps(const float& dt)
{
	//float fps = 1.0f / dt;
	int fps = static_cast<float>(1.0f / dt);
	stringstream iss;
	iss << "Fps: " << fps;
	this->fpsText.setString(iss.str());
	this->fpsText.setPosition
	(
		this->gfx_settings->ActiveResolution.width - (this->fpsText.getGlobalBounds().width + 17.f),
		40.f
	);
	
}

void State::renderFpsText(RenderTarget& target)
{

	target.draw(this->fpsText);

}



void State::UpdateMosePos(View* view)
{
	this->MosPosScreen = Mouse::getPosition();
	this->MosPosWindow = Mouse::getPosition(*this->window);

	if(view)
		this->window->setView(*view);

	this->MosPosView = this->window->mapPixelToCoords(Mouse::getPosition(*this->window));
	this->MousePosGrid = Vector2u
	(
		static_cast<unsigned>(this->MosPosView.x) / static_cast<unsigned> (this->gridSize)
		,
		static_cast<unsigned>(this->MosPosView.y) / static_cast<unsigned> (this->gridSize)

	);

	this->window->setView(this->window->getDefaultView());
}

void State::EndState()
{
	this->quit = true;
}


