//
// Created by Daniil Nedaiborsch on 13.04.2020.
//

#pragma once

#include <memory>
#include <vector>
#include <utility>

#include "Lexeme.hpp"
#include "SString.hpp"

using std::pair;
using std::vector;
using std::shared_ptr;

namespace clnt::finders {
    bool isident(char c);
    size_t findNonSpace(SString const&, vector<char> const&);


    typedef shared_ptr<Lexeme> (*Finder) (SString const&, shared_ptr<Lexeme>);

    shared_ptr<Lexeme> findName(SString const&, shared_ptr<Lexeme> = nullptr);
    shared_ptr<Lexeme> findString(SString const&, shared_ptr<Lexeme>);
    shared_ptr<Lexeme> findBackslash(SString const&, shared_ptr<Lexeme>);
    shared_ptr<Lexeme> findOperator(SString const&, shared_ptr<Lexeme>);

    extern vector<Finder> finders;
    void init();


}
