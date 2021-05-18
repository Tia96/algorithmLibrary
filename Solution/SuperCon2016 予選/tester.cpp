#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <sstream>
#include <random>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstdio>
#include <fstream>
#include <signal.h>

const std::string base =
" 6 18 25 13 35 14 11 20 33 19 7 21 36 2 32 22 10 9 30 34 12 3 17 15 1 29 4 23 26 28 27 8 5 31 16 24 \n"
" 30 6 27 10 18 20 32 4 5 26 16 28 1 24 35 13 17 21 3 33 25 14 34 2 23 15 11 12 19 31 22 29 8 36 7 9 \n"
" 28 1 33 18 20 11 9 36 22 4 23 17 30 16 2 32 24 7 13 25 19 8 31 15 26 21 6 14 10 34 5 12 29 35 3 27 \n"
" 5 34 30 33 6 3 11 16 19 1 29 35 36 18 25 8 15 9 7 10 31 23 13 27 24 12 4 32 22 17 28 21 2 14 26 20 \n"
" 19 13 34 6 32 7 31 8 28 29 5 10 15 27 14 36 1 18 3 17 24 11 35 21 20 16 2 25 26 22 23 30 9 4 12 33 \n"
" 20 6 32 21 7 25 1 34 28 13 30 5 26 19 22 18 14 12 36 2 11 16 17 29 24 23 15 8 10 31 4 27 3 35 33 9 \n"
" 2 11 30 25 23 20 19 35 31 7 6 13 29 18 8 12 17 27 4 3 15 36 21 32 33 34 1 22 16 5 24 10 26 9 28 14 \n"
" 35 6 25 16 24 5 7 1 15 28 31 29 27 36 12 14 3 19 9 26 18 8 17 33 10 20 11 32 34 4 23 22 30 13 2 21 \n"
" 19 7 36 12 34 3 2 23 26 14 21 25 16 18 30 17 24 6 15 22 10 9 20 35 32 33 4 28 1 13 27 8 5 31 11 29 \n"
" 31 19 13 11 27 10 9 1 35 21 20 25 15 17 23 29 5 22 7 24 4 14 26 36 33 32 8 2 30 6 16 18 28 34 3 12 \n";


long long calc_cnt, calc_time;
void signalHandler(int) {
	std::cout << "Samples: " << calc_cnt << std::endl;
	std::cout << "Average Time: "<< (double)calc_time / calc_cnt << "µs" << std::endl;

	exit(0);
}

bool check(const std::array<int, 36>& arr) {
    long long used = 0;
    
	int sx[6], sy[6], sz[2];

	for(int i = 0; i < 6; ++i)
		sx[i] = sy[i] = 0;

	sz[0] = sz[1] = 0;

	for(int i = 0; i < 6; ++i) {
		for(int j = 0; j < 6; ++j) {
            if(used & (1ll << arr[j * 6 + i])) {
                return false;
            }else {
                used |= 1ll << arr[j * 6 + i];
            }
			sx[i] += arr[i * 6 + j];
			sy[i] += arr[j * 6 + i];
		}
		sz[0] += arr[i * 6 + i];
		sz[1] += arr[i * 6 + 5 - i];
	}

	for(int i = 0; i < 6; ++i) {
		if(sx[i] != 111 || sy[i] != 111)
			return false;
	}

    if(sz[0] != 111 || sz[1] != 111) {
        return false;
    }

	return true;
}

#define Write 1
#define Read 0

std::string exec2(const std::string& cmd, const std::string& in) {
	int pin[2], pout[2], perr[2];

	pipe(pin), pipe(pout), pipe(perr);

	pid_t pid = fork();

	if(pid < 0)
		return "";

	if(pid == 0) {
		close(pin[Write]), close(pout[Read]), close(perr[Read]);

		dup2(pin[Read], STDIN_FILENO);
		dup2(pout[Write], STDOUT_FILENO);
		dup2(perr[Write], STDERR_FILENO);

		execlp(cmd.c_str(), cmd.c_str(), NULL);

		_exit(1);
	}else {
		close(pin[Read]), close(pout[Write]), close(perr[Write]);

		write(pin[Write], in.c_str(), in.size());

		close(pin[Write]);

		int status;

		char buf[1024];
		int len;
		std::string res;
		while((len = read(pout[Read], buf, 1024)) > 0) {
			res += std::string(buf, static_cast<std::string::size_type>(len));
		}

		waitpid(pid, &status, 0);

		close(pout[Read]);
		close(perr[Read]);

		return res;
	}
}

int main(int argc, char* argv[]) {
	signal(SIGINT, signalHandler);

	if(argc < 3)
		return 1;

	std::vector<std::array<int, 36>> vec;

	std::stringstream ss(base);
	std::string str;
	while(std::getline(ss, str)) {
		std::stringstream line(str);

		std::array<int, 36> vals;
		for(int i = 0; i < 36; ++i) {
			int v;
			if(!(line >> v)) {
				std::cout << "error: " << str << std::endl;

				return 1;
			}

			vals[i] = v;
		}

		vec.emplace_back(vals);
	}

	if(vec.size() == 0){
		return 1;
	}

	std::mt19937 mt{std::random_device{}()};
//	std::uniform_int_distribution<int> num(0, 35);
//	std::uniform_int_distribution<int> set(0, vec.size() - 1);

	std::ofstream ofs(argv[2], std::ios::app);

	if(!ofs) {
		std::cout << "Unable to open " << argv[2] << std::endl;

		return 1;
	}

	while(true) {
		auto v = vec[mt() % vec.size()];

		int cnt = 0;
		while(cnt != 15) {
			auto i = mt() % 36;

			if (v[i]) {
				v[i] = 0;

				++cnt;
			}
		}

		std::string in;

		for(int i = 0; i < v.size(); ++i) {
			std::stringstream ss;
			ss << v[i];

			in += ss.str() + " ";
		}

		auto res = exec2(argv[1], in);

		if(res.size() == 0) {
			std::cout << "IE " << in << std::endl;
		}else {
			std::stringstream ss(res);

			std::array<int, 36> vals;
			for(int i = 0; i < 36; ++i) {
				int v;
				if(!(ss >> v)) {
					std::cout << "error: Failed to parse " << res << std::endl;

					break;
			    }

			 	vals[i] = v;
			}
			int time;
			if(!(ss >> time)) {
				std::cout << "error: Unable to get the time " << res << std::endl;
		    }


			if(check(vals)) {
				std::cout << "AC, " << time / 1000 << "ms, " << in << std::endl;

				if(time / 1000 > 50) {
					ofs << "AC, " << time / 1000 << "ms, " << in << std::endl;
				}

				++calc_cnt, calc_time += time;
			}else {
				std::cout << "WA, " << time / 1000 << "ms, " << in << std::endl;

				ofs << "WA, " << time / 1000 << "ms, " << in << std::endl;
			}
		}
	}

}
