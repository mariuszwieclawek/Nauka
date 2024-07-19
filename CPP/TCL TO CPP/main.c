#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h> // For usleep()

// Define some hardware-specific constants
#define REG_BASE_ADDR 0x40000000
#define REG_READ(addr) (*(volatile uint32_t *)(REG_BASE_ADDR + (addr)))
#define REG_WRITE(addr, value) (*(volatile uint32_t *)(REG_BASE_ADDR + (addr)) = (value))

// Constants
#define DEFAULT_Y_AMP_VP 180
#define DEFAULT_Y_AMP_VN -179

// Global variables
static int g_YAmpVP = DEFAULT_Y_AMP_VP;
static int g_YAmpVN = DEFAULT_Y_AMP_VN;
static double g_berLimit = 1e-2;
static FILE *g_fileId;
static char g_filepath[256];
static char g_filename[64];

// Bit Error Rate Calculation
double get_ber(uint32_t err_cnt, uint32_t smp_cnt) {
    if (smp_cnt == 0) return 1.0; // Avoid division by zero
    return (double)err_cnt / smp_cnt;
}

// Print results to the file
void print_result(double** measure, int measure_pts) {
    if (g_fileId) {
        fprintf(g_fileId, "Xoffset,Yoffset,BER\n");
        for (int i = 0; i < measure_pts; i++) {
            fprintf(g_fileId, "%.2f,%.2f,%.4f\n", measure[i][0], measure[i][1], measure[i][2]);
        }
        fflush(g_fileId);
    }
}

// Utility functions (placeholders)
int getVolt(const char* type) {
    return strcmp(type, "POS") == 0 ? g_YAmpVP : g_YAmpVN;
}

const char* get_prbs_string(void) {
    return "PRBS7"; // Placeholder
}

// Register read/write functions
uint32_t reg_read(uint32_t addr) {
    return REG_READ(addr);
}

void reg_write(uint32_t addr, uint32_t value) {
    REG_WRITE(addr, value);
}

// Set Yoffset value
void setYoffset(int Yoffset) {
    if (Yoffset > 127 || Yoffset < -127) {
        printf("setYoffset out of range\n");
        return;
    }
    if (Yoffset < 0) {
        Yoffset = (Yoffset * -1) | 0x80;
    }
    reg_write(0x1c, Yoffset);
}

// Set Xoffset value
void setXoffset(int Xoffset) {
    const int max_reg = 0x7ff;
    int offs = Xoffset;
    if (Xoffset < 0) {
        offs = -Xoffset;
        offs--;
        offs = (max_reg - offs) | 0x800;
    }
    reg_write(0x20, offs);
}

// Get Xoffset value
int getXoffset(void) {
    const int max_reg = 0x7ff;
    int offs = reg_read(0x20);
    if (offs & 0x800) {
        offs = max_reg - (offs & max_reg);
        offs--;
        offs = -offs;
    }
    return offs;
}

// Get Yoffset value
int getYoffset(void) {
    const int max_reg = 0x7f;
    int reg_val = reg_read(0x1c);
    if (reg_val & (1 << 7)) {
        reg_val *= -1;
    }
    return reg_val;
}

// Reset GTH
void gth_reset(void) {
    reg_write(0x40000000, 1);
    while (reg_read(0x04) == 0) {
        usleep(1000); // Wait 1 ms
    }
}

// Perform a single scan
void do_single_scan(void) {
    reg_write(0x28, 1);
    usleep(1000); // Wait 1 ms
    reg_write(0x38, 123);
    while (reg_read(0x2c) == 0) {
        usleep(1000); // Wait 1 ms
        reg_write(0x38, 123);
    }
}

