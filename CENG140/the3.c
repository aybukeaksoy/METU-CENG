#include <stdio.h>
#include <stdlib.h>
#include "the3.h"

Apartment* add_apartment(Apartment* head, int index, char* apartment_name, int max_bandwidth){

  int i=0;
  Apartment *curr,*prev,*newnode;
  curr=head;
  prev=NULL;
  
  if (head)
  {
    if(index!=0)
    {
      while (i<index)
      {
        prev=curr;
        curr=curr->next;
        i++;
      }
      newnode=malloc(sizeof(Apartment));
      newnode->name=apartment_name;
      newnode->max_bandwidth=max_bandwidth;
      newnode->flat_list=NULL;
      prev->next=newnode;
      newnode->next=curr;
    }
    else
    {
      while (curr->next!=head)
      {
        curr=curr->next;
      }
      newnode=malloc(sizeof(Apartment));
      newnode->next=head;
      curr->next=newnode;
      newnode->name=apartment_name;
      newnode->max_bandwidth=max_bandwidth;
      newnode->flat_list=NULL;
      head=newnode;
    }
  }
  else 
  {
    newnode=malloc(sizeof(Apartment));
    head=newnode;
    head->next=head;
    head->name=apartment_name;
    head->max_bandwidth=max_bandwidth;
    head->flat_list=NULL;
  }
  return head;
}

int check_apartment_names(char* apartment_name,char* name)
{
   int i=0,len1=0,len2=0,count=0;
   while (apartment_name[i]!='\0')
    {
        len1++;
        i++;
    }
    i=0;
    while (name[i]!='\0')
    {
        len2++;
        i++;
    }
    if (len1==len2)
    {
       for(i=0;i<len1;i++)
       {
          if(apartment_name[i]==name[i])
          {
            count++;
          }
       }
    }
    if (count==len1)
    {
       return 1;
    }
    else
    {
       return 0;
    }

}

int calculate_sum(Flat *head){
    Flat *curr;
    int sum=0;
    curr=head;
    while(curr)
    {
      sum+=curr->initial_bandwidth;
      curr=curr->next;
    }

    return sum;
}

void add_flat(Apartment* head, char* apartment_name, int index, int flat_id, int initial_bandwidth)
{
  /* NULL CONDITION */
  int i=0,sum=0;
  Apartment *track;
  Flat *curr,*previous,*newnode;
  track=head;
  while (track)
  {
    if(check_apartment_names(apartment_name,track->name))
    {
       curr=track->flat_list;
       previous=NULL;
       if(!(track->flat_list))
       {
          newnode=malloc(sizeof(Flat));
          newnode->prev=NULL;
          newnode->next=NULL;
          newnode->is_empty=0;
          newnode->id=flat_id;
          newnode->initial_bandwidth=initial_bandwidth;
          track->flat_list=newnode;


       }
       else if (index!=0)
       {
          while(i<index)
          {
            previous=curr;
            curr=curr->next;
            i++;
          }
          newnode=malloc(sizeof(Flat));
          previous->next=newnode;
          newnode->prev=previous;
          newnode->next=curr;
          if (curr)
          {
            curr->prev=newnode;
          }
          newnode->is_empty=0;
          newnode->id=flat_id;
          sum=calculate_sum(track->flat_list);
          if (initial_bandwidth<=((track->max_bandwidth)-sum))
          {
            newnode->initial_bandwidth=initial_bandwidth;
          }
          else
          {
            newnode->initial_bandwidth=(track->max_bandwidth)-sum;
          }
       }
       
       else
       {
          newnode=malloc(sizeof(Flat));
          newnode->prev=NULL;
          newnode->next=curr;
          curr->prev=newnode;
          track->flat_list=newnode;
          newnode->is_empty=0;
          newnode->id=flat_id;
          sum=calculate_sum(track->flat_list);
          if (initial_bandwidth<=((track->max_bandwidth)-sum))
          {
            newnode->initial_bandwidth=initial_bandwidth;
          }
          else
          {
            newnode->initial_bandwidth=(track->max_bandwidth)-sum;
          }
       }
       break;
    }

    track=track->next;
  }
}

Apartment* remove_apartment(Apartment* head, char* apartment_name)
{
   /* if you remove the head */
   
   Apartment *track,*previous,*lastnode;
   Flat *curr,*temp;
   int count=0,i=0;
   previous=NULL;
   track=head;
   while(track)
   {
    if(check_apartment_names(apartment_name,track->name))
    {
      curr=track->flat_list;
      while(curr)
      {
        temp=curr;
        curr=curr->next;
        free(temp);
      }
      if(count==0)
      {
        lastnode=head;
        while (lastnode->next!=head)
        {
          i=1;
          lastnode=lastnode->next;
        }
        if(i==0)
        {
          head=NULL;
        }
        else
        {
          head=track->next;
          lastnode->next=track->next;
        }

      }
      else
      {
        previous->next=track->next;
      }
      free(track);
      break;
    }
     
    previous=track;
    track=track->next;
    count++;
   }
  return head;
}

void make_flat_empty(Apartment* head, char* apartment_name, int flat_id)
{
   Apartment *track;
   Flat *curr;
   track=head;
   while (track)
   {
      if(check_apartment_names(apartment_name,track->name))
      {
        curr=track->flat_list;
        while(curr)
        {
           if(curr->id==flat_id)
           {
              curr->is_empty=1;
              curr->initial_bandwidth=0;
           }
           curr=curr->next;
        }
       
        break;
      }
    track=track->next;
   }

}

