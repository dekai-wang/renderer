//
//  main.cpp
//  renderer
//
//  Created by MrMac on 2020/5/21.
//  Copyright © 2020 MrMac. All rights reserved.
//

#include <iostream>

#include "Application.hpp"

int main(int argc, char** argv)
{
    Application app;
    
    app.init(480, 320);
    
    app.loop();

    return 0;
}
