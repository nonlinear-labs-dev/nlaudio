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

#include "common/controlinterface.h"

#include <iostream>
#include <thread>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>

#include <sys/types.h>
#include <sys/socket.h> /* For accept */
#include <unistd.h> /* For read, errno, STDIN_FILENO */
#include <limits.h> /* For PIPE_BUF */
#include <functional>

#include<arpa/inet.h>
#include <sys/un.h>

namespace Nl {

using namespace std::placeholders;

/** \ingroup Tools
 *
 * \brief Constructor
 * \param func Function name
 * \param file File name
 * \param line Line number
 * \param errorNumber Alsa error number
 * \param what Descriptive string
 *
*/
ControlInterfaceException::ControlInterfaceException(std::string func, std::string file, int line, int errorNumber, std::string what) :
    m_func(func),
    m_file(file),
    m_msg(what),
    m_line(line),
    m_errno(errorNumber) {}

/** \ingroup Tools
 *
 * \brief Returns the desciptive string of the exception
 * \return A deciptive string of the exception
*/
const char* ControlInterfaceException::what() const noexcept
{
    std::stringstream ss;
    ss << m_file << ":" << m_func << ":" << m_line << ": " << m_msg;
    return ss.str().c_str();
}

std::ostream& operator<<(std::ostream& lhs, CommandDescriptor const& rhs)
{
    lhs << "[" << rhs.shortCmd << " | " << rhs.cmd << "]  " << rhs.description;
    return lhs;
}

ControlInterface::ControlInterface(JobHandle jobHandle) :
    m_isRunning(false),
    m_terminateRequest(false),
    m_thread(nullptr),
    m_jobHandle(jobHandle)
{
    // Add default commands
    // help
    Nl::CommandDescriptor cmdHelp;
    cmdHelp.description = "Show all available commands";
    cmdHelp.cmd = "help";
    cmdHelp.shortCmd = "h";
    cmdHelp.func = ControlInterface::help;
    addCommand(cmdHelp);

    // exit
    Nl::CommandDescriptor cmdExit;
    cmdExit.description = "Terminate audio engine";
    cmdExit.cmd = "exit";
    cmdExit.shortCmd = "e";
    cmdExit.func = ControlInterface::exit;
    addCommand(cmdExit);
}

void ControlInterface::start()
{
    if (!m_isRunning) {
        m_terminateRequest.store(false);
        m_thread = new std::thread(&ControlInterface::run, this);
        m_isRunning = true;
    }
}

void ControlInterface::stop()
{
    if (m_isRunning) {
        m_terminateRequest.store(true);
        m_thread->join();
        delete m_thread;
        m_thread = nullptr;
        m_isRunning = false;
    }
}

void ControlInterface::addCommand(const CommandDescriptor &cd)
{
    m_commands.push_back(CommandDescriptor(cd));
}

//static
void ControlInterface::help(std::vector<std::string> args, JobHandle jobHandle, int sockfd, ControlInterface *ptr)
{
    (void)args;
    (void)jobHandle;
    (void)sockfd;

    std::string msg = "Available Commands:\n\n";
    write(sockfd, msg.c_str(), msg.size());

    msg = "[q | quit]  Quit remote interface\n";
    write(sockfd, msg.c_str(), msg.size());

    std::stringstream s;
    std::copy(ptr->m_commands.begin(), ptr->m_commands.end(), std::ostream_iterator<CommandDescriptor>(s, "\n"));
    write(sockfd, s.str().c_str(), s.str().length());
}

//static
void ControlInterface::exit(std::vector<std::string> args, JobHandle jobHandle, int sockfd, ControlInterface *ptr)
{
    (void)args;
    (void)jobHandle;
    (void)sockfd;

    std::cout << "Storing..." << std::endl;
    jobHandle.workingThreadHandle.terminateRequest->store(true);
    //ptr->m_terminateRequest.store(true);
}

// Static
void ControlInterface::run(ControlInterface *ptr)
{
    //Create socket
    int sockfd = ::socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cerr << "Can not create socket" << std::endl;
        ptr->m_terminateRequest.store(true);
    }

