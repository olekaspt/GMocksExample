#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "MockTurtle.h"
#include "painter.h"
#include "Game.h"
#include "MockRealObject.h"


class MockTest {
public:
    MOCK_METHOD(void, SomeMethod, ());
};

TEST(TestCaseName, TestName) {
    MockTest mock;
    EXPECT_CALL(mock, SomeMethod);
    mock.SomeMethod();

}

using ::testing::AtLeast;
TEST(PainterTest, CanDrawSomething) {
    MockTurtle turtle;
    EXPECT_CALL(turtle, PenDown())
        .Times(AtLeast(1));

    Painter painter(&turtle);

    EXPECT_TRUE(painter.DrawCircle(0, 0, 10));
}
using ::testing::Return;
TEST(PainterTest, Returns) {
    MockTurtle turtle;
    EXPECT_CALL(turtle, GetX())
        .Times(8)
        .WillOnce(Return(100))
        .WillOnce(Return(150))
        .WillRepeatedly(Return(200));


    EXPECT_EQ(turtle.GetX(), 100);
    EXPECT_EQ(turtle.GetX(), 150);
    EXPECT_EQ(turtle.GetX(), 200);
    EXPECT_EQ(turtle.GetX(), 200);
    EXPECT_EQ(turtle.GetX(), 200);

    EXPECT_EQ(turtle.GetX(), 200);

    EXPECT_EQ(turtle.GetX(), 200);
    EXPECT_EQ(turtle.GetX(), 200);
}

TEST(PainterTest, ReturnsMoreUseful) {
    MockTurtle turtle;
    EXPECT_CALL(turtle, GetX())
        .Times(8)
        .WillOnce(Return(100))
        .WillOnce(Return(150))
        .WillRepeatedly(Return(200));


    Game game(&turtle);

    game.ChaseTurtle();

    EXPECT_EQ(game.GetDogX(), 200);
    EXPECT_EQ(game.GetMoves(), 8);


}

using ::testing::_;
using ::testing::Ge;
TEST(PainterTest, ReturnsEvenMoreUseful) {
    MockTurtle turtle;
    EXPECT_CALL(turtle, GetX())
        .Times(8)
        .WillOnce(Return(100))
        .WillOnce(Return(150))
        .WillRepeatedly(Return(200));

    // Expects the turtle to move forward by 100 units.
    EXPECT_CALL(turtle, Forward( Ge( 80)  )).Times(AtLeast(1));
   
    EXPECT_CALL(turtle, GoTo(50, _)).Times(AtLeast(1));

    Game game(&turtle);

    game.ChaseTurtle();

    EXPECT_EQ(game.GetDogX(), 200);
    EXPECT_EQ(game.GetMoves(), 8);


}

using ::testing::StrictMock;
using ::testing::NiceMock;
TEST(PainterTest, ExpensiveOperationAllowed) {
    NiceMock<MockTurtle> turtle;
    EXPECT_CALL(turtle, GetX())
        .Times(8)
        .WillOnce(Return(100))
        .WillOnce(Return(150))
        .WillRepeatedly(Return(200));

    // Expects the turtle to move forward by 100 units.
    EXPECT_CALL(turtle, Forward(Ge(80))).Times(AtLeast(1));

    EXPECT_CALL(turtle, GoTo(50, _)).Times(AtLeast(1));

    Game game(&turtle);

    game.ChaseTurtle();

    EXPECT_EQ(game.GetDogX(), 200);
    EXPECT_EQ(game.GetMoves(), 8);


}

TEST(PainterTest, ExpensiveNotOperationAllowed) {
    StrictMock<MockTurtle> turtle;
    EXPECT_CALL(turtle, GetX())
        .Times(8)
        .WillOnce(Return(100))
        .WillOnce(Return(150))
        .WillRepeatedly(Return(200));

    // Expects the turtle to move forward by 100 units.
    EXPECT_CALL(turtle, Forward(Ge(80))).Times(AtLeast(1));

    EXPECT_CALL(turtle, GoTo(50, _)).Times(AtLeast(1));

    EXPECT_CALL(turtle, GetY())
        .Times(8);

    Game game(&turtle);

    game.ChaseTurtle();

    EXPECT_EQ(game.GetDogX(), 200);
    EXPECT_EQ(game.GetMoves(), 8);


}

TEST(PainterTest, ExpensiveNotOperationAllowed2) {
    MockTurtle turtle;
    EXPECT_CALL(turtle, GetX())
        .Times(8)
        .WillOnce(Return(100))
        .WillOnce(Return(150))
        .WillRepeatedly(Return(200));

    // Expects the turtle to move forward by 100 units.
    EXPECT_CALL(turtle, Forward(Ge(80))).Times(AtLeast(1));

    EXPECT_CALL(turtle, GoTo(50, _)).Times(AtLeast(1));

    EXPECT_CALL(turtle, SomeExpensiveOpertion())
        .Times(0);
    EXPECT_CALL(turtle, GetY())
        .Times(8);

    Game game(&turtle);

    game.ChaseTurtle();

    EXPECT_EQ(game.GetDogX(), 200);
    EXPECT_EQ(game.GetMoves(), 8);


}

TEST(MockRealObject, MockCallsMock) {
    MockRealObject2 mockObject;
    EXPECT_CALL(mockObject, DoWork(_))
        .Times(2)
        .WillOnce(Return(16))
        .WillOnce(Return(32));


    EXPECT_EQ(mockObject.DoWork(2), 16);
    EXPECT_EQ(mockObject.DoWork(4), 32);


}

TEST(MockRealObject, MockCallsMock2) {
    MockRealObject2 mockObject;
    ON_CALL(mockObject, DoWork(_))
        .WillByDefault(Return(16));


    EXPECT_EQ(mockObject.DoWork(2), 16);
    EXPECT_EQ(mockObject.DoWork(4), 16);


}

TEST(MockRealObject, MockCallsReal) {
    MockRealObject mockObject;
    EXPECT_CALL(mockObject, DoWork(_))
        .Times(2);


    EXPECT_EQ(mockObject.DoWork(2), 4);
    EXPECT_EQ(mockObject.DoWork(4), 8);


}

using ::testing::InSequence;

TEST(MockTurtle, Sequences) {
    MockTurtle turtle;

    {
        InSequence s;
        
        EXPECT_CALL(turtle, GetX());
        EXPECT_CALL(turtle, GetY());
        EXPECT_CALL(turtle, GoTo(5, 13));
        EXPECT_CALL(turtle, PenDown());
    }
    Game game(&turtle);

    game.DoStuff();



}

TEST(MockTurtle, UnSequences) {
    MockTurtle turtle;

    EXPECT_CALL(turtle, PenDown());
    EXPECT_CALL(turtle, GetX());
    
    EXPECT_CALL(turtle, GoTo(5, 13));
    EXPECT_CALL(turtle, GetY());

    Game game(&turtle);

    game.DoStuff();



}
