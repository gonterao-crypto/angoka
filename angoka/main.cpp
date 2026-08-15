#include <iostream>
#include <random>
#include <string>
#include <format>
#include <compare>
#include <vector>
#include <fstream>

std::string getzeroume(int x, int maxk) {
	std::string m = "";
	m = std::format("{:0{}}", x, maxk);
	return m;
}

enum class hold {
	ic,
	rf,
	wf,
	no
};

int main(int argc, char* argv[]) {
	if (argc < 1) return -1;

	int KEYMIN = 2;
	int KEYMAX = 999;
	int UCHARMAX = 255 * KEYMAX;
	int UCHARNOB = 1;
	bool HELP = false;
	bool RUN = false;
	bool ZEROARI = false;
	bool WFILE = true;
	bool HAS_ERROR = false;
	std::string WFILENAME = "out.an";
	bool RFILE = true;
	std::string RFILENAME = "in.an";

	while (UCHARMAX /= 10)
		++UCHARNOB;

	bool isango = true;
	unsigned char* bef = nullptr;
	hold h = hold::no;
	if (argc == 1) {
		std::cout << R"(If you need assistance, please type "-help".)" << std::endl;
		return 0;
	}
	for (int i = 1; i < argc; i++) {
		std::string_view m = std::string_view(argv[i]);
		switch (h) {
			case hold::ic: {
				bef = (unsigned char*)argv[i];
				h = hold::no;
				break;
			}
			case hold::rf: {
				RFILENAME = argv[i];
				h = hold::no;
				break;
			}
			case hold::wf:
			{
				WFILENAME = argv[i];
				h = hold::no;
				break;
			}
			default: {
				if (m == "-r") {
					RUN = true;
				} else if (m == "-h") {
					HELP = true;
				} else if (m == "-d") {
					isango = false;
				} else if (m == "-with-zero") {
					ZEROARI = true;
				} else if (m == "-ic") {
					h = hold::ic;
					RFILE = false;
				} else if (m == "-oc") {
					WFILE = false;
				} else if (m == "-of") {
					h = hold::wf;
					WFILE = true;
				} else if (m == "-if") {
					h = hold::rf;
					RFILE = true;
				} else if (m == "-ff") {
					std::string mrfilename = RFILENAME;
					RFILENAME = WFILENAME;
					WFILENAME = mrfilename;
				} else if (m == "-help") {
					HELP = true;
				} else if (m != "") {
					std::cout << "Invalid argument at " << m << std::endl;
					RUN = false;
					HAS_ERROR = true;
				}
				break;
			}
		}
	}

	if (HELP) {
		std::cout << "--HELP--" << std::endl;
		std::cout << "-help      | help                                      |" << std::endl;
		std::cout << "-h         | help                                      |" << std::endl;
		std::cout << "-r         | run                                       |" << std::endl;
		std::cout << "-with-zero | Include null characters during encryption |" << std::endl;
		std::cout << "-d         | decryption                                |" << std::endl;
		std::cout << "-ic        | input console                             | [input]" << std::endl;
		std::cout << "-oc        | output console                            |" << std::endl;
		std::cout << "-of        | output file                               | [file name]" << std::endl;
		std::cout << "-if        | input file                                | [file name]" << std::endl;
		std::cout << "-ff        | file name flip                            |" << std::endl;

		return 0;
	}









	if (RUN && !HAS_ERROR) {
		std::string rfl = "";
		if (RFILE) {
			std::ifstream file(RFILENAME);
			if (file) {
				std::getline(file, rfl);
				bef = (unsigned char*)rfl.c_str();
			} else {
				return -1;
			}
		}

		if (bef == nullptr) return -1;
		if (isango) {


			std::random_device rd;
			std::mt19937_64 mt64(rd());

			std::uniform_int_distribution<uint64_t> get_rand_uni_int(KEYMIN, KEYMAX);

			int key = get_rand_uni_int(mt64);

			std::string out = "";

			for (int i = 0; i <= std::strlen((const char*)bef); i++) {
				if (!ZEROARI && ((int)bef[i] == 0)) break;
				out += getzeroume((int)bef[i] * key, UCHARNOB);
			}
			out += getzeroume(key, UCHARNOB);

			if (WFILE) {
				std::ofstream outputfile(WFILENAME);
				outputfile << out;
				outputfile.close();
				std::cout << "OK" << std::endl;
			} else {
				std::cout << out << std::endl;
			}
		} else {
			std::vector<int> n;
			if (UCHARNOB > std::strlen((const char*)bef)) return -1;
			for (int i = 0; i < std::strlen((const char*)bef); i++) {
				if (i % UCHARNOB == 0) {
					std::string nb = "";
					for (int j = 0;j < UCHARNOB; j++) {
						nb += (char)bef[j + i];
					}

					n.push_back(stoi(nb));
				}
			}
			int key = n[n.size() - 1];

			std::string out = "";

			for (int i = 0; i < n.size() - 1; i++) {
				out += (char)(n[i] / key);
			}
			if (WFILE) {
				std::ofstream outputfile(WFILENAME);
				outputfile << out;
				outputfile.close();
				std::cout << "OK" << std::endl;
			} else {
				std::cout << out << std::endl;
			}
		}
	}
}