#include "classes.h"
#include "inheritance.h"
#include "polymorphism.h"

int main() {
    // ── 클래스 기초 ──
    cls_basic();
    cls_constructor();
    cls_access();
    cls_this();

    // ── 상속 ──
    inh_basic();
    inh_access();
    inh_constructor_order();

    // ── 다형성 ──
    poly_virtual();
    poly_override();
    poly_pure_virtual();

    return 0;
}
