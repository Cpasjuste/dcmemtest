//
// Created by cpasjuste on 29/01/2021.
//

#ifndef DCMEMTEST_MAIN_H
#define DCMEMTEST_MAIN_H

class MemTest : public c2d::C2DRenderer {

public:
    explicit MemTest(const c2d::Vector2f &size);

    bool quit = false;

private:

    bool onInput(c2d::Input::Player *players) override;

    void onUpdate() override;
};

#endif //DCMEMTEST_MAIN_H
