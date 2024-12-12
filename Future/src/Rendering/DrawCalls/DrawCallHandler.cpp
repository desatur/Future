#include "DrawCallHandler.hpp"

namespace Future {
    unsigned int DrawCallHandler::Push(DrawRequest request) {
        drawRequestQueue.push_back(request);
    }

    bool DrawCallHandler::Pop(unsigned int id) {
        auto it = std::find_if(drawRequestQueue.begin(), drawRequestQueue.end(),
                               [id](const DrawRequest& request) {
                                   return request.ID == id;
                               });
        if (it != drawRequestQueue.end()) {
            drawRequestQueue.erase(it);
            return true;
        }
        return false;
    }

    void DrawCallHandler::DrawFrame() {
        for (unsigned int i = 0; i < drawRequestQueue.size(); i++)
        {
            //drawRequestQueue[i].mesh.Draw(shader, camera, matricesMeshes[i], translationsMeshes[i], rotationsMeshes[i], scalesMeshes[i]);
        }
        drawRequestQueue.clear();
    }
}