#!/bin/bash
sudo rm -r /usr/lib/libspotkv.so*
sudo rm -r /usr/local/lib/libspotkv*
sudo cp out-shared/libspotkv.so* /usr/local/lib &sudo cp out-shared/libspotkv.so* /usr/lib &sudo cp -R include/* /usr/local/include & sudo cp out-static/libspotkv.a /usr/local/lib
