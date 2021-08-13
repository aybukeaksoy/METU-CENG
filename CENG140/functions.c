#include <stdlib.h>
#include <stdio.h>

#define n_sector 3

/* Fill in the functions and define helper functions if you need to */

float*** create_sector_times(unsigned int* n_drivers, unsigned int* n_laps){
    
    float*** sector_times;
    unsigned int laps=0,drivers=0;
    int i=0,j=0,k=0;
    float temp=0;
    scanf("%u",n_drivers);
    scanf("%u",n_laps);
    drivers=*n_drivers;
    laps=*n_laps;
    
    sector_times=(float ***) malloc(sizeof(float**)*drivers);
    for(i=0;i<drivers;i++)
    {
        sector_times[i]=(float **) malloc(sizeof(float*)*laps);
        for(j=0;j<laps;j++)
        {
            sector_times[i][j]=(float *) malloc(sizeof(float)*n_sector);
            for(k=0;k<n_sector;k++)
            {
                scanf("%f",&temp);
                sector_times[i][j][k]=temp;
            }
        }
    }

    /*
    sector_times=(float ***) malloc(sizeof(float**)*drivers);
    *sector_times=(float **) malloc(sizeof(float*)*laps);
    **sector_times=(float *) malloc(sizeof(float));
    */
    return sector_times;
}


unsigned int** create_positions(unsigned int* p_drivers, unsigned int* n_races){
    
    unsigned int** positions;
    unsigned int pdrivers=0,races=0,temp=0;
    int i=0,j=0;
    scanf("%u",p_drivers);
    scanf("%u",n_races);
    pdrivers=*p_drivers;
    races=*n_races;
    positions= (unsigned int**) malloc(sizeof(unsigned int*)*pdrivers);
    for(i=0;i<pdrivers;i++)
    {
        positions[i]=(unsigned int*) malloc(sizeof(unsigned int)*races);
        for(j=0;j<races;j++)
        {
            scanf("%u",&temp);
            positions[i][j]=temp;
        }
    }

    return positions;
}


float** calculate_lap_times(float*** sector_times, unsigned int n_drivers, unsigned int n_laps){
    
    float** lap_times;
    int i=0,j=0;
    lap_times=(float**) malloc(sizeof(float*)*n_drivers);
    for (i=0;i<n_drivers;i++)
    {
        lap_times[i]=(float*) malloc(sizeof(float)*n_laps);
        for (j=0;j<n_laps;j++)
        {
            lap_times[i][j]=sector_times[i][j][0]+sector_times[i][j][1]+sector_times[i][j][2];
        }
    }

    return lap_times;
}


unsigned int find_fastest_lap(float** lap_times, unsigned int n_drivers, unsigned int n_laps){
    
    int i=0,j=0;
    unsigned int index=0;
    float min=0;
    min=lap_times[0][0];
    for(i=0;i<n_drivers;i++)
    {
        for(j=0;j<n_laps;j++)
        {
            if (lap_times[i][j]<(min-0.0001))
            {
                min=lap_times[i][j];
                index=i;
            }   
        }
    }
    return index;
}


unsigned int find_driver_fastest_lap(float** sector_times_of_driver, unsigned int n_laps){
    int i=0,j=0;
    unsigned int index=0;
    float sum=0,min=0;
    min=sector_times_of_driver[0][0]+sector_times_of_driver[0][1]+sector_times_of_driver[0][2]; /* lap 0 */
    for(i=0;i<n_laps;i++)
    {
       
       for(j=0;j<n_sector;j++)
       {
           sum+=sector_times_of_driver[i][j];
       }
       if (sum<(min-0.0001))
       {
           min=sum;
           index=i;
       }
       sum=0;
    }
    return index;
}


