#include "DataDogStatsD.h"

using namespace std;

/// <summary>Initialise the DogStatsD with the API and app key, defaulting to host localhost and port 8125</summary>
/// <param name="api_key">Your API Key</param>
/// <param name="app_key">Your app key</param>

DataDogStatsD::DataDogStatsD()
{
	this->host = "127.0.0.1";
	this->port = 8125;
}

DataDogStatsD::DataDogStatsD(std::string host, unsigned int port)
{
	this->host = host;
	this->port = port;
}

DataDogStatsD::DataDogStatsD(string api_key, string app_key)
{
this->api_key = api_key;
this->app_key = app_key;
this->host = "127.0.0.1";
this->port = 8125;
}

/// <summary>Initialise the DogStatsD with the API and app key, customised hostname and default port of 8125</summary>
/// <param name="api_key">Your API Key</param>
/// <param name="app_key">Your app key</param>
/// <param name="host">The hostname to send to DogStatsD
DataDogStatsD::DataDogStatsD(string api_key, string app_key, string host)
{
	this->api_key = api_key;
	this->app_key = app_key;
	this->host = host;
	this->port = 8125;
}

/// <summary>Initialise the DogStatsD with the API and app key, customised port number defaults to host localhost</summary>
/// <param name="api_key">Your API Key</param>
/// <param name="app_key">Your app key</param>
/// <param name="port">The port number to send to DogStatsD</param>
DataDogStatsD::DataDogStatsD(string api_key, string app_key, unsigned int port)
{
	this->api_key = api_key;
	this->app_key = app_key;
	this->host = "127.0.0.1";
	this->port = port;
}

/// <summary>Initialise the DogStatsD with the API and app key, with customised hostname and port</summary>
/// <param name="api_key">Your API Key</param>
/// <param name="app_key">Your app key</param>
/// <param name="host">Hostname to send to DogStatsD</param>
/// <param name="port">Port number to send to DogStatsD</param>
DataDogStatsD::DataDogStatsD(string api_key, string app_key, string host, unsigned int port)
{
	this->api_key = api_key;
	this->app_key = app_key;
	this->host = host;
	this->port = port;
}

void DataDogStatsD::increment(std::string stats)
{
	std::vector<std::string> statsArray;
	statsArray.push_back(stats);
	this->updateStats(statsArray, 1, 1.0, "");
}

void DataDogStatsD::increment(std::string stats, std::string tags)
{
	std::vector<std::string> statsArray;
	statsArray.push_back(stats);
	this->updateStats(statsArray, 1, 1.0, tags);
}

void DataDogStatsD::increment(std::vector<std::string> stats)
{
	this->updateStats(stats, 1, 1.0, "");
}

void DataDogStatsD::increment(std::vector<std::string> stats, std::string tags)
{
	this->updateStats(stats, 1, 1.0, tags);
}

void DataDogStatsD::decrement(std::string stats)
{
	std::vector<std::string> statsArray;
	statsArray.push_back(stats);
	this->updateStats(statsArray, -1, 1.0, "");
}

void DataDogStatsD::decrement(std::string stats, std::string tags)
{
	std::vector<std::string> statsArray;
	statsArray.push_back(stats);
	this->updateStats(statsArray, -1, 1.0, tags);
}

void DataDogStatsD::decrement(std::vector<std::string> stats)
{
	this->updateStats(stats, -1, 1.0, "");
}

void DataDogStatsD::decrement(std::vector<std::string> stats, string tags)
{
	this->updateStats(stats, -1, 1.0, tags);
}

void DataDogStatsD::timing(std::string stats, float timeInSeconds)
{
	stringstream valueStream;
	valueStream << (timeInSeconds) << "|ms";
	std::map<std::string, std::string> data;
	data[stats] = valueStream.str();
	this->send(data, 1.0);
}

void DataDogStatsD::timing(std::string stats, float timeInSeconds, std::string tags)
{
	stringstream valueStream;
	valueStream << (timeInSeconds) << "|ms";
	std::map<std::string, std::string> data;
	data[stats] = valueStream.str();
	this->send(data, 1.0, tags);
}



void DataDogStatsD::gauge(std::string stats, float value)
{
	stringstream valueStream;
	valueStream << (value) << "|g";

	std::map<std::string, std::string> data;
	data[stats] = valueStream.str();
	this->send(data, 1.0);
}

void DataDogStatsD::gauge(std::string stats, float value, std::string tags)
{
	stringstream valueStream;
	valueStream << (value) << "|g";

	std::map<std::string, std::string> data;
	data[stats] = valueStream.str();
	this->send(data, 1.0, tags);
}

void DataDogStatsD::histogram(std::string stats, float value)
{
	stringstream valueStream;
	valueStream << (value) << "|h";

	std::map<std::string, std::string> data;
	data[stats] = valueStream.str();
	this->send(data, 1.0);
}

