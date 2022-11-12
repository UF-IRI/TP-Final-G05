#include "iri.cpp"
#include <iostream>
#include <ctime>

int main() {
   
	time_t now;
	time_t timer;
	struct tm TenyAgo = { 0 };
	double seconds;
	time(&now);

	TenyAgo.tm_hour = 0;   TenyAgo.tm_min = 0; TenyAgo.tm_sec = 0;
	TenyAgo.tm_year = TenyAgo.tm_year - 10; TenyAgo.tm_mon = 0; TenyAgo.tm_mday = 1;

	time(&timer);  /* get current time; same as: timer = time(NULL)  */

	seconds = difftime(now, mktime(&TenyAgo));


}
