//
// Created by cpasjuste on 29/01/2021.
//

#include "cross2d/c2d.h"

using namespace c2d;

int main(int argc, char *argv[]) {

    // create main renderer
    auto *renderer = new C2DRenderer(Vector2f(640, 480));
    renderer->setClearColor(Color::Gray);

    while (true) {

        // stop if any key is pressed
        if (renderer->getInput()->getKeys() != 0) {
            break;
        }

        // renderer everything
        renderer->flip();
    }

    // will delete child's (textures, shapes, text..)
    delete (renderer);

    return 0;
}
