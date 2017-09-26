#pragma once

#include <SFML/Config.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Network/IpAddress.hpp>

typedef sf::Uint16 GameID;
typedef std::pair<sf::IpAddress, unsigned short> PlayerIdentifier;
constexpr unsigned short SERVER_PORT = 54000;

const sf::Time TICK_SPEED = sf::seconds(1.0f / 20.0f);

const sf::Time AUTHENTICATION_TIMEOUT = sf::seconds(5.0f);
const sf::Time KEEP_ALIVE_TIMEOUT = sf::seconds(10.0f);
const sf::Time DISCONNECT_TIMEOUT = sf::seconds(20.0f);

const sf::Time TIME_BEFORE_GAME_START = sf::seconds(30.0f);

const unsigned long MAXIMUM_PLAYERS_PER_GAME = 8;
