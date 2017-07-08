/**
 * implementation of FCFS with Safety algorithm
 * 5 processes
 * 3 resources
 * random burst time
 * predefine number of instances available of each resource
 * predefine number of instances of each resource allocation of each process
 * predefine Maximum number of instances of each resource Need by each process
 * each process that schedule to execute can have request for number of instances of each resource
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
    int i=0,j=0,t=0,min,min_i;
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

    /* Data Structures for the Banker’s Algorithm  */
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
    /* END Data Structures for the Banker’s Algorithm  */

    /* Safety Algorithm */
    int Work[NUM_RESOURCES];
    int Finish[NUM_PROCESSES];
    for(j=0;j<NUM_RESOURCES;++j){
        Work[j] = Available[j];
    }
    for(i=0;i<NUM_PROCESSES;++i){
        Finish[i] = 0;
    }
    int flag;
    for(i=0;i<NUM_PROCESSES;++i){
        flag = 1;
        if(Finish[i]=0){
            for(j=0;j<NUM_RESOURCES;++j){
                if(Need[i][j] <= Work[j]);
                else {flag=0;break;}
            }
        }
        else{
            flag=0;break;
        }
        if(flag==1){
            for(j=0;j<NUM_RESOURCES;++j){
                Work[j] += Allocation[i][j];
            }
            Finish[i] = 1;
        }
    }
    flag = 1;
    for(i=0;i<NUM_PROCESSES;++i){
        if(Finish[i] == 1);
        else{
            flag=0;break;
        }
    }
    if(flag==1){
        printf("the system is in a safe state\n");
    }
    else{
        printf("the system is not in a safe state\n");
    }
    /* END Safety Algorithm */

    /* FCFS */
    for(i=0;i<NUM_PROCESSES;++i){
        Finish[i] = 0;
    }
    min;
    min_i;
    j = 0;
    t = 0;
    i = 0;
    int total_flag = 0;
    int request[NUM_RESOURCES];
    while(total_flag == 0){
        if(Finish[i] == 0){
            printf("the process %d can have request for instances of each resources A,B,C : ",i);
            scanf("%d,%d,%d",&request[0],&request[1],&request[2]);
            /* Resource-Request Algorithm for Process Pi */
            flag = 1;
            for(j=0;j<NUM_RESOURCES;++j){
                if(request[j] <= Need[i][j]){
                    if(request[j] <= Available[j]){
                        Available[j] -= request[j];
                        Allocation[i][j] += request[j];
                        Need[i][j] -= request[j];
                    }
                    else{
                        printf("ERROR : resources are not available\n");
                        flag = 0;
                        break;
                    }
                }
                else {
                    printf("ERROR : process has exceeded its maximum claim\n");
                    flag = 0;
                    break;
                }
            }
            if(flag == 1){
                for(j=0;j<NUM_RESOURCES;++j){
                    Work[j] = Available[j];
                }
                for(j=0;j<NUM_RESOURCES;++j){
                    if(Need[i][j] <= Work[j]);
                    else {flag=0;break;}
                }
                if(flag==1){
                    for(j=0;j<NUM_RESOURCES;++j){
                        Work[j] += Allocation[i][j];
                    }
                    Finish[i] = 1;
                }
                if(Finish[i] == 1){
                    printf("the process is in a safe state\n");
                    for(j=0;j<burst[i];++j){
                        printf("in time %d the process %d executed\n",t,i);
                        t++;
                    }
                    for(j=i;j<NUM_PROCESSES;++j){
                        wait[j] += burst[i];
                    }
                    for(j=0;j<NUM_RESOURCES;++j){
                        Available[j] += Allocation[i][j];
                        Allocation[i][j] = 0;
                    }
                    i = (i+1)%NUM_PROCESSES;
                }
                else{
                    printf("the process is not in a safe state\n");
                    printf("the process %d should wait\n",i);
                    printf("should take allocation from process %d\n",i);
                    for(j=0;j<NUM_RESOURCES;++j){
                        Available[j] += Allocation[i][j];
                        Allocation[i][j] = 0;
                    }
                    int k;
                    for(k=0;k<NUM_PROCESSES;++k){
                        if(Finish[k]!=1)
                            total_flag=1;
                        else
                            total_flag=0;
                    }
                    i = (i+1)%NUM_PROCESSES;
                }
            }
            else{
                printf("the process %d should wait\n",i);
                printf("should take allocation from process %d\n",i);
                for(j=0;j<NUM_RESOURCES;++j){
                    Available[j] += Allocation[i][j];
                    Allocation[i][j] = 0;
                }
                i = (i+1)%NUM_PROCESSES;
            }
        }
        else{
            i = (i+1)%NUM_PROCESSES;
        }
        int k;
        for(k=0;k<NUM_PROCESSES;++k){
            if(Finish[k]==1)
                total_flag=1;
            else{
                total_flag=0;
                break;
            }
        }
    }


    /* END Resource-Request Algorithm for Process Pi */
    int sum = 0;
    for(i=0;i<NUM_PROCESSES;++i){
        sum  += wait[i];
    }
    printf("average of waiting time : %d \n",sum/NUM_PROCESSES);
    /* END FCFS */


    return 0;
}
