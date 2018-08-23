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

#include <common/debugbuffer.h>

#include <iostream>

namespace Nl {

void DebugBuffer::insert(const SharedPrintableDebugBufferItem& item)
{
    std::lock_guard<std::mutex> guard(m_lock);
    m_items.push(item);
}

std::ostream& operator<<(std::ostream &s, DebugBuffer& p)
{
    std::queue<SharedPrintableDebugBufferItem> copy;

    {
        std::lock_guard<std::mutex> guard(p.m_lock);
        copy = p.m_items;
        while (!p.m_items.empty()) p.m_items.pop();
    }

    while (!copy.empty()) {
        s << copy.front()->print();
        copy.pop();
    }

    return s;
}

SharedDebugBuffer createSharedDebugBuffer()
{
    return SharedDebugBuffer(new DebugBuffer);
}

} // namespace NL
