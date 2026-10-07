#include <stdio.h>
#include <math.h>

struct UnoptimizedDevice {
    int deviceID;
    float voltage;
    int status;
    double measuredPower;
    float current;
    int operatingMinutes;
};

struct OptimizedDevice {
    double measuredPower;
    float voltage;
    float current;
    int deviceID;
    int status;
    int operatingMinutes;
};

int main() {
    struct UnoptimizedDevice oldDevice;
    struct OptimizedDevice device;

    double calculatedPower;
    double difference;
    double differencePercent;
    double energyKWh;

    /* So sanh kich thuoc struct */
    printf("===== PHAN TICH MEMORY PADDING =====\n");
    printf("Size struct chua toi uu: %zu bytes\n",
           sizeof(oldDevice));

    printf("Size struct da toi uu:  %zu bytes\n",
           sizeof(device));

    printf("\n===== NHAP THONG TIN THIET BI =====\n");

    printf("Nhap ma thiet bi: ");
    scanf("%d", &device.deviceID);

    printf("Nhap dien ap U (V): ");
    scanf("%f", &device.voltage);

    printf("Nhap dong dien I (A): ");
    scanf("%f", &device.current);

    printf("Nhap cong suat do duoc P (W): ");
    scanf("%lf", &device.measuredPower);

    printf("Nhap trang thai (0-Tat, 1-Bat): ");
    scanf("%d", &device.status);

    printf("Nhap thoi gian hoat dong (phut): ");
    scanf("%d", &device.operatingMinutes);

    if (device.voltage <= 0) {
        printf("\nLOI: Dien ap phai lon hon 0!\n");
        return 0;
    }

    if (device.current < 0) {
        printf("\nLOI: Dong dien khong duoc am!\n");
        return 0;
    }

    if (device.operatingMinutes < 0) {
        printf("\nLOI: Thoi gian hoat dong khong duoc am!\n");
        return 0;
    }

    if (device.status != 0 && device.status != 1) {
        printf("\nLOI: Trang thai chi duoc la 0 hoac 1!\n");
        return 0;
    }

    calculatedPower = device.voltage * device.current;

    printf("\n===== KET QUA PHAN TICH =====\n");

    printf("Ma thiet bi: %d\n", device.deviceID);
    printf("Dien ap: %.2f V\n", device.voltage);
    printf("Dong dien: %.2f A\n", device.current);
    printf("Cong suat do duoc: %.2f W\n",
           device.measuredPower);

    printf("Cong suat tinh toan: %.2f W\n",
           calculatedPower);

    if (calculatedPower > 0) {
        difference = fabs(device.measuredPower - calculatedPower);
        differencePercent =
            (difference / calculatedPower) * 100.0;

        printf("Do sai lech: %.2f%%\n",
               differencePercent);

        if (differencePercent > 5.0) {
            printf("CANH BAO: Cam bien cong suat bao sai lech!\n");
        } else {
            printf("Cong suat cam bien nam trong gioi han cho phep.\n");
        }
    }

    if (device.current > 30.0 ||
        device.measuredPower > 6600.0) {

        printf("CANH BAO: QUA TAI NGUY HIEM!\n");

        if (device.current > 30.0) {
            printf("- Dong dien vuot qua 30.0 A.\n");
        }

        if (device.measuredPower > 6600.0) {
            printf("- Cong suat vuot qua 6600.0 W.\n");
        }
    } else {
        printf("Trang thai tai: AN TOAN.\n");
    }

    if (device.status == 0 &&
        device.current > 0.05) {

        printf("CANH BAO: RO RI DIEN HOAC TAI AN!\n");
    } else {
        printf("Khong phat hien ro ri dien.\n");
    }

    energyKWh =
        device.measuredPower *
        (device.operatingMinutes / 60.0) /
        1000.0;

    printf("\n===== DIEN NANG TIEU THU =====\n");
    printf("Thoi gian hoat dong: %d phut\n",
           device.operatingMinutes);

    printf("Dien nang tieu thu: %.4f kWh\n",
           energyKWh);

    printf("\n===== HOAN TAT =====\n");

    return 0;
}