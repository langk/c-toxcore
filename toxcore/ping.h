/*
 * Buffered pinging using cyclic arrays.
 */

/*
 * Copyright © 2016-2018 The TokTok team.
 * Copyright © 2013 Tox project.
 * Copyright © 2013 plutooo
 *
 * This file is part of Tox, the free peer to peer instant messenger.
 * This file is donated to the Tox Project.
 *
 * Tox is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Tox is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Tox.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef C_TOXCORE_TOXCORE_PING_H
#define C_TOXCORE_TOXCORE_PING_H

#include "DHT.h"
#include "network.h"

#include <stdint.h>

#ifndef IP_PORT_DEFINED
#define IP_PORT_DEFINED
typedef struct IP_Port IP_Port;
#endif /* IP_PORT_DEFINED */

#ifndef DHT_DEFINED
#define DHT_DEFINED
typedef struct DHT DHT;
#endif /* DHT_DEFINED */

#ifndef MONO_TIME_DEFINED
#define MONO_TIME_DEFINED
typedef struct Mono_Time Mono_Time;
#endif /* MONO_TIME_DEFINED */

#ifndef PING_DEFINED
#define PING_DEFINED
typedef struct Ping Ping;
#endif /* PING_DEFINED */

Ping *ping_new(const struct Mono_Time *mono_time, DHT *dht);

void ping_kill(Ping *ping);

/** Add nodes to the to_ping list.
 * All nodes in this list are pinged every TIME_TOPING seconds
 * and are then removed from the list.
 * If the list is full the nodes farthest from our public_key are replaced.
 * The purpose of this list is to enable quick integration of new nodes into the
 * network while preventing amplification attacks.
 *
 *  return 0 if node was added.
 *  return -1 if node was not added.
 */
int32_t ping_add(Ping *ping, const uint8_t *public_key, struct IP_Port ip_port);

void ping_iterate(Ping *ping);

int32_t ping_send_request(Ping *ping, struct IP_Port ipp, const uint8_t *public_key);

#endif // C_TOXCORE_TOXCORE_PING_H
