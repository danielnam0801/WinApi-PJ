#include "pch.h"
#include "PathMgr.h"
#include "Core.h"
void PathMgr::Init()
{
	GetCurrentDirectory(255,m_strResPath);
	wcscat_s(m_strResPath, 255, L"\\Res\\");
	//SetWindowText(Core::GetInst()->GetHwnd(),m_strResPath);
}

std::string PathMgr::ReplaceAll(std::string message, std::string pattern, std::string replace)
{
	std::string result = message;
	std::string::size_type pos = 0;
	std::string::size_type offset = 0;
	while ((pos = result.find(pattern, offset)) != std::string::npos) 
	{
		result.replace(result.begin() + pos, result.begin() + pos + pattern.size(), replace);        offset = pos + replace.size();
		offset = pos + replace.size();
	}
	return result;
}
