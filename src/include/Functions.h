/*
 *  Functions.h
 *  ipbx_yate
 *
 *  Created by Guilherme Rezende <guilhermebr@gmail.com>
 *
 */

#include <yatengine.h>

using namespace TelEngine;


bool QuerySingle(String& query,bool result);
Array* QueryMulti(Message& m, String& query);
