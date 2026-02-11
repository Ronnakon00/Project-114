#include <stdio.h>
#include <math.h>

int main() {

    //รับขนาดของเมทริก
    int n;
    printf("Size of array: ");
    scanf("%d", &n);

    double mat[n][n + 1];
    double answer[n];

    //รับขอมูลของเมทริก
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lf", &mat[i][j]); 
        }
        printf("= ");
        scanf("%lf", &mat[i][n]);     
    }

    // เริ่มกระบวนการ Gauss Elimination with Pivoting
    for (int i = 0; i < n; i++) {
        
        //หาแถวที่มีค่าสัมบูรณ์มากที่สุดในคอลัมน์ i เก็บค่ามากสุดไว้ใน pivotRow
        int pivotRow = i;
        for (int k = i + 1; k < n; k++) {
            if (fabs(mat[k][i]) > fabs(mat[pivotRow][i])) {
                pivotRow = k; 
            }
        }

        // สลับแถวปัจจุบันกับแถว pivotRow (ใช้ double สำหรับ temp)
        for (int k = i; k <= n; k++) {
            double temp = mat[i][k];
            mat[i][k] = mat[pivotRow][k];
            mat[pivotRow][k] = temp;
        }

        //กำจัดตัวเลขใต้ Pivot ให้เป็น 0
        for (int j = i + 1; j < n; j++) {
            double factor = mat[j][i] / mat[i][i]; //หาตัวที่สามารถ
            for (int k = i; k <= n; k++) {
                mat[j][k] = mat[j][k] - (factor * mat[i][k]);
            }
        }
    }

    //คำนวณหาค่า x จากล่างขึ้นบน
    for (int i = n - 1; i >= 0; i--) {// ไล่จากแถวล่างขึ้นบน
        answer[i] = mat[i][n];
        for (int j = i + 1; j < n; j++) {// ไล่ตัวแปรทางขวาที่รู้ค่าแล้ว
            answer[i] = answer[i] - (mat[i][j] * answer[j]);
        }
        answer[i] /= mat[i][i];// หารด้วยสัมประสิทธิ์ตัวหน้าสุดเพื่อให้ได้ค่าตัวแปรนั้นจริงๆ
    }

    //แสดงคำตอบ
    printf("\nAnswer:\n");
    for (int i = 0; i < n; i++) {
        printf("x%d = %.2f\n", i + 1, answer[i]);
    }

    return 0;
}