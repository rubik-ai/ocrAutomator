#include "Network.h"
#include <boost/uuid/uuid_io.hpp>
#include "Error.h"
#include "Version.h"

namespace ip = boost::asio::ip;
namespace proto = Docapost::IA::Tesseract::Proto;

void Network::BroadcastLoop()
{
	mUdpSocket.async_receive_from(boost::asio::buffer(mDefaultBuffer, max_length), mUdpSenderEndpoint, [this](boost::system::error_code ec, std::size_t bytes_recvd)
	{
		if (!ec && bytes_recvd > 0)
		{
			RespondBroadcast();
		}

		BroadcastLoop();
	});
} 
void Network::RespondBroadcast()
{
	proto::NetworkInfo s;
	s.set_port(mPort);
	s.set_version(VERSION);
	
	
	s.SerializeToArray(mDefaultBuffer, 1024);
	mUdpSocket.async_send_to(
		boost::asio::buffer(mDefaultBuffer, s.ByteSize()), mUdpSenderEndpoint,
		[this](boost::system::error_code /*ec*/, std::size_t /*bytes_sent*/)
	{
	});
}

void Network::InitBroadcastReceiver()
{
	BroadcastLoop();
}

void Network::InitComm()
{
	mTcpAcceptor.async_accept(mTcpSocket,
		[this](boost::system::error_code ec)
	{
		if (!ec)
		{
			auto obj = std::make_shared<NetworkSession>(std::move(mTcpSocket), mGen());

			obj->onSlaveConnect.connect([this](NetworkSession* ns, int thread, std::string hostname)
			{
				this->mConnections[ns->Id()] = ns;
				this->onSlaveConnect(ns, thread, hostname);
			});

			obj->onSlaveSynchro.connect([this](NetworkSession* ns, int thread, int required, std::vector<std::tuple<boost::uuids::uuid, int, boost::posix_time::ptime, boost::posix_time::ptime, boost::posix_time::time_duration, std::string>>& results)
			{
				this->onSlaveSynchro(ns, thread, required, results);
			});


			obj->onSlaveDisconnect.connect([this](NetworkSession* ns, boost::unordered_map<boost::uuids::uuid, bool>& noUsed)
			{
				this->mConnections.erase(ns->Id());
				this->onSlaveDisconnect(ns, noUsed);
			});

			// On a besoin de faire tourner la communication dans un nouveau thread pour pouvoir accepter d'autre client
			std::thread([obj]()
			{
				CatchAllErrorSignals();
				try
				{
					obj->Start();
				}
				catch(std::exception &e)
				{
					BOOST_LOG_WITH_LINE(Log::CommonLogger, boost::log::trivial::warning) << "[exception]: " << e.what();
				}
			}).detach();
		}

		InitComm();
	});
}

void Network::Start()
{
	std::lock_guard<std::mutex> lock(mStateMutex);
	while (true) {
		try {

			if (!mTcpAcceptor.is_open())
			{
				mTcpAcceptor.close();
				mTcpAcceptor = std::move(ip::tcp::acceptor(mService, ip::tcp::endpoint(ip::tcp::v4(), mPort)));
			}

			BOOST_LOG_WITH_LINE(Log::CommonLogger, boost::log::trivial::trace) << "ASIO service starting";
			boost::system::error_code ec;
			mService.run(ec);
			if (ec) { // handling asio system errors
				BOOST_LOG_WITH_LINE(Log::CommonLogger, boost::log::trivial::warning) << "[system-error]: " << ec.message();
				continue;
			}
			break;
		}
		catch (const std::exception& ex) {
			BOOST_LOG_WITH_LINE(Log::CommonLogger, boost::log::trivial::warning) << "[exception]: " << ex.what();
		}
	}
}
void Network::Stop()
{
	BOOST_LOG_WITH_LINE(Log::CommonLogger, boost::log::trivial::trace) << "Stoping ASIO service";
	const auto conn = mConnections;
	for (auto& c : conn)
	{
		c.second->onSlaveDisconnect.disconnect_all_slots();
		//delete c.second;
	}
	if(mUdpSocket.is_open())
		mUdpSocket.close();
	if (mTcpAcceptor.is_open())
		mTcpAcceptor.close();
	mService.stop();
	std::lock_guard<std::mutex> lock(mStateMutex);
}

Network::Network(short port) : 
mService(),
mUdpSocket(mService, ip::udp::endpoint(boost::asio::ip::address_v4::any(), port)),
mTcpSocket(mService),
mTcpAcceptor(mService, ip::tcp::endpoint(ip::tcp::v4(), port)),
mPort(port)
{
	mUdpSocket.set_option(boost::asio::socket_base::broadcast(true));
}

Network::~Network()
{
}
