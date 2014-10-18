/*
<--------------------------------------------------------------------------->
Created by Ghostcrawler336 @ AC-Web.org
Modified by DownBoard @ AC-Web.org
Date of modify: 2014-07-15
<--------------------------------------------------------------------------->
*/

#include "ScriptPCH.h"
#include "Chat.h"
#include "Common.h"

/* Colors */
#define MSG_COLOR_ORANGE "|cffFFA500"
#define MSG_COLOR_DARKORANGE "|cffFF8C00"
#define MSG_COLOR_RED "|cffFF0000"
#define MSG_COLOR_LIGHTRED "|cffD63931"
#define MSG_COLOR_ROYALBLUE "|cff4169E1"
#define MSG_COLOR_LIGHTBLUE "|cffADD8E6"
#define MSG_COLOR_YELLOW "|cffFFFF00"
#define MSG_COLOR_GREEN "|cff008000"
#define MSG_COLOR_PURPLE "|cffDA70D6"
#define MSG_COLOR_WHITE  "|cffffffff"
#define MSG_COLOR_SUBWHITE  "|cffbbbbbb"

/* Ranks */
#define OWNER "Owner"
#define COOWNER "Co-Owner"
#define HEADADMIN "HeadAdmin"
#define ADMIN "Admin"
#define DEVELOPER "Dev"
#define HEADGAMEMASTER "HeadGM"
#define GAMEMASTER "GM"
#define TRIALGM "TrialGM"
#define DONOR "Donor"
#define PLAYER "Player"


class World_Chat : public CommandScript
{
public:
	World_Chat() : CommandScript("World_Chat") { }

	static bool HandleWorldChatCommand(ChatHandler * pChat, const char * msg)
	{
		if (!*msg)
			return false;

		Player * player = pChat->GetSession()->GetPlayer();
		char message[1024];

		switch (player->GetSession()->GetSecurity())
		{
			case SEC_PLAYER:
				snprintf(message, 1024, "[Player][%s%s|r]: %s%s|r", MSG_COLOR_WHITE, player->GetName().c_str(), MSG_COLOR_WHITE, msg);
				sWorld->SendGlobalText(message, NULL);
				break;
				
			case SEC_DONOR:
				snprintf(message, 1024, "[Donor][%s%s|r]: %s%s|r", MSG_COLOR_ORANGE, player->GetName().c_str(), MSG_COLOR_ORANGE, msg);
				sWorld->SendGlobalText(message, NULL);
				break;
				
			case SEC_TRIALGM:
				snprintf(message, 1024, "[Trial-GM][%s%s|r]: %s%s|r", MSG_COLOR_LIGHTBLUE, player->GetName().c_str(), MSG_COLOR_LIGHTBLUE, msg);
				sWorld->SendGlobalText(message, NULL);
				break;

			case SEC_GAMEMASTER:
				snprintf(message, 1024, "[GM][%s%s|r]: %s%s|r", MSG_COLOR_ROYALBLUE, player->GetName().c_str(), MSG_COLOR_ROYALBLUE, msg);
				sWorld->SendGlobalText(message, NULL);
				break;

			case SEC_HEADGAMEMASTER:
				snprintf(message, 1024, "[Head-GM][%s%s|r]: %s%s|r", MSG_COLOR_DARKORANGE, player->GetName().c_str(), MSG_COLOR_DARKORANGE, msg);
				sWorld->SendGlobalText(message, NULL);
				break;

			case SEC_DEVELOPER:
				snprintf(message, 1024, "[Dev][%s%s|r]: %s%s|r", MSG_COLOR_PURPLE, player->GetName().c_str(), MSG_COLOR_PURPLE, msg);
				sWorld->SendGlobalText(message, NULL);
				break;

			case SEC_ADMIN:
				snprintf(message, 1024, "[Admin][%s%s|r]: %s%s|r", MSG_COLOR_GREEN, player->GetName().c_str(), MSG_COLOR_GREEN, msg);
				sWorld->SendGlobalText(message, NULL);
				break;

			case SEC_HEADADMIN:
				snprintf(message, 1024, "[Head-Admin][%s%s|r]: %s%s|r", MSG_COLOR_WHITE, player->GetName().c_str(), MSG_COLOR_WHITE, msg);
				sWorld->SendGlobalText(message, NULL);
				break;

			case SEC_COOWNER:
				snprintf(message, 1024, "[Co-Owner][%s%s|r]: %s%s|r", MSG_COLOR_LIGHTRED, player->GetName().c_str(), MSG_COLOR_LIGHTRED, msg);
				sWorld->SendGlobalText(message, NULL);
				break;

			case SEC_OWNER:
				snprintf(message, 1024, "[Owner][%s%s|r]: %s%s|r", MSG_COLOR_RED, player->GetName().c_str(), MSG_COLOR_RED, msg);
				sWorld->SendGlobalText(message, NULL);
				break;
		}
		return true;
	}

	ChatCommand * GetCommands() const
	{
		static ChatCommand HandleWorldChatCommandTable[] =
		{
			{ "world", rbac::RBAC_PERM_COMMAND_WORLD_CHAT, true, &HandleWorldChatCommand, "", NULL },
			{ NULL, 0, false, NULL, "", NULL }
		};
		return HandleWorldChatCommandTable;
	}
};

void AddSC_World_Chat()
{
	new World_Chat;
}