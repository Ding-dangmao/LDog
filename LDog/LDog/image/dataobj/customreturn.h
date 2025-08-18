#ifndef CUSTOM_RETURN_H
#define CUSTOM_RETURN_H

#include"../config/util_include.h"
#include"return.h"
#include OATPP_CODEGEN_BEGIN(DTO)


class image_group_info {
public:
	oatpp::String id;
	oatpp::String name;
	oatpp::String image_num;
	oatpp::String createtime;
	oatpp::String updatetime;
};

class image_info {
public:
	oatpp::String id;
	oatpp::String name;
	oatpp::String type;
	oatpp::String size;
	oatpp::String width;
	oatpp::String height;
	oatpp::String url;
	oatpp::String createtime;
	oatpp::String updatetime;
};


namespace __class {
	class ImageGroupInfoClass;
	class ImageInfoClass;
}

typedef oatpp::data::mapping::type::Primitive<image_group_info, __class::ImageGroupInfoClass> ImageGroupInfo;
typedef oatpp::data::mapping::type::Primitive<image_info, __class::ImageInfoClass> ImageInfo;


namespace __class {
	class ImageGroupInfoClass {
	private:
		class Inter :public oatpp::Type::Interpretation<ImageGroupInfo, oatpp::UnorderedFields<oatpp::String>> {
		public:
			oatpp::UnorderedFields<oatpp::String>interpret(const ImageGroupInfo& value)const override {
				return {
					{"id",value->id},
					{"name",value->name},
					{"image_num",value->image_num},
					{"createtime",value->createtime},
					{"updatetime",value->updatetime}
				};
			}

			ImageGroupInfo reproduce(const oatpp::UnorderedFields<oatpp::String>& map)const override {
				return ImageGroupInfo({
					map["id"],
					map["name"],
					map["image_num"],
					map["createtime"],
					map["updatetime"]
					});
			}
		};
	public:
		static const oatpp::ClassId CLASS_ID;
		static oatpp::Type* getType() {
			auto x = oatpp::Type::Info();
			x.interpretationMap["custom-types"] = new Inter();
			static oatpp::Type type(CLASS_ID, x);
			return &type;
		}
	};

	class ImageInfoClass {
	private:
		class Inter :public oatpp::Type::Interpretation<ImageInfo, oatpp::UnorderedFields<oatpp::String>> {
		public:
			oatpp::UnorderedFields<oatpp::String>interpret(const ImageInfo& value)const override {
				return {
					{"id",value->id},
					{"name",value->name},
					{"type",value->type},
					{"size",value->size},
					{"width",value->width},
					{"height",value->height},
					{"url",value->url},
					{"createtime",value->createtime},
					{"updatetime",value->updatetime}
				};
			}
			ImageInfo reproduce(const oatpp::UnorderedFields<oatpp::String>& map)const override {
				return ImageInfo({
					map["id"],
					map["name"],
					map["type"],
					map["size"],
					map["width"],
					map["height"],
					map["url"],
					map["createtime"],
					map["updatetime"]
					});
			}
		};
	public:
		static const oatpp::ClassId CLASS_ID;
		static oatpp::Type* getType() {
			auto x = oatpp::Type::Info();
			x.interpretationMap["custom-types"] = new Inter();
			static oatpp::Type type(CLASS_ID, x);
			return &type;
		}
	};
}


class ImageGroupListReturn :public LDog::BaseDTOR {
	DTO_INIT(ImageGroupListReturn, BaseDTOR)
	DTO_FIELD(oatpp::List<ImageGroupInfo>, group_list);
};

class ImageListReturn :public LDog::BaseDTOR {
	DTO_INIT(ImageListReturn, BaseDTOR)
	DTO_FIELD(oatpp::List<ImageInfo>, image_list);
};

#include OATPP_CODEGEN_END(DTO)
#endif // !CUSTOM_RETURN_H