void DataDogStatsD::histogram(std::string stats, float value, std::string tags)
{
	stringstream valueStream;
	valueStream << (value) << "|h";

	std::map<std::string, std::string> data;
	data[stats] = valueStream.str();
	this->send(data, 1.0, tags);
}

void DataDogStatsD::set(std::string stats, float value)
{
	stringstream valueStream;
	valueStream << (value) << "|s";

	std::map<std::string, std::string> data;
	data[stats] = valueStream.str();
	this->send(data, 1.0);
}

void DataDogStatsD::set(std::string stats, float value, std::string tags)
{
	stringstream valueStream;
	valueStream << (value) << "|s";

	std::map<std::string, std::string> data;
	data[stats] = valueStream.str();
	this->send(data, 1.0, tags);
}

void DataDogStatsD::updateStats(std::vector<std::string> stats, int delta, float sampleRate, string tags)
{
	std::map<string, string> data;

	//Loop over the stats and create the multi dimension array of stat => value
	for (std::vector<std::string>::iterator it = stats.begin(); it != stats.end(); ++it)
	{
		data[*it] = "1|c";
	}

	this->send(data, sampleRate, tags);

}

void DataDogStatsD::send(std::map<string, string> data, float sampleRate, string tags)
{
	if (data.size() == 0)
	{
		return;
	}

	std::map<string, string> sampledData;
	if (sampleRate < 1)
	{
		for (std::map<string, string>::iterator it = data.begin(); it != data.end(); ++it)
		{
			if ((Helpers::rand() / Helpers::rand_mx()) <= sampleRate)
			{
				stringstream valueStream;
				valueStream << it->second << "|@" << sampleRate;
				string value = valueStream.str();
				sampledData[it->first] = value;
			}
		}
	}
	else
	{
		sampledData = data;
	}

	if (sampledData.size() == 0)
	{
		return;
	}

	for (std::map<string, string>::iterator it = sampledData.begin(); it != sampledData.end(); ++it)
	{
		stringstream output;

		output << it->first << ":" << it->second << tags;
		string udp_message = output.str();
		this->flush(udp_message);
	}
}

void DataDogStatsD::event(DDEvent& ddEvent)
{
	//cout << ddEvent.returnDDEventUDPString() << endl;
	string udp_message = ddEvent.returnDDEventUDPString();
	cout << udp_message << endl;
	this->flush(udp_message);
}

CURL * DataDogStatsD::initCurl(DDEvent ddEvent, string *response, struct curl_slist *list, const char *jsonString)
{
	CURL *curl = NULL;

	curl = curl_easy_init();
	if (curl == NULL)
	{
		cout << "Failed to initialise curl" << endl;
		return NULL;
	}

	list = curl_slist_append(list, "Content-Type: application/json");

	stringstream dd_url_stream;
	dd_url_stream << "https://app.datadoghq.com/api/v1/events?api_key=" << this->api_key << "&application_key=" << this->app_key;
	string dd_url = dd_url_stream.str();


	curl_easy_setopt(curl, CURLOPT_URL, dd_url.c_str());
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 1);
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &DataDogStatsD::curlResponseWriteCallback);
	curl_easy_setopt(curl, CURLOPT_HEADER, 0);
	curl_easy_setopt(curl, CURLOPT_POST, 1);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (unsigned)strlen(jsonString));
	curl_easy_setopt(curl, CURLOPT_COPYPOSTFIELDS, jsonString);

	return curl;
}

