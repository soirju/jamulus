/******************************************************************************\
 * Copyright (c) 2021
 *
 * Author(s):
 *  Christoph Meyer
 *
 ******************************************************************************
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later 
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT 
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more 
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 *
\******************************************************************************/

#pragma once

#ifdef WITH_API

#include <pistache/endpoint.h>

#include "server.h"
#include "client.h"

using namespace Pistache;

class CApi {
    public: 
        CApi(CServer* server, int port );
        CApi(CClient* client, int port );
};

class CApiHandler : public Http::Handler {

    public: 
        HTTP_PROTOTYPE(CApiHandler)
        void onRequest(const Http::Request& request, Http::ResponseWriter response);
};

#endif

