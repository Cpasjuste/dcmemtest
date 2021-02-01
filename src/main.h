//
// Created by cpasjuste on 29/01/2021.
//

#ifndef DCMEMTEST_MAIN_H
#define DCMEMTEST_MAIN_H

#include "cross2d/c2d.h"
#include "memtest.h"

/* Leave space at the beginning and end of memory for this program and for the stack */
#define SAFE_AREA     0x100000
#define STACK_SIZE    65536
#define BASE_ADDRESS  (volatile datum *) (0x8c000000 + SAFE_AREA)
#define NUM_BYTES_32  (32 * 1024 * 1024 - SAFE_AREA - STACK_SIZE)
#define NUM_BYTES_16  (16 * 1024 * 1024 - SAFE_AREA - STACK_SIZE)

class MemTest : public c2d::C2DRenderer {

public:
    explicit MemTest(const c2d::Vector2f &size);

    void doTest();

    void setText(int num, const char *fmt, ...);

    bool quit = false;

private:

    bool onInput(c2d::Input::Player *players) override;

    void onUpdate() override;

    c2d::C2DText *text[4];
};

#endif //DCMEMTEST_MAIN_H
