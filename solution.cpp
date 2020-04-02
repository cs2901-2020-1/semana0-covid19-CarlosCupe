#include <iostream>
#include <fstream>
#include <string>
#include <ctime> 

using namespace std;

int compare_string(string line_a, string line_b, int *num_char) {
    int similarity_index = 0;
    string min, max;


    if (line_a.length() > line_b.length()) {
        min = line_b;
        max = line_a;
    } else {
        min = line_a;
        max = line_b;
    }

    for (int i = 0; i < min.length(); i++) {
        if (line_a[i] == line_b[i] && line_a[i] != '\n') similarity_index++;
    }

    (*num_char) += max.length();

    return similarity_index;
}

int compare_files(ifstream *file_a, ifstream *file_b, int *num_char) {
    int similarity_index = 0;
    string line_a, line_b;

    while (!file_a->eof() && !file_b->eof()) {
        if (file_a->eof()) line_a = "";
        else getline(*file_a, line_a);
        
        if (file_b->eof()) line_b = "";
        else getline(*file_b, line_b);

        similarity_index += compare_string(line_a, line_b, num_char);
    }

    file_a->clear();
    file_a->seekg(0, ios::beg);
    file_b->clear();
    file_b->seekg(0, ios::beg);

    return similarity_index;
}

int main() {
    unsigned start, end;

    double **similarity_matrix = new double*[5];
    ifstream files[5];
    string header, files_name[] = { 
        "AY274119.txt",
        "AY278488.2.txt",
        "MN908947.txt",
        "MN988668.txt",
        "MN988669.txt"
    };

    for (int i = 0; i < 5; i++) {
        files[i].open(files_name[i]);
        similarity_matrix[i] = new double[5];
    }

    int total_char, similarity;
    start = clock();

    for (int i = 0; i < 5; i++) {
        for (int j = i + 1; j < 5; j++) {
            if (i == j) continue;
            getline(files[i], header);
            getline(files[j], header);
            total_char = 0;
            similarity = compare_files(&files[i], &files[j], &total_char);
            similarity_matrix[i][j] = similarity * 1.0 / total_char;
        }
        files[i].close();
    }
    
    end = clock();
    double time = (double(end - start) / CLOCKS_PER_SEC);
    
    cout << endl << "Comparison chart of COVID-19 variant" << endl << endl;
    cout << "\t\t";
    
    for (int i = 1; i < 5; i++) {
        cout << files_name[i] << '\t';
    }
    cout << endl;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < i + 1; j++) {
            if (j == 0)
                cout << files_name[i] << '\t';
            else cout << "\t-\t";
        }
        for (int j = i + 1; j < 5; j++) {
            printf("%.2f%%\t\t", similarity_matrix[i][j]*100);
        }
        cout << endl;
    }
    cout << endl << "Execution Time: " << time << "ms" << endl;
	return 0;
}
