#include <iostream>
#include <cassert>
#include "Message.h"
#include "User.h"
#include "Encryption.h"
#include "Broker.h"

using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    os << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        os << vec[i];
        if (i != vec.size() - 1)
            os << ", ";
    }
    os << "]";
    return os;
}

int main() {
    Broker& broker = Broker::initBroker();
    auto lucas = User::getInstance("lucas", broker);
    auto bastien = User::getInstance("bastien", broker);
    auto pfeur = User::getInstance("pfeur", broker);

    lucas->connectUser();
    pfeur->connectUser();
    bastien->connectUser();

    // Test 1 : IDs uniques
    assert(lucas->getUserID() != bastien->getUserID());
    assert(lucas->getUserID() != pfeur->getUserID());
    assert(bastien->getUserID() != pfeur->getUserID());

    // Test 2 : Envoi et réception de message
    message_t msg;
    msg.senderID = lucas->getUserID();
    msg.targetID = bastien->getUserID();
    msg.content = "coucou bebou";
    lucas->sendMessage(msg);

    // Vérifie que le message est bien dans la boîte de Bastien
    auto messages = broker.getMessagesForUser(bastien->getUserID());
    assert(!messages.empty());
    assert(messages.front().sender_id == lucas->getUserID());

    // Test 3 : Réception/décryptage
    bastien->receiveMessage();

    // Test 4 : Utilisateurs connectés
    auto connected = broker.getAllConnectedUser();
    assert(std::find(connected.begin(), connected.end(), lucas->getUserID()) != connected.end());
    assert(std::find(connected.begin(), connected.end(), bastien->getUserID()) != connected.end());
    assert(std::find(connected.begin(), connected.end(), pfeur->getUserID()) != connected.end());

    // Test 4b : Utilisateurs connectés et déconnectés
    lucas->disconnectUser();
    connected = broker.getAllConnectedUser();
    assert(std::find(connected.begin(), connected.end(), lucas->getUserID()) == connected.end());
    assert(std::find(connected.begin(), connected.end(), bastien->getUserID()) != connected.end());
    assert(std::find(connected.begin(), connected.end(), pfeur->getUserID()) != connected.end());

    // Test 5 : Déconnexion et envoi de message
    bastien->disconnectUser();
    message_t msg2;
    msg2.senderID = pfeur->getUserID();
    msg2.targetID = bastien->getUserID();
    msg2.content = "tu es là ?";
    pfeur->sendMessage(msg2);

    // Bastien ne doit pas recevoir le message tant qu'il n'est pas reconnecté
    std::cout << "Rien ne doit être affiché ici" << std::endl;

    assert(broker.getMessagesForUser(bastien->getUserID()).size() == 1); // Le message est stocké
    bastien->receiveMessage(); // Doit afficher le message "tu es là ?"
    // Test 6 : Reconnexion et récupération
    std::cout << "Le message doit s'afficher ci-après" << std::endl;
    bastien->connectUser();
    bastien->receiveMessage(); // Doit afficher le message "tu es là ?"

    // Test 7 : Envoi par utilisateur non connecté
    std::cout << "Rien ne doit être affiché ici" << std::endl;
    message_t msg3;
    msg3.senderID = lucas->getUserID();
    msg3.targetID = bastien->getUserID();
    msg3.content = "test offline";
    lucas->sendMessage(msg3);
    bastien->receiveMessage();

    std::cout << "Tous les tests sont passés" << std::endl;
    return 0;
}
