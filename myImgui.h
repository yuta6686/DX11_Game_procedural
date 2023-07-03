#pragma once



class MyImgui
{
public:
	inline static std::map<std::string, bool> flags;
	inline static void InitFlags()
	{
		flags["Water"] = true;
		flags["Field"] = true;
	}
};
