#pragma once
#include "../common.hpp"

namespace echttp
{

class header_option
{
public:
	// ����option_item����.
	typedef std::pair<std::string, std::string> option_item;
	// ����option_item_list����.
	typedef std::vector<option_item> option_item_list;
	// for boost::assign::insert
	typedef option_item value_type;
public:
	header_option() {}
	~header_option() {}

public:

	// ����������������Ӧ��:
	// http_stream s;
	// s.request_options(request_opts()("cookie","XXXXXX"));
	header_option& operator()(const std::string& key, const std::string& val)
	{
		insert(key, val);
		return *this;
	}

	// ���ѡ��, ��key/value��ʽ���.
	void insert(const std::string& key, const std::string& val)
	{
		m_opts.push_back(option_item(key, val));
	}

	// ���ѡ��� std::part ��ʽ.
	void insert(value_type& item)
	{
		m_opts.push_back(item);
	}

	// ɾ��ѡ��.
	header_option& remove(const std::string& key)
	{
		for (option_item_list::iterator i = m_opts.begin(); i != m_opts.end(); i++)
		{
			if (i->first == key)
			{
				m_opts.erase(i);
				return *this;
			}
		}
		return *this;
	}

	// ����ָ��key��value.
	bool find(const std::string& key, std::string& val) const
	{
		std::string s = key;
		boost::to_lower(s);
		for (option_item_list::const_iterator f = m_opts.begin(); f != m_opts.end(); f++)
		{
			std::string temp = f->first;
			boost::to_lower(temp);
			if (temp == s)
			{
				val = f->second;
				return true;
			}
		}
		return false;
	}

	// ����ָ���� key �� value. û�ҵ����� ""�������Ǹ�͵���İ���.
	std::string find(const std::string& key) const
	{
		std::string v;
		find(key,v);
		return v;
	}

	// �õ�Header�ַ���.
	std::string header_string() const
	{
		std::string str;
		for (option_item_list::const_iterator f = m_opts.begin(); f != m_opts.end(); f++)
		{
			str += (f->first + ": " + f->second + "\r\n");
		}
		return str;
	}

	// ���.
	void clear()
	{
		m_opts.clear();
	}

	// ��������option.
	option_item_list& option_all()
	{
		return m_opts;
	}

	// ���ص�ǰoption����.
	int size() const
	{
		return m_opts.size();
	}

protected:
	option_item_list m_opts;
};

}