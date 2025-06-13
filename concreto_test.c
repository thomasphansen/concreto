#include <assert.h>
#include <math.h>
#include "concreto.h"

static void test_parse_ratio_valid() {
    MixRatio r;
    assert(parse_ratio("1-2-3", &r));
    assert(fabs(r.cement - 1.0) < 1e-6);
    assert(fabs(r.sand - 2.0) < 1e-6);
    assert(fabs(r.gravel - 3.0) < 1e-6);
}

static void test_parse_ratio_invalid() {
    MixRatio r;
    assert(!parse_ratio("1-2", &r));
    assert(!parse_ratio("a-b-c", &r));
}

static void test_wc_ratio() {
    assert(fabs(wc_ratio(5.0) - 0.65) < 1e-6);
    assert(fabs(wc_ratio(15.0) - 0.60) < 1e-6);
    assert(fabs(wc_ratio(30.0) - 0.55) < 1e-6);
    assert(fabs(wc_ratio(50.0) - 0.50) < 1e-6);
}

static void test_compute_volumes() {
    MixRatio r = {1, 2, 3};
    Volumes v = compute_volumes(6.0, r);
    assert(fabs(v.cement - 1.0) < 1e-6);
    assert(fabs(v.sand - 2.0) < 1e-6);
    assert(fabs(v.gravel - 3.0) < 1e-6);
}

static void test_compute_masses() {
    Volumes v = {1, 2, 3};
    Masses m = compute_masses(v, 20.0); /* wc_ratio -> 0.60 */
    assert(fabs(m.cement - 1440.0) < 1e-6);
    assert(fabs(m.sand - 3200.0) < 1e-6);
    assert(fabs(m.gravel - 4650.0) < 1e-6);
    assert(fabs(m.water - 864.0) < 1e-6);
}

int main(void) {
    test_parse_ratio_valid();
    test_parse_ratio_invalid();
    test_wc_ratio();
    test_compute_volumes();
    test_compute_masses();
    return 0;
}
