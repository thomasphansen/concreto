#ifndef CONCRETO_H
#define CONCRETO_H

#ifdef __cplusplus
extern "C" {
#endif

#define DENSITY_CEMENT 1440.0
#define DENSITY_SAND 1600.0
#define DENSITY_GRAVEL 1550.0
#define DENSITY_WATER 1000.0

typedef struct {
    double cement;
    double sand;
    double gravel;
} MixRatio;

typedef struct {
    double cement;
    double sand;
    double gravel;
} Volumes;

typedef struct {
    double cement;
    double sand;
    double gravel;
    double water;
} Masses;

int parse_ratio(const char *str, MixRatio *ratio);
double wc_ratio(double granulometry);
Volumes compute_volumes(double total_volume, MixRatio ratio);
Masses compute_masses(Volumes volumes, double granulometry);

#ifdef __cplusplus
}
#endif

#endif // CONCRETO_H
