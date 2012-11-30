/*
 *  EngineHandlers.h
 *  ipbx_yate
 *
 *  Created by Guilherme Rezende <guilhermebr@gmail.com>
 *
 */

#include <yatengine.h>

using namespace TelEngine;



class EngineTimerHandler : public MessageHandler
{
public:
    EngineTimerHandler()
	: MessageHandler("engine.timer",10) { }
    virtual bool received(Message& msg);
};

class EngineStatusHandler : public MessageHandler
{
public:
    EngineStatusHandler()
	: MessageHandler("engine.status") { }
    virtual bool received(Message& msg);
};
