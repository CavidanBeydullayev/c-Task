#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <iomanip>
#include <fstream>
#include <sstream>

using namespace std;

struct User {
    string username;
    string password;
    string name;
    string surname;
    string fathername;
    string phone;
    string email;
};

struct Admin {
    string username;
    string password;
};

struct Question {
    string category;
    string text;
    string correctAnswer;
    vector<string> options;
};

unordered_map<string, User> userDatabase;
vector<Question> questionDatabase;

string encryptPassword(const string& password) {
    string encrypted = "";
    for (char c : password) {
        encrypted += c + 3;
    }
    return encrypted;
}

void registerUser() {
    User newUser;
    cout << "Ad daxil edin: ";
    cin >> newUser.name;
    cout << "Soyad daxil edin: ";
    cin >> newUser.surname;
    cout << "Telefon nömrəsi daxil edin: ";
    cin >> newUser.fathername;
    cout << "Ata adı daxil edin: ";
    cin >> newUser.phone;
    cout << "E-poçt daxil edin: ";
    cin >> newUser.email;
    cout << "İstifadəçi adı daxil edin: ";
    cin >> newUser.username;

    if (userDatabase.find(newUser.username) != userDatabase.end()) {
        cout << "Bu istifadəçi adı artıq mövcuddur.\n";
        return;
    }

    string password;
    cout << "Şifrə daxil edin: ";
    cin >> password;
    newUser.password = encryptPassword(password);

    userDatabase[newUser.username] = newUser;
    cout << "Qeydiyyat uğurla tamamlandı!\n";
}

User* loginUser() {
    string username, password;
    cout << "İstifadəçi adı: ";
    cin >> username;
    cout << "Şifrə: ";
    cin >> password;

    if (userDatabase.find(username) != userDatabase.end()) {
        User& user = userDatabase[username];
        if (user.password == encryptPassword(password)) {
            cout << "Giriş uğurludur. Xoş gəldiniz, " << user.name << "!\n";
            return &user;
        }
    }

    cout << "Yanlış istifadəçi adı və ya şifrə.\n";
    return nullptr;
}

void addQuestion() {
    Question newQuestion;
    cout << "Kateqoriya daxil edin: ";
    cin >> newQuestion.category;
    cin.ignore();
    cout << "Sual mətni daxil edin: ";
    getline(cin, newQuestion.text);

    cout << "Doğru cavabı daxil edin: ";
    cin >> newQuestion.correctAnswer;

    cout << "Cavab variantlarını daxil edin (4 variant):\n";
    for (int i = 0; i < 4; ++i) {
        string option;
        cout << "Variant " << i + 1 << ": ";
        cin >> option;
        newQuestion.options.push_back(option);
    }

    questionDatabase.push_back(newQuestion);
    cout << "Sual uğurla əlavə edildi.\n";
}

