int main (int argc, string argv[])
{
    // stores the first integer in your command line argument
    int yourNumber = atoi(argv[1]);
    
    // an array of numbers
    int values[] = {1,2,3,4,5,6,7,8,9};
    int numbersInArray = 9;
    
    // create a for loop to iterate over each item in the array
    for (int i = 0; i < numbersInArray; i++)
    {
        // test to see if your number is in the array
        if (values[i] == yourNumber)
        {
            // return true if it is
            printf("Your number %i is in the array :)\n", values[i]);
            return true;
        }
    }
    // return false if it's not
    printf("Your number does not exist in the array :(\n");
    return false;
}
