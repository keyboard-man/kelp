/*************************************************************************
	> File Name: image_metadata.h
	> Author: He Jieting
    > mail: rambo@mail.ustc.edu.cn
	> Created Time: 2015年05月12日 星期二 20时06分35秒
 ************************************************************************/

#ifndef KELP_COMM_IMAGE_METADATA_H_
#define KELP_COMM_IMAGE_METADATA_H_

#include <string>
#include <vector>

namespace kelp
{
struct ImageMetadata
{
	std::string name;
	char* data;
	int size;
};

typedef std::vector<ImageMetadata> ImageData;
};
#endif
