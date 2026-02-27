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

        // สลับแถวปัจจุบันกับแถว pivotRow 
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
        answer[i] = answer[i] / mat[i][i];// หารด้วยสัมประสิทธิ์ตัวหน้าสุดเพื่อให้ได้ค่าตัวแปรนั้นจริงๆ
    }

    //แสดงคำตอบ
    printf("\nAnswer:\n");
    for (int i = 0; i < n; i++) {
        printf("x%d = %.2f\n", i + 1, answer[i]);
    }

    return 0;
}
###########################################################################################################################
#include <stdio.h>
#include <math.h> // ต้องใช้สำหรับฟังก์ชัน fabs

void gaussJordanSolver() {
    int n, i, j, k, mode;
    float a[10][11], ratio;
//------------------รับInput------------------------
    printf("\n--- Gauss-Jordan Elimination ---\n");
    printf("Enter number of variables (n): ");
    scanf("%d", &n);//เก็บเข้าตัวแปร n ว่ามี x(1,2,3,..) กี่ตัว

    printf("Select Input Mode:\n");
    printf("1. Equation Form (e.g., 2x + 3y = 5)\n");
    printf("2. Matrix Form (e.g., Row 1 Col 1)\n");
    printf("Choice: ");
    scanf("%d", &mode);//เลือกเป็น matrix เลยหรือว่า เป็นสมการ

    printf("\nEnter Data:\n");
    for (i = 0; i < n; i++) {
        printf("--- Row %d ---\n", i + 1);
        for (j = 0; j < n; j++) {
            if (mode == 1)
                printf("Coefficient of x%d: ", j + 1);//เก็บพจน์(ตัวเลข)ข้างหน้าตัวแปรเป็นแบบสมการให้เข้าอาเรย์ของ a ตำแหน่งที่ j ของ i
            else
                printf("A[%d][%d]: ", i + 1, j + 1);//แสดงเก็ยแบบ maxtrix ตรงๆเลย
            scanf("%f", &a[i][j]);
        }
        if (mode == 1)
            printf("Constant value (Right side): ");//ถ้าเป็นสมการใช้ ใส่คำตอบด้านซ้ายด้วย
        else
            printf("B[%d]: ", i + 1); //จากรูปแบบสมการเชิงเส้น AX=B Bในที่นี้จะเป็นคำตอบของAX(matrix นี้) 
        scanf("%f", &a[i][n]);
    }

    for (i = 0; i < n; i++) {
        if (a[i][i] == 0.0) {
            printf("Error: Zero pivot detected.\n");//หารด้วย 0 ไม่ได้
            return;
        }

        for (j = 0; j < n; j++) {
            if (i != j) {//ตัวตั้งไม่หารตัวเอง
                ratio = a[j][i] / a[i][i];//อ่านไปทีละrow เก็บ ratioไว้ (ตัวที่จะกำจัด/ตัวตั้ง) เช่น6/2=>ratio = 3
                for (k = 0; k < n + 1; k++) {
                    a[j][k] = a[j][k] - ratio * a[i][k];//k วิ่งไปทีละ col ต้องเปลี่ยนค่าทั้ง col จนถึง B
                }                                     //ค่าเดิม(ตัวที่ต้องจำกัด) - ratio*ตัวตั้ง จัวที่จะกำจัด 0 เช่น 6-3(2)
            }
        }
    }

    for (i = 0; i < n; i++) {
        a[i][n] = a[i][n] / a[i][i];//คำตอบ = a[i][n](คำตอบB) / a[i][i]ทแยง
        a[i][i] = 1;
    }

    printf("\n--- Solution ---\n");
    for (i = 0; i < n; i++) {
        printf("x%d = %.4f\n", i + 1, a[i][n]);
    }
}

