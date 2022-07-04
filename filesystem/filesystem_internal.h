/*
filesystem.h - engine FS
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

#ifndef FILESYSTEM_INTERNAL_H
#define FILESYSTEM_INTERNAL_H

#include "xash3d_types.h"
#include "filesystem.h"

typedef struct zip_s zip_t;
typedef struct pack_s pack_t;
typedef struct wfile_s wfile_t;

enum
{
	SEARCHPATH_PLAIN = 0,
	SEARCHPATH_PAK,
	SEARCHPATH_WAD,
	SEARCHPATH_ZIP
};

typedef struct stringlist_s
{
	// maxstrings changes as needed, causing reallocation of strings[] array
	int		maxstrings;
	int		numstrings;
	char		**strings;
} stringlist_t;

typedef struct searchpath_s
{
	string  filename;
	int     type;
	int     flags;
	union
	{
		pack_t  *pack;
		wfile_t *wad;
		zip_t   *zip;
	};
	struct searchpath_s *next;
} searchpath_t;

extern searchpath_t *fs_searchpaths;
extern poolhandle_t  fs_mempool;
extern fs_memfuncs_t g_memfuncs;
extern fs_logfuncs_t g_logfuncs;
extern qboolean      fs_ext_path;
extern char          fs_rodir[MAX_SYSPATH];

#define Mem_Malloc( pool, size ) g_memfuncs._Mem_Alloc( pool, size, false, __FILE__, __LINE__ )
#define Mem_Calloc( pool, size ) g_memfuncs._Mem_Alloc( pool, size, true, __FILE__, __LINE__ )
#define Mem_Realloc( pool, ptr, size ) g_memfuncs._Mem_Realloc( pool, ptr, size, true, __FILE__, __LINE__ )
#define Mem_Free( mem ) g_memfuncs._Mem_Free( mem, __FILE__, __LINE__ )
#define Mem_AllocPool( name ) g_memfuncs._Mem_AllocPool( name, __FILE__, __LINE__ )
#define Mem_FreePool( pool ) g_memfuncs._Mem_FreePool( pool, __FILE__, __LINE__ )

#define Con_Printf  (*g_logfuncs._Con_Printf)
#define Con_DPrintf (*g_logfuncs._Con_DPrintf)
#define Con_Reportf (*g_logfuncs._Con_Reportf)
#define Sys_Error   (*g_logfuncs._Sys_Error)

//
// filesystem.c
//
void stringlistappend( stringlist_t *list, char *text );
int           FS_SysFileTime( const char *filename );
file_t       *FS_OpenHandle( const char *syspath, int handle, fs_offset_t offset, fs_offset_t len );
file_t       *FS_SysOpen( const char *filepath, const char *mode );
const char   *FS_FixFileCase( const char *path );
searchpath_t *FS_FindFile( const char *name, int *index, qboolean gamedironly );

//
// pak.c
//
int      FS_FileTimePAK( pack_t *pack );
int      FS_FindFilePAK( pack_t *pack, const char *name );
void     FS_PrintPAKInfo( char *dst, size_t size, pack_t *pack );
void     FS_ClosePAK( pack_t *pack );
void     FS_SearchPAK( stringlist_t *list, pack_t *pack, const char *pattern );
file_t  *FS_OpenPackedFile( pack_t *pack, int pack_ind );
qboolean FS_AddPak_Fullpath( const char *pakfile, qboolean *already_loaded, int flags );

//
// wad.c
//
int      FS_FileTimeWAD( wfile_t *wad );
int      FS_FindFileWAD( wfile_t *wad, const char *name );
void     FS_PrintWADInfo( char *dst, size_t size, wfile_t *wad );
void     FS_CloseWAD( wfile_t *wad );
void     FS_SearchWAD( stringlist_t *list, wfile_t *wad, const char *pattern );
byte    *FS_LoadWADFile( const char *path, fs_offset_t *sizeptr, qboolean gamedironly );
qboolean FS_AddWad_Fullpath( const char *wadfile, qboolean *already_loaded, int flags );

//
// zip.c
//
int      FS_FileTimeZIP( zip_t *zip );
int      FS_FindFileZIP( zip_t *zip, const char *name );
void     FS_PrintZIPInfo( char *dst, size_t size, zip_t *zip );
void     FS_CloseZIP( zip_t *zip );
void     FS_SearchZIP( stringlist_t *list, zip_t *zip, const char *pattern );
byte    *FS_LoadZIPFile( const char *path, fs_offset_t *sizeptr, qboolean gamedironly );
file_t  *FS_OpenZipFile( zip_t *zip, int pack_ind );
qboolean FS_AddZip_Fullpath( const char *zipfile, qboolean *already_loaded, int flags );

#endif // FILESYSTEM_INTERNAL_H
