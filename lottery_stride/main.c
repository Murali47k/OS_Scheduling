#include <stdio.h>
#include <stdlib.h>
#include "parse_task.h"
#include <time.h>
#include "lottery.h"
#include "stride.h"
#include <limits.h>
int main(){
    Process* process_list = NULL;
    // Parse the input file
    parse_file("task.txt", &process_list);
    int n=len_list(process_list);
    //Lottery(process_list, cumulative_ticket_list(process_list,n),n);
    Strides(process_list,stride_lst_of_process(process_list),n);
    
    return 0;
}