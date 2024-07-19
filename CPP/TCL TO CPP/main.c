#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

// Mock definitions for hardware register addresses and values
#define REG_BASE_ADDR 0x40000000
#define REG_WRITE(addr, value) do { printf("Writing value 0x%X to address 0x%X\n", (value), (addr)); } while (0)
#define REG_READ(addr) (0)  // Replace with actual read implementation

// Function declarations
void reg_write(uint32_t addr, uint32_t value);
uint32_t reg_read(uint32_t addr);
double get_ber(uint32_t err_cnt, uint32_t smp_cnt);
void print_result(double measure_arr[][4], size_t size);
double get_Yoffset(double base_V, double base_ber, double curr_ber);
void print_config_scan_param(int YPAmpV, int YNAmpV, int Xoff_min, int Xoff_max, int Xoff_step, int Yoff_min, int Yoff_max, int Yoff_step, double ber_limit, const char* prbs, const char* test_type);
double get_voltage(void);
void set_eye(const char* prbs, const char* presc);
void gth_reset(void);
void do_single_scan(void);
void setYoffset(int Yoffset);
void setXoffset(int Xoffset);
int getXoffset(void);
int getYoffset(void);
void eye_scan(int Xmin, int Xmax, int Xstep, int measure_pts);
void eye_matrix_scan(int Xmin, int Xstep, int Xmax, int Ymin, int Ystep, int Ymax);
void gth_self_test(void);
void init_eye_user(const char* prbs, const char* presc);
void init_eye_default(void);
void print_config(void);
void run(void);

// Function definitions
void reg_write(uint32_t addr, uint32_t value) {
    REG_WRITE(addr + REG_BASE_ADDR, value);
}

uint32_t reg_read(uint32_t addr) {
    return REG_READ(addr + REG_BASE_ADDR);
}

double get_ber(uint32_t err_cnt, uint32_t smp_cnt) {
    if (err_cnt == 0) {
        return 1.0 / smp_cnt;
    } else if (smp_cnt == 0) {
        return 1.0;
    } else {
        return (double)err_cnt / (err_cnt + smp_cnt);
    }
}

void print_result(double measure_arr[][4], size_t size) {
    int cos = 1;
    for (size_t i = 0; i < size; i++) {
        if (cos) {
            printf("%0.2e, %0.2f, %0.2f, ", measure_arr[i][0], measure_arr[i][1], measure_arr[i][2]);
            cos = 0;
        } else {
            printf("%0.2e, %0.2e, %0.2e, %0.1f, ", measure_arr[i][0], measure_arr[i][1], measure_arr[i][2], measure_arr[i][3]);
        }
    }
    printf("\n");
}

double get_Yoffset(double base_V, double base_ber, double curr_ber) {
    return base_V * log10(curr_ber) / log10(base_ber);
}

void print_config_scan_param(int YPAmpV, int YNAmpV, int Xoff_min, int Xoff_max, int Xoff_step, int Yoff_min, int Yoff_max, int Yoff_step, double ber_limit, const char* prbs, const char* test_type) {
    printf("+Yvolatge mv, %d\n", YPAmpV);
    printf("-Yvolatge mv, %d\n", YNAmpV);
    printf("XoffsMin, %d\n", Xoff_min);
    printf("XoffsMax, %d\n", Xoff_max);
    if (Yoff_step != 0) {
        printf("YoffStep, %d\n", Yoff_step);
        printf("YoffsMin, %d\n", Yoff_min);
        printf("YoffsMax, %d\n", Yoff_max);
    } else {
        printf("Yoff, %d\n", Yoff_min);
    }
    printf("BerLimit, %0.2e\n", ber_limit);
    printf("PRBS, %s\n", prbs);
    printf("TestType, %s\n", test_type);
}

double get_voltage(void) {
    int presc = 0;
    int step = 1;
    int tmp_presc = reg_read(0x24);
    int Hoffs = (getYoffset() < 0) ? -1 : 0;
    step = (Hoffs < 0) ? -1 : 1;

    reg_write(0x00, 1);
    while (reg_read(0x04) == 0) {}

    reg_write(0x08, 1);
    reg_write(0x18, 1);

    reg_write(0x24, presc);
    double vs_range = 1.5;

    while (1) {
        setYoffset(Hoffs);
        do_single_scan();
        uint32_t err_cnt = reg_read(0x30) * (1 + pow(2, reg_read(0x24)));
        uint32_t smp_cnt = reg_read(0x34) * (1 + pow(2, reg_read(0x24)));
        gth_reset();
        if (err_cnt == 0) {
            Hoffs += step;
        } else {
            reg_write(0x24, tmp_presc);
            break;
        }
    }
    return Hoffs * vs_range;
}

