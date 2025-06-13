#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "concreto.h"

int parse_ratio(const char *str, MixRatio *ratio) {
    double a = 0, b = 0, c = 0;
    if (sscanf(str, "%lf-%lf-%lf", &a, &b, &c) != 3 || a <= 0 || b <= 0 || c <= 0)
        return 0;
    ratio->cement = a;
    ratio->sand = b;
    ratio->gravel = c;
    return 1;
}

double wc_ratio(double granulometry) {
    if (granulometry <= 10.0) return 0.65;
    if (granulometry <= 20.0) return 0.60;
    if (granulometry <= 40.0) return 0.55;
    return 0.50;
}

Volumes compute_volumes(double total_volume, MixRatio ratio) {
    double sum = ratio.cement + ratio.sand + ratio.gravel;
    Volumes v;
    v.cement = total_volume * (ratio.cement / sum);
    v.sand = total_volume * (ratio.sand / sum);
    v.gravel = total_volume * (ratio.gravel / sum);
    return v;
}

Masses compute_masses(Volumes volumes, double granulometry) {
    Masses m;
    m.cement = volumes.cement * DENSITY_CEMENT;
    m.sand = volumes.sand * DENSITY_SAND;
    m.gravel = volumes.gravel * DENSITY_GRAVEL;
    m.water = m.cement * wc_ratio(granulometry);
    return m;
}

#if !defined(UNIT_TEST) && !defined(WITHOUT_MAIN)
int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Uso: %s <traco a-b-c> <granulometria_mm> <volume_m3>\n", argv[0]);
        return 1;
    }

    MixRatio ratio;
    if (!parse_ratio(argv[1], &ratio)) {
        fprintf(stderr, "Formato de tra\xC3\xA7o inv\xC3\xA1lido: %s\n", argv[1]);
        return 1;
    }

    double granulometry = atof(argv[2]);
    if (granulometry <= 0) {
        fprintf(stderr, "Granulometria inv\xC3\xA1lida: %s\n", argv[2]);
        return 1;
    }

    double volume = atof(argv[3]);
    if (volume <= 0) {
        fprintf(stderr, "Volume inv\xC3\xA1lido: %s\n", argv[3]);
        return 1;
    }

    Volumes vols = compute_volumes(volume, ratio);
    Masses masses = compute_masses(vols, granulometry);

    double water_vol = masses.water / DENSITY_WATER;

    printf("Cimento: %.2f kg (%.2f L)\n", masses.cement, vols.cement * 1000.0);
    printf("Agua: %.2f kg (%.2f L)\n", masses.water, water_vol * 1000.0);
    printf("Areia: %.2f kg (%.2f L)\n", masses.sand, vols.sand * 1000.0);
    printf("Brita: %.2f kg (%.2f L)\n", masses.gravel, vols.gravel * 1000.0);

    return 0;
}
#endif
