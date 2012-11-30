/*
 *  CallRouteMessage.h
 *  ipbx_yate
 *
 *  Created by Guilherme Rezende <guilhermebr@gmail.com>
 *
 */


#include <yatengine.h>

using namespace TelEngine;

class CallRouteMessage
{
public:
    CallRouteMessage(Message &msg);
    

    String driver;
    String callername;
    String caller;
    String called;
    String address;
    String context;
    String timeout;
    String maxcall;
    String rtp_f;
    String username;
    String domain;
    String in_line;
    String ip_host;
    String ip_port;
    String device;
    String sip_uri;
};
