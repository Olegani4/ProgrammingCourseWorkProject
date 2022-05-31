
class CardDetails {
public:
	void dataInput(unsigned int clientNumInp);
	void dataOutput();

	char* firstNameRet() { return firstName; }
	char* lastNameRet() { return lastName; }
	unsigned int clientNumberRet() { return clientNumber; }
	char* cardNumberRet() { return cardNumber; }

private:
	unsigned int clientNumber{};
	char cardNumber[32]{};
	char firstName[256]{};
	char lastName[256]{};
	char expirationDate[6]{};
	char cvc_cvv2[4]{};
};
