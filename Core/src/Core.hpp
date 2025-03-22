#include "Export.hpp"

class FUTURE_API Core {
public:
    Core();
    virtual ~Core();
    void Run();
};

Core* CreateApplication();