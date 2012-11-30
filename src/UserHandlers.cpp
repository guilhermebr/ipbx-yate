/*
 *  UserHandlers.cpp
 *  ipbx_yate
 *
 *  Created by Guilherme Rezende on 01/04/11.
 *  Copyright 2011 IPsafe. All rights reserved.
 *
 */

#include <yatengine.h>
#include <yatephone.h>
#include <stdio.h>
#include <stdlib.h>

#include "include/UserHandlers.h"

using namespace TelEngine;

bool UserAuthHandler::received(Message &msg)
{
	
	Output("Received message '%s'", msg.c_str());
	
	
	String username;
	username = msg.getValue("username");
	if (!username)
	{
		Output("Fail Username: %s", username.c_str());
		return false;
	}
	
	Output("Username: %s", username.c_str());
	
	String query;
	
	query = "SELECT senha FROM ramais WHERE ramal='";
	query.append(username);
	query.append("' AND senha IS NOT NULL AND senha<>''");
	
	Output("Query:'%s'",query.c_str());	
	
	
	
	Message m("database");
	
	m.setParam("account","ipbx");
	m.setParam("query",query);
	m.setParam("results",String::boolText(true));
	
	
	
	if (!Engine::dispatch(m))
	{
		Output("Error Dispatch!!!");	
		return false;
	}
	
	if (m.getIntValue("rows") < 1)
	{
		Output("Error GetInValue!!!");	
		return false;
	}
	
	Array* a = static_cast<Array*>(m.userObject("Array"));
	if (!a)
		return false;
	String result = YOBJECT(String,a->get(0,1));
	Output("Resultado da query '%s' é %s",query.c_str(),result.c_str());	
	msg.retValue() = result;	
	
	return true;
}

bool UserRegisterHandler::received(Message &msg)
{
	
	Output("Received message '%s'", msg.c_str());
	
	
	
	String query;
	
	query = "UPDATE ramais SET location='";
	query.append(msg.getValue("data"));
	query.append("',expires=CURRENT_TIMESTAMP + INTERVAL '");
	query.append(msg.getValue("expires"));
	query.append(" s' WHERE ramal='");
	query.append(msg.getValue("username"));
	query.append("'");
	
	Output("Query:'%s'",query.c_str());	
	
	Message m("database");
	
    m.setParam("account","ipbx");
    m.setParam("query",query);
    m.setParam("results",String::boolText(false));
	
	if (!Engine::dispatch(m))
	{
		Output("Error Dispatch!!!");	
		return false;
	}
	
	return true;
}


bool UserUnRegisterHandler::received(Message &msg)
{
	
	Output("Received message '%s'", msg.c_str());
	
	
	
	String query;
	
	query = "UPDATE ramais SET location=NULL,expires=NULL WHERE expires IS NOT NULL AND ramal='";
	query.append(msg.getValue("username"));
	query.append("'");
	
	Output("Query:'%s'",query.c_str());	
	
	Message m("database");
	
    m.setParam("account","ipbx");
    m.setParam("query",query);
    m.setParam("results",String::boolText(false));
	
	if (!Engine::dispatch(m))
	{
		Output("Error Dispatch!!!");	
		return false;
	}
	
	return true;
}
