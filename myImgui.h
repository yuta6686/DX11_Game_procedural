#pragma once
struct ParameterLabel 
{
	enum LABEL {
		LABEL_X,
		LABEL_Y,
		LABEL_Z,
		LABEL_W,
	};

	std::string x = "parameter.x";
	std::string y = "parameter.y";
	std::string z = "parameter.z";
	std::string w = "parameter.w";

	void ChangeLavel(const LABEL& label, const std::string& name);

	void ChangeLabel(const std::string& x_name="parameter.x",
		const std::string& y_name="parameter.y",
		const std::string& z_name="parameter.z",
		const std::string& w_name="parameter.w");
};
struct ParameterEnableAxis
{
	bool x = true;
	bool y = true;
	bool z = true;
	bool w = true;
};
class MyImguiData 
{
public:	
	float _min = 0.0f;
	float _max = 1.0f;

	XMFLOAT4 _parameter, _parameter2;
	ParameterLabel _label,_label2;
	ParameterEnableAxis _eAxis;
public:
	void SetMinMax(const float& value);
	void SetMinMax(const float& min, const float& max);
	bool GetMyFlag(const std::string& name);
	void SetMyFlag(const std::string& name,const bool& flag = true);
	void DragFloatParameter(const std::string& name);
	void DragFloatParameter2(const std::string& name);
};

class MyImgui
{
public:
	inline static std::map<std::string, bool> flags;	
	inline static void InitFlags()
	{
		flags["Water"] = true;
		flags["Field"] = true;
	}

	static void ImguiPosition(XMFLOAT3* position, float min = -100, float max = 100);
	static void ImguiScale( XMFLOAT3* scale, float min = -100, float max = 100);
};
