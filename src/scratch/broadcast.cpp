// SPDX-License-Identifier: Apache-2.0

#include <scratchcpp/broadcast.h>

#include "broadcast_p.h"

using namespace libscratchcpp;

/*! Constructs Broadcast. */
Broadcast::Broadcast(const std::string &id, const std::string &name, bool isBackdropBroadcast) :
    Entity(id),
    impl(spimpl::make_unique_impl<BroadcastPrivate>(name, isBackdropBroadcast))
{
}

/*! Returns the name of the broadcast. */
const std::string &Broadcast::name() const
{
    return impl->name;
}

/*! Sets the name of the broadcast. */
void Broadcast::setName(const std::string &newName)
{
    impl->name = newName;
}

/*! Returns true if this broadcast belongs to a backdrop. */
bool Broadcast::isBackdropBroadcast() const
{
    return impl->isBackdropBroadcast;
}