float* selection_sort(float* arr, unsigned int len, char ord){
    
    float* sorted_arr;
    int i=0,j=0,min_index=0,max_index=0;
    float temp=0;
    sorted_arr=(float*) malloc(sizeof(float)*len);
    for(i=0;i<len;i++)
    {
        sorted_arr[i]=arr[i];
    }
    if (ord=='A')
    {
        for(i=0;i<len;i++)
        {
            min_index=i;
            for(j=i;j<len;j++)
            {
                if(sorted_arr[j]<sorted_arr[min_index])
                {
                    min_index=j;
                }
            }
            temp=sorted_arr[i];
            sorted_arr[i]=sorted_arr[min_index];
            sorted_arr[min_index]=temp;
        }
    }
    if (ord=='D')
    {
        for(i=0;i<len;i++)
        {
            max_index=i;
            for(j=i;j<len;j++)
            {
                if(sorted_arr[j]>sorted_arr[max_index])
                {
                    max_index=j;
                }
            }
            temp=sorted_arr[i];
            sorted_arr[i]=sorted_arr[max_index];
            sorted_arr[max_index]=temp;
        }
    }

    return sorted_arr;
}

unsigned int finishing_positions_helper(float* sum_of_laps,unsigned int id,unsigned int n_drivers) /* will find the ranking of each driver. */
{
    unsigned int rank=1;
    float min=0;
    int i=0;
    min=sum_of_laps[id];
    for(i=0;i<n_drivers;i++)
    {
        if(sum_of_laps[i]<(min-0.0001))
        {
            rank++;
        }
        else if(((sum_of_laps[i]<=(min+0.0001))||(sum_of_laps[i]>=(min-0.0001))) && (i<id))
        {
            rank++;
        }
    }
    return rank;
}


unsigned int* find_finishing_positions(float** lap_times, unsigned int n_drivers, unsigned int n_laps){
    
    int i=0,j=0;
    unsigned int k=0,temp=0;
    float sum=0;
    unsigned int* finishing_positions;
    unsigned int* ranks;
    float* sum_of_laps;
    sum_of_laps=(float*) malloc(sizeof(float)*n_drivers);
    finishing_positions=(unsigned int*) malloc(sizeof(unsigned int)*n_drivers);
    ranks=(unsigned int*) malloc(sizeof(unsigned int)*n_drivers);
    
    for(i=0;i<n_drivers;i++)
    {
        for(j=0;j<n_laps;j++)
        {
            sum+=lap_times[i][j];
        }
        sum_of_laps[i]=sum;
        sum=0;
    }
    for(k=0;k<n_drivers;k++)
    {
        temp=finishing_positions_helper(sum_of_laps,k,n_drivers);
        ranks[k]=temp;
    }

    for(i=0;i<n_drivers;i++)
    {
        for(j=0;j<n_drivers;j++)
        {
            if((i+1)==ranks[j])
            {
                finishing_positions[i]=j;
            }
        }
    }


    return finishing_positions;
}


float* find_time_diff(float** lap_times, unsigned int n_drivers, unsigned int n_laps, unsigned int driver1,unsigned int driver2){
    
    float* time_diff;
    float diff=0;
    int i=0;
    time_diff=(float*) malloc(sizeof(float)*n_laps);
   
    for(i=0;i<n_laps;i++)
    {
        time_diff[i]=lap_times[driver1][i]-lap_times[driver2][i]+diff;    
        diff+=lap_times[driver1][i]-lap_times[driver2][i];
    }

    return time_diff;
}


unsigned int* calculate_total_points(unsigned int** positions, unsigned int p_drivers, unsigned int n_races){
    
    unsigned int* points;
    unsigned int* total_points;
    int i=0,j=0,k=0;
    unsigned int sum=0;
    points=(unsigned int*) malloc(sizeof(unsigned int)*p_drivers);
    total_points=(unsigned int*) malloc(sizeof(unsigned int)*p_drivers);
    while (i<p_drivers)
    {
        scanf("%u",(points+i));
        i++;
    }
    
    for(j=0;j<p_drivers;j++)
    {
        for(k=0;k<n_races;k++)
        {
            sum+=points[positions[j][k]-1];
        }
        total_points[j]=sum;
        sum=0;
    }

    return total_points;
}


unsigned int find_season_ranking(unsigned int* total_points, unsigned int p_drivers, unsigned int id){
    
    unsigned int rank=1,max=0;
    int i=0;
    max=total_points[id];
    for(i=0;i<p_drivers;i++)
    {
        if(total_points[i]>(max+0.0001))
        {
            rank++;
        }
        else if(((total_points[i]<=(max+0.0001)) || (total_points[i]>=(max-0.0001))) && (i<id))
        {
            rank++;
        }
    }
    return rank;
}

