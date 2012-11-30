/*
 *  CallHandlers.h
 *  ipbx_yate
 *
 *  Created by Guilherme Rezende <guilhermebr@gmail.com>
 *
 */

#include <yatengine.h>

using namespace TelEngine;


class CallRouteHandler : public MessageHandler
{
public:
    CallRouteHandler()
	: MessageHandler("call.route",10) { }
    virtual bool received(Message& msg);
};


class CallPreRouteHandler : public MessageHandler
{
public:
    CallPreRouteHandler()
	: MessageHandler("call.preroute",10) { }
    virtual bool received(Message& msg);
};

class CallCdrHandler : public MessageHandler
{
public:
    CallCdrHandler()
	: MessageHandler("call.cdr",10) { }
    virtual bool received(Message& msg);
};
