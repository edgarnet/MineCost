/*
 * =====================================================================================
 *
 *       Filename:  miners.cpp
 *
 *    Description:  Determines the profit earned while mining cryptocurrencies with GPUs.
 *    		    Difficulty is adjusted via 'estimated weekly payout'.
 *
 *        Version:  1.0
 *        Created:  11/03/2017 10:10:22 PM
 *       Revision:  Miner information is encapsulated in 'struct miner'.
 *       Compiler:  gcc 7.2.1
 *
 *         Author:  Edgar Perez (eap), edgar.a.perez@wsu.edu
 *   Organization:  Miami Ultras Ltd.
 *
 * =====================================================================================
 */

#include <iostream>

#define 	HOURS 	168
#define		CLS 	"\033[2J\033[1;1H"

struct miner 
{
	int weeks;
	int cards;
	int cap;
	float pDraw;
	float price;
	float power;
};

float revenue( struct miner * serf, float ewp );

void reset( struct miner * serf ) { serf->cards = serf->cap = serf->weeks = serf->power = serf->price = 0; }

int main(void) 
{
	struct miner worker;
	float payout;

	while ( true ) 
	{
		std::cout << "Enter the amount of weeks you will be mining (Press 0 to exit):" << std::endl;
		std::cin >> worker.weeks;
		if ( worker.weeks < 1 ) break; 

		do
		{ 
			std::cout << std::endl << "Enter how many graphics card(s) your have" << std::endl;
			std::cin >> worker.cards;
			
			std::cout << std::endl << "Enter the cost of your graphics card:" << std::endl;
			std::cin >> worker.price;
			
			std::cout << std::endl << "Enter the power draw in kW/h of your card:" << std::endl;
			std::cin >> worker.pDraw;
			
			std::cout << std::endl << "Enter the cost of power per kW/h:" << std::endl;
			std::cin >> worker.power;
			
			std::cout << std::endl << "Enter the estimated weekly payout:" << std::endl;
			std::cin >> payout;
			
			std::cout << std::endl << "Enter a graphics card cap:" << std::endl;
			std::cin >> worker.cap;
			std::cout << CLS;
		} 
		while ( worker.cards < 1 || worker.power < 0 || worker.pDraw < 0 || payout <= 0);
		std::cout << std::endl;

		float total = revenue( &worker, payout );
		std::cout << std::endl << "You made $" << total << " in total revenue after " << worker.weeks << " weeks." << std::endl;
		reset( &worker );
		std::cout << std::endl;
	}

	return 0;
}

float revenue( struct miner * serf, float ewp ) 
{
	float total = 0, check = 0;
	
	for (int i = 1; i <= serf->weeks; i++) 
	{
		check += ewp * serf->cards - HOURS * serf->power * serf->pDraw;
		
		if ( check >= serf->price && serf->cards < serf->cap )
		{
			check = 0;
			serf->cards++;
		}
		else if ( serf->cards >= serf->cap ) 
		{
			total += check;
			check = 0;
		}

		std::cout << "Week: " << i << " | Cards: " << serf->cards << " | Weekly Earnings: " << 10 * serf->cards << " | Total: " << total << std::endl;
	}

	return total;
}
