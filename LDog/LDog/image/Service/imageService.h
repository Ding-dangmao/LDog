#ifndef IMAGE_SERVICE_H
#define IMAGE_SERVICE_H

#include"../dataobj/obj.h"


class ImageService {
	using c_ref_str = const std::string&;
public:
	ImageService() = default;
	~ImageService() = default;
	static ImageUploadStartReturn::Wrapper uploadStart(const ImageUploadStart::Wrapper dto);
	static ImageCompleteReturn::Wrapper uploadComplete(const ImageUploadComplete::Wrapper dto);
	static ImageUploadReturn::Wrapper uploadImage(const ImageUpload::Wrapper dto);

}


#endif // !IMAGE_SERVICE_H
