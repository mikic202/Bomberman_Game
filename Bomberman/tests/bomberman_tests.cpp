#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../Items/Bomb.h"


TEST_CASE("Tests for Item class")
{
	SECTION("Setters and getters tests")
	{
		Item item;
		item.set_name("new_item");
		REQUIRE(item.name() == "new_item");

		sf::Vector2f  pos = { 3, 3 };
		item.set_position(pos);
		REQUIRE(item.position() == pos);

		sf::Vector2f  scale = { .3, .3 };
		item.rescale(scale);
		sf::Sprite items_sprite = item.item_sprite();
		REQUIRE(items_sprite.getPosition() == pos);
		REQUIRE(items_sprite.getScale() == scale);

		REQUIRE_THROWS(item.load_immage_from_file("abcnnd"));
	}
}


TEST_CASE("Tests for Bomb class")
{
	SECTION("Initialization tests")
	{
		sf::Vector2f pos = { 2, 1 };
		sf::Vector2f scale = { .5, .6 };
		Bomb bomb(pos, 5, 9, 3, scale);

		REQUIRE(bomb.delay() == 9);

		REQUIRE(bomb.radius() == 5);

		REQUIRE(bomb.strength() == 3);
	}


	SECTION("Setters tests")
	{
		Bomb bomb({1, 2}, 5, 9, 3, {1, 2});

		bomb.set_delay(4);
		REQUIRE(bomb.delay() == 4);

		bomb.set_radius(1);
		REQUIRE(bomb.radius() == 1);

		bomb.set_strength(7);
		REQUIRE(bomb.strength() == 7);
	}

	SECTION("blowing up tests")
	{
		Bomb bomb({ 1, 2 }, 5, 2, 3, { 1, 2 });

		REQUIRE(!bomb.did_blow());

		//bool n = bomb.did_blow();
		//REQUIRE(bomb.did_blow());
	}
}
