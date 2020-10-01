/*Christian Zinck and Syed Taswar Mahbub
 * COMP 11 
 * Lab 1
 * 2/1/2017 
 * Done both Extra Credit 1 and 2
 */

#include <iostream>
using namespace std;

const int SPIDER_TICKETS = 3;
const int MINION_TICKETS = 10;

int main()
{
  int cont = 1;
  while (cont == 1)
  {
  int numMinions = 0, numSpiders = 0, numTickets = 0, leftOverTickets = 0;
  char choice;
  cout << "How many tickets do you have?" << endl;
  cin >> numTickets;
  cout << "If you prefer spiders, enter 's' and if you prefer minions enter 'm'." << endl;
  cin >> choice;
  
  if (choice == 's')
  {
    numSpiders = numTickets/SPIDER_TICKETS;
    leftOverTickets = numTickets%SPIDER_TICKETS;
    cout << "You can get " << numSpiders << " spider with " << leftOverTickets;
    cout << " tickets left over." << endl;
  if (leftOverTickets == 2)
    cout << "You were so close to getting another spider!" << endl;
  else if (leftOverTickets == 1)
    cout << "You were 2 tickets away from getting another spider!" << endl;
  else
    cout << "Congratulations you used all your tickets!" << endl;
  
  }
  else if (choice == 'm')
  {
    if (numTickets % 10 == 0){
    numMinions = numTickets/MINION_TICKETS;
    cout << "You can get " << numMinions << " minions." << endl;
    cout << "Congratulations you used all your tickets!" << endl;
    }
    else{
      numMinions = numTickets/MINION_TICKETS;
      leftOverTickets = numTickets % MINION_TICKETS;
      numSpiders = leftOverTickets / SPIDER_TICKETS;
      leftOverTickets = leftOverTickets % SPIDER_TICKETS;
    cout << "You can get " << numMinions << " minions and " << numSpiders << " spider with ";
    cout << leftOverTickets << " tickets left over." << endl;
    if (leftOverTickets == 2)
    cout << "You were so close to getting another spider!" << endl;
  else if (leftOverTickets == 1)
    cout << "You were 2 tickets away from getting another spider!" << endl;
  else
    cout << "Congratulations you used all your tickets!" << endl;
    }
  }
  else
  {
  cout << "Please enter a lowercase 's' for spiders or 'm' for minions." << endl;
  }
  cout << "Would you like to continue(0-no, 1-yes)?" << endl;
  cin >> cont;
	
  return 0;
  }
}
