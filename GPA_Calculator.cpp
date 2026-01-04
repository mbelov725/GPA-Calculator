#include <iostream>
#include <string>
#include <vector>



class Course;
class Course_list;
void line();
void menu();
void submenu();
int main();

class Course {
    public:
        Course( std::string code, std::string name, double weight, double percentage );
        double calculate_gpa( double percentage ) const;
        std::string get_code() const;
        std::string get_name() const;
        double get_weight() const;
        double get_percentage() const;
        double get_gpa() const;
        void set_code( std::string code );
        void set_name( std::string name );
        void set_weight( double weight );
        void set_percentage( double percentage );
    private:
        std::string code_;    
        std::string name_;
        double weight_;
        double percentage_;
        double gpa_;

    friend std::ostream &operator<<( std::ostream &out, Course const &course );
};

Course::Course( std::string code, std::string name, double weight, double percentage ):
code_{ code },
name_{ name },
weight_{ weight },
percentage_{ percentage },
gpa_{ calculate_gpa( percentage_ ) } {
}

double Course::calculate_gpa( double percentage ) const {
    if (percentage >= 90) return 4.0;
    else if (percentage >= 85) return 3.9;
    else if (percentage >= 80) return 3.7;
    else if (percentage >= 77) return 3.3;
    else if (percentage >= 73) return 3.0;
    else if (percentage >= 70) return 2.7;
    else if (percentage >= 67) return 2.3;
    else if (percentage >= 63) return 2.0;
    else if (percentage >= 60) return 1.7;
    else if (percentage >= 57) return 1.3;
    else if (percentage >= 53) return 1.0;
    else if (percentage >= 50) return 0.7;
    else return 0.0;
}

std::string Course::get_code() const {
    return code_;
}

std::string Course::get_name() const {
    return name_;
}

double Course::get_weight() const {
    return weight_;
}

double Course::get_percentage() const {
    return percentage_;
}

double Course::get_gpa() const {
    return gpa_;
}

void Course::set_code( std::string code ) {
    code_ = code;
}

void Course::set_name( std::string name ) {
    name_ = name;
}

void Course::set_weight( double weight ) {
    if ( weight == 0.25 || weight == 0.5 ) {
        weight_ = weight;
    } else {
        std::cout << "Invalid weight" << std::endl;
    }
}

void Course::set_percentage( double percentage ) {
    if ( 0 <= percentage && percentage <= 100 ) {
        percentage_ = percentage;
        gpa_ = calculate_gpa( percentage_ );
    } else {
        std::cout << "Invalid percentage" << std::endl;
    }
}

std::ostream &operator<<( std::ostream &out, Course const &course ) {
    out << "Course code: " << course.code_ << std::endl;
    out << "Course name: " << course.name_ << std::endl;
    out << "Course weight: " << course.weight_ << std::endl;
    out << "Course percentage: " << course.percentage_ << std::endl;

    return out;
}

class Course_list {
    public:
        void add_course();
        void display_courses() const;
        void edit_course();
        void delete_course();
        void calculate_cumulative_gpa() const;
    private:
        std::vector<Course> list_;
};

void Course_list::add_course() {
    std::string code{};
    std::string name{};
    double weight{};
    double percentage{};

    line();
    std::cout << "Enter course code: ";
    std::cin >> code;

    std::cout << "Enter course name: ";
    std::cin >> name;

    std::cout << "Enter weight: ";
    std::cin >> weight;

    while ( weight != 0.25 && weight != 0.5 ) {
        std::cout << "Weight must be 0.25 or 0.5" << std::endl;
        std::cout << "Enter valid weight: ";
        std::cin >> weight;
    }

    std::cout << "Enter percentage: ";
    std::cin >> percentage;

    while ( percentage < 0 || percentage > 100 ) {
        std::cout << "Percetnage must be between 0 and 100" << std::endl;
        std::cout << "Enter valid percentage: ";
        std::cin >> percentage;
    }

    Course course( code, name, weight, percentage );

    list_.push_back( course );
}

void Course_list::display_courses() const {
    line();

    if ( list_.size() == 0 ) {
        std::cout << "You have no courses to display" << std::endl;
        return;
    }

    std::cout << "1." << std::endl;
    std::cout << list_[0];

    for ( std::size_t k{1}; k < list_.size(); ++k ) {
        std::cout << std::endl;
        std::cout << k + 1 << "." << std::endl;
        std::cout << list_[k];
    }
}

