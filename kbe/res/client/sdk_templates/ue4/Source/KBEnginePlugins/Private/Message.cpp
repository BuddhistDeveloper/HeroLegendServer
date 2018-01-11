
#include "Message.h"
#include "KBDebug.h"

Message::Message() :
	id(0),
	name(TEXT("")),
	msglen(-1)
{
}

Message::Message(MessageID mid, const FString& mname, int16 mmsglen):
	id(mid),
	name(mname),
	msglen(mmsglen)
{
}

Message::~Message()
{
}

FString Message::c_str()
{
	return FString::Printf(TEXT("%s id:%u, len : %d"), *name, id, msglen);
}

void Message::handle(MemoryStream& s) 
{
	SCREEN_ERROR_MSG("Message::handle(): interface(%s), handleMethod no implement!",
		*c_str());
}

Messages::Messages() :
	loginappMessages(),
	baseappMessages(),
	clientMessages(),
	messages(),
	fixedMessageID()
{
	bindFixedMessage();
}

Messages::~Messages()
{
}

Messages& Messages::getSingleton()
{
	return g_Messages;
}

void Messages::clear()
{
	/* �˴�������������KBEngine��destroy֮���޷����һ���Ϣ
		for (auto& Elem : messages)
			delete Elem.Value;

		messages.Empty();

		loginappMessages.Empty();
		baseappMessages.Empty();
		clientMessages.Empty();

		bindFixedMessage();
	*/

	return;
}

void Messages::bindFixedMessage()
{
	if (messages.Num() > 0)
		return;

	// ������Ҫ֪�����������ֵ����Э������ID���������̴ӷ���˵���Э����Ϳ���֪������Э����
	// ����Э��˵���μ�: http://www.kbengine.org/cn/docs/programming/clientsdkprogramming.html
	messages.Add(TEXT("Loginapp_importClientMessages"), new Message(5, TEXT("importClientMessages"), 0));
	messages.Add(TEXT("Loginapp_hello"), new Message(4, TEXT("hello"), -1));

	messages.Add(TEXT("Baseapp_importClientMessages"), new Message(207, TEXT("importClientMessages"), 0));
	messages.Add(TEXT("Baseapp_importClientEntityDef"), new Message(208, TEXT("importClientMessages"), 0));
	messages.Add(TEXT("Baseapp_hello"), new Message(200, TEXT("hello"), -1));

	fixedMessageID.Add(TEXT("Client_onHelloCB"), 521);
	fixedMessageID.Add(TEXT("Client_onScriptVersionNotMatch"), 522);
	fixedMessageID.Add(TEXT("Client_onVersionNotMatch"), 523);
	fixedMessageID.Add(TEXT("Client_onImportClientMessages"), 518);
}

Message* Messages::add(Message* pMessage, MessageID mid, const FString& mname, int16 mmsglen)
{
	if (findClientMessage(mid))
		return pMessage;

	if (fixedMessageID.Contains(mname))
	{
		mid = fixedMessageID.FindRef(mname);
	}

	pMessage->id = mid;
	pMessage->name = mname;
	pMessage->msglen = mmsglen;

	static int tmpID = 0;

	// ����ID�ظ�
	if (mid == 0)
	{
		--tmpID;
		clientMessages.Add(tmpID, pMessage);
	}
	else
	{
		clientMessages.Add(pMessage->id, pMessage);
	}

	messages.Add(pMessage->name, pMessage);
	
	INFO_MSG("Message::add(): %s", *pMessage->c_str());
	return pMessage;
}

Message* Messages::findClientMessage(MessageID mid)
{
	return clientMessages.FindRef(mid);
}

Message* Messages::findMessage(const FString& mname)
{
	return messages.FindRef(mname);
}

