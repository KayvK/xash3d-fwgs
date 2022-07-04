#pragma once
#ifndef FSINFO_H
#define FSINFO_H

#include "xash3d_types.h"
#include "const.h"
#include "com_model.h"

typedef struct gameinfo_s
{
	// filesystem info
	char		gamefolder[MAX_QPATH];	// used for change game '-game x'
	char		basedir[MAX_QPATH];	// base game directory (like 'id1' for Quake or 'valve' for Half-Life)
	char		falldir[MAX_QPATH];	// used as second basedir
	char		startmap[MAX_QPATH];// map to start singleplayer game
	char		trainmap[MAX_QPATH];// map to start hazard course (if specified)
	char		title[64];	// Game Main Title
	float		version;		// game version (optional)

	// .dll pathes
	char		dll_path[MAX_QPATH];	// e.g. "bin" or "cl_dlls"
	char		game_dll[MAX_QPATH];	// custom path for game.dll

	// .ico path
	char		iconpath[MAX_QPATH];	// "game.ico" by default

	// about mod info
	string		game_url;		// link to a developer's site
	string		update_url;	// link to updates page
	char		type[MAX_QPATH];	// single, toolkit, multiplayer etc
	char		date[MAX_QPATH];
	size_t		size;

	int		gamemode;
	qboolean		secure;		// prevent to console acess
	qboolean		nomodels;		// don't let player to choose model (use player.mdl always)
	qboolean		noskills;		// disable skill menu selection
	qboolean		render_picbutton_text; // use font renderer to render WON buttons

	char		sp_entity[32];	// e.g. info_player_start
	char		mp_entity[32];	// e.g. info_player_deathmatch
	char		mp_filter[32];	// filtering multiplayer-maps

	char		ambientsound[NUM_AMBIENTS][MAX_QPATH];	// quake ambient sounds

	int		max_edicts;	// min edicts is 600, max edicts is 8196
	int		max_tents;	// min temp ents is 300, max is 2048
	int		max_beams;	// min beams is 64, max beams is 512
	int		max_particles;	// min particles is 4096, max particles is 32768

	char		game_dll_linux[64];	// custom path for game.dll
	char		game_dll_osx[64];	// custom path for game.dll

	qboolean	added;
} gameinfo_t;

typedef enum
{
	GAME_NORMAL,
	GAME_SINGLEPLAYER_ONLY,
	GAME_MULTIPLAYER_ONLY
} gametype_t;

typedef struct fsinfo_s
{
	gameinfo_t	*GameInfo;	// current GameInfo
	gameinfo_t	*games[MAX_MODS];	// environment games (founded at each engine start)
	int		numgames;
} fsinfo_t;

#endif // FSINFO_H
