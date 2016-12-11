#include "Client.h"

#include <iostream>

#ifndef TESTS_H
#define TESTS_H

void TestMessages();
//void TestOfflineMessages();
//void TestUserList();

//####################################

void TestMessages()
{
    Client cl1("test1");
    Client cl2("test2");

    int seq = 1;
    while (seq <= 10)
    {
        std::stringstream msg;
        msg << "Message " << seq;
        cl1.SendMessage("test2", msg.str());
        std::cout << "\n#####\n";
        assert(cl2.ReceiveMessage() == msg.str());
        std::cout << "\n#####\n";
        seq++;
    }
}

//void TestOfflineMessages()
//{
//    Client cl1("test1");
//    cl1.SendMessage("test2", "Message 1");
//    cl1.SendMessage("test2", "Message 2");
//
//    Client cl2("test2");
//    assert(cl2.ReceiveMessage().compare("Message 1") == 0);
//    assert(cl2.ReceiveMessage().compare("Message 2") == 0);
//}
//
//void TestUserList()
//{
//    Client cl1("test1");
//    messenger::UserList list = cl1.GetActiveUsers();
//    assert(std::find_if(list.begin(), list.end(), [&](const messenger::User& user) -> bool
//    {
//        return user.identifier == "test1@localhost";
//    }) != list.end());
//}

#endif