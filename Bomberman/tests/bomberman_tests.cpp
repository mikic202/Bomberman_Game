#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../Items/Bomb.h"
#include"../Items/Box.h"
#include"../Game Board/StoryModeBoard.h"
#include"../Game Board/VersusModeBoard.h"
#include <Windows.h>


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
		Bomb bomb(pos, 5, 3, 3, scale);

		REQUIRE(bomb.delay() == 3);

		REQUIRE(bomb.radius() == 5);

		REQUIRE(bomb.strength() == 3);
	}


	SECTION("Setters tests")
	{
		Bomb bomb({1, 2}, 5, 3, 3, {1, 2});

		bomb.set_delay(2);
		REQUIRE(bomb.delay() == 2);

		bomb.set_radius(1);
		REQUIRE(bomb.radius() == 1);

		bomb.set_strength(7);
		REQUIRE(bomb.strength() == 7);
	}

	SECTION("blowing up tests")
	{
		Bomb bomb({ 1, 2 }, 5, 2, 3, { 1, 2 });

		REQUIRE(!bomb.did_blow());


		// Test below generates additional procesing time
		// but it works

		//Sleep(3000);
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
		REQUIRE(wall.item_sprite().getPosition().x == 1);
		REQUIRE(wall.item_sprite().getScale().x == 3);
	}

	SECTION("Test coliding with player")
	{
		sf::Texture test_texture;
		if (!test_texture.loadFromFile(PLAYER_PATH));
		Wall wall({ 1, 2 }, { 3, 4 });
		Player player({ 1, 2 }, test_texture, { 3, 4 }, 2);
		bool boll_val = wall.is_coloding_player(std::make_shared<Player>(player));
		REQUIRE(boll_val);
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


TEST_CASE("Explosion class tests")
{
	SECTION("Initialization tests")
	{
		REQUIRE_NOTHROW(Explosion({ 1, 2 }, { 3, 4 }));
	}

	SECTION("Test explosion expiring")
	{
		Explosion explosion({ 1, 2 }, { 3, 4 });

		Sleep(1010);
		REQUIRE(explosion.did_end());
	}
}


TEST_CASE("Door class tests")
{
	SECTION("Initialization tests")
	{
		REQUIRE_NOTHROW(Door({ 1, 2 }, { 3, 4 }));
	}
}


//TODO TESTS FOR PLAYER
TEST_CASE("Tests for GameBoard class")
{
	SECTION("Setters and getters tests tests")
	{
		sf::Texture test_texture;
		GameBoard board;
		Player player({ 1, 2 }, test_texture, { 3, 4 }, 2);

		board.add_player(player);
		REQUIRE(board.players()[0] -> get_hp() == 3);

	}

	SECTION("add_items tests")
	{
		GameBoard board;

		board.add_item(Wall());
		REQUIRE(board.items().size() == 1);
	}

	SECTION("remove_items tests")
	{
		GameBoard board;

		board.add_item(Wall());

		board.remove_item(0);
		REQUIRE(board.items().size() == 0);
	}
}


TEST_CASE("Tests for StoryModeBoard class")
{
	sf::Texture test_texture;
	SECTION("Constructor tests")
	{
		StoryModeBoard board(4, 1, test_texture, test_texture, test_texture);

		REQUIRE(board.level_number() == 4);

		REQUIRE(board.items().size() <= 20*50/4 + 40);
	}

	SECTION("Getters tests")
	{
		StoryModeBoard board(4, 1, test_texture, test_texture, test_texture);

		REQUIRE(board.door_position().x >= 50/2);

		
	}

	SECTION("Move items tests")
	{
		StoryModeBoard board(4, 1, test_texture, test_texture, test_texture);

		sf::Vector2f initial_position = board.items()[0]->position();
		board.move_items({ 20, 0 });
		REQUIRE((board.items()[0]->position().x == initial_position.x + 20.f && board.items()[0]->position().y == initial_position.y));
	}
}


TEST_CASE("Tests for VersusModeBoard")
{
	SECTION("Constructor tests")
	{
		sf::Texture test_texture;
		VersusModeBoard board(16, test_texture, test_texture);

		REQUIRE(board.size() == 16);

		REQUIRE(board.items().size() >= 16 * 16 / 4);
	}
}
