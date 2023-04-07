/*
 * Copyright (C) 2015 Niek Linnenbank
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <ProcessClient.h>
#include "Renice.h"

Renice::Renice(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("Output system process list");
    parser().registerFlag('n', "priority", "Change the process to this priority");
    parser().registerPositional("PRIORITY", "Set the process to this priority");
    parser().registerPositional("PID", "Set this process ID to new prioity");
}

Renice::Result Renice::exec()
{
    ProcessClient process;

    ProcessID pid = atoi(arguments().get("PID"));
    u8 priority = atoi(arguments().get("PRIORITY"));

    ProcessClient::Info info;
    const ProcessClient::Result result = process.processInfo(pid, info);
    if(result != ProcessClient::Success)
    {
        return InvalidArgument;
    }

    if (priority > 5 || priority < 1)
    {
        return InvalidArgument;
    }
    


    process.setPriority(pid, priority);
    printf("\nfinished");
    return Success;
}