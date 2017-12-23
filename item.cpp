//A program to implement Basic Recommendation system using item-item similarity.
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

					{ 10, 9, 0, 9, 0, 8, 2, 0, 0, 9 },

					{ 0, 0, 0, 3, 0, 10, 9, 8, 3, 0 },

					{ 0, 5, 0, 3, 0, 0, 8, 9, 2, 0 },

					{ 0, 0, 5, 0, 0, 0, 7, 0, 0, 0 },

					{ 0, 9, 0, 0, 0, 0, 8, 9, 2, 9 },
	
					{ 5, 0, 0, 8, 0, 0, 0, 5, 0, 0 },

					{ 0, 5, 0, 10, 2, 0, 0, 3, 0, 0 },

					{ 0, 1, 0, 7, 5, 0, 0, 9, 0, 1 },

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
	float cos_dist[ITEMS] = { 0 };
	int i, j, k, flag = 0;
	float highest = 0;		//to keep track of the highest cosine distance
	int high_ndx = -1;
	int count = 0;
	float sum = 0, avg;

	for( k = 0; k < ITEMS; k++ )
	{
		if( util_mat[user_num][k] == 0 )
		{
			for( i = 0; i < ITEMS; i++ )
			{
				if( i != k )
					cos_dist[i] = cos_similarity( norm_mat, k, i );
				else
					cos_dist[i] = 0;
			}	

			sum = 0;
			count = 0;
			for( i = 0; i < 4; i++ )
			{
				highest = 0;
				
				for( j = 0; j < ITEMS; j++ )
				{
					if( cos_dist[j] > highest )
					{
						high_ndx = j;
						highest = cos_dist[j];
					}
				}

				cout << "Highest : " << highest << "\t Ndx : " << high_ndx << endl;
				
				if( highest != 0 )
				{
					sum = sum + util_mat[user_num][high_ndx];
					count++;
				}
			}

			avg = sum / count;

			if( avg > 5 )
			{
				if( flag == 0 )
					cout << "Recommended " << " :" << endl;
				cout << "\t\t" << "- " << list[k] << "\t";
				cout << " with rating " << setprecision(2) << avg << endl;
				flag = 1;
			}

			
		}
	}

}


float cos_similarity( float norm_mat[USERS][ITEMS], int item_num , int ref_item_num )
{
	int j;
	float numerator = 0;
	float den_user = 0, den_ref = 0;
	float result;
	
	for( j = 0; j < USERS; j++ )
	{
		if( norm_mat[j][item_num] != 0 && norm_mat[j][ref_item_num] != 0 )
			numerator = numerator + norm_mat[j][item_num] * norm_mat[j][ref_item_num];
		
		den_user = den_user + norm_mat[j][item_num] * norm_mat[j][item_num];
		den_ref = den_ref + norm_mat[j][ref_item_num] * norm_mat[j][ref_item_num];
	}
	
	result = numerator / ( sqrt( den_user) * sqrt( den_ref ) );
	return result;
}



