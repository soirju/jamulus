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

//Let's run this code only if GAMELIFT is enabled. Only with Server targets!
#if WITH_GAMELIFT

#include "gameliftserver.h"
#include "aws/gamelift/server/GameLiftServerAPI.h"

GameliftServer::GameliftServer(const int          iNewMaxNumChan,
                   const QString&     strLoggingFileName,
                   const quint16      iPortNumber,
                   const QString&     strHTMLStatusFileName,
                   const QString&     strCentralServer,
                   const QString&     strServerInfo,
                   const QString&     strServerListFilter,
                   const QString&     strServerPublicIP,
                   const QString&     strNewWelcomeMessage,
                   const QString&     strRecordingDirName,
                   const bool         bNDisconnectAllClientsOnQuit,
                   const bool         bNUseDoubleSystemFrameSize,
                   const bool         bNUseMultithreading,
                   const bool         bDisableRecording,
                   const ELicenceType eNLicenceType )
{
    // Initailize Gamelift SDK
    Aws::GameLift::Server::InitSDKOutcome initOutcome = 
            Aws::GameLift::Server::InitSDK(); 

    // initialize jamulus server
    CServer::CServer(    iNewMaxNumChan,
            strLoggingFileName,
            iPortNumber,
            strHTMLStatusFileName,
            strCentralServer,
            strServerInfo,
            strServerListFilter,
            strServerPublicIP,
            strNewWelcomeMessage,
            strRecordingDirName,
            bNDisconnectAllClientsOnQuit,
            bNUseDoubleSystemFrameSize,
            bNUseMultithreading,
            bDisableRecording,
            eNLicenceType );


}

GameliftServer::~GameLiftServer() 
{
    CServer::~CServer();
}


#endif
