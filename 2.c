#include <stdio.h>
#include <math.h>

int main() {

    //รับขนาดของเมทริก
    int n;
    printf("Size of array: ");
    scanf("%d", &n);

    double A[n][n]; 
    double L[n][n];
    double U[n][n];
    double b[n];
    double y[n];
    double x[n];

    //รับขอมูลของเมทริก
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lf", &A[i][j]);
        }
        printf("= ");
        scanf("%lf", &b[i]);
    }

    // กำหนดค่าเริ่มต้น L และ U = 0
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            L[i][j] = 0;
            U[i][j] = 0;
        }
    }

    // เริ่มกระบวนการ LU 
    for (int i = 0; i < n; i++) {

        // คำนวณ U
        for (int k = i; k < n; k++) {
            double sum = 0;
            for (int j = 0; j < i; j++)
                sum = sum + (L[i][j] * U[j][k]);

            U[i][k] = A[i][k] - sum;
        }

        // คำนวณ L
        for (int k = i; k < n; k++) {
            if (i == k)
                L[i][i] = 1;//ถ้าค่าของแถว และ คอลัม เท่ากัน จะให้ตำ่แหน่งนั่นเป็น 1
            else {
                double sum = 0;
                for (int j = 0; j < i; j++)
                    sum = sum + (L[k][j] * U[j][i]);

                L[k][i] = (A[k][i] - sum) / U[i][i];
            }
        }
    }

    // หา y จาก Ly = b
    for (int i = 0; i < n; i++) {
        double sum = 0;
        for (int j = 0; j < i; j++)
            sum = sum + (L[i][j] * y[j]); //การคูณเมทริก ปกติ

        y[i] = b[i] - sum;
    }

    // หา x จาก Ux = y
    for (int i = n - 1; i >= 0; i--) {
        double sum = 0;
        for (int j = i + 1; j < n; j++)
            sum = sum + (U[i][j] * x[j]); //การคูณเมทริก ปกติ

        x[i] = (y[i] - sum) / U[i][i];
    }

    // แสดงผลลัพธ์
    printf("\nAnswer:\n");
    for (int i = 0; i < n; i++) {
        printf("x%d = %.2f\n", i + 1, x[i]);
    }

    return 0;
}
