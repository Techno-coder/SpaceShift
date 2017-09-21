#pragma once

#include <SFML/Config.hpp>
#include <SFML/System/Time.hpp>

typedef sf::Uint64 PlayerID;
typedef sf::Uint16 GameID;

constexpr unsigned short SERVER_PORT = 54001; //TODO change later
const sf::Time TICK_SPEED = sf::seconds(1.0f / 20.0f);

const sf::Time AUTHENTICATION_TIMEOUT = sf::seconds(5.0f);
const sf::Time KEEP_ALIVE_TIMEOUT = sf::seconds(10.0f);
const sf::Time DISCONNECT_TIMEOUT = sf::seconds(20.0f);