#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Function to calculate time quantum for low priority process
int GetLowPriority(int n, int TQ) { 
    int low_p = 0; 
    low_p = TQ - (2 * TQ / 10); // Using integer arithmetic
    return low_p;
}

// Function to calculate time quantum for high priority process
int GetHighPriority(int n, int TQ) {
    int high_p = 0; 
    high_p = TQ + (2 * TQ / 10); // Using integer arithmetic
    return high_p;
}

// Function to calculate time quantum for medium priority process
int GetMediumPriority(int n, int TQ) { 
    int medium_p = 0; 
    medium_p = TQ; 
    return medium_p;
}


// Function to display the time quantum for each priority level
int DisplayTimeQuantum(int n, int TQ) {
    printf("\n------------------------------------\n");
    printf("***** Time Quantum: %d *****\n", TQ);
    printf("------------------------------------");
    printf("\nTime Quantum for High Priority Process: %d", GetHighPriority(n, TQ));
    printf("\nTime Quantum for Medium Priority Process: %d", GetMediumPriority(n, TQ));
    printf("\nTime Quantum for Low Priority Process: %d", GetLowPriority(n, TQ));
    printf("\n------------------------------------\n");
    return 1;
}


// Function to run the simulation based on the given parameters
int RunSimulation(int n, int TQ, int BT[], int AT[], int WT[], 
    int TAT[], int P_val[], bool P_flag[]) {
    int RQ_ctr = 0, temp_WT = 0, exit_t = 0, ctx_s = 0, rem_RQ = 0, rem_BT[n], new_TQ[n];
    memset(rem_BT, 0, n*sizeof(int));
    memset(new_TQ, 0, n*sizeof(int));
    RQ_ctr = n;
    float Avg_WT = 0.0, Avg_TT = 0.0;
    
    
// Initialize remaining burst time and time quantum for each process

    for(int i = 0; i < n; i++){
        rem_BT[i] = BT[i];
        if(P_val[i] == 1){
            new_TQ[i] = GetLowPriority(n, TQ);
        }
        else if(P_val[i] == 2){
            new_TQ[i] = GetMediumPriority(n, TQ);
        }
        else if(P_val[i] == 3){
            new_TQ[i] = GetHighPriority(n, TQ);
        }
    }
    
    printf("------------------------------------\n");
    printf("***** Gantt Chart *****\n");
    printf("------------------------------------\n");
    
    
     // Main simulation loop
    while(1){ 
        bool process_status = true;
        
        // Check for processes with burst time less than or equal to 100
        for(int i = 0; i < n; i++){
            if(rem_BT[i] > 0 && rem_BT[i] <= 100){
             // Update process information
                P_flag[i] = 1;
                exit_t = temp_WT + rem_BT[i];
                TAT[i] = exit_t - AT[i];
                WT[i] = TAT[i] - BT[i];
                temp_WT += rem_BT[i];
                printf("%d (%d)| ", i+1, temp_WT);
                ctx_s++; 
                rem_BT[i] = 0; 
                exit_t = 0;
                RQ_ctr--;
                process_status = false;    
            }
        }
        
        // Check for processes with burst time greater than 100
        // Handle processes based on their priority and remaining burst time
                // Update process information
                // Print the Gantt chart
                // Update counters and flags
        for(int i = 0; i < n; i++){
            if(rem_BT[i] > 100){
                if(rem_BT[i] <= new_TQ[i]){
                    P_flag[i] = 1;
                    exit_t = temp_WT + rem_BT[i];
                    TAT[i] = exit_t - AT[i];
                    WT[i] = TAT[i] - BT[i];
                    temp_WT += rem_BT[i];
                    printf("%d (%d)| ", i+1, temp_WT);
                    ctx_s++;
                    rem_BT[i] = 0; 
                    exit_t = 0;
                    RQ_ctr--;
                    process_status = false;    
                }
                else if((rem_BT[i] > new_TQ[i]) && rem_BT[i] <= (new_TQ[i] + (0.3 * new_TQ[i])) && P_val[i] == 3){    
                    P_flag[i] = 1;
                    exit_t = temp_WT + rem_BT[i];
                    TAT[i] = exit_t - AT[i];
                    WT[i] = TAT[i] - BT[i];
                    temp_WT += rem_BT[i];
                    printf("%d (%d)| ", i+1, temp_WT);
                    ctx_s++;
                    rem_BT[i] = 0; 
                    exit_t = 0;
                    RQ_ctr--;
                    process_status = false;    
                }
                else if((rem_BT[i] > new_TQ[i]) && rem_BT[i] <= (new_TQ[i] + (0.2 * new_TQ[i])) && (P_val[i] == 2 || P_val[i] == 1)){
                    P_flag[i] = 1;
                    exit_t = temp_WT + rem_BT[i];
                    TAT[i] = exit_t - AT[i];
                    WT[i] = TAT[i] - BT[i];
                    temp_WT = temp_WT + rem_BT[i];
                    printf("%d (%d)| ", i+1, temp_WT);
                    ctx_s++;
                    rem_BT[i] = 0;
                    exit_t = 0;
                    RQ_ctr--;
                    process_status = false;    
                }
                else{ 
                    if(P_val[i] == 1){
                        process_status = false;        
                        rem_BT[i] -= new_TQ[i];
                        temp_WT += new_TQ[i];
                        printf("%d (%d)| ", i+1, temp_WT);
                        ctx_s++;
                    }
                    else if(P_val[i] == 2){
                        process_status = false;     
                        rem_BT[i] -= new_TQ[i];
                        temp_WT += new_TQ[i];     
                        printf("%d (%d)| ", i+1, temp_WT);
                        ctx_s++;
                    }
                    else if(P_val[i] == 3){
                        process_status = false;     
                        rem_BT[i] -= new_TQ[i];
                        temp_WT += new_TQ[i];
                        printf("%d (%d)| ", i+1, temp_WT);
                        ctx_s++;
                    }
                }
            }
        }
        if(process_status == true && RQ_ctr == 0){
            break;
        }
    }
    
    // Display process table with waiting time, turnaround time, and other information
    printf("\n------------------------------------\n");
    printf("***** Process Table *****\n");
    printf("------------------------------------\n");
    printf("Process \tBurst Time \tArrival Time \tWaiting Time \tTurn Around Time"); 
    for(int i = 0; i < n; i++){
        Avg_WT += WT[i];
        Avg_TT += TAT[i];
        printf("\n\t%d\t%d\t\t%d\t\t%d\t\t%d",i+1, BT[i], AT[i], WT[i], TAT[i]); 
    }
    printf("\n------------------------------------\n");
    printf("\nAverage Waiting Time: %0.1f", Avg_WT/n);
    printf("\nAverage Turnaround Time: %0.1f", Avg_TT/n);
    printf("\nTotal no. of context switches: %d\n", ctx_s);
    return 1;
}


