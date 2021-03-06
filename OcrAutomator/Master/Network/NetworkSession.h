#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <boost/asio.hpp>
#include <thread>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/uuid/uuid.hpp>
#include <boost/unordered_map.hpp>
#include <boost/signals2.hpp>
#include "Protobuf/Protobuf_all.h"
#include <queue>
#include "Buffer/MemoryFileBuffer.h"

namespace ip = boost::asio::ip;

class NetworkSession : public std::enable_shared_from_this<NetworkSession>
{
private:
	enum { max_length = 1024 };
	char mDefaultBuffer[max_length];
	std::string mHostname;

	ip::tcp::socket mSocket;

	boost::unordered_map<boost::uuids::uuid, bool> mFileSend;
	boost::uuids::uuid mId;

	std::queue<std::shared_ptr<std::vector<char>>> mWriteQueue; 
	boost::asio::io_service::strand mStrand;

	void WriteToStream(std::shared_ptr<std::vector<char>>);
	void WriteNextItemToStream();
	void WriteHandler(const boost::system::error_code& error,const size_t bytesTransferred);
	void ReceiveData(int length);
	void ReceiveDataHeader();
	void CloseSocket();
public:
	boost::signals2::signal<void(NetworkSession*, int, int, std::vector<std::tuple<boost::uuids::uuid, int, boost::posix_time::ptime, boost::posix_time::ptime, boost::posix_time::time_duration, std::vector<std::string>*>>&)> onSlaveSynchro;
	boost::signals2::signal<void(NetworkSession*, int, std::string)> onSlaveConnect;
	boost::signals2::signal<void(NetworkSession*, boost::unordered_map<boost::uuids::uuid, bool>&)> onSlaveDisconnect;

	explicit NetworkSession(ip::tcp::socket socket, boost::uuids::uuid id);
	void Start();
	void Stop();
	void SendStatus(int done, int skip, int total, int psm, int oem, std::string lang);
	void SendSynchro(int thread, int done, int skip, int total, bool isEnd, int pending, boost::unordered_map<boost::uuids::uuid, Docapost::IA::Tesseract::MemoryFileBuffer*> files);

	boost::uuids::uuid& Id() { return mId; }
	boost::unordered_map<boost::uuids::uuid, bool> FileState() const { return mFileSend; }
	std::string Hostname() const { return mHostname; }

	~NetworkSession();
};

