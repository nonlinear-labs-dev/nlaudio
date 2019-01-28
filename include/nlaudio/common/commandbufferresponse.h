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

class CommandBufferResponse;
typedef std::shared_ptr<CommandBufferResponse> SharedCommandBufferResponse;

class PrintableCommandBufferResponseItem;
typedef std::shared_ptr<PrintableCommandBufferResponseItem> SharedPrintableCommandBufferResponseItem;

class PrintableCommandBufferResponseItem
{
public:
    virtual void print(std::ostream &s) = 0;
    std::ostream &operator<<(std::ostream &s);
};

template <typename T>
class CommandBufferResponseItem : public PrintableCommandBufferResponseItem
{
public:
    CommandBufferResponseItem(const T& item)
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

class CommandBufferResponse
{
public:
    void insert(const SharedPrintableCommandBufferResponseItem& item);
    bool canRead();

private:
    std::mutex m_lock;
    std::queue<SharedPrintableCommandBufferResponseItem> m_items;
    friend std::ostream& operator<<(std::ostream &s, CommandBufferResponse& p);
};

template <typename T>
SharedPrintableCommandBufferResponseItem pack(T d)
{
    return SharedPrintableCommandBufferResponseItem(new CommandBufferResponseItem<T>(d));
}

SharedCommandBufferResponse createSharedCommandBufferResponse();

} // namespace Nl
