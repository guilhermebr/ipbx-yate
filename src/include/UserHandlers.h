/*
 *  UserHandlers.h
 *  ipbx_yate
 *
 *  Created by Guilherme Rezende <guilhermebr@gmail.com>
 *
 */

#include <yatengine.h>

using namespace TelEngine;

class UserAuthHandler : public MessageHandler
{
public:
    UserAuthHandler()
	: MessageHandler("user.auth",10) { }
    virtual bool received(Message& msg);
};

class UserRegisterHandler : public MessageHandler
{
public:
    UserRegisterHandler()
	: MessageHandler("user.register",10) { }
    virtual bool received(Message& msg);
};

class UserUnRegisterHandler : public MessageHandler
{
public:
    UserUnRegisterHandler()
	: MessageHandler("user.unregister",10) { }
    virtual bool received(Message& msg);
};
