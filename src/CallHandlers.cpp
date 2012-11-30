/*
 *  CallHandlers.cpp
 *  ipbx_yate
 *
 *  Created by Guilherme Rezende <guilhermebr@gmail.com>
 *
 */


#include <yatengine.h>
#include <yatephone.h>
#include <stdio.h>
#include <stdlib.h>

#include "include/CallHandlers.h"
#include "include/Functions.h"
#include "include/CallRouteMessage.h"



using namespace TelEngine;

bool CallRouteHandler::received(Message &msg)
{
    
	
	Output("Received message '%s'", msg.c_str());
    CallRouteMessage callvars(msg);

    
	String query;

	//Primeiro verifica Origem
    
	String location = callvars.driver + "/" + callvars.driver + ":" + callvars.caller + "@" + callvars.address;
    
    
	query = "SELECT 'from inside' as call_type FROM ramais WHERE ramal = '" + callvars.caller + "' AND location LIKE '"+ location+ "%' ";

    query += "UNION SELECT 'from outside' as call_type FROM provedores WHERE enderecoip = '" + callvars.ip_host + "'";
    
    
	if (!QuerySingle(query,true))
    {
        //Chamada de origem desconhecida. Adicionar a Log de Segurança
        Output("Unknown origin: '%s'", callvars.sip_uri.c_str());
        msg.setParam("error","noauth");
        return false;
    }
    
    Output("Result QUERY: '%s'",query.c_str());
    
    String call_type = query;
	
    Output("CALL_TYPE: '%s'",call_type.c_str());

    if (call_type == "from outside")
    {
    
        Output("Routing to DID: '%s'",callvars.called.c_str());
        return true;
        // return  routeToDid(callvars,msg)
    }
	
    //Verifica Destino (Interno ou externo?)
    Output("Internal Call");

    query.clear();
    

    query = "SELECT location, (CASE WHEN location IS NULL OR naoperturbe IS TRUE THEN 'offline' ELSE 'online' END) AS error FROM ramais WHERE ramal = '" + callvars.called + "'";
   
    Message m("database");

    Array *a = QueryMulti(m, query);
    
    if(!a) //|| (a->getRows() < 1)
    {
        Output("Device dont found... bye");
        msg.setParam("error","noroute");
        return true;
    }
    
    Output("Internal Call to Device");
    
    //Route to Ramal 
    String error = YOBJECT(String,a->get(1,1));
        
    if (error == "offline") 
    {
        //  query = "";
        Output("Device offline or in do not disturb state");
        msg.setParam("error","noroute");
        return true;
    }
        
    location = YOBJECT(String,a->get(0,1));
        
    Output("[Online] location: '%s'",location.c_str());
    msg.setParam("ipbx", "ok");
    msg.retValue() = location;	

	return true;
	
}


bool CallPreRouteHandler::received(Message &msg)
{
	
	Output("Received message '%s'", msg.c_str());
	
	String caller = msg.getValue("caller");
	
	Output("CALLER: '%s' :: Used after for Blacklist.", caller.c_str());
	
	return true;

}

