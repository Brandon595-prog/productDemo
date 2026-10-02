#include <iostream> 
#include <iomanip> 
#include <map>  
#include <string> 
#include <numeric> 
#include <algorithm>


using namespace std; 

//display any key value pair regardless of type 
template <typename K,typename V> 
void display_pair(pair<K, V> p) 
{
	cout << p.first << " =$" << p.second << endl; 
	
}

// functor object to check to see if a price is below a limit (functor can store information) 

struct PriceUnder 
{
	double limit; 

	PriceUnder(double l) {
		limit = l; //assign a value directly to the constructor
		
	}
	
	bool operator()(pair<string, double> p) const {
		return p.second < limit; //const guarantees that calling the functor won't change the values or the limit 
		
	}
	
};

int main() 
{

cout << "Product Inventroy\n\n"; 

	map<string, double> products {
		{"Guitar", 199.99}, 
		{"Piano", 799.99}, 
		{"Drums", 249.99}, 
		{"Violin", 489.99},
		{"Flute", 120.50}
	}; 

	cout << "All Products: \n"; 
	for_each(products.begin(), products.end(), display_pair<string, double>); 

	double totalValue = accumulate(products.begin(), products.end(), 0.0, 
		[](double sum, pair<string, double> p){ 
			return sum + p.second;
		}
	); 

	cout << "\nTotal Inventory Value = $" << totalValue << endl; 

	
	double limit = 500.0; 
	int underLimit = count_if(products.begin(), products.end(), PriceUnder(limit)); 
	cout << "NUmber of Products under $" << limit << ": " << underLimit << endl; 

	auto iter = find_if(products.begin(), products.end(), PriceUnder(150)); 
	if (iter != products.end()) {
		cout << "Found product under $150: " << iter->first << " $" << iter->second << endl;
	}
	else {
		cout << "No products found under $150!" << endl;
	} 
	return 0; 
	

}
