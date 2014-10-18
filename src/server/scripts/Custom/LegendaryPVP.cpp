// Made By ToxicDev
class LegOnPvPKill : public PlayerScript
{
public:
	LegOnPvPKill() : PlayerScript("LegOnPvPKill") {}

	// Change This To Your Token ID
	uint32 itemid = 1;

	void OnPVPKill(Player* killer, Player* /*killed*/)
	{
		switch (urand(1, 100))
		{
		case 33:
			killer->AddItem(itemid, 800255);
			break;
		}
	}
};

void AddSC_LegOnPvPKill()
{
	new LegOnPvPKill();
}