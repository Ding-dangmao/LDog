#ifndef UTIL_INCLUDE_H
#define UTIL_INCLUDE_H
#include"oatpp/oatpp_component.hpp"
#include"oatpp/oatpp_controller-example.h"
#include"oatpp/oatpp_run.hpp"
#include"oatpp/api_client/client_run.hpp"
#include"yaml/yaml_p.h"
#include"mysql/mysqlc.h"
#include"thread_pool/thread_pool_p.hpp"
#include"thread_pool/thread_pool_util.h"
#include"memory_pool/memory_pool_p.hpp"

#ifndef SINGLE_DATA_TO_DATA_V1(obj,data)
#define SINGLE_DATA_TO_DATA_V1(obj,data)\
obj->##data=data;
#define SINGLE_DATA_TO_DATA_V2(obj1,obj2,data)\
obj2->##data=obj1->##data;
#endif


#define DTO_TO_DO_1(dto,do,a)\
SINGLE_DATA_TO_DATA_V2(dto,do,a)
#define DTO_TO_DO_2(dto,do,a,b)\
SINGLE_DATA_TO_DATA_V2(dto,do,a)\
SINGLE_DATA_TO_DATA_V2(dto,do,b)
#define DTO_TO_DO_3(dto,do,a,b,c)\
SINGLE_DATA_TO_DATA_V2(dto,do,a)\
SINGLE_DATA_TO_DATA_V2(dto,do,b)\
SINGLE_DATA_TO_DATA_V2(dto,do,c)
#define DTO_TO_DO_4(dto,do,a,b,c,d)\
SINGLE_DATA_TO_DATA_V2(dto,do,a)\
SINGLE_DATA_TO_DATA_V2(dto,do,b)\
SINGLE_DATA_TO_DATA_V2(dto,do,c)\
SINGLE_DATA_TO_DATA_V2(dto,do,d)
#define DTO_TO_DO_5(dto,do,a,b,c,d,e)\
SINGLE_DATA_TO_DATA_V2(dto,do,a)\
SINGLE_DATA_TO_DATA_V2(dto,do,b)\
SINGLE_DATA_TO_DATA_V2(dto,do,c)\
SINGLE_DATA_TO_DATA_V2(dto,do,d)\
SINGLE_DATA_TO_DATA_V2(dto,do,e)
#define DTO_TO_DO_6(dto,do,a,b,c,d,e,f)\
SINGLE_DATA_TO_DATA_V2(dto,do,a)\
SINGLE_DATA_TO_DATA_V2(dto,do,b)\
SINGLE_DATA_TO_DATA_V2(dto,do,c)\
SINGLE_DATA_TO_DATA_V2(dto,do,d)\
SINGLE_DATA_TO_DATA_V2(dto,do,e)\
SINGLE_DATA_TO_DATA_V2(dto,do,f)
#define DTO_TO_DO_7(dto,do,a,b,c,d,e,f,g)\
SINGLE_DATA_TO_DATA_V2(dto,do,a)\
SINGLE_DATA_TO_DATA_V2(dto,do,b)\
SINGLE_DATA_TO_DATA_V2(dto,do,c)\
SINGLE_DATA_TO_DATA_V2(dto,do,d)\
SINGLE_DATA_TO_DATA_V2(dto,do,e)\
SINGLE_DATA_TO_DATA_V2(dto,do,f)\
SINGLE_DATA_TO_DATA_V2(dto,do,g)
#define DTO_TO_DO_8(dto,do,a,b,c,d,e,f,g,h)\
SINGLE_DATA_TO_DATA_V2(dto,do,a)\
SINGLE_DATA_TO_DATA_V2(dto,do,b)\
SINGLE_DATA_TO_DATA_V2(dto,do,c)\
SINGLE_DATA_TO_DATA_V2(dto,do,d)\
SINGLE_DATA_TO_DATA_V2(dto,do,e)\
SINGLE_DATA_TO_DATA_V2(dto,do,f)\
SINGLE_DATA_TO_DATA_V2(dto,do,g)\
SINGLE_DATA_TO_DATA_V2(dto,do,h)
#define DTO_TO_DO_9(dto,do,a,b,c,d,e,f,g,h,i)\
SINGLE_DATA_TO_DATA_V2(dto,do,a)\
SINGLE_DATA_TO_DATA_V2(dto,do,b)\
SINGLE_DATA_TO_DATA_V2(dto,do,c)\
SINGLE_DATA_TO_DATA_V2(dto,do,d)\
SINGLE_DATA_TO_DATA_V2(dto,do,e)\
SINGLE_DATA_TO_DATA_V2(dto,do,f)\
SINGLE_DATA_TO_DATA_V2(dto,do,g)\
SINGLE_DATA_TO_DATA_V2(dto,do,h)\
SINGLE_DATA_TO_DATA_V2(dto,do,i)
#define DTO_TO_DO_10(dto,do,a,b,c,d,e,f,g,h,i,j)\
SINGLE_DATA_TO_DATA_V2(dto,do,a)\
SINGLE_DATA_TO_DATA_V2(dto,do,b)\
SINGLE_DATA_TO_DATA_V2(dto,do,c)\
SINGLE_DATA_TO_DATA_V2(dto,do,d)\
SINGLE_DATA_TO_DATA_V2(dto,do,e)\
SINGLE_DATA_TO_DATA_V2(dto,do,f)\
SINGLE_DATA_TO_DATA_V2(dto,do,g)\
SINGLE_DATA_TO_DATA_V2(dto,do,h)\
SINGLE_DATA_TO_DATA_V2(dto,do,i)\
SINGLE_DATA_TO_DATA_V2(dto,do,j)
#define DTO_TO_DO_11(dto,do,a,b,c,d,e,f,g,h,i,j,k)\
SINGLE_DATA_TO_DATA_V2(dto,do,a)\
SINGLE_DATA_TO_DATA_V2(dto,do,b)\
SINGLE_DATA_TO_DATA_V2(dto,do,c)\
SINGLE_DATA_TO_DATA_V2(dto,do,d)\
SINGLE_DATA_TO_DATA_V2(dto,do,e)\
SINGLE_DATA_TO_DATA_V2(dto,do,f)\
SINGLE_DATA_TO_DATA_V2(dto,do,g)\
SINGLE_DATA_TO_DATA_V2(dto,do,h)\
SINGLE_DATA_TO_DATA_V2(dto,do,i)\
SINGLE_DATA_TO_DATA_V2(dto,do,j)\
SINGLE_DATA_TO_DATA_V2(dto,do,k)
#define DTO_TO_DO_12(dto,do,a,b,c,d,e,f,g,h,i,j,k,l)\
SINGLE_DATA_TO_DATA_V2(dto,do,a)\
SINGLE_DATA_TO_DATA_V2(dto,do,b)\
SINGLE_DATA_TO_DATA_V2(dto,do,c)\
SINGLE_DATA_TO_DATA_V2(dto,do,d)\
SINGLE_DATA_TO_DATA_V2(dto,do,e)\
SINGLE_DATA_TO_DATA_V2(dto,do,f)\
SINGLE_DATA_TO_DATA_V2(dto,do,g)\
SINGLE_DATA_TO_DATA_V2(dto,do,h)\
SINGLE_DATA_TO_DATA_V2(dto,do,i)\
SINGLE_DATA_TO_DATA_V2(dto,do,j)\
SINGLE_DATA_TO_DATA_V2(dto,do,k)\
SINGLE_DATA_TO_DATA_V2(dto,do,l)

