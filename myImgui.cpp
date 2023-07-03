#include "stdafx.h"

void MyImguiData::SetMinMax(const float& value)
{	
	_min = -fabs(value);
	_max = fabs(value);
}

void MyImguiData::SetMinMax(const float& min, const float& max)
{
	_min = min;
	_max = max;
}

bool MyImguiData::GetMyFlag(const std::string& name)
{
	return MyImgui::flags[name];
}

void MyImguiData::SetMyFlag(const std::string& name, const bool& flag)
{
	MyImgui::flags[name] = flag;
}

void MyImguiData::DragFloatParameter(const std::string& name)
{
	if (ImGui::TreeNode(name.c_str())) {
		if(_eAxis.x)
			ImGui::DragFloat(_label.x.c_str(), &_parameter.x, 0.05f, _min,_max);
		if(_eAxis.y)
			ImGui::DragFloat(_label.y.c_str(), &_parameter.y, 0.05f, _min,_max);
		if(_eAxis.z)
			ImGui::DragFloat(_label.z.c_str(), &_parameter.z, 0.05f, _min,_max);
		if(_eAxis.w)
			ImGui::DragFloat(_label.w.c_str(), &_parameter.w, 0.05f, _min,_max);
		ImGui::TreePop();
	}
}

void MyImguiData::DragFloatParameter2(const std::string& name)
{
	if (ImGui::TreeNode(name.c_str())) 
	{
		ImGui::DragFloat(_label2.x.c_str(), &_parameter2.x, 0.05f, _min, _max);
		ImGui::DragFloat(_label2.y.c_str(), &_parameter2.y, 0.05f, _min, _max);
		ImGui::DragFloat(_label2.z.c_str(), &_parameter2.z, 0.05f, _min, _max);
		ImGui::DragFloat(_label2.w.c_str(), &_parameter2.w, 0.05f, _min, _max);
		ImGui::TreePop();
	}
}

void ParameterLabel::ChangeLavel(const LABEL& label, const std::string& name)
{
	switch (label)
	{
	case ParameterLabel::LABEL_X:
		x = name;
		break;
	case ParameterLabel::LABEL_Y:
		y = name;
		break;
	case ParameterLabel::LABEL_Z:
		z = name;
		break;
	case ParameterLabel::LABEL_W:
		w = name;
		break;
	default:
		break;
	}
}

void ParameterLabel::ChangeLabel(const std::string& x_name, const std::string& y_name, const std::string& z_name, const std::string& w_name)
{
	x = x_name;
	y = y_name;
	z = z_name;
	w = w_name;
}
