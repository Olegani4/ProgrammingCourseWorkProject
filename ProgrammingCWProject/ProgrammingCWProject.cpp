#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <limits>
#include <conio.h>
#include <fstream>
#include <ctime>
#include <algorithm>

/// Headers ///
#include "product.h"
#include "card_details.h"
#include "payment.h"

/// Templates ///
/**
 * @brief Check if the price is greater than or equal to the discounted price.
 * @tparam T Type of template.
 * @param price The price of product.
 * @param discountPrice The price with discount of product.
 * @return 1 (true) or 0 (false).
*/
template<typename T>
T isGreaterOrEqual(T price, T discountPrice) {
	return price >= discountPrice;
}

/// Validation functions ///
/**
 * @brief Check if string is appropriate to convert it to positive double.
 * @param numCheck The string for checking.
 * @return True (if string is appropriate), false (if string is not appropriate).
*/
bool isPosDnumber(std::string numCheck) {
	bool isNum = true;
	for (unsigned int i = 0; i < numCheck.size(); i++)
		if (numCheck[i] < 46 || numCheck[i] == 47 || numCheck[i] > 57 || numCheck[0] == 46) {	// If element of numCheck 
																								// is not a number, excluding ".",
																								// or first element is ".".
			isNum = false;
			break;
		}
	if (isNum == true)
		if (numCheck.size() >= 2)
			if (numCheck[0] == '0' && numCheck[1] != 46)	// If the first element of numCheck is "0" and the second element is not ".".
				isNum = false;
	if (isNum == true)
		if (std::stod(numCheck) == 0)	// If numCheck converted to double == 0.
			isNum = false;
	return isNum;
}
/**
 * @brief Overloaded function. Check if string is appropriate to convert it to positive unsigned int.
 * @param numCheck The string for checking.
 * @return True (if string is appropriate), false (if string is not appropriate).
*/
bool isPosUInumber(std::string numCheck) {
	bool isNum = true;
	for (unsigned int i = 0; i < numCheck.size(); i++)
		if (numCheck[i] < 48 || numCheck[i] > 57 || numCheck[0] == '0') {	// If element of numCheck is not a number or is '0'.
			isNum = false;
			break;
		}
	return isNum;
}
/**
 * @brief Overloaded function. Check if char variable is appropriate to convert it to unsigned int.
 * @param numCheck The char variable for checking.
 * @return True (if char variable is appropriate), false (if char variable is not appropriate).
*/
bool isPosUInumber(char numCheck) {
	bool isNum = true;
	if (numCheck < 48 || numCheck > 57)	// If element of numCheck is not a number.
		isNum = false;
	return isNum;
}

