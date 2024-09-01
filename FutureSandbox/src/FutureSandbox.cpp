#include <iostream>
#include "../../Future/Future.hpp"

class FutureSandbox : public Future::Engine {
public:
    FutureSandbox() {

    }
    ~FutureSandbox() {
    }
};

Future::Engine* Future::CreateApplication() {
    return new FutureSandbox;
}