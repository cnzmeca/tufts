/* COMP11
 * Spring 2017
 * Lab 3 - Caesar Cipher
 * Christian Zinck, Jonah Vogel, Daniel Geary 
 */

#include <iostream> 
#include <string> 
using namespace std;
 
string encrypt(string, int);
string decrypt(string, int);
int main()
{
	// Variables for the original message,
	// encrypted message, and shift value 
    string message, encryptedMessage;  
    int shift, type;
    cout << "Enter 1 to encrypt or 2 to decrypt";
    cin >> type;
    while ( type != 1 && type != 2)
    {
        cout << "You must enter 1 or 2. \n";
        cout << "Please enter again. \n";
        cin >> type;
    }
    if (type == 1)
    {
    cout << "Please enter a message: "; 
	cin >> message;

    cout << "Please enter a shift.\n";
    cin >> shift; 

	// Validate the shift to be > 0
    while (shift < 1)
    {
        cout << "Shift must be > 0.\n";
        cout << "Please enter again. \n"; 
        cin >> shift; 
    }

	// Call the function to encrypt the
	// original message and report
    encryptedMessage = encrypt(message, shift); 

    cout << "\nEncoded message: " 
		 << encryptedMessage << "\n\n"; 
    }
    else
    {
	cout << "Please enter an encrypted message: ";
        cin >> encryptedMessage;

 	cout << "Please enter a shift.\n";
    	cin >> shift;

        while (shift < 1)
	{
        cout << "Shift must be > 0.\n";
        cout << "Please enter again. \n";
        cin >> shift;
    	}
	message = decrypt(encryptedMessage, shift);
	cout << "\nDecoded message: "
                 << message << "\n\n";
	
    }
    return 0;
}

string encrypt(string message, int shift)
{
	string encryptedMessage = "";
	int messageLength = message.length();
	for (int i = 0; i < messageLength; i++)
	{
		if (message[i] >= 97 && message[i] <= 122)
		{
			encryptedMessage += 97 + ((message[i]-97 + shift)%26);
		}
		else
		{
			encryptedMessage[i] = message[i];
		}
	}
	return encryptedMessage;
}

string decrypt(string encryptedMessage, int shift)
{
        string message = "";
        int encryptedMessageLength = encryptedMessage.length();
        for (int i = 0; i < encryptedMessageLength; i++)
        {
                if (encryptedMessage[i] >= 97 && encryptedMessage[i] <= 122)
                {
			message += 97 + ((encryptedMessage[i]- 97 - shift)%26);
		}
                else
                {
                        message[i] = encryptedMessage[i];
                }
        }
        return message;
}

