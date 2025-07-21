#ifndef NACOS_H
#define NACOS_H

#include<iostream>
#include<map>

#ifdef Linux
#include"Nacos.h"

using namespace nacos;

#define CONFIG_BY_YAML
#ifdef CONFIG_BY_YAML
#include"../yaml/yaml_p.h"
#endif // CONFIG_BY_YAML

class NacosP{
    class ConfigListenerP;
    class ServiceListenerP;

public:
	using c_ref_string = const std::string&;
    NacosP(c_ref_string ip,c_ref_string port)noexcept;
#ifdef CONFIG_BY_YAML
    NacosP(const YamlP& yaml);
#endif //CONFIG_BY_YAML
    ~NacosP();

public:
    NacosString getConfig(c_ref_string config_name);
    void setConfig(c_ref_string config_name,c_ref_string config);

    void addListener(int listener_id,c_ref_string config_name);
    void removeListener(int listener_id,c_ref_string config_name);

    void registerInstance(NacosString serviceName,
                          c_ref_string ip,
                          int port,
                          c_ref_string instanceId,
                          bool ephemeral,
                          c_ref_string clusterName="DefaultCluster");
    void deregisterInstance(NacosString serviceName,
                            c_ref_string ip,
                            int port);
    
    void subscribe(int listener_id,NacosString serviceName);
    void unsubscribe(int listener_id,NacosString serviceName);

private:
    class ConfigListenerP:public Listener{
    private:
        int num;
    public:
        ConfigListenerP(int num):num(num){}
        void receiveConfigInfo(const NacosString& configInfo){
            std::cout << "===================================" << std::endl;
            std::cout << "Watcher: " << num << std::endl;
            std::cout << "Watched Key UPDATED:" << configInfo << std::endl;
            std::cout << "===================================" << std::endl;
        }
    };

    class ServiceListenerP:public EventListener{
    private:
        int num;
    public:
        ServiceListenerP(int num):num(num){}
        
        void receiveNamingInfo(const ServiceInfo& serviceInfo){
            std::cout << "===================================" << std::endl;
            std::cout << "Watcher: " << num << std::endl;
            std::cout << "Watched service UPDATED: " << serviceInfo.toInstanceString() << std::endl;
            std::cout << "===================================" << std::endl;
        }
    };

    Properties props;
    INacosServiceFactory *factory;
    ConfigService* config_service;
    NamingService* naming_service;
    std::map<int,ConfigListenerP*> config_mapper;
    std::map<int,ServiceListenerP*> service_mapper;
};


#endif //Linux

#endif //NACOS_H