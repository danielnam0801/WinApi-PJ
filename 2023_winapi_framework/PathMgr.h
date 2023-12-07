#pragma once
#include <string>
class PathMgr
{
	SINGLE(PathMgr);
public:
	void Init();
	std::string ReplaceAll(std::string message, std::string pattern, std::string replace);
	std::string GetPathWithOutRes(std::string path)
	{
		std::string str = path;
		str.erase(str.begin(), std::find(str.begin(), str.end(), '/') + 1);
		return str;
	}
	const wchar_t* GetResPath() const 
	{ return m_strResPath; }
private:
	wchar_t m_strResPath[255];
};