#define DO_TO_DTO_1(do,dto,a)\
SINGLE_DATA_TO_DATA_V2(do,dto,a)
#define DO_TO_DTO_2(do,dto,a,b)\
SINGLE_DATA_TO_DATA_V2(do,dto,a)\
SINGLE_DATA_TO_DATA_V2(do,dto,b)
#define DO_TO_DTO_3(do,dto,a,b,c)\
SINGLE_DATA_TO_DATA_V2(do,dto,a)\
SINGLE_DATA_TO_DATA_V2(do,dto,b)\
SINGLE_DATA_TO_DATA_V2(do,dto,c)
#define DO_TO_DTO_4(do,dto,a,b,c,d)\
SINGLE_DATA_TO_DATA_V2(do,dto,a)\
SINGLE_DATA_TO_DATA_V2(do,dto,b)\
SINGLE_DATA_TO_DATA_V2(do,dto,c)\
SINGLE_DATA_TO_DATA_V2(do,dto,d)
#define DO_TO_DTO_5(do,dto,a,b,c,d,e)\
SINGLE_DATA_TO_DATA_V2(do,dto,a)\
SINGLE_DATA_TO_DATA_V2(do,dto,b)\
SINGLE_DATA_TO_DATA_V2(do,dto,c)\
SINGLE_DATA_TO_DATA_V2(do,dto,d)\
SINGLE_DATA_TO_DATA_V2(do,dto,e)
#define DO_TO_DTO_6(do,dto,a,b,c,d,e,f)\
SINGLE_DATA_TO_DATA_V2(do,dto,a)\
SINGLE_DATA_TO_DATA_V2(do,dto,b)\
SINGLE_DATA_TO_DATA_V2(do,dto,c)\
SINGLE_DATA_TO_DATA_V2(do,dto,d)\
SINGLE_DATA_TO_DATA_V2(do,dto,e)\
SINGLE_DATA_TO_DATA_V2(do,dto,f)
#define DO_TO_DTO_7(do,dto,a,b,c,d,e,f,g)\
SINGLE_DATA_TO_DATA_V2(do,dto,a)\
SINGLE_DATA_TO_DATA_V2(do,dto,b)\
SINGLE_DATA_TO_DATA_V2(do,dto,c)\
SINGLE_DATA_TO_DATA_V2(do,dto,d)\
SINGLE_DATA_TO_DATA_V2(do,dto,e)\
SINGLE_DATA_TO_DATA_V2(do,dto,f)\
SINGLE_DATA_TO_DATA_V2(do,dto,g)
#define DO_TO_DTO_8(do,dto,a,b,c,d,e,f,g,h)\
SINGLE_DATA_TO_DATA_V2(do,dto,a)\
SINGLE_DATA_TO_DATA_V2(do,dto,b)\
SINGLE_DATA_TO_DATA_V2(do,dto,c)\
SINGLE_DATA_TO_DATA_V2(do,dto,d)\
SINGLE_DATA_TO_DATA_V2(do,dto,e)\
SINGLE_DATA_TO_DATA_V2(do,dto,f)\
SINGLE_DATA_TO_DATA_V2(do,dto,g)\
SINGLE_DATA_TO_DATA_V2(do,dto,h)
#define DO_TO_DTO_9(do,dto,a,b,c,d,e,f,g,h,i)\
SINGLE_DATA_TO_DATA_V2(do,dto,a)\
SINGLE_DATA_TO_DATA_V2(do,dto,b)\
SINGLE_DATA_TO_DATA_V2(do,dto,c)\
SINGLE_DATA_TO_DATA_V2(do,dto,d)\
SINGLE_DATA_TO_DATA_V2(do,dto,e)\
SINGLE_DATA_TO_DATA_V2(do,dto,f)\
SINGLE_DATA_TO_DATA_V2(do,dto,g)\
SINGLE_DATA_TO_DATA_V2(do,dto,h)\
SINGLE_DATA_TO_DATA_V2(do,dto,i)
#define DO_TO_DTO_10(do,dto,a,b,c,d,e,f,g,h,i,j)\
SINGLE_DATA_TO_DATA_V2(do,dto,a)\
SINGLE_DATA_TO_DATA_V2(do,dto,b)\
SINGLE_DATA_TO_DATA_V2(do,dto,c)\
SINGLE_DATA_TO_DATA_V2(do,dto,d)\
SINGLE_DATA_TO_DATA_V2(do,dto,e)\
SINGLE_DATA_TO_DATA_V2(do,dto,f)\
SINGLE_DATA_TO_DATA_V2(do,dto,g)\
SINGLE_DATA_TO_DATA_V2(do,dto,h)\
SINGLE_DATA_TO_DATA_V2(do,dto,i)\
SINGLE_DATA_TO_DATA_V2(do,dto,j)
#define DO_TO_DTO_11(do,dto,a,b,c,d,e,f,g,h,i,j,k)\
SINGLE_DATA_TO_DATA_V2(do,dto,a)\
SINGLE_DATA_TO_DATA_V2(do,dto,b)\
SINGLE_DATA_TO_DATA_V2(do,dto,c)\
SINGLE_DATA_TO_DATA_V2(do,dto,d)\
SINGLE_DATA_TO_DATA_V2(do,dto,e)\
SINGLE_DATA_TO_DATA_V2(do,dto,f)\
SINGLE_DATA_TO_DATA_V2(do,dto,g)\
SINGLE_DATA_TO_DATA_V2(do,dto,h)\
SINGLE_DATA_TO_DATA_V2(do,dto,i)\
SINGLE_DATA_TO_DATA_V2(do,dto,j)\
SINGLE_DATA_TO_DATA_V2(do,dto,k)
#define DO_TO_DTO_12(do,dto,a,b,c,d,e,f,g,h,i,j,k,l)\
SINGLE_DATA_TO_DATA_V2(do,dto,a)\
SINGLE_DATA_TO_DATA_V2(do,dto,b)\
SINGLE_DATA_TO_DATA_V2(do,dto,c)\
SINGLE_DATA_TO_DATA_V2(do,dto,d)\
SINGLE_DATA_TO_DATA_V2(do,dto,e)\
SINGLE_DATA_TO_DATA_V2(do,dto,f)\
SINGLE_DATA_TO_DATA_V2(do,dto,g)\
SINGLE_DATA_TO_DATA_V2(do,dto,h)\
SINGLE_DATA_TO_DATA_V2(do,dto,i)\
SINGLE_DATA_TO_DATA_V2(do,dto,j)\
SINGLE_DATA_TO_DATA_V2(do,dto,k)\
SINGLE_DATA_TO_DATA_V2(do,dto,l)





#endif //UTIL_INCLUDE_H