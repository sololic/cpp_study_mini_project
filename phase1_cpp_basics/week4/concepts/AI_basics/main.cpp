#include "operators.h"
#include "control_flow.h"

int main() {
    // ── 연산자 심화 ──
    op_integer_division();
    op_increment();
    op_ternary();
    op_bitwise();

    // ── 조건문 & 반복문 ──
    cf_switch();
    cf_do_while();
    cf_break_continue();

    return 0;
}
