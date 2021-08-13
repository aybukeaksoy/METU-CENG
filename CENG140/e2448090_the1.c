#include <stdio.h>
#define ROW 25
#define COLUMN 25


int decide_color(int r,int c,int image[ROW][COLUMN])
{
    if (0<=r && r<ROW && 0<=c && c<COLUMN)
    {
        return image[r][c];
    }
    else if (r<0 && c<0)
    {
        return 0;
    }
    else if (r<0 && 0<=c && c<COLUMN)
    {
        return 1;
    }
    else if (r<0 && c>=COLUMN)
    {
        return 2;
    }
    else if (0<=r && r<ROW && c>=COLUMN)
    {
        return 3;
    }
    else if (r>=ROW && c>=COLUMN)
    {
        return 4;
    }
    else if (r>=ROW && 0<=c && c<COLUMN)
    {
        return 5;
    }
    else if (r>=ROW && c<0)
    {
        return 6;
    }
    else
    {
        return 7;
    }
}



int fill_image(int color,int fillr,int fillc,int image[ROW][COLUMN],int prev)
{
    if (fillr<0 || fillr>=ROW || fillc<0 || fillc>=COLUMN)
    {
        return 0;
    }
    else if (image[fillr][fillc]==color || image[fillr][fillc]!=prev )
    {
        return 0;
    }
    else
    {
        image[fillr][fillc]=color;
        fill_image(color,fillr-1,fillc-1,image,prev);
        fill_image(color,fillr-1,fillc,image,prev);
        fill_image(color,fillr-1,fillc+1,image,prev);
        fill_image(color,fillr,fillc+1,image,prev);
        fill_image(color,fillr+1,fillc+1,image,prev);
        fill_image(color,fillr+1,fillc,image,prev);
        fill_image(color,fillr+1,fillc-1,image,prev);
        fill_image(color,fillr,fillc-1,image,prev);

    }
    return 0;
}

int top_left(int arr[2][2],int result[2],int diff[2])
{
    int r1=0,r2=0,c1=0,c2=0;
    r1=arr[0][0];
    c1=arr[0][1];
    r2=arr[1][0];
    c2=arr[1][1];

    if (r1>=r2 && c1>=c2)
    {
        result[0]=r2;
        result[1]=c2;
        diff[0]=r1-r2;
        diff[1]=c1-c2;
    }
    else if (r2>=r1 && c2>=c1)
    {
        result[0]=r1;
        result[1]=c1;
        diff[0]=r2-r1;
        diff[1]=c2-c1;
    }
    else if (r2>=r1 && c1>=c2)
    {
        result[0]=r1;
        result[1]=c2;
        diff[0]=r2-r1;
        diff[1]=c1-c2;
    }
    else if (r1>=r2 && c2>=c1)
    {
        result[0]=r2;
        result[1]=c1;
        diff[0]=r1-r2;
        diff[1]=c2-c1;
    }
    return 0;
}

int copy_paste(int copy_result[2],int paste_result[2],int diff[2],int image[ROW][COLUMN])
{
    int i=0,j=0,count=0,row_diff=0,column_diff=0;
    row_diff=diff[0];
    column_diff=diff[1];
    for(i=0;i<=row_diff;i++)
        {
            for(j=0;j<=column_diff;j++)
            {
                
                if (image[paste_result[0]+i][paste_result[1]+j]!=image[copy_result[0]+i][copy_result[1]+j])
                {
                    image[paste_result[0]+i][paste_result[1]+j]=image[copy_result[0]+i][copy_result[1]+j];
                    count++;
                }
            }
        }
    return count;
}


