#include<stdio.h>

int n,length;
long sender_checksum,receiver_checksum;

long add(long n1, long n2)
{
	long n3=0;
	int t,i=0,remainder=0,sum[length],a[length],b[length];
	while(n1!=0)
	{
		a[i++] = n1 % 10;
		n1 = n1 / 10;
	}
	while(i < length)
		a[i++] = 0;
	i = 0;
	while(n2!=0)
	{
		b[i++] = n2 % 10;
		n2 = n2 / 10;
	}
	while(i < length)
		b[i++] = 0;
	i = 0;
	while(i < length)
    {
        sum[i] = (a[i] + b[i] + remainder) % 2;
        remainder = (a[i] + b[i] + remainder) / 2;
        i++;
    }
    i = 0;
    while(remainder != 0)
    {
    	t = (sum[i] + remainder) % 2;
		remainder = (sum[i] + remainder) / 2;
    	sum[i] = t;
    	i++;
	}
    i=length-1;
    while(i>=0)
    {
    	n3=n3*10+sum[i];
    	i--;
	}
	return n3;
}

long complement(long n1)
{
	int i,a[length];
	while(n1!=0)
	{
		a[i++] = n1 % 10;
		n1 = n1 / 10;
	}
	while(i < length)
		a[i++] = 0;
	i = 0;
	while(i < length)
	{
		if(a[i] == 0)
			a[i] = 1;
		else
			a[i] = 0;
		i++;
	}
	i = length-1;
	while(i>=0)
    {
    	n1=n1*10+a[i];
    	i--;
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
	printf("Enter length of data to be sent : ");
	scanf("%d",&length);
	sender();
	receiver();
	print();
	return 0;
}
