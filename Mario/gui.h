#pragma once



enum Button_State

{	Button_Idle = 0, Button_Pressed , Button_Hover};

struct ButtonComponent
{
	RectangleShape& background;
	Text& text;

	ButtonComponent(RectangleShape& background, Text& text) : background(background)
		, text(text) {};
};


namespace GUI
{
	
	class Button
	{
	private:

		short unsigned ButtonState;
		short unsigned id;

		

		//Font* font;
		shared_ptr<Font> font = make_unique<Font>();
		Text text;

		RectangleShape background;



		Color IdleColor;
		Color HoverColor;
		Color ActiveColor;


		bool pressed;
		bool hover;

		

		 
	public:

		Button(float pos_x, float pos_y, float height, float width, shared_ptr<Font>font, string text,
			Color IdleColor, Color HoverColor, Color ActiveColor, Texture& texture, unsigned Char_size = 70, const bool ShowBackround = 0
			, short unsigned id = 0);


		

		void SetText(const string text);
		const string GetText();
		Vector2f GetButtonSize();
		const bool IsPressed() const;
		const short unsigned& getId()const;
		void SetId(const short unsigned id);
		const FloatRect getTextGlobalbounds() const ;
		void update(const Vector2f MousePos);

		void RenderButton(RenderTarget* target);
		
		void render(RenderTarget* target);

		const bool CustomIsPressed(FloatRect pos);

		bool test();
		
		ButtonComponent* buttonComponent();
		
	};

	class DropDownList
	{
	private:

		Button* activeElement;
		vector<Button*>list;
		RectangleShape test;
		shared_ptr<Font> font;
		Texture& texture;
		bool showList = false;
		unsigned charSize = 30;
		string ActiveElementText;

		float keytime;
		float keytimeMax;
		bool getKeyTime();
		

		void InitActiveElement(RenderWindow& window, shared_ptr<Font> font, Texture& texture, string list_nbr, float Pos_y
			, unsigned index, short unsigned id, short unsigned font_size = 35);
		
	public:
		DropDownList(RenderWindow &window ,shared_ptr<Font> font, Texture& texture, string list[]
		,unsigned elemnts_nbr,unsigned default_index, float Pos_y, short unsigned font_size = 35);
	    virtual ~DropDownList();

		const short unsigned& getId()const;
		void update(const Vector2f MousePos, const float &dt);
		
		void render(RenderTarget* target);

		const string GetListText();
	};

	class Label
	{
	private:
		shared_ptr<Font> font = make_unique<Font>();
		Text text;

		RectangleShape background;
	public:
		Label(float pos_x, float pos_y, float height, float width, shared_ptr<Font>font, string text,
			 Texture& texture,Color color, unsigned Char_size = 70, const bool ShowBackround = 1);

		void RenderLabel(RenderTarget* target);
		void render(RenderTarget* target);
	};


	class TextureSelector
	{
		bool active;
		float GridSize;

		RectangleShape bounds;
		Sprite sheet;
		
		RectangleShape selector;
		Vector2u MousePosGrid;
		IntRect TextureRect;
		 
		bool hide = false;


		


	public:
		TextureSelector(const Texture &texture_sheet,Color color,float grid_size, float height, float width,float x, float y);

		void  ChangeTexture(IntRect& texture_rect, const bool allow);
		void update(const Vector2f MousePos, IntRect& texture_rect, const bool allow);

		const bool TextureSelectorIsActive()const;
		
		void show(const bool show);

		void renderSelector(RenderTarget& target);
		void renderTextureSelectorWindow(RenderTarget& target);
		


		
		
	};

	class PopUpWinodw
	{
	private:
		RectangleShape container;
		RectangleShape blurBackround;
		RectangleShape item;
		map<string, Button*>buttons;
		Text text;
		shared_ptr<Font>font = make_shared<Font>();
		bool isActive;
		bool readMode = false;

	public:
		PopUpWinodw(const Vector2f size, const Vector2f conatiner_pos, const Color color,
			shared_ptr<Font>font, const string text,const string buttoncontent,Texture &texture
		,Texture* itemTexture = nullptr, const bool read_mode = false);

		void closeWindow();
		void openWindow();
		void ReadMode(const RenderWindow &window);
		const bool buttonIsPressed(const string name);
		void update(const Vector2f MousePos);
		void render(RenderTarget& target);
	};



	class DialogueWindow
	{
	private:
		

		RectangleShape container;
		Text text;
		map<string, Button*> buttons;
		shared_ptr<Font>font = make_shared<Font>();
		bool isActive;
		Clock renderTime;
		
		float keytime;
		float keytimeMax;

		bool skip = false;


	public:
		DialogueWindow(const Vector2f size, const Vector2f position, const short char_size,
			shared_ptr<Font>font, const string text,  Texture& texture, const Vector2f button_position);

		const bool isskip()const ;
		const bool Active()const;
		bool getKeyTime();
		void setActive(const bool active);
		void setDialogue(const string line, RenderWindow& window);
		void update(const RenderWindow& window, const Vector2f MousePos, const float& dt);
		void printElapsedTime();
		void render(RenderTarget& target);
	};

	class PopUpText
	{
	private:
		bool active;
		bool Finished;
		float RenderTime;
		Font &font;
		shared_ptr<Text> text = make_shared<Text>();
		shared_ptr<Clock> timer = make_shared<Clock>();

	public:
		PopUpText(Font &font,const short char_size, const float render_time);
		void addText(const RenderWindow& window, const string text, 
		const short* char_size = nullptr, const float offset_x = 0.f);
		const bool isActive()const;
		const bool isFinished()const;
		void update();
		void render(RenderTarget& target);

	};

}
namespace playerGui
{
	class HpBar
	{
	private:
		Texture& texture;
		Sprite sprite;
		Font& font;
		Text text;
	public:

		HpBar(const float pos_X,
			const float pos_Y, Texture& texture
		,Font &font, const string title, Color TextColor);

		
		void render(RenderTarget& target, float hp);

	};

	class ItemPreview
	{
	private:
		RectangleShape Item;
		RectangleShape Container;
		Text text;
		Font font;

	public:
		ItemPreview(const Vector2f size, const Vector2f Position,
			const short outlineThickness, const Color outlineColor, Texture &texture, Font &font);

		
		void update(Texture& texture, const bool item_is_in_inevntory);
		void render(RenderTarget& target, const string *info = nullptr);
	};

}

