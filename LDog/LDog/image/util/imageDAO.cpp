#include "imageDAO.h"
#include "imageDAO.h"
#include "imageDAO.h"
#include "imageDAO.h"
#include "imageDAO.h"
#include"imageDAO.h"


std::string ImageDAO::serializeImageSHA256(c_ref_string a_sha256, c_ref_string h_sha256, c_ref_string t_sha256)
{
	boost::json::object obj;
	obj["a"] = a_sha256;
	obj["h"] = h_sha256;
	obj["t"] = t_sha256;
	return serialize(obj);
}

bool ImageDAO::insertImage(int user_id, c_ref_string image_key, c_ref_string a_sha256, c_ref_string h_sha256, c_ref_string t_sha256, c_ref_string image_name, c_ref_string image_type, c_ref_string url, signed image_size, signed image_width, signed image_height)
{
	std::string hash_sha256 = this->serializeImageSHA256(a_sha256, h_sha256, t_sha256);
	refreshTime();
	c_ref_string sql_statement = "insert into image (user_id, image_key, hash_sha256, original_name, mime_type, url, file_size, width, height, createtime, updatetime) VALUE(? , ? , ? , ? , ? , ? , ? , ? , ? , ? , ? )";
	this->mysql_->executePre(sql_statement, user_id, image_key, hash_sha256, image_name, image_type, url, image_size, image_width, image_height, this->time_, this->time_);
	return true;
}

bool ImageDAO::insertImageGroup(int user_id, c_ref_string group_name)
{
	refreshTime();
	std::string sql_statement = "insert into image_group (user_id, group_name, createtime, updatetime) value (?,?,?,?)";
	this->mysql_->executePre(sql_statement, user_id, group_name, this->time_, this->time_);
	return true;
}

bool ImageDAO::insertImageAndGroupRelation(int image_id, int group_id)
{
	c_ref_string sql_statement = "insert into image_image_group_relevancy (image_id, image_group_id) value (?,?)";
	this->mysql_->executePre(sql_statement, image_id, group_id);
	return true;
}

bool ImageDAO::isExistGroup(c_ref_string group_name, int user_id)
{
	c_ref_string sql_statement = "select COUNT(*) from image_group where user_id=? and group_name=?";
	MysqlP::guard_ResultSet result_set = this->mysql_->executePreQuery(sql_statement, user_id, group_name);
	if (result_set.get() && result_set.get()->next()) {
		return result_set.get()->getBoolean(1);
	}
	return false;
}

bool ImageDAO::isExistImage(int user_id, c_ref_string a_sha256, c_ref_string h_sha256, c_ref_string t_sha256)
{
	c_ref_string sql_statement = "select COUNT(*) from image where user_id=? AND JSON_UNQUOTE(JSON_EXTRACT(hash_sha256, '$.a')) = ? AND JSON_UNQUOTE(JSON_EXTRACT(hash_sha256, '$.h')) = ? AND JSON_UNQUOTE(JSON_EXTRACT(hash_sha256, '$.t')) = ?";
	MysqlP::guard_ResultSet result_set = this->mysql_->executePreQuery(sql_statement, user_id,a_sha256,h_sha256,t_sha256);
	if (result_set.get() && result_set.get()->next()) {
		return result_set.get()->getBoolean(1);
	}
	return false;
}

bool ImageDAO::isExistImageKey(c_ref_string image_key)
{
	c_ref_string sql_statement = "select COUNT(*) from image where image_key=?";
	MysqlP::guard_ResultSet result_set = this->mysql_->executePreQuery(sql_statement,image_key);
	if (result_set.get() && result_set.get()->next()) {
		return result_set.get()->getBoolean(1);
	}
	return false;
}

std::string ImageDAO::getImageKeyByImageId(int image_id)
{
	c_ref_string sql_statement = "select image_key from image where id=?";
	MysqlP::guard_ResultSet result_set = this->mysql_->executePreQuery(sql_statement,image_id);
	if (result_set.get() && result_set.get()->next()) {
		return result_set.get()->getString(1);
	}
	return std::string();
}

