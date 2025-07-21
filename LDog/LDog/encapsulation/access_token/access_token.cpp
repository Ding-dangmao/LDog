#include"access_token.h"

std::string AccessToken::keyGeneratorRT(unsigned short length)
{
	/*auto now = Clock::systemClock();*/
	IntRandomGen int_random_gen(-100, 100);
	std::string access_token;
	/*前半段代表类型(数字或者字母),后半段代表值,共length段*/
	for (unsigned short i = 1; i <= length; i++) {
		unsigned a = std::abs(int_random_gen());
		unsigned b = std::abs(int_random_gen());
		if (a % 2) {
			const char& tb = ((b % 54) > 26) ? char(b % 54 - 27 + 65) : char(b % 54 + 97);
			access_token += tb;
		}
		else {
			const char& tb = b % 10 + 48;
			access_token += tb;
		}
	}
	return access_token;
}
