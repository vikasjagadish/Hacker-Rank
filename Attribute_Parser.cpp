#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <regex>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    cin.ignore();

    map<string, string> attributes;
    vector<string> tagStack;

   regex attrPattern(R"REGEX((\w+)\s*=\s*"([^"]*)")REGEX");

    for (int i = 0; i < n; i++) {
        string line;
        getline(cin, line);

        if (line[1] == '/') {
            tagStack.pop_back();
        } else {
            size_t end = line.find_first_of(" >");
            string tag = line.substr(1, end - 1);

            string path = tagStack.empty()
                        ? tag
                        : tagStack.back() + "." + tag;

            tagStack.push_back(path);

            auto begin = sregex_iterator(
                line.begin(), line.end(), attrPattern
            );
            auto finish = sregex_iterator();

            for (auto it = begin; it != finish; ++it) {
                string name = (*it)[1].str();
                string value = (*it)[2].str();

                attributes[path + "~" + name] = value;
            }
        }
    }

    for (int i = 0; i < q; i++) {
        string query;
        cin >> query;

        if (attributes.find(query) != attributes.end()) {
            cout << attributes[query] << '\n';
        } else {
            cout << "Not Found!" << '\n';
        }
    }

    return 0;
}