/// Classes functions ///
/**
 * @brief Assign values to data members of class Product.
*/
void Product::dataInput() {
	std::cout << "\n+====================================================================+";
	std::cout << '\n' << "Product name: ";
	std::cin.get(prodName, 256);
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::cout << "Manufacturer: ";
	std::cin.get(manufacturer, 256);
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	while (true) {
		std::cout << "Storage size (GB): ";
		std::string storageSizeStr{};
		std::getline(std::cin, storageSizeStr);
		if (isPosUInumber(storageSizeStr) && storageSizeStr < "999999999") {
			storageSize = std::stoul(storageSizeStr);	// Assign storageSize converted value from string storageSizeStr.
			break;
		}
		else
			std::cout << "!!! - Your storage size input is wrong. Try again.\n";
	}

	std::cout << "Colour: ";
	std::cin.get(colour, 128);
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::string oneMeasure{};
	unsigned int i{};
	while (true) {
		std::cout << "Measure (height) mm: ";
		std::cin >> oneMeasure;

		if (isPosDnumber(oneMeasure)) {
			for (unsigned int j = 0; j < oneMeasure.size(); j++) {
				measures[i] = oneMeasure[j];   // Assign 'j' element of oneMeasure checked string to 'i' element of measure.
				i++;
			}
			// Putting in measures array ' x ' to split measures.
			measures[i] = ' ';
			i++;
			measures[i] = 'x';
			i++;
			measures[i] = ' ';
			i++;
			break;
		}
		else
			std::cout << "!!! - Your measure (height) input is wrong. Try again.\n";
	}

	while (true) {
		std::cout << "Measure (width) mm: ";
		std::cin >> oneMeasure;

		if (isPosDnumber(oneMeasure)) {
			for (unsigned int j = 0; j < oneMeasure.size(); j++) {
				measures[i] = oneMeasure[j];	// Assign 'j' element of oneMeasure checked string to 'i' element of measure.
				i++;
			}
			// Putting again in measures array ' x ' to split measures.
			measures[i] = ' ';
			i++;
			measures[i] = 'x';
			i++;
			measures[i] = ' ';
			i++;
			break;
		}
		else
			std::cout << "!!! - Your measure (width) input is wrong. Try again.\n";
	}

	while (true) {
		std::cout << "Measure (thickness) mm: ";
		std::cin >> oneMeasure;

		if (isPosDnumber(oneMeasure)) {
			for (unsigned int j = 0; j < oneMeasure.size(); j++) {
				measures[i] = oneMeasure[j];	// Assign 'j' element of oneMeasure checked string to 'i' element of measure.
				i++;
			}
			break;
		}
		else
			std::cout << "!!! - Your measure (thickness) input is wrong. Try again.\n";
	}

	while (true) {
		std::cout << "Price (EUR): ";
		std::string priceStr{};
		std::cin >> priceStr;
		if (isPosDnumber(priceStr)) {
			price = std::stod(priceStr);	// Assign checked and converted (to double) string priceStr to price.
			break;
		}
		else
			std::cout << "!!! - Your price input is wrong. Try again.\n";
	}

	while (true) {
		std::cout << "Price with discount (EUR): ";
		std::string discountPriceStr{};
		std::cin >> discountPriceStr;
		if (isPosDnumber(discountPriceStr)) {
			if (isGreaterOrEqual<double>(price, std::stod(discountPriceStr)) == 1) {
				discountPrice = std::stod(discountPriceStr);	// Assign checked and converted (to double) string 
																// discountPriceStr to discountPrice.
				break;
			}
			else
				std::cout << "!!! - The discount price cannot exceed the regular price. Try again.\n";
		}
		else
			std::cout << "!!! - Your price with discount input is wrong. Try again.\n";
	}

	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::cout << "+====================================================================+\n";
}
/**
 * @brief Print values of data members of class Product.
 * @param num The unsigned int to indicate the product number.
*/
void Product::dataOutput(unsigned int num) {

	std::cout << "\n+---------------------------------------------------------------------+\n";
	std::cout << "|#" << num << "|\n";
	std::cout << " > Product name: " << prodName << '\n';
	std::cout << " > Manufacturer: " << manufacturer << '\n';
	std::cout << " > Storage size: " << storageSize << " GB\n";
	std::cout << " > Colour: " << colour << '\n';
	std::cout << " > Measures (height x width x thickness): " << measures << " mm\n";
	std::cout << " > Price: " << price << " EUR\n";
	std::cout << " > Price with discount: " << discountPrice << " EUR\n";
	std::cout << "+---------------------------------------------------------------------+\n";
}
/**
 * @brief Write all products to "all_products.bin" file.
 * @param allProducts Vector of type Product containing all products.
*/
void Product::write_products(std::vector<Product> allProducts) {
	std::string fname = "all_products.bin";
	std::ofstream ofs{ fname, std::ios::binary }; // Binary file creation.

	for (const auto& c : allProducts) {		// Write all products where each data member of class Product is written to the file.
		ofs.write((char*)&c.prodName, sizeof(c.prodName));
		ofs.write((char*)&c.manufacturer, sizeof(c.manufacturer));
		ofs.write((char*)&c.price, sizeof(c.price));
		ofs.write((char*)&c.discountPrice, sizeof(c.discountPrice));
		ofs.write((char*)&c.storageSize, sizeof(c.storageSize));
		ofs.write((char*)&c.colour, sizeof(c.colour));
		ofs.write((char*)&c.measures, sizeof(c.measures));
	}
	ofs.close();

}
/**
 * @brief Read all products to parameter from "all_products.bin" file.
 * @param allProducts Vector of type Product for containing all products.
 * @return Changed parameter allProducts if binary file was opened.
*/
std::vector<Product> Product::read_products(std::vector<Product> allProducts) {
	std::string fname = "all_products.bin";
	std::ifstream ifs{ fname, std::ios::binary };	// Binary file opening.

	Product prodDetails{};

	if (ifs) {		// If file is opened.
		while (!ifs.eof()) {	// Read data.
			ifs.read((char*)&prodDetails.prodName, sizeof(prodDetails.prodName));
			ifs.read((char*)&prodDetails.manufacturer, sizeof(prodDetails.manufacturer));
			ifs.read((char*)&prodDetails.price, sizeof(prodDetails.price));
			ifs.read((char*)&prodDetails.discountPrice, sizeof(prodDetails.discountPrice));
			ifs.read((char*)&prodDetails.storageSize, sizeof(prodDetails.storageSize));
			ifs.read((char*)&prodDetails.colour, sizeof(prodDetails.colour));
			ifs.read((char*)&prodDetails.measures, sizeof(prodDetails.measures));
			if (!ifs.eof())
				allProducts.push_back(prodDetails);
		}
	}
	ifs.close();

	return allProducts;
}
/**
 * @brief Assign values to data members of class CardDetails.
 * @param clientNumInp The unsigned int to indicate the client number.
*/
void CardDetails::dataInput(unsigned int clientNumInp) {
	clientNumber = clientNumInp;

	char cardNumCheck{};

	std::cout << "\nCard number: ";
	for (unsigned int i = 0; i < 19; i++) {
		if (i == 4 || i == 9 || i == 14)
			cardNumber[i] = ' ';	// Put a space after every 4 digits.
		else
			while (true) {
				cardNumCheck = getch();
				if (isPosUInumber(cardNumCheck) || cardNumCheck == 8) {		// If cardNumCheck is a digit or cardNumCheck is a backspace.
					cardNumber[i] = cardNumCheck;
					break;
				}
			}
		std::cout << cardNumber[i];
		if (cardNumber[i] == 8 && i > 0)	// If element of cardNumber is backspace and i is greater than 0.
			i -= 2;		// Return to input of previous element.
		else if (cardNumber[i] == 8 && i == 0) {	// If element of cardNumber is backspace and i is 0.
			std::cout << "\nCard number: ";
			i--;	// Stay on the first cardNumber element.
		}
	}


	std::cout << "\nFirst name: ";
	std::cin.get(firstName, 256);
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	for (unsigned int i = 0; firstName[i] != '\0'; i++)		// For all letters.
		if (firstName[i] >= 97 && firstName[i] <= 122)	// If the letter is not in uppercase then put it in uppercase.
			firstName[i] -= 32;




	std::cout << "Last name: ";
	std::cin.get(lastName, 256);
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	for (unsigned int i = 0; lastName[i] != '\0'; i++)		// For all letters.
		if (lastName[i] >= 97 && lastName[i] <= 122)	// If the letter is not in uppercase then put it in uppercase.
			lastName[i] -= 32;


	char expDateCheck{};
	std::cout << "Expiration date (example: 01/22): ";
	for (unsigned int i = 0; i < 5; i++) {
		if (i == 2)
			expirationDate[i] = '/';	// Put '/' in expirationDate after 2 digits.
		else
			while (true) {
				expDateCheck = getch();
				if (expDateCheck == 8) {	// If expDateCheck == backspace.
					expirationDate[i] = expDateCheck;
					break;
				}
				if (((i == 0 && (expDateCheck == '0' || expDateCheck == '1'))					// If expiration date corresponds to
					|| (i == 1 && (expDateCheck >= '1' && expDateCheck <= '2'))					// such forms: 0(1-9)/xx or 1(1-2)/xx.
					|| (i == 1 && (expirationDate[0] == '0' && expDateCheck != '0'))
					|| (i == 1 && (expirationDate[0] == '1' && expDateCheck == '0'))) || i > 1)
					if (isPosUInumber(expDateCheck)) {		// If expDateCheck is number.
						expirationDate[i] = expDateCheck;
						break;
					}
			}
		std::cout << expirationDate[i];
		if (expirationDate[i] == 8 && i > 0)	// If element of expirationDate is backspace and i is greater than 0.
			i -= 2;		// Return to input of previous element.
		else if (expirationDate[i] == 8 && i == 0) {	// If element of expirationDate is backspace and i is 0.
			std::cout << "\nExpiration date (example: 01/22): ";
			i--;	// Stay on the first expirationDate.
		}
	}

	char cvc_cvv2Check{};
	std::cout << "\nCVC/CVV2: ";
	for (unsigned int i = 0; i < 3; i++) {
		while (true) {
			cvc_cvv2Check = getch();
			if (isPosUInumber(cvc_cvv2Check) || cvc_cvv2Check == 8) {	// If cvc_cvv2Check is number or cvc_cvv2Check is backspace.
				cvc_cvv2[i] = cvc_cvv2Check;
				break;
			}
		}
		std::cout << cvc_cvv2[i];
		if (cvc_cvv2[i] == 8 && i > 0)		// If element of cvc_cvv2 is backspace and i is greater than 0.
			i -= 2;		// Return to input of previous element.
		else if (cvc_cvv2[i] == 8 && i == 0) {		// If element of cvc_cvv2 is backspace and i is 0.
			std::cout << "\nCVC/CVV2: ";
			i--;	// Stay on the first cvc_cvv2 element.
		}
	}


}
/**
 * @brief Print values of data members of class CardDetails.
*/
void CardDetails::dataOutput() {
	std::cout << "\n\n\n+--------------------------------------------------+\n";
	std::cout << "Card number: " << cardNumber << '\n';
	std::cout << "First name: " << firstName << '\n';
	std::cout << "Last name: " << lastName << '\n';;
	std::cout << "Expiration date: " << expirationDate << '\n';
	std::cout << "CVC/CVV2: " << cvc_cvv2 << '\n';
	std::cout << "+--------------------------------------------------+\n";
}
/**
 * @brief Assign values to data members of class CardDetails.
 * @param clProducts Vector of type Product containing selected products.
 * @param clientCard Variable of type CardDetails containing entered card details.
*/
void Payment::dataInput(std::vector <Product> clProducts, CardDetails clientCard) {

	pmtNumber = clientCard.clientNumberRet();	// Assign client number to payment number.

	// Assign values to clFirstName, clLastName, card_4LastDig.
	for (unsigned int i = 0; i < 256; i++)
		clFirstName[i] = clientCard.firstNameRet()[i];
	for (unsigned int i = 0; i < 256; i++)
		clLastName[i] = clientCard.lastNameRet()[i];
	for (unsigned int i = 0; i < 8; i++)
		card_4LastDig[i] = clientCard.cardNumberRet()[i + 15];


	// Assign values to productName(s), totalDiscount, totalPay.
	for (unsigned int i = 0; i < clProducts.size(); i++) {
		char prodNameChRet[256]{};
		for (unsigned int j = 0; j < 256; j++)
			prodNameChRet[j] = clProducts[i].prodNameRet()[j];
		productNames.push_back(prodNameChRet);

		////////////////////////////////////////////////////////
		/// Possibility to add functionality of loyalty card ///
		/// here to turn on below the discount for customer. ///
		////////////////////////////////////////////////////////

		if (false) {
			totalDiscount += clProducts[i].priceRet() - clProducts[i].discountPriceRet();	// totalDiscount += price - price with discount.
			totalPay += clProducts[i].discountPriceRet();	// totalPay = sum of all prices with discount.
		}
		else {
			totalDiscount = 0;
			totalPay += clProducts[i].priceRet();	// totalPay = sum of all prices.
		}
	}


	// Receiving current date and time from computer.
	time_t curr_time;
	curr_time = time(NULL);
	char* timeDate{};
	timeDate = ctime(&curr_time);

	for (unsigned int i = 0; i < 11; i++) {		// Assigning a value to paymDate.
		if (i < 3)
			paymDate[i] = timeDate[i + 8];
		if (i >= 3 && i < 7)
			paymDate[i] = timeDate[i + 1];
		if (i >= 7)
			paymDate[i] = timeDate[i + 13];
	}

	for (unsigned int i = 0; i < 8; i++)	// Assigning a value to paymTime.
		paymTime[i] = timeDate[i + 11];

}
/**
 * @brief Print values of data members of class Payment.
*/
void Payment::dataOutput() {

	std::cout << "\n+-----------------------------------------------+";
	std::cout << "\n|                Your payment:                  |";
	std::cout << "\n+-----------------------------------------------+\n";
	std::cout << " Payment number: #" << pmtNumber << '\n';
	std::cout << " Client name: " << clFirstName << " " << clLastName << '\n';
	std::cout << " Card number: **** **** **** " << card_4LastDig << '\n';
	if (totalDiscount != 0)		/// Works only with loyalty card functionality.
		std::cout << "\n Total discount: " << totalDiscount << " EUR";
	std::cout << "\n Total pay: " << totalPay << " EUR\n";
	std::cout << "\n Payment date: " << paymDate;
	std::cout << "\n Payment time: " << paymTime << '\n';

	std::cout << "\n+-----------------------------------------------+";
	std::cout << "\n|               Your products:                  |";
	std::cout << "\n+-----------------------------------------------+\n";
	for (unsigned int i = 0; i < productNames.size(); i++) {
		std::cout << " > Product " << (i + 1) << ": "
			<< productNames[i] << '\n';
	}
	std::cout << "+-----------------------------------------------+\n\n";
}
/**
 * @brief Write all products to "payments.bin" file.
 * @param payments Vector of type Payment containing all payments.
*/
void Payment::write_payments(std::vector <Payment> payments) {
	std::string fname = "payments.bin";
	std::ofstream ofs{ fname, std::ios::binary };	 // Binary file creation.

	for (unsigned int i = 0; i < payments.size(); i++) {	// For all payments.
		payments[i].prodNumber = payments[i].productNames.size();	// Assign the size of vector containing product names to prodNumber.
		ofs.write((char*)&payments[i].prodNumber, sizeof(payments[i].prodNumber));	// Write prodNumber to the file.

		for (unsigned int j = 0; j < payments[i].productNames.size(); j++) {	// Write all product names to the file.
			char productNamesCh[256]{};
			for (unsigned int n = 0; n < payments[i].productNames[j].size(); n++)
				productNamesCh[n] = payments[i].productNames[j][n];
			ofs.write((char*)&productNamesCh, sizeof(productNamesCh));
		}
		// Write other data members of class Payment to the file.
		ofs.write((char*)&payments[i].pmtNumber, sizeof(payments[i].pmtNumber));
		ofs.write((char*)&payments[i].clFirstName, sizeof(payments[i].clFirstName));
		ofs.write((char*)&payments[i].clLastName, sizeof(payments[i].clLastName));
		ofs.write((char*)&payments[i].card_4LastDig, sizeof(payments[i].card_4LastDig));
		ofs.write((char*)&payments[i].totalDiscount, sizeof(payments[i].totalDiscount));
		ofs.write((char*)&payments[i].totalPay, sizeof(payments[i].totalPay));
		ofs.write((char*)&payments[i].paymDate, sizeof(payments[i].paymDate));
		ofs.write((char*)&payments[i].paymTime, sizeof(payments[i].paymTime));
	}
	ofs.close();


}
/**
 * @brief Read all payments to parameter from "all_products.bin" file.
 * @param payments Vector of type Payment for containing all payments.
 * @return Changed parameter payments if binary file was opened.
*/
std::vector<Payment> Payment::read_payments(std::vector <Payment> payments) {
	std::string fname = "payments.bin";
	std::ifstream ifs{ fname, std::ios::binary };	// Binary file opening.

	Payment payDetails;		/// Variable for pushing back the parameter.

	if (ifs) {	// If file is opened.

		while (!ifs.eof()) {
			ifs.read((char*)&payDetails.prodNumber, sizeof(payDetails.prodNumber));		// Read the number of product names.

			for (unsigned int i = 0; i < payDetails.prodNumber; i++) {		// For all product names.
				char prodName[256]{}; /// Variable for product name storage.
				ifs.read((char*)&prodName, sizeof(prodName));	// Read product name.
				payDetails.productNames.push_back(prodName);	// Push back prodName to the vector.
			}

			// Read other data members of class Payment to the payDetails.
			ifs.read((char*)&payDetails.pmtNumber, sizeof(payDetails.pmtNumber));
			ifs.read((char*)&payDetails.clFirstName, sizeof(payDetails.clFirstName));
			ifs.read((char*)&payDetails.clLastName, sizeof(payDetails.clLastName));
			ifs.read((char*)&payDetails.card_4LastDig, sizeof(payDetails.card_4LastDig));
			ifs.read((char*)&payDetails.totalDiscount, sizeof(payDetails.totalDiscount));
			ifs.read((char*)&payDetails.totalPay, sizeof(payDetails.totalPay));
			ifs.read((char*)&payDetails.paymDate, sizeof(payDetails.paymDate));
			ifs.read((char*)&payDetails.paymTime, sizeof(payDetails.paymTime));

			if (!ifs.eof())
				payments.push_back(payDetails);
			payDetails.productNames.clear();	// Clear vector for new product names.
		}
	}
	ifs.close();
	return payments;
}

