# -*- coding: utf-8 -*-
import KBEngine
from KBEDebug import *
from ROLE_INFOS import TRoleInfos
from ROLE_INFOS import TRoleInfosList
from Config import Config
from ErrCode import ErrCode

class Account(KBEngine.Proxy):
	def __init__(self):
		KBEngine.Proxy.__init__(self)
		self.activeRole = None
		
	def onTimer(self, id, userArg):
		"""
		KBEngine method.
		使用addTimer后， 当时间到达则该接口被调用
		@param id		: addTimer 的返回值ID
		@param userArg	: addTimer 最后一个参数所给入的数据
		"""
		DEBUG_MSG(id, userArg)
		
	def onEntitiesEnabled(self):
		"""
		KBEngine method.
		该entity被正式激活为可使用， 此时entity已经建立了client对应实体， 可以在此创建它的
		cell部分。
		"""
		INFO_MSG("account[%i] entities enable. mailbox:%s" % (self.id, self.client))
			
	def onLogOnAttempt(self, ip, port, password):
		"""
		KBEngine method.
		客户端登陆失败时会回调到这里
		"""
		INFO_MSG(ip, port, password)
		return KBEngine.LOG_ON_ACCEPT
		
	def onClientDeath(self):
		"""
		KBEngine method.
		客户端对应实体已经销毁
		"""
		DEBUG_MSG("Account[%i].onClientDeath:" % self.id)
		self.destroy()
	def reqRoleList(self):
		"""
		请求角色列表

		"""
		self.client.onReqRolesListResule(self.roles)
	def reqCreateRole(self,roleTmpl,name):
		"""
		请求创建角色
		"""
		"""
		判断能不能创建了
		"""
		roleinfo = TRoleInfos()
		roleinfo.extend([0,'',0,0])
		if(len(self.roles)) >= Config.getCommonConfig('RoleCount'):
			self.client.onCreateRoleResult(ErrCode.ACCOUNT_ROLE_TOO_MUCH,roleinfo)
			return
		# spaceUType = GlobalConst.g_demoMaps.get(self.getClientDatas()[0], 1)

		props = {
			"name"				: name,
			"level"				: 1,
			"roleTmpl"			: roleTmpl
		}
		role = KBEngine.createBaseLocally('Role',props)
		if role:
			role.writeToDB(self._onRoleSaved)

	def reqRemoveRole(self,id):
		"""
		请求删除角色
		"""
		DEBUG_MSG("Account[%i].reqRemoveRole: %s" % (self.id, dbid))
		found = 0
		
		if dbid in self.characters:
			del self.characters[dbid]
			found = dbid

		self.client.onRemoveRoleResult(found)
	def reqSelectRole(self,id):
		"""
		选择一个角色进行游戏
		"""
		self.client.onReqRolesListResule(self.roles)

	"""
	私有函数
	"""
	def _onRoleSaved(self,success,role):
		if self.isDestroyed:
			if role:
				role.destroy(True)
			return

		roleinfo = TRoleInfos()
		roleinfo.extend([0,"",0,0])

		retCode = 0
		if success:
			"""
			??
			"""
			info = TRoleInfos()
			info.extend([role.databaseID,role.name,role.roleTmpl,1])
			self.roles[role.databaseID] = info
			roleinfo[0] = role.databaseID
			roleinfo[1] = role.name
			roleinfo[2] = role.roleTmpl
			roleinfo[3] = 1
			self.writeToDB()
		else:
			retCode = ErrCode.ROLE_CREATE_FAILED
		
		roleinfo.destroy()
		if self.client:
			self.client.onCreateRoleResult(retCode,roleinfo)



