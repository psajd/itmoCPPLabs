#include "../include/json/json.hpp"
#include "../include/map/MyMap.h"
#include "../include/bprinter/table_printer.h"
#include <iostream>
#include "curl/curl.h"
#include "cstdio"
#include <chrono>
#include <thread>
#include <sys/select.h>


const static char *URL = "https://www.cbr-xml-daily.ru/daily_json.js";
static const char USAGE_MESSAGE[] = "\t\t========== Currency helper =========== \n\n"
                                    "\tInput strings with CharCodes of currency.\n"
                                    "\t/all for input all currency\n"
                                    "\tTo stop input - /q\n"
                                    "\tThe average and median values will be printed after the program is finished\n"
                                    "\tTo complete program write any sequence\n\n";

int kbhit() {
    struct timeval tv;
    fd_set read_fd;

    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&read_fd);
    FD_SET(0, &read_fd);

    if (select(1, &read_fd, NULL, NULL, &tv) == -1)
        return 0;

    if (FD_ISSET(0, &read_fd))
        return 1;

    return 0;
}

namespace curr {
    struct Currency {
    private:
        std::vector<double> values;
        double sum = 0;

    public:
        std::string id_;
        std::string num_code;
        std::string name_;
        std::string char_code_;
        int nominal_;
        double value_;
        double previous_;

        void sum_append(double x) {
            values.push_back(x);
            sum += x;
        }

        double get_median() {
            auto m = values.begin() + values.size() / 2;
            std::nth_element(values.begin(), m, values.end());
            return values[values.size() / 2];
        }

        double get_average() {
            return sum / (double) values.size();
        }
    };

    void to_json(nlohmann::json &j, const Currency &v) {
        j = nlohmann::json{{"ID",       v.id_},
                           {"NumCode",  v.num_code},
                           {"CharCode", v.char_code_},
                           {"Nominal",  v.nominal_},
                           {"Name",     v.name_},
                           {"Value",    v.value_},
                           {"Previous", v.previous_}
        };
    }

    void from_json(const nlohmann::json &j, Currency &v) {
        j.at("ID").get_to(v.id_);
        j.at("NumCode").get_to(v.num_code);
        j.at("CharCode").get_to(v.char_code_);
        j.at("Nominal").get_to(v.nominal_);
        j.at("Name").get_to(v.name_);
        j.at("Value").get_to(v.value_);
        j.at("Previous").get_to(v.previous_);
    }

}


struct json_str {
    char *response;
    size_t size;
};

static size_t write_callback(void *data, size_t size, size_t nmemb, void *userp) {
    size_t real_size = size * nmemb;
    auto *str = (struct json_str *) userp;
    char *ptr = (char *) realloc(str->response, str->size + real_size + 1);

    str->response = ptr;
    memcpy(&(str->response[str->size]), data, real_size);
    str->size += real_size;
    str->response[str->size] = 0;

    return real_size;
}

std::string get_json() {
    CURL *curl_handle = curl_easy_init();
    json_str jsonStr = {nullptr};
    if (curl_handle) {
        curl_easy_setopt(curl_handle, CURLOPT_URL, URL);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *) &jsonStr);
        CURLcode res = curl_easy_perform(curl_handle);
        if (res) {
            throw std::runtime_error("can't get json");
        } else {
            curl_easy_cleanup(curl_handle);
        }
    }
    return std::string{jsonStr.response};
}


void sleep(size_t n) {
    std::chrono::seconds sec(n);
    std::this_thread::sleep_for(sec);
}

void print_errors(const std::vector<std::string> &errs) {
    if (!errs.empty()) {
        std::cout << "Can't find this codes:" << std::endl;
        for (auto code: errs) {
            std::cout << code << std::endl;
        }
        std::cout << std::endl;
    }
}

std::vector<curr::Currency> get_currency_vector(nlohmann::json currency_json) {
    std::vector<curr::Currency> curr;
    for (auto currency: currency_json) {
        std::string char_code = currency["CharCode"];
        curr::Currency v1 = currency_json[char_code].get<curr::Currency>();
        curr.push_back(v1);
    }
    return curr;
}


MyMap<curr::Currency> currency_init(std::vector<std::string> &currency_names) {

    nlohmann::json full_json = nlohmann::json::parse(get_json());
    nlohmann::json currency_json = full_json["Valute"];

    MyMap<curr::Currency> map;
    std::vector<std::string> errs;
    std::vector<std::string> curr_name_new;
    std::vector<curr::Currency> curr = get_currency_vector(currency_json);
    if (currency_names.empty()) {
        for (auto &v: curr) {
            v.sum_append(v.value_);
            map.put(v.char_code_, v);
            curr_name_new.push_back(v.char_code_);
        }
    } else {
        for (const auto &name: currency_names) {
            bool isExist = false;
            for (auto &v: curr) {
                if (name == v.char_code_) {
                    v.sum_append(v.value_);
                    map.put(v.char_code_, v);
                    isExist = true;
                    curr_name_new.push_back(name);
                    break;
                }
            }
            if (!isExist) {
                errs.push_back(name);
            }
        }
    }
    print_errors(errs);
    currency_names = curr_name_new;
    return map;
}

void currency_update(std::vector<std::string> &currency_names, MyMap<curr::Currency> &currency) {

    nlohmann::json full_json = nlohmann::json::parse(get_json());
    nlohmann::json currency_json = full_json["Valute"];
    std::vector<curr::Currency> curr = get_currency_vector(currency_json);

    for (auto &name: currency_names) {
        for (auto &v: curr) {
            if (v.name_ == name) {

                currency[name].sum_append(v.value_);
            }
        }
    }
}

void print_currencies(MyMap<curr::Currency> &v, std::vector<std::string> currency_names) {
    bprinter::TablePrinter tp(&std::cout);
    tp.AddColumn("Char code", 10);
    tp.AddColumn("Num code", 10);
    tp.AddColumn("value", 10);
    tp.PrintHeader();
    for (const auto &name: currency_names) {
        tp << v[name].char_code_ << v[name].num_code << v[name].value_;
    }
    tp.PrintFooter();
    std::cout << std::endl;
}

std::vector<std::string> get_currency_names() {
    std::cout << USAGE_MESSAGE;
    std::vector<std::string> res;
    std::string current_str;
    while (true) {
        std::cin >> current_str;
        if ("/q" == current_str) {
            break;
        }
        if ("/all" == current_str) {
            return std::vector<std::string>{};
        }
        res.push_back(std::string(current_str));
        current_str.clear();
    }
    return res;
}

void print_results(MyMap<curr::Currency> curr, std::vector<std::string> currency_names) {
    std::cout << "\n\t=== Results === \n";

    bprinter::TablePrinter tp(&std::cout);
    tp.AddColumn("Char code", 10);
    tp.AddColumn("Median", 10);
    tp.AddColumn("Average", 10);
    tp.PrintHeader();

    for (const auto &name: currency_names) {
        tp << curr[name].char_code_ << curr[name].get_median() << curr[name].get_average();
    }
    tp.PrintFooter();
}

int main() {

    int requestCounter = 0;
    std::vector<std::string> currency_names = get_currency_names();
    MyMap<curr::Currency> a = currency_init(currency_names);


    if (currency_names.empty()) {
        std::cout << "No matching names";
    } else {
        while (!kbhit()) {
            requestCounter++;
            std::cout << "Request number: " << requestCounter << std::endl;
            currency_update(currency_names, a);
            print_currencies(a, currency_names);
            sleep(10);
        }
        print_results(a, currency_names);
    }

    return 0;
}