// Main function to get input and initiate the simulation
int main()
{
    int n = 0, TQ = 0;
    
    // Get the number of processes and time quantum from user
    printf("Enter the no. of processes: ");
    scanf("%d", &n);  

    printf("Enter Burst Time, Arrival Time, and Priority (1-3) for each process:\n");


    // Declare arrays and variables for process details
    int BT[n], AT[n], PID[n], P_val[n];
    int TAT[n], WT[n], Pid[n];
    bool P_flag[n];
    memset(BT, 0, n*sizeof(int));
    memset(AT, 0, n*sizeof(int));
    memset(WT, 0, n*sizeof(int));
    memset(PID, 0, n*sizeof(int));
    memset(TAT, 0, n*sizeof(int));
    memset(P_val, 0, n*sizeof(int));
    memset(P_flag, 0, n*sizeof(int));

    printf("Enter the time quantum: ");
    scanf("%d", &TQ);


    // Get user input for burst time, arrival time, and priority for each process
    printf("Enter the details for each process:\n");
    for(int i = 0; i < n; i++){
        printf("Process %d:\n", i+1);
        printf("Burst Time: ");
        scanf("%d", &BT[i]);
        printf("Arrival Time: ");
        scanf("%d", &AT[i]);
        printf("Priority (1-3): ");
        scanf("%d", &P_val[i]);
        if(P_val[i] < 1 || P_val[i] > 3) {
            printf("\n------------------------------------\n");
            printf("Enter a value from (1-3).");
            return 0;
        }
    }


    // Display time quantum information and initiate simulation
    printf("\n------------------------------------\n");
    DisplayTimeQuantum(n, TQ);
    RunSimulation(n, TQ, BT, AT, WT, TAT, P_val, P_flag);
    return 0;
}

