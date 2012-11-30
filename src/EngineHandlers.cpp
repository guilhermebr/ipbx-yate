/*
 *  EngineHandlers.cpp
 *  ipbx_yate
 *
 *  Created by Guilherme Rezende <guilhermebr@gmail.com>
 *
 */


#include <yatengine.h>
#include <yatephone.h>
#include <stdio.h>
#include <stdlib.h>

#include "include/EngineHandlers.h"


using namespace TelEngine;


bool EngineStatusHandler::received(Message &msg)
{
	Output("Received message '%s'", msg.c_str());
	
	String result = "name=ipbx,provedores=";
	String query;
	query = "SELECT enderecoip,(CASE WHEN status IS NULL THEN 'offline' else status END) as status FROM provedores WHERE enabled IS TRUE AND usuario IS NOT NULL";

	Message *m = new Message("database");
	
    m->setParam("account","ipbx");
    m->setParam("query",query);
    m->setParam("results",String::boolText(true));
	
	if (Engine::dispatch(m))
	{
		int rows = m->getIntValue("rows");
		if (rows>0)
		{
			result.append(rows);
			for (int i=1 ; i<=rows ; i++) 
			{
				Array* a = static_cast<Array*>(m->userObject("Array"));
				result += YOBJECT(String,a->get(0,i));
				result += "=";
				result += YOBJECT(String,a->get(1,i));
				result += ";";
				
			} 
		}
	}
	
	result += "\n";
	
	msg.retValue() = result;

	return true;
}


bool EngineTimerHandler::received(Message &msg)
{
	
	
	String query;
	
	query = "SELECT registro as enabled, protocol, usuario as username, interval, codecs as formats, usuario as authname, senha as password, enderecoip  || ':' || porta as server, domain, outbound , localaddress, modified, enderecoip as account, id as gateway_id, status, TRUE AS gw FROM provedores WHERE registro IS TRUE AND modified IS TRUE AND usuario IS NOT NULL";

//	Output("Query:'%s'",query.c_str());	
	
	Message *m = new Message("database");
	
    m->setParam("account","ipbx");
    m->setParam("query",query);
    m->setParam("results",String::boolText(true));
	
	if (Engine::dispatch(m))
	{
		int rows = m->getIntValue("rows");
		if (rows>0)
		{
			int j;
			for (int i=1 ; i<=rows ; i++) 
			{
				Message *msg= new Message("user.login");
				Array* a = static_cast<Array*>(m->userObject("Array"));
				
				for (j = 0; j < a->getColumns(); j++) 
				{
					String* s = YOBJECT(String,a->get(j,0));
					if (!(s && *s))
						continue;
					String name = *s;
					s = YOBJECT(String,a->get(j,i));
					if (!s)
						continue;
					msg->setParam(name,*s);
					Output("Retornou: '%s' = '%s'",name.c_str(), s->c_str());	
				}
				Engine::enqueue(msg);
			} 
			
		}
		
	}
	
	query = "UPDATE ramais SET location=NULL,expires=NULL WHERE expires IS NOT NULL AND expires<=CURRENT_TIMESTAMP; UPDATE provedores SET modified='f' WHERE modified='t' AND usuario IS NOT NULL";
	
	//	Output("Query:'%s'",query.c_str());	
	
	m = new Message("database");
	
    m->setParam("account","ipbx");
    m->setParam("query",query);
    m->setParam("results",String::boolText(false));
	
	if (!Engine::dispatch(m))
	{
		Output("Error Dispatch!!!");	
		return false;
	}
	
	return true;
}
