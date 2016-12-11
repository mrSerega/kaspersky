#include "Client.h"

#define ERROR_MSG "<error>"

#include <iostream> //TODO: delte this

//default values
std::string Client::_defaultUserId = "guest";
std::string Client::_defaultIp = "127.0.0.1";
unsigned short Client::_defaultPort = 80;
std::string Client::_defaultdomain = "@localhost";

Client::Client():
    Client(_defaultUserId, _defaultIp, _defaultPort)
{}

Client::Client(const std::string& userId) :
    Client(userId, _defaultIp, _defaultPort)
{}

Client::Client(const std::string& userId, const std::string& ip) :
    Client(userId, ip, _defaultPort)
{}

Client::Client(const std::string& userId, const std::string& ip, const unsigned short& port):
    _userId{userId},
    _ip{ip},
    _port{port},
    _domain{_defaultdomain}
{
    messenger::MessengerSettings settings;
    settings.serverUrl = _ip;
    //settings.serverPort = _port; TODO: do it right
    m_messenger = messenger::GetMessengerInstance(settings);

    messenger::SecurityPolicy securityPolicy;//TODO: do it customize???
    m_messenger->Login((_userId + _domain).c_str(), "", securityPolicy, this);//TODO: password!!!port

    std::unique_lock<std::mutex> lock(m_mutex);
    while(!m_ready)
    {
        m_cv.wait(lock);
    }

    m_messenger->RegisterObserver(this);
}


Client::~Client()
{
    m_messenger->Disconnect();
}

void Client::SendMessage(const std::string& recpt, const::std::string& text)//TODO: add other types of content
{
    messenger::MessageContent msg;
    msg.type = messenger::message_content_type::Text;
    std::copy(text.begin(), text.end(), std::back_inserter(msg.data));
    m_messenger->SendMessage(recpt + _domain, msg);
}

std::string Client::ReceiveMessage()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    while (m_recivedMsg.empty())
    {
        m_cv.wait(lock);
    }

    std::string res = m_recivedMsg;
    m_recivedMsg.clear();
    return res;
}

messenger::UserList Client::GetActiveUsers()
{
    m_messenger->RequestActiveUsers(this);
    return m_userList.get_future().get();
}

void Client::OnOperationResult(messenger::operation_result::Type result)
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_ready = true;
    m_cv.notify_all();
}

void Client::OnOperationResult(messenger::operation_result::Type result, const messenger::UserList& users)
{
    m_userList.set_value(users);
}

void Client::OnMessageStatusChanged(const messenger::MessageId& msgId, messenger::message_status::Type status)
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_recivedMsg = ERROR_MSG;
    m_cv.notify_all();
}

void Client::OnMessageReceived(const messenger::UserId& senderId, const messenger::Message& msg)
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_recivedMsg.assign(reinterpret_cast<const char*>(&msg.content.data[0]), msg.content.data.size());
    m_cv.notify_all();
}