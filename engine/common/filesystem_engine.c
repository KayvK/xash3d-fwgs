 /*
filesystem.c - game filesystem based on DP fs
Copyright (C) 2007 Uncle Mike

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
*/

#include "common.h"
#include "library.h"

/*
================
FS_Rescan_f
================
*/
void FS_Rescan_f( void )
{
	FS_Rescan();
}

/*
============
FS_ClearPath_f

only for debug targets
============
*/
void FS_ClearPaths_f( void )
{
	FS_ClearSearchPath();
}

static fs_memfuncs_t fs_memfuncs =
{
	FS_MEMFUNCS_INTERFACE_VERSION,
	_Mem_AllocPool,
	_Mem_FreePool,
	_Mem_Alloc,
	_Mem_Realloc,
	_Mem_Free,
};

static fs_logfuncs_t fs_logfuncs =
{
	FS_LOGFUNCS_INTERFACE_VERSION,
	Con_Printf,
	Con_DPrintf,
	Con_Reportf,
	Sys_Error,
};

/*
================
FS_Init
================
*/
void FS_Init( void )
{
	qboolean		hasBaseDir = false;
	qboolean		hasGameDir = false;
	qboolean		caseinsensitive = true;
	int		i;
	string gamedir;

	Cmd_AddRestrictedCommand( "fs_rescan", FS_Rescan_f, "rescan filesystem search pathes" );
	Cmd_AddRestrictedCommand( "fs_path", FS_Path_f, "show filesystem search pathes" );
	Cmd_AddRestrictedCommand( "fs_clearpaths", FS_ClearPaths_f, "clear filesystem search pathes" );

#if !XASH_WIN32
	if( Sys_CheckParm( "-casesensitive" ) )
		caseinsensitive = false;
#endif

	if( !Sys_GetParmFromCmdLine( "-game", gamedir ))
		Q_strncpy( gamedir, SI.basedirName, sizeof( gamedir )); // gamedir == basedir

	FS_InitStdio( caseinsensitive, host.rootdir, SI.basedirName, gamedir, host.rodir, &fs_memfuncs, &fs_logfuncs );

	if( !Sys_GetParmFromCmdLine( "-dll", SI.gamedll ))
		SI.gamedll[0] = 0;

	if( !Sys_GetParmFromCmdLine( "-clientlib", SI.clientlib ))
		SI.clientlib[0] = 0;
}

/*
================
FS_Shutdown
================
*/
void FS_Shutdown( void )
{
	int	i;

	FS_ShutdownStdio();

	memset( &SI, 0, sizeof( sysinfo_t ));

}




