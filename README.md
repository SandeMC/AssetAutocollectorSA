# AssetAutocollectorSA
![image](https://github.com/SandeMC/AssetAutocollectorSA/assets/70141395/30e70080-a344-4e1e-91dc-0516c89e0925)

Automatically collects your revenue from every owned asset every time the clock resets after 12:00 (saving takes 6 hours, dying/getting arrested takes 12). Works even in interiors, but you need to touch grass at least once per session for it to work. It also disables the ability to grab money yourself - though the pickup itself will be there. 

Made with [plugin-sdk](https://github.com/DK22Pac/plugin-sdk), based on the [original script by DK22Pac](https://gtaforums.com/topic/882892-asset-autocollector/?do=findComment&comment=1069437800). 

Changes from the original script:
- Account for time skips (dying, arrested, saving - though it's prone to cheating if you switch from a savefile that is at 12:00 or later to a savefile that's at 11:00 or earlier).
- Adjust the pickup check to make sure it only triggers when outside of an interior and not on a mission, allowing it to count even when inside an interior.
