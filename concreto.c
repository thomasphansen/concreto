#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DENSITY_CEMENT 1440.0 // kg per cubic meter
#define DENSITY_SAND 1600.0   // kg per cubic meter
#define DENSITY_GRAVEL 1550.0 // kg per cubic meter

static double wc_ratio(double granulometry) {
    if (granulometry <= 10.0) return 0.65; // finer aggregates -> more water
    if (granulometry <= 20.0) return 0.60;
    if (granulometry <= 40.0) return 0.55;
    return 0.50;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Uso: %s <traco a-b-c> <granulometria_mm> <volume_m3>\n", argv[0]);
        return 1;
    }

    double a = 0, b = 0, c = 0;
    if (sscanf(argv[1], "%lf-%lf-%lf", &a, &b, &c) != 3 || a <= 0 || b <= 0 || c <= 0) {
        fprintf(stderr, "Formato de tra\303\247o inv\303\241lido: %s\n", argv[1]);
        return 1;
    }

    double granulometry = atof(argv[2]);
    if (granulometry <= 0) {
        fprintf(stderr, "Granulometria inv\303\241lida: %s\n", argv[2]);
        return 1;
    }

    double volume = atof(argv[3]);
    if (volume <= 0) {
        fprintf(stderr, "Volume inv\303\241lido: %s\n", argv[3]);
        return 1;
    }

    double sum_parts = a + b + c;
    double cement_vol = volume * (a / sum_parts);
    double sand_vol = volume * (b / sum_parts);
    double gravel_vol = volume * (c / sum_parts);

    double cement_mass = cement_vol * DENSITY_CEMENT;
    double sand_mass = sand_vol * DENSITY_SAND;
    double gravel_mass = gravel_vol * DENSITY_GRAVEL;

    double water_mass = cement_mass * wc_ratio(granulometry);

    printf("Cimento: %.2f kg\n", cement_mass);
    printf("Agua: %.2f kg\n", water_mass);
    printf("Areia: %.2f kg\n", sand_mass);
    printf("Brita: %.2f kg\n", gravel_mass);

    return 0;
}
