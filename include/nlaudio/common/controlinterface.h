/***
  Copyright (c) 2018 Nonlinear Labs GmbH

  Authors: Pascal Huerst <pascal.huerst@gmail.com>

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, see <http://www.gnu.org/licenses/>.
***/

#pragma once

#include <string>
#include <atomic>
#include <thread>
#include <list>
#include <vector>
#include <ostream>

#include <audio/audiofactory.h>

namespace Nl {

class ControlInterfaceException : public std::exception
{
public:
    ControlInterfaceException(std::string func, std::string file, int line, int errorNumber, std::string what);
    virtual const char* what() const noexcept;

private:
    std::string m_func;
    std::string m_file;
    std::string m_msg;
    int m_line;
    int m_errno;
};




class ControlInterface;
typedef void (*command)(std::vector<std::string> args, JobHandle jobHandle, int sockfd, ControlInterface *ptr);

struct CommandDescriptor {
    command func;
    std::string cmd;
    std::string shortCmd;
    std::string description;
};

std::ostream& operator<<(std::ostream& lhs, CommandDescriptor const& rhs);






class ControlInterface {

public:
    ControlInterface(JobHandle jobHandle);
    void start();
    void stop();

    void addCommand(const CommandDescriptor&cd);

    template <Nl::CommandBuffer::Command cb>
    Nl::CommandDescriptor makeCommand(const std::string& description, const std::string& cmd, const std::string& shortCmd)
    {
        Nl::CommandDescriptor cd;
        cd.description = description;
        cd.cmd = cmd;
        cd.shortCmd = shortCmd;
        cd.func = [](std::vector<std::string> args, Nl::JobHandle jobHandle, int sockfd, Nl::ControlInterface *ptr)
        {
            jobHandle.cmdBuffer->set(cb);
            while (!jobHandle.cmdBufferResponse->canRead())
                std::this_thread::sleep_for(std::chrono::milliseconds(100));

            std::stringstream s;
            s<<*jobHandle.cmdBufferResponse.get();
            write(sockfd, s.str().c_str(), s.str().size());
        };

        return cd;
    }

private:
    static int read(int fd, std::string *data);
    static void handleClient(int fd, ControlInterface *ptr);
    static void run(ControlInterface *ptr);
    static void help(std::vector<std::string> args, JobHandle jobHandle, int sockfd, ControlInterface *ptr);
    static void exit(std::vector<std::string> args, JobHandle jobHandle, int sockfd, ControlInterface *ptr);
    bool m_isRunning;
    std::atomic<bool> m_terminateRequest;
    std::thread *m_thread;
    std::list<CommandDescriptor> m_commands;
    JobHandle m_jobHandle;
};


} // namespace Nl