void Course_list::edit_course() {
    if ( list_.size() == 0 ) {
        line();
        std::cout << "You have no courses to edit" << std::endl;
        return;
    }

    display_courses();
    std::cout << std::endl;

    std::size_t number{0};
    std::cout << "Enter the number of the course you would like to edit: ";
    std::cin >> number;

    if ( number <= 0 || list_.size() < number ) {
        std::cout << "Invalid number" << std::endl;
        return;
    }

    int option{0};

    do {
        submenu();
        std::cin >> option;
        std::cout << std::endl;

        switch( option ) {
            case 1: {
                std::string new_code;
                std::cout << "Enter the new code: ";
                std::cin >> new_code;
                list_[number - 1].set_code( new_code );
                break;
            }

            case 2: {
                std::string new_name;
                std::cout << "Enter the new name: ";
                std::cin >> new_name;
                list_[number - 1].set_name( new_name );
                break;
            }

            case 3: {
                double new_weight{0};
                std::cout << "Enter the new weight: ";
                std::cin >> new_weight;
                list_[number - 1].set_weight( new_weight );
                break;
            }

            case 4: {
                double new_percentage{0};
                std::cout << "Enter the new percentage: ";
                std::cin >> new_percentage;
                list_[number - 1].set_percentage( new_percentage );
                break;
            }

            case 5: {
                break;
            }

            default: {
                std::cout << "Invalid option" << std::endl;
                break;
            }
        }

        std::cout << std::endl;
        std::cout << list_[number - 1];
    } while ( option != 5 );
}

void Course_list::delete_course() {
    if ( list_.size() == 0 ) {
        line();
        std::cout << "You have no courses to delete" << std::endl;
        return;
    }

    display_courses();
    std::cout << std::endl;

    std::size_t number{0};
    std::cout << "Enter the number of the course you would like to delete: ";
    std::cin >> number;

    if ( 0 < number && number <= list_.size()) {
        list_.erase( list_.begin() + number - 1 );
    } else {
        std::cout << "Invalid number" << std::endl;
    }
}

void Course_list::calculate_cumulative_gpa() const {
    line();

    if ( list_.size() == 0 ) {
        std::cout << "You have no courses" << std::endl;
        return;
    }

    double sum{0};
    double credits{0};

    for ( std::size_t k{0}; k < list_.size(); ++k ) {
        Course course{ list_[k]};
        double gpa{ course.get_gpa() };
        double weight{ course.get_weight() };
    
        sum += gpa*weight;
        credits += weight;
    }

    std::cout << "Your cumulative GPA is " << sum/credits << "/4.0" << std::endl;
}

void line() {
    std::cout << "-----------------------------------" << std::endl;
}

void menu() {
    line();
    std::cout << "(1) Add a course" << std::endl;
    std::cout << "(2) Edit a course" << std::endl;
    std::cout << "(3) Delete a course" << std::endl;
    std::cout << "(4) Display courses" << std::endl;
    std::cout << "(5) Calculate cumulative GPA" << std::endl;
    std::cout << "(6) Exit" << std::endl;
    std::cout << "Enter option [1,6]: ";
}

void submenu() {
    std::cout << std::endl;
    std::cout << "(1) Edit course code" << std::endl;
    std::cout << "(2) Edit course name" << std::endl;
    std::cout << "(3) Edit course weight" << std::endl;
    std::cout << "(4) Edit course percentage" << std::endl;
    std::cout << "(5) Exit" << std::endl;
    std::cout << "Enter option [1,5]: ";
}

int main() {
    Course_list courses;
    int choice{0};

    do {
        menu();
        std::cin >> choice;

        switch ( choice ) {
            case 1: {
                courses.add_course();
                break;
            }

            case 2: {
                courses.edit_course();
                break;
            }

            case 3: {
                courses.delete_course();
                break;
            }

            case 4: {
                courses.display_courses();
                break;
            }

            case 5: {
                courses.calculate_cumulative_gpa();
                break;
            }

            case 6: {
                break;
            }

            default: {
                std::cout << "Invalid option" << std::endl;
            }
        }
    } while ( choice != 6 );

    return 0;
}