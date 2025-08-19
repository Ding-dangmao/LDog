# README
## 懒狗图床

此图床设计为内网管理图床,若在公网开放并未设计账户注册接口,只能通过手动录入账户数据或自行设计接口

## 数据库准备

~~~sql
create table account_storge
(
    id          int auto_increment comment '用户唯一标识'
        primary key,
    nickname    varchar(50) not null comment '昵称',
    password    varchar(20) null,
    type        int         null comment '用户类型',
    create_time datetime    null,
    update_time datetime    null,
    constraint account_storge_pk_2
        unique (nickname)
)
    comment '存储用户的账户';
    
create table image
(
    id            int auto_increment
        primary key,
    user_id       int          not null,
    image_key     varchar(100) null,
    hash_sha256   json         null,
    original_name varchar(255) not null,
    mime_type     varchar(64)  not null,
    url           varchar(150) not null,
    file_size     bigint       null,
    width         int          null,
    height        int          null,
    createtime    datetime     null,
    updatetime    datetime     null
);

create table image_group
(
    id         int auto_increment
        primary key,
    user_id    int         null,
    group_name varchar(50) null,
    createtime datetime    null,
    updatetime datetime    null
);

create table image_image_group_relevancy
(
    image_id       int null,
    image_group_id int null,
    constraint image_image_group_relevancy_image_group_id_fk
        foreign key (image_group_id) references image_group (id),
    constraint image_image_group_relevancy_image_id_fk
        foreign key (image_id) references image (id)
);
~~~

## 存储文件示图

主文件夹为: ldog_images

子目录:

- image_info: 存储图片上传临时信息
- images: 存储上传后合成的图片
- temp: 临时存储上传图片

![image-20250818143830576.png](https://www.ddcat.club/picture/async?image_key=M0OB870s645JzJ5l9857j4S79x7uHEn9HG8cdSGkJ6O7%7BJ4a2tSy0xQ2ax20U47h)

## 目前已有功能

- 上传图片
- 获取图片
- 获取图片组
- 数据缓存清理
- 支持跨平台

## 待完成功能

- 请求数据校验
- 自动部署脚本
- 后端SHA256再校验

## 相应前端
