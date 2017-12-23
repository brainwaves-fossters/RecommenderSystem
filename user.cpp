//A program to implement Basic Recommendation system using user-user similarity.
//0 is assigned to items which are not rated.
//An item is rated in the scale 1-10.
//A good rating is taken to be above 5


#include<iostream>
#include<math.h>
#include<stdlib.h>
#include<iomanip>

#define USERS 10		//Number of users
#define ITEMS 10		//Number of items

using namespace std;

void normalize( int util_mat[USERS][ITEMS], float norm_mat[USERS][ITEMS] );

void recommend( float norm_mat[USERS][ITEMS], int util_mat[USERS][ITEMS], int user_num );
//Function to recommend items

float cos_similarity( float norm_mat[USERS][ITEMS], int user_num , int ref_user_num );
//to compute cosine distance

char list[ITEMS][30] = { "Harry Potter", "Twilight", "One night at call center", "Five point Someone", "3 Mistakes of my life", "One tree hill", "friends", "Lord of the rings", "2 States", "The Tiger" };


int main()
{
	int util_mat[USERS][ITEMS] = { 
					{ 0, 0, 0, 3, 0, 0, 8, 9, 2, 0 },

					{ 10, 0, 0, 9, 0, 8, 2, 0, 0, 9 },

					{ 0, 0, 0, 3, 0, 10, 9, 8, 3, 0 },

					{ 0, 5, 0, 3, 0, 0, 8, 9, 2, 0 },

					{ 0, 0, 5, 0, 0, 0, 7, 0, 0, 0 },

					{ 0, 5, 0, 0, 0, 0, 8, 9, 2, 9 },
	
					{ 5, 0, 0, 8, 0, 0, 0, 5, 0, 0 },

					{ 0, 5, 0, 10, 2, 0, 0, 3, 0, 0 },

					{ 0, 3, 0, 7, 5, 0, 0, 9, 0, 1 },

					{ 9, 8, 0, 5, 9, 0, 3, 0, 6, 0 },
				};
	
	float norm_mat[USERS][ITEMS];		//to store the normalized matrix
	int i, j;

	normalize( util_mat, norm_mat );	//normalizes utility matrix
	
	while( 1 )
	{
		cout << "1. Recommend items\n2.Display Utility Matrix\n3.Display Normalized matrix\n4.Exit\nEnter your choice : ";	
		int ch;
	
		cin >> ch;
		cout << endl<< endl;
		switch( ch )
		{
			case 1:
				int num;
				cout << "Enter user number [1-10] : ";
				cin >> num;
				cout << "\n";

				num--;
				recommend( norm_mat, util_mat,  num );
				
				break;

			case 2:
				cout << "Item numbers : \n";
				for( j = 0; j < ITEMS; j++ )
					cout << "\t" << j+1 << "." << list[j] << endl;
				cout << endl;
				cout << "Item No" << "\t\t";
				for( j = 0; j < ITEMS; j++ )
					cout << j+1 << "\t";
				cout << endl << endl;
				for( i = 0; i < USERS; i++ )
				{
					cout << "User " << i+1 << "\t\t";
					for( j = 0; j < ITEMS; j++ )
						cout << util_mat[i][j] << "\t";
					cout << endl << endl;
				}
				break;

			case 3:
				cout << "Item numbers : \n";
				for( j = 0; j < ITEMS; j++ )
					cout << "\t" << j+1 << "." << list[j] << endl;
				cout << endl;
				cout << "Item No" << "\t\t";
				for( j = 0; j < ITEMS; j++ )
					cout << setw(3) << j+1 << "\t";
				cout << endl << endl;
				for( i = 0; i < USERS; i++ )
				{
					cout << "User " << i+1 << "\t\t";
					for( j = 0; j < ITEMS; j++ )
						cout << setw(3) << setprecision(2) << norm_mat[i][j] << "\t";
					cout << endl << endl;
				}
				break;


			case 4:
				exit( 0 );
		}
	}
	
	return 0;
}



void normalize( int util_mat[USERS][ITEMS], float norm_mat[USERS][ITEMS] )
{
	int i, j, count, sum = 0;
	float avg = 0;
	
	for( i = 0; i < USERS; i++ )
	{
		sum = 0;
		count = 0;
		for( j = 0; j < ITEMS; j++ )
		{
			if( util_mat[i][j] != 0 )
			{
				count++;
				sum = sum + util_mat[i][j];
			}
		}
		avg = (float) sum / count;		//computing the average rating of that user
		
		for( j = 0; j < ITEMS; j++ )
		{
			if( util_mat[i][j] != 0 )
			{
				norm_mat[i][j] = util_mat[i][j] - avg;		//normalizing the rating
			}
			
			else
				norm_mat[i][j] = 0;		//not rated
		}
	}
}
	
		
void recommend( float norm_mat[USERS][ITEMS], int util_mat[USERS][ITEMS], int user_num )
{
	float cos_dist[USERS] = { 0 };
	int i, j;
	float highest = 0;		//to keep track of the highest cosine distance
	float lowest = 1;

	for( i = 0; i < USERS; i++ )
	{
		if( i != user_num )
			cos_dist[i] = cos_similarity( norm_mat, user_num, i );
		else
			cos_dist[i] = 0;
		if( cos_dist[i] > highest )
			highest = cos_dist[i];
		if( cos_dist[i] < lowest )
			lowest = cos_dist[i];
	}

	for( i = 0; i < USERS; i++ )
	{
		if( i == user_num )
			continue;
		if( cos_dist[i] >= 0 && cos_dist[i] >= highest - 0.3 )
		{
			int flag = 0;
			for( j = 0; j < ITEMS; j++ )
			{
				if(norm_mat[user_num][j] == 0 && norm_mat[i][j] != 0 && util_mat[i][j]>5)
				//if item is not been read by the user and its rating is good
				{
					if( flag == 0 )
						cout << "Recommended by user " << i+1 << " :" << endl;
					cout << "\t\t\t" << "- " << list[j] << "\t";
					cout << " with rating " << util_mat[i][j] << endl;
					flag = 1;
				}
			}
			cout << "\n";
		}
	}

	for( i = 0; i < USERS; i++ )
	{
		if( i == user_num )
			continue;
		if( cos_dist[i] < 0 && cos_dist[i] <= lowest + 0.3 )
		{
			int flag = 0;
			for( j = 0; j < ITEMS; j++ )
			{
				if(norm_mat[user_num][j] == 0 && norm_mat[i][j] != 0 && util_mat[i][j]<5)
				//if item is not been read by the user and its rating is good
				{
					if( flag == 0 )
						cout << "Negative Recommendation by user " << i+1 << " :" << endl;
					cout << "\t\t\t" << "- " << list[j] << "\t";
					cout << " with rating " << util_mat[i][j] << endl;
					flag = 1;
				}
			}
			cout << "\n";
		}
	}

}


float cos_similarity( float norm_mat[USERS][ITEMS], int user_num , int ref_user_num )
{
	int j;
	float numerator = 0;
	float den_user = 0, den_ref = 0;
	float result;
	
	for( j = 0; j < ITEMS; j++ )
	{
		if( norm_mat[user_num][j] != 0 && norm_mat[ref_user_num][j] != 0 )
			numerator = numerator + norm_mat[user_num][j] * norm_mat[ref_user_num][j];
		
		den_user = den_user + norm_mat[user_num][j] * norm_mat[user_num][j];
		den_ref = den_ref + norm_mat[ref_user_num][j] * norm_mat[ref_user_num][j];
	}
	
	result = numerator / ( sqrt( den_user) * sqrt( den_ref ) );
	return result;
}


