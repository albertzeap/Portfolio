
#include <cmath>
#include <iostream>
#include <utility>
#include <iomanip>
#include <limits>
#include <string>

#include "GroceryItem.hpp"

namespace
{



	constexpr auto EPSILON = 1.0E-4;
}




//Constructor Definition with Member Initialization
GroceryItem::GroceryItem(const std::string & UPC, 
						 const std::string & brandName, 	
						 const std::string & productName, 
						 double price)
:	_upc(UPC),
 	_brandName(brandName),
  	_productName(productName),
  	_price(price)
{}





//Mutators 
void GroceryItem::upc(const std::string & upc)
{_upc = upc;}

void GroceryItem::brandName(const std::string & brandName)
{	_brandName = brandName;}

void GroceryItem::productName(const std::string & productName)
{_productName = productName;}

void GroceryItem::price(double price)
{_price = price;}




//String Functions Definitions(Get)
std::string GroceryItem::upc() const
{ return _upc;}

std::string GroceryItem::brandName() const
{return _brandName;}

std::string GroceryItem::productName() const
{return _productName;}

double GroceryItem::price() const
{return _price; }






//Stream Insertion and Extraction Definitions
std::istream& operator>>(std::istream& stream, GroceryItem & groceryItem)
{
	GroceryItem workingItem;

	stream >> std::quoted(workingItem._upc         )
		   >> std::quoted(workingItem._brandName   )
		   >> std::quoted(workingItem._productName )
		   >> 			  workingItem._price;

	stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n' );

	groceryItem = std::move(workingItem);

	return stream;

}

std::ostream& operator<<(std::ostream & stream, const GroceryItem & groceryItem)
{
	stream << "UPC: "   	<< std::quoted( groceryItem.upc()         ) << ", "
		   << "Brand: " 	<< std::quoted( groceryItem.brandName()   ) << ", "
		   << "Product: "   << std::quoted( groceryItem.productName() ) << ", "
		   << "Price: $"	<<				groceryItem.price()         << '\n';

	return stream;

}






//Inequality and Equality Operator Overloads Definitions
bool operator == (const GroceryItem & lhs, const GroceryItem & rhs)
{
	if constexpr( (true) )
	{
	 return 	lhs._upc 			== rhs._upc
	 		&&  lhs._productName 	== rhs._productName
			&&  lhs._brandName		== rhs._brandName
			&&  std::abs(lhs._price - rhs._price) < EPSILON;


	}
	else
	{
		return !(lhs < rhs) && !(rhs < lhs);
	}
}
	

bool operator< (const GroceryItem & lhs, const GroceryItem & rhs)
{
	if (auto result = lhs._upc			.compare(rhs._upc		 ); result != 0 ) return result < 0;
	if (auto result = lhs._productName	.compare(rhs._productName); result != 0 ) return result < 0;
	if (auto result = lhs._brandName	.compare(rhs._brandName  ); result != 0 ) return result < 0;
	if (std::abs(lhs._price - rhs._price ) >= EPSILON )

	return false;


}







bool operator != (const GroceryItem & lhs, const GroceryItem & rhs) { return !(lhs == rhs); }
bool operator <= (const GroceryItem & lhs, const GroceryItem & rhs) { return !(rhs < lhs);  }
bool operator >  (const GroceryItem & lhs, const GroceryItem & rhs) { return  (rhs < lhs);  }
bool operator >= (const GroceryItem & lhs, const GroceryItem & rhs) { return !(lhs < rhs);  }






