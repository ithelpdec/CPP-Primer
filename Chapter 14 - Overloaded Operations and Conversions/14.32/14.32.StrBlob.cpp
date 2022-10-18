
#include "StrBlob.hpp"
#include "StrBlobPtr.hpp"
#include "ConstStrBlobPtr.hpp"

StrBlob::StrBlob() : data(std::make_shared<std::vector<std::string>>()) { }
StrBlob::StrBlob(std::initializer_list<std::string> &&il) : data(std::make_shared<std::vector<std::string>>(il)) { }
StrBlob::StrBlob (const StrBlob &o) { data = std::make_shared<std::vector<std::string>>(*o.data); }

StrBlob& StrBlob::operator=(const StrBlob &rhs)
{
    data = std::make_shared<std::vector<std::string>>(*rhs.data);
    std::cout << "StrBlob() assign -> data.use_count() = " << data.use_count() << std::endl;
    return *this;
}

std::string& StrBlob::operator[](std::size_t &n) { return (*data)[n]; }
const std::string& StrBlob::operator[](std::size_t &n) const { return (*data)[n]; }

void StrBlob::push_back(const std::string &t) { data->push_back(t); }
void StrBlob::push_back(std::string &&t) { data->push_back(std::move(t)); }
void StrBlob::pop_back() { data->pop_back(); }

std::string& StrBlob::front() { check(0, "front on empty StrBlob"); return data->front(); }
std::string& StrBlob::back() { check(0, "back on empty StrBlob"); return data->back(); }
const std::string& StrBlob::front() const { check(0, "front on empty StrBlob"); return data->front(); }
const std::string& StrBlob::back() const { check(0, "back on empty StrBlob"); return data->back(); }

StrBlobPtr StrBlob::begin() { return StrBlobPtr(*this); }
StrBlobPtr StrBlob::end() { return StrBlobPtr(*this, data->size()); }
ConstStrBlobPtr StrBlob::cbegin() const { return ConstStrBlobPtr(*this); }
ConstStrBlobPtr StrBlob::cend() const { return ConstStrBlobPtr(*this, data->size()); }

void StrBlob::check(size_type i, const std::string &msg) const
{ if (i >= data->size()) throw std::out_of_range(msg); }

bool operator==(const StrBlob &lhs, const StrBlob &rhs) { return lhs.size() == rhs.size(); }
bool operator!=(const StrBlob &lhs, const StrBlob &rhs) { return lhs != rhs; }

bool operator<(const StrBlob &lhs, const StrBlob &rhs) { return *lhs.data < *rhs.data; }
bool operator>(const StrBlob &lhs, const StrBlob &rhs) { return rhs < lhs; }
bool operator<=(const StrBlob &lhs, const StrBlob &rhs) { return !(lhs > rhs); }
bool operator>=(const StrBlob &lhs, const StrBlob &rhs) { return !(lhs < rhs); }

std::ostream& operator<<(std::ostream &os, const StrBlob &sb)
{ os << sb.data << " "; return os; }

void readStrBlob(std::ifstream &file, StrBlob &sb)
{
    std::string line;
    while (std::getline(file, line))
        sb.push_back(line);
}

int main()
{
    StrBlob sb = { "man", "bear", "pig" };
    StrBlobPtr sbp(sb);
    StrBlobPtrPtr sbpp(&sbp);
    
    // use of operator->() function for sbpp
    std::cout << "Printing first element of vector...\n";
    std::cout << sb.front() << " (using sb)" << std::endl;
    std::cout << *sbp << " (using sbp)" << std::endl;
    std::cout << sbpp.operator->()->deref() << " (using sbpp)" << std::endl;
    // the following code, encapsulated using built-in dereference also works
    // std::cout << **(sbpp.operator->()) << " (using sbpp)" << std::endl;
    
    // another use of operator->() function for sbpp
    std::cout << "\nUsing the same approach to provide first element's size...\n";
    std::cout << sb.size() << " (using sb)" << std::endl;
    std::cout << sbp->size() << " (using sbp)" << std::endl;
    std::cout << sbpp.operator->()->deref().size() << " (using sbpp)" <<std::endl;
    // again, further encapsulated
    // std::cout << (**(sbpp.operator->())).size() << " (using sbpp)" << std::endl;
    
    return 0;
}
