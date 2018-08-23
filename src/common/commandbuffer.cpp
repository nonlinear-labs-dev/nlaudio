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

#include <common/commandbuffer.h>

namespace Nl {

CommandBuffer::Command CommandBuffer::get()
{
    Command ret = CMD_NO_CMD;

    if (!m_queue.empty()) {
        std::lock_guard<std::mutex> guard(m_lock);
        ret = m_queue.front();
        m_queue.pop();
    }

    return ret;
}

void CommandBuffer::set(CommandBuffer::Command c)
{
    std::lock_guard<std::mutex> guard(m_lock);
    m_queue.push(c);
}

SharedCommandBuffer createSharedCommandBuffer()
{
    return SharedCommandBuffer(new CommandBuffer);
}



} // namespace Nl