std::string ImageDAO::getImageURLByImageKey(c_ref_string image_key) {
	c_ref_string sql_statement = "select url from image where image_key=?";
	MysqlP::guard_ResultSet result_set = this->mysql_->executePreQuery(sql_statement, image_key);
	if (result_set.get() && result_set.get()->next()) {
		return result_set.get()->getString(1);
	}
	return std::string();
}

int ImageDAO::getImageIdBySHA256(int user_id, c_ref_string a_sha256, c_ref_string h_sha256, c_ref_string t_sha256)
{
	c_ref_string sql_statement = "SELECT id FROM image WHERE user_id=? AND JSON_UNQUOTE(JSON_EXTRACT(hash_sha256, '$.a')) = ? AND JSON_UNQUOTE(JSON_EXTRACT(hash_sha256, '$.h')) = ? AND JSON_UNQUOTE(JSON_EXTRACT(hash_sha256, '$.t')) = ?";
	MysqlP::guard_ResultSet result_set = this->mysql_->executePreQuery(sql_statement, user_id,a_sha256,h_sha256,t_sha256);
	if (result_set.get() && result_set.get()->next()) {
		return result_set.get()->getInt(1);
	}
	return -1;
}

int ImageDAO::getImageGroupId(c_ref_string group_name, int user_id)
{
	c_ref_string sql_statement = "select id from image_group where user_id=? and group_name=?";
	MysqlP::guard_ResultSet result_set = this->mysql_->executePreQuery(sql_statement, user_id, group_name);
	if (result_set.get() && result_set.get()->next()) {
		return result_set.get()->getInt(1);
	}
	return -1;
}

image_group_list_do::Wrapper ImageDAO::getImageGroupByUserID(int user_id)
{
	c_ref_string sql_statement = "SELECT  g.id AS group_id,g.group_name,g.createtime,g.updatetime,COUNT(r.image_id) AS image_num FROM image_group AS g LEFT JOIN image_image_group_relevancy AS r ON r.image_group_id = g.id WHERE   g.user_id = ? GROUP BY g.id, g.group_name, g.createtime, g.updatetime";
	MysqlP::guard_ResultSet result_set = this->mysql_->executePreQuery(sql_statement, user_id);
	auto  image_group_list_do= image_group_list_do::createShared();
	if (result_set.get()) {
		while (result_set.get()->next()) {
			image_group_info_do::Wrapper info= image_group_info_do::createShared();
			info->id = result_set.get()->getString("group_id");
			info->name = result_set.get()->getString("group_name");
			info->image_num = result_set.get()->getString("image_num");
			info->createtime = result_set.get()->getString("createtime");
			info->updatetime = result_set.get()->getString("updatetime");
			image_group_list_do->group_list.push_back(info);
		}
	}
	return image_group_list_do;
}

image_list_do::Wrapper ImageDAO::getImageByGroupID(int group_id)
{
	c_ref_string sql_statement = "SELECT i.id, i.original_name, i.mime_type, i.file_size, i.width, i.height, i.image_key, i.createtime, i.updatetime FROM image AS i INNER JOIN image_image_group_relevancy AS r ON i.id = r.image_id WHERE r.image_group_id = ?";
	MysqlP::guard_ResultSet result_set = this->mysql_->executePreQuery(sql_statement, group_id);
	image_list_do::Wrapper image_list_do= image_list_do::createShared();
	if (result_set.get()) {
		while (result_set.get()->next()) {
			image_info_do::Wrapper info= image_info_do::createShared();
			info->id = result_set.get()->getString("id");
			info->name = result_set.get()->getString("original_name");
			info->type = result_set.get()->getString("mime_type");
			info->size = result_set.get()->getString("file_size");
			info->width = result_set.get()->getString("width");
			info->height = result_set.get()->getString("height");
			info->url = result_set.get()->getString("image_key");
			info->createtime = result_set.get()->getString("createtime");
			info->updatetime = result_set.get()->getString("updatetime");
			image_list_do->image_list.push_back(info);
		}
	}
	return image_list_do;
}


