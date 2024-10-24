#include "src/sum.h"
#include "/var/lib/gems/3.0.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"








void test_sum_positive_numbers(void)

{

    UnityAssertEqualNumber((UNITY_INT)((5)), (UNITY_INT)((sum(2,3))), (

   ((void *)0)

   ), (UNITY_UINT)(9), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((10)), (UNITY_INT)((sum(5,5))), (

   ((void *)0)

   ), (UNITY_UINT)(10), UNITY_DISPLAY_STYLE_INT);

}



void test_sum_negative_numbers(void)

{

    UnityAssertEqualNumber((UNITY_INT)((-1)), (UNITY_INT)((sum(-1,0))), (

   ((void *)0)

   ), (UNITY_UINT)(15), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((-5)), (UNITY_INT)((sum(-5,0))), (

   ((void *)0)

   ), (UNITY_UINT)(16), UNITY_DISPLAY_STYLE_INT);

}



void test_sum_zero(void)

{

    UnityAssertEqualNumber((UNITY_INT)((5)), (UNITY_INT)((sum(5,0))), (

   ((void *)0)

   ), (UNITY_UINT)(21), UNITY_DISPLAY_STYLE_INT);

}
