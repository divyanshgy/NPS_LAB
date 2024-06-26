#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define bucket_cap 50
#define token_rate 10
#define num_packets 20

struct TokenBucket{
	int tokens;
};
void initialize (struct TokenBucket *bucket){
	bucket->tokens=0;
}
void addToken(struct TokenBucket *bucket){
	int i;
	if (bucket->tokens < bucket_cap) {
        bucket->tokens++;
    }
}
int getToken(struct TokenBucket *bucket){
	if (bucket->tokens>0){
		bucket->tokens--;
		return 1;
	}
	else{
		return 0;
	}
}
int main(){
	int i;
	struct TokenBucket b1;
	initialize(&b1);

	srand((unsigned int)time(NULL));

	for (i=0;i<num_packets;i++){
		sleep(rand()%3);
		if (getToken(&b1)){
			printf("Packet %d: Congestion avoided. Token granted.\n",i+1);
		}
		else{
			printf("Packet %d: Congestion! Token not granted.\n",i+1);
		}
		addToken(&b1);
	}
	return 0;
}