void set_eye(const char* prbs, const char* presc) {
    uint32_t prbs_val = 0;
    if (strcmp(prbs, "PRBS7") == 0) {
        prbs_val = 0x01;
    } else if (strcmp(prbs, "PRBS15") == 0) {
        prbs_val = 0x02;
    } else if (strcmp(prbs, "PRBS31") == 0) {
        prbs_val = 0x03;
    } else {
        printf("Unknown PRBS type: %s\n", prbs);
        return;
    }

    uint32_t presc_val = 0;
    if (strcmp(presc, "1") == 0) {
        presc_val = 0x01;
    } else if (strcmp(presc, "2") == 0) {
        presc_val = 0x02;
    } else if (strcmp(presc, "4") == 0) {
        presc_val = 0x03;
    } else {
        printf("Unknown prescaler value: %s\n", presc);
        return;
    }

    reg_write(0x08, prbs_val);
    reg_write(0x18, 1);
    reg_write(0x1c, 0);
    reg_write(0x20, 0);
    reg_write(0x24, presc_val);

    printf("PRBS set to 0x%X, Prescaler set to 0x%X\n", prbs_val, presc_val);
}

void gth_reset(void) {
    reg_write(0x00, 1);
    while (reg_read(0x04) == 0) {}
}

void do_single_scan(void) {
    reg_write(0x28, 1);
    // Simulate a delay for scan
    for (volatile int i = 0; i < 1000; i++) {}
    reg_write(0x38, 123);
    while (reg_read(0x2c) == 0) {
        // Simulate a delay for scan
        for (volatile int i = 0; i < 1000; i++) {}
        reg_write(0x38, 123);
    }
}

void setYoffset(int Yoffset) {
    if (Yoffset > 127 || Yoffset < -127) {
        printf("setYoffset out of range\n");
        return;
    }
    if (Yoffset < 0) {
        Yoffset = (uint8_t)(-Yoffset | 0x80);
    }
    reg_write(0x1c, Yoffset);
}

void setXoffset(int Xoffset) {
    const uint32_t max_reg = 0x7ff;
    uint32_t offs = Xoffset;
    if (Xoffset < 0) {
        offs = (uint32_t)(-Xoffset - 1);
        offs = (max_reg - offs) | 0x800;
    }
    reg_write(0x20, offs);
}

int getXoffset(void) {
    const uint32_t max_reg = 0x7ff;
    uint32_t offs = reg_read(0x20);
    if (offs & 0x800) {
        offs = (max_reg - (offs & max_reg)) - 1;
        return -offs;
    }
    return (int)offs;
}

int getYoffset(void) {
    int Yoffs = reg_read(0x1c);
    if (Yoffs & 0x80) {
        return (int)(-((Yoffs & 0x7f) | 0x80));
    }
    return Yoffs;
}

void eye_scan(int Xmin, int Xmax, int Xstep, int measure_pts) {
    for (int i = Xmin; i <= Xmax; i += Xstep) {
        setXoffset(i);
        do_single_scan();
        // Call your measurement function and store results
        // Example: measure_arr[i] = get_measurements();
    }
}

void eye_matrix_scan(int Xmin, int Xstep, int Xmax, int Ymin, int Ystep, int Ymax) {
    for (int x = Xmin; x <= Xmax; x += Xstep) {
        setXoffset(x);
        for (int y = Ymin; y <= Ymax; y += Ystep) {
            setYoffset(y);
            do_single_scan();
            // Call your measurement function and store results
            // Example: measure_arr[x][y] = get_measurements();
        }
    }
}

void gth_self_test(void) {
    printf("Starting self test...\n");
    // Implement self-test logic here
}

void init_eye_user(const char* prbs, const char* presc) {
    printf("Initializing eye scan with user settings...\n");
    set_eye(prbs, presc);
    gth_reset();
}

void init_eye_default(void) {
    printf("Initializing eye scan with default settings...\n");
    set_eye("PRBS7", "1");
    gth_reset();
}

void print_config(void) {
    // Print configuration settings
}

void run(void) {
    // Placeholder for running the main operations
    printf("Running the scan...\n");
}

int main(void) {
    init_eye_default();
    run();
    return 0;
}
