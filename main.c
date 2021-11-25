#include <stdio.h>

#define TAB_MAX 31
#define POINTS_MAX 3


int main(void) {

  //                            x   y  z
  int points[POINTS_MAX][3] = {{5, -10, 0}, 
                              {-10,  5, 0}, 
                              { 10,  10, 0}};



  char tab[TAB_MAX][TAB_MAX];



  for (int i = 0; i < TAB_MAX; i++)
  {
    for (int y = 0; y < TAB_MAX; y++)
    {
      
      tab[i][y] = '_';

      for (int u = 0; u < POINTS_MAX; u++)
      {
        
        if (points[u][0] + TAB_MAX/2 == y &&
            points[u][1] + TAB_MAX/2 == i)
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

  for (int i = 0; i < 3; i++)
  {
    
    x0 = points[i][0];
    y0 = points[i][1];

    x1 = points[(i + 1) % 3][0];
    y1 = points[(i + 1) % 3][1];

    dx = x1 - x0;
    dy = y1 - y0;

    printf("dx:%d, dy:%d\n", dx, dy);

    p = 2 * dy - dx;
    
    if (dx > 0 && dy > 0)
    {
      while (x0 < points[(i + 1) % 3][0] || y0 < points[(i + 1) % 3][1])
      {
        if(p>=0)
        {
          tab[y0 + TAB_MAX/2][x0 + TAB_MAX/2] = '#';
          y0++;
          p += 2*dy - 2*dx;
        }
        else
        {
          tab[y0 + TAB_MAX/2][x0 + TAB_MAX/2] = '#';
          p += 2*dy;
          
        }
        x0++;
      }
    }
    else 
    if (dx < 0 && dy < 0)
    {
      while (x0 > points[(i + 1) % 3][0] || y0 > points[(i + 1) % 3][1])
      {
        printf("%d\n", p);
        if(p>=0)
        {
          tab[y0 + TAB_MAX/2][x0 + TAB_MAX/2] = '#';
          p += dy;
          x0--;
          
        }
        else
        {
          tab[y0 + TAB_MAX/2][x0 + TAB_MAX/2] = '#';
          // wtf pk quand on fait *2 sur dx sa marche 
          p -= dy - 2*dx;
        }
        y0--;
      }
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