#include <stdio.h>
#include <stdlib.h>

struct allocationElements{
    int *elementPtr;
    int elementSize;
}elementArray[10000];

int elementArrayMaxIndex = 0;

void printElementArray()
{
    printf("Current Allocation is:\n");
    for(int i = 0; i<elementArrayMaxIndex; i++){
        if(elementArray[i].elementSize != -1){
            printf("%d\n", elementArray[i].elementSize);
        }
    }    
}
 
int my_function_alloc(int size_of_allocation)
{
    int* ptr;
    int i;

    ptr = (int*)malloc(size_of_allocation * sizeof(int));
 
    if (ptr == NULL) {
        printf("Memory not allocated.\n");
        exit(0);
    }
    
    else {
        printf("Memory successfully allocated using malloc.\n");
    }
    
    elementArray[elementArrayMaxIndex].elementPtr = ptr;
    elementArray[elementArrayMaxIndex].elementSize = size_of_allocation;
    elementArrayMaxIndex++;
    
    printElementArray();
 
    return 0;
}

int my_function_dealloc(int size_of_allocation)
{
    int* toDeallocPtr = NULL;
    
    for(int i=0;i<elementArrayMaxIndex; i++)
    {
        if(elementArray[i].elementSize == size_of_allocation)
        {
            toDeallocPtr = elementArray[i].elementPtr;
            elementArray[i].elementSize = -1;
            elementArray[i].elementPtr = NULL;
        }
    }
    
    if(toDeallocPtr == NULL)
    {
        printf("No memory chunk of given size\n");
        return (-1);
    }
    else
    {
        printf("Memory Chunk found, Deallocated\n");
        free(toDeallocPtr);
    }
    
    printElementArray();
    
    return (0);
}

int main()
{
    int inputChoice, size_of_allocation, size_of_deallocation, allocationStatus, continueChoice = 'n';
    do{
        printf("Press 1 for allocation\nPress 2 for Deallocation\n");
        scanf("%d", &inputChoice);
        if(inputChoice == 1){
            printf("Enter memory size to be allocated\n");
            scanf("%d", &size_of_allocation);
            allocationStatus = my_function_alloc(size_of_allocation);
        }
        else if(inputChoice == 2){
            printf("Enter memory size to be deallocated\n");
            scanf("%d", &size_of_deallocation);
            allocationStatus = my_function_dealloc(size_of_deallocation);
        }
        printf("Do you want to continue\n1 - for Yes\n2 - for No\n");
        scanf("%d",&continueChoice);
    }while(continueChoice == 1);
    return 0;
}