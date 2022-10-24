# Live audio for DJI Goggles V1 and V2

New version compatible with V1 and V2 goggles. Normal Airunit with an integrated microphone required. Will not work with Caddx Vista.

Packages with the matching name must be installed on both airunit and goggles.

Audio volume can be set:
- by playing back a video that doesn't contain any audio and set the volume from there.
- with CLI command `setprop persist.dji.volume.headphone 6` with persistent values from 1-6.
- with CLI command `tinymix 2 48 48`. Values up to 63. 


## Manual installation

Install:
- `download package-name.ipk`
- `adb push /tmp/package-name.ipk`
- `opkg install /tmp/package-name.ipk`

Alternative method:  https://github.com/fpv-wtf/wtfos/wiki/Installing-third-party-packages

Make ipk:
- `make ipk`
