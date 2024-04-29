#include <gtest.h>
#include "list.h"

TEST(TList, can_create_empty_list) {
	ASSERT_NO_THROW(TList<int> l);
}

TEST(TList, can_create_with_pFirst_node) {
	TNode<int>* p = new TNode<int>(5);
	ASSERT_NO_THROW(TList<int> l(p));
}

TEST(TList, can_create_copied_list) {
	TList<int> l;
	ASSERT_NO_THROW(TList<int> l2(l));
}

TEST(TList, isEmpty_return_true) {
	TList<int> l;
	ASSERT_TRUE(l.isEmpty());
}

TEST(TList, isEmpty_return_false) {
	TList<int> l;
	l.insertLast(3);
	ASSERT_FALSE(l.isEmpty());
}

TEST(TList, can_clear_list) {
	TList<int> l;
	l.insertLast(2);
	ASSERT_NO_THROW(l.clear());
}

TEST(TList, clear_makes_list_empty) {
	TList<int> l;
	l.insertLast(2);
	l.insertLast(3);
	l.clear();
	ASSERT_TRUE(l.isEmpty());
}

TEST(TList, can_search_exist_data) {
	TList<int> l;
	l.insertLast(3);
	ASSERT_NO_THROW(l.search(3));
}

TEST(TList, search_find_right_data) {
	TList<int> l;
	l.insertLast(3);
	l.insertLast(2);
	TNode<int>* p = l.search(3);
	ASSERT_EQ(p->data, 3);
}

TEST(TList, search_throw_when_data_not_exist) {
	TList<int> l;
	l.insertLast(3);
	ASSERT_ANY_THROW(l.search(2));
}

TEST(TList, can_insert_first_in_empty_list) {
	TList<int> l;
	ASSERT_NO_THROW(l.insertFirst(2));
}

TEST(TList, can_insert_first_in_filled_list) {
	TNode<int>* p = new TNode<int>(5);
	TList<int> l(p);
	ASSERT_NO_THROW(l.insertFirst(2));
}

TEST(TList, insert_first_set_element_in_first_pos) {
	TNode<int>* p = new TNode<int>(5);
	TList<int> l(p);
	l.insertFirst(1);
	EXPECT_EQ(1, l.getCurrent()->data);
}

TEST(TList, can_insert_last_in_empty_list) {
	TList<int> l;
	ASSERT_NO_THROW(l.insertLast(2));
}

TEST(TList, can_insert_last_in_filled_list) {
	TNode<int>* p = new TNode<int>(5);
	TList<int> l(p);
	ASSERT_NO_THROW(l.insertLast(2));
}

TEST(TList, insert_last_set_element_in_last_pos) {
	TNode<int>* p = new TNode<int>(1);
	TList<int> l(p);
	l.insertLast(5);
	l.next();
	EXPECT_EQ(5, l.getCurrent()->data);
}

TEST(TList, insert_after_throw_when_data_not_exist) {
	TNode<int>* p = new TNode<int>(5);
	TList<int> l(p);
	ASSERT_ANY_THROW(l.insertAfter(3, 4));
}

TEST(TList, can_insert_after_when_data_exist) {
	TList<int> l;
	l.insertLast(5);
	ASSERT_NO_THROW(l.insertAfter(3, 5));
}

TEST(TList, insert_after_set_element_in_after_pos) {
	TList<int> l;
	l.insertLast(1);
	l.insertLast(3);
	l.insertAfter(2, 1);
	EXPECT_EQ(1, l.getCurrent()->data);
	l.next();
	EXPECT_EQ(2, l.getCurrent()->data);
	l.next();
	EXPECT_EQ(3, l.getCurrent()->data);
}

TEST(TList, insert_before_throw_when_data_not_exist) {
	TNode<int>* p = new TNode<int>(5);
	TList<int> l(p);
	ASSERT_ANY_THROW(l.insertBefore(3, 4));
}

TEST(TList, can_insert_before_when_data_exist) {
	TNode<int>* p = new TNode<int>(5);
	TList<int> l(p);
	ASSERT_NO_THROW(l.insertAfter(3, 5));
}

TEST(TList, insert_before_set_element_in_before_pos) {
	TList<int> l;
	l.insertLast(1);
	l.insertLast(3);
	l.insertBefore(2, 3);
	EXPECT_EQ(1, l.getCurrent()->data);
	l.next();
	EXPECT_EQ(2, l.getCurrent()->data);
	l.next();
	EXPECT_EQ(3, l.getCurrent()->data);
}

TEST(TList, can_remove_element) {
	TNode<int>* p = new TNode<int>(5);
	TList<int> l(p);
	ASSERT_NO_THROW(l.remove(5));
}

TEST(TList, remove_throw_when_dana_not_exist) {
	TNode<int>* p = new TNode<int>(5);
	TList<int> l(p);
	ASSERT_ANY_THROW(l.remove(4));
}

TEST(TList, remove_throw_when_list_empty) {
	TList<int> l;
	ASSERT_ANY_THROW(l.remove(4));
}

TEST(TList, can_get_size) {
	TList<int> l;
	l.insertLast(1);
	l.insertLast(2);
	l.insertLast(3);
	EXPECT_EQ(l.getSize(), 3);
}

TEST(TList, can_get_current_elemet){
	TList<int> l;
	l.insertLast(1);
	EXPECT_EQ(l.getCurrent()->data, 1);
}

TEST(TList, can_get_next) {
	TList<int> l;
	l.insertLast(1);
	l.insertLast(2);
	l.next();
	EXPECT_EQ(l.getCurrent()->data, 2);
}

TEST(TList, can_reset) {
	TList<int> l;
	l.insertLast(1);
	l.insertLast(2);
	l.next();
	l.reset();
	EXPECT_EQ(l.getCurrent()->data, 1);
}

TEST(TList, can_descending_insert_insert_into_empty_list) {
	TList<int> l;
	ASSERT_NO_THROW(l.descendingInsert(1));
}

TEST(TList, descending_insert_is_correct) {
	TList<int> l;
	l.descendingInsert(2);
	l.descendingInsert(3);
	l.descendingInsert(1);
	EXPECT_EQ(3, l.getCurrent()->data);
	l.next();
	EXPECT_EQ(2, l.getCurrent()->data);
	l.next();
	EXPECT_EQ(1, l.getCurrent()->data);
}