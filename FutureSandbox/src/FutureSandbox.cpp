#include <iostream>
#include "../../Future/include/Future.hpp"

class FutureSandbox : public Future::Engine {
public:
    FutureSandbox() {

    }
    ~FutureSandbox() {

    }
};

int main() {
    FutureSandbox* fs = new FutureSandbox();
    fs->Run();
    delete fs;
    return 0;
}
