// import the thrift headers
// #include <thrift/concurrency/ThreadManager.h>
// #include <thrift/concurrency/PosixThreadFactory.h>
#include <thrift/protocol/TBinaryProtocol.h>
// #include <thrift/server/TSimpleServer.h>
// #include <thrift/server/TThreadPoolServer.h>
// #include <thrift/server/TThreadedServer.h>
#include <thrift/server/TNonblockingServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <thrift/TToString.h>

// import common utility headers
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>
#include <fstream>
#include <sys/time.h>
#include <iomanip>
#include <boost/filesystem.hpp>

#include <stdlib.h>
#include <time.h>

// import opencv headers
#include "opencv2/core/core.hpp"
#include "opencv2/core/types_c.h"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/gpu.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/gpu/gpu.hpp"
#include "boost/program_options.hpp"
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
#include "boost/algorithm/string/replace.hpp"

// import the service headers
#include "IPAService.h"
#include "SchedulerService.h"
#include "service_constants.h"
#include "service_types.h"
#include "types_constants.h"
#include "types_types.h"
#include "commons.h"


// define the namespace
using namespace std;
using namespace cv;

namespace fs = boost::filesystem;

using namespace apache::thrift;
using namespace apache::thrift::concurrency;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;

// define the constant
// #define THREAD_WORKS 16
// FIXME this is only used for testing, command line option is required
// #define IMAGE_DATABASE "/home/hailong/sirius/sirius-application/image-matching/matching/landmarks/db"
// #define MATCHING_METHOD 1
// #define IMAGE_DATABASE "/home/hailong/sirius/sirius-application/image-matching/matching/landmarks/db"
class SpeechRecognitionServiceHandler : public IPAServiceIf {
	public:
		// put the model training here so that it only needs to
		// be trained once
		SpeechRecognitionServiceHandler() {
			this->budget = 100;
			this->SERVICE_NAME = "asr";
			this->SCHEDULER_IP = "141.212.107.226";
			this->SCHEDULER_PORT = 8888;
			this->SERVICE_IP = "clarity28.eecs.umich.edu";
			this->SERVICE_PORT = 9092;
		}
		~SpeechRecognitionServiceHandler() {
		}
		
		void updatBudget(const double budget) {
			this->budget = budget;
    			cout << "service " << this->SERVICE_NAME << " at " << this->SERVICE_IP << ":" << this->SERVICE_PORT << " update its budget to " << this->budget << endl;
  		}

		void submitQuery(const  ::QuerySpec& query) {
    			// Your implementation goes here
			// 1. record the time when the query comming into the queue 
			// 2. put the query to a thread saft queue structure
			// 3. a private class generates a helper thread to process the query from the queue
  		}
		void initialize() {
			// 1. register to the command center
			TClient tClient;
			this->scheduler_client = tClient.creatSchedulerClient(this->SCHEDULER_IP, this->SCHEDULER_PORT);
			THostPort hostPort;
			hostPort.ip = this->SERVICE_IP;
			hostPort.port = this->SERVICE_PORT;
			RegMessage regMessage;
			regMessage.app_name = this->SERVICE_NAME;
			regMessage.endpoint = hostPort;
			regMessage.budget = this->budget;
			cout << "registering to command center runnig at " << this->SCHEDULER_IP << ":" << this->SCHEDULER_PORT << endl;	
			RegReply regReply;
			this->scheduler_client->registerBackend(regReply, regMessage);
			cout << "service stage " << this->SERVICE_NAME << " successfully registered itself at " << this->SERVICE_IP << ":" << this->SERVICE_PORT << endl;
			this->service_list = &regReply.service_list;
			if (this->service_list != NULL)
				cout << "Received " << this->service_list->size() << " downstream service candidates" << endl;
			else
				cout << "Received 0 downstream service candidates" << endl;
			if (this->service_list != NULL && this->service_list->size() != 0) {
				THostPort downstream_hostPort = randomAssignService(this->service_list);
				this->DOWNSTREAM_SERVICE_IP = downstream_hostPort.ip;
				this->DOWNSTREAM_SERVICE_PORT = downstream_hostPort.port;
				this->service_client = tClient.creatIPAClient(this->DOWNSTREAM_SERVICE_IP,
						this->DOWNSTREAM_SERVICE_PORT);
			} else {
				cout << "no downstream service candidates are found by command center"<< endl;
				if (regReply.final_stage) {
					cout << "reaching the final service stage of the workflow" << endl;
				}
			}
			// 2. launch the helper thread
		}

