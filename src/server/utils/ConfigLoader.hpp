#pragma once

#include <string>
#include <exception>
#include <yaml-cpp/yaml.h>

// TODO: proper method + add type checks
static const std::vector<std::string> MANDATORY_VALUES{
	"port"
};


class ConfigLoader : public YAML::Node
{
public:
	ConfigLoader(const std::string &filePath)
		: YAML::Node(YAML::LoadFile(filePath))
	{
		for (auto &mandatoryValue : MANDATORY_VALUES) {
			if (!(*this)[mandatoryValue])
				throw std::runtime_error("No value specified for \"" + mandatoryValue + "\" in config file!");
		}
	}
	~ConfigLoader() = default;

	inline std::string getFilePath() { return _filePath; }

private:
	const std::string _filePath;
};

