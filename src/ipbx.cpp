/*
 *  ipbc.cpp
 *  ipbx_core
 *
 *  Created by Guilherme Rezende <guilhermebr@gmail.com>
 *
 */

#include <yatengine.h>
#include <yatephone.h>
#include <stdio.h>
#include <stdlib.h>

#include "include/ipbx.h"
#include "include/UserHandlers.h"
#include "include/EngineHandlers.h"
#include "include/CallHandlers.h"


using namespace TelEngine;


IPBX::IPBX()
: Module("ipbx","database"), m_init(false)
{
	Output(">>> Loaded module IPBX for database");
}

IPBX::~IPBX()
{
	Output(">>> Unloading module IPBX for database");
}

void IPBX::initialize()
{
    Output(">>> Initializing Module IPBX");
	
	//Limpa tabela de chamadas ativas, e campo de chamadas em uso dos ramais.
	String query;
//	query = "TRUNCATE TABLE chamadas_ativas; UPDATE ramais SET inuse_count=0;";
    query = "UPDATE ramais SET inuse_count=0;";


	Output("Query:'%s'",query.c_str());	
	
	Message m("database");
	
    m.setParam("account","ipbx");
    m.setParam("query",query);
    m.setParam("results",String::boolText(true));
	
	bool error = !Engine::dispatch(m) || m.getParam("error");
	if (error)
	{
		Output("Error Dispatch truncate!!!");	
	}
	
//	free(m);
	
	//Seta handlers para as mensagens
	
	if(!m_init) {
		Engine::install(new CallRouteHandler);
		Engine::install(new CallPreRouteHandler);
        Engine::install(new CallCdrHandler);
		Engine::install(new EngineTimerHandler);
		Engine::install(new EngineStatusHandler);
		Engine::install(new UserUnRegisterHandler);
		Engine::install(new UserRegisterHandler);
		Engine::install(new UserAuthHandler);


		m_init = true;
	}
	
	
	//Lista provedores que precisam enviar registro, e envia pedido de registro.

	query = "SELECT (CASE WHEN registro = 'Não' OR registro = 'Sim' THEN True ELSE False END) AS enabled, tecnologia as protocol, usuario as username, interval, codecs as formats, usuario as authname, senha as password, enderecoip  || ':' || porta as server, domain, outbound , localaddress, modified, enderecoip as account, id as gateway_id, status, TRUE AS gw FROM provedores WHERE registro = 'Sim' AND enderecoip IS NOT NULL AND usuario IS NOT NULL ORDER BY enderecoip;";
	
	Output("Query:'%s'",query.c_str());	
	
	Message m2("database");
	
    m2.setParam("account","ipbx");
    m2.setParam("query",query);
    m2.setParam("results",String::boolText(true));
	
	if (Engine::dispatch(m2))
	{
		int rows = m2.getIntValue("rows");
		if (rows>0)
		{
			Array* a = static_cast<Array*>(m2.userObject("Array"));
			int j;
			for (int i=1 ; i<=rows ; i++) 
			{
				Message *m3= new Message("user.login");
				
				for (j = 0; j < a->getColumns(); j++) 
				{
					String* s = YOBJECT(String,a->get(j,0));
					if (!(s && *s))
						continue;
					String name = *s;
					s = YOBJECT(String,a->get(j,i));
					if (!s)
						continue;
					m3->setParam(name,*s);
					Output("Returned: '%s' = '%s'",name.c_str(), s->c_str());	
				}
				Engine::enqueue(m3);
			} 
	
		}
			
	}
}

INIT_PLUGIN(IPBX);
/* vi: set ts=8 sw=4 sts=4 noet: */
