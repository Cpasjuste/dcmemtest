//
// Created by cpasjuste on 29/01/2021.
//

#include "cross2d/c2d.h"
#include "main.h"

using namespace c2d;

MemTest::MemTest(const Vector2f &size) : C2DRenderer(size) {
    setClearColor(Color::Gray);
    getFont()->setFilter(Texture::Filter::Point);
    getFont()->setOffset({0, 5});

    auto *border = new C2DRectangle({2, 2, getSize().x - 4, getSize().y - 4});
    border->setFillColor(Color::Transparent);
    border->setOutlineColor(Color::Yellow);
    border->setOutlineThickness(2);
    add(border);
}

bool MemTest::onInput(c2d::Input::Player *players) {

    unsigned int keys = players[0].keys;

    if (keys & EV_QUIT) {
        quit = true;
    }

    return C2DRenderer::onInput(players);
}

void MemTest::onUpdate() {
    C2DRenderer::onUpdate();
}

int main() {

    // create main renderer
    auto *memTest = new MemTest({C2D_SCREEN_WIDTH, C2D_SCREEN_HEIGHT});
    printf("renderer\n");

    while (!memTest->quit) {
        memTest->flip();
    }

    // will delete child's (textures, shapes, text..)
    delete (memTest);

    return 0;
}
