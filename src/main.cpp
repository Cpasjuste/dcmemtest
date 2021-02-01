//
// Created by cpasjuste on 29/01/2021.
//

#include "main.h"

using namespace c2d;

MemTest::MemTest(const Vector2f &size) : C2DRenderer(size) {
    getFont()->setFilter(Texture::Filter::Point);
    getFont()->setOffset({0, 5});

    auto *border = new C2DRectangle({2, 2, getSize().x - 4, getSize().y - 4});
    border->setFillColor(Color::Gray);
    border->setOutlineColor(Color::Yellow);
    border->setOutlineThickness(2);
    add(border);

    auto title = new C2DText("DC MEMTEST @ CPASJUSTE", 16);
    title->setFillColor(Color::Yellow);
    title->setOutlineThickness(2);
    title->setPosition(16, 16);
    add(title);

    text[0] = new C2DText("BASE ADDRESS: ??, BYTES: ??", 16);
    text[1] = new C2DText("DATA BUS TEST: WAITING...", 16);
    text[2] = new C2DText("ADDRESS BUS TEST: WAITING...", 16);
    text[3] = new C2DText("DEVICE TEST: WAITING...", 16);

    for (int i = 0; i < 4; i++) {
        text[i]->setOutlineThickness(2);
        text[i]->setPosition(16, (float) (96 + (i * 32)));
        add(text[i]);
    }

    flip();
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

void MemTest::doTest() {

    uint32_t data, *address;
    unsigned long num_bytes;

    /*
    if (mm_top() == 0x8e000000) {
        num_bytes = NUM_BYTES_32;
    } else {
        num_bytes = NUM_BYTES_16;
    }
    */
    num_bytes = NUM_BYTES_16;
    setText(0, "BASE ADDRESS: %p, BYTES: %lu", BASE_ADDRESS, num_bytes);

    fflush(stdout);
    data = memTestDataBus(BASE_ADDRESS);
    if (data != 0) {
        setText(1, "DATA BUS TEST: FAIL AT %08lx", data);
    } else {
        setText(1, "DATA BUS TEST: PASS");
    }
    fflush(stdout);

    fflush(stdout);
    address = memTestAddressBus(BASE_ADDRESS, num_bytes);
    if (address != nullptr) {
        setText(2, "ADDRESS BUS TEST: FAIL AT %p", address);
    } else {
        setText(2, "ADDRESS BUS TEST: PASS");
    }
    fflush(stdout);

    fflush(stdout);
    address = memTestDevice(BASE_ADDRESS, num_bytes);
    if (address != nullptr) {
        setText(3, "DEVICE TEST: FAIL AT %p", address);
    } else {
        setText(3, "DEVICE TEST: PASS");
    }
    fflush(stdout);
}

void MemTest::setText(int num, const char *fmt, ...) {
    va_list args;
    char buffer[512];

    memset(buffer, 0, 512);
    va_start(args, fmt);
    vsnprintf(buffer, MAX_PATH, fmt, args);
    va_end(args);

    text[num]->setString(Utility::toUpper(buffer));
    flip();
    delay(1000);
}

int main() {

    // create main renderer
    auto *memTest = new MemTest({C2D_SCREEN_WIDTH, C2D_SCREEN_HEIGHT});
    memTest->doTest();

    while (!memTest->quit) {
        memTest->flip();
    }

    // will delete child's (textures, shapes, text..)
    delete (memTest);

    return 0;
}
