/*
This source file is part of KBEngine
For the latest info, see http://www.kbengine.org/

Copyright (c) 2008-2017 KBEngine.

KBEngine is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

KBEngine is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.
 
You should have received a copy of the GNU Lesser General Public License
along with KBEngine.  If not, see <http://www.gnu.org/licenses/>.
*/


#if defined(DEFINE_IN_INTERFACE)
	#undef KBE_KBCMD_TOOL_INTERFACE_H
#endif


#ifndef KBE_KBCMD_TOOL_INTERFACE_H
#define KBE_KBCMD_TOOL_INTERFACE_H

// common include	
#if defined(INTERFACES)
#include "kbcmd.h"
#endif
#include "kbcmd_interface_macros.h"
#include "network/interface_defs.h"
//#define NDEBUG
// windows include	
#if KBE_PLATFORM == PLATFORM_WIN32
#else
// linux include
#endif
	
namespace KBEngine{

/**
	KBCMD��Ϣ�꣬  ����Ϊ���� ��Ҫ�Լ��⿪
*/

/**
	KBCMD������Ϣ�ӿ��ڴ˶���
*/
NETWORK_INTERFACE_DECLARE_BEGIN(KBCMDInterface)

	// ĳapp��������look��
	KBCMD_MESSAGE_DECLARE_ARGS0(lookApp, NETWORK_FIXED_MESSAGE)

	// ĳ��app��app��֪���ڻ״̬��
	KBCMD_MESSAGE_DECLARE_ARGS2(onAppActiveTick, NETWORK_FIXED_MESSAGE,
		COMPONENT_TYPE, componentType,
		COMPONENT_ID, componentID)

NETWORK_INTERFACE_DECLARE_END()

#ifdef DEFINE_IN_INTERFACE
	#undef DEFINE_IN_INTERFACE
#endif

}

#endif // KBE_KBCMD_TOOL_INTERFACE_H