/// Sort functions ///		
/**
 * @brief Check vector products by names A-Z via comparing products' members of two vector elements.
 * @param prod1 Referenced constant variable of type Product.
 * @param prod2 Referenced constant variable of type Product.
 * @return True (if prodNameStr1 alphabetically less than prodNameStr2),
		   false (if prodNameStr1 alphabetically greater than prodNameStr2).
*/
bool productSort(const Product& prod1, const Product& prod2)
{
	std::string prodNameStr1{};
	std::string prodNameStr2{};
	for (unsigned int i = 0; prod1.prodName[i] != '\0'; i++)
		prodNameStr1.push_back(prod1.prodName[i]);	// Assign to string the values of char array.
	for (unsigned int i = 0; prod2.prodName[i] != '\0'; i++)
		prodNameStr2.push_back(prod2.prodName[i]);	// Assign to string the values of char array.
	return prodNameStr1 < prodNameStr2;
}
/**
 * @brief Check vector products manufacturers A-Z via comparing products' members of two vector elements.
 * @param prod1 Referenced constant variable of type Product.
 * @param prod2 Referenced constant variable of type Product.
 * @return True (if prodManufacStr1 alphabetically less than prodManufacStr2),
		   false (if prodManufacStr1 alphabetically greater than prodManufacStr2).
*/
bool manufacturerSort(const Product& prod1, const Product& prod2)
{
	std::string prodManufacStr1{};
	std::string prodManufacStr2{};
	for (unsigned int i = 0; prod1.manufacturer[i] != '\0'; i++)
		prodManufacStr1.push_back(prod1.manufacturer[i]);	// Assign to string the values of char array.
	for (unsigned int i = 0; prod2.manufacturer[i] != '\0'; i++)
		prodManufacStr2.push_back(prod2.manufacturer[i]);	// Assign to string the values of char array.
	return prodManufacStr1 < prodManufacStr2;
}
/**
 * @brief Check vector products prices via comparing price of first product to price of second product.
 * @param prod1 Referenced constant variable of type Product.
 * @param prod2 Referenced constant variable of type Product.
 * @return True (if price of first product is less than price of second product),
 *		   false (if price of first product is greater than price of second product).
*/
bool lowestPriceSort(const Product& prod1, const Product& prod2)
{
	return prod1.price < prod2.price;
}
/**
 * @brief Check vector products prices via comparing price of first product to price of second product.
 * @param prod1 Referenced constant variable of type Product.
 * @param prod2 Referenced constant variable of type Product.
 * @return True (if price of first product is greater than price of second product),
 *		   false (if price of first product is less than price of second product).
*/
bool highestPriceSort(const Product& prod1, const Product& prod2)
{
	return prod1.price > prod2.price;
}
/**
 * @brief Check vector products storage sizes via comparing storage size of first product to storage size of second product.
 * @param prod1 Referenced constant variable of type Product.
 * @param prod2 Referenced constant variable of type Product.
 * @return True (if storage size of first product is less than storage size of second product),
 *		   false (if storage size of first product is greater than storage size of second product).
*/
bool lowestStrgSizeSort(const Product& prod1, const Product& prod2)
{
	return prod1.storageSize < prod2.storageSize;
}
/**
 * @brief Check vector products storage sizes via comparing storage size of first product to storage size of second product.
 * @param prod1 Referenced constant variable of type Product.
 * @param prod2 Referenced constant variable of type Product.
 * @return True (if storage size of first product is greater than storage size of second product),
 *		   false (if storage size of first product is less than storage size of second product).
*/
bool highestStrgSizeSort(const Product& prod1, const Product& prod2)
{
	return prod1.storageSize > prod2.storageSize;
}
/**
 * @brief Check vector products by colours A-Z via comparing products' members of two vector elements.
 * @param prod1 Referenced constant variable of type Product.
 * @param prod2 Referenced constant variable of type Product.
 * @return True (if prodColStr1 alphabetically less than prodColStr2),
		   false (if prodColStr1 alphabetically greater than prodColStr2).
*/
bool colourSort(const Product& prod1, const Product& prod2)
{
	std::string prodColStr1{};
	std::string prodColStr2{};
	for (unsigned int i = 0; prod1.colour[i] != '\0'; i++)
		prodColStr1.push_back(prod1.colour[i]);	// Assign to string the values of char array.
	for (unsigned int i = 0; prod2.colour[i] != '\0'; i++)
		prodColStr2.push_back(prod2.colour[i]);	// Assign to string the values of char array.
	return prodColStr1 < prodColStr2;
}
///><///

