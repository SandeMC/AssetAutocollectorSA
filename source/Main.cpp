#include "plugin.h"
#include "game_sa\CClock.h"
#include "game_sa\CPickups.h"
#include "game_sa\CWorld.h"
#include "game_sa\CHud.h"
#include "game_sa\CGame.h"
#include "game_sa\CTheScripts.h"

using namespace plugin;

class AssetAutocollector {
public:
    AssetAutocollector() {
        static CdeclEvent<AddressList<0x53BFBD, H_CALL>, PRIORITY_AFTER, ArgPickNone, void()> myOnClockUpdate;
        static unsigned int lastStoredHour = 0;
        static unsigned int numAssets = 0;
        static unsigned int totalMoney = 0;
        static bool playerCantReceive = true;
        static bool ranPickupCheck = false;
        static bool hasPlayerDied = false;

        myOnClockUpdate.before += [] {
            lastStoredHour = CClock::ms_nGameClockHours;
        };
        myOnClockUpdate.after += [] {
            if (CGame::currArea != 0 || CTheScripts::IsPlayerOnAMission() || CWorld::Players[0].m_nPlayerState != PLAYERSTATE_PLAYING) {
                playerCantReceive = true;
            }
            else {
                playerCantReceive = false;
                totalMoney = 0;
                numAssets = 0;
                ranPickupCheck = false;
                hasPlayerDied = false;
            }
            if (!playerCantReceive && !ranPickupCheck) {
                for (unsigned int i = 0; i < MAX_NUM_PICKUPS; ++i) {
                    if (CPickups::aPickUps[i].m_nPickupType == PICKUP_ASSET_REVENUE) {
                        totalMoney += CPickups::aPickUps[i].m_nMoneyPerDay;
                        CPickups::aPickUps[i].m_fRevenueValue = 0.0f;
                        ++numAssets;
                        ranPickupCheck = true;
                    }
                }
            }
            if (CClock::ms_nGameClockHours < lastStoredHour) {
                if (totalMoney > 0) {
                    CWorld::Players[0].m_nMoney += totalMoney;
                    static char text[256];
                    sprintf(text, "You have earned $%d from %d assets", totalMoney, numAssets);
                    CHud::SetHelpMessage(text, true, false, false);
                    if (!playerCantReceive) {
                        totalMoney = 0;
                        numAssets = 0;
                        ranPickupCheck = false;
                    }
                }
            }
            if (CWorld::Players[0].m_nPlayerState == PLAYERSTATE_HASDIED && lastStoredHour >= 12 && !hasPlayerDied || CWorld::Players[0].m_nPlayerState == PLAYERSTATE_HASBEENARRESTED && lastStoredHour >= 12 && !hasPlayerDied) {
                if (totalMoney > 0) {
                    CWorld::Players[0].m_nMoney += totalMoney;
                    static char text[256];
                    sprintf(text, "You have earned $%d from %d assets", totalMoney, numAssets);
                    CHud::SetHelpMessage(text, true, false, false);
                    if (!playerCantReceive) {
                        totalMoney = 0;
                        numAssets = 0;
                        ranPickupCheck = false;
                    }
                }
                hasPlayerDied = true;
            }
            lastStoredHour = CClock::ms_nGameClockHours;
            };
    }
} plg;