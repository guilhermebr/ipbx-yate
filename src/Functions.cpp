/*
 *  Functions.cpp
 *  ipbx_core
 *
 *  Created by Guilherme Rezende <guilhermebr@gmail.com>
 *
 */

#include "Functions.h"
#include <yatengine.h>

using namespace TelEngine;


bool QuerySingle(String& query,bool result)
{
    
    if (query.null())
        return false;
    
    Output("Query '%s'", query.c_str());
           
    Message m("database");
    
    m.setParam("account","ipbx");
    m.setParam("query",query);
    m.setParam("results",String::boolText(result));
    
    if (!Engine::dispatch(m))
	{
		Output("Query error '%s'",query.c_str());	
        return false;
	}

    if (!result) {
        return true;
    }
    
    if ((m.getIntValue("rows") != 1) || (m.getIntValue("columns") != 1))
    {
        Output("No return '%s'",query.c_str());	
        return false;
    }
    
    query.clear();
    
    Array* a = static_cast<Array*>(m.userObject("Array"));
    if (!a)
        return false;
    query = YOBJECT(String,a->get(0,1));
    Output("Result: %s",query.c_str());	
    
    return true;
    
}

Array* QueryMulti(Message& m, String& query)
{
    
    if (query.null())
        return 0;

    Output("Query '%s'", query.c_str());

    m.setParam("account","ipbx");
    m.setParam("query",query);
    m.setParam("results",String::boolText(true));
    
    if (!Engine::dispatch(m))
        return 0;
    
    int rows = m.getIntValue("rows",0);
    
    Output("Rows: '%d'", rows);

	Array *a = static_cast<Array*>(m.userObject("Array"));
    
    if (!(a && rows))
        return 0;

	return a;
}