int rotate_image(int copy_image[2][2],int paste_image[2][2],int image[ROW][COLUMN],int angle, char direction,int row_diff,int column_diff)
{
    int i=0,j=0,count=0;
    if (angle==0 && (direction=='L' || direction=='R'))
    {
       for(i=0;i<row_diff;i++)
       {
            for(j=0;j<column_diff;j++)
            {
                
                if (image[paste_image[0][0]+i][paste_image[0][1]+j]!=image[copy_image[0][0]+i][copy_image[0][1]+j])
                {
                    image[paste_image[0][0]+i][paste_image[0][1]+j]=image[copy_image[0][0]+i][copy_image[0][1]+j];
                    count++;
                }
            }
        }
    }
    else if (angle==180 && (direction=='L' || direction=='R'))
    {
        for(i=0;i<row_diff;i++)
        {
            for(j=0;j<column_diff;j++)
            {
                if (image[paste_image[0][0]+i][paste_image[0][1]+j]!=image[copy_image[1][0]-i][copy_image[1][1]-j])
                {
                    image[paste_image[0][0]+i][paste_image[0][1]+j]=image[copy_image[1][0]-i][copy_image[1][1]-j];
                    count++;
                }
            }
        }
    }
    else if((direction=='L' && angle==90) || (direction=='R' && angle==270))
    {
        for(i=0;i<row_diff;i++)
        {
            for(j=0;j<column_diff;j++)
            {
                if (image[paste_image[0][0]+i][paste_image[0][1]+j]!=image[copy_image[0][0]+j][copy_image[1][1]-i])
                {
                    image[paste_image[0][0]+i][paste_image[0][1]+j]=image[copy_image[0][0]+j][copy_image[1][1]-i];
                    count++;
                }
            }
        }
    }
    else if((direction=='R' && angle==90) || (direction=='L' && angle==270))
    {
        for(i=0;i<row_diff;i++)
        {
            for(j=0;j<column_diff;j++)
            {
                if (image[paste_image[0][0]+i][paste_image[0][1]+j]!=image[copy_image[1][0]-j][copy_image[0][1]+i])
                {
                    image[paste_image[0][0]+i][paste_image[0][1]+j]=image[copy_image[1][0]-j][copy_image[0][1]+i];
                    count++;
                }
            }
        }
    }
    
   
    return count;
}

int main(void)
{

    int image[ROW][COLUMN],copy_image[2][2],paste_image[2][2],copy_result[2],paste_result[2],diff[2];
    int i=0,j=0,r=0,c=0,color=0,fillr=0,fillc=0,prev=0,count=0,angle=0,row_diff=0,column_diff=0;
    char op,direction;
    for (i=0;i<ROW;i++)
    {
        for (j=0;j<COLUMN;j++)
        {
               scanf(" %d",&image[i][j]);
        }
    }
    scanf(" %c",&op);
    if (op=='F')
    {
        scanf(" %d %d",&r,&c);
        scanf(" %d %d",&fillr,&fillc);
        color=decide_color(r,c,image);
        prev=image[fillr][fillc];
        fill_image(color,fillr,fillc,image,prev);
    
        for (i=0;i<ROW;i++)
        {
            for (j=0;j<COLUMN;j++)
            {
               printf("%d ",image[i][j]);
            }
            printf("\n");
        }
    }
    else if (op=='P')
    {
        scanf(" %d %d %d %d",&copy_image[0][0],&copy_image[0][1],&copy_image[1][0],&copy_image[1][1]);
        scanf(" %d %d %d %d",&paste_image[0][0],&paste_image[0][1],&paste_image[1][0],&paste_image[1][1]);
        top_left(copy_image,copy_result,diff);
        top_left(paste_image,paste_result,diff);
        count=copy_paste(copy_result,paste_result,diff,image);
        for (i=0;i<ROW;i++)
        {
            for (j=0;j<COLUMN;j++)
            {
               printf("%d ",image[i][j]);
            }
            printf("\n");
        }
        printf("%d\n",count);
    }
    else if (op=='R')
    {
        scanf(" %c %d",&direction,&angle);
        scanf(" %d %d %d %d",&copy_image[0][0],&copy_image[0][1],&copy_image[1][0],&copy_image[1][1]);
        scanf(" %d %d %d %d",&paste_image[0][0],&paste_image[0][1],&paste_image[1][0],&paste_image[1][1]);
        row_diff=copy_image[1][0]-copy_image[0][0]+1;
        column_diff=copy_image[1][1]-copy_image[0][1]+1;
        count=rotate_image(copy_image,paste_image,image,angle,direction,row_diff,column_diff);
        for (i=0;i<ROW;i++)
        {
            for (j=0;j<COLUMN;j++)
            {
               printf("%d ",image[i][j]);
            }
            printf("\n");
        }
        printf("%d\n",count);
    }

    return 0;
}



