#include<stdio.h>

int n;
long sender_checksum,receiver_checksum;

long add(long n1, long n2)
{
	long n3=0;
	int i=0,remainder=0,sum[20];
	while (n1 != 0 || n2 != 0)
    {
        sum[i++] =(n1 % 10 + n2 % 10 + remainder) % 2;
        remainder =(n1 % 10 + n2 % 10 + remainder) / 2;
        n1 = n1 / 10;
        n2 = n2 / 10;
    }
    i--;
    while(i>=0)
    {
    	n3=n3*10+sum[i];
    	i--;
	}
	if (remainder != 0)
		return add(n3,1);
	else
		return n3;
}

long complement(long n1)
{
	int r;
	long x=0;
	while(n1!=0)
	{
		r=n1%10;
		if(r==0)
			r=1;
		else
			r=0;
		x=(x*10)+r;
		n1=n1/10;
	}
	while(x!=0)
	{
		r=x%10;
		n1=(n1*10)+r;
		x=x/10;
	}
	return n1;
}

void sender()
{
	int i;
	long sender_data[n],sum=0;
	printf("\n\n===================================================================");
	printf("\nSENDER");
	printf("\n===================================================================");
	printf("\nEnter the data sent : \n");
	for(i=0;i<n;i++)
		scanf("%ld",&sender_data[i]);
	for(i=0;i<n;i++)
		sum=add(sum,sender_data[i]);
	printf("Sender's Sum = %ld",sum);
	sender_checksum = complement(sum);
	printf("\nSender's'Checksum = %ld",sender_checksum);
}

void receiver()
{
	int i;
	long receiver_data[n],sum=0;
	printf("\n\n===================================================================");
	printf("\nRECEIVER");
	printf("\n===================================================================");
	printf("\nEnter the data received : \n");
	for(i=0;i<n;i++)
		scanf("%ld",&receiver_data[i]);
	for(i=0;i<n;i++)
		sum=add(sum,receiver_data[i]);
	printf("Receiver's Sum = %ld",sum);
	sum=add(sum,sender_checksum);
	printf("\nReceiver's Sum after adding Sender's Checksum = %ld",sum);
	receiver_checksum = complement(sum);
	printf("\nReceiver's Checksum = %ld",receiver_checksum);
	
}

void print()
{
	printf("\n\n================================================================");
	if(receiver_checksum==0)
		printf("\n\nSuccessful Transmission of data from sender to receiver.");
	else
		printf("\n\nUnsuccessful Transmission of data from sender to receiver.");
	printf("\n\n================================================================");
}

int main()
{
	printf("Enter number of data to be sent : ");
	scanf("%d",&n);
	sender();
	receiver();
	print();
	return 0;
}
