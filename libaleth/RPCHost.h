/*
	This file is part of cpp-ethereum.

	cpp-ethereum is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	cpp-ethereum is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with cpp-ethereum.  If not, see <http://www.gnu.org/licenses/>.
*/
/** @file RPCHost.h
 * @author Gav Wood <i@gavwood.com>
 * @date 2015
 */

#pragma once

#include <libdevcore/Common.h>
#include <libweb3jsonrpc/IpcServer.h>

template <class... Is> class ModularServer;

namespace dev
{

struct SessionPermissions;
class SafeHttpServer;

namespace rpc
{
class DBFace;
class WhisperFace;
class NetFace;
class BzzFace;
class Web3Face;
}

namespace aleth
{

class AlethFace;
class WebThreeServer;
class AlethWhisper;

class RPCHost
{
public:
	RPCHost() = default;
	RPCHost(AlethFace* _aleth) { init(_aleth); }
	~RPCHost();

	void init(AlethFace* _aleth);
	std::string newSession(SessionPermissions const& _p);
	WebThreeServer* web3Face() const { return m_web3Face; }
	AlethWhisper* whisperFace() const { return m_whisperFace; }
	SafeHttpServer* httpConnector() const;
	IpcServer* ipcConnector() const;

private:
	WebThreeServer* m_web3Face;
	AlethWhisper* m_whisperFace;
	std::shared_ptr<ModularServer<WebThreeServer, rpc::DBFace, rpc::WhisperFace, rpc::NetFace, rpc::BzzFace, rpc::Web3Face>> m_rpcServer;
	unsigned m_httpConnectorId;
	unsigned m_ipcConnectorId;
};

}
}
