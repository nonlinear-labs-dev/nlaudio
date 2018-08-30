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

#include <queue>
#include <memory>
#include <mutex>
//#include <numeric>

namespace Nl {

class CommandBuffer;
typedef std::shared_ptr<CommandBuffer> SharedCommandBuffer;

class CommandBuffer {
public:
    enum Command {
        CMD_GET_TCD_INPUT,
        CMD_GET_SIGNAL,
        CMD_GET_PARAM,
        CMD_GET_CPU_LOAD,
        CMD_RESET,
        CMD_NO_CMD = std::numeric_limits<int>::max() // Sentinel
    };

    Command get();
    void set(Command c);

private:
    std::queue<Command> m_queue;
    std::mutex m_lock;

};

SharedCommandBuffer createSharedCommandBuffer();

} // namespace Nl
