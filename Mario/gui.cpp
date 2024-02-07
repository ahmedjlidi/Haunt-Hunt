#include "stdafx.h"
#include "gui.h"
using namespace GUI;

Button::Button(float pos_x, float pos_y, float height, float width,
	shared_ptr<Font>font, string text, Color IdleColor, Color HoverColor, Color ActiveColor,
	Texture &texture, unsigned Char_size, const bool ShowBackround, short unsigned id)
{
	this->id = id;
	this->IdleColor = IdleColor;
	this->HoverColor = HoverColor;
	this->ActiveColor = ActiveColor;

	this->ButtonState = Button_Idle;

	this->background.setPosition(pos_x, pos_y);
	this->background.setSize(Vector2f(height, width));
	if(!ShowBackround)
		this->background.setFillColor(Color::Transparent);
	else
	{
		Color color(255, 255, 255);
		color.a = 75;
		this->background.setFillColor(Color::Black);
	}

	this->font = move(font);
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(this->IdleColor);
	this->text.setCharacterSize(Char_size);
	this->text.setOutlineThickness(3);
	this->text.setOutlineColor(Color::Black);
	// Assuming the text's origin is at its center
	this->text.setOrigin(this->text.getGlobalBounds().width / 2, this->text.getGlobalBounds().height / 2);

	// Calculate the center of the button
	float centerX = this->background.getPosition().x + this->background.getSize().x / 2.f;
	float centerY = this->background.getPosition().y + this->background.getSize().y / 2.f;

	// Set the text's position to the center of
	//  the button
	this->text.setPosition(centerX, centerY);


}

void GUI::Button::SetText(const string text)
{
	this->text.setString(text);
}

const string GUI::Button::GetText()
{
	return this->text.getString();
}



Vector2f Button::GetButtonSize()
{
	return this->background.getSize();
}





void Button::update(const Vector2f MousePos)
{
	//idle
	
	this->ButtonState = Button_Idle;
	
	
	if (this->background.getGlobalBounds().contains(MousePos))
	{
		//hover
		this->ButtonState = Button_Hover;
		
		
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			//pressed
			this->ButtonState = Button_Pressed;
			
		}

	}

	switch (this->ButtonState)
	{
	case Button_Idle:
		this->text.setFillColor(IdleColor);
		break;
	case Button_Pressed:
		this->text.setFillColor(ActiveColor);
		
		break;
	case Button_Hover:
		this->text.setFillColor(HoverColor);
		break;
	}
	
}

const bool Button::IsPressed() const
{
	if (this == nullptr) 
	{
		return false;
	}

	if (this->ButtonState == Button_Pressed)
		return true;

	return false;
}

const short unsigned& GUI::Button::getId() const
{
	return this->id;
}

void GUI::Button::SetId(const short unsigned id)
{
	this->id = id;
	
}

const FloatRect GUI::Button::getTextGlobalbounds() const
{
	return this->text.getGlobalBounds();
}


void Button::RenderButton(RenderTarget* target)
{
	target->draw(this->background);
	target->draw(this->text);
	
}

void Button::render(RenderTarget* target)
{
	this->RenderButton(target);
	
}

ButtonComponent* GUI::Button::buttonComponent()
{
	return new ButtonComponent(this->background, this->text);
}

const bool GUI::Button::CustomIsPressed(FloatRect pos)
{
	return (this->background.getGlobalBounds().intersects(pos)
		&&Mouse::isButtonPressed(Mouse::Left));
}









//======================================drop down list




void GUI::DropDownList::InitActiveElement(RenderWindow& window, shared_ptr<Font> font, Texture& texture
,string list_nbr, float Pos_y, unsigned index, short unsigned id, short unsigned font_size)
{
	const Vector2f buttonSize = { 300, 100 };
	const float PosX = 450.f;

	const Color Idle = Color(255, 255, 255);
	if(index > 0)
	this->list.push_back (new Button(PosX + 75, Pos_y, 150,50, font, list_nbr,
		Idle, Color(172, 172, 172), Color(49, 153, 132), texture, font_size,0,id));
	else
		this->list.push_back(new Button(PosX, Pos_y, 300, 100, font, list_nbr,
			Idle, Color(172, 172, 172), Color(49, 153, 132), texture, font_size, 0, id));

	this->keytime = 0.f;
	this->keytimeMax = 11.f;

	 //if char size is 1/2 of original(70) increase 75 to pos x when index >0
}

bool GUI::DropDownList::getKeyTime()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}
	return false;
}