	private:
		double budget;
		string SERVICE_NAME;
		string SCHEDULER_IP;
		int SCHEDULER_PORT;
		string SERVICE_IP;
		int SERVICE_PORT;
		String DOWNSTREAM_SERVICE_IP;
		int DOWNSTREAM_SERVICE_PORT;
		IPAServiceClient *service_client;
		SchedulerServiceClient *scheduler_client;
		vector<THostPort> *service_list; 
		THostPort randomAssignService(vector<THostPort> *service_list) {
			// initialize random seed
			srand(time(NULL));
			// generate random number between 0 and size of the candidate list
			int choice = rand() % service_list->size();
			THostPort hostPort = service_list->at(choice);
			return hostPort;
		}
		string execute_asr(string input) {
			// TODO 1. transform the binary file into a local wav file
			// 2. pass the wav file path to pocketsphinx system call
			struct timeval tp;
			gettimeofday(&tp, NULL);
			long int timestamp = tp.tv_sec * 1000000 + tp.tv_usec;
			ostringstream sstream;
                        sstream << timestamp;
			string wav_path = "query-" + sstream.str() + ".wav";
			ofstream wavfile(wav_path.c_str(), ios::binary);
                        wavfile.write(input.c_str(), input.size());
                        wavfile.close();
			string cmd = "/usr/bin/pocketsphinx_continuous -infile" + wav_path;
			char *cstr = new char[cmd.length() + 1];
			strcpy(cstr, cmd.c_str());
			return exec_cmd(cstr);
		}
		string exec_cmd(char *cmd) {
			FILE* pipe = popen(cmd, "r");
			if (!pipe)
				return "ERROR";
			char buffer[128];
			string result = "";
			while(!feof(pipe)) {
				if(fgets(buffer, 128, pipe) != NULL)
					result += buffer;
    			}
			pclose(pipe);
			return result;
		}
};

int main(int argc, char **argv){
	// initial the transport factory
	// boost::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
	// boost::shared_ptr<TServerTransport> serverTransport(new TServerSocket(9092));
	// initial the protocal factory
	// boost::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());
	// initial the request handler
	// boost::shared_ptr<ImageMatchingServiceHandler> handler(new ImageMatchingServiceHandler());
	// initial the processor
	// boost::shared_ptr<TProcessor> processor(new ImageMatchingServiceProcessor(handler));
	// initial the thread manager and factory
	// boost::shared_ptr<ThreadManager> threadManager = ThreadManager::newSimpleThreadManager(THREAD_WORKS);
	// boost::shared_ptr<PosixThreadFactory> threadFactory = boost::shared_ptr<PosixThreadFactory>(new PosixThreadFactory());
	// threadManager->threadFactory(threadFactory);
	// threadManager->start();
	
	// initial the image matching server
	// TThreadPoolServer server(processor, serverTransport, transportFactory, protocolFactory, threadManager);
	// boost::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());
	SpeechRecognitionServiceHandler *speechRecognition = new SpeechRecognitionServiceHandler();
  	boost::shared_ptr<SpeechRecognitionServiceHandler> handler(speechRecognition);
  	// boost::shared_ptr<ImageMatchingServiceHandler> handler(new ImageMatchingServiceHandler());
	boost::shared_ptr<TProcessor> processor(new IPAServiceProcessor(handler));
  	// boost::shared_ptr<TServerTransport> serverTransport(new TServerSocket(9092));
  	// boost::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());

  	// TNonblockingServer server(processor, serverTransport, transportFactory, protocolFactory);
  	// TNonblockingServer server(processor, protocolFactory, 9092);
	TServers tServer;
	thread thrift_server;
	cout << "Starting the speech recognition service..." << endl;
	// tServer.launchSingleThreadThriftServer(9092, processor);
	tServer.launchSingleThreadThriftServer(9092, processor, thrift_server);
	speechRecognition->initialize();
	// server.serve();
	cout << "Done..." << endl;
	thrift_server.join();
	/*
	while(true) {
	}
	*/
	return 0;
}
