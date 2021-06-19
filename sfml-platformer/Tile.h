#pragma once

enum TileTypes {
	DEFAULT = 0,
	DAMAGING,
	DOODAD,
	PICKABLE
};

class Tile
{
private:

protected:
	sf::RectangleShape shape;
	bool collision;
	short type;
public:
	Tile();
	Tile(int grid_x, int grid_y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& texture_rect, bool collison = false, short type = TileTypes::DEFAULT);
	virtual ~Tile();

	const short& getType()const;

	const bool& getCollision()const;
	const sf::Vector2f& getPosition()const;
	const sf::FloatRect getGlobalBounds()const;
	const sf::IntRect getTextureRect() const;
	sf::RectangleShape getShape();

	void deleteTile();
	const bool intersects(const sf::FloatRect bounds)const;

	void update();
	void render(sf::RenderTarget& target);
};