int find_sum_of_max_bandwidths(Apartment* head)
{
   int sum=0;
   if(head)
   {
     Apartment *track;
     track=head;
     while(track->next!=head)
     {
       sum+=track->max_bandwidth;
       track=track->next;
     }
     sum+=track->max_bandwidth;
   }

   return sum;
}

Apartment* merge_two_apartments(Apartment* head, char* apartment_name_1, char* apartment_name_2)
{
   /* dont forget to consıder null situation */
   
   Apartment *first,*second,*prev,*lastnode;
   Flat *curr;
   first=head;
   second=head;
   prev=NULL;
   lastnode=head;
   while(first)
   {
      if(check_apartment_names(apartment_name_1,first->name))
      {
        break;
      }
      first=first->next;
   }
   while(second)
   {
      if(check_apartment_names(apartment_name_2,second->name))
      {
        break;
      }
      prev=second;
      second=second->next;
   }
   curr=first->flat_list;
   while(curr && curr->next)
   {
      curr=curr->next;
   }
   if(curr && second->flat_list )
   {
      curr->next=second->flat_list;
      second->flat_list->prev=curr;
      second->flat_list=NULL;
      first->max_bandwidth+=second->max_bandwidth;
      if(second==head)
      {
        while (lastnode->next!=head)
        {
          lastnode=lastnode->next;
        }
        lastnode->next=second->next;
        head=second->next;
      }
      else
      {
        prev->next=second->next;
      }
      free(second);
   }
   else
   {
      first->max_bandwidth+=second->max_bandwidth;
      if(second==head)
      {
        while (lastnode->next!=head)
        {
          lastnode=lastnode->next;
        }
        lastnode->next=second->next;
        head=second->next;
      }
      else
      {
        prev->next=second->next;
      }
      free(second);
   }
   
   
  
   return head;
}

void relocate_flats_to_same_apartment(Apartment* head, char* new_apartment_name, int flat_id_to_shift, int* flat_id_list)
{
  Apartment *newap,*track;
  Flat *id_to_shift,*curr;
  int i=0,flag=0;
  newap=head;
  /*  carrying the pointer newap to new apartment  */
  while(newap)
  {
    if(check_apartment_names(new_apartment_name,newap->name))
    {
      break;
    }
    newap=newap->next;
  }
  id_to_shift=newap->flat_list;
  /* carrying the pointer id_to_shift to id to shift under new apartment*/
  while(id_to_shift)
  {
    if(id_to_shift->id==flat_id_to_shift)
    {
      break;
    }
    id_to_shift=id_to_shift->next;
  }

  while(flat_id_list[i]!=0)
  {
    flag=0;
    track=head;
    curr=NULL;
    while(track)
    {
      curr=track->flat_list;
      while(curr)
      {
        if(curr->id==flat_id_list[i])
        {
          flag=1;
          if((curr->prev==NULL) && (curr->next==NULL))
          {
            track->flat_list=NULL;
            if(id_to_shift->prev==NULL)
            {
              curr->next=id_to_shift;
              id_to_shift->prev=curr;
              curr->prev=NULL;
              newap->flat_list=curr;
            }
            else
            {
              /* ortada veya sonda*/
              curr->next=id_to_shift;
              id_to_shift->prev->next=curr;
              curr->prev=id_to_shift->prev;
              id_to_shift->prev=curr;

            }

          }
          else if(curr->prev==NULL)
          {
            /* en başta */
            track->flat_list=curr->next;
            curr->next->prev=NULL;
            /* taşıcağı yerde baştaysa*/
            if(id_to_shift->prev==NULL)
            {
              curr->next=id_to_shift;
              id_to_shift->prev=curr;
              curr->prev=NULL;
              newap->flat_list=curr;
            }
            else
            {
              /* ortada veya sonda*/
              curr->next=id_to_shift;
              id_to_shift->prev->next=curr;
              curr->prev=id_to_shift->prev;
              id_to_shift->prev=curr;

            }
          }
          else if (curr->next==NULL)
          {
            /* en sonda */
            curr->prev->next=NULL;
            if(id_to_shift->prev==NULL)
            {
              curr->next=id_to_shift;
              id_to_shift->prev=curr;
              curr->prev=NULL;
              newap->flat_list=curr;
            }
            else
            {
              curr->next=id_to_shift;
              id_to_shift->prev->next=curr;
              curr->prev=id_to_shift->prev;
              id_to_shift->prev=curr;
            }

          }
          else
          {
            /* ortada */
            curr->prev->next=curr->next;
            curr->next->prev=curr->prev;
            if(id_to_shift->prev==NULL)
            {
              curr->next=id_to_shift;
              id_to_shift->prev=curr;
              curr->prev=NULL;
              newap->flat_list=curr;
            }
            else
            {
              curr->next=id_to_shift;
              id_to_shift->prev->next=curr;
              curr->prev=id_to_shift->prev;
              id_to_shift->prev=curr;
            }

          }
          track->max_bandwidth-=curr->initial_bandwidth;
          newap->max_bandwidth+=curr->initial_bandwidth;
          break;
        }
        curr=curr->next;
      }
      if(flag)
      {
        break;
      }
      track=track->next;
    }
    i++;
  }


}

