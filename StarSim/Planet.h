#pragma once
#include <string.h>
#include "Body.h"

using std::string;


class Planet : public Body
{
public:
	Planet(const char* objFilePath);
	Planet();
	string GetName() { return m_name; }
	void SetName(string name) { m_name = name; }
private:
	string m_name;
	Body m_parentStar;
};

