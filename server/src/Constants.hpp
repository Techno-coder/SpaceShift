#pragma once

#include <SFML/Config.hpp>
#include <SFML/System/Time.hpp>

typedef sf::Uint64 PlayerID;
typedef sf::Uint16 GameID;

constexpr unsigned short SERVER_PORT = 54001;
const sf::Time TICK_SPEED = sf::seconds(1.0f / 20.0f);
