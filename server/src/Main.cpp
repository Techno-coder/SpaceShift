#include <SFML/Network/UdpSocket.hpp>
#include <SFML/Network/Packet.hpp>
#include "../../shared/packets/HandshakeResponse.hpp"

int main() {
	sf::UdpSocket socket;
	if (socket.bind(54000) != sf::Socket::Done) {
		return 1;
	}

	unsigned short port = 54000;
	sf::IpAddress ipAddress = sf::IpAddress::LocalHost;
	sf::Packet packet;
	while (true) {
		if (socket.receive(packet, ipAddress, port) != sf::Socket::Done) {
			printf("Error occurred.");
		} else {
			HandshakeResponsePacket responsePacket;
			responsePacket.responseCode = HandshakeResponsePacket::ResponseCode::SUCCESSFUL;
			sf::Packet temp = responsePacket.generatePacket();
			socket.send(temp, ipAddress, port);
		}
	}

}