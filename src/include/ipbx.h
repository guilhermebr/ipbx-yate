/*
 *  ipbx.h
 *  ipbx_core
 *
 *  Created by Guilherme Rezende <guilhermebr@gmail.com>
 *
 */

#include <yatengine.h>

using namespace TelEngine;


class IPBX :  public Module
{
public:
	IPBX();
	~IPBX();
	virtual void initialize();
//	virtual bool received(Message &msg,int id);
	
private:	
	bool m_init;
	
};