/// Filter functions ///
/**
 * @brief Filter products by input name.
 * @param allProducts Vector of type Product for containing all products.
 * @param allProductsFiltered Vector of type Product for containing filtered products.
 * @return Vector containing filtered products.
*/
std::vector <Product> productNamesFltr(std::vector <Product> allProducts, std::vector <Product> allProductsFiltered)
{
	char nameFltr[256]{};
	std::cout << "\nPress ENTER to get list of all products.";
	std::cout << "\nEnter the name of product you want to find: ";
	std::cin.get(nameFltr, 256);
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	for (unsigned int i = 0; i < allProducts.size(); i++) {		// For all elements of vector allProducts.
		char* productNameRet = allProducts[i].prodNameRet();	// Assign product name to char pointer productNameRet.
		bool returnCheck = true;
		for (unsigned int j = 0; nameFltr[j] != '\0'; j++) {	// For input nameFltr.
			if (j == 0) {	// For first element of nameFltr check uppercase and lowercase letter for a match with product names.
				if (nameFltr[j] != productNameRet[j] && nameFltr[j] - 32 != productNameRet[j]) {
					returnCheck = false;
					break;
				}
			}
			else	// For other elements of nameFltr check for a match with product names.
				if (nameFltr[j] != productNameRet[j]) {
					returnCheck = false;
					break;
				}
		}
		if (returnCheck == true)	// If the beginning of productNameRet is the same with nameFltr.
			allProductsFiltered.push_back(allProducts[i]);	// Add product to filtered vector.
	}
	if (allProductsFiltered.size() == 0) {
		system("cls");
		std::cout << "\n+--------------------------------------------------+\n";
		std::cout << "| ! - There are no products matching your request. |\n";
		std::cout << "+--------------------------------------------------+\n";
		system("pause");
	}
	return allProductsFiltered;
}
/**
 * @brief Filter products by input manufacturer.
 * @param allProducts Vector of type Product for containing all products.
 * @param allProductsFiltered Vector of type Product for containing filtered products.
 * @return Vector containing filtered products.
*/
std::vector <Product> manufacturersFltr(std::vector <Product> allProducts, std::vector <Product> allProductsFiltered)
{
	char manufacturerFltr[256]{};
	std::cout << "\nPress ENTER to get list of all products.";
	std::cout << "\nEnter the manufacturer you want to find: ";
	std::cin.get(manufacturerFltr, 256);
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	for (unsigned int i = 0; i < allProducts.size(); i++) {		// For all elements of vector allProducts.
		char* manufacturerRet = allProducts[i].manufacturerRet();	// Assign manufacturer to char pointer manufacturerRet.
		bool returnCheck = true;
		for (unsigned int j = 0; manufacturerFltr[j] != '\0'; j++) {	// For input manufacturerFltr.
			if (j == 0) {	// For first element of manufacturerFltr check uppercase and lowercase letter for a match with product manufacturers.
				if (manufacturerFltr[j] != manufacturerRet[j] && manufacturerFltr[j] - 32 != manufacturerRet[j]) {
					returnCheck = false;
					break;
				}
			}
			else	// For other elements of manufacturerFltr check for a match with product manufacturers.
				if (manufacturerFltr[j] != manufacturerRet[j]) {
					returnCheck = false;
					break;
				}
		}
		if (returnCheck == true)	// If the beginning of manufacturerRet is the same with manufacturerFltr.
			allProductsFiltered.push_back(allProducts[i]);	// Add product to filtered vector.
	}
	if (allProductsFiltered.size() == 0) {
		system("cls");
		std::cout << "\n+--------------------------------------------------+\n";
		std::cout << "| ! - There are no products matching your request. |\n";
		std::cout << "+--------------------------------------------------+\n";
		system("pause");
	}
	return allProductsFiltered;
}
/**
 * @brief Filter products by input storage size.
 * @param allProducts Vector of type Product for containing all products.
 * @param allProductsFiltered Vector of type Product for containing filtered products.
 * @return Vector containing filtered products.
*/
std::vector <Product> storageSizeFltr(std::vector <Product> allProducts, std::vector <Product> allProductsFiltered)
{
	unsigned int storageSize{};
	std::string storageSizeStr{};
	std::cout << "\nPress ENTER to get list of all products.";
	while (true) {
		std::cout << "\nEnter the storage size you want to find (GB): ";
		std::getline(std::cin, storageSizeStr);
		if (storageSizeStr.size() == 0)		// If ENTER pressed.
			return allProducts;
		if (isPosUInumber(storageSizeStr) && storageSizeStr < "999999999") {		// Check if input is positive unsigned int.
			storageSize = std::stoul(storageSizeStr);	// Convert string to unsigned int.
			break;
		}
		else
			std::cout << "!!! - Your storage size input is wrong. Try again.\n";
	}

	for (unsigned int i = 0; i < allProducts.size(); i++)
		if (allProducts[i].storageSizeRet() == storageSize)	// If any product's storage size matches with input storageSize.
			allProductsFiltered.push_back(allProducts[i]);	// Add product to filtered vector. 

	if (allProductsFiltered.size() == 0) {
		system("cls");
		std::cout << "\n+--------------------------------------------------+\n";
		std::cout << "| ! - There are no products matching your request. |\n";
		std::cout << "+--------------------------------------------------+\n";
		system("pause");
	}
	return allProductsFiltered;
}
/**
 * @brief Filter products by input storage size.
 * @param allProducts Vector of type Product for containing all products.
 * @param allProductsFiltered Vector of type Product for containing filtered products.
 * @return Vector containing filtered products.
*/
std::vector <Product> colourFltr(std::vector <Product> allProducts, std::vector <Product> allProductsFiltered)
{
	char colourFltr[256]{};
	std::cout << "\nPress ENTER to get list of all products.";
	std::cout << "\nEnter the colour you want to find: ";
	std::cin.get(colourFltr, 128);
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	for (unsigned int i = 0; i < allProducts.size(); i++) {		// For all elements of vector allProducts.
		char* colourRet = allProducts[i].colourRet();	// Assign product colour to char pointer colourRet.
		bool returnCheck = true;
		for (unsigned int j = 0; colourFltr[j] != '\0'; j++) {	// For input colourFltr.
			if (j == 0) {	// For first element of colourFltr check uppercase and lowercase letter for a match with product colours.
				if (colourFltr[j] != colourRet[j] && colourFltr[j] - 32 != colourRet[j]) {
					returnCheck = false;
					break;
				}
			}
			else	// For other elements of colourFltr check for a match with product colours.
				if (colourFltr[j] != colourRet[j]) {
					returnCheck = false;
					break;
				}
		}
		if (returnCheck == true)	// If the beginning of colourRet is the same with colourFltr.
			allProductsFiltered.push_back(allProducts[i]);	// Add product to filtered vector.
	}

	if (allProductsFiltered.size() == 0) {
		system("cls");
		std::cout << "\n+--------------------------------------------------+\n";
		std::cout << "| ! - There are no products matching your request. |\n";
		std::cout << "+--------------------------------------------------+\n";
		system("pause");
	}
	return allProductsFiltered;
}
/**
 * @brief Filter products by input of minimal price and maximal price.
 * @param allProducts Vector of type Product for containing all products.
 * @param allProductsFiltered Vector of type Product for containing filtered products.
 * @return Vector containing filtered products.
*/
std::vector <Product> priceFltr(std::vector <Product> allProducts, std::vector <Product> allProductsFiltered)
{
	double minPrice{};
	double maxPrice{};
	std::string minPriceStr{};
	std::string maxPriceStr{};

	std::cout << "\nPress ENTER to get list of all products.";
	while (true) {
		std::cout << "\n\nEnter the minimal price (EUR): ";
		std::getline(std::cin, minPriceStr);
		if (minPriceStr.size() == 0)		// If ENTER pressed.
			return allProducts;
		if (minPriceStr == "0") {
			minPrice = std::stod(minPriceStr);	// Convert string to double.
			break;
		}
		if (isPosDnumber(minPriceStr)) {	// Check if input is positive double.
			minPrice = std::stod(minPriceStr);	// Convert string to double.
			break;
		}
		else
			std::cout << "!!! - Your minimal price input is wrong. Try again.";
	}

	while (true) {
		std::cout << "Enter the maximal price (EUR): ";
		std::getline(std::cin, maxPriceStr);
		if (maxPriceStr.size() == 0)		// If ENTER pressed.
			return allProducts;
		if (isPosDnumber(maxPriceStr)) {	// Check if input is positive double.
			maxPrice = std::stod(maxPriceStr);	// Convert string to double.
			if (minPrice > maxPrice)
				std::cout << "!!! - Minimal price cannot be greater than maximal price.\n\n";
			else
				break;
		}
		else
			std::cout << "!!! - Your maximal price input is wrong. Try again.\n\n";
	}


	for (unsigned int i = 0; i < allProducts.size(); i++)
		if (allProducts[i].priceRet() >= minPrice && allProducts[i].priceRet() <= maxPrice)		// If product price is within 
																								// the range of entered values.
			allProductsFiltered.push_back(allProducts[i]);	// Add product to filtered vector. 

	if (allProductsFiltered.size() == 0) {
		system("cls");
		std::cout << "\n+--------------------------------------------------+\n";
		std::cout << "| ! - There are no products matching your request. |\n";
		std::cout << "+--------------------------------------------------+\n";
		system("pause");
	}
	return allProductsFiltered;
}

