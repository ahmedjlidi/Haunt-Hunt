#pragma once



class TexturePreview
{
private:

	Texture& texture;
	RectangleShape texture_preview;
	IntRect TextureRect;
	RectangleShape background;
	RectangleShape frame;
	Sprite CustomSpritePreview;
	Text text;
	Font font;
	void PrevieWindow(const RenderWindow& window ,float grid_size, float pos_x, float pos_y
						,float width, float height);

	bool show;


	Texture backround_texture;

	void InitTexture();
public:
	TexturePreview(RenderWindow &window, Texture &texture,const IntRect& texture_rect, unsigned grid_size
					,float pos_x, float pos_y, float width, float height);

	void updateVisibilty(unsigned key, const bool keytime, bool & hideButton);
	void update(const IntRect& texture_rect);

	void setTexture(Sprite &sprite);
	const RectangleShape&  GetPreviewScreenPos() const;

	
	void render(RenderTarget &target, bool renderSpritePreviw);
};

