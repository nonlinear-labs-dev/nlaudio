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
namespace DebugBuffer {

SharedDebugBufferQueue createSharedDebugBufferQueue()
{
    auto *queuePtr = new std::queue<SharedPrintableDebugBuffer>();
    return std::shared_ptr<std::queue<SharedPrintableDebugBuffer>>(queuePtr);
}

void print(SharedDebugBufferQueue q, std::ostream &out)
{
    while (!q->empty()) {
        std::shared_ptr<Nl::PrintableDebugBuffer> curr = q->front();
        out << curr->print();
        q->pop();
    }
}

} // namespace DebugBuffer
} // namespace NL
