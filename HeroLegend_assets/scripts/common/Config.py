from KBEDebug import *
import os
import json

class Config():
    def __init__(self):
        self.readCommonConfig()
    def readCommonConfig(self):
        try:
            module_path = os.path.dirname(__file__)    
            filename = module_path + '/../../res/conf/Common.json'
            f = open(filename)
            data = f.read()
            self.commonConfig = json.loads(data)
            DEBUG_MSG("RoleCount % s" % (self.commonConfig[0]['RoleCount']))
        finally:
            if f:
                f.close()
    def getCommonConfig(self,name):
        return self.commonConfig[0][name];
        