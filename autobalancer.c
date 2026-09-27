//r_iron is 10
//c_oil is 70

#include <stdio.h>
#include <stdlib.h>
#define getbuf() do { fgets(Buffer, sizeof(Buffer), stdin); } while (0)

int main() {
    //AUTOBALANCER
    char Buffer[64];
    puts("---input ct---");
    getbuf();
    int Input_Ct = atoi(Buffer);
    int* Input_Amounts = malloc(sizeof(int) * Input_Ct);
    int* Input_Prices = malloc(sizeof(int) * Input_Ct);
    for (int C1 = 0; C1 < Input_Ct; C1++) {
        char Carrier[64];
        snprintf(Carrier, sizeof(Carrier), "---input quantity %i---", C1 + 1);
        puts(Carrier);
        getbuf();
        Input_Amounts[C1] = atoi(Buffer);
        snprintf(Carrier, sizeof(Carrier), "---input sell val. %i---", C1 + 1);
        puts(Carrier);
        getbuf();
        Input_Prices[C1] = atoi(Buffer);
    }
    puts("---output ct---");
    getbuf();
    int Output_Ct = atoi(Buffer);
    int* Output_Amounts = malloc(sizeof(int) * Output_Ct);
    for (int C1 = 0; C1 < Output_Ct; C1++) {
        char Carrier[64];
        snprintf(Carrier, sizeof(Carrier), "---output quantity %i---", C1 + 1);
        puts(Carrier);
        getbuf();
        Output_Amounts[C1] = atoi(Buffer);
    }

    //TMP!!!
    double* Output_Prices = malloc(sizeof(double) * Output_Ct);
 double Total_Input_Value = 0.0;
    for (int C1 = 0; C1 < Input_Ct; C1++) {
        Total_Input_Value += (double)Input_Amounts[C1] * (double)Input_Prices[C1];
    }
    double Total_Output_Value = Total_Input_Value * 1.2;

    // Split that value across outputs, weighted by how many units each output produces.
    // Default: split evenly across output *types*, then divide by quantity to get per-unit price.
    // (Change this if some outputs should get a bigger cut than others.)
    int Total_Output_Units = 0;
    for (int C1 = 0; C1 < Output_Ct; C1++) {
        Total_Output_Units += Output_Amounts[C1];
    }

    double Value_Per_Unit = (Total_Output_Units > 0)
        ? Total_Output_Value / Total_Output_Units
        : 0.0;

    for (int C1 = 0; C1 < Output_Ct; C1++) {
        Output_Prices[C1] = Value_Per_Unit; // per-unit sell price for this output
    }

    // --- PRINT RESULTS ---
    printf("\nTotal input value: %.2f\n", Total_Input_Value);
    printf("Total output value (with %.1fx margin): %.2f\n", 1.2, Total_Output_Value);
    for (int C1 = 0; C1 < Output_Ct; C1++) {
        printf("Output %d: %d units @ %.2f each (batch value %.2f)\n",
               C1 + 1, Output_Amounts[C1], Output_Prices[C1],
               Output_Prices[C1] * Output_Amounts[C1]);
    }
    //ENDTMP!!!
    free(Input_Prices);
    free(Input_Amounts);
    free(Output_Amounts);
    free(Output_Prices);
    return 0;
}