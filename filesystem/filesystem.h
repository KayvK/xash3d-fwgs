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

#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <stdarg.h>
#include <stddef.h>
#include "xash3d_types.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#include "fsinfo.h"

// filesystem flags
#define FS_STATIC_PATH  ( 1U << 0 )  // FS_ClearSearchPath will be ignore this path
#define FS_NOWRITE_PATH ( 1U << 1 )  // default behavior - last added gamedir set as writedir. This flag disables it
#define FS_GAMEDIR_PATH ( 1U << 2 )  // just a marker for gamedir path
#define FS_CUSTOM_PATH  ( 1U << 3 )  // custom directory
#define FS_GAMERODIR_PATH       ( 1U << 4 ) // caseinsensitive

#define FS_GAMEDIRONLY_SEARCH_FLAGS ( FS_GAMEDIR_PATH | FS_CUSTOM_PATH | FS_GAMERODIR_PATH )

//
// filesystem.c
//
typedef struct
{
	int	numfilenames;
	char	**filenames;
	char	*filenamesbuffer;
} search_t;

//
// memory interface
//
typedef struct fs_memfuncs_t
{
	int version;

	// memory
	poolhandle_t (*_Mem_AllocPool)( const char *name, const char *filename, int fileline );
	void  (*_Mem_FreePool)( poolhandle_t *poolptr, const char *filename, int fileline );
	void *(*_Mem_Alloc)( poolhandle_t poolptr, size_t size, qboolean clear, const char *filename, int fileline );
	void *(*_Mem_Realloc)( poolhandle_t poolptr, void *memptr, size_t size, qboolean clear, const char *filename, int fileline );
	void  (*_Mem_Free)( void *data, const char *filename, int fileline );
} fs_memfuncs_t;

typedef struct fs_logfuncs_t
{
	int version;

	// logging
	void    (*_Con_Printf)( const char *fmt, ... ) _format( 1 ); // typical console allowed messages
	void    (*_Con_DPrintf)( const char *fmt, ... ) _format( 1 ); // -dev 1
	void    (*_Con_Reportf)( const char *fmt, ... ) _format( 1 ); // -dev 2

	void    (*_Sys_Error)( const char *fmt, ... ) _format( 1 );
} fs_logfuncs_t;

#define FS_MEMFUNCS_INTERFACE_VERSION 1
#define FS_LOGFUNCS_INTERFACE_VERSION 1

extern fsinfo_t EXPORT_ FI;
#define GI           FI.GameInfo
#define FS_Gamedir() GI->gamefolder
#define FS_Title()   GI->title

qboolean EXPORT FS_InitStdio( qboolean caseinsensitive, const char *rootdir, const char *basedir, const char *gamedir, const char *rodir, fs_memfuncs_t *memfuncs, fs_logfuncs_t *logfuncs );
void EXPORT FS_ShutdownStdio( void );
void EXPORT FS_Path( void );
void EXPORT FS_Rescan( void );
void EXPORT FS_ClearSearchPath( void );
void EXPORT FS_AllowDirectPaths( qboolean enable );
void EXPORT FS_AddGameDirectory( const char *dir, uint flags );
void EXPORT FS_AddGameHierarchy( const char *dir, uint flags );
void EXPORT FS_LoadGameInfo( const char *rootfolder );
const char EXPORT *FS_GetDiskPath( const char *name, qboolean gamedironly );
byte EXPORT *FS_LoadFile( const char *path, fs_offset_t *filesizeptr, qboolean gamedironly );
qboolean EXPORT CRC32_File( dword *crcvalue, const char *filename );
qboolean EXPORT MD5_HashFile( byte digest[16], const char *pszFileName, uint seed[4] );
byte EXPORT *FS_LoadDirectFile( const char *path, fs_offset_t *filesizeptr );
qboolean EXPORT FS_WriteFile( const char *filename, const void *data, fs_offset_t len );
search_t EXPORT *FS_Search( const char *pattern, int caseinsensitive, int gamedironly );
file_t EXPORT *FS_Open( const char *filepath, const char *mode, qboolean gamedironly );
fs_offset_t EXPORT FS_Write( file_t *file, const void *data, size_t datasize );
fs_offset_t EXPORT FS_Read( file_t *file, void *buffer, size_t buffersize );
int EXPORT FS_VPrintf( file_t *file, const char *format, va_list ap );
int EXPORT FS_Seek( file_t *file, fs_offset_t offset, int whence );
int EXPORT FS_Gets( file_t *file, byte *string, size_t bufsize );
int EXPORT FS_Printf( file_t *file, const char *format, ... ) _format( 2 );
fs_offset_t EXPORT FS_FileSize( const char *filename, qboolean gamedironly );
int EXPORT FS_FileTime( const char *filename, qboolean gamedironly );
int EXPORT FS_Print( file_t *file, const char *msg );
qboolean EXPORT FS_Rename( const char *oldname, const char *newname );
int EXPORT FS_FileExists( const char *filename, int gamedironly );
int EXPORT FS_SetCurrentDirectory( const char *path );
qboolean EXPORT FS_SysFileExists( const char *path, qboolean casesensitive );
qboolean EXPORT FS_FileCopy( file_t *pOutput, file_t *pInput, int fileSize );
qboolean EXPORT FS_Delete( const char *path );
int EXPORT FS_UnGetc( file_t *file, byte c );
fs_offset_t EXPORT FS_Tell( file_t *file );
qboolean EXPORT FS_Eof( file_t *file );
int EXPORT FS_Close( file_t *file );
int EXPORT FS_Getc( file_t *file );
fs_offset_t EXPORT FS_FileLength( file_t *f );
qboolean EXPORT FS_FindLibrary( const char *dllname, qboolean directpath, char *dllpath, size_t dllpathlen, qboolean *encrypted, qboolean *custom_loader, char *fullPath, size_t fullpathlen );
void EXPORT FS_Path_f( void );

#ifdef __cplusplus
}
#endif // __cplusplus

#endif//FILESYSTEM_H
