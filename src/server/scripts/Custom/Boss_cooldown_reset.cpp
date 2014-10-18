/*
Script : Player Cooldown Reset On Boss & World Boss Kill
Author : Callmephil
Patch : 3.3.5 - 4.3.4
Version : 1.5
Special thx to  Core Surgeon (Ac-Web) for group check.
*/
#include "Group.h"

enum SPELL_DEBUFF
{
	// WOTLK
	DEBUFF_SATED = 57724,
	DEBUFF_EXHAUSTION = 57723,
	// CATA
	DEBUFF_TEMPORAL_DISPLACEMENT = 80354,
	DEBUFF_INSANITY = 95809,
};

void remove_debuff_and_cooldown(Player* player)
{
	uint32 remove_debuff_spell[4] =
	{
		DEBUFF_SATED, DEBUFF_EXHAUSTION, DEBUFF_TEMPORAL_DISPLACEMENT, DEBUFF_INSANITY
	};

	for (uint32 i = 0; i < sizeof(remove_debuff_spell) / sizeof(uint32); i++)
		if (player->HasAura(remove_debuff_spell[i]))
			player->RemoveAura(remove_debuff_spell[i]);

	player->RemoveAllSpellCooldown();
}

void PlayerIsInGroup(Player* player)
{
	Group * group = player->GetGroup();

	Group::MemberSlotList const &members = group->GetMemberSlots();
	for (Group::MemberSlotList::const_iterator itr = members.begin(); itr != members.end(); ++itr)
	{
		Group::MemberSlot const &slot = *itr;
		Player* player = ObjectAccessor::FindPlayer((*itr).guid);
		if (player && player->GetSession())
			remove_debuff_and_cooldown(player);
	}
}

bool IsInDungeonOrRaid(Player* player)
{
	if (sMapStore.LookupEntry(player->GetMapId())->Instanceable())
		return true; // boolean need to return to a value
	return false;
}

class Cooldown_Reset : public PlayerScript
{
public:
	Cooldown_Reset() : PlayerScript("Cooldown_Reset") {}

	void OnCreatureKill(Player* player, Creature* boss)
	{
		if ((IsInDungeonOrRaid(player)) && (boss->isWorldBoss() || boss->IsDungeonBoss()))
		{
			if (player->GetGroup())
				PlayerIsInGroup(player);
			else
				remove_debuff_and_cooldown(player);
		}
	}
};

void AddSC_Cooldown_Reset()
{
	new Cooldown_Reset();
}