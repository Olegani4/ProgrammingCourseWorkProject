#pragma warning(disable : 4996)


class Product {
public:
	friend bool productSort(const Product& prod1, const Product& prod2);
	friend bool manufacturerSort(const Product& prod1, const Product& prod2);
	friend bool lowestPriceSort(const Product& prod1, const Product& prod2);
	friend bool highestPriceSort(const Product& prod1, const Product& prod2);
	friend bool lowestStrgSizeSort(const Product& prod1, const Product& prod2);
	friend bool highestStrgSizeSort(const Product& prod1, const Product& prod2);
	friend bool colourSort(const Product& prod1, const Product& prod2);

	void dataInput();
	void dataOutput(unsigned int num);
	void write_products(std::vector<Product> allProducts);
	std::vector<Product> read_products(std::vector<Product> allProducts);

	char* prodNameRet() { return prodName; }
	char* manufacturerRet() { return manufacturer; }
	double priceRet() { return price; }
	double discountPriceRet() { return discountPrice; }
	unsigned int storageSizeRet() { return storageSize; }
	char* colourRet() { return colour; }

private:
	char prodName[256]{};
	char manufacturer[256]{};
	double price{};
	double discountPrice{};
	unsigned int storageSize{};
	char colour[128]{};
	char measures[64]{};
};
