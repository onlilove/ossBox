#pragma once
#include <sstream>
#include <fstream>
#include <openssl\md5.h>
#include <openssl\sha.h>
#include <openssl\hmac.h>
#include <boost\algorithm\string.hpp>
#include <boost/date_time/posix_time/posix_time.hpp> 
#include <boost/date_time/local_time_adjustor.hpp> 
#include <boost/date_time/c_local_time_adjustor.hpp> 
#include <boost/locale/encoding.hpp>

using namespace std;

namespace weblib
{

	template <class target,class source>
	target convert(const source &t)
	{
		std::stringstream stream;

		stream<<t;//�����д�ֵ

		target result;//����洢ת�����

		stream>>result;//��result��д��ֵ

		return result;
	};

	
	//����ת��
	std::string	UrlEncode(const std::string& szToEncode);
	std::string	UrlDecode(const std::string& szToDecode);
	std::string	Utf8Encode(const std::string& szToEncode);
        std::string	Utf8Decode(const std::string& szToDecode);
	std::string	base64Encode(const unsigned char * Data,int DataByte);
	std::string	string_md5(std::string str);
	 std::string	char_md5(char* data,size_t len);

	//�ַ�������
	std::string substr(const std::string &str,std::string sStart,std::string sEnd);
	std::string  replace_all(std::string&   str,const   std::string&   old_value,const   std::string&   new_value);

	//�ļ�����
        bool		isFile(std::string filePath);
        size_t		fileToChar(std::string filePath , char* &buffer,long pos=0,long size=0);
        size_t		fileLen(std::string filePath);
        const std::vector<std::string>& DirFiles(const std::string& rootPath,std::vector<std::string>& container=*(new std::vector<std::string>()));
	std::vector<std::string> explode(std::string strs,std::string delimiter);
	
	//����
	std::string	GetCurrentTimeGMT();//��õ�ǰ��GMTʱ���
	std::string	ossAuth(std::string key,std::string data);//����oss��֤��
	std::string	GetFormInputValue(std::string strs,std::string name);

}