void addPhysicsQuestions() {
    Question q1;
    q1.category = "Hərəkət";
    q1.text = "Bir cismin sürəti 10 m/s-dir və hərəkət istiqamətindəki qüvvə 20 N-dir. Cismin kütləsi nə qədərdir?";
    q1.correctAnswer = "2 kg";
    q1.options = { "1 kg", "2 kg", "5 kg", "10 kg" };
    questionDatabase.push_back(q1);

    Question q2;
    q2.category = "Elektrik";
    q2.text = "2 ohm-luq müqavimətə sahib bir dövrədə 10 volt gərginlik tətbiq olunduqda, dövrədən keçən cərəyanın miqdarı nə qədər olacaq?";
    q2.correctAnswer = "5 A";
    q2.options = { "1 A", "5 A", "10 A", "15 A" };
    questionDatabase.push_back(q2);


    Question q3;
    q3.category = "Termodinamika";
    q3.text = "Qazın başlanğıc həcmi 4 m³, təzyiqi isə 2 atm-dır. Əgər təzyiq 4 atm-ə qalxarsa, həcmi necə dəyişir (Boyle qanununa əsasən)?";
    q3.correctAnswer = "2 m³";
    q3.options = { "1 m³", "2 m³", "4 m³", "8 m³" };
    questionDatabase.push_back(q3);


    Question q4;
    q4.category = "Optika";
    q4.text = "Bir işıq şüası vakuumda 300,000 km/s sürətində hərəkət edir. Şüa həmin sürətlə hansı maddə vasitəsilə keçir?";
    q4.correctAnswer = "Hava";
    q4.options = { "Hava", "Su", "Şüşə", "Metal" };
    questionDatabase.push_back(q4);


    Question q5;
    q5.category = "Elektromaqnetizm";
    q5.text = "Bir naqil boyunca cərəyan axır. Bu naqil ətrafında yaranan maqnit sahəsinin istiqaməti necə müəyyən edilir?";
    q5.correctAnswer = "Sol əl qaydası ilə";
    q5.options = { "Sağ əl qaydası ilə", "Sol əl qaydası ilə", "Sirkulyar hərəkətlə", "Rəyliyə doğru" };
    questionDatabase.push_back(q5);

    cout << "Fizika sualları uğurla əlavə olundu.\n";
}

void takeTest(User* user) {
    if (questionDatabase.empty()) {
        cout << "Hazırda mövcud suallar yoxdur.\n";
        return;
    }

    int correctAnswers = 0;
    for (const auto& question : questionDatabase) {
        cout << "Kateqoriya: " << question.category << "\n";
        cout << "Sual: " << question.text << "\n";
        for (size_t i = 0; i < question.options.size(); ++i) {
            cout << i + 1 << ". " << question.options[i] << "\n";
        }
        int answer;
        cout << "Cavabınızı seçin (1-4): ";
        cin >> answer;

        if (answer >= 1 && answer <= 4 && question.options[answer - 1] == question.correctAnswer) {
            ++correctAnswers;
        }
        else {
            cout << "Yanlış cavab!\n";
        }
    }

    cout << "Test nəticəsi: " << correctAnswers << "/" << questionDatabase.size() << "\n";
}

void adminPanel(Admin admin) {
    string username, password;
    cout << "Admin istifadəçi adı: ";
    cin >> username;
    cout << "Admin şifrə: ";
    cin >> password;

    if (username == admin.username && encryptPassword(password) == admin.password) {
        cout << "Admin panelinə daxil oldunuz.\n";
        while (true) {
            cout << "\n1. Sual əlavə et\n";
            cout << "2. Fizika suallarını əlavə et\n";
            cout << "3. İstifadəçiləri göstər\n";
            cout << "4. Çıxış\n";
            int choice;
            cout << "Seçiminizi edin: ";
            cin >> choice;
            if (choice == 1) {
                addQuestion();
            }
            else if (choice == 2) {
                addPhysicsQuestions();
            }
            else if (choice == 3) {
                for (const auto& pair : userDatabase) {
                    cout << "İstifadəçi: " << pair.second.username << "\n";
                }
            }
            else if (choice == 4) {
                break;
            }
            else {
                cout << "Yanlış seçim. Yenidən cəhd edin.\n";
            }
        }
    }
    else {
        cout << "Yanlış admin adı və ya şifrə.\n";
    }
}

int main() {
    Admin admin = { "admin", encryptPassword("admin123") };
    while (true) {
        cout << "\n1. Username sing up\n";
        cout << "2. Username login\n";
        cout << "3. Admin tab\n";
        cout << "4. Exit\n";
        int choice;
        cout << "Enter the choice: ";
        cin >> choice;

        if (choice == 1) {
            registerUser();
        }
        else if (choice == 2) {
            User* user = loginUser();
            if (user) {
                takeTest(user);
            }
        }
        else if (choice == 3) {
            adminPanel(admin);
        }
        else if (choice == 4) {
            cout << "Exit\n";
            break;
        }
        else {
            cout << "Wrong choice try again\n";
        }
    }

}
