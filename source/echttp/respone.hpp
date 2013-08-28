#pragma once

#include "common.hpp"
#include <map>
#include "detail/header.hpp"

namespace  echttp{

class respone
{
public:
    respone();
    ~respone();

    int         error_code;
	std::string error_msg;//������Ϣ

    int status_code;//http״̬��
    header_option header;//����ͷ��

    size_t length;//�������ݴ�С
	boost::shared_array<char> body;//��������

    std::string save_path;//�����ļ�path���������ļ������ֵΪ�ļ�·��

	bool parse_header(std::string);

    bool save_body(std::vector<char> buffer,size_t length);

    void notify_status(size_t total,size_t now);
    void register_notify_callback();

private:

};

respone::respone()
{
}

respone::~respone()
{
}

bool respone::parse_header(std::string)
{
	return false;
}

	
}