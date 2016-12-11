#ifndef CLIENT_H
#define CLIENT_H

#include <condition_variable>
#include <mutex>
#include <sstream>
#include <future>
#include <cassert>
#include <iterator>

#include "callbacks.h"
#include "messenger.h"
#include "observers.h"
#include "settings.h"
#include "types.h"

class Client: 
    public messenger::ILoginCallback,
    messenger::IMessagesObserver,
    messenger::IRequestUsersCallback
{
public:
    Client();
    Client(const std::string& userId);
    Client(const std::string& userId, const std::string& ip);
    Client(const std::string& userId, const std::string& ip, const unsigned short& port);
    
    ~Client();
    
    void SendMessage(const std::string& recpt,const std::string& text);//TODO: add other type of contetnt
    std::string ReceiveMessage();
    messenger::UserList GetActiveUsers();
    void OnOperationResult(messenger::operation_result::Type result) override;
    void OnOperationResult(messenger::operation_result::Type result, const messenger::UserList& users) override;
    void OnMessageStatusChanged(const messenger::MessageId& msgId, messenger::message_status::Type status) override;
    void OnMessageReceived(const messenger::UserId& senderId, const messenger::Message& msg) override;

    messenger::UserList userList;

private:
    

    std::shared_ptr<messenger::IMessenger> m_messenger;
    std::mutex m_mutex;
    std::condition_variable m_cv;
    bool m_ready;
    std::string m_recivedMsg;
    std::promise<messenger::UserList> m_userList;

    std::string _userId;
    std::string _ip;
    unsigned short _port;
    std::string _domain;
    
    static std::string _defaultUserId;
    static std::string _defaultIp;
    static unsigned short _defaultPort;
    static std::string _defaultdomain;
};

#endif