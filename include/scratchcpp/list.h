// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <string>
#include <scratchcpp/veque.h>

#include "value.h"
#include "entity.h"

namespace libscratchcpp
{

class Target;
class Monitor;
class ListPrivate;

/*! \brief The List class represents a Scratch list. */
class LIBSCRATCHCPP_EXPORT List
    : public veque::veque<Value>
    , public Entity
{
    public:
        List(const std::string &id, const std::string &name);
        List(const List &) = delete;

        const std::string &name();
        void setName(const std::string &name);

        Target *target() const;
        void setTarget(Target *target);

        Monitor *monitor() const;
        void setMonitor(Monitor *monitor);

        long indexOf(const Value &value) const;
        bool contains(const Value &value) const;

        /*! Removes the item at index. */
        void removeAt(int index) { erase(begin() + index); }

        /*! Inserts an item at index. */
        void insert(int index, const Value &value) { veque<Value>::insert(begin() + index, value); }

        /*! Replaces the item at index. */
        void replace(int index, const Value &value) { at(index) = value; }

        std::string toString() const;

        std::shared_ptr<List> clone();

    private:
        spimpl::unique_impl_ptr<ListPrivate> impl;
};

} // namespace libscratchcpp