GUI::DropDownList::DropDownList(RenderWindow& window, shared_ptr<Font> font, Texture& texture, string list[]
                                ,unsigned elemnts_nbr, unsigned default_index, float Pos_y, short unsigned font_size)
	:texture(texture),font(font)
{
	this->showList = false;
	float PosY = Pos_y;
	for (size_t i = 0; i < elemnts_nbr; i++)
	{
		
		this->InitActiveElement(window, this->font, this->texture, list[i], PosY, i,i, font_size);
		
		PosY += 75;
		
	}

	this->activeElement = new Button(*this->list[0]);
	this->list.erase(this->list.begin());
}

GUI::DropDownList::~DropDownList()
{
	delete this->activeElement;
	for (auto* e : this->list)
	{
		delete e;
	}
}




const short unsigned& GUI::DropDownList::getId() const
{
	return this->activeElement->getId();
}

void GUI::DropDownList::update(const Vector2f MousePos, const float &dt)
{

	if (this->keytime < this->keytimeMax)
		this->keytime += 100.f * dt;

	this->activeElement->update(MousePos);
	if (this->activeElement->IsPressed() && this->getKeyTime())
	{
		if (!this->showList)
			this->showList = true;
		else
			this->showList = false;
	}

	if (this->showList)
	{
		for (auto& e : this->list)
		{
			e->update(MousePos);
			if (e->IsPressed() && this->getKeyTime())
			{
				// Store the current active element in the list
				this->list.push_back(this->activeElement);

				// Update the active element with the clicked item
				const string temp = this->activeElement->GetText();
				const unsigned tempInt = this->activeElement->getId();
				this->activeElement->SetText(e->GetText());
				this->activeElement->SetId(e->getId());

				e->SetText(temp);
				e->SetId(tempInt);

				this->showList = false;
			}
		}
	}
}

void GUI::DropDownList::render(RenderTarget* target)
{
	this->activeElement->render(target);
	
	if (this->showList)
	{
		for (auto& e : this->list)
		{
			e->render(target);
		}
	}

	
	
}

const string GUI::DropDownList::GetListText()
{
	return this->ActiveElementText;
}

//LABELS

GUI::Label::Label(float pos_x, float pos_y, float height, float width
	, shared_ptr<Font> font, string text, Texture& texture, Color color
	, unsigned Char_size, const bool ShowBackround)
{
	this->background.setPosition(pos_x, pos_y);
	this->background.setSize(Vector2f(height, width));
	if (ShowBackround)
		this->background.setFillColor(Color::Transparent);
	else
	{
		Color color(255, 255, 255);
		color.a = 75;
		this->background.setFillColor(Color::Black);
	}

	this->font = move(font);
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(color);
	this->text.setCharacterSize(Char_size);
	this->text.setOutlineThickness(3);
	this->text.setOutlineColor(Color::Black);
	// Assuming the text's origin is at its center
	this->text.setOrigin(this->text.getGlobalBounds().width / 2, this->text.getGlobalBounds().height / 2);

	// Calculate the center of the button
	float centerX = this->background.getPosition().x + this->background.getSize().x / 2.f;
	float centerY = this->background.getPosition().y + this->background.getSize().y / 2.f;

	// Set the text's position to the center of
	//  the button
	this->text.setPosition(centerX, centerY);
}



void GUI::Label::RenderLabel(RenderTarget* target)
{
	target->draw(this->background);
	target->draw(this->text);
}

void GUI::Label::render(RenderTarget* target)
{
	this->RenderLabel(target);

}


GUI::TextureSelector::TextureSelector(const Texture& texture_sheet,
	Color color, float grid_size, float height, float width, float x, float y)
{
	this->active = false;
	this->GridSize = grid_size;

	this->bounds.setSize(Vector2f(width, height));
	this->bounds.setPosition(x, y);
	this->bounds.setFillColor(color);
	this->bounds.setOutlineThickness(1);
	this->bounds.setOutlineColor(Color::White);

	this->sheet.setTexture(texture_sheet);

	this->sheet.setPosition(x, y);

	if (this->sheet.getGlobalBounds().width > this->bounds.getGlobalBounds().width)
	{
		this->sheet.setTextureRect(IntRect(0, 0, this->bounds.getGlobalBounds().width,
			this->sheet.getGlobalBounds().height));


	}

	if (this->sheet.getGlobalBounds().height > this->bounds.getGlobalBounds().height)
	{
		this->sheet.setTextureRect(IntRect(0, 0, this->sheet.getGlobalBounds().width,
			this->bounds.getGlobalBounds().height));


	}

	this->TextureRect.width = static_cast<int>(this->GridSize);
	this->TextureRect.height = static_cast<int>(this->GridSize);;

	this->selector.setSize(Vector2f(this->GridSize, this->GridSize));
	this->selector.setPosition(x, y);
	this->selector.setFillColor(Color::Transparent);
	this->selector.setOutlineThickness(1);
	this->selector.setOutlineColor(Color::Red);

	this->hide = false;
}


