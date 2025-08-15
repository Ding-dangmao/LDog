#include"tool.h"



system_clock::time_point Clock::systemClock()
{
	return system_clock::now();
}

steady_clock::time_point Clock::steadyClock()
{
	return steady_clock::now();
}

high_resolution_clock::time_point Clock::highResolutionClock()
{
	return high_resolution_clock::now();
}

/*
* 获取时间格式为: 星期 月 日 时分秒 年
*/
char* Clock::time() {
	const time_t t_t = system_clock::to_time_t(Clock::systemClock());
	return std::ctime(&t_t);
}


void ToolP::splitStr(char* str, const char* delim, std::vector<std::string>& vec) {
	char* tp;
	tp = strtok(str, delim);
	while (tp) {
		vec.push_back(tp);
		tp = strtok(str, delim);
	}
}


bool ToolP::createFile(const std::string& file_name)
{
	std::ofstream ofs(file_name, std::ios::trunc);
	if (ofs.is_open()) {
		ofs.close();
		return true;
	}
	return false;
}

bool ToolP::SaveStringToFile(const std::string& file_name, const std::string& data, std::ios_base::openmode mode)
{
	std::ofstream ofs(file_name, mode);
	if (!ofs.is_open()) {
		createFile(file_name);
	}
	std::ofstream offs(file_name, mode);
	if (offs.is_open()) {
		offs << data;
		offs.close();
		return true;
	}
	return false;
}

bool ToolP::appendDataFile(const std::initializer_list<std::string> file_list)
{
	std::ofstream ofs(*file_list.begin(), std::ios::app | std::ios::binary);
	if (!ofs.is_open()) {
		return false;
	}
	for (auto it = file_list.begin() + 1; it != file_list.end(); it++) {
		std::ifstream ifs(*it, std::ios::in | std::ios::binary);
		if (!ifs.is_open()) {
			return false;
		}
		while (ifs) {
			ifs.read(buffer, IMAGE_CHUNK_SIZE);
			std::streamsize bytesRead = ifs.gcount();
			if (bytesRead > 0) {
				ofs.write(buffer, bytesRead);
			}
		}
		ifs.close();
	}
	ofs.close();
	return true;
}

int ToolP::splitDataFile(const std::string& file_name, const std::string& save_path)
{
	size_t chunk_{};
	std::ifstream ifs(file_name, std::ios::in | std::ios::binary);
	if (!ifs.is_open()) {
		std::cerr << "Failed to open file: " << file_name << std::endl;
		return -1;
	}
	while (ifs) {
		ifs.read(buffer, IMAGE_CHUNK_SIZE);
		std::streamsize bytesRead = ifs.gcount();
		if (bytesRead > 0) {
			std::string chunk_file_name = save_path + "/" + "file_name" + ".part" + std::to_string(++chunk_);
			std::ofstream ofs(chunk_file_name, std::ios::out | std::ios::binary);
			if (!ofs.is_open()) {
				ifs.close();
				std::cerr << "Failed to create chunk file: " << chunk_file_name << std::endl;
				return -1;
			}
			ofs.write(buffer, bytesRead);
			ofs.close();
		}
	}
	ifs.close();
	return chunk_;
}

