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
    float* Output_Prices = malloc(sizeof(float) * Output_Ct);
    float Total_Input = 0;
    for (int C1 = 0; C1 < Input_Ct; C1++) {
        Total_Input += (float)Input_Amounts[C1] * (float)Input_Prices[C1];
    }
    float Total_Output = Total_Input * 1.2f;
    float Total_Output_Units = 0;
    for (int C1 = 0; C1 < Output_Ct; C1++) {
        Total_Output_Units += Output_Amounts[C1];
    }
    float Value_Unit = (Total_Output_Units > 0) ? Total_Output / Total_Output_Units : 0;
    for (int C1 = 0; C1 < Output_Ct; C1++) {
        Output_Prices[C1] = Value_Unit;
    }
    //TMP, stolen from some random-axe website!!!
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