    int enable = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) {
        std::cerr << "Can not set socket option SO_REUSEADDR: " << ::strerror(errno) << std::endl;
        ptr->m_terminateRequest.store(true);
        ::close(sockfd);
    }

    enable = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, &enable, sizeof(int)) < 0) {
        std::cerr << "Can not set socket option SO_REUSEPORT: " << ::strerror(errno) << std::endl;
        ptr->m_terminateRequest.store(true);
        ::close(sockfd);
    }

    struct sockaddr_in server;
    memset(&server, 0, sizeof(struct sockaddr_in));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    if (::bind(sockfd, (struct sockaddr*)&server, sizeof(server)) < 0) {
        std::cerr << "Can not bind to socket: " << ::strerror(errno) << std::endl;
        ptr->m_terminateRequest.store(true);
        ::close(sockfd);
    }

    if(::listen(sockfd, 5) < 0) {
        std::cerr << "Can not listen to socket: " << ::strerror(errno) << std::endl;
        ptr->m_terminateRequest.store(true);
    }

    timeval tv;
    fd_set fd;

    while(!ptr->m_terminateRequest.load()) {

        int ret = 0;
        tv.tv_sec = 1;
        tv.tv_usec = 0;

        FD_ZERO(&fd);
        FD_SET(sockfd, &fd);

        if ((ret = select(sockfd+1, &fd, NULL, NULL, &tv)) == 0) {
            continue;
        } else if (ret < 0) {
            std::cerr << "Error in select: " << ::strerror(ret) << std::endl;
            ptr->m_terminateRequest.store(true);
            continue;
        }

        int fd = TEMP_FAILURE_RETRY(accept(sockfd, NULL, NULL));
        if (fd < 0) {
            std::cerr << "Can not listen to socket: " << ::strerror(errno) << std::endl;
            ptr->m_terminateRequest.store(true);
            continue;
        }

        ControlInterface::handleClient(fd, ptr);
    }

    TEMP_FAILURE_RETRY(::close(sockfd));
}

// Static
int ControlInterface::read(int fd, std::string *data)
{
    int ret = TEMP_FAILURE_RETRY(::recv(fd, &(*data)[0], data->size(), 0));

    return ret;
}

// Static
void ControlInterface::handleClient(int fd, ControlInterface *ptr)
{
    new std::thread([](int fd, ControlInterface *ptr) {

        std::string data = "";
        data.resize(1024);

        while(!ptr->m_terminateRequest.load()) {

            if (ControlInterface::read(fd, &data) < 0)
                break;

            std::istringstream f(data);
            std::vector<std::string> tokens;

            copy(std::istream_iterator<std::string>(f),
                 std::istream_iterator<std::string>(),
                 std::back_inserter(tokens));

            if (tokens.size() == 0)
                continue;

            std::string cmd = tokens[0];
            tokens.erase(tokens.begin());

            // Special case: quit
            if (cmd == "quit" || cmd == "q") {
                std::string gb = "Goodbye!\n";
                write(fd, gb.c_str(), gb.size());
                break;
            }

            // Todo: access over ptr must be mutexed!
            bool foundCmd = false;
            for (auto i = ptr->m_commands.begin(); i != ptr->m_commands.end(); ++i) {
                if (i->cmd == cmd || i->shortCmd == cmd) {
                    i->func(tokens, ptr->m_jobHandle, fd, ptr);
                    foundCmd = true;
                }
            }

            if (!foundCmd) {
                std::string ret = "Unknown command (" + cmd + ")! Try 'help' if unsure.\n";
                write(fd, ret.c_str(), ret.size());
            }

        }
        TEMP_FAILURE_RETRY(::close(fd));

    }, fd, ptr);

}

} // namespace Nl