/// Menus functions ///
/**
 * @brief Print Main Menu.
*/
void mainMenuOutput() {
	std::cout << "\n+--------------------------+\n";
	std::cout << "|         Main Menu        |\n";
	std::cout << "+---+----------------------+\n";
	std::cout << "| 1 | Get list of products |\n";
	std::cout << "+---+----------------------+\n";
	std::cout << "| 2 | Go to shopping cart  |\n";
	std::cout << "+---+----------------------+\n";
	std::cout << "| 3 | Check my payment     |\n";
	std::cout << "+---+----------------------+\n";
	std::cout << "| 4 | Manage products      |\n";
	std::cout << "|   | (needs permissions)  |\n";
	std::cout << "+---+----------------------+\n";


	std::cout << "\nPress ESC to exit the programme.";
	std::cout << "\nEnter number of menu option: ";
}
/**
 * @brief Print Product Filter Menu and pass vector allProducts through selected by user filter option.
 * @param allProducts Vector of type Product containing all products.
 * @return Vector of type Product containing filtered products.
*/
std::vector <Product> allProductsFilter(std::vector <Product> allProducts) {
	std::vector <Product> allProductsFiltered{};

	while (true) {
		system("cls");

		std::cout << "\n+-----------------------------+\n";
		std::cout << "|     Product Filter Menu     |\n";
		std::cout << "+---+-------------------------+\n";
		std::cout << "| 1 | Filter by name          |\n";
		std::cout << "+---+-------------------------+\n";
		std::cout << "| 2 | Filter by manufacturer  |\n";
		std::cout << "+---+-------------------------+\n";
		std::cout << "| 3 | Filter by storage size  |\n";
		std::cout << "+---+-------------------------+\n";
		std::cout << "| 4 | Filter by colour        |\n";
		std::cout << "+---+-------------------------+\n";
		std::cout << "| 5 | Filter by price         |\n";
		std::cout << "+---+-------------------------+\n";

		std::cout << "\nPress ESC to return to Main Menu.";
		std::cout << "\nEnter number of menu option you want to sort products: ";

		bool escPFM = true;
		char optionPSM = getch();
		std::cout << optionPSM;

		switch (optionPSM) {

		case '1':
			allProductsFiltered = productNamesFltr(allProducts, allProductsFiltered);
			break;

		case '2':
			allProductsFiltered = manufacturersFltr(allProducts, allProductsFiltered);
			break;

		case '3':
			allProductsFiltered = storageSizeFltr(allProducts, allProductsFiltered);
			break;

		case '4':
			allProductsFiltered = colourFltr(allProducts, allProductsFiltered);
			break;

		case '5':
			allProductsFiltered = priceFltr(allProducts, allProductsFiltered);
			sort(allProductsFiltered.begin(), allProductsFiltered.end(), lowestPriceSort);
			break;

		case 27:	// Escape option.
			allProducts.clear();	// To determine further the choice of this option.
			break;

		default:
			escPFM = false;
			break;
		}
		if (escPFM == true)
			break;
	}

	return allProductsFiltered;
}
/**
 * @brief Print Products Sort Menu and pass vector allProducts through selected by user sort option.
 * @param allProducts Vector of type Product containing all products.
 * @return Sorted parameter.
*/
std::vector <Product> allProductsSort(std::vector <Product> allProducts) {
	while (true) {
		system("cls");

		std::cout << "\n+--------------------------+\n";
		std::cout << "|    Products Sort Menu    |\n";
		std::cout << "+---+----------------------+\n";
		std::cout << "| 1 | Product names (A-Z)  |\n";
		std::cout << "+---+----------------------+\n";
		std::cout << "| 2 | Manufacturers (A-Z)  |\n";
		std::cout << "+---+----------------------+\n";
		std::cout << "| 3 | Lowest price on top  |\n";
		std::cout << "+---+----------------------+\n";
		std::cout << "| 4 | Highest price on top |\n";
		std::cout << "+---+----------------------+\n";
		std::cout << "| 5 | Lowest storage size  |\n";
		std::cout << "|   | on top               |\n";
		std::cout << "+---+----------------------+\n";
		std::cout << "| 6 | Highest storage size |\n";
		std::cout << "|   | on top               |\n";
		std::cout << "+---+----------------------+\n";
		std::cout << "| 7 | Colour (A-Z)         |\n";
		std::cout << "+---+----------------------+\n";

		std::cout << "\nPress ESC to return to Main Menu.";
		std::cout << "\nEnter number of menu option you want to sort products: ";

		bool escPSM = true;
		char optionPSM = getch();
		std::cout << optionPSM;

		switch (optionPSM) {

		case '1':
			sort(allProducts.begin(), allProducts.end(), productSort);
			break;

		case '2':
			sort(allProducts.begin(), allProducts.end(), manufacturerSort);
			break;

		case '3':
			sort(allProducts.begin(), allProducts.end(), lowestPriceSort);
			break;

		case '4':
			sort(allProducts.begin(), allProducts.end(), highestPriceSort);
			break;

		case '5':
			sort(allProducts.begin(), allProducts.end(), lowestStrgSizeSort);
			break;

		case '6':
			sort(allProducts.begin(), allProducts.end(), highestStrgSizeSort);
			break;

		case '7':
			sort(allProducts.begin(), allProducts.end(), colourSort);
			break;

		case 27:	// Escape option.
			allProducts.clear();	// To determine further the choice of this option.
			break;

		default:
			escPSM = false;
			break;

		}
		if (escPSM == true)
			break;
	}

	return allProducts;
}
///><///


