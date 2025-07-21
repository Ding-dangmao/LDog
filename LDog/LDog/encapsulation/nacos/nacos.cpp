#include "nacos.h"

#ifdef Linux

NacosP::NacosP(c_ref_string ip, c_ref_string port) noexcept
{
    this->props[PropertyKeyConst::SERVER_ADDR]=ip+":"+port;
    this->factory=NacosFactoryFactory::getNacosFactory(props);
    this->config_service=this->factory->CreateConfigService();
    this->naming_service=this->factory->CreateNamingService();
}
#ifdef CONFIG_BY_YAML
NacosP::NacosP(const YamlP &yaml):NacosP(yaml["nacos.ip"],yaml["nacos.port"])
{}
NacosP::~NacosP()
{
    ResourceGuard<INacosServiceFactory>_guardFactory(this->factory);
    ResourceGuard <ConfigService>_serviceFactory_config(this->config_service);
    ResourceGuard <NamingService>_serviceFactory_naming(this->naming_service);
}
#endif // CONFIG_BY_YAML


NacosString NacosP::getConfig(c_ref_string config_name){
    NacosString val="";
    try{
        val=config_service->getConfig(config_name,NULLSTR,1000);
    }catch(NacosException&e){
		std::cout<<"Request failed with curl code: "<<e.errorcode()
		<<std::endl<<"Reason: "<<e.what()<<std::endl;
		return "-1";
	}
    return val;
}
void NacosP::setConfig(c_ref_string config_name,c_ref_string config){
    bool bSucc=false;
    try{
        bSucc=config_service->publishConfig(config_name,NULLSTR,config);
    }catch(NacosException&e){
		std::cout<<
		"Request failed with curl code: "<<e.errorcode()<<std::endl<<
		"Reason: "<<e.what()<<std::endl;
	}
    return;
}
void NacosP::addListener(int listener_id,c_ref_string config_name){
    ConfigListenerP* theListener = new ConfigListenerP(listener_id);
    this->config_mapper[listener_id]=theListener;
    this->config_service->addListener(config_name,NULLSTR,theListener);
}
void NacosP::removeListener(int listener_id,c_ref_string config_name){
    if(this->config_mapper.count(listener_id)){
        ConfigListenerP* theListener=this->config_mapper[listener_id];
        this->config_mapper.erase(listener_id);
        this->config_service->removeListener(config_name,NULLSTR,theListener);
    }
}
void NacosP::registerInstance(
                          NacosString serviceName,
                          c_ref_string ip,
                          int port,
                          c_ref_string instanceId,
                          bool ephemeral,
                          c_ref_string clusterName)
{
    Instance instance;
    instance.clusterName=clusterName;
    instance.ip=ip;
    instance.port=port;
    instance.instanceId=instanceId;
    instance.ephemeral=ephemeral;
    this->naming_service->registerInstance(serviceName,instance);
}
void NacosP::deregisterInstance(
                            NacosString serviceName,
                            c_ref_string ip,
                            int port)
{
    this->naming_service->deregisterInstance(serviceName,ip,port);
}

void NacosP::subscribe(int listener_id,NacosString serviceName){
    ServiceListenerP* theListener =new ServiceListenerP(listener_id);
    this->service_mapper[listener_id]=theListener;
    this->naming_service->subscribe(serviceName,theListener);
}
 void NacosP::unsubscribe(int listener_id,NacosString serviceName){
    if(this->service_mapper.count(listener_id)){
        ServiceListenerP* theListener = this->service_mapper[listener_id];
        this->service_mapper[listener_id];
        this->naming_service->unsubscribe(serviceName,theListener);
    }
 }


 #endif Linux