void GUI::TextureSelector::ChangeTexture(IntRect& texture_rect, const bool allow)
{
	if (allow)
	{
		texture_rect = this->TextureRect;
	}
}

void GUI::TextureSelector::update(const Vector2f MousePos, IntRect& texture_rect , const bool allow)
{
	if (!this->hide)
	{
		if (this->bounds.getGlobalBounds().contains(MousePos))
		{
			this->active = true;
		}
		else
			this->active = false;

		if (this->active)
		{
			this->MousePosGrid.x = (
				(MousePos.x - this->bounds.getPosition().x) / static_cast<unsigned>(this->GridSize)
				);

			this->MousePosGrid.y = ((MousePos.y - this->bounds.getPosition().y) / static_cast<unsigned>(this->GridSize)
				);

			this->selector.setPosition
			(
				this->bounds.getPosition().x + this->MousePosGrid.x * this->GridSize,
				this->bounds.getPosition().y + this->MousePosGrid.y * this->GridSize
			);

			this->TextureRect.left = static_cast<int>(this->selector.getPosition().x - this->bounds.getPosition().x);
			this->TextureRect.top = static_cast<int>(this->selector.getPosition().y - this->bounds.getPosition().y);

			this->ChangeTexture(texture_rect, allow);
		}
	}
	if (Mouse::isButtonPressed(Mouse::XButton1))
	{
		this->bounds.move(0, -4.f);
		this->sheet.setPosition(this->bounds.getPosition().x, this->bounds.getPosition().y);
	}
	else if (Mouse::isButtonPressed(Mouse::XButton2))
	{
		this->bounds.move(0, 4.f);
		this->sheet.setPosition(this->bounds.getPosition().x, this->bounds.getPosition().y);
	}

	else if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		this->bounds.move(4.f,0.f );
		this->sheet.setPosition(this->bounds.getPosition().x, this->bounds.getPosition().y);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		this->bounds.move(-4.f, 0.f);
		this->sheet.setPosition(this->bounds.getPosition().x, this->bounds.getPosition().y);
	}

}

const bool GUI::TextureSelector::TextureSelectorIsActive() const
{
	return this->active;
}

void GUI::TextureSelector::show(const bool show)
{
	if (show)
	{
		if (this->hide == false)
		{
			this->hide = true;
		}
		else
			this->hide = false;
	}
}





void GUI::TextureSelector::renderSelector(RenderTarget& target)
{
	if (!this->hide)
	{
		target.draw(this->selector);
	}
}

void GUI::TextureSelector::renderTextureSelectorWindow(RenderTarget& target)
{
	if (!this->hide)
	{
		target.draw(this->bounds);
		target.draw(this->sheet);
	}
}





//////Pop Up window

GUI::PopUpWinodw::PopUpWinodw(const Vector2f size, const Vector2f conatiner_pos,
	const Color color, shared_ptr<Font>font, const string text,
	const string buttoncontent, Texture& texture, Texture* itemTexture, const bool read_mode) : font(font), readMode(read_mode)
{
	this->container.setSize(size);
	this->container.setPosition(conatiner_pos);
	this->container.setTexture(&texture);
	/*this->container.setFillColor(color);*/


	this->text.setFont(*this->font);
	this->text.setCharacterSize(25.f);
	this->text.setFillColor(Color::White);
	this->text.setOutlineThickness(2.f);
	this->text.setOutlineColor(Color::Black);
	this->text.setString(text);

	
	

	// Center the text within the container
	float textX = this->container.getPosition().x + (this->container.getSize().x - this->text.getGlobalBounds().width) / 2.f;
	float textY = this->container.getPosition().y + this->text.getGlobalBounds().height + 10.f;

	this->text.setPosition(textX, textY);

	if (itemTexture)
	{
		this->item.setSize(Vector2f(100.f, 100.f));
		this->item.setTexture(itemTexture);
		this->item.setPosition(textX, textY + 70.f);
	}

	float x = this->container.getPosition().x + 20.f;
	float y = this->container.getPosition().y + this->container.getSize().y / 1.5f;


	

	this->buttons["Default"] = new Button(x, y ,200.f, 150.f, this->font, buttoncontent,
		Color(255, 255, 255), Color(172, 172, 172), Color(49, 153, 132), texture, 25.f, false);


	this->isActive = true;
}



