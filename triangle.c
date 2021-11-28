#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define TAB_MAX 51
#define POINTS_MAX 3


int main(void) {

	//                            x   y  z
	double points[POINTS_MAX][3] = {
									{0,  15, -10}, 
									{-15 -10, -1},
                                    {13, -15, -5}
									};


	char tab[TAB_MAX][TAB_MAX];
	
	int ztab[TAB_MAX][TAB_MAX];
	
	for (int i = 0; i < TAB_MAX; i++)
	{
		for (int y = 0; y < TAB_MAX; y++)
		{
			ztab[i][y] = 0;
		}
		
	}
	
	char char_tab[15] = ".,-~:;=!*#$@%8&";

	double angle_x = 0;
	double angle_y = 0;
	double angle_z = 0;

	int transformedx0;
	int transformedy0;
	int transformedz0;
	
	int transformedx1;
	int transformedy1;
	int transformedz1;

	for (;;)
	{
		
	angle_x += 0.05;
	angle_y += 0.07;
	angle_z += 0.07;
	
	double rotation_x[3][3] = {{1,            0,            0}, 
							   {0, cos(angle_x), -sin(angle_x)}, 
							   {0, sin(angle_x), cos(angle_x)}};
									
	double rotation_y[3][3] = {{cos(angle_y), 0,-sin(angle_y)}, 
							   {0,            1,           0}, 
							   {sin(angle_y), 0, cos(angle_y)}};
							 
	double rotation_z[3][3] = {{cos(angle_z), -sin(angle_z),0}, 
							   {sin(angle_z), cos(angle_z), 0}, 
							   {0,            0,            1}};
							   
	
	
	double projection[3][3] = {{ ( 1.0 / tan(60 * 3.14/180) ) / 1 , 0, 0},
							   {   0,  1.0 / tan(60 * 3.14/180),        0},
							   {0,      0,  ( (100 + 0.1) / (0.1 - 100) )}};

	for (int i = 0; i < TAB_MAX; i++)
	{
		for (int y = 0; y < TAB_MAX; y++)
		{
      
		tab[i][y] = ' ';

			for (int u = 0; u < POINTS_MAX; u++)
			{
        
				transformedx0 = points[u][0] * rotation_y[0][0] + points[u][1] * rotation_y[0][1] + points[u][2] * rotation_y[0][2];
				transformedy0 = points[u][0] * rotation_y[1][0] + points[u][1] * rotation_y[1][1] + points[u][2] * rotation_y[1][2];
				transformedz0 = points[u][0] * rotation_y[2][0] + points[u][1] * rotation_y[2][1] + points[u][2] * rotation_y[2][2];
				/*
				transformedx0 = transformedx0 * rotation_x[0][0] + transformedy0 * rotation_x[0][1] + transformedz0 * rotation_x[0][2];
				transformedy0 = transformedx0 * rotation_x[1][0] + transformedy0 * rotation_x[1][1] + transformedz0 * rotation_x[1][2];
				transformedz0 = transformedx0 * rotation_x[2][0] + transformedy0 * rotation_x[2][1] + transformedz0 * rotation_x[2][2];
				
				transformedx0 = transformedx0 * rotation_z[0][0] + transformedy0 * rotation_z[0][1] + transformedz0 * rotation_z[0][2];
				transformedy0 = transformedx0 * rotation_z[1][0] + transformedy0 * rotation_z[1][1] + transformedz0 * rotation_z[1][2];
				transformedz0 = transformedx0 * rotation_z[2][0] + transformedy0 * rotation_z[2][1] + transformedz0 * rotation_z[2][2];
				*/
				transformedx0 = transformedx0 * projection[0][0] + transformedy0 * projection[0][1] + transformedz0 * projection[0][2];
				transformedy0 = transformedx0 * projection[1][0] + transformedy0 * projection[1][1] + transformedz0 * projection[1][2];
				transformedz0 = transformedx0 * projection[2][0] + transformedy0 * projection[2][1] + transformedz0 * projection[2][2];
				
        
				if (transformedx0 + TAB_MAX/2 == y && -transformedy0 + TAB_MAX/2 == i)
				{
					if (i < TAB_MAX && i >= 0 && y < TAB_MAX && y > 0)
					{
						tab[i][y] = '#';
					}
				}

			}

			
		}
		
	}

	

	int x0, y0, z0, x1, y1, z1;
	int dx, dy;
	int p;
	double index, n_ligne;
	int z_moyenne;
	
	int mid_z_line[POINTS_MAX];
	int order_display[POINTS_MAX] = {-1, -1, -1};

	for (int l = 0; l < 2; l++)
	{

	for (int u = 0; u < POINTS_MAX; u++)
	{
    
		int i = u;
		if (l == 1 && u == 0)
		{
			for (int n = 0; n < POINTS_MAX; n++)
			{
				int little = 0;
				
				for (int m = 0; m < POINTS_MAX; m++)
				{
					
					if(mid_z_line[m] <= mid_z_line[n])
					{
						little = m;
						
					}
					
				}
				order_display[n] = little;
				mid_z_line[little] = 100;
			}
			
			
			
			
		}
		
		if (l == 1)
		{
			i = order_display[u];
			
		}
		
		transformedx0 = points[i][0] * rotation_y[0][0] + points[i][1] * rotation_y[0][1] + points[i][2] * rotation_y[0][2];
		transformedy0 = points[i][0] * rotation_y[1][0] + points[i][1] * rotation_y[1][1] + points[i][2] * rotation_y[1][2];
		transformedz0 = points[i][0] * rotation_y[2][0] + points[i][1] * rotation_y[2][1] + points[i][2] * rotation_y[2][2];
		/*		
		transformedx0 = transformedx0 * rotation_x[0][0] + transformedy0 * rotation_x[0][1] + transformedz0 * rotation_x[0][2];
		transformedy0 = transformedx0 * rotation_x[1][0] + transformedy0 * rotation_x[1][1] + transformedz0 * rotation_x[1][2];
		transformedz0 = transformedx0 * rotation_x[2][0] + transformedy0 * rotation_x[2][1] + transformedz0 * rotation_x[2][2];
		
		transformedx0 = transformedx0 * rotation_z[0][0] + transformedy0 * rotation_z[0][1] + transformedz0 * rotation_z[0][2];
		transformedy0 = transformedx0 * rotation_z[1][0] + transformedy0 * rotation_z[1][1] + transformedz0 * rotation_z[1][2];
		transformedz0 = transformedx0 * rotation_z[2][0] + transformedy0 * rotation_z[2][1] + transformedz0 * rotation_z[2][2];
		*/
		transformedx0 = transformedx0 * projection[0][0] + transformedy0 * projection[0][1] + transformedz0 * projection[0][2];
		transformedy0 = transformedx0 * projection[1][0] + transformedy0 * projection[1][1] + transformedz0 * projection[1][2];
		transformedz0 = transformedx0 * projection[2][0] + transformedy0 * projection[2][1] + transformedz0 * projection[2][2];
		
		
		
		transformedx1 = points[(i + 1) % POINTS_MAX][0] * rotation_y[0][0] + points[(i + 1) % POINTS_MAX][1] * rotation_y[0][1] + points[(i + 1) % POINTS_MAX][2] * rotation_y[0][2];
		transformedy1 = points[(i + 1) % POINTS_MAX][0] * rotation_y[1][0] + points[(i + 1) % POINTS_MAX][1] * rotation_y[1][1] + points[(i + 1) % POINTS_MAX][2] * rotation_y[1][2];
		transformedz1 = points[(i + 1) % POINTS_MAX][0] * rotation_y[2][0] + points[(i + 1) % POINTS_MAX][1] * rotation_y[2][1] + points[(i + 1) % POINTS_MAX][2] * rotation_y[2][2];
		/*	
		transformedx1 = transformedx1 * rotation_x[0][0] + transformedy1 * rotation_x[0][1] + transformedz1 * rotation_x[0][2];
		transformedy1 = transformedx1 * rotation_x[1][0] + transformedy1 * rotation_x[1][1] + transformedz1 * rotation_x[1][2];
		transformedz1 = transformedx1 * rotation_x[2][0] + transformedy1 * rotation_x[2][1] + transformedz1 * rotation_x[2][2];
			
		transformedx1 = transformedx1 * rotation_z[0][0] + transformedy1 * rotation_z[0][1] + transformedz1 * rotation_z[0][2];
		transformedy1 = transformedx1 * rotation_z[1][0] + transformedy1 * rotation_z[1][1] + transformedz1 * rotation_z[1][2];
		transformedz1 = transformedx1 * rotation_z[2][0] + transformedy1 * rotation_z[2][1] + transformedz1 * rotation_z[2][2];
		*/	
		transformedx1 = transformedx1 * projection[0][0] + transformedy1 * projection[0][1] + transformedz1 * projection[0][2];
		transformedy1 = transformedx1 * projection[1][0] + transformedy1 * projection[1][1] + transformedz1 * projection[1][2];
		transformedz1 = transformedx1 * projection[2][0] + transformedy1 * projection[2][1] + transformedz1 * projection[2][2];
    
		
    
    
		x0 = transformedx0;
		y0 = transformedy0;
		z0 = transformedz0;
		
		x1 = transformedx1;
		y1 = transformedy1;
		z1 = transformedz1;
		
		

		dx = x1 - x0;
		dy = y1 - y0;

		n_ligne = 0;
		index = 0;
		
		int ligne_done = 0;

		if (dx > dy)
		{
			p = dy - dx;
		}
		else
		{
			p = dx - dy;
		}
		
		// Début du massacre le plus total 
		if (dx >= 0 && dy >= 0)
		{
			while ((x0 < transformedx1 || y0 < transformedy1))
			{
				
				if (ligne_done == 0)
				{			
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
					n_ligne++;
					
					if (!(x0 < transformedx1 || y0 < transformedy1))
					{
						x0 = transformedx0;
						y0 = transformedy0;
						ligne_done = 1;
						
						if (dx > dy)
						{
							p = dy - dx;
						}
						else
						{
							p = dx - dy;
						}
						
					}
					
				}
				else
				{
				
					
					z_moyenne = transformedz0 * ((n_ligne-index) / n_ligne) + transformedz1 * (index / n_ligne);
					
					if (index == n_ligne/2)
					{
						mid_z_line[i] = z_moyenne;
					}
					
					if (-y0 + TAB_MAX/2 < TAB_MAX && -y0 + TAB_MAX/2 >= 0 && x0 + TAB_MAX/2 < TAB_MAX && x0 + TAB_MAX/2 > 0)
					{
						ztab[-y0 + TAB_MAX/2][x0 + TAB_MAX/2] = z_moyenne;
						tab[-y0 + TAB_MAX/2][x0 + TAB_MAX/2] = char_tab[12 - (z_moyenne + 10) / 2];
					}
					
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
					
					index++;
					
				}
					
				
			}
		}
		else 
		if (dx <= 0 && dy <= 0)
		{
			while (x0 > transformedx1 || y0 > transformedy1)
			{
				
				if (ligne_done == 0)
				{			
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
					n_ligne++;
					
					if (!(x0 > transformedx1 || y0 > transformedy1))
					{
						x0 = transformedx0;
						y0 = transformedy0;
						ligne_done = 1;
						
						if (dx > dy)
						{
							p = dy - dx;
						}
						else
						{
							p = dx - dy;
						}
						
					}
					
				}
				
				else
				{
				
					z_moyenne = transformedz0 * ((n_ligne-index) / n_ligne) + transformedz1 * (index / n_ligne);
					
					if (index == n_ligne/2)
					{
						mid_z_line[i] = z_moyenne;
					}
					
					if (-y0 + TAB_MAX/2 < TAB_MAX && -y0 + TAB_MAX/2 >= 0 && x0 + TAB_MAX/2 < TAB_MAX && x0 + TAB_MAX/2 > 0)
					{
						ztab[-y0 + TAB_MAX/2][x0 + TAB_MAX/2] = z_moyenne;		
						tab[-y0 + TAB_MAX/2][x0 + TAB_MAX/2] = char_tab[12 - (z_moyenne + 10) / 2];
					}
					
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
					index++;
				}
			}
		}
		else 
		if (dx < 0 && dy > 0)
		{
			
			while (x0 > transformedx1 || y0 < transformedy1)
			{
				
				
				if (ligne_done == 0)
				{			
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
					n_ligne++;
					
					if (!(x0 > transformedx1 || y0 < transformedy1))
					{
						x0 = transformedx0;
						y0 = transformedy0;
						ligne_done = 1;
						
						if (dx > dy)
						{
							p = dy - dx;
						}
						else
						{
							p = dx - dy;
						}
						
					}
					
				}
				
				else
				{
					z_moyenne = transformedz0 * ((n_ligne-index) / n_ligne) + transformedz1 * (index / n_ligne);
					
					if (index == n_ligne/2)
					{
						mid_z_line[i] = z_moyenne;
					}
					
					if (-y0 + TAB_MAX/2 < TAB_MAX && -y0 + TAB_MAX/2 >= 0 && x0 + TAB_MAX/2 < TAB_MAX && x0 + TAB_MAX/2 > 0)
					{	
						ztab[-y0 + TAB_MAX/2][x0 + TAB_MAX/2] = z_moyenne;
						tab[-y0 + TAB_MAX/2][x0 + TAB_MAX/2] = char_tab[12 - (z_moyenne + 10) / 2];
					}
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
					index++;
				}
			}
		}
		else 
		if (dx > 0 && dy < 0)
		{
			
			while (x0 < transformedx1 || y0 > transformedy1)
			{
				
				
				if (ligne_done == 0)
				{			
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
					n_ligne++;
					
					if (!(x0 < transformedx1 || y0 > transformedy1))
					{
						x0 = transformedx0;
						y0 = transformedy0;
						ligne_done = 1;
						
						if (dx > dy)
						{
							p = dy - dx;
						}
						else
						{
							p = dx - dy;
						}
						
					}
					
				}
				
				else
				{
					z_moyenne = transformedz0 * ((n_ligne-index) / n_ligne) + transformedz1 * (index / n_ligne);
					
					if (index == n_ligne/2)
					{
						mid_z_line[i] = z_moyenne;
					}
					
					if (-y0 + TAB_MAX/2 < TAB_MAX && -y0 + TAB_MAX/2 >= 0 && x0 + TAB_MAX/2 < TAB_MAX && x0 + TAB_MAX/2 >= 0)
					{
						ztab[-y0 + TAB_MAX/2][x0 + TAB_MAX/2] = z_moyenne;
						tab[-y0 + TAB_MAX/2][x0 + TAB_MAX/2] = char_tab[12 - (z_moyenne + 10) / 2];
					}
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
					index++;
				}
			}
		}
		// Fin du massacre
	}
	}
	
	int left_point;
	int right_point;
	
	
	for (int i = TAB_MAX - 1; i >= 0; i--)
	{
		left_point = 0;
		right_point = 0;
		
		
		for (int y = 0; y < TAB_MAX; y++)
		{
			if (tab[i][y] != ' ' && left_point == 0)
			{
				left_point = y + 1;
			}
			if (tab[i][y] != ' ')
			{
				right_point = y;
			}
		}
		
		int z0 = ztab[i][left_point];
		int z1 = ztab[i][right_point];
		
		//printf("z0:%d, z1:%d, i:%d, lp:%d, rp:%d\n", z0, z1, i, left_point, right_point);
		//printf("lp:%c, rp:%c\n", tab[i][left_point], tab[i][right_point]);
		
		for (int y = left_point; y < right_point; y++)
		{
			
			index = (y+1)-left_point;
			n_ligne = right_point-left_point;
			z_moyenne = z0 * ((n_ligne-index) / n_ligne) + z1 * (index / n_ligne);
			
			tab[i][y] = char_tab[12 - (z_moyenne + 10) / 2];
			
			
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
	usleep(50000);
	system("clear");
	}	

  return 0;
}
