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
        static unsigned int lastStoredMinute = 0;
        static unsigned int numAssets = 0;
        static unsigned int totalMoney = 0;
        static bool playerCantReceive = true;

        myOnClockUpdate.after += [] {
            if (CGame::currArea != 0 || CTheScripts::IsPlayerOnAMission() || CWorld::Players[0].m_nPlayerState != PLAYERSTATE_PLAYING) {
                playerCantReceive = true;
            }
            else {
                playerCantReceive = false;
                totalMoney = 0;
                numAssets = 0;
            }

            if (!playerCantReceive) {
                for (unsigned int i = 0; i < MAX_NUM_PICKUPS; ++i) {
                    if (CPickups::aPickUps[i].m_nPickupType == PICKUP_ASSET_REVENUE) {
                        totalMoney += CPickups::aPickUps[i].m_nMoneyPerDay;
                        CPickups::aPickUps[i].m_fRevenueValue = 0.0f;
                        ++numAssets;
                    }
                }
            }
            if (CClock::ms_nGameClockHours < lastStoredHour && lastStoredHour >= 12 && (lastStoredMinute == CClock::ms_nGameClockMinutes || CClock::ms_nGameClockMinutes - lastStoredMinute == 1 || (lastStoredMinute == 59 && CClock::ms_nGameClockMinutes == 0 && (CClock::ms_nGameClockHours - lastStoredHour == 1 || lastStoredHour == 23 && CClock::ms_nGameClockHours == 0)))) {
                if (totalMoney > 0) {
                    CWorld::Players[0].m_nMoney += totalMoney;
                    static char text[256];
                    sprintf(text, "You have earned $%d from %d/10 assets.", totalMoney, numAssets);
                    CHud::SetHelpMessage(text, true, false, false);
                }
            }
            lastStoredHour = CClock::ms_nGameClockHours;
            lastStoredMinute = CClock::ms_nGameClockMinutes;
            };
    }
} plg;