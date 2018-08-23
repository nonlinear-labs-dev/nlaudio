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

class DebugBuffer;
typedef std::shared_ptr<DebugBuffer> SharedDebugBuffer;

class PrintableDebugBufferItem;
typedef std::shared_ptr<PrintableDebugBufferItem> SharedPrintableDebugBufferItem;

class PrintableDebugBufferItem
{
public:
    virtual void print(std::ostream &s) = 0;
    std::ostream &operator<<(std::ostream &s);
};

template <typename T>
class DebugBufferItem : public PrintableDebugBufferItem
{
public:
    DebugBufferItem(const T& item)
    {
        set(item);
    }

    void set(const T& item)
    {
        m_shadow = item;
    }

    T get(void) const
    {
        return m_shadow;
    }

    virtual void print(std::ostream &s) override
    {
        s << m_shadow;
    }
private:
    T m_shadow;
};

class DebugBuffer
{
public:
    void insert(const SharedPrintableDebugBufferItem& item);

private:
    std::mutex m_lock;
    std::queue<SharedPrintableDebugBufferItem> m_items;
    friend std::ostream& operator<<(std::ostream &s, DebugBuffer& p);
};

template <typename T>
SharedPrintableDebugBufferItem pack(T d)
{
    return SharedPrintableDebugBufferItem(new DebugBufferItem<T>(d));
};

SharedDebugBuffer createSharedDebugBuffer();

} // namespace Nl
