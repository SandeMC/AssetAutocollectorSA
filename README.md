# AssetAutocollectorSA
![image](https://github.com/SandeMC/AssetAutocollectorSA/assets/70141395/54f4845b-ac47-4372-bfcc-c4d0551466ea)

Automatically collects your revenue from every owned asset every time the clock resets or if you die/get arrested when the clock is at 12:00 or later. Works even in interiors, but you need to touch grass (go outside) at least once per session for it to work.

Made with [plugin-sdk](https://github.com/DK22Pac/plugin-sdk), based on the [original script by DK22Pac](https://gtaforums.com/topic/882892-asset-autocollector/?do=findComment&comment=1069437800). 

Changes from the original script:
- Account for dying and being arrested
- Adjust the pickup check to make sure it only triggers when outside of an interior and not on a mission, allowing it to count even when inside an interior.
- Reset the values after collection happened (only if the values can be set again)
