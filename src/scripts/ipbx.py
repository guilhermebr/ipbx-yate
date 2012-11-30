#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Author: Guilherme Rezende <guilhermebr@gmail.com>
#
# Script used to test YATE functions and messages

from libyate import Yate

class IPBX:
    def __init__(self):
        self.app = Yate()
        self.app.__Yatecall__ = self.retenv
        

    def retenv(self, ev):
        if ev == "":
            self.app.Output("Event is Empty")
        elif ev == "incoming":
            self.app.Output("Message: " + self.app.name + " id: " + self.app.id)
            
            if self.app.name == "engine.debug":
                    self.app.Output("ENGINE DEBUG")

            elif self.app.name == "engine.command":
                    self.app.Output("ENGINE COMMAND")
            
            elif self.app.name == "engine.status":
                    self.app.Output("ENGINE STATUS")
                    
            elif self.app.name == "engine.timer":
                    self.app.Output("ENGINE TIMER")
            
            elif self.app.name == "user.notify":
                    self.app.Output("USER NOTIFY")
                    
            elif self.app.name == "user.auth":
                    self.app.Output("USER AUTH")
            
            elif self.app.name == "user.register":
                    self.app.Output("USER REGISTER")
            
            elif self.app.name == "user.unregister":
                    self.app.Output("USER UNREGISTER")
            
            elif self.app.name == "call.route":
                    self.app.Output("CALL ROUTE")
                    
            elif self.app.name == "call.answered":
                    self.app.Output("CALL ANSWERED")        
                    
            elif self.app.name == "chan.hangup":
                    self.app.Output("CHAN HANGUP")
                    
            elif self.app.name == "chan.disconnected":
                    self.app.Output("CHAN DISCONNECTED")
                            
            elif self.app.name == "call.cdr":
                    self.app.Output("CALL CDR")       
                    
            else:
                    self.app.Acknowledge()
                    
            self.app.Acknowledge()
            self.count = self.count + 1

                    
        elif ev == "answer":
            self.app.Output("IPBX Answered: " + self.app.name + " id: " + self.app.id)
        elif ev == "installed":
            self.app.Output("IPBX Installed: " + self.app.name)
        elif ev == "uninstalled":
            self.app.Output("IPBX Uninstalled: " + self.app.name)
        else:
            self.app.Output("IPBX event: " + self.app.type)

    def uninstall(self):
        self.app.Uninstall("engine.timer")

    def main(self):
     
        self.count = 0

        self.app.Install("engine.timer", 10)
        self.app.Install("user.register", 10);
        self.app.Install("user.unregister", 10);
        self.app.Install("user.auth", 10);  
        self.app.Install("call.route", 10);
        self.app.Install("call.cdr", 10);

        self.app.Install("call.answered",50);
        self.app.Install("chan.disconnected",50);
        self.app.Install("chan.hangup", 10);

        self.app.Install("user.notify", 10);
        self.app.Install("engine.status");
        self.app.Install("engine.command");
        self.app.Install("engine.debug");

        while True:
            self.app.flush()
            
            if self.count == 10:
                self.uninstall()
                break
        
        self.app.Output("PYTHON: Bye!")

        # close file descriptors
        self.app.close()
        
    
# execution start here!
if __name__ == '__main__':
    a = IPBX()
    a.main()