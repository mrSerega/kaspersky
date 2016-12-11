#ifndef INTEROP_H
#define INTEROP_H

#define EXPORT __declspec(dllexport)

extern "C"
{
    void EXPORT make_client(const char* login, const char* password);//TODO: add password
    void EXPORT delete_client();
    void EXPORT send_text_message(const char* recpt, const char* text_content);
    EXPORT const char*  receive_text_message();
    EXPORT int add(int a, int b) { return a + b; }//TODO: delete this
    EXPORT void get_users(const char** user_list);
}

#endif