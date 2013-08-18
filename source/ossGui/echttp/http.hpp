#include "common.hpp"
#include "respone.hpp"
#include "request.hpp"
#include <boost/regex.hpp>
#include "client.hpp"
#include "iopool.hpp"

namespace echttp
{
	class http
	{
	public:
		request Request;
		typedef	boost::function<void(boost::shared_ptr<respone>)> HttpCallBack;

		http(void)
		{
			this->m_ioServ=&iopool::Instance(4)->io;
		}

		~http(void){}


		boost::shared_ptr<respone> Get(std::string url)
		{
			boost::shared_array<char> data;
			this->Request.BuildBody("GET",url,data,0);

			client client(*m_ioServ);

			boost::shared_ptr<ClientResult> result=client.Send(&this->Request);
			boost::shared_ptr<respone> respone=this->buildRespone(result);

			return respone;

		}

		boost::shared_ptr<respone> Post(std::string url,std::string data)
		{
			char * dataAry=new char [data.length()];
			memset(dataAry,0,data.length());
			memcpy(dataAry,data.c_str(),data.length());

			boost::shared_array<char> postdata(dataAry);
			this->Request.BuildBody("POST",url,postdata,data.length());

			client client(*m_ioServ);

			boost::shared_ptr<ClientResult> result=client.Send(&this->Request);
			boost::shared_ptr<respone> respone=this->buildRespone(result);

			return respone;
		}

		boost::shared_ptr<respone> Get(std::string ip,std::string port,std::string url)
		{
			boost::shared_array<char> data;
			this->Request.BuildProxyBody("GET",ip,port,url,data,0);

			client client(*m_ioServ);

			boost::shared_ptr<ClientResult> result=client.Send(&this->Request);
			boost::shared_ptr<respone> respone=this->buildRespone(result);

			return respone;
		}

		boost::shared_ptr<respone> Post(std::string ip,std::string port,std::string url,std::string data)
		{
			char * dataAry=new char [data.length()];
			memset(dataAry,0,data.length());
			memcpy(dataAry,data.c_str(),data.length());

			boost::shared_array<char> postdata(dataAry);
			this->Request.BuildProxyBody("POST",ip,port,url,postdata,data.length());

			client client(*m_ioServ);

			boost::shared_ptr<ClientResult> result=client.Send(&this->Request);
			boost::shared_ptr<respone> respone=this->buildRespone(result);

			return respone;
		}

		void Delete(std::string url,HttpCallBack cb)
		{
			boost::shared_array<char> data;
			this->Request.BuildBody("DELETE",url,data,0);

			client *httpClient=new client(*m_ioServ);
			httpClient->Send(&this->Request,boost::bind(&http::MessageBack,this,_1,cb,httpClient));
			return ;
		}

		void Put(std::string url,std::string data,HttpCallBack cb)
		{
			char * dataAry=new char [data.length()];
			memset(dataAry,0,data.length());
			memcpy(dataAry,data.c_str(),data.length());

			boost::shared_array<char> postdata(dataAry);
			this->Request.BuildBody("PUT",url,postdata,data.length());

			client *httpClient=new client(*m_ioServ);
			httpClient->Send(&this->Request,boost::bind(&http::MessageBack,this,_1,cb,httpClient));
			return ;
		}

		void PutChar(std::string url,boost::shared_array<char> buf,size_t dataLen,HttpCallBack cb)
		{
			this->Request.BuildBody("PUT",url,buf,dataLen);
			client *httpClient=new client(*m_ioServ);
			httpClient->Send(&this->Request,boost::bind(&http::MessageBack,this,_1,cb,httpClient));
			return ;
		}


		void Get(std::string url,HttpCallBack cb)
		{
			boost::shared_array<char> data;
			this->Request.BuildBody("GET",url,data,0);

			client *httpClient=new client(*m_ioServ);
			httpClient->Send(&this->Request,boost::bind(&http::MessageBack,this,_1,cb,httpClient));
			return ;
		}

