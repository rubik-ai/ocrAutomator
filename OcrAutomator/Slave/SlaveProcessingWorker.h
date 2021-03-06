#pragma once
#include "Base/BaseProcessingWorker.h"
#include "Slave/Network/NetworkClient.h"
#include "SlaveFileStatus.h"
#include <future>

namespace Docapost {
	namespace IA {
		namespace Tesseract {
			class SlaveProcessingWorker : public BaseProcessingWorker<SlaveFileStatus>
			{
			private:

				std::atomic<int> threadToRun;
								
				std::shared_ptr<NetworkClient> mNetwork;
				boost::thread* mNetworkThread = nullptr;
				std::thread* mAsioThread = nullptr;
				std::mutex mStackToSendMutex;

				std::atomic<int> mPending{ 0 };

				std::string mIp;

				std::deque<SlaveFileStatus*> mFilesToSend;

				void AddFileToSend(SlaveFileStatus* file);
				SlaveFileStatus* GetFileToSend();

				void NetwordLoop();

				void ThreadLoop(int id) override;

				void TerminateThread(int id);

				void OnMasterConnectedHandler();
				void OnMasterDisconnectHandler();
				void OnMasterStatusChangedHandler(int threadToRun, int done, int skip, int total, int psm, int oem, std::string lang);
				void OnMasterSynchroHandler(int thread, int done, int skip, int total, bool end, int pending, boost::unordered_map<std::string, MemoryFileBuffer*> files);
			public:
				boost::signals2::signal<void(SlaveFileStatus*)> onEndProcessFile;
				boost::signals2::signal<void(SlaveFileStatus*)> onStartProcessFile;
				boost::signals2::signal<void()> onProcessEnd;
				boost::signals2::signal<void()> onNewBatch;

				SlaveProcessingWorker(OcrFactory& ocr, int port = 12000, std::string ip = std::string());
				~SlaveProcessingWorker();

				bool NetworkEnable() const { return mNetwork != nullptr;  }
				int Port() const
				{
					if (NetworkEnable())
						return mNetwork->Port();
					else
						return 0;
				}
				std::thread* Run(int nbThread) override;

				std::string remote_address() const { return mNetwork->GetRemoteAddress(); }
				bool remote_isconnected() const { return mNetwork != nullptr && mNetwork->IsOpen(); }
			};
		}
	}
}
