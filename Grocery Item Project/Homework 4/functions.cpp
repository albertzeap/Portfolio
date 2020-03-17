#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iomanip>

#include "functions.hpp"
#include "GroceryItemDatabase.hpp"





Inventory_DB loadInventory()
{
  const std::string & filename = "GroceryStoreInventory.dat";
  Inventory_DB  database;

  std::ifstream fin;
  
  try
  {
    fin.exceptions( std::ios::badbit | std::ios::failbit | std::ios::eofbit );

    fin.open( filename, std::ios::binary );

     std::string    upc;
     unsigned int   quantity;      
        
      while(!fin.eof())
      {
        fin >> upc >> quantity;

        database.insert(std::pair <std::string , unsigned int > (upc, quantity)); //inserts the upc and quantity pair into map
      } 
     fin.close();
    
  }

  catch (const std::ios::failure & ex)
  {
    if (!fin.eof())
    {
      database.clear();
      std::cerr << "ERROR opening or reading from " << filename << ", using an empty database\n"
                << "  Error code:  " << ex.code() << '\n'
                << "  Meaning:     " << ex.what() << '\n';
    }
  }
  return database;  
}


void processCustomerShoppingCarts( ShoppingCarts const & shoppingCarts, Inventory_DB & inventory )
{
  double amountDue = 0.0;
  GroceryItemDatabase & storeDataBase = GroceryItemDatabase::instance();

  for( const auto & shopping_iterator : shoppingCarts) //loop that iterates through shoppinCarts
    {
      std::cout << shopping_iterator.first << "'s shopping cart contains: \n"; //Print customer name

            for ( const auto & items_iterator : shopping_iterator.second) //loop that iterates through groceryitems in a cart
            {
                    if( auto grocery = storeDataBase.find( items_iterator.first ) ) 
                    {
                     amountDue += grocery->price();
                     std::cout << std::setw(20) << *grocery;


                     for( auto & stock : inventory) //Decrements the in-store stock of product
                      {
                         if( items_iterator.first == stock.first ) //Checks to see if grocery item is in stock
                          {
                           stock.second = stock.second - 1;
                          }
                      }

                    }
            }

      //Prints the total amount of a customers cart
        std::cout << std::fixed << std::setprecision(2) << std::showpoint << std::string( 15, ' ') <<std::string( 25, '-') << '\n'
        << std::setw(22) << "Total $" << amountDue << '\n' << '\n'; 
        amountDue = 0.0; 
      }


  }




  void reorderItems ( ShoppingCarts const & shoppingCarts, Inventory_DB & inventory )
  {
    
    for (auto & shopping_iterator : shoppingCarts )
    {

      for (auto & items_iterator : shopping_iterator.second)
      {
        


        for (auto & stock : inventory)
        {
          if (items_iterator.first == stock.first && stock.second < 15) //Checks to see if UPC matches and if stock is less than 15
          {
            std::cout << '"' << stock.first << '"' << " at " << stock.second << ',' << " re-ordering 20 more \n";
            stock.second = stock.second + 20;
          }
        }
      
      
      
      }
    }

}



