#include "xlnt_p.h"


#ifdef Windows
/*
*
*将文件置空(恢复默认,并删除初始时的sheet
*
*/
XlntP::XlntP(){
	this->wb_ = xlnt::workbook::empty();
	this->ws_ = this->wb_.active_sheet();
	this->wb_.remove_sheet(this->ws_);
}
/*
*
*
*
*/
bool XlntP::generateFile(std::string excell_name) {
	this->wb_.save(excell_name+".xlsx");
	return true;
}
/*
* 
* 
* 
*/
void XlntP::writeLineByLine(const std::vector<std::vector<std::string>>& data) {
	for (int i = 0; i < data.size(); i++) {
		for (int j = 0; j < data.at(i).size();j++) {
			this->ws_
				.cell(xlnt::cell_reference(i + 1, j + 1))
				.value(data.at(i).at(j));
		}
	}
}
/*
*
*
*
*/
std::vector<std::vector<std::string>> XlntP::readLineByLine() {
	std::vector<std::vector<std::string>> data;
	for (auto row : this->ws_) {
		std::vector<std::string> row_data;
		for (auto cell : row) {
			row_data.push_back(cell.to_string());
		}
		data.push_back(row_data);
	}
	return data;
}
/*
*
*
*
*/
std::vector<std::vector<std::string>> XlntP::readLineByLine(const xlnt::worksheet& ws)
{
	std::vector<std::vector<std::string>> data;
	for (const auto& row : ws) {
		std::vector<std::string> row_data;
		for (auto cell : row) {
			row_data.push_back(cell.to_string());
		}
		data.push_back(row_data);
	}
	return data;
}
/*
*
*
*
*/
bool XlntP::isSheetExist(const std::string& title) {
	if (this->wb_.contains(title))
		return true;
	return false;
}
/*
*
*
*
*/
bool XlntP::isSheetExist(const xlnt::workbook& wb, const std::string title)
{
	if (wb.contains(title))
		return true;
	return false;
}
/*
*
*
*
*/
xlnt::worksheet XlntP::sheet_by_title(const std::string& title)
{
	return this->wb_.sheet_by_title(title);
}
/*
*
*
*
*/
void XlntP::createSheet(const std::string& title) {
	this->ws_ = this->wb_.create_sheet();
	this->ws_.title(title);
}
/*
*
*
*
*/
bool XlntP::writeVecToFile(const std::vector<std::vector<std::string>>& data,const std::string& title) {
	if (!isSheetExist(title))
		return false;
	this->ws_ = sheet_by_title(title);
	writeLineByLine(data);
	return true;
}
/**
*
*使用时请指定文件路径
*
*/
std::vector<std::vector<std::string>> XlntP::readFileToVec(const std::string& excell_name, const std::string& title) {
	xlnt::workbook wb;
	//应添加加载默认路径

	//文件是否存在
	try
	{
		wb.load(excell_name+".xlsx");
	}
	catch (const xlnt::exception& e)
	{
		std::cout << "error: " << e.what() << std::endl;
		return std::vector<std::vector<std::string>>{{"file not found"}};
	}
	//sheet是否存在
	if (!isSheetExist(wb, title))
		return std::vector<std::vector<std::string>>{{"sheet not found"}};
	//读取数据
	return readLineByLine(wb.sheet_by_title(title));
}


#endif
