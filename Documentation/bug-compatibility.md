# Bug-compatibility in Xash3D FWGS

Xash3D FWGS has special mode for games that rely on original engine bugs.

In this mode, we only emulate behaviour of selected functions that may lead to game logic bugs, crashes, etc, but at same time enabling them will break other games, that specifically made for Xash or other game engines. By default, we honor games that either have fixes these issues OR doesn't encounter them.

At this time, we only support GoldSrc bug-compatibility. It can be enabled with `-bugcomp` command line switch.

## GoldSrc bug-compatibility

### Emulated bugs

* pfnPEntityOfEntIndex in GoldSrc will return NULL for last player due to incorrect player index comparison

### Games and mods that require this

* Counter-Strike: Condition Zero - Deleted Scenes
