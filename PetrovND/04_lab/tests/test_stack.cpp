#include <gtest.h>
#include "stack.h"

class StackTest :public::testing::Test {
protected:
    Stack<int> st;
    void resize(int step = 10) { st.resize(); }
    int maxSize() { return st.maxSize; }
};

TEST_F(StackTest, resize) {
    StackTest::resize();
    EXPECT_EQ(StackTest::maxSize(), 20);
}

TEST(Stack, create_stack)
{
    ASSERT_NO_THROW(Stack<int> s(3));
}

TEST(Stack, cant_create_stack_with_zero_length)
{
    ASSERT_ANY_THROW(Stack<int> s(0));
}

TEST(Stack, cant_create_stack_with_negative_length)
{
    ASSERT_ANY_THROW(Stack<int> s(-2));
}

TEST(Stack, copy_constructor_test)
{
    Stack<int> s(3);
    ASSERT_NO_THROW(Stack<int> s2(s));
}

TEST(Stack, copied_stack_is_equal_to_source)
{
    Stack<int> s1(3);
    s1.push(1);
    s1.push(2);
    s1.push(3);

    Stack<int> s2(s1);
    EXPECT_EQ(s2, s1);
}

TEST(Stack, copy_constructor_test_memory)
{
    Stack<int> s1(3);
    s1.push(1);
    s1.push(2);
    s1.push(3);

    Stack<int> s2(s1);
    s2.pop();
    s2.push(4);

    EXPECT_NE(s2.top(), s1.top());
}

TEST(Stack, assignment_perator_test)
{
    Stack<int> s1(3);
    s1.push(1);
    s1.push(2);
    s1.push(3);

    Stack<int> s2;
    s2 = s1;

    EXPECT_EQ(s1, s2);
}

TEST(Stack, assignment_operator_memory_test)
{
    Stack<int> s1(3);
    s1.push(1);
    s1.push(2);
    s1.push(3);

    Stack<int> s2 = s1;
    s2.pop();
    s2.push(4);

    EXPECT_NE(s2.top(), s1.top());
}

TEST(Stack, equality_operator_true)
{
    Stack<int> stack1;
    stack1.push(1);
    stack1.push(2);
    stack1.push(3);

    Stack<int> stack2;
    stack2.push(1);
    stack2.push(2);
    stack2.push(3);

    ASSERT_TRUE(stack1 == stack2);
}

TEST(Stack, equality_operator_false)
{
    Stack<int> stack1;
    stack1.push(1);
    stack1.push(2);
    stack1.push(3);

    Stack<int> stack3;
    stack3.push(4);
    stack3.push(5);

    ASSERT_FALSE(stack1 == stack3);
}

TEST(Stack, stack_is_empty_true)
{
    Stack<int> s(3);
    EXPECT_EQ(1,s.isEmpty());
}

TEST(Stack, stack_is_empty_false)
{
    Stack<int> s(3);
    s.push(1);
    EXPECT_EQ(0, s.isEmpty());
}

TEST(Stack, stack_is_full_false)
{
    Stack<int> s(3);
    s.push(1);
    EXPECT_EQ(0, s.isFull());
}

TEST(Stack, stack_is_full_true)
{
    Stack<int> s(3);
    for (int i = 0; i < 3; i++)
        s.push(i);
    EXPECT_EQ(1, s.isFull());
}

TEST(Stack, can_pop_elements)
{
	Stack<int> st(2);
	st.push(100);
	st.push(42);
	st.pop();
	EXPECT_EQ(100, st.top());
}

TEST(Stack, can_get_top)
{
    Stack<int> st(2);
	st.push(100);
	st.push(42);
    EXPECT_EQ(42, st.top());
}

TEST(Stack, throws_when_top_element_is_empty) 
{
	Stack<int> st(1);
	ASSERT_ANY_THROW(st.top());
}

TEST(Stack, throws_when_pop_element_is_empty) 
{
	Stack<int> st(1);
	ASSERT_ANY_THROW(st.pop());
}

TEST(Stack, resize_works)
{
    Stack<int> s1(2);
    s1.push(1);
    s1.push(2);
    EXPECT_NO_THROW(s1.push(3));
}

