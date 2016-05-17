/*************************************************************************
	> File Name: ../module/image_module.cpp
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年05月12日 星期二 20时39分08秒
 ************************************************************************/

#include <iostream>
#include <fstream>

#include "log4cxx/logger.h"

#include "comm/image_metadata.h"

extern "C"
{
	void ImageHandler(kelp::ImageData&);
}

void ImageHandler(kelp::ImageData& data)
{
	std::cout << "This is image handler:will read image from /home/zhuce/1.png" << std::endl;
	log4cxx::LoggerPtr log_;
	log_ = log4cxx::Logger::getLogger("image_module");

	std::ifstream ifs;
	ifs.open("/home/zhuce/1.png",std::ifstream::binary);
	if(ifs)
	{
		ifs.seekg(0,ifs.end);
		int length = ifs.tellg();
		ifs.seekg(0,ifs.beg);

		std::cout << "size:" << length << std::endl;

		char* buf = new char[length];

		ifs.read(buf,length);
		if(ifs)
			std::cout << "all characters read successfully." << std::endl;
		else
			std::cout << "error:only " << ifs.gcount() << "could be read" << std::endl;

		ifs.close();

		kelp::ImageMetadata metadata;
		metadata.name = "1_png";
		metadata.data = buf;
		metadata.size = length;

		data.push_back(metadata);
	}
	else
	{
		LOG4CXX_WARN(log_,"Can not open image file!");
	}

	std::cout << "End call of image handler" << std::endl;
}