bool DataDogStatsD::event(DDEvent ddEvent, bool nonBlockingMode, void(*eventCallback)(bool result, string error))
{
	//Send the request blocking the current thread until a response is returned - don't call this too often or your app may lock
	if (!nonBlockingMode)
	{
		string response;
		struct curl_slist *list = NULL;
		string jsonString;
		ddEvent.getDDEventAsJSONString(&jsonString);
		CURL *curl = this->initCurl(ddEvent, &response, list, jsonString.c_str());
		if (curl == NULL)
		{
			if (eventCallback != nullptr)
			{
				eventCallback(false, "Failed to initialise curl");
			}
			return false;
		}

		CURLcode res = curl_easy_perform(curl);
		if (res != CURLE_OK)
		{
			string error = curl_easy_strerror(res);
			if (eventCallback != nullptr)
			{
				eventCallback(false, error);
			}
			curl_slist_free_all(list);
			curl_easy_cleanup(curl);
			
			return false;
		}
		else
		{
			long response_code;
			curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
			curl_slist_free_all(list);
			curl_easy_cleanup(curl);
			if (eventCallback != nullptr)
			{
				if (response_code == 200 || response_code == 201 || response_code == 202)
				{
					eventCallback(true, "");
					return true;
				}
				else
				{
					eventCallback(false, response);
					return false;
				}
			}
			else
			{
				if (response_code == 200 || response_code == 201 || response_code == 202)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
	}
	else
	{
		//Make sure we only have 1 thread running at a time, if the thread for the HTTP event is already running return an error
		if (!httpEventThreadStarted)
		{
			//Return an error if we've got a null eventCallback function as otherwise, how you supposed to know if it failed to post the event
			//If you're not worried whether the event post was not successful call DataDogStatsD::event(DDEvent) to send over UDP throught the agent
			if (eventCallback == nullptr)
			{
				cout << "Eventcallback cannot be null if sending event in non blocking mode" << endl;
				return false;
			}
			else
			{
				httpEventThreadStarted = true;
				this->http_event_thread = new thread(&DataDogStatsD::sendDDEventinthread, this, ddEvent, eventCallback);
				return true;
			}
		}
		else
		{
			if (eventCallback != nullptr)
			{
				eventCallback(false, "HTTP Event thread is already sending an event, wait until the current event has been finished");
				return false;
			}
			else
			{
				return false;
			}
		}
	}
}

void DataDogStatsD::sendDDEventinthread(DDEvent ddEvent, void(*eventCallback)(bool result, string error))
{
	string response;
	struct curl_slist *list = NULL;
	string jsonString;
	ddEvent.getDDEventAsJSONString(&jsonString);

	CURL *curl = this->initCurl(ddEvent, &response, list, jsonString.c_str());
	if (curl == NULL)
	{
		eventCallback(false, "Failed to initialsie curl");
		httpEventThreadStarted = false;
		return;
	}

	CURLcode res = curl_easy_perform(curl);
	if (res != CURLE_OK)
	{
		string error = curl_easy_strerror(res);
		eventCallback(false, error);
		//cout << "Failed to perform curl: " << error << endl;
		curl_slist_free_all(list);
		curl_easy_cleanup(curl);
		httpEventThreadStarted = false;
		return;
	}
	else
	{
		long response_code;
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
		if (response_code == 200 || response_code == 201 || response_code == 202)
		{
			eventCallback(true, "");
		}
		else
		{
			eventCallback(false, response);
		}
		curl_slist_free_all(list);
		curl_easy_cleanup(curl);
		httpEventThreadStarted = false;
		return;
	}
}

size_t DataDogStatsD::curlResponseWriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

void DataDogStatsD::flush(string& udp_message)
{
#ifndef _WIN32

	int udp_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	/*struct sockaddr_in sin;

	sin.sin_family = AF_INET;
	inet_pton(AF_INET, this->host.c_str(), &sin.sin_addr);
//	sin.sin_addr.s_addr = htonl(this->host.c_str());
	sin.sin_port = htons(this->port);*/

	struct sockaddr_in serv_addr;
	bzero((char *)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	//serv_addr.sin_addr.s_addr = htonl(this->host.c_str());
	inet_pton(AF_INET, this->host.c_str(), &serv_addr.sin_addr);
	serv_addr.sin_port = htons(this->port);

	/*if (!bind(udp_socket, (struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		cout << "Failed to bind UDP port" << endl;
	}*/

	connect(udp_socket, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

	write(udp_socket, udp_message.c_str(), udp_message.length());
	

	close(udp_socket);
#else
	cout << "Sending " << udp_message << endl;
#endif
}

string DataDogStatsD::returnSerializedTagsString(std::string tags)
{
	stringstream valueStream;
	valueStream << "|#" << tags;
	return valueStream.str();
}

string DataDogStatsD::returnSerializedTagsString(std::vector<std::string> tags)
{
	if (tags.size() == 0)
	{
		return string("");
	}

	stringstream valueStream;
	valueStream << "|#";
	int i = 0;
	for (std::vector<string>::iterator it = tags.begin(); it != tags.end(); ++it)
	{
		valueStream << i << ":" << *it << ",";
		i++;
	}
	string value = valueStream.str();
	value.pop_back();
	return value;
}
	
string DataDogStatsD::returnSerializedTagsString(std::map<std::string, std::string> tags)
{
	stringstream valueStream;
	valueStream << "|#";
	int i = 0;
	for (std::map<string, string>::iterator it = tags.begin(); it != tags.end(); ++it)
	{
		valueStream << it->first << ":" << it->second << ",";
		i++;
	}
	string value =  valueStream.str();
	value.pop_back();
	return value;
}

long DataDogStatsD::getTimeInMicroSeconds()
{
#ifndef _WIN32
	struct timeval time;
	gettimeofday(&time, NULL);
	long microsec = ((unsigned long long)time.tv_sec * 1000000) + time.tv_usec;
	return microsec;
#else
	return 0;
#endif
}

DataDogStatsD::~DataDogStatsD()
{
	if (this->http_event_thread != NULL)
	{
		this->http_event_thread->join();

		delete this->http_event_thread;
		this->http_event_thread = NULL;
	}
}