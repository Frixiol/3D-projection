#include <stdio.h>


#define TAB_MAX 71
#define POINTS_MAX 3


int main(void) {

	//                            x   y  z
	double points[POINTS_MAX][3] = {{5,  -20, 0}, 
                                  {-21,   15, 0}, 
                                  { 15,   -5, 0}};


	char tab[TAB_MAX][TAB_MAX];

	

	for (int i = 0; i < TAB_MAX; i++)
	{
		for (int y = 0; y < TAB_MAX; y++)
		{
      
			tab[i][y] = ' ';

			for (int u = 0; u < POINTS_MAX; u++)
			{
        
				if (points[u][0] + TAB_MAX/2 == y && -points[u][1] + TAB_MAX/2 == i)
				{
					tab[i][y] = '#';
				}

			}
			printf("%c", tab[i][y]);
		}
		printf("\n");
	}

	
	printf("\n");
	

	int x0, y0, x1, y1;
	int dx, dy;
	int p;
	

	for (int i = 0; i < POINTS_MAX; i++)
	{
    
    
    
		x0 = points[i][0];
		y0 = points[i][1];
		
		
		x1 = points[(i + 1) % 3][0];
		y1 = points[(i + 1) % 3][1];


		dx = x1 - x0;
		dy = y1 - y0;

		

		if (dx > dy)
		{
			p = dy - dx;
		}
		else
		{
			p = dx - dy;
		}
		
		// Début du massacre
		if (dx >= 0 && dy >= 0)
		{
			while (x0 < points[(i + 1) % 3][0] || y0 < points[(i + 1) % 3][1])
			{
				tab[-y0 + TAB_MAX/2][x0 + TAB_MAX/2] = '#';
				if(p>=0)
				{
					y0++;
					p += - 2*dx;
				}
				else
				{
					p += 2*dy;
					x0++;
				}
			}
		}
		else 
		if (dx <= 0 && dy <= 0)
		{
			while (x0 > points[(i + 1) % 3][0] || y0 > points[(i + 1) % 3][1])
			{
				
				tab[-y0 + TAB_MAX/2][x0 + TAB_MAX/2] = '#';
				if(p<=0)
				{
					x0--;
					p +=  - 2*dy;
				}
				else
				{
					y0--;
					p += 2*dx;
				}
			}
		}
		else 
		if (dx < 0 && dy > 0)
		{
			
			while (x0 > points[(i + 1) % 3][0] || y0 < points[(i + 1) % 3][1])
			{
				
				tab[-y0 + TAB_MAX/2][x0 + TAB_MAX/2] = '#';
				if(p<=0)
				{
					x0--;
					p -=  - 2*dy;
				}
				else
				{
					y0++;
					p += 2*dx;
				}
			}
		}
		else 
		if (dx > 0 && dy < 0)
		{
			
			while (x0 < points[(i + 1) % 3][0] || y0 > points[(i + 1) % 3][1])
			{
				
				tab[-y0 + TAB_MAX/2][x0 + TAB_MAX/2] = '#';
				if(p<=0)
				{
					x0++;
					p +=  - 2*dy;
				}
				else
				{
					y0--;
					p -= 2*dx;
				}
			}
		}
		// Fin du massacre
	}
  
	
	int left_point;
	int right_point;
	
	
	for (int i = TAB_MAX; i >= 0; i--)
	{
		left_point = 0;
		right_point = 0;
		
		
		for (int y = 0; y < TAB_MAX; y++)
		{
			if (tab[i][y] == '#' && left_point == 0)
			{
				left_point = y + 1;
			}
			if (tab[i][y] == '#')
			{
				right_point = y;
			}
		}
		
		for (int y = left_point; y < right_point; y++)
		{
			tab[i][y] = '+';
		}
		
	}
  
  
	for (int i = 0; i < TAB_MAX; i++)
	{
		for (int y = 0; y < TAB_MAX; y++)
		{
			printf("%c", tab[i][y]);
		}
		printf("\n");
	}
	

  return 0;
}
