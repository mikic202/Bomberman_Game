#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../Items/Bomb.h"
#include"../Items/Box.h"
#include"../Game Board/StoryModeBoard.h"
#include"../Game Board/VersusModeBoard.h"


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


TEST_CASE("Testing Wall class")
{
	SECTION("Ititialization tests")
	{
		Wall wall({ 1, 2 }, { 3, 4 });

		sf::Sprite wall_sprite = wall.item_sprite();

		REQUIRE(wall.get_global_bounds() == wall_sprite.getGlobalBounds());
	}
}


TEST_CASE("Tsting Box class")
{
	SECTION("Initialization tests")
	{
		Box box({ 1, 2 }, 2, { 5, 6 });

		REQUIRE(box.hits_to_brake() == 2);
	}

	SECTION("Setters tests")
	{
		Box box({ 1, 2 }, 2, { 5, 6 });

		box.set_hits_to_brake(4);
		REQUIRE(box.hits_to_brake() == 4);
	}

	SECTION("Box hitting test")
	{
		Box box({ 1, 2 }, 5, { 5, 6 });

		REQUIRE(!box.hit(2));

		REQUIRE(box.hit(4));
	}
}

//TODO TESTS FOR PLAYER
TEST_CASE("Tests for GameBoard class")
{
	SECTION("Setters and getters tests tests")
	{
		GameBoard board;
		//Player player(1, 2, 3, 4, 5, 6);

		//board.add_player(player);
		//REQUIRE(board.players()[0] -> get_hp() == 6);

	}

	SECTION("add_items tests")
	{
		GameBoard board;

		board.add_item(Wall());
		REQUIRE(board.items().size() == 1);
	}
}


TEST_CASE("Tests for StoryModeBoard class")
{
	SECTION("Constructor tests")
	{
		StoryModeBoard board(4, 1);

		REQUIRE(board.level_number() == 4);

		REQUIRE(board.items().size() <= 20*50/4 + 40);
	}

	SECTION("Getters tests")
	{
		StoryModeBoard board(4, 1);

		REQUIRE(board.door_position().x >= 50/2);

		
	}
}


TEST_CASE("Tests for VersusModeBoard")
{
	SECTION("Constructor tests")
	{
		VersusModeBoard board(16);

		REQUIRE(board.size() == 16);

		REQUIRE(board.items().size() >= 16 * 16 / 4);
	}
}