// Perform an eye scan
void eye_scan(int Xmin, int Xmax, int Xstep, int measure_pts) {
    double** measure = (double**)malloc(measure_pts * sizeof(double*));
    for (int i = 0; i < measure_pts; i++) {
        measure[i] = (double*)malloc(4 * sizeof(double));
    }

    int Xoffset = Xmin;
    uint32_t err_cnt, smp_cnt;
    double min_ber, max_ber, curr_ber;
    double ber_delta_limit = 0.5;
    int nmb_of_reapets_lim = 5;
    int nmb_of_reapets = 0;
    int repeated = 0;

    while (Xoffset < Xmax) {
        int measure_cnt = 1;
        min_ber = 1.0;
        max_ber = 0.0;
        while (measure_cnt < measure_pts) {
            if (measure_cnt == 0) {
                for (int i = 0; i < 3; i++) {
                    measure[i][0] = Xoffset;
                    measure[i][1] = getYoffset();
                    measure[i][2] = measure_pts;
                }
            }

            setXoffset(Xoffset);
            do_single_scan();
            err_cnt = reg_read(0x30);
            smp_cnt = reg_read(0x34);
            gth_reset();
            curr_ber = get_ber(err_cnt, smp_cnt);
            measure[measure_cnt][0] = err_cnt;
            measure[measure_cnt][1] = smp_cnt;
            measure[measure_cnt][2] = curr_ber;
            measure[measure_cnt][3] = getYoffset(); // Placeholder

            if (max_ber < curr_ber) {
                max_ber = curr_ber;
            }
            if (min_ber > curr_ber) {
                min_ber = curr_ber;
            }
            measure_cnt++;
        }

        print_result(measure, measure_pts);

        if (nmb_of_reapets == 0) {
            double ber_delta;
            if (max_ber != min_ber) {
                ber_delta = fabs(log10(min_ber) - log10(max_ber));
            } else {
                ber_delta = 0;
            }
            if (ber_delta > ber_delta_limit && measure_pts > 1 && repeated == 0) {
                nmb_of_reapets = (int)round(ber_delta / ber_delta_limit);
                if (nmb_of_reapets > nmb_of_reapets_lim) {
                    nmb_of_reapets = nmb_of_reapets_lim;
                }
                printf("Repeats: %d Delta: %lf ber delta\n", nmb_of_reapets, ber_delta);
            } else {
                Xoffset += Xstep;
                repeated = 0;
            }
        } else {
            nmb_of_reapets--;
            repeated = 1;
        }
    }

    for (int i = 0; i < measure_pts; i++) {
        free(measure[i]);
    }
    free(measure);
}

// Perform an eye matrix scan
void eye_matrix_scan(int Xmin, int Xstep, int Xmax, int Ymin, int Ystep, int Ymax) {
    if (Xmax < Xmin) {
        printf("Xmax must be > Xmin\n");
        return;
    }
    if (Ymax < Ymin) {
        printf("Ymax must be > Ymin\n");
        return;
    }

    snprintf(g_filename, sizeof(g_filename), "TrenzOutScan_%s.txt", __DATE__);
    snprintf(g_filepath, sizeof(g_filepath), "C:\\Users\\ST8782\\Documents\\vitis\\Test2\\app_component\\_ide\\psinit\\%s", g_filename);
    g_fileId = fopen(g_filepath, "w");
    if (g_fileId == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fprintf(g_fileId, "Config scan parameters\n");
    fprintf(g_fileId, "Xmin: %d, Xmax: %d, Xstep: %d, Ymin: %d, Ymax: %d, Ystep: %d\n", Xmin, Xmax, Xstep, Ymin, Ymax, Ystep);
    fprintf(g_fileId, "BER limit: %f\n", g_berLimit);
    fprintf(g_fileId, "PRBS string: %s\n", get_prbs_string());

    for (int y = Ymin; y <= Ymax; y += Ystep) {
        setYoffset(y);
        eye_scan(Xmin, Xmax, Xstep, 5);
    }

    fclose(g_fileId);
}

// Initialize eye with default parameters
void init_eye_default(void) {
    set_eye("PRBS7", "10");
    print_config();
}

// Initialize eye with user parameters
void init_eye_user(const char* prbs, const char* presc) {
    set_eye(prbs, presc);
    print_config();
}

// Print configuration details
void print_config(void) {
    g_YAmpVP = getVolt("POS");
    g_YAmpVN = getVolt("NEG");

    g_berLimit = get_ber(0, 65535 * (1 + (1 << reg_read(0x24))));

    printf("Yoffset is set to %d\n", getYoffset());
    printf("Xoffset is set to %d\n", getXoffset());
    printf("PRBS is set to %s\n", get_prbs_string());
    printf("BER limit is %s\n", g_berLimit);
    printf("voltage %d %d mv\n", g_YAmpVP, g_YAmpVN);
}

// Perform GTH self-test
void gth_self_test(void) {
    printf("LINK TEST\n");

    set_eye("PRBS7", "1");
    do_single_scan();

    uint32_t err_cnt = reg_read(0x30);
    uint32_t smp_cnt = reg_read(0x34);

    double curr_ber = get_ber(err_cnt, smp_cnt);

    if (curr_ber < 1e-2) {
        printf("LINK TEST: OK!\n");
    } else {
        printf("LINK TEST: BAD LINK\n");
    }
}

// Run the test
void run(void) {
    init_eye_default();
    gth_self_test();
    eye_matrix_scan(-1, 1, 1, -1, 1, 1);
}

// Main function
int main(void) {
    run();
    return 0;
}
