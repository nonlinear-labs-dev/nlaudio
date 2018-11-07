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

#include <common/commandbufferresponse.h>

#include <iostream>

namespace Nl {

void CommandBufferResponse::insert(const SharedPrintableCommandBufferResponseItem& item)
{
    std::lock_guard<std::mutex> guard(m_lock);
    m_items.push(item);
}

bool CommandBufferResponse::canRead()
{
    std::lock_guard<std::mutex> guard(m_lock);
    return !m_items.empty();
}

std::ostream &PrintableCommandBufferResponseItem::operator<<(std::ostream &s)
{
    print(s);
    return s;
}

std::ostream& operator<<(std::ostream &s, CommandBufferResponse& p)
{
    static std::queue<SharedPrintableCommandBufferResponseItem> copy;

    {
        std::lock_guard<std::mutex> guard(p.m_lock);
        p.m_items.swap(copy);
    }

   // if (!copy.empty()) s << "Debug: " << std::endl;
    while (!copy.empty()) {
        s << "  ";
        copy.front().get()->operator<<(s);
        copy.pop();
    }
    s << std::endl;

    return s;
}

SharedCommandBufferResponse createSharedCommandBufferResponse()
{
    return SharedCommandBufferResponse(new CommandBufferResponse);
}

} // namespace NL