void inverseMatrixSolver() {
    int n, i, j, k, mode, findX;
    float a[10][20], b[10], x[10], ratio, sum, temp, pivotVal;
    int pivotRow;

    printf("\n--- Inverse Matrix Method ---\n");
    printf("Enter number of variables (n): ");
    scanf("%d", &n);

    printf("Select Input Mode for Matrix A:\n");
    printf("1. Equation Coefficients\n");
    printf("2. Matrix Elements\n");
    printf("Choice: ");
    scanf("%d", &mode);

    printf("\nEnter Matrix A (Coefficients):\n");
    for (i = 0; i < n; i++) {
        printf("--- Row %d ---\n", i + 1);
        for (j = 0; j < n; j++) {
            if (mode == 1)
                printf("Coefficient of x%d: ", j + 1);
            else
                printf("A[%d][%d]: ", i + 1, j + 1);
            scanf("%f", &a[i][j]);
        }
    }

    printf("\nDo you want to find the solution for X (Ax = b)?\n");
    printf("1. Find Inverse & Solution)\n");
    printf("2. Find Inverse ONLY\n");
    printf("Choice: ");
    scanf("%d", &findX);

    if (findX == 1) {
        printf("\nEnter Vector B (Constants):\n");
        for (i = 0; i < n; i++) {
            if (mode == 1)
                printf("Constant for equation %d: ", i + 1);
            else
                printf("b[%d]: ", i + 1);
            scanf("%f", &b[i]);
        }
    }
    //สร้างเมทริกซ์เอกลักษณ์ ต่อจาก n หรือ A ( A|I )
    for (i = 0; i < n; i++) {
        for (j = n; j < 2 * n; j++) {
            if (j == i + n) a[i][j] = 1.0;//เส้นทแยงลง =1 ถ้าไม่ = 0
            else a[i][j] = 0.0;
        }
    }

    for (i = 0; i < n; i++) {
        pivotRow = i;
        for (k = i + 1; k < n; k++) {
            if (fabs(a[k][i]) > fabs(a[pivotRow][i])) {//fabsคือค่าสมบูรณ์ หาfabsที่มากที่สุด
                pivotRow = k;
            }
        }

        if (fabs(a[pivotRow][i]) < 0.000001) {//ค่าสมบูรณ์ใกล้เคียง 0 มากๆ
            printf("\nError: Matrix is Singular (Determinant is 0).\n");
            printf("Cannot find Inverse Matrix.\n");
            return;
        }

        if (pivotRow != i) {
            for (j = 0; j < 2 * n; j++) {//สับถึงI
                temp = a[i][j];
                a[i][j] = a[pivotRow][j];
                a[pivotRow][j] = temp;
            }
        }//สับแถวให้ค่าสมบูรณ์มาก ไม่ใช่แถวปัจจุบัน 
        

        pivotVal = a[i][i];
        for (j = 0; j < 2 * n; j++) {
            a[i][j] = a[i][j] / pivotVal;//หารให้เส้นแนวทแยงเป็น1
        }

        for (k = 0; k < n; k++) {
            if (k != i) {
                ratio = a[k][i];
                for (j = 0; j < 2 * n; j++) {
                    a[k][j] = a[k][j] - ratio * a[i][j];
                }
            }
        }
    }

    printf("\n--- Inverse Matrix (A^-1) ---\n");
    for (i = 0; i < n; i++) {
        for (j = n; j < 2 * n; j++) {
            printf("%.2f\t", a[i][j]);
        }
        printf("\n");
    }

    if (findX == 1) {//A^-1 * B
        printf("\n--- Solution (x = A^-1 * b) ---\n");
        for (i = 0; i < n; i++) {
            sum = 0;
            for (j = 0; j < n; j++) {
                sum = sum + (a[i][j + n] * b[j]);//I * b
            }
            x[i] = sum;
            printf("x%d = %.4f\n", i + 1, x[i]);
        }
    }
}

int main() {
    int choice;
    printf("==================================\n");
    printf("   Linear Equation Solver (C)     \n");
    printf("==================================\n");
    printf("1. Gauss-Jordan Elimination (Rule 2)\n");
    printf("2. Inverse Matrix Method (Rule 4)\n");
    printf("Select Rule: ");
    scanf("%d", &choice);

    if (choice == 1) {
        gaussJordanSolver();
    } else if (choice == 2) {
        inverseMatrixSolver();
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}
###########################################################################################################################
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