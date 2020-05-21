//
//  Utils.hpp
//  renderer
//
//  Created by MrMac on 2020/5/21.
//  Copyright © 2020 MrMac. All rights reserved.
//

#ifndef Utils_hpp
#define Utils_hpp

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class Utils {
public:
    static std::string getFileData(const char* path)
    {
        std::string data;
        try {
            std::ifstream file(path, file.binary | file.in);
            if (file.is_open())
            {
                std::stringstream ss;
                ss << file.rdbuf();
                data = ss.str();
            }
        } catch (std::ifstream::failure& e) {
            std::cout << e.what();
        }
        return data;
    };
};

#endif /* Utils_hpp */
