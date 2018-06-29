// Oliver Kullmann, 28.6.2018 (Swansea)
/* Copyright 2018 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Satisfiability/Quantification/DQCNF/AutarkiesL1.cpp
  \brief A simple translation of the level-1 autarky problem for DQCNFs
  to SAT, using the direct encoding.

  COMPILE with

> g++ --std=c++11 -Wall -Ofast -DNDEBUG -o autL1 AutarkiesL1.cpp

  Alternatively the makefile (called "makefile") in this
  directory can be used:

> make all

  USAGE:

> autL1 [input] [output] [log]

*/

#include <limits>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <type_traits>
#include <exception>
#include <algorithm>
#include <set>
#include <array>

#include <cstdlib>
#include <cstdint>
#include <cassert>

namespace {

// --- General input and output ---

const std::string version = "0.0.9";
const std::string date = "29.6.2018";

const std::string program = "autL1";

enum class Error {
  file_reading=1,
  file_writing=2,
  file_pline=3,
  num_vars=4,
  allocation=5,
  literal_read=6,
  variable_value=7,
  number_clauses=8,
  empty_clause=9
};
/* Extracting the underlying code of enum-classes (scoped enums) */
template <typename EC>
inline constexpr int code(const EC e) noexcept {return static_cast<int>(e);}


// Error output with ERROR-prefix, and each on a new line:
struct Outputerr {
  const std::string e = "ERROR[" + program + "]: ";
  template <typename T>
  const Outputerr& operator <<(const T& x) const {
    std::cerr << e << x << "\n";
    return *this;
  }
};
Outputerr errout;

/* Class for output-objects solout and logout, which are initialised
   by function set_output from the command-line parameters. The two
   public members (besides the constructor) are
     out << x;
     out.endl();
  which send the output to the internally stored ostream *p, if set.
  The destructor deletes *p iff member del = true.
*/
class Output {
  std::ostream* p = nullptr;
  bool del = false;
  friend void set_output(const int, const char* const*) noexcept;
public :
  ~Output() { if (del) delete p; }
  template <typename T>
  const Output& operator <<(const T& x) const { if (p) *p << x; return *this; }
  void endl() const { if (p) {*p << "\n"; p->flush();} }
};
Output solout;
Output logout;

/* Assuming argv starts with
     input [output] [log]
   and setting solout, logout accordingly, with special cases for "-nil"
   (discarding output) and "-cout", "-cerr" and "-clog", while otherwise
   files are created (for output=log only one file):
*/
void set_output(const int argc, const char* const argv[]) noexcept {
  std::ios_base::sync_with_stdio(false);
  logout.p = &std::cout;
  if (argc == 2) { solout.p = &std::cout; return; }
  const std::string outname(argv[2]);
  if (outname == "-cout") solout.p = &std::cout;
  else if (outname == "-cerr") solout.p = &std::cerr;
  else if (outname == "-clog") solout.p = &std::clog;
  else if (outname != "-nil") {
    solout.p = new std::ofstream(outname, std::ios::app);
    if (not *solout.p) {
      errout << ("Invalid output file: \"" + outname + "\".");
      std::exit(code(Error::file_writing));
    }
    solout.del = true;
  }
  if (argc == 3) return;
  const std::string logname(argv[3]);
  if (logname == "-cerr") logout.p = &std::cerr;
  else if (logname == "-clog") logout.p = &std::clog;
  else if (logname == "-nil") logout.p = nullptr;
  else if (logname != "-cout") {
    if (logname == outname) logout.p = solout.p;
    else {
      logout.p = new std::ofstream(logname, std::ios::app);
      if (not *logout.p) {
        errout << ("Invalid output file: \"" + logname + "\".");
        std::exit(code(Error::file_writing));
      }
      logout.del = true;
    }
  }
}

/* Input object, initialised with a "filename", which can be "-cin", in which
   case the input comes from standard input; for objects in of type Input,
   the instream is accessed via *in:
*/
class Input {
  std::istream* const p;
  const bool del;
  Input(const Input&) = delete;
  Input(Input&&) = delete;
public :
  Input(const std::string& f) : p(f == "-cin" ? &std::cin : new std::ifstream(f)), del(f != "-cin") {
    if (not *p) {
      errout << "Invalid input filename.";
      std::exit(code(Error::file_reading));
    }
  }
  ~Input() { if (del) delete p; }
  std::istream& operator *() const { return *p; }
};


// --- Data structures for literals and variables ---

/*
  The basic classes are Var (variables) and Lit (literals), where
  Lit contains Lit_int, "Literals as integers", which are signed integers,
  while variables are unsigned.

  Polarities pos, neg are expressed via the enumeration-type Pol.

  Operations for Lit_int x, Lit y,y', Var v, Pol p:

   - Lit() (the singular literal)
   - copy-construction, assignment for Lit
   - Lit(x) (non-converting)
   - Lit(v, p)
   - bool(y) (explicit; true iff x is not singular)
   - -y, -p
   - y == y', y != y'
   - var(y) (yields Var)
   - sign(y) (yields Polarity)
   - ostream << y, istream >> y

   Lit-literals are constructed by n_l for unsigned long-long n.
*/

#ifndef LIT_TYPE
# define LIT_TYPE std::int32_t
#endif
typedef LIT_TYPE Lit_int;
static_assert(std::is_signed<Lit_int>::value, "Type \"Lit_int\" must be signed integral.");
static_assert(sizeof(Lit_int) != 1, "Lit_int = char (or int8_t) doesn't work with reading (since not numbers are read, but characters).");
constexpr Lit_int max_lit = std::numeric_limits<Lit_int>::max();
static_assert(- -max_lit == max_lit, "Problem with negating max_lit.");

typedef std::make_unsigned<Lit_int>::type Var;
static_assert(Lit_int(Var(max_lit)) == max_lit, "Problem with Var and Lit_int.");
inline constexpr bool valid(const Var v) noexcept { return v <= Var(max_lit); }

enum class Pol { n, p };
inline constexpr Pol operator -(const Pol p) noexcept {
  return (p==Pol::p) ? Pol::n : Pol::p;
}
constexpr std::array<Pol,2> Polarities {{Pol::n, Pol::p}};

static_assert(std::is_pod<Pol>::value, "Pol is not POD.");
static_assert(static_cast<int>(Pol::n) == 0, "Pol::n != 0.");
static_assert(static_cast<int>(Pol::p) == 1, "Pol::p != 1.");
static_assert(Pol::n < Pol::p, "Order problem with Pol.");
static_assert(-Pol::n == Pol::p and -Pol::p == Pol::n, "Negation problem with Pol.");
static_assert(Pol(false) == Pol::n and Pol(true) == Pol::p, "Conversion problem from bool to Pol.");
static_assert(Pol(0) == Pol::n and Pol(1) == Pol::p, "Conversion problem from int to Pol.");
static_assert(Polarities.size() == 2 and Polarities[0] == Pol::n and Polarities[1] == Pol::p, "Problem with array Polarities");

class Lit {
  Lit_int x;
public :
  Lit() = default;
  constexpr explicit Lit(const Lit_int x) noexcept : x(x) {}
  constexpr Lit(const Var v, const Pol p) noexcept : x(p==Pol::p?v:-Lit_int(v)) {}
  constexpr explicit operator bool() const noexcept { return x; }
  constexpr Lit operator -() const noexcept { return Lit(-x); }
  constexpr bool operator ==(const Lit y) const noexcept { return x == y.x; }
  constexpr bool operator !=(const Lit y) const noexcept { return x != y.x; }
  friend constexpr Var var(const Lit x) noexcept { return std::abs(x.x); }
  friend constexpr Pol sign(const Lit x) noexcept {return Pol(x.x >= 0);}
  friend std::ostream& operator <<(std::ostream& out, const Lit x) {
    return out << x.x;
  }
  friend std::istream& operator >>(std::istream& in, Lit& x) {
    return in >> x.x;
  }
};
static_assert(std::is_pod<Lit>::value, "Lit is not POD.");

inline constexpr Lit operator"" _l(const unsigned long long x) noexcept {return Lit(x);}
static_assert(0_l == Lit(), "Problem with default construction of Lit.");
// Remark: As usual, as a local variable, the declaration "Lit x;" does not
// initialise x.
static_assert(1_l==Lit(1) and -1_l==Lit(-1), "Problem with construction of Lit.");
static_assert(not 0_l, "Problem with conversion of singular literal to bool.");
static_assert(1_l and -1_l, "Problem with conversion of valid literal to bool.");
static_assert(1_l != -1_l, "Problem with negation and/or inequality.");
static_assert(- -1_l == 1_l, "Problem with double negation.");
static_assert(0_l == -0_l, "Problem with negation of singular literal.");
static_assert(var(-1_l) == 1, "Problem with var().");
static_assert(sign(-1_l) == Pol::n, "Problem with sign().");
static_assert(1_l == Lit(1,Pol::p) and -1_l == Lit(1,Pol::n), "Problem with polarity.");

typedef std::vector<Lit> Lit_vec;


// --- Data structures for clause and clause-sets ---

typedef std::uint_fast64_t Count_t;

struct InputParameter {
  Var n;
  Count_t c;
};

typedef std::set<Var> Varset;
typedef std::set<Varset> VarSetsystem;
typedef std::set<VarSetsystem>::const_iterator Dependency;
typedef std::vector<Dependency> Dvector;

struct VarManagement {
  Varset A, E;
  Dvector D;
};

typedef std::set<Lit> Clause;
typedef std::pair<Clause,Clause> DClause;
typedef std::set<DClause> DCLS;

struct ClauseSet {
  DCLS F;
  Varset A, E;
  Var na, ne, n;
  Count_t t; // number of tautological clauses
  Count_t c;
};


// --- Input ---


// Aborts via std::exit in case of input-errors:
InputParameter read_header(std::istream& f) noexcept {
  InputParameter ip;
  std::string line;
  assert(f.good());
  while (true) {
    std::getline(f, line);
    const auto c = line[0];
    if (c == '\0') { // empty line
      errout << "Empty line (no p-line found).";
      std::exit(code(Error::file_reading));
    }
    if (c == 'p') break;
    if (c != 'c') {
      errout << "Comment lines must start with \"c\".";
      std::exit(code(Error::file_reading));
    }
  }
  assert(line[0] == 'p');
  std::stringstream s(line);
  {std::string inp; s >> inp;
   if (inp != "p") {
     errout << "Syntax error in parameter line (\"p\" not followed by space).";
     std::exit(code(Error::file_pline));
   }
   assert(s);
   if (s.eof()) {
     errout << "Syntax error in parameter line (p-line ends after \"p\").";
     std::exit(code(Error::file_pline));
   }
   s >> inp;
   if (not s or inp != "cnf") {
     errout << "Syntax error in parameter line (no \"cnf\").";
     std::exit(code(Error::file_pline));
   }
  }
  s >> ip.n;
  if (not s) {
    errout << "Reading error with parameter maximal-variable-index "
      "(too big or not-a-number).";
    std::exit(code(Error::file_pline));
  }
  if (not valid(ip.n)) {
    errout << "Parameter maximal-variable-index n=" << ip.n <<
      " is too big for numeric_limits<Lit_int>::max=" << max_lit << ".";
    std::exit(code(Error::num_vars));
  }
  s >> ip.c;
  if (not s) {
    errout << "Reading error with parameter number-of-clauses "
      "(too big or not-a-number).";
    std::exit(code(Error::file_pline));
  }
  if (not s.eof()) {
    errout << "Syntax error in parameter line (something after c-parameter).";
    std::exit(code(Error::file_pline));
  }
  return ip;
}

VarManagement read_dependencies(std::istream& f, const InputParameter& ip) noexcept {
  VarManagement V;
  try { V.D.resize(ip.n); }
  catch (const std::bad_alloc&) {
    errout << "Allocation error for dependency-vector of size " <<
      ip.n << ".";
    std::exit(code(Error::allocation));
  }
  return V;
}


typedef std::int_fast64_t Rounds;

// Returns false iff no (further) clause was found;
// reference-parameter C is empty iff a tautological clause was found:
inline bool read_a_clause_from_file(std::istream& f, Lit_vec& C) {
  {static std::vector<Rounds> literal_table(n_vars+1,0);
   static Rounds round = 0;
   Lit x;
   assert(f.good());
   f >> x;
   if (f.eof()) {
     literal_table.clear(); literal_table.shrink_to_fit();
     return false;
   }
   C.clear();
   assert(round != std::numeric_limits<Rounds>::max());
   ++round;
   while (true) { // reading literals into C
     if (not f) {
       errout << "Invalid literal-read.";
       std::exit(code(Error::literal_read));
     }
     assert(f.good());
     if (not x) break; // end of clause
     const Var v = var(x);
     if (v > n_vars) {
       errout << "Literal " << x << " contradicts n=" << n_vars << ".";
       std::exit(code(Error::variable_value));
     }
     const auto t = literal_table[v];
     const auto comp = (sign(x) == Pol::p) ? round : -round;
     if (t == -comp) { // tautology
       C.clear();
       do
         if (not (f >> x)) {
           errout << "Invalid literal-read in tautological clause.";
           std::exit(code(Error::literal_read));
         }
       while (x);
       return true;
     }
     else if (t != comp) {
       C.push_back(x);
       literal_table[v] = comp;
     }
     f >> x;
   }
  }
  if (C.empty()) {
    errout << "Found empty clause in input.";
    std::exit(code(Error::empty_clause));
  }
  return true;
}

// Error only if announced number of clauses too small (but may be too big):
inline void add_a_clause_to_formula(const Lit_vec& D) {
  const auto n = D.size();
  if (n == 0) { // means tautology here
    ++n_taut;
    return;
  }
  if (n_clauses >= n_header_clauses) {
    errout << "More than " << n_header_clauses << " clauses, contradicting cnf-header.";
    std::exit(number_clauses_error);
  }
  // XXX
  ++n_clauses;
  n_lit_occurrences += n;
}

ClauseSet read_clauses(std::istream& in, const InputParameter& ip, const VarManagement& V) {
  ClauseSet F;
  {Lit_vec C;
   while (read_a_clause_from_file(in,C)) add_a_clause_to_formula(C);
  }
  try { lits.init(n_lit_occurrences, max_occ_var, clauses.cl, count); }
  catch (const std::bad_alloc&) {
    errout << "Allocation error for ClauseP-vector of size " <<
       n_lit_occurrences << " (the number of literal occurrences).";
    std::exit(code(Error::allocation));
  }
  return F;
}


// --- Output ---

void show_usage() {
  std::cout << "USAGE:\n"
    "> " << program << " (-v | --version)\n"
    " shows version informations and exits.\n"
    "> " << program << " (-cin | filename)\n"
    " runs the translator with input from standard input or filename.\n"
    "> " << program << " (-cin | filename) (-cout | -cerr | filename2 | -nil)\n"
      " furthermore appends the DIMACS-output to standard output or standard error or filename2, or ignores it\n "
      "(default is -cout).\n"
    "The same redirection can be done with the statistics output (as a third command-argument; default is -cout).\n"
    "For example, with\n"
    "> " << program << " -cin Out -nil\n"
    "input comes from standard input, the translation is put to file Out, and the statistics are discarded.\n"
    "While with\n"
    "> " << program << " In Out Out\n"
    "the input comes from file In, and both translations and statistics are appended to Out "
      "(first the statistics).\n";
  std::exit(0);
}

#define S(x) #x
#define STR(x) S(x)

void version_information() {
  std::cout << program << ":\n"
   " author: Oliver Kullmann\n"
   " url:\n"
   "  https://github.com/OKullmann/oklibrary/blob/master/Satisfiability/Solvers/TawSolver/tawSolver.cpp\n"
   " Version: " << version << "\n"
   " Last change date: " << date << "\n"
   " Macro settings:\n"
   "  LIT_TYPE = " STR(LIT_TYPE) " (with " << std::numeric_limits<Lit_int>::digits << " binary digits)\n"
#ifdef NDEBUG
   " Compiled with NDEBUG\n"
#else
   " Compiled without NDEBUG\n"
#endif
#ifdef __OPTIMIZE__
   " Compiled with optimisation options\n"
#else
   " Compiled without optimisation options\n"
#endif
   " Compilation date: " __DATE__ " " __TIME__ "\n"
#ifdef __GNUC__
   " Compiler: g++, version " __VERSION__ "\n"
#else
   " Compiler not gcc\n"
#endif
#ifdef OKLIB
   " Provided in the OKlibrary " "http://" STR(OKLIB) "\n"
#endif
#ifdef GIT_ID
   " Git ID = " STR(GIT_ID) "\n"
#endif
  ;
  std::exit(0);
}


void output(const std::string filename) {
  logout << "s ";
  logout <<
         "c max_occurring_variable                " << max_occ_var << "\n"
         "c number_of_clauses                     " << n_clauses << "\n"
         "c maximal_clause_length                 " << max_clause_length << "\n"
         "c number_of_literal_occurrences         " << n_lit_occurrences << "\n"
         "c p_param_variables                     " << n_vars << "\n"
         "c p_param_clauses                       " << n_header_clauses << "\n"
         "c number_tautologies                    " << n_taut << "\n"
         "c file_name                             " << filename << "\n"
         "c options                               \"" << options << "\"";
  logout.endl();
}



} // anonymous namespace

int main(const int argc, const char* const argv[]) {
  if (argc == 1) show_usage();
  const std::string filename = argv[1];
  if (filename == "-v" or filename == "--version") version_information();
  if (argc >= 3 and filename == std::string(argv[2])) {
      errout << "Output filename: \"" << argv[2]  << "\" identical with input filename.";
      std::exit(code(Error::file_writing));
  }
  if (argc >= 4 and filename == std::string(argv[3])) {
      errout << "Log filename: \"" << argv[3]  << "\" identical with input filename.";
      std::exit(code(Error::file_writing));
  }

  const Input in(filename);
  set_output(argc, argv);

  const InputParameter ip = read_header(*in);
  const VarManagement V = read_dependencies(*in, ip);
  const ClauseSet F = read_clauses(*in, ip, V);
}
