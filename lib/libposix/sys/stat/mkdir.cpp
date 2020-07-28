/*
 * Copyright (C) 2009 Niek Linnenbank
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <FileSystemClient.h>
#include "errno.h"
#include "limits.h"
#include "unistd.h"
#include "stdio.h"
#include "string.h"
#include "sys/stat.h"

int mkdir(const char *path, mode_t mode)
{
    const FileSystemClient filesystem;
    char fullpath[PATH_MAX];

    // Relative or absolute?
    if (path[0] != '/')
    {
        char cwd[PATH_MAX];

        // What's the current working dir?
        getcwd(cwd, PATH_MAX);
        snprintf(fullpath, sizeof(fullpath), "%s/%s", cwd, path);
    }
    else
        strlcpy(fullpath, path, sizeof(fullpath));

    // Ask FileSystem to create the file for us
    const FileSystem::Result result = filesystem.createFile(fullpath,
                                                            FileSystem::DirectoryFile,
                                                           (FileSystem::FileModes) (mode & FILEMODE_MASK),
                                                            DeviceID());
    // Set errno
    if (result == FileSystem::Success)
        errno = ESUCCESS;
    else
        errno = EIO;

    // Report result
    return errno == ESUCCESS ? 0 : -1;
}
