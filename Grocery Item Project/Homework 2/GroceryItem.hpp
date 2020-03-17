#pragma once
#include <string> 
#include <iostream>

class GroceryItem
{
        //Stream Insertion and Extraction Operators
		friend std::ostream& operator <<(std::ostream & stream, const GroceryItem & groceryItem);
		friend std::istream& operator >>(std::istream & stream, 	  GroceryItem & groceryItem);
		
		//Inequality and Equality Operator Overloads
		friend bool operator == (const GroceryItem & lhs, const GroceryItem & rhs);
		friend bool operator <  (const GroceryItem & lhs, const GroceryItem & rhs);
		

	public:
		//Constructors
		GroceryItem()= default; 
		GroceryItem( const std::string & productName, 
					 const std::string & UPC 			= {},
			 		 const std::string & brandName 	    = {}, 
			 		 
			 		 double 			 price 			= 0.0 ); //Constructor with Member Initialization
		

		//Mutators
		void upc			(const std::string & upc);
		void brandName		(const std::string & brandName);
		void productName	(const std::string & productName);
		void price			(double 			 price);

		//String Functions
		std::string upc			()const;
		std::string brandName 	()const;
		std::string productName ()const;
		double 		price 		()const;

		

		
		
	private:
		std::string _upc,
					_brandName,
					_productName;
			double _price = 0.0;
};

//Logical Operators 
bool operator == (const GroceryItem & lhs, const GroceryItem & rhs);
bool operator != (const GroceryItem & lhs, const GroceryItem & rhs);

bool operator <  (const GroceryItem & lhs, const GroceryItem & rhs);
bool operator <= (const GroceryItem & lhs, const GroceryItem & rhs);
bool operator >  (const GroceryItem & lhs, const GroceryItem & rhs);
bool operator >= (const GroceryItem & lhs, const GroceryItem & rhs);



