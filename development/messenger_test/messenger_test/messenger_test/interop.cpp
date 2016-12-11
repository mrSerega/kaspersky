#include "interop.h"

#include "Client.h"
#include "types.h"
#include <string.h>

Client* client = nullptr;

void  make_client(const char* login, const char* password)
{
    client = new Client(std::string(login));
}

void  delete_client() 
{
    if (client != nullptr) {
        delete client;
        client = nullptr;
    }
}

void  send_text_message(const char* recpt, const char* text_content)
{
    client->SendMessage(std::string(recpt), std::string(text_content));
}

const char* receive_text_message()
{
    return client->ReceiveMessage().data();
}

void get_users(const char** user_list) {
    client->userList = client->GetActiveUsers();
    int n = client->userList.size();
    for (int i = 0; i < n; i++) {
        user_list[i] = (client->userList[i].identifier).data();
        printf(user_list[i]);
    }
}