int main() {
	/// Declaration & initialization of basic variables and vectors ///
	std::vector <Product> allProducts{};
	std::vector <Product> clProducts{};
	Product anyProduct{};
	CardDetails clientCard{};
	std::vector <Payment> payments{};
	Payment clientPayment{};
	Payment clPaymentClr{};
	///><///

	/// Loading data from files to programme ///
	allProducts = anyProduct.read_products(allProducts);
	payments = clientPayment.read_payments(payments);
	///><///

	std::vector <Product> allProductsSave = allProducts;	// Create allProducts save.

	bool escMM = false;
	bool escAM = false;

	while (!escMM) {	// Main programme loop.

		allProducts = allProductsSave;	// Refresh allProducts.

		system("cls");
		mainMenuOutput();	// Call Main Menu.

		char optionMM = getch();	//	Get Main Menu option from the user.
		std::cout << optionMM;

		/// Declaration & initialization of variables for Main Menu options ///
		unsigned int paymentNum{};
		unsigned int prodNum{};
		std::string paymentNumStr{};
		std::string prodNumStr{};

		char optionYesNo{};
		char filterOption{};

		double totalPay{};
		double totalDiscountPay{};
		///><///

		switch (optionMM) {
		case '1':	// Get list of products.
			if (allProducts.size() > 0) {	// If any product exists.
				allProducts = allProductsSort(allProducts);		// Call sort function.
				if (allProducts.size() == 0) {	// Escape to Main Menu was selected in sort function.
					break;
				}

				while (true) {	// Product filtering.
					system("cls");
					std::cout << "\nDo you want to filter products?\n";

					std::cout << "+---+-----+\n";
					std::cout << "| 1 | Yes |\n";
					std::cout << "+---+-----+\n";
					std::cout << "| 2 | No  |\n";
					std::cout << "+---+-----+\n";

					std::cout << "Enter the number of option: ";
					filterOption = getch();		//	Get filter option from the user.
					std::cout << filterOption;

					if (filterOption == '1') {	// If yes.
						allProducts = allProductsFilter(allProducts);	// Call filter function.
						break;
					}
					else if (filterOption == '2') {	// If no.
						system("cls");
						break;
					}
				}

				if (allProducts.size() == 0) { // Escape to Main Menu was selected in filter function.

					break;
				}

				std::cout << "\n_______________________________Products________________________________\n";
				for (unsigned int i = 0; i < allProducts.size(); i++)	// Print products after sorting and filtering (if it was).
					allProducts[i].dataOutput(i + 1);
				std::cout << "\nIf you don't want to select anything, type '0'.";

				while (true) {	// Add product to the shopping cart.
					std::cout << "\nType number of product you would like to add to your shopping cart: ";
					std::cin >> prodNumStr;
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					if (prodNumStr == "0")	// Escape Add product loop to escape to Main Menu.
						break;
					if (isPosUInumber(prodNumStr) && prodNumStr < "999999999") {	// Number validation.	
						prodNum = std::stoul(prodNumStr);	// Convert string to unsigned int.
						break;
					}
					else
						std::cout << "!!! - Your product number input is wrong. Try again.\n";
				}
				if (prodNumStr == "0")	// Escape to Main Menu option.
					break;
				prodNum -= 1;	// To determine a position in the allProducts vector. 
								// Product number is greater by 1 than the position in the vector.

				clProducts.push_back(allProducts[prodNum]);		// Push back clProducts vector with product selected by user.

				std::cout << "\nChoosen product successfully added to your shopping cart!\n";
				system("pause");
			}
			else {
				system("cls");
				std::cout << "\n+----------------------------------+\n";
				std::cout << "| ! - There is no any product yet. |\n";
				std::cout << "+----------------------------------+\n";
				system("pause");
			}
			break;

		case '2':	// Go to shopping cart.
			system("cls");

			if (clProducts.size() > 0) {	// If at least one product has been selected by the user.
				std::cout << "\n+--------------------------------------------------+\n";
				std::cout << "|                Your shopping cart                |\n";
				std::cout << "+--------------------------------------------------+\n";
				for (unsigned int i = 0; i < clProducts.size(); i++) {
					clProducts[i].dataOutput(i + 1);	// Print out all products selected by the user.
					totalPay += clProducts[i].priceRet();	// Count total pay of all products prices sum.
					totalDiscountPay += clProducts[i].discountPriceRet(); // Count total pay of all products prices sum.
				}
				std::cout << "\n >> Total pay: " << totalPay << " EUR";
				std::cout << "\n >> Total pay with discount: " << totalDiscountPay << " EUR\n";

				while (true) {	// Offer to make a purchase or postpone it.
					std::cout << "\nWould you like to complete your shopping and go to payment process?\n";
					std::cout << "Type 'Y' if yes, type 'N' if no: ";

					optionYesNo = getch();
					std::cout << optionYesNo << '\n';


					if (optionYesNo == 'Y' || optionYesNo == 'y') {		// If yes.
						while (true) {
							system("cls");
							std::cout << "Please enter your card details.\n";
							clientCard.dataInput(payments.size() + 1);	// Card details input.
							clientCard.dataOutput();

							while (true) {	// Card details check offer and payment creation.
								std::cout << "\nAre the card details correct?\n";
								std::cout << "Type 'Y' if yes, type 'N' if no: ";
								optionYesNo = getch();
								std::cout << optionYesNo << '\n';

								if (optionYesNo == 'Y' || optionYesNo == 'y') {		// If yes (card details are correct).

									clientPayment.dataInput(clProducts, clientCard);	// Payment creation.

									///////////////////////////////////////////////////////////
									/// Possibility to add card payment functionality here. ///
									///////////////////////////////////////////////////////////

									payments.push_back(clientPayment);		// Push back payment to payments vector.
									clientPayment.write_payments(payments);		// Call payments write function.
									clProducts.clear();		// Clear clProducts vector from selected products.

									system("cls");
									clientPayment.dataOutput();		// Print out client payment.
									system("pause");

									clientPayment = clPaymentClr;	// Clear clientPayment variable.

									optionYesNo = 'N';	// Set 'N' value to optionYesNo to return to Main Menu.
									break;
								}
								else if (optionYesNo == 'N' || optionYesNo == 'n') {	// If no (card details are not correct).
									system("cls");
									std::cout << "Please enter your card details.\n";
									clientCard.dataInput(payments.size() + 1);		// Card details input again.
									clientCard.dataOutput();
								}
							}
							if (optionYesNo == 'N' || optionYesNo == 'n')
								break;
						}
						break;
					}
					else if (optionYesNo == 'N' || optionYesNo == 'n')	// If no.
						break;
				}
			}
			else {
				std::cout << "\n+------------------------------------------------------+\n";
				std::cout << "| ! - There is no any product in your shopping cart.   |\n";
				std::cout << "+------------------------------------------------------+\n";
				system("pause");
			}
			break;

		case '3':	// Check my payment.
			while (true) {
				system("cls");
				std::cout << "\n+-------------------------------------------------------------+\n";
				std::cout << " If you want to return to Main Menu, type '0' or press ENTER.\n";
				std::cout << " Enter your payment number: ";
				std::getline(std::cin, paymentNumStr);
				if ((paymentNumStr[0] == '0' && paymentNumStr.size() == 1) || paymentNumStr.empty())	// If payment number is equal to 0 
																										// or is empty.
					break;
				if (isPosUInumber(paymentNumStr) && paymentNumStr < "999999999") {		// Number validation.	
					if (std::stoul(paymentNumStr) > payments.size()) {		// If payment number exceeds size of payments vector.
						std::cout << "\n There is no payment #" << paymentNumStr << ".";
						std::cout << "\n Check your payment number and try again.\n";
						std::cout << "+-------------------------------------------------------------+\n";
						system("pause");
					}
					else {
						paymentNum = std::stoul(paymentNumStr);		// Convert paymentNumStr to unsigned int paymentNum.
						paymentNum -= 1;	// To determine a position in the payments vector. 
											// Payment number is greater by 1 than the position in the vector.
						std::cout << "+-------------------------------------------------------------+\n";
						payments[paymentNum].dataOutput();	// Print out selected payment.
						system("pause");
						break;
					}
				}
				else {
					std::cout << "\n !!! - Your payment number input is wrong. Try again.\n";
					std::cout << "+-------------------------------------------------------------+\n";
					system("pause");
				}
			}
			break;

		case '4':	// Manage products.

			while (true) {	// Administrator Menu authorization and management.

				/// Password for authorization to Administrator Menu ///
				char password[8] = "admin";
				///><///

				char passwordCheck[8]{};
				bool escPsw = false;
				std::cout << "\n\nEnter a password: ";

				for (unsigned int i = 0; password[i] != '\0'; i++) {		// Password input.
					passwordCheck[i] = getch();
					if (passwordCheck[i] == 27) {	// If entered escape.
						escPsw = true;	// Escape from password input.
						break;
					}
					if (passwordCheck[i] == 8) {	// If entered backspace.
						if (i != 0)
							i -= 2;		// Return to input of previous element.
						else if (i == 0)
							i--;	// Stay on the first passwordCheck element.

						system("cls");		// Refresh console to remove the asterisk.
						mainMenuOutput();
						std::cout << "4";
						std::cout << "\n\nEnter a password: ";
						for (unsigned int j = 0; passwordCheck[j] != 8; j++)	// Print out new number of asterisk.
						{
							if (passwordCheck[j + 1] == 8)
								break;
							std::cout << "*";
						}
					}
					else
						std::cout << "*";
				}
				if (escPsw == true)		// If entered escape.
					break;		// Return to Main Menu.

				if (!strcmp(passwordCheck, password)) {		// If password entered correct.
					system("cls");
					std::cout << "\n+--------------------------------------------------+\n";
					std::cout << "          >> Administrator authorized! <<\n";
					std::cout << "+--------------------------------------------------+\n";
					system("pause");

					escAM = false;

					while (!escAM) {	// Administrator Menu management.
						system("cls");

						if (allProducts.size() > 0) {	// If any product exists.
							std::cout << "\n_______________________________Products________________________________\n";
							for (unsigned int i = 0; i < allProducts.size(); i++)	// Print out all products.
								allProducts[i].dataOutput(i + 1);
						}

						std::cout << "\n+----------------------------+\n";
						std::cout << "|     Administrator Menu     |\n";
						std::cout << "+---+------------------------+\n";
						std::cout << "| 1 | Add product            |\n";
						std::cout << "+---+------------------------+\n";
						std::cout << "| 2 | Edit product           |\n";
						std::cout << "+---+------------------------+\n";
						std::cout << "| 3 | Remove product         |\n";
						std::cout << "+---+------------------------+\n";
						std::cout << "| 4 | Get number of payments |\n";
						std::cout << "+---+------------------------+\n";

						std::cout << "\nPress ESC to exit the Administrator Menu.";
						std::cout << "\nEnter number of menu option: ";

						/// Declaration & initialization of variables and iterator for Administrator Menu options ///
						unsigned int prodNum{};
						std::string prodNumStr{};
						auto it = allProducts.begin();
						///><///

						char optionAM = getch();
						std::cout << optionAM << '\n';

						switch (optionAM) {		// Administrator Menu options.
						case '1':	// Add product.
							anyProduct.dataInput();		// Call add product function.
							allProducts.push_back(anyProduct);	// Push back anyProduct to allProducts vector.
							anyProduct.write_products(allProducts);		// Write file with new products.
							allProductsSave = allProducts;		// Refresh allProductsSave.

							std::cout << "\nProduct successfully added!\n";
							system("pause");
							break;

						case '2':	// Edit product.
							std::cout << "\nIf you don't want to edit anything, type '0'.\n";

							while (true) {
								std::cout << "Type the number of product you want to edit: ";
								std::cin >> prodNumStr;
								if (prodNumStr == "0")
									break;	// Escape from loop.
								if (isPosUInumber(prodNumStr) && prodNumStr < "999999999") {		// Number validation.
									prodNum = std::stoul(prodNumStr);	// Convert prodNumStr to unsigned int prodNum.
									if (prodNum <= allProducts.size())	// If the limit of elements is reached.
										break;
									else
										std::cout << "!!! - There is no product with such number. Try again.\n\n";
								}
								else
									std::cout << "!!! - Your product number input is wrong. Try again.\n\n";
							}
							if (prodNumStr == "0")
								break;	// Return to Administator Menu.

							prodNum -= 1;	// To determine a position in the allProducts vector. 
											// Product number is greater by 1 than the position in the vector.

							std::cin.clear();
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

							allProducts[prodNum].dataInput();	// Replace existing product data with new data input.
							anyProduct.write_products(allProducts);		// Write file with edited product.
							allProductsSave = allProducts;	  // Refresh allProductsSave.

							std::cout << "\nProduct successfully edited!\n";
							system("pause");
							break;

						case '3':	//  Remove product.
							std::cout << "\nIf you don't want to remove anything, type '0'.\n";

							while (true) {
								std::cout << "Type the number of product you want to remove: ";
								std::cin >> prodNumStr;
								if (prodNumStr == "0")
									break;	// Escape from loop.
								if (isPosUInumber(prodNumStr) && prodNumStr < "999999999") {		// Number validation.
									prodNum = std::stoul(prodNumStr);	// Convert prodNumStr to unsigned int prodNum.
									if (prodNum <= allProducts.size())	// If the limit of elements is reached.
										break;
									else
										std::cout << "!!! - There is no product with such number. Try again.\n\n";

								}
								else
									std::cout << "!!! - Your product number input is wrong. Try again.\n\n";
							}
							if (prodNumStr == "0")
								break;	// Return to Administator Menu.

							prodNum -= 1;	// To determine a position in the allProducts vector. 
											// Product number is greater by 1 than the position in the vector.

							it = allProducts.begin();	// Refresh iterator.
							for (unsigned int i = 0; i < prodNum; i++)	// Assign to iterator the prodNum position of vector element.
								it++;
							allProducts.erase(it);	// Remove vector element.

							anyProduct.write_products(allProducts);		// Write file with edited product.
							allProductsSave = allProducts;	  // Refresh allProductsSave.

							std::cin.clear();
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

							std::cout << "\nProduct successfully removed!\n";
							system("pause");
							break;

						case '4':	// Get number of payments.
							system("cls");
							std::cout << "\n+--------------------------------------------------+\n";
							std::cout << " > The database stores " << payments.size() << " payments.\n";
							std::cout << "+--------------------------------------------------+\n";
							system("pause");
							break;

						case 27:	// Escape option.
							escAM = true;

						default:
							break;
						}
						if (escAM == true)
							break;	// Return to Main Menu.
					}
					break;
				}
				else {
					system("cls");
					std::cout << "\n+---------------------------------------+\n";
					std::cout << "| ! - Password is incorrect. Try again. |\n";
					std::cout << "+---------------------------------------+\n";
					system("pause");

					system("cls");	// Refresh console.
					mainMenuOutput();
					std::cout << "4";
				}
			}
			break;

		case 27:	// Exit the programme.
			escMM = true;
			break;
		}
	}
	return 0;
}