void GUI::PopUpWinodw::update(const Vector2f MousePos)
{
	if (this->isActive)
	{
		for (const auto& e : this->buttons)
		{
			e.second->update(MousePos);
		}
	}
}

const bool GUI::PopUpWinodw::buttonIsPressed(const string name) 
{
	if (this->buttons.find(name) != this->buttons.end())
		return this->buttons[name]->IsPressed();
	
	return false;
}





void GUI::PopUpWinodw::closeWindow()
{
	this->isActive = false;
}

void GUI::PopUpWinodw::openWindow()
{
	this->isActive = true;
}

void GUI::PopUpWinodw::ReadMode(const RenderWindow &window)
{
	if (readMode)
	{
		const Vector2f size = { static_cast<float>(window.getSize().x) , static_cast<float>(window.getSize().y) };
		this->blurBackround.setSize(Vector2f(size));
		this->blurBackround.setFillColor(Color(50, 50, 50, 120));

		float scale = 2.f;
		this->container.setScale(scale, scale);
		this->container.setPosition
		(
			(window.getSize().x / 2.f) - this->container.getGlobalBounds().width/ 2.f,
			(window.getSize().y / 2.f) - this->container.getGlobalBounds().height / 2.f
		);
		/*this->text.setScale(scale, scale);*/
		this->text.setPosition
		((this->container.getPosition().x + this->container.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		  (this->container.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height /2.f
		);
		this->item.setScale(scale, scale);


		auto& button_backround = this->buttons["Default"]->buttonComponent()->background;
		auto& button_text = this->buttons["Default"]->buttonComponent()->text;

		button_backround.setScale(scale, scale);
		button_text.setScale(scale, scale);

		button_backround.setPosition
		(
			this->container.getPosition().x + 10.f,
			(this->container.getPosition().y + this->container.getGlobalBounds().height) - (button_backround.getGlobalBounds().height /2.f + 50.f)
		);



		
		button_text.setPosition
		(
			(button_backround.getPosition().x + button_backround.getGlobalBounds().width / 2.f) - button_text.getGlobalBounds().width/ 2.f,
			(button_backround.getPosition().y + button_backround.getGlobalBounds().height / 2.f) - button_text.getGlobalBounds().height/ 2.f
		);
	}
}


void GUI::PopUpWinodw::render(RenderTarget& target)
{
	if (this->isActive)
	{
		if (this->readMode)
		{
			target.draw(this->blurBackround);
		}
		target.draw(this->container);
		target.draw(this->text);
		target.draw(this->item);
		for (const auto& e : this->buttons)
		{
			if (e.second)
				e.second->render(&target);
		}
	}
}


//////////////////////////////////////////////////////////////
//player Gui


//hp bar

playerGui::HpBar::HpBar( const float pos_X,
	const float pos_Y, Texture& texture,
	 Font& font, const string title, Color TextColor)
	: texture(texture), font(font)
{	

	this->sprite.setTexture(this->texture);
	this->sprite.setScale(0.35, 0.35);
	this->sprite.setPosition(pos_X - 76, pos_Y - 115);


	this->text.setFont(this->font);
	this->text.setCharacterSize(50);
	this->text.setFillColor(TextColor);
	this->text.setOutlineColor(Color::Black);
	this->text.setOutlineThickness(2);
	this->text.setPosition(this->sprite.getPosition().x + this->sprite.getGlobalBounds().width + 15.f, pos_Y);
	this->text.setString(title);

}





void playerGui::HpBar::render(RenderTarget& target, float hp)
{
	stringstream iss;
	iss << "Hp: " << hp << " +";
	this->text.setString(iss.str());

	target.draw(this->sprite);
	target.draw(this->text);

}
/*==================================================================*/

playerGui::ItemPreview::ItemPreview(const Vector2f size, const Vector2f Position,
	const short outlineThickness, const Color outlineColor,Texture &texture, Font &font) : font(font)
{
	this->Container.setSize(size);
	this->Container.setPosition(Position);
	this->Container.setFillColor(Color(50, 50, 50, 100));
	this->Container.setOutlineThickness(outlineThickness);
	this->Container.setOutlineColor(outlineColor);

	this->Item.setSize(size);
	this->Item.setPosition(Position);


	this->text.setCharacterSize(30);
	this->text.setFont(this->font);
	this->text.setFillColor(Color::White);
	this->text.setOutlineThickness(2);
	this->text.setOutlineColor(Color::Black);
	this->text.setPosition(Position.x - 15.f, Container.getSize().y + Position.y + text.getGlobalBounds().width + 10);


}

void playerGui::ItemPreview::update(Texture &texture, const bool item_is_in_inevntory)
{
	if(item_is_in_inevntory)
		this->Item.setTexture(&texture);
}

void playerGui::ItemPreview::render(RenderTarget& target, const string* info)
{
	if (info)
	{
		this->text.setString(*info);
		target.draw(this->text);
	}
	target.draw(this->Container);
	target.draw(this->Item);
}

/*dialogue window============================================================*/

GUI::DialogueWindow::DialogueWindow(const Vector2f size, const Vector2f position, const short char_size,
	shared_ptr<Font>font, const string text, Texture& texture, const Vector2f button_position)
{

	this->container.setSize(size);
	this->container.setFillColor(Color::Black);


	this->text.setFont(*font);
	this->text.setCharacterSize(char_size);
	this->text.setOutlineThickness(2.f);
	this->text.setOutlineColor(Color::Black);
	this->text.setFillColor(Color::White);
	this->text.setString(text);
	this->text.setPosition(position);

	this->buttons["Next"] = new Button(((button_position).x - 350.f), button_position.y - 200, 300, 100, font, "Next",
		Color(255, 255, 255), Color(172, 172, 172), Color(49, 153, 132), texture, 50.f);

	this->buttons["Skip"] = new Button(0.f, button_position.y - 200, 300, 100, font, "Skip",
		Color(255, 255, 255), Color(172, 172, 172), Color(49, 153, 132), texture, 50.f);

	this->keytime = 0.f;
	this->keytimeMax = 13.f;
}


const bool GUI::DialogueWindow::isskip()const
{
	return this->skip;
}

const bool GUI::DialogueWindow::Active()const
{
	return this->isActive;
}



void GUI::DialogueWindow::setActive(const bool active)
{
	this->isActive = active;
	this->renderTime.restart();
}

void GUI::DialogueWindow::setDialogue(const string line, RenderWindow& window)
{
	this->text.setString(line);

	this->text.setPosition(
		(window.getSize().x / 2.f) - this->text.getGlobalBounds().width / 2.f
		, (window.getSize().y / 2.f) - this->text.getGlobalBounds().height / 2.f);

}

bool GUI::DialogueWindow::getKeyTime()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}
	return false;
}

