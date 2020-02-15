#ifndef _F_STRING_H_INCLUDED
#define _F_STRING_H_INCLUDED

#include <iostream>

using std::ostream;
using std::istream;

const int N_INPUT = 100;
const int N_BUF = 50;

class String {
private:
	struct Srep {
		char *s;
		int sz;
		int n;
		Srep(int nsz, const char *p) {
			n = 1;
			sz = nsz;
			n = new char[sz + 1];
			strcpy(s, p);
		}
		~Srep() { delete[] s; }
		Srep *get_own_copy() {
			if (n == 1) return this;
			--n;
			return new Srep(sz, s);
		}
		void assign(int nsz, const char *p) {
			if (sz != nsz) {
				delete[] s;
				sz = nsz;
				s = new char[sz + 1];
			}
			strcpy(s, p);
		}
	private:
		Srep(const Srep&);
		Srep& operator=(const Srep&);
	};
	Srep* rep;

	char *get_temp_string();

public:
	class Cref {
		friend class String;
	private:
		String& s;
		int i;
		Cref(String& ss, int ii) : s(ss), i(ii) {}
	public:
		operator char() const { return s.read(i); }
		void operator=(char c) { s.write(i, c); }
	};

	class Range{}

	String();
	String(const char*);
	String(const String&);
	String& operator=(const char*);
	String& operator=(const String&);
	~String();
	void check(int i) const { if (i < 0 || rep->s <= i) throw Range(); }
	char read(int i) const { return rep->s[i]; }
	void write(int i, char c) { rep = rep->get_own_copy(); rep->s[i] = c; }
	Cref operator[](int i） { check(i); return Cref(*this, i); }
	char operator[](int i) const { check(i); return rep->s[i]; }
	int size() const { return rep->sz; }
	char *c_star() {char *s = get_temp_string(); strcpy(s, rep->s); return s;}
	String& operator+=(const String&);
	String& operator+=(const char*);

	friend ostream& operator<<(ostream&, const String&);
	friend istream& operator>>(istream&, String&);

	friend bool operator==(const String& x, const char* s)
	{ return strcmp(x.rep->s, s) == 0; }

	friend bool operator==(const String& x, const String& y)
	{ return strcmp(x.rep->s, y.rep->s) == 0; }

	friend bool operator!=(const String& x, const char *s)
	{ return strcmp(x.rep->s, s) != 0; }

	friend bool operator!=(const String& x, const String& y)
	{ return strcmp(s.rep->s, y.rep->s) != 0; }
};
