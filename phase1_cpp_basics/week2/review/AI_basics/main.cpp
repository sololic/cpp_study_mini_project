#include "references_review.h"
#include "pointers_review.h"
#include "vectors_review.h"

int main() {
    // ── 참조 복습 ──
    ref_basic();
    ref_const();
    ref_vs_copy();
    ref_in_function();

    // ── 포인터 복습 ──
    ptr_basic();
    ptr_nullptr();
    ptr_vs_ref();
    ptr_const();

    // ── 동적배열 복습 ──
    vec_basic();
    vec_loop();
    vec_modify();
    vec_2d();

    return 0;
}
