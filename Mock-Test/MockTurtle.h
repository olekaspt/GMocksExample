#pragma once
#include "Turtle.h"
#include "gmock/gmock.h"  // Brings in gMock.


class MockTurtle : public Turtle {
public:

    MOCK_METHOD(void, PenUp,())
    MOCK_METHOD0(PenDown, void());
    MOCK_METHOD1(Forward, void(int distance));
    MOCK_METHOD1(Turn, void(int degrees));
    MOCK_METHOD2(GoTo, void(int x, int y));
    MOCK_CONST_METHOD0(GetX, int());
    MOCK_CONST_METHOD0(GetY, int());
    MOCK_METHOD0(SomeExpensiveOpertion, void());

};