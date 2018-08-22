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

#include <mutex>
#include <memory>
#include <queue>
#include <string>
#include <sstream>

namespace Nl {

class PrintableDebugBuffer;

typedef std::shared_ptr<PrintableDebugBuffer> SharedPrintableDebugBuffer;
typedef std::shared_ptr<std::queue<SharedPrintableDebugBuffer>> SharedDebugBufferQueue;

class PrintableDebugBuffer
{
public:
    virtual std::ostream &operator<<(std::ostream &s) = 0;
    virtual std::string print() = 0;
};

template <typename T>
class LockedDebugBuffer : public PrintableDebugBuffer
{
public:
    LockedDebugBuffer(const T& item)
    {
        set(item);
    }

    void set(const T& item)
    {
        std::lock_guard<std::mutex> guard(m_lock);

        m_shadow = item;
    }

    T get(void) const
    {
        std::lock_guard<std::mutex> guard(m_lock);

        return m_shadow;
    }

    virtual std::ostream &operator<<(std::ostream &s) override
    {
        s << m_shadow;
        return s;
    }

    virtual std::string print() override
    {
        std::stringstream ss;
        ss << m_shadow;
        return ss.str();
    }

private:
    T m_shadow;
    std::mutex m_lock;
};

namespace DebugBuffer {
    SharedDebugBufferQueue createSharedDebugBufferQueue();
    void print(SharedDebugBufferQueue q, std::ostream &out);

    template <typename T>
    SharedPrintableDebugBuffer pack(T d)
    {
        return SharedPrintableDebugBuffer(new LockedDebugBuffer<T>(d));
    };
} // namespace DebugBuffer

} // namespace Nl
