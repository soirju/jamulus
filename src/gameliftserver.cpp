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

#include<chrono>
#include "gameliftserver.h"

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
                   const ELicenceType eNLicenceType ) : CServer(
                        iNewMaxNumChan,
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
                        eNLicenceType )
{
    // Called after CServer constructor is executed
    // Initailize Gamelift SDK - timeout of 3 seconds for server connection
    qDebug() << "Initialize Gamelift SDK";
    auto outcome = Aws::GameLift::Server::InitSDK();
    qInfo() << "Initialization succeeded";

    qDebug() << "Start Process Ready procedure";
    std::string serverLog("serverOut.log");        // Example of a log file written by the game server
    std::vector<std::string> logPaths;
    logPaths.push_back(serverLog);

    int listenPort = 22124;

    Aws::GameLift::Server::ProcessParameters processReadyParameter = Aws::GameLift::Server::ProcessParameters(
        std::bind(&GameliftServer::onStartGameSession, this, std::placeholders::_1),
        std::bind(&GameliftServer::onProcessTerminate, this),
        std::bind(&GameliftServer::onHealthCheck, this),
        listenPort,
        Aws::GameLift::Server::LogParameters(logPaths)); 

    auto outcome2 =  Aws::GameLift::Server::ProcessReady(processReadyParameter);


}

GameliftServer::~GameliftServer() 
{
    qInfo() << "Terminate Gamelift";
    // stop gamelift server
    auto outcome = Aws::GameLift::Server::ProcessEnding();
}

// Implement callback functions
void GameliftServer::onStartGameSession(Aws::GameLift::Server::Model::GameSession myGameSession)
{
// game-specific tasks when starting a new game session, such as loading map
auto outcome = Aws::GameLift::Server::ActivateGameSession ();
}

void GameliftServer::onProcessTerminate()
{
// game-specific tasks required to gracefully shut down a game session, 
// such as notifying players, preserving game state data, and other cleanup
delete this;
}

bool GameliftServer::onHealthCheck()
{
    bool health;
    // complete health evaluation within 60 seconds and set health
    health=true;
    return health;
}



#endif
