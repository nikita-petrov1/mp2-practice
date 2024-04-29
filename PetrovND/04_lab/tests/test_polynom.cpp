#include <gtest.h>
#include "polynom.h"

const std::string str{ "2*x-y*z+z" };

TEST(TPolynom, create_empty_polinom)
{
	ASSERT_NO_THROW(TPolynom p());
}

TEST(TPolynom, create_polinom)
{
	ASSERT_NO_THROW(TPolynom p(str));
}

TEST(TPolynom, can_create_copied_polinom)
{
	TPolynom p1(str);
	ASSERT_NO_THROW(TPolynom p2(p1));
}

TEST(TPolynom, equality_operator_is_correct)
{
	TPolynom p1(str);
	TPolynom p2(str);

	EXPECT_EQ(p1, p2);
}

TEST(TPolynom, copied_polinom_is_eq)
{
	TPolynom p1(str);
	TPolynom p2(p1);
	EXPECT_EQ(p1, p2);
}

TEST(TPolynom, no_throw_when_polynom_will_be_empty)
{
	ASSERT_NO_THROW(TPolynom p("x-x+y-y+z-z"));
}

TEST(TPolynom, collecting_terms_test) {
	TPolynom p1("x+x-x+x+y+y+z+z+z");
	TPolynom p2("2*x+2*y+3*z");
	EXPECT_EQ(p1, p2);
}

TEST(TPolynom, collecting_terms_to_zero) {
	TPolynom p1("x+x-x-x+y-y");
	TPolynom p2("0");
	EXPECT_EQ(p1, p2);
}

TEST(TPolynom, conversation_test) {
	TPolynom p1("x+x-x+x+y+y+z+z+z");
	TPolynom p2("2*x+2*y+3*z");

	EXPECT_EQ(p1, p2);
}

TEST(TPolynom, can_create_polynom_in_different_order)
{
	TPolynom p("x+y+z");
	TPolynom p_reordered("z+y+x");

	EXPECT_EQ(p, p_reordered);
}

TEST(TPolynom, can_create_polynom_with_negative_coefficient)
{
	ASSERT_NO_THROW(TPolynom p("-10*x^4"));
}

TEST(TPolynom, calculate_is_correct1)
{
	TPolynom pol(str);
	double res = pol(1, 2, 3);
	EXPECT_EQ(-1, res);
}

TEST(TPolynom, calculate_is_correct2)
{
	TPolynom pol("x^3*z+x^2+y+y+1");
	double res = pol(0.9, 0.2, 0.7);
	ASSERT_NEAR(2.7203, res, 0.001f);
}

TEST(TPolynom, calculate_is_correct3)
{
	TPolynom p("5");
	EXPECT_EQ(p(0, 0, 0), 5);
}

TEST(TPolynom, calculate_is_correct4)
{
	TPolynom pol("x+x^2+y+x+1");
	double res = pol(1, 2, 3);
	EXPECT_EQ(6, pol(1, 2, 3));
}

TEST(TPolynom, dx_is_correct)
{
	TPolynom pol("5*x^4+x^2+y+z+1");
	TPolynom tmp("20*x^3+2x^1");
	EXPECT_EQ(pol.dx(), tmp);
}

TEST(TPolynom, dy_is_correct)
{
	TPolynom pol("y^3+y^2+x+z+1");
	TPolynom tmp("3y^2+2y^1");
	EXPECT_EQ(pol.dy(), tmp);
}

TEST(TPolynom, dz_is_correct)
{
	TPolynom pol("z^3+z^2+y+x+1");
	TPolynom tmp("3z^2+2z^1");
	EXPECT_EQ(pol.dz(), tmp);
}

TEST(TPolynom, empty_dx)
{
	TPolynom pol("z+y*z");
	TPolynom tmp("0");
	EXPECT_EQ(pol.dx(), tmp);
}

TEST(TPolynom, empty_dy)
{
	TPolynom pol("z*x^4+z");
	TPolynom tmp("0");
	EXPECT_EQ(pol.dy(), tmp);
}

TEST(TPolynom, empty_dz)
{
	TPolynom pol("3*y+2*x^2+0*z");
	TPolynom tmp("0");
	EXPECT_EQ(pol.dz(), tmp);
}

TEST(TPolynom, sum_is_correct)
{
	TPolynom pol1("x^3+y^2+y+x+1");
	TPolynom pol2("x^3+y+z+1");
	TPolynom pol3("2x^3+y^2+2y+x+2+z");
	EXPECT_EQ(pol1 + pol2, pol3);
}

TEST(TPolynom, empty_sum)
{
	TPolynom pol1("x^3-y^2+4");
	TPolynom pol2("-x^3+y^2-4");
	TPolynom pol3("0");
	EXPECT_EQ(pol1 + pol2, pol3);
}

TEST(TPolynom, diff_is_correct)
{
	TPolynom pol1("2*x^3+y^2+y+x");
	TPolynom pol2("x^3-2y^2+z");
	TPolynom pol3("x^3+3*y^2+y^1+x-z");
	EXPECT_EQ(pol1 - pol2, pol3);
}

TEST(TPolynom, empty_diff)
{
	TPolynom p1("-3*x^2-2*y+5");
	TPolynom p2("-3*x^2-4*y+2*y+5");
	TPolynom p3("0");
	EXPECT_EQ(p1 - p2, p3);
}

TEST(TPolynom, mult_is_correct1)
{
	TPolynom pol1("x^2+y");
	TPolynom pol2("x^3+x");
	TPolynom pol3("x^5+x^3+x^3*y+x*y");

	EXPECT_EQ(pol1 * pol2, pol3);
}

TEST(TPolynom, mult_by_zero)
{
	TPolynom pol1("x^2+y");
	TPolynom pol2("0");
	TPolynom pol3("0");
	EXPECT_EQ(pol1 * pol2, pol3);
}