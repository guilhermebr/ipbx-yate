//
//  CallRouteMessage.cpp
//  ipbx_yate
//
//  Created by Guilherme Rezende <guilhermebr@gmail.com> on 17/04/11.
//  Copyright 2011 IPsafe. All rights reserved.
//

#include "CallRouteMessage.h"



CallRouteMessage::CallRouteMessage(Message &msg)
{
    int debug = 0;
    
    driver = msg.getValue("module");
    callername = msg.getValue("callername");
    caller = msg.getValue("caller");
    called = msg.getValue("called");
    address = msg.getValue("address");
    context = msg.getValue("context");
    timeout = msg.getValue("timeout");
    maxcall = msg.getValue("maxcall");
    rtp_f = msg.getValue("rtp_forward");
    username = msg.getValue("username");
    domain = msg.getValue("domain");
    in_line = msg.getValue("in_line");
    ip_host = msg.getValue("ip_host");
    ip_port = msg.getValue("ip_port");
    device = msg.getValue("device");
    sip_uri = msg.getValue("sip_uri");
    
    if (debug)
    {
        
        Output("######## NO LINE TRUST  ###########");
        
        Output("expired_user: '%s'", msg.getValue("expired_user"));
        Output("xsip_nonce_age: '%s'", msg.getValue("xsip_nonce_age"));
        
        
        Output("######## SIP  ###########");
        
        Output("antiloop: '%s'", msg.getValue("antiloop"));
        Output("ip_host: '%s'", msg.getValue("ip_host"));
        Output("ip_port: '%s'", msg.getValue("ip_port"));
        Output("sip_uri: '%s'", msg.getValue("sip_uri"));
        Output("sip_from: '%s'", msg.getValue("sip_from"));
        Output("sip_to: '%s'", msg.getValue("sip_to"));
        Output("sip_callid: '%s'", msg.getValue("sip_callid"));
        Output("device: '%s'", msg.getValue("device"));
        
        Output("######## DIVERT  ###########");
        
        Output("divert_reason: '%s'", msg.getValue("divert_reason"));
        Output("divert_privacy: '%s'", msg.getValue("divert_privacy"));
        Output("divert_screen: '%s'", msg.getValue("divert_screen"));
        Output("diverter: '%s'", msg.getValue("diverter"));
        Output("divertername: '%s'", msg.getValue("divertername"));
        Output("diverteruri: '%s'", msg.getValue("diverteruri"));
        
        Output("######## NAT / SDP  ###########");
        
        Output("rtp_nat_addr: '%s'", msg.getValue("rtp_nat_addr"));
        Output("rtp_addr: '%s'", msg.getValue("rtp_addr"));
        Output("sdp_raw: '%s'", msg.getValue("sdp_raw"));
        Output("rtp_forward: '%s'", msg.getValue("rtp_forward"));
        Output("reason: '%s'", msg.getValue("reason"));
        Output("diverteruri: '%s'", msg.getValue("diverteruri"));
        
        
        
    }
    
    Output("##############################");
    
    Output("DRIVER: '%s'", driver.c_str());
    Output("CALLERNAME: '%s'", callername.c_str());
    
    Output("CALLER: '%s'", caller.c_str());
    Output("CALLED: '%s'", called.c_str());
    Output("ADDRESS: '%s'",address.c_str());
    Output("CONTEXT: '%s'",context.c_str());
    Output("TIMEOUT: '%s'",timeout.c_str());
    Output("MAXCALL: '%s'",maxcall.c_str());
    Output("RTP_F: '%s'", rtp_f.c_str());
    Output("username: '%s'",username.c_str());
    Output("domain: '%s'", domain.c_str());
    Output("in_line: '%s'", in_line.c_str());
    Output("sip_uri: '%s'", sip_uri.c_str());

    
    
    Output("##############################");
}
