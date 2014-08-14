#include "Generator.h"
#include <string>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <sstream>
#include <iostream>
#include <stdio.h> 
#include <curl/curl.h> 
#include <rapidjson/document.h>
#include <rapidjson/writer.h> 
#include <rapidjson/stringbuffer.h> 
#include <iostream> 
#include <atlstr.h> 
#include <string.h>

//using namespace rapidjson;
static std::string *DownloadedResponse;

template<class Element, class Sequence> LSystem<Element, Sequence>::LSystem()
{
}

template<class Element, class Sequence> LSystem<Element, Sequence>::~LSystem()
{
	for(int i = 0; i < rules.size(); i++)
	{
		delete rules[i];
	}
}

template<class Element, class Sequence> void LSystem<Element, Sequence>::addRule(Element hd, Sequence tl)
{
	rules.push_back(new LSystemRule(hd, tl));
}

template<class Element, class Sequence> Sequence &LSystem<Element, Sequence>::replace(Element &hd)
{
	static Sequence seq;
	seq.clear();
	for(int i = 0; i < rules.size(); i++)
	{
		if(rules[i]->isMatch(hd))
			return rules[i]->getTail();
	}
	seq.push_back(hd);
	return seq;
}

template<class Element, class Sequence> void LSystem<Element, Sequence>::iterate()
{
	Sequence newstate;
	for(int i = 0; i < state.size(); i++)
	{
		Sequence &replacement = replace(state[i]);
		for(int e = 0; e < replacement.size(); e++)
		{
			newstate.push_back(replacement[e]);
		}
	}
	state = newstate;
}

void initLSystem()
{
	std::string json = DownloadJSON("http://api.reddit.com");
	rapidjson::Document d; 
	d.Parse(json.c_str()); 
	printf("%s\n", d["likes"].GetString()); 
	/*CURL *curl; 
	CURLcode res;
	char * readBuffer("test"); 
	curl = curl_easy_init();
	
	if(curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, "http://api.reddit.com");
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // Perform the request, res will get the return code 
		res = curl_easy_perform(curl); // Check for errors 
		if(res != CURLE_OK){
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		}

		//size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata);
		//CURLcode curl_easy_setopt(CURL *handle, CURLOPT_WRITEFUNCTION, write_callback); 
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, readBuffer); // always cleanup curl_easy_cleanup(curl); 
	}
	
	std::cout<<res;
	
	//CString str(curl_easy_strerror(res));
	
	rapidjson::Document d; 
	
	d.Parse(readBuffer); 
	printf("%s\n", d["likes"].GetString()); 
	
	//system("pause");
	*/
	
	
	/*
	const char* json = "{\"project\":\"rapidjson\",\"stars\":10}";
    Document d;
    d.Parse(json);

    // 2. Modify it by DOM.
    Value& s = d["stars"];
    s.SetInt(s.GetInt() + 1);

    // 3. Stringify the DOM
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    d.Accept(writer);

    // Output {"project":"rapidjson","stars":11}
    std::cout << buffer.GetString() << std::endl;
	/*

	/*
	LSystem<char, string> test;
	std::vector<string> initString;
	test.setState("<html><head></head><body><p1>This is a paragraph</p1></body></html>");
	test.addRule('a', "aba");
	test.addRule('b', "bc");
	test.addRule('c', "aaa");
	
	int numIterations = 3;

	for(int i = 0; i<numIterations + 1; i++)
	{
		printf("state%i:", i);
		printf(" %s\n", test.getState().c_str());
		test.iterate();
	}
	*/
}



std::string DownloadJSON(std::string URL)
{   
    CURL *curl;
    CURLcode res;
    struct curl_slist *headers=NULL; // init to NULL is important 
    std::ostringstream oss;
    curl_slist_append(headers, "Accept: application/json");  
    curl_slist_append( headers, "Content-Type: application/json");
    curl_slist_append( headers, "charsets: utf-8"); 
    curl = curl_easy_init();

    if (curl) 
    {
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPGET,1); 
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); 
        curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,writer);
        res = curl_easy_perform(curl);

        if (CURLE_OK == res) 
        { 
            char *ct;         
            res = curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &ct);
            if((CURLE_OK == res) && ct)
                return *DownloadedResponse;
        }
    }

}

static int writer(char *data, size_t size, size_t nmemb, std::string *buffer_in)
{

    // Is there anything in the buffer?  
    if (buffer_in != NULL)  
    {
        // Append the data to the buffer    
        buffer_in->append(data, size * nmemb);

        // How much did we write?   
        DownloadedResponse = buffer_in;

        return size * nmemb;  
    }

    return 0;

}   

std::string getLSystemString(){
	return("aba");
}