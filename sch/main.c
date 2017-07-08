/**
 * implementation of FCFS with banker algorithm
 * 5 processes
 * 3 resources
 * random burst time
 * predefine number of instances available of each resource
 * predefine number of instances of each resource allocation of each process
 * predefine Maximum number of instances of each resource Need by each process
 */


#include <stdio.h>
#include <windows.h>

#define NUM_PROCESSES 5
#define NUM_RESOURCES 3

int main()
{
    srand(time(NULL));
    //STARTUPINFO si[NUM_PROCESSES];
    //PROCESS_INFORMATION pi[NUM_PROCESSES];
    int burst[NUM_PROCESSES];
    int i;
    int wait[NUM_PROCESSES];
    for(i=0;i<NUM_PROCESSES;++i){ wait[i] = 0; }
    int total_burst = 0;
    for(i=0;i<NUM_PROCESSES;++i){
        /* allocate memory */
        //ZeroMemory(&si[i], sizeof(si[i]));
        //si[i].cb = sizeof(si[i]);
        //ZeroMemory(&pi[i], sizeof(pi[i]));

        /* create child process */
        //if( !CreateProcess( NULL,   // No module name (use command line)
        //    "C:\\WINDOWS\\system32\\mspaint.exe",        // Command line
        //    NULL,           // Process handle not inheritable
        //    NULL,           // Thread handle not inheritable
        //    FALSE,          // Set handle inheritance to FALSE
        //    0,              // No creation flags
        //    NULL,           // Use parent's environment block
        //    NULL,           // Use parent's starting directory
        //    &si[i],            // Pointer to STARTUPINFO structure
        //    &pi[i] )           // Pointer to PROCESS_INFORMATION structure
        //)
        //{
        //   printf( "CreateProcess failed (%d).\n", GetLastError() );
        //    return;
        //}
        /* parent will wait for the child to complete */
        //WaitForSingleObject(pi[i].hProcess, INFINITE);
        //printf("Child Complete");
        /* close handles */
        //CloseHandle(pi[i].hProcess);
        //CloseHandle(pi[i].hThread);
        burst[i] = rand()%10+1;
        printf(" burst of process %d is %d\n",i,burst[i]);
        total_burst += burst[i];
    }
    /* FCFS */
    int min;
    int min_i;
    int j;
    int t=0;
    i = 0;
    for(t=0;t<total_burst;){
        for(j=0;j<burst[i];++j){
            printf("in time %d the process %d executed\n",t,i);
            t++;
        }
        for(j=i;j<NUM_PROCESSES;++j){
            wait[j] += burst[i];
        }
        i++;
    }
    int sum = 0;
    for(i=0;i<NUM_PROCESSES;++i){
        sum  += wait[i];
    }
    printf("average of waiting time : %d \n",sum/NUM_PROCESSES);
    /* END FCFS */
    int Resource[NUM_RESOURCES] = {10,5,7};
    int Allocation[NUM_PROCESSES][NUM_RESOURCES] = {{0,1,0},{2,0,0},{3,0,2},{2,1,1},{0,0,2}};
    int Max[NUM_PROCESSES][NUM_RESOURCES] = {{7,5,3},{3,2,2},{9,0,2},{2,2,2},{4,3,3}};
    int Available[NUM_RESOURCES] = {10,5,7};
    int Need[NUM_PROCESSES][NUM_RESOURCES] = {{7,5,3},{3,2,2},{9,0,2},{2,2,2},{4,3,3}};
    for(i=0;i<NUM_PROCESSES;++i){
        for(j=0;j<NUM_RESOURCES;++j){
            Available[j] -= Allocation[i][j];
        }
    }
    for(i=0;i<NUM_PROCESSES;++i){
        for(j=0;j<NUM_RESOURCES;++j){
            Need[i][j] = Max[i][j] - Allocation[i][j];
        }
    }
    for(i=0;i<NUM_PROCESSES;++i){
        for(j=0;j<NUM_RESOURCES;++j){
            printf("%d ",Need[i][j]);
        }
        printf("\n");
    }
    return 0;
}
