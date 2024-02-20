#include <iostream>
#include <stdio.h>

using namespace std;

struct node
{
  node *prev;
  int seatstatus;
  node *next;
};

node *head[8] = {NULL};

void displayallseats()
{
  for (int i = 0; i < 8; i++)
  {
    node *temp = head[i];
    printf("%d: \t", i);
    while (temp != NULL)
    {
      if (temp->seatstatus == 0)
        printf("_\t"); // Print underscore for vacant seat
      else
        printf("X\t"); // Print 'X' for filled seat
      temp = temp->next;
    }
    printf("\n");
  }
}

void booktheseat()
{
  int r, numSeats, col;
  printf("Enter the Row number:");
  scanf("%d", &r);

  printf("Enter the number of seats to book:");
  scanf("%d", &numSeats);

  int bookedCount = 0;
  printf("Enter the column numbers to book the seats (starting from 1): ");
  while (bookedCount < numSeats)
  {
    scanf("%d", &col);

    if (col < 1 || col > 6)
    {
      printf("Invalid column number. Please enter a number between 1 and 6.\n");
      continue;
    }

    node *temp = head[r - 1];
    int i = 1;
    while (temp != NULL && i < col)
    {
      temp = temp->next;
      i++;
    }

    if (temp != NULL && temp->seatstatus == 0)
    {
      temp->seatstatus = 1;
      bookedCount++;
    }
    else
    {
      printf("Seat in column %d is already booked or not available.\n", col);
    }
  }

  printf("\n\n%d seats booked successfully in row %d.\n", numSeats, r);
}

void cancelseat()
{
  int r, s;
  printf("Enter the Row number\n");
  scanf("%d", &r);

  printf("Enter the seat number\n");
  scanf("%d", &s);

  node *temp = head[r - 1];
  int i = 0;
  while (i < (s - 1))
  {
    i++;
    temp = temp->next;
  }

  if (temp->seatstatus == 1)
  {
    temp->seatstatus = 0;
    printf("Ticket canceled successfully.\n");
  }
  else
  {
    printf("Seat is already available.\n");
  }
}

int main()
{
  node *previous;
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 6; j++)
    {
      node *temp = new node();
      temp->prev = NULL;
      temp->seatstatus = 0;
      temp->next = NULL;

      if (head[i] == NULL)
      {
        head[i] = temp;
        previous = temp;
      }
      else
      {
        previous->next = temp;
        temp->prev = previous;
        previous = temp;
      }
    }
  }

  int choice = 0;
  while (choice != 4)
  {
    printf("\n\n1.Display the Available Seats\n2.Book the Tickets\n3.Cancel the tickets\n4.Exit\n");
    printf("Enter your Choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
      displayallseats();
      break;
    case 2:
      booktheseat();
      break;
    case 3:
      cancelseat();
      break;
    case 4:
      printf("Exiting...\n");
      break;
    default:
      printf("Invalid choice. Please try again.\n");
    }
  }

  return 0;
}
