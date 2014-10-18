const int32 KillerStreak1 = 3;
const int32 KillerStreak2 = 8;
const int32 KillerStreak3 = 15;
const int32 KillerStreak4 = 25;
const int32 KillerStreak5 = 40;
const int32 KillerStreak6 = 60;
const int32 KillerStreak7 = 90;
const int32 KillerStreak8 = 130;
const int32 KillerStreak9 = 170;
const int32 KillerStreak10 = 200;


struct SystemInfo
{
	uint64 KillStreak;
	uint64 LastGUIDKill;
};

static std::map<uint32, SystemInfo> KillingStreak;

class System_OnPVPKill : public PlayerScript
{
public:
	System_OnPVPKill() : PlayerScript("System_OnPVPKill") {}

	void OnPVPKill(Player *pKiller, Player *pVictim)
	{
		uint32 kGUID;
		uint32 vGUID;
		kGUID = pKiller->GetGUID();
		vGUID = pVictim->GetGUID();
		if (kGUID == vGUID)
		{
			return;
		}
		if (KillingStreak[kGUID].LastGUIDKill == vGUID)
		{
			return;
		}

		KillingStreak[kGUID].KillStreak++;
		KillingStreak[vGUID].KillStreak = 0;
		KillingStreak[kGUID].LastGUIDKill = vGUID;
		KillingStreak[vGUID].LastGUIDKill = 0;

		switch (KillingStreak[kGUID].KillStreak)
		{
			char msg[500];
			
		 case KillerStreak1: //if the killer gets 3 kill
			 sprintf(msg, "|cffFF0000[KillStreak System]|r: |cffFF0000%s|r killed |cffFF0000%s|cffFFFF05 and is on a kill streak of|cffFF0000 3|r! ", pKiller->GetName().c_str(), pVictim->GetName().c_str());
			 sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
			 pKiller->CastSpell(pKiller, 24378, true);
			 break;

		case KillerStreak2: //if the killer gets 8 kills
			sprintf(msg, "|cffFF0000[KillStreak System]|r: |cffFF0000%s|r killed |cffFF0000%s|cffFFFF05 and is on a nice kill streak of|cffFF0000 8|r! ", pKiller->GetName().c_str(), pVictim->GetName().c_str());
			sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
			pKiller->CastSpell(pKiller, 72521, true);
			break;

		case KillerStreak3: //if the killer gets 15 kills
			sprintf(msg, "|cffFF0000[KillStreak System]|r: |cffFF0000%s|r killed |cffFF0000%s|cffFFFF05 and is on an awesome kill streak of|cffFF0000 15|r! ", pKiller->GetName().c_str(), pVictim->GetName().c_str());
			sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
			pKiller->CastSpell(pKiller, 46423, true);
			break;

		case KillerStreak4: //if the killer gets 25 kills
			sprintf(msg, "|cffFF0000[KillStreak System]|r: |cffFF0000%s|r killed |cffFF0000%s|cffFFFF05 and is on a CRAZY kill streak of|cffFF0000 25|r! ", pKiller->GetName().c_str(), pVictim->GetName().c_str());
			sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
			pKiller->CastSpell(pKiller, 72301, true);
			pKiller->CastSpell(pKiller, 72302, true);
			pKiller->CastSpell(pKiller, 72303, true);
			pKiller->CastSpell(pKiller, 72304, true);
			break;

		case KillerStreak5: //if the killer gets 40 kills
			sprintf(msg, "|cffFF0000[KillStreak System]|r: |cffFF0000%s|r killed |cffFF0000%s|cffFFFF05 and is on a LEGENDARY kill streak of|cffFF0000 40|r! ", pKiller->GetName().c_str(), pVictim->GetName().c_str());
			sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
			pKiller->CastSpell(pKiller, 72523, true);
			break;

		case KillerStreak6: //if the killer gets 60 kills
			sprintf(msg, "|cffFF0000[KillStreak System]|r: |cffFF0000%s|r killed |cffFF0000%s|cffFFFF05 and is on a MAGNIFICENT kill streak of|cffFF0000 60|r! ", pKiller->GetName().c_str(), pVictim->GetName().c_str());
			sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
			pKiller->AddItem(189912, 1);
			break;

		case KillerStreak7: //if the killer gets 90 kills
			sprintf(msg, "|cffFF0000[KillStreak System]|r: |cffFF0000%s|r killed |cffFF0000%s|cffFFFF05 and is on a SUPERIOR kill streak of|cffFF0000 90|r! ", pKiller->GetName().c_str(), pVictim->GetName().c_str());
			sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
			pKiller->AddItem(189912, 3);
			break;

		case KillerStreak8: //if the killer gets 130 kills
			sprintf(msg, "|cffFF0000[KillStreak System]|r: |cffFF0000%s|r killed |cffFF0000%s|cffFFFF05 and is on an AMAZING kill streak of|cffFF0000 130|r! ", pKiller->GetName().c_str(), pVictim->GetName().c_str());
			sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
			pKiller->AddItem(189912, 8);
			break;

		case KillerStreak9: //if the killer gets 170 kills
			sprintf(msg, "|cffFF0000[KillStreak System]|r: |cffFF0000%s|r killed |cffFF0000%s|cffFFFF05 and is on a SUPER kill streak of|cffFF0000 170|r! ", pKiller->GetName().c_str(), pVictim->GetName().c_str());
			sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
			pKiller->AddItem(189912, 15);
			break;

		case KillerStreak10: //if the killer gets 200 kills
			sprintf(msg, "|cffFF0000[KillStreak System]|r: |cffFF0000%s|r killed |cffFF0000%s|cffFFFF05 and is on an INSANE kill streak of|cffFF0000 200|r! ", pKiller->GetName().c_str(), pVictim->GetName().c_str());
			sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
			pKiller->AddItem(222111, 1);
			break;
			
		}
	}
};

void AddSC_System()
{
	new System_OnPVPKill;
}