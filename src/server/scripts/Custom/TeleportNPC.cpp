#include "ScriptMgr.h"

class npc_tp : public CreatureScript
{
public:

	npc_tp()
		: CreatureScript("npc_tp")
	{
	}

	bool OnGossipHello(Player* player, Creature* creature)
	{
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface/ICONS/Spell_Arcane_PortalShattrath:40:40:-18:0|t|c9933FFMall", GOSSIP_SENDER_MAIN, 1);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface/ICONS/Ability_DualWield:40:40:-18:0|t|c9933FFDuel Zone", GOSSIP_SENDER_MAIN, 2);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface/ICONS/Achievement_Arena_2v2_7:40:40:-18:0|t|c9933FFGurubashi arena", GOSSIP_SENDER_MAIN, 3);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface/ICONS/INV_Misc_Book_03:40:40:-18:0|t|c9933FFProfession Mall", GOSSIP_SENDER_MAIN, 4);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface/ICONS/Achievement_Dungeon_UlduarRaid_Misc_04:40:40:-18:0|t|c9933FFTransmog", GOSSIP_SENDER_MAIN, 5);

		player->PlayerTalkClass->SendGossipMenu(100000, creature->GetGUID());

		return true;
	}

	bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
	{
		player->PlayerTalkClass->ClearMenus();
		if (sender == GOSSIP_SENDER_MAIN)
		{
			switch (action)
			{
			case 1:
				player->TeleportTo(571, 3450.71f, -3624.24f, 248.446f, 5.42249f);
				player->CLOSE_GOSSIP_MENU();
				break;

			case 2:
				player->TeleportTo(0, -1849.86f, -4240.86f, 2.13502f, 0.491186f);
				player->CLOSE_GOSSIP_MENU();
				break;

			case 3:
				player->TeleportTo(0, -13262.6f, 161.518f, 36.4557f, 1.09443f);
				player->CLOSE_GOSSIP_MENU();
				break;

			case 4:
				player->TeleportTo(1, -1564.09f, -1144.92f, 211.576f, 4.82686f);
				player->CLOSE_GOSSIP_MENU();
				break;

			case 5:
				player->TeleportTo(530, -2247.58f, 5558.52f, 67.0236f, 2.83521f);
				player->CLOSE_GOSSIP_MENU();
				break;

			}
		}
	}
};

void AddSC_npc_tp()
{
	new npc_tp();
}