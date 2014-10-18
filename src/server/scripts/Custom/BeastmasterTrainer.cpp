/*
<--------------------------------------------------------------------------->
 - Developer: Kolin 'Valtorei'
 - Complete: 100%
 - ScriptName: 'Beastmaster'
 - Developed: 07/15/2014
 - Update: 09/27/2014
 <--------------------------------------------------------------------------->
 */

#include "Pet.h"

//Pet food
#define MEAT 35953
#define FISH 35951
#define CHEESE 35952
#define FRUIT 35948
#define FUNGI 35947
#define BREAD 35950

enum Pet_Food
{
	p_MEAT = 35953,
	p_FISH = 35951,
	p_CHEESE = 35952,
	p_FRUIT = 35948,
	p_FUNGI = 35947,
	p_BREAD = 35950
};

class Beastmaster_Trainer : public CreatureScript
{
public:
    Beastmaster_Trainer() : CreatureScript("Beastmaster_Trainer") {}

    void CreatePet(Player* player, Creature* creature, uint32 entry)
    {	
        Creature* creatureTarget = creature->SummonCreature(entry, player->GetPositionX(), player->GetPositionY() +2, player->GetPositionZ(), player->GetOrientation(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 500);
        if(!creatureTarget)
            return;

        Pet* pet = player->CreateTamedPetFrom(creatureTarget, 0);
        if(!pet)
            return;

        creatureTarget->setDeathState(JUST_DIED);
        creatureTarget->RemoveCorpse();
        creatureTarget->SetHealth(0);

        pet->SetPower(POWER_HAPPINESS, 10480000);

        pet->SetUInt64Value(UNIT_FIELD_CREATEDBY, player->GetGUID());
        pet->SetUInt64Value(UNIT_FIELD_FACTIONTEMPLATE, player->getFaction());
        pet->SetUInt64Value(UNIT_FIELD_LEVEL, player->getLevel());

        pet->GetMap()->AddToMap(pet->ToCreature());

        pet->GetCharmInfo()->SetPetNumber(sObjectMgr->GeneratePetNumber(), true);
        if(!pet->InitStatsForLevel(player->getLevel()))
            TC_LOG_INFO("misc", "Failure: No Init Stats for entry %u", entry);

        pet->UpdateAllStats();
        player->SetMinion(pet, true);

        pet->SavePetToDB(PET_SAVE_AS_CURRENT);
		pet->InitTalentForLevel();
		player->PetSpellInitialize();
				
		player->CLOSE_GOSSIP_MENU();
		creature->MonsterWhisper("You have learned a way of the beast, congratulations.",  /*LANG_UNIVERSAL,*/ player);
	}
			
	bool OnGossipHello(Player* player, Creature* creature)
	{
		if(player->getClass() != CLASS_HUNTER)
		{
			creature->MonsterWhisper("I can only train Hunters in the way of the beast.",  /*LANG_UNIVERSAL,*/ player);
			player->CLOSE_GOSSIP_MENU();
			return false;
		}
		
		if (player->GetPet())
		{
			creature->MonsterWhisper("You must leave your current pet in order to gain a new one.", /*LANG_UNIVERSAL,*/ player);
			player->CLOSE_GOSSIP_MENU();
			return false;
		}

		player->ADD_GOSSIP_ITEM(1, "Obtain a New Pet", GOSSIP_SENDER_MAIN, 1);
		/*if (player->CanTameExoticPets())
			player->ADD_GOSSIP_ITEM(2, "Obtain a New Exotic Pet", GOSSIP_SENDER_MAIN, 3);*/
		player->ADD_GOSSIP_ITEM(3, "Stable your Pet", GOSSIP_SENDER_MAIN, GOSSIP_OPTION_STABLEPET), 4;
		player->ADD_GOSSIP_ITEM(4, "Buy food for your Pet", GOSSIP_SENDER_MAIN, 5);
		player->ADD_GOSSIP_ITEM(5, "Nevermind!", GOSSIP_SENDER_MAIN, 150);
				
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			return true;
	}
			
	bool OnGossipSelect(Player* player, Creature* creature, uint32 /* sender */, uint32 action)
	{
		player->PlayerTalkClass->ClearMenus();
					
		switch (action)
		{
			//Main Menu
			case 100:
				OnGossipHello(player, creature);
				break;
				
			//Nevermind
			case 150:
				player->CLOSE_GOSSIP_MENU();
				break;

			//Pet Stable					
			case GOSSIP_OPTION_STABLEPET:
				player->GetSession()->SendStablePet(creature->GetGUID());
				break;
				
			//Pet Menu					
			case 1:
				player->ADD_GOSSIP_ITEM(6, "Bat", GOSSIP_SENDER_MAIN, 11);
				player->ADD_GOSSIP_ITEM(6, "Bear", GOSSIP_SENDER_MAIN, 12);
				player->ADD_GOSSIP_ITEM(6, "Carrion Bird", GOSSIP_SENDER_MAIN, 13);
				player->ADD_GOSSIP_ITEM(6, "Cat", GOSSIP_SENDER_MAIN, 44);
				player->ADD_GOSSIP_ITEM(6, "Crab", GOSSIP_SENDER_MAIN, 15);
				player->ADD_GOSSIP_ITEM(6, "Crocolisk", GOSSIP_SENDER_MAIN, 16);
				player->ADD_GOSSIP_ITEM(6, "Dragonhawk", GOSSIP_SENDER_MAIN, 17);
				player->ADD_GOSSIP_ITEM(6, "Gorilla", GOSSIP_SENDER_MAIN, 18);
				player->ADD_GOSSIP_ITEM(6, "Hyena", GOSSIP_SENDER_MAIN, 19);
				player->ADD_GOSSIP_ITEM(6, "Eagle", GOSSIP_SENDER_MAIN, 20);
				player->ADD_GOSSIP_ITEM(6, "Moth", GOSSIP_SENDER_MAIN, 21);
				player->ADD_GOSSIP_ITEM(4, "Next Page ->", GOSSIP_SENDER_MAIN, 2);
				player->ADD_GOSSIP_ITEM(4, "<- Main Menu", GOSSIP_SENDER_MAIN, 100);
				player->ADD_GOSSIP_ITEM(5, "Nevermind!", GOSSIP_SENDER_MAIN, 150);
					player->SEND_GOSSIP_MENU(1, creature->GetGUID());
				break;

			//Pet Menu 2					
			case 2:
				player->ADD_GOSSIP_ITEM(6, "Raptor", GOSSIP_SENDER_MAIN, 22);
				player->ADD_GOSSIP_ITEM(6, "Ravager", GOSSIP_SENDER_MAIN, 23);
				player->ADD_GOSSIP_ITEM(6, "Scorpid", GOSSIP_SENDER_MAIN, 24);
				player->ADD_GOSSIP_ITEM(6, "Serpent", GOSSIP_SENDER_MAIN, 25);
				player->ADD_GOSSIP_ITEM(6, "Strider", GOSSIP_SENDER_MAIN, 26);
				player->ADD_GOSSIP_ITEM(6, "Spider", GOSSIP_SENDER_MAIN, 27);
				player->ADD_GOSSIP_ITEM(6, "Spore Bat", GOSSIP_SENDER_MAIN, 28);
				player->ADD_GOSSIP_ITEM(6, "Turtle", GOSSIP_SENDER_MAIN, 29);
				player->ADD_GOSSIP_ITEM(6, "Warp Stalker", GOSSIP_SENDER_MAIN, 30);
				player->ADD_GOSSIP_ITEM(6, "Wasp", GOSSIP_SENDER_MAIN, 31);
				player->ADD_GOSSIP_ITEM(6, "Worg", GOSSIP_SENDER_MAIN, 32);
				player->ADD_GOSSIP_ITEM(4, "<- Previous Page", GOSSIP_SENDER_MAIN, 1);
				player->ADD_GOSSIP_ITEM(4, "<- Main Menu", GOSSIP_SENDER_MAIN, 100);
				player->ADD_GOSSIP_ITEM(5, "Nevermind!", GOSSIP_SENDER_MAIN, 150);
					player->SEND_GOSSIP_MENU(1, creature->GetGUID());
				break;

			//Exoctic Pet Menu					
			case 3:
				player->ADD_GOSSIP_ITEM(6, "Arcturis", GOSSIP_SENDER_MAIN, 33);
				player->ADD_GOSSIP_ITEM(6, "Basilisk", GOSSIP_SENDER_MAIN, 34);
				player->ADD_GOSSIP_ITEM(6, "Chimaera", GOSSIP_SENDER_MAIN, 35);
				player->ADD_GOSSIP_ITEM(6, "Core Hound", GOSSIP_SENDER_MAIN, 36);
				player->ADD_GOSSIP_ITEM(6, "Devilsaur", GOSSIP_SENDER_MAIN, 37);
				player->ADD_GOSSIP_ITEM(6, "Gondri.", GOSSIP_SENDER_MAIN, 38);
				player->ADD_GOSSIP_ITEM(6, "Loque'nahak", GOSSIP_SENDER_MAIN, 39);
				player->ADD_GOSSIP_ITEM(6, "Rhino", GOSSIP_SENDER_MAIN, 40);
				player->ADD_GOSSIP_ITEM(6, "Skoll", GOSSIP_SENDER_MAIN, 41);
				player->ADD_GOSSIP_ITEM(6, "Silithid", GOSSIP_SENDER_MAIN, 42);
				player->ADD_GOSSIP_ITEM(6, "Worm", GOSSIP_SENDER_MAIN, 43);
				player->ADD_GOSSIP_ITEM(4, "<- Main Menu", GOSSIP_SENDER_MAIN, 100);
				player->ADD_GOSSIP_ITEM(5, "Nevermind!", GOSSIP_SENDER_MAIN, 150);
					player->SEND_GOSSIP_MENU(1, creature->GetGUID());
				break;

			//Pet IDs
			case 11: //Bat
				CreatePet(player, creature, 23959);
				break;

			case 12: //Bear
				CreatePet(player, creature, 29562);
				break;

			case 13: //Carrion Bird
				CreatePet(player, creature, 16972);
				break;

			case 44: //Cat
				CreatePet(player, creature, 28085);
				break;

			case 15: //Crab
				CreatePet(player, creature, 3106);
				break;

			case 16: //Crocolisk
				CreatePet(player, creature, 24138);
				break;

			case 17: //Dragonhawk
				CreatePet(player, creature, 27946);
				break;

			case 18: //Gorilla
				CreatePet(player, creature, 28096);
				break;

			case 19: //Hyena
				CreatePet(player, creature, 27294);
				break;

			case 20: //Eagle
				CreatePet(player, creature, 26369);
				break;

			case 21: //Moth
				CreatePet(player, creature, 18468);
				break;

			case 22: //Raptor
				CreatePet(player, creature, 14821);
				break;

			case 23: //Ravager
				CreatePet(player, creature, 23326);
				break;

			case 24: //Scorpid
				CreatePet(player, creature, 9698);
				break;

			case 25: //Serpent
				CreatePet(player, creature, 28358);
				break;

			case 26: //Strider
				CreatePet(player, creature, 22807);
				break;

			case 27: //Spider
				CreatePet(player, creature, 23958);
				break;

			case 28: //Sporebat
				CreatePet(player, creature, 18128);
				break;

			case 29: //Turtle
				CreatePet(player, creature, 25482);
				break;

			case 30: //Warpchaser
				CreatePet(player, creature, 18884);
				break;

			case 31: //Wasp
				CreatePet(player, creature, 28086);
				break;

			case 32: //Worg
				CreatePet(player, creature, 20330);
				break;

			//Exotic IDs	
			case 33: //Arcturis
				CreatePet(player, creature, 38453);
				break;

			case 34: //Basilisk
				CreatePet(player, creature, 28203);
				break;

			case 35: //Chimaera
				CreatePet(player, creature, 21879);
				break;

			case 36: //Core Hound
				CreatePet(player, creature, 21108);
				break;

			case 37: //Devilsaur
				CreatePet(player, creature, 20931);
				break;

			case 38: //Gondri
				CreatePet(player, creature, 33776);
				break;

			case 39: //Loque'nahak
				CreatePet(player, creature, 32517);
				break;

			case 40: //Rhino
				CreatePet(player, creature, 30445);
				break;

			case 41: //Skoll
				CreatePet(player, creature, 35189);
				break;

			case 42: //Silithid
				CreatePet(player, creature, 5460);
				break;

			case 43: //Worm
				CreatePet(player, creature, 30148);
				break;

			case 5: //Pet Food Menu
				player->PlayerTalkClass->ClearMenus();

				player->ADD_GOSSIP_ITEM(1, "Meat", GOSSIP_SENDER_MAIN, 51);
				player->ADD_GOSSIP_ITEM(2, "Fish", GOSSIP_SENDER_MAIN, 52);
				player->ADD_GOSSIP_ITEM(3, "Cheese", GOSSIP_SENDER_MAIN, 53);
				player->ADD_GOSSIP_ITEM(4, "Fruit", GOSSIP_SENDER_MAIN, 54);
				player->ADD_GOSSIP_ITEM(5, "Fungi", GOSSIP_SENDER_MAIN, 55);
				player->ADD_GOSSIP_ITEM(6, "Bread", GOSSIP_SENDER_MAIN, 56);
				player->ADD_GOSSIP_ITEM(4, "<- Main Menu", GOSSIP_SENDER_MAIN, 100);
				player->ADD_GOSSIP_ITEM(7, "Nevermind!", GOSSIP_SENDER_MAIN, 150);
					player->SEND_GOSSIP_MENU(1, creature->GetGUID());
				//return true;
				break;

				//Pet Food
			case 51:
				player->AddItem(p_MEAT, 20);
				break;

			case 52:
				player->AddItem(p_FISH, 20);
				break;

			case 53:
				player->AddItem(p_CHEESE, 20);
				break;

			case 54:
				player->AddItem(p_FRUIT, 20);
				break;

			case 55:
				player->AddItem(p_FUNGI, 20);
				break;

			case 56:
				player->AddItem(p_BREAD, 20);
				break;
		}
					
	return true;
	}
};

void AddSC_Beastmaster_Trainer()
{
	new Beastmaster_Trainer;
}