void GUI::DialogueWindow::update(const RenderWindow& window, const Vector2f MousePos, const float &dt)
{
		if (this->keytime < this->keytimeMax)
			this->keytime += 100.f * dt;

	

	if (this->isActive)
	{
		for (auto& e : this->buttons)
		{
			e.second->update(MousePos);
		}
		if (this->buttons["Next"]->IsPressed() && this->getKeyTime())
		{
			this->isActive = false;
		}
		else if (this->buttons["Skip"]->IsPressed() && this->getKeyTime())
		{
			this->skip = true;
		}
	}


	if (this->isActive)
	{
		if (this->renderTime.getElapsedTime().asSeconds() >= 5.f)
		{
			this->isActive = false;
		}
	}





}



void GUI::DialogueWindow::printElapsedTime()
{
	cout << this->renderTime.getElapsedTime().asSeconds() << "\n";
}


void GUI::DialogueWindow::render(RenderTarget& target)
{
	if (this->isActive)
	{


		target.draw(this->container);
		target.draw(this->text);
		for (const auto& e : this->buttons)
		{
			e.second->render(&target);
		}
	}


	
}

GUI::PopUpText::PopUpText(Font &font,const short char_size, const float render_time)
	:font(font),RenderTime(render_time)
{
	this->text->setFont(this->font);
	this->text->setCharacterSize(char_size);
	this->text->setFillColor(Color::White);
	this->text->setOutlineThickness(2);
	this->text->setOutlineColor(Color::Black);
	this->active = false;
	this->Finished = false;
}

void GUI::PopUpText::addText(const RenderWindow& window, const string text,
	const short* char_size, const float offset_x )
{
	
	this->text->setString(text);

	if (char_size)
		this->text->setCharacterSize(*char_size);

	this->text->setPosition(700.f + offset_x, this->text->getGlobalBounds().height + 10.f);
	this->active = true;
	this->Finished = false;
	this->timer->restart();
	
}




const bool GUI::PopUpText::isActive() const
{
	return this->active;
}

const bool GUI::PopUpText::isFinished() const
{
	return this->Finished;
}

void GUI::PopUpText::update()
{
	if (this->active && !this->Finished)
	{
		if (timer->getElapsedTime().asSeconds() >= this->RenderTime)
		{
			this->Finished = true;
			this->active = false;
		}
	}
	else if (!this->Finished)
	{
		timer->restart();
	}
}

void GUI::PopUpText::render(RenderTarget& target)
{
	
	if (!this->Finished && this->active)
	{
		target.draw(*this->text);
	}
		
}
