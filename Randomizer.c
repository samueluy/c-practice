#include <stdio.h>

int main()
{
	srand(time(NULL));
	
	int i, amount, result;
	
	printf("How many names will you randomize?: ");
	scanf("%d", &amount);
	
	char names[amount][20];
	
	for(i = 0; i < amount; i++)
	{
		printf("Enter #%d: ", i+1);
		scanf("%s", &names[i]);
	}
	 
	result = (rand() % (amount - 1));
	
	printf("%s", names[result]);
	
	return 0;
}
