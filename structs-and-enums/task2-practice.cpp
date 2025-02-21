#include <iostream>

constexpr unsigned STUDENT_NAME_MAX_LEN = 256;
constexpr unsigned INITIAL_GRADE_NUM = 4;

struct StudentBook {
    char* student_name;
    unsigned faculty_number;
    unsigned grades_num;
    unsigned grades_size;
    double* grades;
};

void init_student_book(StudentBook* sb, char* student_name, unsigned faculty_number) {
    sb->student_name = student_name;
    sb->faculty_number = faculty_number;
    sb->grades_num = 0;
    sb->grades_size = INITIAL_GRADE_NUM;
    sb->grades = new double[sb->grades_size];
}

void deinit_student_book(StudentBook* sb) {
    sb->student_name = nullptr;
    sb->grades = nullptr;
}

void add_grade(StudentBook* sb, double grade) {
    if (sb->grades_num == sb->grades_size) {
        unsigned new_size = sb->grades_size * 2;
        double* grades = new double[new_size];

        for (int i = 0; i < new_size; ++i) {
            grades[i] = sb->grades[i];
        }

        delete[] sb->grades;
        
        sb->grades = grades;
        sb->grades_size = new_size;
    }

    sb->grades[sb->grades_num++] = grade;
}

void sort_descending(StudentBook* sb) {
    for (int i = 0; i < sb->grades_num; ++i) {
        for (int j = 0; j < sb->grades_num - i - 1; ++j) {
            if (sb->grades[j] < sb->grades[j+1]) {
                double temp = sb->grades[j];
                sb->grades[j] = sb->grades[j+1];
                sb->grades[j+1] = temp;    
            }
        }
    }
}

double calculate_average(StudentBook* sb, bool exclude_failed) {
    unsigned count = 0;
    double sum = 0;

    for (int i = 0; i < sb->grades_num; ++i) {
        if (exclude_failed && sb->grades[i] < 3.0) {
            continue;
        }
        sum += sb->grades[i];
        count += 1;
    }

    return sum / count;
}

unsigned get_failed_subjects_count(StudentBook* sb) {
    unsigned failed_count = 0;

    for (int i = 0; i < sb->grades_num; ++i) {
        if (sb->grades[i] < 3.0) {
            failed_count += 1;
        }
    }

    return failed_count;
}

bool can_advance_to_next_year(StudentBook* sb) {
    unsigned failed_count = get_failed_subjects_count(sb);

    if (failed_count > 4) {
        return false;
    }

    if (failed_count == 4 && calculate_average(sb, true) >= 4.00) {
        return true;
    }
    
    return true;
}

bool qualifies_for_scholarship(StudentBook* sb) {
    return get_failed_subjects_count(sb) == 0 && calculate_average(sb, true) >= 5.00;
}

int main() {
    StudentBook sb {};
    char* name = new char[STUDENT_NAME_MAX_LEN];
    std::cin.getline(name, STUDENT_NAME_MAX_LEN, '\n');

    init_student_book(&sb, name, 10101010);

    add_grade(&sb, 5.5);
    add_grade(&sb, 6.0);
    add_grade(&sb, 4.2);
    add_grade(&sb, 2.9);

    sort_descending(&sb);

    std::cout << "Average grade: " << calculate_average(&sb, true) << std::endl;
    std::cout << "Can advance to next year: " << (can_advance_to_next_year(&sb) ? "Yes" : "No") << std::endl;
    std::cout << "Qualifies for scholarship: " << (qualifies_for_scholarship(&sb) ? "Yes" : "No") << std::endl;


    deinit_student_book(&sb);

    return 0;
}