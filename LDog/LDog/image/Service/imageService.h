#ifndef IMAGE_SERVICE_H
#define IMAGE_SERVICE_H

#include"../dataobj/obj.h"
#include"../util/util.h"
#include<unordered_map>
#include<boost/url.hpp>

class ImageService {
	using c_ref_str = const std::string&;
public:
	ImageService() = default;
	~ImageService() = default;
	static ImageUploadStartReturn::Wrapper uploadStart(const ImageUploadStart::Wrapper dto);
	static ImageCompleteReturn::Wrapper uploadComplete(const ImageUploadComplete::Wrapper dto);
	static ImageUploadReturn::Wrapper uploadImage(const ImageUpload::Wrapper dto);
	static ImageGroupListReturn::Wrapper getImageGroupInfo(const image_group_info_get::Wrapper dto);
	static ImageListReturn::Wrapper getImageInfo(const image_info_get::Wrapper dto);
	//access_token -> name+unix_time
	static std::unordered_map<std::string, std::string> imageAccessTokenMap;
	static unsigned short times_;
};


#endif // !IMAGE_SERVICE_H
