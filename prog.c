
#include <stdio.h>

#define ROWS 3
#define COLS 3



void matmul(int a[], int b[], int c[])
{
	
	
	for (int i = 0; i < ROWS; i++)
	{
		for (int y = 0; y < 1; y++)
		{
			int sum = 0;
			for (int k = 0; k < COLS; k++)
			{
				sum += a[i * 3 + k] * b[k];
			}
			c[i] = sum;
		}
	}
	
}



void print_array(int a[])
{
	
	for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 22; j++) {
            printf("%d ", a[i * 22 + j]);
        }
        printf("\n");
    }
	
}




int main(int argc, char **argv)
{
	
	
	int ascreen[11 * (11 * 2)];
	
	for (int i = 5; i >= -5; i--)
	{
		for (int y = -10; y <= 11; y++)
		{
			if ((y + 10) % 2 == 1)
			{
				ascreen[(10 - (i + 5)) * 22 + (y + 10)] = i;
			}
			else
			{
				ascreen[(10 - (i + 5)) * 22 + (y + 10)] = y / 2;
			}
		}
	}
	
	
	int plane[4 * 3] = { -2,  2, -2,  2,  // x
						  4,  4, -4, -4,  // y
						 -2, -2,  2,  2 }; // z
						  
						  
		
		
	/*int a[9] = { 1, 0, 0, 
				 1, 2, 0, 
				 0, 0, 1};
						  
						  
	int b[3] = { 2, 
				 1, 
				 0 };
						  
	
	int c[3];
	
	matmul(a, b, c);
	
	print_array(c);*/
	
	for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 22; j++) {
			if (ascreen[i * 22 + j] >= 0){
				printf(" ");
			}
			
			printf("%d;", ascreen[i * 22 + j]);
			if (j % 2 == 1){
				printf("|");
			}
        }
        printf("\n\n");
    }
    
   
	
	
	
	return 0;
}