		void Post(std::string url,std::string data,HttpCallBack cb)
		{
			char * dataAry=new char [data.length()];
			memset(dataAry,0,data.length());
			memcpy(dataAry,data.c_str(),data.length());

			boost::shared_array<char> postdata(dataAry);
			this->Request.BuildBody("POST",url,postdata,data.length());

			client *httpClient=new client(*m_ioServ);
			httpClient->Send(&this->Request,boost::bind(&http::MessageBack,this,_1,cb,httpClient));
			return ;
		}

		void Get(std::string ip,std::string port,std::string	url,HttpCallBack cb)
		{
			boost::shared_array<char> data;
			this->Request.BuildProxyBody("GET",ip,port,url,data,0);

			client *httpClient=new client(*m_ioServ);
			httpClient->Send(&this->Request,boost::bind(&http::MessageBack,this,_1,cb,httpClient));
			return ;
		}

		void Post(std::string ip,std::string port,std::string url,std::string data,HttpCallBack cb)
		{
			char * dataAry=new char [data.length()];
			memset(dataAry,0,data.length());
			memcpy(dataAry,data.c_str(),data.length());

			boost::shared_array<char> postdata(dataAry);
			this->Request.BuildProxyBody("POST",ip,port,url,postdata,data.length());

			client *httpClient=new client(*m_ioServ);
			httpClient->Send(&this->Request,boost::bind(&http::MessageBack,this,_1,cb,httpClient));
			return ;
		}

		void MessageBack(boost::shared_ptr<ClientResult> result,HttpCallBack cb,client *client)
		{
			boost::shared_ptr<respone> respone=this->buildRespone(result);

			if(cb!=NULL)
			{
				cb(respone);
			}
			if(client!=NULL)
			{
				delete client;
				client=NULL;
			}
		}

		

	private:
		boost::asio::io_service *m_ioServ;

		void BuildHeader(boost::shared_ptr<respone> respone,std::string header)
		{
			if(header.find("HTTP")!=std::string::npos)
			{
				std::string h=header.substr(header.find(" ")+1);
				h=h.substr(0,h.find(" "));
				respone->statusCode=convert<int,std::string>(h);

				boost::smatch result;
				std::string regtxt("\\b(\\w+?): (.*?)\r\n");
				boost::regex rx(regtxt);

				std::string::const_iterator it=header.begin();
				std::string::const_iterator end=header.end();

				while (regex_search(it,end,result,rx))
				{
					std::string key=result[1];
					std::string value=result[2];
					respone->headerMap[key]=value;
					it=result[0].second;
				}
			}else
			{
				respone->statusCode=-1;
			}
		}

		void BuildCookie(std::string header)
		{
			boost::smatch result;
			std::string regtxt("Set-Cooki.*? (.*?)=(.*?);");
			boost::regex rx(regtxt);

			std::string::const_iterator it=header.begin();
			std::string::const_iterator end=header.end();

			while (regex_search(it,end,result,rx))
			{
				std::string cookie_key=result[1];
				std::string cookie_value=result[2];

				if (Request.m_cookies.find(cookie_key)==std::string::npos)
				{
					Request.m_cookies+=cookie_key+"="+cookie_value+"; ";
				}
				else
				{
					std::string reg="("+cookie_key+")=(.*?);";
					boost::regex regrep(reg,    boost::regex::icase|boost::regex::perl);
					Request.m_cookies=boost::regex_replace(Request.m_cookies,regrep,"$1="+cookie_value+";");
				}

				it=result[0].second;
			}

		}

		boost::shared_ptr<respone> buildRespone(boost::shared_ptr<ClientResult> result)
		{
			boost::shared_ptr<respone> httpRespone(new respone);
			httpRespone->errMsg=result->errMsg;
			httpRespone->errorCode=result->errorCode;
			httpRespone->header=result->header;
			httpRespone->body=result->msg;
			httpRespone->len=result->len;

			if(result->errorCode==0 && result->header!=""){
				this->BuildCookie(result->header);
				this->BuildHeader(httpRespone,result->header);
			}
			return httpRespone;
		}

	};


}