bool CallCdrHandler::received(Message &msg)
{
	
	Output("Received message '%s'", msg.c_str());
	
	String operation = msg.getValue("operation");
    String reason = msg.getValue("reason");
    
	
	Output("Operation: '%s'", operation.c_str());
    
    if (operation == "initialize")
    {
        String query;
        query = "INSERT INTO log_chamadas(time, chan, address, direction, billid, caller, called, duration, billtime, ringtime, status, reason, ended) VALUES(TIMESTAMP 'EPOCH' + INTERVAL '";
        
        query += msg.getValue("time");
        query += " s', '";
        query += msg.getValue("chan");
        query += "', '"; 
        query += msg.getValue("address");
        query += "', '";
        query += msg.getValue("direction");
        query += "', '";
        query += msg.getValue("billid");
        query += "', '";
        query += msg.getValue("caller");
        query += "', '";
        query += msg.getValue("called");
        query += "', INTERVAL '";
        query += msg.getValue("duration");
        query += " s', INTERVAL '";
        query += msg.getValue("billtime");
        query += " s', INTERVAL '";
        query += msg.getValue("ringtime");
        query += " s', '";
        query += msg.getValue("status");
        query += "', '" + reason + "', false)";
        
        query += "; UPDATE ramais SET inuse_count=(CASE WHEN inuse_count IS NOT NULL THEN inuse_count+1 ELSE 1 END) WHERE ramal='";
        query += msg.getValue("external");
        query += "'";    
        
        if (!QuerySingle(query,false))
        {
            //Chamada de origem desconhecida. Adicionar a Log de Segurança
            Output("Error inserting CDR ");
            return false;
        }
    
    }
    
    if (operation == "update")
    {
        
        String query;
        
        query = "UPDATE log_chamadas SET address='";
        query +=  msg.getValue("address");
        query += "', direction='";
        query +=  msg.getValue("direction");
        query += "', billid='";
        query +=  msg.getValue("billid");
        query += "', caller='";
        query +=  msg.getValue("caller");
        query += "', called='";
        query +=  msg.getValue("called");
        query += "', duration=INTERVAL '";
        query +=  msg.getValue("duration");
        query += " s', billtime=INTERVAL '";
        query +=  msg.getValue("billtime");
        query += " s', ringtime=INTERVAL '";
        query +=  msg.getValue("ringtime");
        query += " s', status='";
        query +=  msg.getValue("status");
        query += "', reason='" + reason + "' WHERE chan='";
        query +=  msg.getValue("chan");
        query += "' AND time=TIMESTAMP 'EPOCH' + INTERVAL '";
        query +=  msg.getValue("time");
        query += " s'";
        
        if (!QuerySingle(query,false))
        {
            //Chamada de origem desconhecida. Adicionar a Log de Segurança
            Output("Error inserting CDR ");
            return false;
        }
        
    }
    
    if (operation == "finalize")
    {
        String direction(msg.getValue("direction"));
        
        String query;
        
        query = "UPDATE log_chamadas SET address='";
        query += msg.getValue("address");
        query += "', direction='";
        query += direction;
        query += "', billid='";
        query += msg.getValue("billid");
        query == "', caller='";
        query += msg.getValue("caller");
        query += "', called='";
        query += msg.getValue("called");
        query += "', duration=INTERVAL '";
        query += msg.getValue("duration");
        query += " s', billtime=INTERVAL '";
        query += msg.getValue("billtime");
        query += " s', ringtime=INTERVAL '";
        query += msg.getValue("ringtime");
        query += " s', status='";
        query += msg.getValue("status");
        query += "', reason='" + reason + "', ended='t' WHERE chan='";
        query += msg.getValue("chan");
        query += "' AND time=TIMESTAMP 'EPOCH' + INTERVAL '";
        query += msg.getValue("time");
        query += " s'";
      
        query += ";UPDATE ramais SET inuse_count=(CASE WHEN inuse_count>0 THEN inuse_count-1 ELSE 0 END), inuse_last=now() WHERE ramal='";
        query += msg.getValue("external");
        query += "'";
        
        
        //incoming log
        //if (direction == "incoming")
        //{
        //     query += ";INSERT INTO relatorio(origem, ramal, agente, destino, desvio, status, duracao, datachamada,provedor, nome, tipo_agente, valor, tipo_chamada, observacao, billid) VALUES(";
            
            Output("IPBX VARIABLE: '%s'", msg.getValue("id"));
            
        //}
        
        
        
        if (!QuerySingle(query,false))
        {
            //Chamada de origem desconhecida. Adicionar a Log de Segurança
            Output("Error inserting CDR ");
            return false;
        }
        
        
    }
	
	return true;
    
}

	
