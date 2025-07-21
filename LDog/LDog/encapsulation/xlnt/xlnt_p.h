#ifndef XLNT_P_H
#define XLNT_P_H

#include<iostream>


#include<memory>
#include<vector>

#ifdef Windows
#include"xlnt/xlnt.hpp"

/**
* 
* 
* xlnt��һ����װ������
* һ��XlntP�����һ��Excell�ļ�,
* ���еķǶ�ȡ�����Ĳ��������Ϊ�䱾������Excell�ļ�
* ��ȡ��������Ǳ���,Ϊ����Excell�ļ�
* 
*/
class XlntP {
public: 
	XlntP();
	inline static std::shared_ptr<XlntP> createShared() {
		return std::make_shared<XlntP>();
	}
private:
	void writeLineByLine(const std::vector<std::vector<std::string>>& data);
	std::vector<std::vector<std::string>> readLineByLine();
	static std::vector<std::vector<std::string>> readLineByLine(const xlnt::worksheet& ws);

	bool isSheetExist(const std::string& sheet_name);
	static bool isSheetExist(const xlnt::workbook& wb, const std::string title);
	xlnt::worksheet sheet_by_title(const std::string& title);
public:
	void createSheet(const std::string& sheet_name);
	bool writeVecToFile(const std::vector<std::vector<std::string>>& data,const std::string& sheet_name);
	std::vector<std::vector<std::string>> readFileToVec(const std::string& excell_name, const std::string& sheet_name);
	//std::vector<std::vector<std::string>> readFileToVec(const std::string& title);
	bool generateFile(std::string excell_name);
	
private:
	xlnt::workbook wb_;
	xlnt::worksheet ws_;
};

#endif

#endif //XLNT_P_H