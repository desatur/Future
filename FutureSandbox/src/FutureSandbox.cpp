#include <iostream>

namespace FutureEngine {
    __declspec(dllimport) void Test();
}

int main() {
    FutureEngine::Test();
    return 0;
}
