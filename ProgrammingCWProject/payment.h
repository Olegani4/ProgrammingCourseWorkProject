
class Payment {
public:
	void dataInput(std::vector <Product> clProducts, CardDetails clientCard);
	void dataOutput();
	void write_payments(std::vector <Payment> payments);
	std::vector<Payment> read_payments(std::vector <Payment> payments);

	unsigned int pmtNumberRet() { return pmtNumber; }

private:
	unsigned int prodNumber{};
	unsigned int pmtNumber{};
	char clFirstName[256]{};
	char clLastName[256]{};
	char card_4LastDig[8]{};
	std::vector<std::string> productNames{};
	double totalDiscount{};
	double totalPay{};
	char paymDate[12]{};
	char paymTime[9]{};
};
