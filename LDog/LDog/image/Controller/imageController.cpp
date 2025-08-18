#include"imageController.h"

void TopcTool::decode(oatpp::String& t)
{
	std::ostringstream ss;
	ss << boost::urls::decode_view(t->c_str());
	t = ss.str();
}
